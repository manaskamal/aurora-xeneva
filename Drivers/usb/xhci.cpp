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
#include "xhci_cmd.h"
#include <hal.h>
#include "usb_def.h"


extern int poll_event_for_trb;
extern bool event_available;
extern int poll_return_trb_type;
extern int trb_event_index;


#define USB_SLOT_CTX_DWORD0(entries, hub, multi_tt, speed, route_string) \
	(((entries & 0x1F) << 27) | ((hub & 1) << 26) | ((multi_tt & 1) << 25) | ((speed & 0xF) << 20) | (route_string & ((1<<20) - 1)))

#define USB_SLOT_CTX_DWORD1(num_ports, root_hub_port, max_exit_latency) \
	(((num_ports & 0xFF) << 24) | ((root_hub_port & 0xFF) << 16) | (max_exit_latency & 0xFFFF))

#define USB_ENDPOINT_CTX_DWORD0(max_esit_high, interval, lsa, max_p_streams, mult, ep_state) \
	(((max_esit_high & 0xFF) << 24) | ((interval & 0xFF) << 16) | ((lsa & 1) << 15) | ((max_p_streams & 0x1F) << 10) | ((mult & 0x3) << 8) | (ep_state & 0x7))

#define USB_ENDPOINT_CTX_DWORD1(max_packet_size, max_burst_size, hid, ep_type, cerr) \
	(((max_packet_size & 0xFFFF) << 16) | ((max_burst_size & 0xFF) << 8) | ((hid & 1) << 7) | ((ep_type & 0x7) << 3)  | ((cerr & 0x3) << 1))

#define USB_ENDPOINT_CTX_DWORD2(trdp, dcs) \
	((trdp & 0xFFFFFFF0) | (dcs & 1))

#define USB_ENDPOINT_CTX_DWORD3(trdp) \
	((trdp >> 32) & 0xFFFFFFFF)

#define USB_ENDPOINT_CTX_DWORD4(max_esit_lo, average_trb_len) \
	(((max_esit_lo & 0xFFFF) << 16) | (average_trb_len & 0xFFFF))

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
 * xhci_get_max_packet_sz -- get the packet size by usb speed
 * @param speed -- speed of USB port
 */
size_t xhci_get_max_packet_sz (uint8_t speed) {
	switch(speed) {
	case USB_LOW_SPEED:
	case USB_FULL_SPEED:
		return 8;
	case USB_HIGH_SPEED:
		return 64;
	case USB_SUPER_SPEED:
	case USB_SUPER_SPEED_PLUS:
		return 512;
	default:
		return 512;
	}
}

/*
 * xhci_create_device_ctx -- creates a device context
 * for a particuler USB device
 * @param dev -- pointer to usb device
 * @param slot_num -- slot id
 * @param port_speed -- speed of this port
 * @param root_port_num -- root hub port number
 */
void xhci_create_device_ctx (usb_dev_t* dev, uint8_t slot_num, uint8_t port_speed, uint8_t root_port_num) {

	uint64_t dev_ctx = (uint64_t)AuPmmngrAlloc();
	memset((void*)dev_ctx, 0, 4096);
	dev->dev_ctx_base_array[slot_num] = dev_ctx;
	
	uint64_t input_ctx = (uint64_t)AuPmmngrAlloc();
	memset((void*)input_ctx, 0, 4096);

	volatile uint32_t* aflags = raw_offset<volatile uint32_t*>(input_ctx, 4);
	*aflags = 3;

	*raw_offset<volatile uint32_t*>(input_ctx,0x20) = USB_SLOT_CTX_DWORD0(1,0,0,port_speed,0);
	*raw_offset<volatile uint32_t*>(input_ctx,0x20 + 4) = USB_SLOT_CTX_DWORD1(0,root_port_num,0);

	/* initialize the endpoint 0 ctx here */
	*raw_offset<volatile uint32_t*>(input_ctx,0x40) = USB_ENDPOINT_CTX_DWORD0(0,0,0,0,0,0);
	*raw_offset<volatile uint32_t*>(input_ctx,0x40 + 4) = USB_ENDPOINT_CTX_DWORD1(xhci_get_max_packet_sz(port_speed),0,0,4,3);
	*raw_offset<volatile uint32_t*>(input_ctx,0x40 + 8) = USB_ENDPOINT_CTX_DWORD2(dev->cmd_ring_phys, 1);
	*raw_offset<volatile uint32_t*>(input_ctx,0x40 + 12) = USB_ENDPOINT_CTX_DWORD3(dev->cmd_ring_phys);
	*raw_offset<volatile uint32_t*>(input_ctx,0x40 + 0x10) = USB_ENDPOINT_CTX_DWORD4(0,8);

	memcpy((void*)dev_ctx, raw_offset<void*>(input_ctx, 0x20), 0x40);

	/* Here we need an function, which will issues commands to this slot */
	/* (Incomplete) */
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
			printf ("Slot Type -> %d \n", ((prot->port_cap_field2) & 0xff));
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
	dev->evnt_ring_max = erst->ring_seg_size;

	dev->rt_regs->intr_reg[0].evtRngSegTabSz = 1;
	dev->rt_regs->intr_reg[0].evtRngDeqPtrLo =  (event_ring_seg << 4) | (1 << 3);
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
	ctrl |= 1; //dev->cmd_ring_cycle;
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

	xhci_ring_doorbell(dev);
}

/*
 * xhci_ring_doorbell -- rings the doorbell
 * @param dev -- Pointer to usb structure
 */
void xhci_ring_doorbell(usb_dev_t* dev) {
	dev->db_regs->doorbell[0] = (0<<16) | 0;
}


/*
 * xhci_send_command_multiple -- sends multiple commands to the command ring
 * @param dev -- Pointer to usb structure
 * @param trb -- TRB address containing multiple TRBs
 * @param num_count -- counts of TRB to send
 */
void xhci_send_command_multiple (usb_dev_t* dev, xhci_trb_t* trb, int num_count) {
	for (int i = 0; i < num_count; i++) {
		trb[i].trb_control |= 1;

		dev->cmd_ring[dev->cmd_ring_index].trb_param_1 = trb[i].trb_param_1;
		dev->cmd_ring[dev->cmd_ring_index].trb_param_2 = trb[i].trb_param_2;
		dev->cmd_ring[dev->cmd_ring_index].trb_status = trb[i].trb_status;
		dev->cmd_ring[dev->cmd_ring_index].trb_control = trb[i].trb_control;

		dev->cmd_ring_index++;

		if (dev->cmd_ring_index >= 63 ) {
			dev->cmd_ring[dev->cmd_ring_index].trb_control ^= 1;
			if (dev->cmd_ring[dev->cmd_ring_index].trb_control & (1<<1)) {
				dev->cmd_ring_cycle ^= 1;
			}
			dev->cmd_ring_index = 0;
		}

	}

	dev->db_regs->doorbell[0] = (0<<16) | 0;
}


/*
 * xhci_poll_event -- waits for an event to occur on interrupts
 * @param usb_device -- pointer to usb device structure
 * @param trb_type -- type of trb to look
 * @return trb_event_index -- index of the trb on event_ring_segment
 */
int xhci_poll_event (usb_dev_t* usb_device, int trb_type) {
	int idx = -1;
	for (;;) {
		if (event_available && poll_return_trb_type == trb_type 
			&& trb_event_index != -1) {
				event_available = false;
				idx = trb_event_index;
				trb_event_index = -1;
				poll_return_trb_type = -1;
				return idx;
		}
	}

	return trb_event_index;
}

/*
 * xhci_get_port_speed -- converts port speed number to 
 * readable string
 * @param port_speed -- port speed number
 */
char* xhci_get_port_speed (uint8_t port_speed) {
	switch(port_speed) {
	case USB_SPEED_RESERVED:
		return "[USB_PORT_SPEED]: invalid";
	case USB_FULL_SPEED:
		return "[USB_PORT_SPEED]: full speed";
	case USB_LOW_SPEED:
		return "[USB_PORT_SPEED]: low speed";
	case USB_HIGH_SPEED:
		return "[USB_PORT_SPEED]: high speed";
	case USB_SUPER_SPEED:
		return "[USB_PORT_SPEED]: super speed";
	case USB_SUPER_SPEED_PLUS:
		return "[USB_PORT_SPEED]: super speed+";
	default:
		return "[USB_PORT_SPEED]: unknown";
	}
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

			uint8_t port_speed = (this_port->port_sc >> 10) & 0xf;
			printf ("Port Num -> %d, Port Speed -> %s \n", i, xhci_get_port_speed(port_speed));
			for (int i = 0; i < 10000000; i++)
				;
			
			uint8_t slot_id = 0;

			/* Enable slot command */
			xhci_enable_slot(dev,0);
			int idx = xhci_poll_event(dev,TRB_EVENT_CMD_COMPLETION);
			if (idx != -1) {
				xhci_event_trb_t *evt = (xhci_event_trb_t*)dev->event_ring_segment;
				xhci_trb_t *trb = (xhci_trb_t*)evt;
				slot_id = (trb[idx].trb_control >> 24);
				//printf ("Event received -> %d, slot_id -> %d \r\n",evt[idx].trbType, evt[idx].completionCode);
				printf ("Slot id -> %d \n", slot_id);
			}
			
			/* After getting a device slot, 
			 * allocate device slot data structures
			 */
			xhci_create_device_ctx(dev,slot_id,port_speed,i);

			this_port->port_sc |= (1<<9);
			/*printf ("Port Initialized %d, Power -> %d, PED -> %d \n", i, ((this_port->port_sc & (1<<9)) & 0xff),
				((this_port->port_sc & (1<<1)) & 0xff));*/
		}
	}

	//for(;;);
}
