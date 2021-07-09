/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  evntsh -- Shared Event for Mouse enhancement
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ===============================================
 */

#ifndef __EVNTSH_H__
#define __EVNTSH_H__

#include <stdint.h>

#ifdef ARCH_X64
#include <arch\x86_64\mmngr\vmmngr.h>
#endif

typedef struct _mail_ {
	uint8_t  byte;
	uint8_t  byte2;
	uint32_t dword;
	uint32_t dword2;
	uint64_t quad;
	uint64_t quad2;
	uint64_t quad3;
	uint64_t quad4;
	uint64_t quad5;
	uint64_t quad6;
}mail_t;


extern void initialize_event_shared ();
extern void event_shared_push_data(mail_t data);

#endif