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

#ifndef __XHCI_CMD_H__
#define __XHCI_CMD_H__

#include <stdint.h>
#include "xhci.h"

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
extern void xhci_enable_slot (usb_dev_t *dev,int slot_type);

/* xhci_send_noop_cmd -- Send No operation command
 * @param dev -- Pointer to USB structure
 */
extern void xhci_send_noop_cmd (usb_dev_t* dev);
#endif