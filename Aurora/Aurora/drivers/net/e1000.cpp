/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  e1000.h -- Intel Ethernet i217 driver
 *
 *  /PROJECT - Aurora Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *  Intel PRO/1000 Ethernet
 * ================================================
 */

#include <drivers\net\e1000.h>
#include <pmmngr.h>
#include <stdio.h>
#include <arch\x86_64\mmngr\kheap.h>
#include <console.h>
#include <string.h>
#include <serial.h>


e1000_dev *i_net_dev = NULL;

#define INTS ((1<<2) | (1<<6) | (1<<7) | (1<<1) | (1<<0) | (1<<17) | (1<<4) | (1<<16))

uint32_t e1000_read_command (uint16_t p_address) {
	if (i_net_dev->e1000_base != 0) {
		x64_outportd (i_net_dev->e1000_base,p_address);
		char *io_data = (char*)(i_net_dev->e1000_base + 4);
		return x64_inportd ((uint16_t)io_data);
	}else 
		return *(uint32_t*)(i_net_dev->e1000_mem_base + p_address);

}

void e1000_write_command (uint16_t p_address, uint32_t p_value) {
	if (i_net_dev->e1000_base != 0) {
		x64_outportd (i_net_dev->e1000_base, p_address);
		x64_outportd (i_net_dev->e1000_base + 4, p_value);  //4
	}else
		*(uint32_t*)(i_net_dev->e1000_mem_base + p_address) = p_value;
}

bool e1000_detect_eeprom () {
	
	uint32_t val = 0;
	e1000_write_command (REG_EEPROM, 0x1);

	for (int i = 0; i < 1000 && ! i_net_dev->eerprom_exists; i++) {
		val = e1000_read_command (REG_EEPROM);
		if (val & 0x10)
			i_net_dev->eerprom_exists = true;
		else
			i_net_dev->eerprom_exists = false;
	}

	return i_net_dev->eerprom_exists;
}


uint32_t e1000_eerprom_read (uint8_t addr) {
	
	uint16_t data = 0;
	uint32_t tmp = 0;
	if (i_net_dev->eerprom_exists) {
		e1000_write_command (REG_EEPROM, (1) | ((uint32_t)(addr) << 8));
		while (! ((tmp = e1000_read_command (REG_EEPROM)) & (1 << 4)));
	} else {
		e1000_write_command ( REG_EEPROM, (1) | ((uint32_t)(addr) << 2));
		while (!((tmp = e1000_read_command (REG_EEPROM)) & (1 << 1)));
	}
	data = (uint16_t)((tmp >> 16) & 0xFFFF);
	return data;
}


bool e1000_read_mac_address () {
	if (i_net_dev->eerprom_exists) {
		printf ("EEPROM exist\n");
		uint32_t temp;
		temp = e1000_eerprom_read (0);
		i_net_dev->mac[0] = temp & 0xff;
		i_net_dev->mac[1] = temp >> 8;
		temp = e1000_eerprom_read (1);
		i_net_dev->mac[2] = temp & 0xff;
		i_net_dev->mac[3] = temp >> 8;
		temp = e1000_eerprom_read (2);
		i_net_dev->mac[4] = temp & 0xff;
		i_net_dev->mac[5] = temp >> 8;
	} else {
		printf ("Applying memory map\n");
		uint8_t * mem_base_mac_8 = (uint8_t*)(i_net_dev->e1000_mem_base + 0x5400);
		uint32_t * mem_base_mac_32 = (uint32_t*) (i_net_dev->e1000_mem_base + 0x5400);
		if (mem_base_mac_32[0] != 0) {
			for (int i = 0; i < 6; i++) {
				i_net_dev->mac[i] = mem_base_mac_8[i];
			}
		}else {
			return false;
		}
	}

	return true;
}

void e1000_interrupt_handler (size_t v, void* p) {
	x64_cli();

	uint32_t icr = e1000_read_command (REG_ICR);

	//e1000_write_command (REG_IMASK, 0x1);
	if (icr & E1000_ICR_RECEIVE) {
		
		uint32_t head = inportd (REG_RXDESCHEAD);

		while (i_net_dev->rx_tail != head){
			_debug_print_ ("E1000 recevied \r\n");
			size_t size = i_net_dev->rx_desc[i_net_dev->rx_tail]->length;
			uint8_t status = i_net_dev->rx_desc[i_net_dev->rx_tail]->status;

			if ((status & 0x1)==0){
				break;
			}
			
			size -= 4;

			_debug_print_ ("E1000 Bytes received -> %d bytes, status 0x%x \r\n", size, status);

			i_net_dev->rx_tail++;
			i_net_dev->rx_tail %= E1000_NUM_RX_DESC;
		}

		if (i_net_dev->rx_tail == head) {
			e1000_write_command (REG_RXDESCTAIL, (head + E1000_NUM_RX_DESC - 1) % E1000_NUM_RX_DESC);
		}else {
			e1000_write_command (REG_RXDESCTAIL, i_net_dev->rx_tail);
		}

	}else if (icr & E1000_ICR_TRANSMIT) {
		_debug_print_ ("E1000 interrupt data transmit \r\n");
	} else if (icr & E1000_ICR_LINK_CHANGE) {
		_debug_print_ ("E1000 interrupt link change %s \r\n", (e1000_read_command(REG_STATUS) & (1<<1)) ? "up" : "down");
	} else {
		_debug_print_ ("E1000 unknown interrupt \r\n");
	}

	e1000_write_command (REG_ICR, 1);
	interrupt_end(i_net_dev->e1000_irq);
	x64_sti();
}
	

void e1000_rx_init () {

	i_net_dev->rx_desc_base = (uint64_t*)pmmngr_alloc();
	memset (i_net_dev->rx_desc_base, 0, 4096);
	uint64_t rx_desc_base = (uint64_t)i_net_dev->rx_desc_base;

	for (int i = 0; i < E1000_NUM_RX_DESC; i++) {
		i_net_dev->rx_desc[i] = (e1000_rx_desc*)(i_net_dev->rx_desc_base + (i * 16));
		i_net_dev->rx_desc[i]->addr = (uint64_t)pmmngr_alloc();   
		i_net_dev->rx_desc[i]->status = 0;
	}



	e1000_write_command (REG_RXDESCLEN, E1000_NUM_RX_DESC * 16);

	e1000_write_command(REG_RXDESCHEAD, 0);
	e1000_write_command(REG_RXDESCTAIL, E1000_NUM_RX_DESC - 1);

	e1000_write_command (REG_RXDESCKHI, rx_desc_base >> 32);
	e1000_write_command (REG_RXDESCLO, rx_desc_base);
	
	i_net_dev->rx_tail = 0;

	e1000_write_command (REG_RCTRL, RCTL_EN | (1<<2) | 
		(1<<4) | (1<<15) | (1<<25) | (3<<16) | (1<<26));
}


void e1000_tx_init () {

	i_net_dev->tx_desc_base = (uint64_t*)pmmngr_alloc();
	uint64_t base_address = (uint64_t)i_net_dev->tx_desc_base;
	for (int i = 0; i < E1000_NUM_TX_DESC; i++) {
		i_net_dev->tx_desc[i] = (e1000_tx_desc*)(i_net_dev->tx_desc_base + (i * 16));
		i_net_dev->tx_desc[i]->addr = (uint64_t)pmmngr_alloc();
		i_net_dev->tx_desc[i]->cmd = (1<<0);
	}
	e1000_write_command (REG_TXDESCHI, base_address >> 32);
	e1000_write_command (REG_TXDESCLO, base_address);

	e1000_write_command (REG_TXDESCLEN, E1000_NUM_TX_DESC * 16);

	e1000_write_command (REG_TXDESCHEAD, 0);
	e1000_write_command (REG_TXDESCTAIL,0);
	i_net_dev->tx_tail = 0;

	uint32_t tctl = e1000_read_command (REG_TCTRL);
	tctl &= ~(0xFF << 4);
	//tctl |= (15<<4);

	tctl |= TCTL_EN;
	tctl |= TCTL_PSP;
	tctl |= (1<<24);
	e1000_write_command(REG_TCTRL,tctl);

}

void e1000_setup_interrupt () {
	e1000_write_command (0xD8, 0xFFFF);
	e1000_write_command (0xD0, 0xFFFF);
	e1000_read_command (0xc0);
}

void e1000_send_packet (void* data, size_t size) {
	uint32_t cur, head;
	
	cur = e1000_read_command (REG_TXDESCTAIL) % E1000_NUM_TX_DESC; //i_net_dev->tx_tail;
	printf ("CUR Tx tail -> %d\n", cur);
	i_net_dev->tx_tail++;
	i_net_dev->tx_tail %= E1000_NUM_TX_DESC;

	head = e1000_read_command(REG_TXDESCHEAD);
	if (i_net_dev->tx_tail == head) {
		i_net_dev->tx_tail = cur;
		return;
	}

	if (size > 2048) {  //max buffer size 2048 (2KB)
		size = 2048;
	}

	

	i_net_dev->tx_desc[cur]->cmd = CMD_EOP | CMD_IFCS | CMD_RS; // | CMD_RPS | CMD_IDE;
	i_net_dev->tx_desc[cur]->length = size;
	memcpy ((void*)i_net_dev->tx_desc[cur]->addr, data, size);
	e1000_write_command(REG_TXDESCTAIL, i_net_dev->tx_tail);
	printf ("TX Next tail -> %d\n", e1000_read_command (REG_TXDESCTAIL) % E1000_NUM_TX_DESC);
	for(;;) {
		if (i_net_dev->tx_desc[cur]->status) {
			printf ("Transmit status ->%x\n", i_net_dev->tx_desc[cur]->status);
			printf ("Transmitted\n");
			break;
		}
	}
}

void e1000_handle_receive () {
	for(;;) {
	if((i_net_dev->rx_desc[i_net_dev->rx_tail]->status)) {
		//printf ("E1000 New Packet received #1\n");
		uint8_t *buf = (uint8_t*)i_net_dev->rx_desc[i_net_dev->rx_tail]->addr;
		uint16_t len = i_net_dev->rx_desc[i_net_dev->rx_tail]->length;
		//printf ("E1000 New Packet received #2\n");
		i_net_dev->rx_desc[i_net_dev->rx_tail]->status = 0;
		uint16_t old_cur = i_net_dev->rx_tail;
		i_net_dev->rx_tail = (i_net_dev->rx_tail + 1) % E1000_NUM_RX_DESC;
		e1000_write_command (REG_RXDESCTAIL, old_cur);
		printf ("E1000 New Packet received #3\n");
		break;
	}
	}
}

void e1000_reset () {
	e1000_write_command (REG_CTRL, (1<<31));
	for (int i = 0; i < 1000; i++)
		;
	//! Reset the hardware guide from MINIX3
	e1000_write_command (REG_CTRL, (1 << 26));
	for (int i = 0; i < 1000; i++)
		;
	e1000_write_command (REG_CTRL, (1<<0));

	e1000_write_command (REG_CTRL, (1<<3));
	for (int i = 0; i < 1000; i++)
		;
	e1000_write_command (REG_CTRL, (1<<6));
	for (int i = 0; i < 1000; i++)
		;
	e1000_write_command (REG_CTRL, (1<<11));
	e1000_write_command (REG_CTRL, ~(1<<3));
	for (int i = 0; i < 1000;i++)
		;
	e1000_write_command (REG_CTRL, ~(1<<31));

	e1000_write_command (REG_FCAL, 0);
	e1000_write_command (REG_FCAH, 0);
	e1000_write_command (REG_FCT, 0);
	e1000_write_command (REG_FCTTV, 0);
	//e1000_write_command (REG_CTRL, (1<<30));

	for (int i = 0; i < 1000; i++)
		;
	


}


void e1000_initialize () {
	int func, dev_, bus = 0;
	pci_device_info *dev = (pci_device_info*)pmmngr_alloc();
	if (!pci_find_device_class (0x02,0x00, dev,&bus, &dev_, &func)) {
		_debug_print_ ("Intel Ethernet not found\n");
		return;
	}

	uint16_t command = 0;
	read_config_16 (0,bus,dev_,func,0x4,&command);
	if (((command >> 10) & 0xff) != 0) {
		_debug_print_ ("E1000 INterrupt Disabled in PCI ConfigSpace\n");
	}

	i_net_dev = (e1000_dev*)malloc(sizeof(e1000_dev));
    
    i_net_dev->e1000_mem_base = dev->device.nonBridge.baseAddress[1] & ~0xf;

	for (int i = 0; i < 6; i++) {
		if ( dev->device.nonBridge.baseAddress[i] & 1){
			  //TODO:Auto search  4
			
	        i_net_dev->e1000_base = dev->device.nonBridge.baseAddress[i] & ~3; 
			break;
		}
	}
	i_net_dev->e1000_irq = dev->device.nonBridge.interruptLine;
	bool pci_status = pci_alloc_msi (func, dev_, bus, e1000_interrupt_handler);
	if (pci_status) {
		_debug_print_ ("E1000 Supports MSI\n");
	}
	if (!pci_status) {
		if (dev->device.nonBridge.interruptLine != 255) {
			_debug_print_("E1000 legacy irq -> %d, pin -> %d\n", dev->device.nonBridge.interruptLine, dev->device.nonBridge.interruptPin);
			write_config_8 (0,bus,dev_,func,0x3C, 10);
			read_config_8 (0,bus, dev_, func, 0x3C,&dev->device.all.interruptLine);
			interrupt_set (10, e1000_interrupt_handler,dev->device.nonBridge.interruptLine);
		}
	}

	pci_enable_bus_master (bus,dev_,func);

	
	e1000_write_command (REG_RCTRL, 0);
	e1000_write_command (REG_TCTRL, TCTL_PSP);
	e1000_read_command (REG_STATUS);
	for (int i = 0; i < 10000; i++)
		;

	uint32_t ctrl = e1000_read_command(REG_CTRL);
	ctrl |= CTRL_RST;
	e1000_write_command(REG_CTRL, ctrl);
	for (int i = 0; i < 20000; i++)
		;

	e1000_write_command (REG_IMC, 0xFFFFFFFF);
	e1000_write_command (REG_ICR, 0xFFFFFFFF);
	e1000_read_command (REG_STATUS);

	e1000_write_command(0x0028, 0x002C8001);
	e1000_write_command(0x002c, 0x0100);
	e1000_write_command(0x0030, 0x8808);
	e1000_write_command(0x0170, 0xFFFF);

	/* Link up */
	uint32_t status = e1000_read_command (REG_CTRL);
	status |= CTRL_SLU;
	status |= (2<<8);
	status &= ~CTRL_LRST;
	status &= ~CTRL_PHY_RST;
	e1000_write_command(REG_CTRL, status);

	for (int i = 0; i < 128; ++i) {
		e1000_write_command (REG_MTA + i * 4, 0);
	}

	for (int i = 0; i < 64; ++i) {
		e1000_read_command (0x4000 + i * 4);
	}


	e1000_rx_init ();
	e1000_tx_init ();

	e1000_write_command (REG_RDTR, 0);
	e1000_write_command (REG_ITR, 500);
	e1000_read_command (REG_STATUS);


	e1000_write_command (REG_IMASK, INTS);

	for (int i = 0; i < 10000; i++)
		;

	if (e1000_read_mac_address()) {
		//! Set the MAC address code
		_debug_print_ ("MAC Address read successfully\n");
	}
	_debug_print_ ("e1000 setup completed\n");
}
