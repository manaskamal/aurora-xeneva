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
#include <arch\x86_64\mmngr\kheap.h>
#include <hal.h>

typedef struct _e1000_nic_ {
	uint32_t mmio_addr;
	e1000_rx_desc *rx;
	e1000_tx_desc *tx;
	uintptr_t rx_phys;
	uintptr_t tx_phys;
	int irq;
	int rx_index;
	int tx_index;
	int link_status;
	uint8_t has_eeprom;
	uint8_t mac[5];
}e1000_nic_dev;

e1000_nic_dev *e1000_nic;
bool first_interrupt = false;

#define INTS (ICR_LSC | ICR_RXO | ICR_RXT0 | ICR_TXQE | ICR_TXDW | ICR_ACK | ICR_RXDMT0 | ICR_SRPD)
#define CTRL_PHY_RST (1UL << 31UL)
#define CTRL_RST     (1UL << 26UL)
#define CTRL_SLU     (1UL << 6UL)
#define CTRL_LRST    (1UL << 3UL)

uint32_t mmio_read32(uintptr_t addr) {
	return *((volatile uint32_t*)(addr));
}

void mmio_write32(uintptr_t addr, uint32_t val) {
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
	printf ("E1000 interrupt handler++\n");
	if (!first_interrupt)
		first_interrupt = true;
	e1000_write_command(e1000_nic, E1000_REG_ICR, status);
}

	

void e1000_disable_interrupt (e1000_nic_dev *dev) {
	e1000_write_command(dev, E1000_REG_IMC, 0xFFFFFFFF);
	e1000_write_command(dev, E1000_REG_ICR, 0xFFFFFFFF);
	e1000_read_command (dev, E1000_REG_STATUS);
}

void e1000_init_rx (e1000_nic_dev * dev) {
	e1000_write_command(dev, E1000_REG_RXDESCLO, dev->rx_phys);
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
	e1000_write_command(dev, E1000_REG_TXDESCLO, dev->tx_phys);
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

/*
 * AuDriverUnload -- Frees and clear up everthing of e1000 driver
 * turn e1000 off!
 */
AU_EXTERN AU_EXPORT int AuDriverUnload() {
	return 0;
}
/*
 * AuDriverMain -- Main entry for e1000 driver
 */
AU_EXTERN AU_EXPORT int AuDriverMain() {
	printf ("[driver]: Initializing e1000 network driver \n");
	int bus, dev_, func = 0;
	pci_device_info dev; 
	if (!pci_find_device_class (0x02,0x00, &dev,&bus, &dev_, &func)) {
		printf ("[driver]: e1000 not found\n");
		return 1;
	}

	
	e1000_nic_dev *e1000_dev = (e1000_nic_dev*)malloc(sizeof(e1000_nic_dev));
	e1000_nic = e1000_dev;
	e1000_dev->rx_phys = (uintptr_t)AuPmmngrAllocBlocks(2);
	e1000_dev->rx = (e1000_rx_desc*)e1000_dev->rx_phys;
	
	e1000_dev->tx_phys = (uintptr_t)AuPmmngrAllocBlocks(2);
	e1000_dev->tx = (e1000_tx_desc*)e1000_dev->tx_phys;
	
	memset(e1000_dev->rx, 0, sizeof(e1000_rx_desc) * 512);
	memset(e1000_dev->tx, 0, sizeof(e1000_tx_desc) * 512);
	
	for (int i = 0; i < 512; ++i) {
		e1000_dev->rx[i].addr = (uint64_t)AuPmmngrAlloc();
		e1000_dev->rx[i].status = 0;
	}

	for (int i = 0; i < E1000_NUM_TX_DESC; ++i) {
		e1000_dev->tx[i].addr = (uint64_t)AuPmmngrAlloc();
		e1000_dev->tx[i].status = 0;
		e1000_dev->tx[i].cmd = (1<<0);
	}

	pci_enable_bus_master(bus,dev_,func);

	e1000_dev->mmio_addr = (uintptr_t)dev.device.nonBridge.baseAddress[0];

	e1000_eeprom_detect(e1000_dev);
	
	e1000_read_mac(e1000_dev);
	for (uint8_t i = 0; i < 6; i++)
		printf ("%x:", e1000_dev->mac[i]);
	
	printf ("\n");


	e1000_write_mac(e1000_dev);

	e1000_dev->irq = dev.device.nonBridge.interruptLine;
	printf ("[driver]: e1000 irq -> %d \n", e1000_dev->irq);
	AuInterruptSet(e1000_dev->irq, e1000_handler, e1000_dev->irq);

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

	AuEnableInterrupts();
	for(;;) {
		if (first_interrupt)
			break;
	}
	AuDisableInterupts();
	printf ("[driver]: e1000 initialized \n");
	return 0;
}

