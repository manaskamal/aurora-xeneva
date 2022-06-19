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

#include "xhci.h"
#include <stdint.h>
#include <arch\x86_64\mmngr\paging.h>
#include <pmmngr.h>
#include <string.h>
#include <stdio.h>
#include <serial.h>
#include <usb.h>

/*
 * xhci_reset -- reset the xhci controller
 * @param dev -- usb device
 */
void xhci_reset (usb_dev_t *dev) {
	//dev->op_regs->op_usbcmd &= ~1;
	//while(!(dev->op_regs->op_usbsts & (1<<0)));

	dev->op_regs->op_usbcmd |= (1<<1);
	while((dev->op_regs->op_usbcmd & (1<<1)));
	while((dev->op_regs->op_usbsts & (1<<11)));
}

/*
 * xhci_device_ontext_init -- initialize the device context
 * base array pointer (DCBAAP)
 */
void xhci_device_context_init (usb_dev_t *dev) {
	uint64_t phys = (uint64_t)AuPmmngrAlloc();
	memset((void*)phys, 0, 4096);
	uint64_t* dcbaa =  (uint64_t*)AuMapMMIO(phys,1);
	dev->dev_ctx_base_array = dcbaa;
	dev->op_regs->op_dcbaap_lo = phys;
	dev->op_regs->op_dcbaap_hi = (phys >> 32);
	uint32_t scratch_hi = dev->cap_regs->cap_hccparams2 >> 21;
	uint32_t scratch_lo = dev->cap_regs->cap_hccparams2 >> 27;
	uint32_t max_scratchpad = (scratch_hi << 5) | scratch_lo;
	
	if (max_scratchpad) {
		uint64_t *spad = (uint64_t*)AuPmmngrAlloc();
		memset(spad, 0, 4096);

		for (unsigned i = 0; i < max_scratchpad; i++) {
			spad[i] = (uint64_t)AuPmmngrAlloc();
			memset(&spad[i], 0, 4096);
		}

		dcbaa[0] = (uint64_t)spad;
	}
}

/*
 * xhci_command_ring_init -- initialize the command ring 
 */
void xhci_command_ring_init(usb_dev_t *dev) {
	uint64_t cmd_ring_phys = (uint64_t)AuPmmngrAlloc();
	memset((void*)cmd_ring_phys, 0, 4096);
	dev->cmd_ring = (xhci_trb_t*)AuMapMMIO(cmd_ring_phys, 1);
	//((volatile uint64_t*)dev->cmd_ring)[63*2] = cmd_ring_phys;
	//((volatile uint64_t*)dev->cmd_ring)[63*2+1] = ((0x2UL | (6UL << 10)) << 32);

	dev->op_regs->op_crcr = cmd_ring_phys | 1;
	dev->op_regs->op_dnctrl = 4;
	dev->cmd_ring_index = 0;
	dev->cmd_ring_max = 64;
	dev->cmd_ring_cycle = 1;
	dev->cmd_ring_phys = cmd_ring_phys;
}

/*
 * xhci_protocol_init -- Initialize XHCI Extended Protocol 
 * @param dev -- Pointer to usb device
 */
void xhci_protocol_init (usb_dev_t *dev) {
	xhci_ext_cap_t *cap = dev->ext_cap;
	while(1) {
		switch(cap->id) {
		case 1: 
			printf ("USB Legacy Support \n");
			//break;
		case 2:{
			printf ("USB Support Protocol \n");
			xhci_ex_cap_protocol_t *prot = (xhci_ex_cap_protocol_t*)cap;
			printf ("Protocol name -> %s , starting port -> %d, max_port -> %d \n", prot->name, 
				(prot->port_cap_field & 0xFF), ((prot->port_cap_field >> 8) & 0xFF));
			printf ("Protocol speed -> %d \n", ((prot->port_cap_field >> 28) & 0xFFFF));
			//break;
	    }
		case 3:
			printf ("USB Extended Power Management \n");
			//break;
		case 4:
			printf ("USB I/O Virtualization \n");
			//break;
		case 5:
			printf ("USB Message Interrupt \n");
			//break;
		case 6:
			printf ("USB Local Memory \n");
			//break;
		case 10:
			printf ("USB Debug Capabiltiy \n");
			//break;
		}
		if (cap->next == 0)
			break;
		cap = ((xhci_ext_cap_t*)cap + (cap->next << 2));
	}
}


/*
 * xhci_event_ring_init -- initialize the 
 * default event ring
 * @param dev -- Pointer to usb device
 */
void xhci_event_ring_init (usb_dev_t *dev) {
	uint64_t e_ring_seg_table = (uint64_t)AuPmmngrAlloc();
	uint64_t* event_ring_seg_table_v = (uint64_t*)AuMapMMIO(e_ring_seg_table, 1);
	memset(event_ring_seg_table_v, 0,4096);

	uint64_t event_ring_seg = (uint64_t)AuPmmngrAlloc();
	uint64_t* event_ring_seg_v = (uint64_t*)AuMapMMIO(event_ring_seg, 1);
	memset(event_ring_seg_v, 0, 4096);
	dev->event_ring_segment = event_ring_seg_v;

	xhci_erst_t *erst = (xhci_erst_t*)e_ring_seg_table;
	erst->event_ring_segment_lo = event_ring_seg & UINT32_MAX;
	erst->event_ring_seg_hi = (event_ring_seg >> 32) & UINT32_MAX;
	erst->ring_seg_size = 4096 / 16;


	dev->evnt_ring_cycle = 1;
	dev->evnt_ring_index = 0;

	dev->rt_regs->intr_reg[0].evtRngSegTabSz = 1;
	dev->rt_regs->intr_reg[0].evtRngDeqPtrLo =  (event_ring_seg << 4) | (0 << 3);
	dev->rt_regs->intr_reg[0].evtRngDeqPtrHi = (event_ring_seg >> 32);
	dev->rt_regs->intr_reg[0].evtRngSegBaseLo = e_ring_seg_table;
	dev->rt_regs->intr_reg[0].evtRngSegBaseHi = (e_ring_seg_table >> 32);
	dev->rt_regs->intr_reg[0].intr_mod = (0 << 16) | 512;
	dev->op_regs->op_usbcmd = (1<<3) | (1<<2) | 0;
	dev->rt_regs->intr_reg[0].intr_man |= (1<<1) | 1;
	dev->op_regs->op_usbcmd |= 1;
	while ((dev->op_regs->op_usbsts & (1<<0)) != 0)
		;

}



/*
 * xhci_send_command -- Sends command to USB device through XHCI
 * host
 * @param dev -- Pointer to usb device structure
 * @param param1 -- parameter 1 of TRB
 * @param param2 -- parameter 2 of TRB
 * @param status -- status of TRB
 * @param ctrl -- control for TRB
 */
void xhci_send_command (usb_dev_t *dev, uint32_t param1, uint32_t param2, uint32_t status, uint32_t ctrl) {
	
	ctrl &= ~1;
	ctrl |= dev->cmd_ring_cycle;
	dev->cmd_ring[dev->cmd_ring_index].trb_param_1 = param1;
	dev->cmd_ring[dev->cmd_ring_index].trb_param_2 = param2;
	dev->cmd_ring[dev->cmd_ring_index].trb_status = status;
	dev->cmd_ring[dev->cmd_ring_index].trb_control = ctrl;

	dev->cmd_ring_index++;

	if (dev->cmd_ring_index >= 63 ) {
		dev->cmd_ring[dev->cmd_ring_index].trb_control ^= 1;
		if (dev->cmd_ring[dev->cmd_ring_index].trb_control & (1<<1)) {
			dev->cmd_ring_cycle ^= 1;
		}
		dev->cmd_ring_index = 0;
	}

	dev->db_regs->doorbell[0] = (0<<16) | 0;
}




/*
 * xhci_port_initialize -- initializes all powered ports
 * @param dev -- Pointer to USB device structures
 */
void xhci_port_initialize (usb_dev_t *dev) {
	for (unsigned int i = 1; i <= dev->num_ports; i++) {
		xhci_port_regs_t *this_port = &dev->ports[i - 1];
		if ((this_port->port_sc & 1)) {	

			/* Reset the port */
			this_port->port_sc |= (1<<4);
			while((this_port->port_sc & (1<<4)) != 0);

			for (int i = 0; i < 10000000; i++)
				;

			/* Enable slot command */
			xhci_send_command(dev,0,0,0,(i << 16)|(9 << 23));
			///* Reset completed */
			//uint8_t bm_req_type = USB_BM_REQUEST_INPUT | USB_BM_REQUEST_STANDARD | USB_BM_REQUEST_DEVICE;
			//uint8_t b_request = USB_BREQUEST_GET_DESCRIPTOR;
			//uint16_t wval = USB_DESCRIPTOR_WVALUE(USB_DESCRIPTOR_DEVICE, 0);
			//xhci_send_command(dev,bm_req_type | b_request << 8 | wval << 16,0 | (18 >>16), (0 << 22) | 8,(3 << 16) | (1<<6) | (2<<10));


			//xhci_trb_t *trb = (xhci_trb_t*)dev->event_ring_segment;
			//for(;;){
			//	xhci_trb_t *event = (xhci_trb_t*)dev->event_ring_segment;
			//	uint64_t erdp = (uint64_t)AuGetPhysicalAddress((uint64_t)AuGetRootPageTable(),(uint64_t)dev->event_ring_segment);
			//	while ((event[dev->evnt_ring_index].trb_control & (1<<0)) == dev->evnt_ring_cycle){
			//		xhci_event_trb_t *evt = (xhci_event_trb_t*)&event[dev->evnt_ring_index];
			//		printf ("port Event Received %d, %x, %d\n", evt->trbType, 
			//			event[dev->evnt_ring_index].trb_control, ((event[dev->evnt_ring_index].trb_status & (1<<24)) & 0xff));

			//		

			//		dev->rt_regs->intr_reg[0].evtRngDeqPtrLo = (erdp + sizeof(xhci_trb_t) * dev->evnt_ring_index);
			//		dev->rt_regs->intr_reg[0].evtRngDeqPtrHi = (erdp + sizeof(xhci_trb_t) * dev->evnt_ring_index)>> 32;
			//		dev->evnt_ring_cycle ^= 1;
			//		dev->rt_regs->intr_reg[0].intr_man = (1<<1) | 0;
			//		dev->evnt_ring_index++;
			//	}
			//	break;
			//}
			this_port->port_sc |= (1<<9);
			printf ("Port Initialized %d, Power -> %d, PED -> %d \n", i, ((this_port->port_sc & (1<<9)) & 0xff),
				((this_port->port_sc & (1<<1)) & 0xff));
		}
	}
}
