/**
 * Copyright (C) Manas Kamal Choudhury 2021
 *
 * dwmmsg.cpp -- DWM Fast IPC Mechanism
 *
 * /PROJECT - Aurora {Xeneva}
 * /AUTHOR  - Manas Kamal Choudhury
 *
 * ============================================
 */

#include <dwmmsg.h>
#include <string.h>
#include <sys.h>

void dwmmsg_send (message_t* msg) {
	uint64_t* data = (uint64_t*)0xFFFFD00000000000;
	data[0] = msg->dword;
	data[1] = msg->dword2;
	data[2] = msg->dword3;
	data[3] = msg->dword4;
	data[4] = msg->dword5;
	data[5] = msg->dword6;
	data[6] = msg->dword7;
	data[7] = msg->dword8;
	data[8] = msg->dword9;
	data[9] = (uint64_t)msg->dword10;
	data[10] = msg->quad;
	data[11] = msg->type;

}

void dwmmsg_receive (void* data) {
	memcpy (data,(void*)0xFFFFFFFFB0000000,4096);
}