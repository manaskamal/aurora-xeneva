/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  xhci.h -- USB extensible host controller interface
 *
 *  /PROJECT - Aurora Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ======================================================
 */

#include <drivers\usb\xhci.h>
#include <drivers\pci.h>
#include <stdio.h>
#include <mm.h>

size_t xhci_base_address = 0;


void xhci_initialize () {
	pci_device_info *dev = (pci_device_info*)pmmngr_alloc();
	if (!pci_find_device_class(0x0C, 0x03, dev)) {
		printf ("USB xHCI: not found\n");
		return;
	}

	xhci_base_address = dev->device.nonBridge.baseAddress[0] + dev->device.nonBridge.baseAddress[1];
	printf ("USB xHCI: found\n");
	printf ("XHCI Base Address -> %x\n", xhci_base_address);

	uint32_t version_address = xhci_base_address + XHCI_CAPREG_HCIVERSION;
	printf ("XHCI Version -> %x\n", ((uint64_t*)version_address)[0]);

	uint64_t hccparams1adr = xhci_base_address + XHCI_CAPREG_HCCPARAMS1;
	uint64_t hccparams1 = ((unsigned long*)hccparams1adr)[0];
	if (hccparams1 & 1) {
		printf ("[XHCI] has 64-bit addressing capability\n");
	}

	printf ("PCI Interrupt line -> %d\n", dev->device.nonBridge.interruptLine);
	pci_print_capabilities(dev);
	//for(;;);
}