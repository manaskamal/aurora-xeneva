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

xhci *xusb_dev;


void xhci_handler (size_t v, void* p) {
	printf ("[XHCI USB]: Interrupt fired\n");
}


void xhci_initialize () {
	pci_device_info *dev = (pci_device_info*)pmmngr_alloc();
	xusb_dev = (xhci*)pmmngr_alloc();

	int bus, dev_, func_ = 0;
	if (!pci_find_device_class(0x0C, 0x03, dev, &bus, &dev_, &func_)) {
		printf ("USB xHCI: not found\n");
		return;
	}
	x64_cli ();
	xusb_dev->xhci_base_address = (dev->device.nonBridge.baseAddress[0] & 0xFFFFFFF0) +((dev->device.nonBridge.baseAddress[1] & 0xFFFFFFFF) << 32);

	xhci_cap_reg *cap = (xhci_cap_reg*)xusb_dev->xhci_base_address;
    uint32_t version = cap->caps_len_hciver >> 16;
	printf ("USB: xHCI version - (%d.%d%d)\n",((version >> 8) & 0xFF), ((version>>4) & 0xF), (version & 0xF));

	xusb_dev->xhci_op_address = ((size_t)cap + (cap->caps_len_hciver & 0xFF));
	xusb_dev->doorbell_address = ((size_t)cap + (cap->dboffset & ~0x3UL));
	xusb_dev->runtime_address = ((size_t)cap + (cap->runtime_offset & ~0x1FUL));

	if (dev->device.nonBridge.interruptLine != 255)
		interrupt_set (dev->device.nonBridge.interruptLine, xhci_handler, dev->device.nonBridge.interruptLine);


	x64_sti();
	//for(;;);
}