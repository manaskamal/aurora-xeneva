/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  amd_am79c973.h -- AMD PCNet FAST III card driver
 *
 *  /PROJECT - Aurora Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ========================================================
 */

#include <drivers\net\amd_am79c973.h>
#include <pmmngr.h>
#include <stdio.h>
#include <mm.h>

size_t amd_io_base = 0;
uint8_t amd_mac[6];
uint32_t amd_irq = 0;
amd_net *a_card_net = nullptr;


void amd_write_bcr (uint16_t bcr, uint16_t value) {
	x64_outportw (amd_io_base + RAP, bcr);
	x64_outportw (amd_io_base, value);
}

void amd_write_csr (uint8_t csr, uint16_t value) {
	x64_outportw (amd_io_base + RAP, csr);
	x64_outportw (amd_io_base + RDP, value);
}

uint16_t amd_read_csr (uint8_t csr) {
	x64_outportw (amd_io_base + RAP, csr);
	return x64_inportw (amd_io_base+RDP);
}


void amd_interrupt_handler (size_t v, void* p) {
	x64_cli();
	printf ("AMD NIC Interrupt handler++\n");
	//apic_local_eoi();
	interrupt_end(amd_irq);
}

void amd_pcnet_initialize () {
	pci_device_info *dev = (pci_device_info*)pmmngr_alloc();
	a_card_net = (amd_net*)pmmngr_alloc();
	//x64_outportw (dev->device.commandReg, ~(1 << 10));
	
	if (!pci_find_device_class (0x02,0x00,dev)) {
		printf ("AMD PCNet card not found\n");
	}
	printf ("AMD Interrupt pin -> %x\n", dev->device.nonBridge.interruptPin);
	amd_io_base = dev->device.nonBridge.baseAddress[0];
	printf ("AMD PCNet card found -> device id -> %x, vendor id -> %x\n", dev->device.deviceID, dev->device.vendorID);
	printf ("AMD Base Address -> %x, -> %x\n", dev->device.nonBridge.baseAddress[0], dev->device.nonBridge.baseAddress[1]);
	printf ("AMD Interrupt line -> %d\n", dev->device.nonBridge.interruptLine);

	amd_irq = dev->device.nonBridge.interruptLine;
	pci_print_capabilities(dev);

	interrupt_set (dev->device.nonBridge.interruptLine, amd_interrupt_handler, dev->device.nonBridge.interruptLine);

	uint16_t temp = x64_inportw (amd_io_base + APROM0);
	amd_mac[0] = temp;
	amd_mac[1] = temp >> 8;
	temp = x64_inportw (amd_io_base + APROM2);
	amd_mac[2] = temp;
	amd_mac[3] = temp >> 8;
	temp = x64_inportw(amd_io_base + APROM4);
	amd_mac[4] = temp;
	amd_mac[5] = temp>>8;


	x64_inportw (amd_io_base + RESET);
	x64_outportw (amd_io_base + RESET, 0);
	for (int i = 0; i < 5; i++)
		;
	amd_write_csr (20,0x0102);

	//!stop
	amd_write_csr (0, 0x04);


	void* rx_buffer = malloc(2048*8);
	void* tx_buffer = malloc(2048*8);
	
	a_card_net->recv_desc = (amd_descriptor*)pmmngr_alloc();
	a_card_net->trans_desc = (amd_descriptor*)pmmngr_alloc();

	for (uint8_t i = 0; i < 8; i++) {
		a_card_net->recv_desc[i].address = (uint32_t)get_physical_address((uint64_t)rx_buffer + i * 2048);
		a_card_net->recv_desc[i].flags = 0x80000000 | 0x0000F000 | (-2048 & 0xFFF);
		a_card_net->recv_desc[i].flags2 = 0;
		a_card_net->recv_desc[i].avail = (uint32_t)rx_buffer + i * 2048;

		a_card_net->trans_desc[i].address = (uint32_t)get_physical_address((uint64_t)tx_buffer+i*2048);
		a_card_net->trans_desc[i].flags = 0x0000F000;
		a_card_net->trans_desc[i].flags2 = 0;
		a_card_net->trans_desc[i].avail = (uint32_t)tx_buffer+i*2048;
	}

	amd_init_block *init_block = (amd_init_block*)pmmngr_alloc();
	memset (init_block, 0, sizeof (amd_init_block));
	init_block->mode = 0x0180;
	init_block->receive_length = 3;
	init_block->transfer_length = 3;
	memcpy (&init_block->physical_address, amd_mac, 6);
	init_block->receive_descriptor = (uint32_t)a_card_net->recv_desc;
	init_block->transmit_descriptor = (uint32_t)a_card_net->trans_desc;
	amd_write_csr(1,(uint16_t)init_block);
	amd_write_csr(2, (uint16_t)init_block >> 16);
	

	printf ("AMD Mac Code -> ");
	for (int i = 0; i < 6; i++)
		printf ("%c", init_block->physical_address[i]);
	printf ("\n");

	//!initialize
	amd_write_csr (0, 0x0041);
	for (int i = 0; i < 1000; i++)
		;
	amd_write_csr (4, 0x4C00 | amd_read_csr (4));
	amd_write_csr (0,0x0042);

	pmmngr_free(init_block);
}