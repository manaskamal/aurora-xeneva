/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  xhci.h -- USB extensible host controller interface
 *
 *  /PROJECT - Aurora Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ======================================================
 */

#ifndef __XHCI_H__
#define __XHCI_H__

#include <stdint.h>

#define XHCI_CAPREG_CAPLENGTH   0x0
#define XHCI_CAPREG_HCIVERSION  0x2
#define XHCI_CAPREG_HCSPARAMS1  0x4
#define XHCI_CAPREG_HCSPARAMS2  0x8
#define XHCI_CAPREG_HCSPARAMS3  0xC
#define XHCI_CAPREG_HCCPARAMS1  0x10
#define XHCI_CAPREG_DBOFF       0x14
#define XHCI_CAPREG_RTSOFF      0x18
#define XHCI_CAPREG_HCCPARAMS2  0x1C

#define XHCI_OPREG_USBCMD   0x0
#define XHCI_OPREG_USBSTS   0x4
#define XHCI_OPREG_PAGESIZE 0x8
#define XHCI_OPREG_DNCTRL  0x14
#define XHCI_OPREG_CRCR    0x18
#define XHCI_OPREG_DCBAAP  0x30
#define XHCI_OPREG_CONFIG  0x38

#define XHCI_OPREG_PORTSCBASE   0x400
#define XHCI_OPREG_PORTPMSCBASE 0x404
#define XHCI_OPREG_PORTLIBASE   0x408
#define XHCI_OPREG_PORTHLPMCBASE 0x40C
#define XHCI_PORTOFFSET 0x10

#define XHCI_OPREG_PORTSC(x) \
	(XHCI_OPREG_PORTSCBASE + (x-1) * XHCI_PORTOFFSET)

#define XHCI_OPREG_PORTPMSC(x) \
(XHCI_OPREG_PORTPMSCBASE + (x-1) * XHCI_PORTOFFSET)
#define XHCI_OPREG_PORTLI(x) \
(XHCI_OPREG_PORTLIBASE + (x-1) * XHCI_PORTOFFSET)
#define XHCI_OPREG_PORTHLPMC(x) \
(XHCI_OPREG_PORTHLPMCBASE + (x-1) * XHCI_PORTOFFSET)

#define XHCI_PORTSC_SPEED_GET(x) \
((x >> 10) & 0xF)

#define XHCI_RUNREG_MFINDEX 0x0
#define XHCI_RUNREG_IMANBASE 0x20
#define XHCI_RUNREG_IMODBASE 0x24
#define XHCI_RUNREG_ERSTSZBASE 0x28
#define XHCI_RUNREG_ERSTBABASE 0x30
#define XHCI_RUNREG_ERDPBASE 0x38
#define XHCI_INTERRUPTEROFFSET 0x20

#define XHCI_RUNREG_IMAN(x) \
(XHCI_RUNREG_IMANBASE + x*XHCI_INTERRUPTEROFFSET)
#define XHCI_RUNREG_IMOD(x) \
(XHCI_RUNREG_IMODBASE + x*XHCI_INTERRUPTEROFFSET)
#define XHCI_RUNREG_ERSTSZ(x) \
(XHCI_RUNREG_ERSTSZBASE + x*XHCI_INTERRUPTEROFFSET)
#define XHCI_RUNREG_ERSTBA(x) \
(XHCI_RUNREG_ERSTBABASE + x*XHCI_INTERRUPTEROFFSET)
#define XHCI_RUNREG_ERDP(x) \
(XHCI_RUNREG_ERDPBASE + x*XHCI_INTERRUPTEROFFSET)

#define XHCI_ECAP_LEGSUP 1
#define XHCI_ECAP_SUPPORT 2

#define XHCI_LEGCTLSTS_DISABLE_SMI	((0x7 << 1) + (0xff << 5) + (0x7 << 17))
#define XHCI_LEGCTLSTS_EVENTS_SMI	(0x7 << 29)

#define XHCI_TRB_TYPE_NOOP 8
#define XHCI_TRB_TYPE_ENABLE_SLOT 9
#define XHCI_TRB_TYPE_ADDRESS_DEVICE 11
#define XHCI_TRB_TYPE_EVALUATE_CONTEXT 13
#define XHCI_TRB_TYPE_RESET_ENDPOINT 14
#define XHCI_TRB_TYPE_TRANSFER_EVENT 32
#define XHCI_TRB_TYPE_COMMAND_COMPLETE 33
#define XHCI_TRB_TYPE_PORT_STATUS_CHANGE 34
#define XHCI_TRB_TYPE_SETUP_STAGE 2
#define XHCI_TRB_TYPE_DATA_STAGE 3
#define XHCI_TRB_TYPE_STATUS_STAGE 4

#define XHCI_TRB_TYPE(x) ((uint64_t)x << 42)
#define XHCI_TRB_SLOTID(x) ((uint64_t)x << 56)

#define XHCI_GET_TRB_TYPE(x) \
((x >> 42) & 0x3F)

#define XHCI_TRB_ADDRESS_BSR ((uint64_t)1<<41)
#define XHCI_TRB_ENABLED 0x100000000
#define XHCI_TRB_ENT 0x200000000
#define XHCI_TRB_ISP 0x400000000
#define XHCI_TRB_IOC 0x2000000000
#define XHCI_TRB_IDT 0x4000000000
#define XHCI_TRB_TRT(x) ((uint64_t)x << 48)
#define XHCI_TRB_DIR_IN ((uint64_t)1 << 48)

#define XHCI_DOORBELL_HOST 0x0
#define XHCI_DOORBELL_HOST_COMMAND 0
#define XHCI_DOORBELL_ENPOINT0 1

#define XHCI_DOORBELL(slot) \
(XHCI_DOORBELL_HOST+slot*4)

#define XHCI_COMPLETION_SUCCESS 1
#define XHCI_COMPLETION_STALL 6

#pragma pack(push, 1)


typedef volatile struct {
	unsigned port_sc;
	unsigned port_pmsc;
	unsigned port_li;
	unsigned res;
} xhci_port_reg_set;


typedef volatile struct {
	unsigned caps_len_hciver;
	unsigned hcsparams1;
	unsigned hcsparams2;
	unsigned hcsparams3;
	unsigned hccparams;
	unsigned dboffset;
	unsigned runtime_offset;
} xhci_cap_reg;


typedef volatile struct {
	unsigned cmd;
	unsigned stat;
	unsigned pagesz;
	char res1[8];
	unsigned dncntrl;
	unsigned cmdrctrlLo;
	unsigned cmdrctrlHi;
	char res2[16];
	unsigned dcbaapLo;
	unsigned dcbaapHi;
	unsigned config;
	char res3[964];
	xhci_port_reg_set port_reg_set[256];
}xhci_op_regs;
#pragma pack(pop)

typedef struct _xhci_ {
	size_t xhci_base_address;
	size_t xhci_op_address;
	size_t doorbell_address;
	size_t runtime_address;
}xhci;

extern void xhci_initialize ();
#endif