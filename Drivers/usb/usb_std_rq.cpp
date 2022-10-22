/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2022, Manas Kamal Choudhury
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

#include <stdint.h>
#include "usb_std_def.h"
#include "xhci_cmd.h"
#include <usb.h>

/*
 * usb_get_device_desc -- sends USB_GET_DESCRIPTOR request to specific device
 * @param dev -- Pointer to usb device structure
 * @param slot -- Pointer to usb slot data structure
 * @param slot_id -- Slot id of the device
 * @param buffer -- address of the buffer where device descriptor will be written
 * @param len -- number of bytes needs to be requested
 */
void usb_get_device_desc (usb_dev_t *dev, xhci_slot_t *slot,uint8_t slot_id, uint64_t buffer,uint16_t len) {
	USB_REQUEST_PACKET pack;
	pack.request_type = USB_BM_REQUEST_INPUT | USB_BM_REQUEST_STANDARD | USB_BM_REQUEST_DEVICE;
	pack.request = USB_BREQUEST_GET_DESCRIPTOR;
	pack.value = USB_DESCRIPTOR_WVALUE(USB_DESCRIPTOR_DEVICE, 0);
	pack.index = 0;
	pack.length = len;

	xhci_send_control_cmd(dev,slot, slot_id, &pack, buffer, len);
}

/*
 * usb_get_string_desc -- request a string descriptor to specific device
 * @param dev -- Pointer to usb device structure
 * @param slot -- Pointer to usb slot data structure
 * @param slot_id -- Slot id of the device
 * @param buffer -- address of the buffer where device descriptor will be written
 * @param id-- type of the string needs to be requested
 */
void usb_get_string_desc (usb_dev_t *dev, xhci_slot_t *slot, uint8_t slot_id, uint64_t buffer, uint16_t id) {
	USB_REQUEST_PACKET pack;
	pack.request_type = USB_BM_REQUEST_INPUT | USB_BM_REQUEST_STANDARD | USB_BM_REQUEST_DEVICE;
	pack.request = USB_BREQUEST_GET_DESCRIPTOR;
	pack.value = USB_DESCRIPTOR_WVALUE(USB_DESCRIPTOR_STRING, id);
	pack.index = 0;
	pack.length = 256;

	xhci_send_control_cmd(dev,slot, slot_id, &pack, buffer, 256);
}