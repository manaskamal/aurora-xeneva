///
///   Copyright (C) Manas Kamal Choudhury 2021
///
///   _ipc_mouse --> Mouse messaging service for Quince
///   
///   /PROJECT - Aurora's Xeneva
///   /AUTHOR  - Manas Kamal Choudhury
///
///========================================================

#ifndef __IPC_MOUSE_H__
#define __IPC_MOUSE_H__

#include <stdint.h>

///! When Mouse moves or clicks it drops the signal
///! in _IPC_MOUSE_SYS area! so that Window manager can
///! get it from that area
#define _IPC_MOUSE_SYS   0x00000000B0000000

//! MOUSE CODES
#define _MOUSE_MOVE  1
typedef struct _dwm_message_ {
	uint16_t type;
	uint32_t dword;
	uint32_t dword2;
	uint32_t dword3;
	uint32_t dword4;
	uint32_t dword5;
	uint32_t dword6;
}mouse_message_t;

//! Main Mouse packet dispatcher
//! @param msg -- Pointer to mouse message address
extern void _ipc_mouse_dispatch (mouse_message_t *msg);

#endif