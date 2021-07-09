/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  dwm_ipc.h -- Desktop Window Manager Message streaming subsystem
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ==================================================================
 */

#ifndef __DWM_IPC_H__
#define __DWM_IPC_H__

#include <stdint.h>
#include <string.h>

#ifdef ARCH_X64
#include <arch\x86_64\mmngr\kheap.h>
#endif

typedef struct _dwm_message_ {
	uint16_t type;
	uint32_t dword;
	uint32_t dword2;
	uint32_t dword3;
	uint32_t dword4;
	uint32_t dword5;
	uint32_t dword6;
}dwm_message_t;

extern void dwm_ipc_init ();
extern void dwm_put_message (dwm_message_t *msg);
extern void dwm_dispatch_message (dwm_message_t *msg);
extern uint64_t* get_dwm_message_q_address ();
#endif