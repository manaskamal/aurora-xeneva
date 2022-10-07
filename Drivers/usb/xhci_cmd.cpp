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

#include "xhci_cmd.h"
#include "xhci.h"

/*
 * xhci_enable_slot -- sends enable slot command to xHC
 * @param dev -- Pointer to usb device structure
 * @param slot_type -- type of slot mainly in between 0-31
 */
void xhci_enable_slot (usb_dev_t *dev,int slot_type) {
	/* Send Enable slot command */
	xhci_send_command(dev,0,0,0,(slot_type << 16) | (TRB_CMD_ENABLE_SLOT << 10));
	xhci_ring_doorbell(dev);
}


/* xhci_send_noop_cmd -- Send No operation command
 * @param dev -- Pointer to USB structure
 */
void xhci_send_noop_cmd (usb_dev_t* dev) {
	xhci_send_command(dev, 0,0,0,TRB_CMD_NO_OP << 10);
	xhci_ring_doorbell(dev);
}

/*
 * xhci_create_setup_trb -- creates a setup stage trb
 */
void xhci_create_setup_trb (usb_dev_t *dev, uint8_t rType, uint8_t bRequest, uint16_t value, uint16_t wIndex, uint16_t wLength) {
	xhci_send_command(dev, rType | bRequest << 8 | value << 16, wIndex | wLength << 16,8,(2 << 10) | (1<<6));
}

/*
 * xhci_create_data_trb -- creates data stage trb
 * @param dev -- pointer to usb structure
 * @param buffer -- pointer to memory area
 * @param size -- size of the buffer
 * @param in_direction -- direction
 */
void xhci_create_data_trb (usb_dev_t* dev, uint64_t buffer, uint16_t size, bool in_direction) {
	uint8_t dir = 0;
	if (in_direction)
		dir = (1<<16);
	else
		dir = (0<<16);
	xhci_send_command (dev,buffer, buffer >> 32, size, dir | (3 << 10) | (1<<1));
}

/*
 * xhci_create_status_trb -- creates status stage trb
 * @param dev -- pointer to usb strucutue
 * @param in_direction -- direction
 */
void xhci_create_status_trb (usb_dev_t* dev, bool in_direction) {
	uint8_t dir = 0;
	if (in_direction)
		dir = 1;
	else
		dir = 0;
	xhci_send_command(dev, 0, 0, 0, (dir << 16) | (4 << 10) | (1<<1));
}

