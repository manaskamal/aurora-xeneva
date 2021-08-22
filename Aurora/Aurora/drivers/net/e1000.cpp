/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  e1000.h -- Intel Ethernet i217 driver
 *
 *  /PROJECT - Aurora Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ================================================
 */

#include <drivers\net\e1000.h>
#include <pmmngr.h>
#include <stdio.h>
#include <mm.h>
#include <console.h>


e1000_dev *i_net_dev = NULL;

uint32_t e1000_read_command (uint16_t p_address) {
	x64_outportd (i_net_dev->e1000_base,p_address);
	char *io_data = (char*)i_net_dev->e1000_base + 4;
	return x64_inportd ((uint16_t)io_data);
}

void e1000_write_command (uint16_t p_address, uint32_t p_value) {
	x64_outportd (i_net_dev->e1000_base, p_address);
	x64_outportd (i_net_dev->e1000_base + 4, p_value);  //4
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
	printf ("E1000 Interrupt fired\n");
	//apic_local_eoi();
	interrupt_end(i_net_dev->e1000_irq);
}
	

void e1000_rx_init () {
	uint64_t tmp_base = (uint64_t)malloc ((sizeof(e1000_rx_desc) * E1000_NUM_RX_DESC) + 16);
	memset ((void*)tmp_base, 0,(sizeof(e1000_rx_desc) * E1000_NUM_RX_DESC) + 16); 
	i_net_dev->rx_desc_base = (tmp_base % 16) ? (uint8_t*)((tmp_base) + 16 - (tmp_base % 16)) : (uint8_t*)tmp_base;
	e1000_rx_desc *rx_desc[E1000_NUM_RX_DESC];
	for (int i = 0; i < E1000_NUM_RX_DESC; i++) {
		rx_desc[i] = (e1000_rx_desc*)(i_net_dev->tx_desc_base + (i * 16));
		rx_desc[i]->addr = (uint64_t)pmmngr_alloc();   //malloc(8192+16);
		rx_desc[i]->status = 0;
	}

	e1000_write_command (REG_RXDESCKHI, (uint32_t)get_physical_address((uint64_t)i_net_dev->rx_desc_base) >> 32);
	e1000_write_command (REG_RXDESCLO,(uint32_t)get_physical_address((uint64_t)i_net_dev->rx_desc_base) & 0xFFFFFFFF);

	printf ("E1000 RX Descriptor HI -> %x, LO -> %x\n", e1000_read_command(REG_RXDESCKHI), e1000_read_command(REG_RXDESCLO));
	e1000_write_command (REG_RXDESCLEN, (uint32_t)(E1000_NUM_RX_DESC * 16));

	e1000_write_command(REG_RXDESCHEAD, 0);
	e1000_write_command(REG_RXDESCTAIL, E1000_NUM_RX_DESC);
	i_net_dev->rx_tail = 0;

	e1000_write_command (REG_CTRL, (RCTL_SBP | RCTL_UPE | RCTL_MPE | RTCL_RDMTS_HALF | RCTL_SECRC | 
		RCTL_LPE | RCTL_BAM | RCTL_BSIZE_8192));
}


void e1000_tx_init () {

	uint64_t tmp_base = (uint64_t)malloc((sizeof(e1000_tx_desc) * E1000_NUM_TX_DESC) + 16);
	memset ((void*)tmp_base, 0, (sizeof(e1000_tx_desc) * E1000_NUM_TX_DESC) + 16);
	i_net_dev->tx_desc_base = (tmp_base % 16) ? (uint8_t*)((tmp_base) + 16 - (tmp_base % 16)) : (uint8_t*)tmp_base;
	e1000_tx_desc *tx_desc[E1000_NUM_TX_DESC];
	for (int i = 0; i < E1000_NUM_TX_DESC; i++) {
		tx_desc[i] = (e1000_tx_desc*)(i_net_dev->tx_desc_base + (i * 16));
		tx_desc[i]->addr = 0;
		tx_desc[i]->cmd = 0;
	}
	e1000_write_command (REG_TXDESCHI, (uint32_t)get_physical_address((uint64_t)i_net_dev->tx_desc_base) >> 32);
	e1000_write_command (REG_TXDESCLO, (uint32_t)get_physical_address((uint64_t)i_net_dev->tx_desc_base) & 0xFFFFFFFF);
	printf ("E1000 TX_DESC_HI -> %x, LO -> %x\n", e1000_read_command(REG_TXDESCHI), e1000_read_command(REG_TXDESCLO));

	e1000_write_command (REG_TXDESCLEN, (uint32_t)(E1000_NUM_TX_DESC * 16));

	e1000_write_command (REG_TXDESCHEAD, 0);
	e1000_write_command (REG_TXDESCTAIL, E1000_NUM_TX_DESC);
	i_net_dev->tx_tail = 0;


	e1000_write_command (REG_TCTRL, (TCTL_EN | TCTL_PSP));
}

void e1000_setup_interrupt () {
	e1000_write_command (0xD8, 0xFFFF);
	e1000_write_command (0xD0, 0xFFFF);
	e1000_read_command (0xc0);
}

void e1000_tx_poll (void* pkt, uint16_t length) {
	i_net_dev->tx_tail = e1000_read_command (REG_TXDESCHEAD);
	printf ("TxTail -> %d\n", i_net_dev->tx_tail);
	i_net_dev->tx_desc[i_net_dev->tx_tail]->addr = (uint64_t)pkt;
	i_net_dev->tx_desc[i_net_dev->tx_tail]->length = length;
	i_net_dev->tx_desc[i_net_dev->tx_tail]->cmd = ((1 << 3) | (3));

	int oldtail = i_net_dev->tx_tail;
	i_net_dev->tx_tail = (i_net_dev->tx_tail + 1) % E1000_NUM_TX_DESC;
	e1000_write_command (REG_TXDESCTAIL, i_net_dev->tx_tail);

	while ( !(i_net_dev->tx_desc[oldtail]->status & 0xF));

	printf ("E1000: Transmit status -> %x\n", (i_net_dev->tx_desc[oldtail]->status & 0xF));
}

void e1000_handle_receive () {
	while ((i_net_dev->rx_desc[i_net_dev->rx_tail]->status & 0x1)) {
		printf ("E1000 New Packet received #1\n");
		uint8_t *buf = (uint8_t*)i_net_dev->rx_desc[i_net_dev->rx_tail]->addr;
		uint16_t len = i_net_dev->rx_desc[i_net_dev->rx_tail]->length;
		printf ("E1000 New Packet received #2\n");
		i_net_dev->rx_desc[i_net_dev->rx_tail]->status = 0;
		uint16_t old_cur = i_net_dev->rx_tail;
		i_net_dev->rx_tail = (i_net_dev->rx_tail + 1) % E1000_NUM_RX_DESC;
		e1000_write_command (REG_RXDESCTAIL, old_cur);
		printf ("E1000 New Packet received #3\n");
	}
}

void e1000_reset () {

	//! Reset the hardware guide from MINIX3
	e1000_write_command (REG_CTRL, (1 << 26));
	for (int i = 0; i < 10; i++)
		;
	e1000_write_command (REG_CTRL, ~(1<<3));
	e1000_write_command (REG_CTRL, ~(1<<31));
	e1000_write_command (REG_CTRL, ~(1<<7));

	e1000_write_command (REG_FCAL, 0);
	e1000_write_command (REG_FCAH, 0);
	e1000_write_command (REG_FCT, 0);
	e1000_write_command (REG_FCTTV, 0);
	
}


void e1000_initialize () {
	pci_device_info *dev = (pci_device_info*)pmmngr_alloc();
	if (!pci_find_device_class (0x02,0x00,dev)) {
		//printf ("Intel Ethernet not found\n");
		return;
	}

	i_net_dev = (e1000_dev*)malloc(sizeof(e1000_dev));
    i_net_dev->e1000_mem_base = dev->device.nonBridge.baseAddress[0] & ~3;

	for (int i = 0; i < 6; i++) {
		if ( dev->device.nonBridge.baseAddress[i] & 1) {
			  //TODO:Auto search  4
			i_net_dev->e1000_base = dev->device.nonBridge.baseAddress[i] & ~1; 
			break;
		}
	}

	//i_net_dev->e1000_base = dev->device.nonBridge.baseAddress[2] & ~1;  //TODO:Auto search 
	i_net_dev->e1000_irq = dev->device.nonBridge.interruptLine;
	

	if (dev->device.nonBridge.interruptLine != 0xFF)
		interrupt_set (dev->device.nonBridge.interruptLine, e1000_interrupt_handler,dev->device.nonBridge.interruptLine);
	
	//!disable all interrupts 
	uint32_t imask = e1000_read_command (REG_IMASK);
	imask |= (1<<0);
	imask |= (1<<1);
	imask |= (1<<2);
	imask |= (1<<3);
	imask |= (1<<4);
	imask |= (1<<5);
	imask |= (1<<6);
	imask |= (1<<7);
	printf ("E1000 Interrupt register -> %x\n", imask);
	e1000_write_command (REG_IMASK, imask);

	e1000_reset();
	e1000_detect_eeprom();
	//!vlan mode
	e1000_write_command (REG_CTRL, (1<<30));

	e1000_write_command (REG_CTRL, (e1000_read_command(REG_CTRL) | ECTRL_SLU));
	for (int i = 0; i < 128; i++)
		e1000_write_command (REG_MTA + (i * 4), 0);

	//!Initialize all statistical counters as per spec section 14.3
	for (int i = 0; i < 64; i++) {
		e1000_write_command (REG_CRCERRS + (i * 4), 0);
	}

	e1000_write_command (REG_IMASK, imask);
	//e1000_write_command (REG_IMASK, 0x1F6DC);
	//e1000_read_command (0xC0);

	if (e1000_read_mac_address()) {
		printf ("E1000 MAC address received\n");
		printf ("E1000 MAC Address: ");
		for (int i = 0; i < 6; i++)
			printf (":%x", i_net_dev->mac[i]);
		printf ("\n");
	}

	e1000_rx_init ();
	e1000_tx_init ();
	pci_print_capabilities(dev);

	e1000_write_command (REG_IMASK, E1000_IMS_LSC | 
		                            E1000_IMS_RXO |
									E1000_IMS_RXT |
									E1000_IMS_TXQE |
									E1000_IMS_TXDW);
	e1000_read_command (0xc0);
	//!verify 
	printf ("E1000 IMASK Reg -> %x\n", e1000_read_command(REG_IMASK));
	//e1000_tx_poll(NULL, 4096);
	//e1000_handle_receive();
}
