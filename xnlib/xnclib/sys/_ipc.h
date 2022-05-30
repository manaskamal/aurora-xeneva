/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  _ipc.h -- Kernel Standard IPC system
 *
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ==================================================
 */

#ifndef __IPC_H__
#define __IPC_H__

#include <stdint.h>
#include <sys\_xeneva.h>

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
	uint16_t dest_id;
	char  buffer[50];
}message_t;


///! Message format
typedef struct _qu_message_ {
	uint8_t type;
	uint8_t to_id;
	uint8_t from_id;
	uint32_t dword;
	uint32_t dword2;
	uint32_t dword3;
	uint32_t dword4;
	uint32_t dword5;
	uint32_t dword6;
	uint32_t dword7;
	uint32_t dword8;
	uint32_t *p_value;
	char *value;
}qu_message_t;

/*
 * pri_event_t -- event message structure
 */
typedef struct _pri_event_ {
	uint8_t type;
	uint8_t to_id;
	uint8_t from_id;
	uint32_t dword;
	uint32_t dword2;
	uint32_t dword3;
	uint32_t dword4;
	uint32_t dword5;
	uint32_t dword6;
	uint32_t dword7;
	uint32_t dword8;
	uint32_t *p_value;
	uint32_t *p_value2;
	char *value;
	unsigned char* value2;
	char char_values[100];
}pri_event_t;

//*********************************************************************
//! Standard Kernel Message Passing System. little lazy
//! more advanced ipc is the shared ipc system, it's fast
//!
//! Standard Kernel Message Passing System is used by Mouse and Keyboard
//!====================================================================

#ifdef __cplusplus
XE_EXTERN {
#endif
XE_EXPORT void message_send (unsigned short dest_id, message_t *msg);
XE_EXPORT void message_receive (message_t *msg);
XE_EXPORT void sys_pipe (int *fd, char* name);
#ifdef __cplusplus
}
#endif


#endif