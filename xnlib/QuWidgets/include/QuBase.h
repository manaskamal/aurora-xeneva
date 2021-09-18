///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   QuBase -- Quince Base Object
///! 
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///!
///!===============================================

#ifndef __QU_BASE_H__
#define __QU_BASE_H__

#include <stdint.h>


//! Codes that are being send to Quince
#define QU_CODE_WIN_CREATE   100
#define QU_CODE_WIN_DESTROY  101
#define QU_CODE_WIN_MINIMIZE 102
#define QU_CODE_WIN_MAXIMIZE 103
#define QU_CODE_DIRTY_UPDATE 104

//! Codes that are sent by Quince to clients
#define QU_CANVAS_READY  200
#define QU_CANVAS_DESTROYED 201


typedef struct __QuMessage__ {
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
}QuMessage;

extern void QuChannelPut (QuMessage *msg, uint16_t to_id);
extern void QuChannelGet (QuMessage *msg);
extern void QuRegisterApplication ();
#endif