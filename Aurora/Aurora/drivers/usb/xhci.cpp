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


void xhci_start_stop (int start) {

	int count;

	xhci_op_regs* op = (xhci_op_regs*)xusb_dev->xhci_op_address;

	if (start) {
		//! set the run/stop bit
		op->cmd |= XHCI_CMD_RUNSTOP;

		for (count = 0; count < 20; count++) {
			if (!(op->stat & XHCI_STAT_HCHALTED)) {
				printf ("USB: stating controller took %d ms\n", count);
				break;
			}
		}


		//! started ?
		if (op->stat &XHCI_STAT_HCHALTED) {
			printf ("USB: error! couldn't clear controller halted bit\n");
			return;
		}
	} else {
		//! stop the controller
		if (op->cmdrctrlLo & XHCI_CRCR_CMDRNGRUNNING) {
			printf ("USB: XHCI stopping command ring\n");
			op->cmdrctrlLo = XHCI_CRCR_COMMANDABORT;
			op->cmdrctrlHi = 0;

			//!wait for stopped
			for (count = 0; count < 5000; count++) {
				if (!(op->cmdrctrlLo & XHCI_CRCR_CMDRNGRUNNING)) {
					printf ("USB: xHCI stopping ring took %d ms\n", count);
					break;
				}
			}

			//! stopped
			if (op->cmdrctrlLo & XHCI_CRCR_CMDRNGRUNNING)
				printf ("USB: xHCI couldn't stop command ring\n");
		}

		//! clear the run/stop bit
		op->cmd &= ~XHCI_CMD_RUNSTOP;

		//!wait for halted
		for (count = 0; count < 20; count++) {
			if (op->stat & XHCI_STAT_HCHALTED) {
				printf ("USB: xHCI stopping controller took %d ms\n", count);
				break;
			}
		}

			//! stopped?
		if (!(op->stat & XHCI_STAT_HCHALTED)){
			printf ("USB: xHCI couldn't set controller halted bit\n");
			return;
		}
	}

	//!successfull
	printf ("USB: xHCI controller reset completed \n");
}


//! Reset the root hub, i.e reset the controller
static void reset () {
	//! stop the controller
	xhci_start_stop(0);

	xhci_op_regs* op_reg = (xhci_op_regs*)xusb_dev->xhci_op_address;
	op_reg->cmd |= XHCI_CMD_HCRESET;

	//! wait until the host controller clears it
	for (int count = 0; count < 2000; count++){
		if (! op_reg->cmd & XHCI_CMD_HCRESET) {
			printf ("USB: xHCI resetting controller took %dms \n",count);
			break;
		}
	}

	//! clear
	if (op_reg->cmd & XHCI_CMD_HCRESET)
	{
		printf ("USB: controller did not clear reset bit\n");
		return;
	}

	//! successfull
	printf ("USB: xHCI controller reset successfully\n");
}


/**
 * Initialize the xhci controller
 */
void xhci_initialize () {
	pci_device_info *dev = (pci_device_info*)pmmngr_alloc();
	xusb_dev = (xhci*)pmmngr_alloc();

	int bus, dev_, func_ = 0;
	if (!pci_find_device_class(0x0C, 0x03, dev, &bus, &dev_, &func_)) {
		printf ("USB xHCI: not found\n");
		return;
	}
	x64_cli ();

	printf ("Scanning MSI support for USB\n");
	pci_print_capabilities(func_, dev_, bus);

	xusb_dev->xhci_base_address = (dev->device.nonBridge.baseAddress[0] & 0xFFFFFFF0) +((dev->device.nonBridge.baseAddress[1] & 0xFFFFFFFF) << 32);

	xhci_cap_reg *cap = (xhci_cap_reg*)xusb_dev->xhci_base_address;
    uint32_t version = cap->caps_len_hciver >> 16;
	printf ("USB: xHCI version - (%d.%d%d)\n",((version >> 8) & 0xFF), ((version>>4) & 0xF), (version & 0xF));

	xusb_dev->xhci_op_address = ((size_t)cap + (cap->caps_len_hciver & 0xFF));
	xusb_dev->doorbell_address = ((size_t)cap + (cap->dboffset & ~0x3UL));
	xusb_dev->runtime_address = ((size_t)cap + (cap->runtime_offset & ~0x1FUL));

	/**if (dev->device.nonBridge.interruptLine != 255)
		interrupt_set (dev->device.nonBridge.interruptLine, xhci_handler, dev->device.nonBridge.interruptLine);**/

	printf ("USB: xHCI interrupt line -> %d\n", dev->device.nonBridge.interruptLine);
	printf ("USB: xHCI interrupt pin -> %d\n", dev->device.nonBridge.interruptPin);
	reset ();
	x64_sti();
	//for(;;);
}