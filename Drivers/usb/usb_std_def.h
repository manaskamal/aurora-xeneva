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

#ifndef __USB_DEF_H__
#define __USB_DEF_H__

#include <stdint.h>
#include "xhci.h"

#define USB_AUDIO_DEV_CLASS   0x01
#define USB_COMMUNICATION_CDC_CTRL_CLASS 0x02
#define USB_HID_DEV_CLASS  0x03
#define USB_PHYSICAL_DEV_CLASS 0x05
#define USB_IMAGE_DEV_CLASS 0x06
#define USB_PRINTER_DEV_CLASS  0x07
#define USB_MASS_STORAGE_DEV_CLASS  0x08
#define USB_HUB_DEV_CLASS  0x09
#define USB_CDC_DATA_DEV_CLASS  0x0A
#define USB_SMART_CARD_DEV_CLASS 0x0B
#define USB_CONTENT_SECURITY_DEV_CLASS 0x0D
#define USB_VIDEO_DEV_CLASS 0x0E
#define USB_PERSONAL_HEALTHCARE_DEV_CLASS 0x0F
#define USB_AUDIO_VIDEO_DEV_CLASS 0x10
#define USB_BILLBOARD_DEV_CLASS 0x11
#define USB_TYPE_C_BRIDGE_CLASS  0x12
#define USB_I3C_DEV_CLASS  0x3C
#define USB_DIAGNOSTIC_DEV_CLASS 0xDC
#define USB_WIRELESS_CONTROLLER_DEV_CLASS 0xE0
#define USB_MISCELLANEOUS_DEV_CLASS 0xEF


struct USB_REQUEST_PACKET {
	uint8_t request_type;
	uint8_t request;
	uint16_t value;
	uint16_t index;
	uint16_t length;
};
#pragma pack(push,1)
typedef struct _dev_desc_ {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint16_t bcdUSB;
	uint8_t  bDeviceClass;
	uint8_t bDeviceSubClass;
	uint8_t bDeviceProtocol;
	uint8_t bMaxPacketSize0;
	uint16_t idVendor;
	uint16_t idProduct;
	uint16_t bcdDevice;
	uint8_t  iManufacturer;
	uint8_t iProduct;
	uint8_t iSerialNumber;
	uint8_t bNumConfigurations;
}usb_dev_desc_t;
#pragma pack(pop)


/*
 * usb_get_device_desc -- sends USB_GET_DESCRIPTOR request to specific device
 * @param dev -- Pointer to usb device structure
 * @param slot -- Pointer to usb slot data structure
 * @param slot_id -- Slot id of the device
 * @param buffer -- address of the buffer where device descriptor will be written
 * @param len -- number of bytes needs to be requested
 */
extern void usb_get_device_desc (usb_dev_t *dev, xhci_slot_t *slot,uint8_t slot_id, uint64_t buffer,uint16_t len);


/*
 * usb_get_string_desc -- request a string descriptor to specific device
 * @param dev -- Pointer to usb device structure
 * @param slot -- Pointer to usb slot data structure
 * @param slot_id -- Slot id of the device
 * @param buffer -- address of the buffer where device descriptor will be written
 * @param id-- type of the string needs to be requested
 */
extern void usb_get_string_desc (usb_dev_t *dev, xhci_slot_t *slot, uint8_t slot_id, uint64_t buffer, uint16_t id);

#endif