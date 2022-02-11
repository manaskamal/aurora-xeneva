/**
 *  Copyright (C) Manas Kamal Choudhury 2022
 *
 *  usb_main.cpp -- the main initializer of usb driver
 *
 *  /PROJECT - Aurora's Xeneva v1.0
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 */


#include <stdint.h>
#include <string.h>
#include <sys.h>
#include "usb.h"
#include "xhci.h"

void *usb_base;

extern "C" void _declspec(dllexport) aurora_write (unsigned char* buffer, size_t length) {
}


//! Aurora Close Driver interface
//! Free up space and perform every clean action
extern "C" void _declspec(dllexport) aurora_close_driver () {

	//[CODE]
}
//! Aurora Init Driver interface
//! Perform every initializing action here
extern "C" int _declspec(dllexport) _cdecl aurora_init_driver (driver_param_t *param) {
	param->kdebug ("Looking for USB xHCI compatibility\n");

	int bus, dev, func;
	pci_device_info device;
	memset (&device, 0, sizeof(pci_device_info));
	if (!param->pci->pci_find_device_class_p(0x0C, 0x03,&device,&bus,&dev,&func)) {
		param->kdebug ("[USB]: xHCI device not found\n");
		return 0;
	}


	param->pci->pci_enable_bus_master_p (bus,dev,func);

	uint32_t addr_low = device.device.nonBridge.baseAddress[0] & 0xFFFFFFF0;
	uint32_t addr_high = device.device.nonBridge.baseAddress[1] & 0xFFFFFFFF;

	size_t xhci_base = addr_low;
	param->kdebug("[USB]: xHCI device found, Base -> %x\n", addr_low);

	if ((xhci_base + XHCI_CAPREG_HCSPARAMS1) & 0x1) {
		param->kdebug ("[USB]: xHCI has 64-bit addressing capability\n");
	}

	xhci_cap_reg *cap = (xhci_cap_reg*)xhci_base;
	uint32_t version = cap->caps_len_hciver >> 16;
	param->kdebug ("[USB]: xHCI version - (%d.%d%d)\n",((version >> 8) & 0xFF), ((version>>4) & 0xF), (version & 0xF));

	param->kdebug ("[USB]: max available slot -> %d\n",cap->hcsparams1 & 0xFF);
	param->kdebug ("[USB]: available ports -> %d\n", (cap->hcsparams1 & XHCI_HCSP1_MAXPORTS) >> 24);

	xhci_op_regs *op = (xhci_op_regs*)(cap + (cap->caps_len_hciver & 0xFF));
	param->kdebug ("[USB]: cap reg -> %x, op reg -> %x\n", cap, op);
	param->kdebug ("[USB]: resetting\n");

	if (op->cmd & 0xff) {
		param->kdebug ("[USB]: xHCI is running\n");
	}

	

	op->cmd = 0;

	for (int i = 0; i < 1000; i++)
		;

	bool stopped = false;
	for (int i = 0; i < 1000; i++) {
		if (op->stat & 0xff) {
			param->kdebug ("[USB]: xHCI stopped\n");
			stopped = true;
			break;
		}
	}

	if (!stopped)
		param->kdebug ("[USB]: xHCI didn't stopped\n");
	return 0;
}