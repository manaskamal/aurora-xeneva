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

#ifndef __XHCI_CMD_H__
#define __XHCI_CMD_H__

#include <stdint.h>
#include "xhci.h"
#include "usb_def.h"

/* Standard XHCI defined Transfer/Command/Event 
 * TRB type values 
 */
#define TRB_TRANSFER_NORMAL                 1
#define TRB_TRANSFER_SETUP_STAGE            2
#define TRB_TRANSFER_DATA_STAGE             3
#define TRB_TRANSFER_STATUS_STAGE           4
#define TRB_TRANSFER_ISOCH                  5
#define TRB_TRANSFER_LINK                   6
#define TRB_TRANSFER_EVENT_DATA             7
#define TRB_TRANSFER_NO_OP                  8
#define TRB_CMD_ENABLE_SLOT                 9
#define TRB_CMD_DISABLE_SLOT                10
#define TRB_CMD_ADDRESS_DEV                 11
#define TRB_CMD_CONFIG_ENDPOINT             12
#define TRB_CMD_EVALUATE_CTX                13
#define TRB_CMD_RESET_ENDPOINT              14
#define TRB_CMD_STOP_ENDPOINT               15
#define TRB_CMD_SET_TR_DEQ_POINTER          16
#define TRB_CMD_RESET_DEV                   17
#define TRB_CMD_FORCE_EVENT                 18
#define TRB_CMD_NEGOTIATE_BANDWIDTH          19
#define TRB_CMD_SET_LATENCY_TOLERANCE_VALUE  20
#define TRB_CMD_GET_PORT_BANDWIDTH           21
#define TRB_CMD_FORCE_HEADER                 22
#define TRB_CMD_NO_OP                        23
#define TRB_CMD_GET_EXT_PROPERTY             24
#define TRB_CMD_SET_EXT_PROPERTY             25
#define TRB_EVENT_TRANSFER                   32
#define TRB_EVENT_CMD_COMPLETION             33
#define TRB_EVENT_PORT_STATUS_CHANGE         34
#define TRB_EVENT_BANDWIDTH_REQUEST          35
#define TRB_EVENT_DOORBELL                   36
#define TRB_EVENT_HOST_CONTROLLER            37
#define TRB_EVENT_DEVICE_NOTIFICATION        38
#define TRB_EVENT_MFINDEX                    39

/* Standard Commands and event */
/*
 * xhci_enable_slot -- sends enable slot command to xHC
 * @param dev -- Pointer to usb device structure
 * @param slot_type -- type of slot mainly in between 0-31
 */
extern void xhci_enable_slot (usb_dev_t *dev,uint8_t slot_type);

/* xhci_send_noop_cmd -- Send No operation command
 * @param dev -- Pointer to USB structure
 */
extern void xhci_send_noop_cmd (usb_dev_t* dev);

/*
 * xhci_create_setup_trb -- creates a setup stage trb
 */
extern void xhci_create_setup_trb (xhci_slot_t* slot, uint8_t rType, uint8_t bRequest, uint16_t value, uint16_t wIndex, uint16_t wLength);

/*
 * xhci_create_data_trb -- creates data stage trb
 * @param dev -- pointer to usb structure
 * @param buffer -- pointer to memory area
 * @param size -- size of the buffer
 * @param in_direction -- direction
 */
extern void xhci_create_data_trb (xhci_slot_t* slot, uint64_t buffer, uint16_t size, bool in_direction);

/*
 * xhci_create_status_trb -- creates status stage trb
 * @param dev -- pointer to usb strucutue
 * @param in_direction -- direction
 */
extern void xhci_create_status_trb (xhci_slot_t* slot, bool in_direction);

/*
 * xhci_address_device -- issues address device command 
 * @param dev -- pointer to usb device structure
 * @param bsr -- block set address request (BSR)
 * @param input_ctx_ptr -- address of input context
 * @param slot_id -- slot id number
 */
extern void xhci_send_address_device (usb_dev_t* dev, uint8_t bsr, uint64_t input_ctx_ptr, uint8_t slot_id);

/*
 * xhci_send_control_cmd -- Sends control commands to xhci
 * @param dev -- pointer to usb device structure
 * @param slot_id -- slot number
 * @param request -- USB request packet structure
 * @param buffer_addr -- input buffer address
 * @param len -- length of the buffer
 */
extern void xhci_send_control_cmd (usb_dev_t* dev,xhci_slot_t* slot,uint8_t slot_id, const USB_REQUEST_PACKET *request, uint64_t buffer_addr, const size_t len);

#endif