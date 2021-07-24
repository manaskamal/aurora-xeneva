/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  message.h -- IPC Messaging protocol 
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ========================================
 */

#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <stdint.h>
#include <stdio.h>

#ifdef ARCH_X64
#include <arch\x86_64\thread.h>
#endif


//! Message format
typedef struct _message_ {
	uint32_t dword;
	uint32_t dword2;
	uint32_t dword3;
	uint32_t dword4;
	uint32_t dword5;
	uint32_t dword6;
	uint32_t dword7;
	uint32_t dword8;
	uint32_t dword9;
	uint32_t *dword10;
	uint64_t quad;
	uint16_t type;
	char  buffer[50];
}message_t;



typedef struct _kernel_message_queue_ {
	message_t msg;
	struct _kernel_message_queue_ *link;
}kernel_message_queue_t;


//!**********************************************
//! FUNCTION PROTOTYPE
//!**********************************************
extern void message_init ();
extern void message_send (uint16_t dest_id, message_t *msg);
extern void message_receive (message_t* msg);
#endif