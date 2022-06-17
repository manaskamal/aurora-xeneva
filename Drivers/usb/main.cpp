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
#include <drivers\pcie.h>
#include <hal.h>
#include "xhci.h"
#include <drivers\pcie.h>
#include <arch\x86_64\mmngr\paging.h>
#include <arch\x86_64\mmngr\kheap.h>
#include <shirq.h>

usb_dev_t *usb_device;
shirq_t *shdev;

void AuUSBInterrupt(size_t v, void* p) {
	//AuFiredSharedHandler(usb_device->irq,v,p,shdev);
	printf ("[usb]: interrupt fired++ \n");

	xhci_trb_t *event = (xhci_trb_t*)usb_device->event_ring_segment;
	uint64_t erdp = (uint64_t)usb_device->event_ring_segment;
	if ((event[usb_device->evnt_ring_index].trb_control & 0xff) == 1){
		printf ("Event Received %d, %x, %d\n", ((event[usb_device->evnt_ring_index].trb_control >> 10) & 0xFF), 
			event->trb_control,  ((event[usb_device->evnt_ring_index].trb_control >> 10) & 0xFF));
		if (((event[usb_device->evnt_ring_index].trb_control >> 10) & 0xFF) == 34){
			printf ("PSC Event port id -> %d , completion_code -> %d \n", ((event[usb_device->evnt_ring_index].trb_param_1 >> 24) & 0xFF),
				((event[usb_device->evnt_ring_index].trb_status >> 24) & 0xff));
			printf ("cycle bit -> %d \n",(event[usb_device->evnt_ring_index].trb_control & 0xff));
		}

		usb_device->evnt_ring_index++;

		usb_device->rt_regs->intr_reg[0].evtRngDeqPtrHi = (erdp + sizeof(xhci_trb_t) * usb_device->evnt_ring_index);
		usb_device->rt_regs->intr_reg[0].evtRngDeqPtrLo = (erdp + sizeof(xhci_trb_t) * usb_device->evnt_ring_index)>> 32;
	
		usb_device->op_regs->op_usbsts &= ~XHCI_USB_STS_EINT;
		usb_device->rt_regs->intr_reg[0].intr_man = 0;
		usb_device->rt_regs->intr_reg[0].intr_man |= (1<<1);	
		printf ("Interrupt pending -> %d, interrupt e -> %d \n", (usb_device->rt_regs->intr_reg[0].intr_man & 0xf), 
		(usb_device->rt_regs->intr_reg[0].intr_man >> 1 & 0xff));
	}

	AuInterruptEnd(usb_device->irq);
}

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
	//printf ("Initializing USB\n");
	int bus, dev, func;

	uint64_t device = pci_express_scan_class(0x0C, 0x03, &bus, &dev, &func);
	if (device == 0xFFFFFFFF){
		printf ("[usb]: xhci not found \n");
		return 1;
	}

	usb_device = (usb_dev_t*)malloc(sizeof(usb_dev_t));

	uint64_t command = pci_express_read(device ,PCI_COMMAND,bus,dev,func);
	command &= ~(1<<10);
	command |= (1<<1);

	
	pci_express_write(device, PCI_COMMAND, command, bus, dev, func);


	uint32_t usb_addr_low = pci_express_read(device, PCI_BAR0, bus, dev, func) & 0xFFFFFFF0;
	uint32_t usb_addr_high = pci_express_read(device, PCI_BAR1, bus, dev, func) & 0xFFFFFFFF;
	uint64_t mmio_addr = (usb_addr_high << 32) | usb_addr_low;

	uint64_t mmio_base = (uint64_t)AuMapMMIO(mmio_addr, 16);
	xhci_cap_regs_t *cap = (xhci_cap_regs_t*)mmio_base;
	uint64_t op_base = (uint64_t)(mmio_base + (cap->cap_caplen_version & 0xFF));
	xhci_op_regs_t *op = (xhci_op_regs_t*)op_base;
	uint64_t rt_base = (uint64_t)(mmio_base + (cap->cap_hccparams2 & ~(0x1FUL)));
	xhci_runtime_regs_t *rt = (xhci_runtime_regs_t*)rt_base;
	uint64_t db_base = (uint64_t)(mmio_base + (cap->cap_dboff & ~0x3UL));
	xhci_doorbell_regs_t *db = (xhci_doorbell_regs_t*)db_base;
	uint64_t ext_base = (uint64_t)(mmio_base + ((cap->cap_hccparams1  >> 16) << 2));
	xhci_ext_cap_t *ext_cap = (xhci_ext_cap_t*)ext_base;
	uint64_t ports_base = (uint64_t)(mmio_base + ((cap->cap_caplen_version & 0xFF)) + 0x400);
	xhci_port_regs_t *ports = (xhci_port_regs_t*)ports_base;

	usb_device->cap_regs = cap;
	usb_device->op_regs = op;
	usb_device->db_regs = db;
	usb_device->rt_regs = rt;
	usb_device->ext_cap = ext_cap;
	usb_device->ports = ports;


	//printf ("[usb]: xhci available slots: %d \n", (cap->cap_hcsparams1 & 0xFF));
	//printf ("[usb]: xhci available ports: %d \n", (cap->cap_hcsparams1 >> 24));

	usb_device->num_slots = (cap->cap_hcsparams1 & 0xFF);
	usb_device->num_ports = (cap->cap_hcsparams1 >> 24);
	
	
	
	/* Reset the XHCI controller */
	xhci_reset(usb_device);
	
	
	uint32_t cfg = op->op_config;
	cfg &= ~0xFF;
	cfg |= usb_device->num_slots;
	op->op_config = cfg;

	/* Initialize Device context base array pointer (DCBAAP) */
	xhci_device_context_init(usb_device);

	/* Initialize command ring circular buffer */
	xhci_command_ring_init(usb_device);
	
	
	setvect(38,AuUSBInterrupt);
	pcie_alloc_msi(device,38,bus,dev,func);
	
	xhci_protocol_init(usb_device);

	xhci_event_ring_init(usb_device);

	for (int i = 0; i < 10000000; i++)
		;

	
	/*xhci_noop_cmd_trb_t test;
	memset(&test, 0, sizeof(xhci_noop_cmd_trb_t));
	test.trb_type = 23;
	test.cycleBit = 1;*/
	

	AuEnableInterrupts();
	
	xhci_send_command(usb_device,0,0,0,(23 << 10));
	for(;;){
		xhci_trb_t *event = (xhci_trb_t*)usb_device->event_ring_segment;
		uint64_t erdp = (uint64_t)usb_device->event_ring_segment;
		if ((event[usb_device->evnt_ring_index].trb_control & 0xff) == 1){
			printf ("Event Received %d, %x, %d\n", ((event[usb_device->evnt_ring_index].trb_control >> 10) & 0xFF), 
				event[usb_device->evnt_ring_index].trb_control,  ((event[usb_device->evnt_ring_index].trb_control >> 10) & 0xFF));

			usb_device->evnt_ring_index++;

			usb_device->rt_regs->intr_reg[0].evtRngDeqPtrHi = (erdp + sizeof(xhci_trb_t) * usb_device->evnt_ring_index);
			usb_device->rt_regs->intr_reg[0].evtRngDeqPtrLo = (erdp + sizeof(xhci_trb_t) * usb_device->evnt_ring_index)>> 32;
			break;
		}

	}

	xhci_port_initialize(usb_device);


	/* for now xhci is under development, i am learning 
	 * xhci and doing experiments within it, that's why
	 * for(;;) loop here
	 */
	for(;;);
	
	return 0;
}