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

#include <stdio.h>
#include <aurora.h>
#include <drivers\pci.h>
#include "xhci.h"
#include <arch\x86_64\mmngr\paging.h>

/*
 * AuDriverUnload -- Frees and clear up everthing of e1000 driver
 * turn e1000 off!
 */
AU_EXTERN AU_EXPORT int AuDriverUnload() {
	return 0;
}
/*
 * AuDriverMain -- Main entry for usb driver
 */
AU_EXTERN AU_EXPORT int AuDriverMain() {
	pci_device_info device;
	int dev, func, bus;
	if (!pci_find_device_class(0x0C, 0x03, &device, &bus, &dev, &func)) {
		printf ("[usb]: xhci not found \n");
	}

	pci_enable_bus_master(bus, dev, func);

	uint64_t usb_addr_low = device.device.nonBridge.baseAddress[0] & 0xFFFFFFF0;
	uint64_t usb_addr_high = device.device.nonBridge.baseAddress[1] & 0xFFFFFFFF;
	uint64_t mmio_addr = (usb_addr_high << 32) | usb_addr_low;

	printf ("[usb]: address low -> %x, address high -> %x \n", usb_addr_low, usb_addr_high);
	printf ("[usb]: mmio addr -> %x \n", mmio_addr);

	uint64_t* mmio_base = (uint64_t*)AuMapMMIO(mmio_addr, 4);
	xhci_cap_regs_t *cap = (xhci_cap_regs_t*)mmio_base;
	xhci_op_regs_t *op = (xhci_op_regs_t*)(cap + (cap->cap_caplen_version & 0xFF));
	
	printf ("[usb]: xhci available slots: %d \n", (cap->cap_hcsparams1 & 0xFF));
	printf ("[usb]: xhci available ports: %d \n", (cap->cap_hcsparams1 >> 24));
	

	for(;;);
}