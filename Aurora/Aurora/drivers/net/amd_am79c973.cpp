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

size_t amd_io_base = 0;
uint8_t amd_mac[6];
uint32_t amd_irq = 0;

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

	if (!pci_find_device_class (0x02,0x00,dev)) {
		printf ("AMD PCNet card not found\n");
	}

	amd_io_base = dev->device.nonBridge.baseAddress[0];
	printf ("AMD PCNet card found -> device id -> %x, vendor id -> %x\n", dev->device.deviceID, dev->device.vendorID);
	printf ("AMD Base Address -> %x, -> %x\n", dev->device.nonBridge.baseAddress[0], dev->device.nonBridge.baseAddress[1]);
	printf ("AMD Interrupt line -> %d\n", dev->device.nonBridge.interruptLine);

	amd_irq = dev->device.nonBridge.interruptLine;
	pci_print_capabilities(dev);

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

	//!initialize
	amd_write_csr (0, 0x41);
	for (int i = 0; i < 1000; i++)
		;
	amd_write_csr (4, 0x4C00 | amd_read_csr (4));
	amd_write_csr (0,0x42);

	interrupt_set (dev->device.nonBridge.interruptLine, amd_interrupt_handler, dev->device.nonBridge.interruptLine);
}