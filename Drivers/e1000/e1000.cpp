/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2021, Manas Kamal Choudhury
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 **/

#include "e1000.h"
#include <stdio.h>
#include <aurora.h>
#include <drivers\pci.h>
#include <drivers\pcie.h>
#include <arch\x86_64\mmngr\kheap.h>
#include <hal.h>
#include <fs\vfs.h>
#include <net\aunet.h>
#include <shirq.h>
#include <arch\x86_64\thread.h>
#include <serial.h>

typedef struct _e1000_nic_ {
	uint64_t mmio_addr;
	e1000_rx_desc *rx;
	e1000_tx_desc *tx;
	uint64_t rx_phys;
	uint64_t tx_phys;
	uint8_t* rx_virt[E1000_NUM_RX_DESC];
	uint8_t* tx_virt[E1000_NUM_TX_DESC];
	int irq;
	int rx_index;
	int tx_index;
	int link_status;
	uint8_t has_eeprom;
	uint8_t mac[6];
}e1000_nic_dev;

e1000_nic_dev *e1000_nic;
shirq_t *shared_device;
bool first_interrupt = false;

#define INTS (ICR_LSC | ICR_RXO | ICR_RXT0 | ICR_TXQE | ICR_TXDW | ICR_ACK | ICR_RXDMT0 | ICR_SRPD)
#define CTRL_PHY_RST (1UL << 31UL)
#define CTRL_RST     (1UL << 26UL)
#define CTRL_SLU     (1UL << 6UL)
#define CTRL_LRST    (1UL << 3UL)

uint32_t mmio_read32(uint64_t addr) {
	return *((volatile uint32_t*)(addr));
}

void mmio_write32(uint64_t addr, uint32_t val) {
	(*((volatile uint32_t*)(addr))) = val;
}

void e1000_write_command(e1000_nic_dev * device, uint16_t addr, uint32_t val) {
	mmio_write32(device->mmio_addr + addr, val);
}

uint32_t e1000_read_command (e1000_nic_dev *device, uint16_t addr) {
	return mmio_read32(device->mmio_addr + addr);
}

int e1000_eeprom_detect (e1000_nic_dev * device) {
	e1000_write_command(device, E1000_REG_EEPROM, 1);

	for (int i = 0; i < 10000 && !device->has_eeprom; ++i) {
		uint32_t val = e1000_read_command(device, E1000_REG_EEPROM);
		if (val & 0x10) device->has_eeprom = 1;
	}

	return 0;
}

uint16_t e1000_eeprom_read(e1000_nic_dev *device, uint8_t addr) {
	uint32_t temp = 0;
	e1000_write_command(device, E1000_REG_EEPROM, 1 | ((uint32_t)(addr) << 8));
	while (!((temp = e1000_read_command(device, E1000_REG_EEPROM)) & (1<<4)));
	return (uint16_t)((temp >> 16) & 0xFFFF);
}

void e1000_write_mac(e1000_nic_dev *device) {
	uint32_t low, high;
	memcpy (&low, &device->mac[0], 4);
	memcpy (&high, &device->mac[4], 2);
	memset((uint8_t*)&high + 2, 0, 2);
	high |= 0x80000000;
	e1000_write_command(device, E1000_REG_RXADDR + 0, low);
	e1000_write_command(device, E1000_REG_RXADDR + 4, high);
}

void e1000_read_mac(e1000_nic_dev *device) {
	if (device->has_eeprom) {
		uint32_t t;
		t = e1000_eeprom_read(device, 0);
		device->mac[0] = t & 0xFF;
		device->mac[1] = t >> 8;
		t = e1000_eeprom_read(device, 1);
		device->mac[2] = t & 0xFF;
		device->mac[3] = t >> 8;
		t = e1000_eeprom_read(device, 2);
		device->mac[4] = t & 0xFF;
		device->mac[5] = t >> 8;
	}else {
		uint32_t mac_addr_low = *(uint32_t*)(device->mmio_addr + E1000_REG_RXADDR);
		uint32_t mac_addr_high = *(uint32_t*)(device->mmio_addr + E1000_REG_RXADDR + 4);
		device->mac[0] = (mac_addr_low >> 0) & 0xFF;
		device->mac[1] = (mac_addr_low >> 8) & 0xFF;
		device->mac[2] = (mac_addr_low >> 16) & 0xFF;
		device->mac[3] = (mac_addr_low >> 24) & 0xFF;
		device->mac[4] = (mac_addr_high >> 0) & 0xFF;
		device->mac[5] = (mac_addr_high >> 8) & 0xFF;
	}
}


void e1000_handler (size_t v, void* p) {
	uint32_t status = e1000_read_command(e1000_nic, E1000_REG_ICR);
	if (!first_interrupt)
		first_interrupt = true;

	printf ("e1000 interrupt -> %d \r\n", e1000_nic->irq);
	if (status & ICR_LSC) {
		e1000_nic->link_status = (e1000_read_command(e1000_nic, E1000_REG_STATUS) & (1<<1));
		printf ("e1000: Link status %s \r\n", (e1000_nic->link_status ? "up" : "down"));
	}

	if (status &ICR_RXT0)
		_debug_print_ ("e1000: received packet \r\n");

	e1000_write_command(e1000_nic, E1000_REG_ICR, status);

	
	AuInterruptEnd(e1000_nic->irq);
}

	

void e1000_disable_interrupt (e1000_nic_dev *dev) {
	e1000_write_command(dev, E1000_REG_IMC, 0xFFFFFFFF);
	e1000_write_command(dev, E1000_REG_ICR, 0xFFFFFFFF);
	e1000_read_command (dev, E1000_REG_STATUS);
}

void e1000_init_rx (e1000_nic_dev * dev) {
	e1000_write_command(dev, E1000_REG_RXDESCLO, v2p(dev->rx_phys));
	e1000_write_command(dev, E1000_REG_RXDESCHI, 0);
	e1000_write_command(dev, E1000_REG_RXDESCLEN, E1000_NUM_RX_DESC * sizeof(e1000_rx_desc));
	e1000_write_command(dev, E1000_REG_RXDESCHEAD, 0);
	e1000_write_command(dev, E1000_REG_RXDESCTAIL, E1000_NUM_RX_DESC - 1);

	dev->rx_index = 0;

	e1000_write_command(dev, E1000_REG_RCTRL, RCTL_EN | 
		(1<<2) | 
		(1<<4) | 
		(1<<15) | 
		(1<<25) | 
		(3<<16) | 
		(1<<26)
		);
}

void e1000_init_tx (e1000_nic_dev * dev) {
	e1000_write_command(dev, E1000_REG_TXDESCLO, v2p(dev->tx_phys));
	e1000_write_command(dev, E1000_REG_TXDESCHI, 0);
	e1000_write_command(dev, E1000_REG_TXDESCLEN, E1000_NUM_TX_DESC * sizeof(e1000_tx_desc));
	e1000_write_command(dev, E1000_REG_TXDESCHEAD, 0);
	e1000_write_command(dev, E1000_REG_TXDESCTAIL, 0);

	dev->tx_index = 0;
	uint32_t tctl = e1000_read_command(dev, E1000_REG_TCTRL);

	/* Collision threshold */
	tctl &= ~(0xFF << 4);
	tctl |= (15 << 4);

	/* turn it on */
	tctl |= TCTL_EN;
	tctl |= TCTL_PSP;
	tctl |= (1<<24);

	e1000_write_command(dev, E1000_REG_TCTRL, tctl);
}

void e1000_send_packet (e1000_nic_dev* dev, uint8_t* payload, size_t payload_size) {
	int tx_tail = e1000_read_command(dev,E1000_REG_TXDESCTAIL);
	int tx_head = e1000_read_command(dev,E1000_REG_TXDESCHEAD);

	memcpy(dev->tx_virt[dev->tx_index], payload,payload_size);
	dev->tx[dev->tx_index].length = payload_size;
	dev->tx[dev->tx_index].cmd = CMD_EOP | CMD_IFCS | CMD_RS;
	dev->tx[dev->tx_index].status = 0;

	if (++dev->tx_index == E1000_NUM_TX_DESC)
		dev->tx_index = 0;

	e1000_write_command(dev,E1000_REG_TXDESCTAIL, dev->tx_index);
	e1000_read_command(dev, E1000_REG_STATUS);
}

/*
 * e1000_write_file -- writes to e1000 device 
 * @param file -- e1000 node
 * @param buffer -- buffer to write
 * @param length -- length of the buffer
 */
void e1000_write_file (vfs_node_t *file, uint64_t* buffer, uint32_t length) {
	printf ("[driver]: writing to e1000 file device \n");
	uint8_t* aligned_buf = (uint8_t*)buffer;
	e1000_send_packet(e1000_nic, aligned_buf, length);
}

/*
 * e1000_ioctl -- e1000 file ioquery
 */
int e1000_ioquery (vfs_node_t *file, int code, void* arg) {
	return 1;
}

/*
 * AuDriverUnload -- Frees and clear up everthing of e1000 driver
 * turn e1000 off!
 */
AU_EXTERN AU_EXPORT int AuDriverUnload() {
	return 0;
}


void e1000_thread() {
	int head = e1000_read_command(e1000_nic, E1000_REG_RXDESCHEAD);
	while(1){
		if (head == e1000_nic->rx_index) {
			head = e1000_read_command(e1000_nic, E1000_REG_RXDESCHEAD);
		}

		if (head != e1000_nic->rx_index){
			//printf ("[network]: packet received \n");
			e1000_nic->rx_index = head;
		}
		sleep_thread(get_current_thread(),1000);
		force_sched();
	}
}
/*
 * AuDriverMain -- Main entry for e1000 driver
 */
AU_EXTERN AU_EXPORT int AuDriverMain() {
	printf ("[driver]: Initializing e1000 network driver \n");
	int bus, dev_, func = 0;
	
	uint32_t device = pci_express_scan_class (0x02,0x00,&bus, &dev_, &func);
	if (device == 0xFFFFFFFF){
		printf ("[driver]: e1000 not found\n");
		return 1;
	}

	e1000_nic_dev *e1000_dev = (e1000_nic_dev*)malloc(sizeof(e1000_nic_dev));

	//pci_enable_bus_master(device);
	//pci_enable_interrupts(device);
	printf ("E1000\n");
	pcie_alloc_msi(device, 40, bus, dev_, func);
	

	e1000_nic = e1000_dev;
	e1000_dev->rx_phys = (uint64_t)p2v((size_t)AuPmmngrAllocBlocks(2));
	e1000_dev->rx = (e1000_rx_desc*)e1000_dev->rx_phys;
	
	e1000_dev->tx_phys = (uint64_t)p2v((size_t)AuPmmngrAllocBlocks(2));
	e1000_dev->tx = (e1000_tx_desc*)e1000_dev->tx_phys;
	
	memset(e1000_dev->rx, 0, sizeof(e1000_rx_desc) * 512);
	memset(e1000_dev->tx, 0, sizeof(e1000_tx_desc) * 512);
	
	for (int i = 0; i < 512; ++i) {
		e1000_dev->rx[i].addr = (uint64_t)AuPmmngrAlloc();
		e1000_dev->rx_virt[i] = (uint8_t*)AuMapMMIO(e1000_dev->rx[i].addr, 1);
		e1000_dev->rx[i].status = 0;
	}

	for (int i = 0; i < E1000_NUM_TX_DESC; ++i) {
		e1000_dev->tx[i].addr = (uint64_t)AuPmmngrAlloc();
		e1000_dev->tx_virt[i] = (uint8_t*)AuMapMMIO(e1000_dev->tx[i].addr, 1);
		memset(e1000_dev->tx_virt[i],0, 4096);
		e1000_dev->tx[i].status = 0;
		e1000_dev->tx[i].cmd = (1<<0);
	}

	uint64_t mmio = pci_express_read(device, PCI_BAR0, bus ,dev_, func);//dev.device.nonBridge.baseAddress[0];
	printf ("MMIO E1000 -> %x \n", mmio);
	e1000_dev->mmio_addr = (uint64_t)AuMapMMIO(mmio,8);

	e1000_eeprom_detect(e1000_dev);
	e1000_read_mac(e1000_dev);
	for (uint8_t i = 0; i < 6; i++)
		printf ("%x:", e1000_dev->mac[i]);
	
	printf ("\n");


	e1000_write_mac(e1000_dev);

	e1000_dev->irq = pci_express_read(device,PCI_INTERRUPT_LINE, bus, dev_, func);//dev.device.nonBridge.interruptLine;

	if (e1000_dev->irq == 0xFF)
		return 1;

	/*shared_device = (shirq_t*)malloc(sizeof(shirq_t));
	shared_device->irq = e1000_dev->irq;
	shared_device->device_id = dev.device.deviceID;
	shared_device->vendor_id = dev.device.vendorID;
	shared_device->IrqHandler = e1000_handler;
	AuSharedDeviceRegister(shared_device);*/

	if (e1000_dev->irq < 255)
		AuInterruptSet(e1000_dev->irq, e1000_handler,e1000_dev->irq, false);
	//else
	//	AuInstallSharedHandler(e1000_dev->irq, true);*/

	
	e1000_disable_interrupt(e1000_dev);

	/* turn off receive + transmit */
	e1000_write_command(e1000_dev, E1000_REG_RCTRL, 0);
	e1000_write_command(e1000_dev, E1000_REG_TCTRL, TCTL_PSP);
	e1000_read_command(e1000_dev, E1000_REG_STATUS);

	for (int i = 0; i < 100000000; i++)
		;

	/*Reset all */
	uint32_t ctrl = e1000_read_command (e1000_dev, E1000_REG_CTRL);
	ctrl |= CTRL_RST;
	e1000_write_command(e1000_dev, E1000_REG_CTRL, ctrl);
	for (int i = 0; i < 20000; i++)
		;
	/* Turn interrupt off again */
	e1000_disable_interrupt(e1000_dev);


	e1000_write_command (e1000_dev, 0x0028, 0x002C8001);
	e1000_write_command(e1000_dev, 0x002c, 0x0100);
	e1000_write_command(e1000_dev, 0x0030, 0x8808);
	e1000_write_command(e1000_dev, 0x0170, 0xFFFF);

	/*Link up */
	uint32_t status = e1000_read_command(e1000_dev, E1000_REG_CTRL);
	status |= CTRL_SLU;
	status |= (2<<8);
	status &= ~CTRL_LRST;
	status &= ~CTRL_PHY_RST;
	e1000_write_command(e1000_dev, E1000_REG_CTRL, status);

	/* Clear statistical counters */
	for (int i = 0; i < 128; ++i) {
		e1000_write_command(e1000_dev, 0x5200 + i * 4, 0);
	}

	for (int i = 0; i < 64; ++i) {
		e1000_read_command(e1000_dev,  0x4000 + i * 4);
	}

	e1000_init_rx(e1000_dev);
	e1000_init_tx(e1000_dev);

	e1000_write_command(e1000_dev, E1000_REG_RDTR, 0);
	e1000_write_command(e1000_dev, E1000_REG_ITR, 500);
	e1000_read_command(e1000_dev, E1000_REG_STATUS);

	e1000_dev->link_status = (e1000_read_command(e1000_dev, E1000_REG_STATUS) & (1<<1));


	e1000_write_command(e1000_dev, E1000_REG_IMS, INTS);


	vfs_node_t *file = (vfs_node_t*)malloc(sizeof(vfs_node_t));
printf ("FILE e1000 created -> %x \n", file);
	strcpy (file->filename, "e1000");
	file->size = 0;
	file->eof = 0;
	file->pos = 0;
	file->current = 0;
	file->flags = FS_FLAG_GENERAL;
	file->device = e1000_nic;
	file->status = 0;
	file->open = 0;
	file->read = 0;
	file->write = e1000_write_file;
	file->read_blk = 0;
	file->ioquery = e1000_ioquery;
	
	vfs_mount ("/dev/e1000", file, 0);

	


	AuNet_t *net = (AuNet_t*)malloc(sizeof(AuNet_t));
	memset(net->mac, 0, 6);
	memcpy (net->mac, e1000_dev->mac,6);
	memset(net->name, 0, 8);
	strcpy(net->name, "e1000");
	AuNetAddAdapter(file,net);


	/*thread_t *nic_thread = create_kthread(e1000_thread,(uint64_t)p2v((uint64_t)AuPmmngrAlloc() + 4096),(uint64_t)AuGetRootPageTable(),
		"e1000_thr",1);*/
	//pcie_print_capabilities(device);
	
	//AuEnableInterrupts();
	//for(;;) {
	//	if (first_interrupt)
	//		break;
	//}
	//AuDisableInterupts();
	printf ("[driver]: e1000 initialized \n");
	return 0;
}

