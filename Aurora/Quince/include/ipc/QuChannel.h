///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuChannel.h -- Quince Communication Channel
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!=================================================

#ifndef __QU_CHANNEL_H__
#define __QU_CHANNEL_H__

#include <stdint.h>

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
}QuMessage;


extern void QuChannelPut (QuMessage *msg, uint16_t to_id);
extern void QuChannelGet (QuMessage *msg);
extern void QuMessageStackGetMsg(QuMessage *r);
extern uint32_t QuStackGetMsgCount ();
#endif