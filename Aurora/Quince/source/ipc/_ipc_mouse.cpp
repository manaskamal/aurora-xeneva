///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  _ipc_mouse.cpp --- Faster IPC mechanism for Mouse
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///! 
///! =====================================================
#include <ipc\_ipc_mouse.h>
#include <string.h>
#include <sys\_term.h>

void _ipc_mouse_dispatch (mouse_message_t *msg) {
	mouse_message_t *tmsg = (mouse_message_t*)0xFFFFFFFFB0000000;
	if (tmsg->type != 0) {
		memcpy (msg,tmsg,sizeof(mouse_message_t));
	}
	memset ((void*)0xFFFFFFFFB0000000, 0, sizeof(mouse_message_t));
}
