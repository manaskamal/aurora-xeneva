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

#ifndef __XHCI_H__
#define __XHCI_H__

#include <stdint.h>

#pragma pack(push,1)
typedef struct _xhci_cap_regs_ {
	uint32_t cap_caplen_version;
	uint32_t cap_hcsparams1;
	uint32_t cap_hcsparams2;
	uint32_t cap_hcsparams3;
	uint32_t cap_hccparams1;
	uint32_t cap_dboff;
	uint32_t cap_hccparams2;
}xhci_cap_regs_t;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct _xhci_op_regs_ {
	uint32_t op_usbcmd;
	uint32_t op_usbsts;
	uint32_t op_pagesize;
	uint32_t op_pad1[2];
	uint32_t op_dnctrl;
	uint32_t op_crcr;
	uint32_t op_pad2[5];
	uint32_t op_dcbaap_lo;
	uint32_t op_dcbaap_hi;
	uint32_t op_config;
}xhci_op_regs_t;
#pragma pack(pop)

typedef struct _usb_dev_ {
	xhci_cap_regs_t *cap_regs;
	xhci_op_regs_t* op_regs;
	uint32_t num_slots;
	uint32_t num_ports;
	uint8_t irq;
}usb_dev_t;


/*
 * xhci_reset -- reset the xhci controller
 * @param dev -- usb device
 */
extern void xhci_reset (usb_dev_t *dev);
#endif