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

#ifndef __XHCI_H__
#define __XHCI_H__

#include <stdint.h>
#include <arch\x86_64\thread.h>

#define XHCI_USB_CMD_INTE  (1<<2) //Interrupter enable
#define XHCI_USB_CMD_HSEE  (1<<3) // Host System Error enable

#define XHCI_USB_STS_HCH  (1<<0)  //HC Halted
#define XHCI_USB_STS_HSE  (1<<2)  //Host System Error -- 1 on error
#define XHCI_USB_STS_EINT (1<<3)  //Event Interrupt
#define XHCI_USB_STS_PCD  (1<<4)  //Port Change Detect
#define XHCI_USB_STS_SSS  (1<<8)  //Save state status -- 1 when cmd_css is 1
#define XHCI_USB_STS_RSS  (1<<9)  //Restore state status
#define XHCI_USB_STS_SRE  (1<<10) //Save Restore error
#define XHCI_USB_STS_CNR  (1<<11) //Controller Not Ready
#define XHCI_USB_STS_HCE  (1<<12) //Host Controller Error

#define XHCI_USB_CFG_MXSLOT_ENABLE  0xFF
#define XHCI_USB_CFG_U3_EN  (1<<8)  //U3 Entry Enable
#define XHCI_USB_CFG_CINFO_EN    (1 << 9) //Config Information Enable

#define XHCI_USB_CCR_RCS  (1<<0)  //Ring Cycle State
#define XHCI_USB_CCR_CS   (1<<1)  //Command Stop
#define XHCI_USB_CCR_CA   (1<<2)  //Command Abort
#define XHCI_USB_CCR_CRR  (1<<3)  //Command Ring Running

#define XHCI_USB_CCR_PTR_LO  0xFFFFFFC0
#define XCHI_USB_CCR_PTR     0xFFFFFFFFFFFFFFC0

#define XHCI_PORTSC_CCS  (1<<0) //Current Connect Status
#define XHCI_PORTSC_PED  (1<<1)  //Port Enabled/Disabled
#define XHCI_PORTSC_OCA  (1<<3)  //Overcurrent Active
#define XHCI_PORTSC_PR   (1<<4)  //Port Reset
#define XHCI_PORTSC_PP   (1<<9)  //Port Power 
#define XHCI_PORTSC_CSC  (1<<17) //Connect Status Change
#define XHCI_PORTSC_PEC  (1<<18)  //Port Enabled/Disabled Change
#define XHCI_PORTSC_PRC  (1<<21)  //Port Reset Change
#define XHCI_PORTSC_WPR  (1<<31) //On USB3 port warm reset

#define XHCI_INT_ERDP_BUSY  (1<<3)


#define XHCI_TRB_SIZE  16 
#define XHCI_EVENT_RING_SEG_TBL_ENTRY_SIZE 16

#define XHCI_TRB_ENT  0x200000000
#define XHCI_TRB_ISP  0x400000000
#define XHCI_TRB_IOC  0x2000000000
#define XHCI_TRB_IDT  0x4000000000
#define XHCI_TRB_TRT(x)   ((uint64_t)x << 48)
#define XHCI_TRB_DIR_IN   ((uint64_t)1 << 48)

#define XHCI_DOORBELL_ENDPOINT_0    1
#define XHCI_DOORBELL_ENDPOINT_1    2


#pragma pack(push,1)
typedef struct _xhci_cap_regs_ {
	uint8_t cap_caplen_version;
	uint8_t reserved;
	uint16_t hci_version;
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
	uint64_t op_crcr;
	uint32_t op_pad2[4];
	uint32_t op_dcbaap_lo;
	uint32_t op_dcbaap_hi;
	uint32_t op_config;
}xhci_op_regs_t;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct _xhci_trb_{
	uint32_t trb_param_1;
	uint32_t trb_param_2;
	uint32_t trb_status;
	uint32_t trb_control;
}xhci_trb_t;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct _xhci_event_trb_ {
	uint64_t ptr;
	uint32_t rsvd: 24;
	uint32_t completionCode: 8;
	uint32_t cycleBit : 1;
	uint32_t rsvd2: 9;
	uint32_t trbType : 6;
	uint32_t rsvd3 : 16;
} xhci_event_trb_t;
#pragma pack(pop)



#pragma pack(push,1)
typedef struct _xhci_link_trb_ {
	uint64_t segment_ptr;
	uint32_t rsvd : 24;
	uint32_t interrupter_target : 8;
	uint32_t cycle_bit : 1;
	uint32_t toggle_cycle : 1;
	uint32_t rsvd2 : 2;
	uint32_t chain_bit : 1;
	uint32_t ioc : 1;
	uint32_t rsvd3 : 4;
	uint32_t trb_type : 6;
	uint32_t rsvd4 : 16;
} xhci_link_trb_t;
#pragma pack (pop)

#pragma pack(push,1)
typedef struct _xhci_setup_trb_t_ {
	uint32_t bmRequestType : 8;
	uint32_t bRequest : 8;
	uint32_t wValue : 16;
	uint32_t wIndex : 16;
	uint32_t wLength : 16;
	uint32_t trbTransferLength : 17;
	uint32_t rsvdZ : 5;
	uint32_t interrupterTarget : 10;
	uint32_t cycleBit : 1;
	uint32_t rsvdZ2 : 4;
	uint32_t ioc : 1;
	uint32_t immediateData : 1;
	uint32_t rsvdZ3 : 3;
	uint32_t trbType : 6;
	uint32_t transferType : 2;
	uint32_t rsvdZ4 : 14;
} xhci_setup_trb_t;
#pragma pack(pop)


#pragma pack(push,1)
typedef struct _xhci_data_trb_ {
	uint64_t dataBuffer;
	uint32_t transferLength : 17;
	uint32_t size : 5;
	uint32_t interrupterTarget : 10;
	uint32_t cycleBit : 1;
	uint32_t evaluateNextTRB : 1;
	uint32_t interrupt_on_short_packet : 1;
	uint32_t no_snoop : 1;
	uint32_t chain_bit : 1;
	uint32_t ioc : 1;
	uint32_t immediate_data : 1;
	uint32_t rsvdZ : 3;
	uint32_t trb_type : 6;
	uint32_t direction : 1;
	uint32_t rsvdZ2 : 15;
}xhci_data_trb_t;
#pragma pack(pop)

typedef struct _xhci_status_trb_ {
	uint32_t rsvdZ0[2];
	uint32_t rsvdZ : 22;
	uint32_t interrupter_target : 10;
	uint32_t cycle_bit : 1;
	uint32_t evaluateNextTRB : 1;
	uint32_t rsvdZ2 : 2;
	uint32_t chainBit : 1;
	uint32_t ioc : 1;
	uint32_t rsvdZ3 : 4;
	uint32_t trb_type : 6;
	uint32_t direction : 1;
	uint32_t rsvdZ4 : 15;
}xhci_status_trb_t;
#pragma pack(pop)


#pragma pack(push,1)
typedef struct _xhci_intr_reg_ {
	unsigned intr_man;
	unsigned intr_mod;
	unsigned evtRngSegTabSz;
	unsigned res;
	unsigned evtRngSegBaseLo;
	unsigned evtRngSegBaseHi;
	unsigned evtRngDeqPtrLo;
	unsigned evtRngDeqPtrHi;
}xhci_interrupter_reg_t;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct _xhci_runtime_regs_ {
	unsigned micro_frame_index;
	char res[28];
	xhci_interrupter_reg_t intr_reg[];
}xhci_runtime_regs_t;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct _xhci_doorbell_ {
	unsigned doorbell[256];
}xhci_doorbell_regs_t;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct _xhci_ex_cap_ {
	uint32_t id : 8;
	uint32_t next : 8;
	uint32_t controller_bios_semaphore : 1;
	uint32_t rsvd : 7;
	uint32_t controller_os_sem : 1;
	uint32_t rsvd2 : 7;
}xhci_ext_cap_t;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct _xhci_ex_cap_protocol_ {
	xhci_ext_cap_t base;
	unsigned char name[4];
	uint32_t port_cap_field;
	uint32_t port_cap_field2;
}xhci_ex_cap_protocol_t;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct _xhci_port_reg_ {
	uint32_t port_sc;
	uint32_t port_pmsc;
	uint32_t port_link_info;
	uint32_t port_hardware_LMP_ctl;
}xhci_port_regs_t;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct _xhci_noop_trb_ {
	uint32_t rsvdZ[3];
	uint32_t cycleBit : 1;
	uint32_t rsvdZ2 : 9;
	uint32_t trb_type : 6;
	uint32_t rsvdZ3 : 16;
}xhci_noop_cmd_trb_t;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct _xhci_erst_ {
	uint32_t event_ring_segment_lo;
	uint32_t event_ring_seg_hi;
	uint32_t ring_seg_size;
	uint32_t rerserved;
}xhci_erst_t;
#pragma pack(pop)

typedef struct _xhci_slot_ {
	uint8_t slot_id;
	uint8_t root_hub_port_num;
	uint64_t cmd_ring_base;
	xhci_trb_t* cmd_ring;
	unsigned cmd_ring_index;
	unsigned cmd_ring_max;
	unsigned cmd_ring_cycle;
}xhci_slot_t;

typedef struct _usb_dev_ {
	bool initialized;
	thread_t *usb_thread;
	xhci_cap_regs_t *cap_regs;
	xhci_op_regs_t* op_regs;
	xhci_doorbell_regs_t *db_regs;
	xhci_runtime_regs_t *rt_regs;
	xhci_ext_cap_t *ext_cap;
	xhci_port_regs_t *ports;
	uint32_t num_slots;
	uint32_t num_ports;
	uint8_t irq;
	uint64_t* dev_ctx_base_array;
	xhci_trb_t *cmd_ring;
	uint64_t cmd_ring_phys;
	unsigned cmd_ring_index;
	unsigned cmd_ring_max;
	unsigned cmd_ring_cycle;
	uint64_t* event_ring_segment;
	unsigned evnt_ring_index;
	unsigned evnt_ring_cycle;
	unsigned evnt_ring_max;
	int poll_event_for_trb;
	bool event_available;
	int poll_return_trb_type;
	int trb_event_index;
}usb_dev_t;

/* USB speed numbers */
#define USB_SPEED_RESERVED   0
#define USB_FULL_SPEED       1
#define USB_LOW_SPEED        2
#define USB_HIGH_SPEED       3
#define USB_SUPER_SPEED      4
#define USB_SUPER_SPEED_PLUS 5

/*
 * xhci_reset -- reset the xhci controller
 * @param dev -- usb device
 */
extern void xhci_reset (usb_dev_t *dev);

/*
 * xhci_device_ontext_init -- initialize the device context
 * base array pointer (DCBAAP)
 */
extern void xhci_device_context_init (usb_dev_t *dev);

/*
 * xhci_command_ring_init -- initialize the command ring 
 */
extern void xhci_command_ring_init(usb_dev_t *dev);

/*
 * xhci_protocol_init -- Initialize XHCI Extended Protocol 
 * @param dev -- Pointer to usb device
 */
extern void xhci_protocol_init (usb_dev_t *dev);

/*
 * xhci_event_ring_init -- initialize the 
 * default event ring
 * @param dev -- Pointer to usb device
 */
extern void xhci_event_ring_init (usb_dev_t *dev);

/*
 * xhci_poll_event -- waits for an event to occur on interrupts
 * @param usb_device -- pointer to usb device structure
 * @param trb_type -- type of trb to look
 * @return trb_event_index -- index of the trb on event_ring_segment
 */
int xhci_poll_event (usb_dev_t* usb_device, int trb_type);

/*
 * xhci_send_command_multiple -- sends multiple commands to the command ring
 * @param dev -- Pointer to usb structure
 * @param trb -- TRB address containing multiple TRBs
 * @param num_count -- counts of TRB to send
 */
void xhci_send_command_multiple (usb_dev_t* dev, xhci_trb_t* trb, int num_count);


/*
 * xhci_send_command -- Sends command to USB device through XHCI
 * host
 * @param dev -- Pointer to usb device structure
 * @param param1 -- parameter 1 of TRB
 * @param param2 -- parameter 2 of TRB
 * @param status -- status of TRB
 * @param ctrl -- control for TRB
 */
void xhci_send_command (usb_dev_t *dev, uint32_t param1, uint32_t param2, uint32_t status, uint32_t ctrl);

/*
 * xhci_send_command_slot -- sends command to slot trb
 * @param slot -- pointer to slot data structure
 * @param param1 -- first parameter of trb structure
 * @param param2 -- 2nd parameter of trb structure
 * @param status -- status field of trb structure
 * @param ctrl -- control field of trb structure
 */
void xhci_send_command_slot (xhci_slot_t* slot,uint32_t param1, uint32_t param2, uint32_t status, uint32_t ctrl);


/*
 * xhci_ring_doorbell -- rings the host doorbell
 * @param dev -- Pointer to usb structure
 */
void xhci_ring_doorbell(usb_dev_t* dev);

/*
 * xhci_ring_doorbell_slot -- rings the doorbell by slot
 * @param dev -- Pointer to usb structure
 * @param slot -- slot id
 * @param endpoint -- endpoint number, it should be 0 if
 * the slot is 0, else values 1-255 should be placed
 *
 */
void xhci_ring_doorbell_slot(usb_dev_t* dev, uint8_t slot, uint32_t endpoint);

/*
 * xhci_port_initialize -- initializes all powered ports
 * @param dev -- Pointer to USB device structures
 */
extern void xhci_port_initialize (usb_dev_t *dev);

/*
 * xhci_port_initialize_by_num -- initializes a specific port
 * @param dev -- Pointer to USB device structures
 */
extern void xhci_port_initialize_by_num (usb_dev_t *dev, unsigned int port);
#endif