///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   QuMessageStore.h -- Quince Message Storing data structure
///!
///!   When clients sends messages to Quince, Quince don't respond to it
///!   immediately, it stores the message and response to every message
///!   in serial way (asynchronized)
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///!
///!======================================================================

#ifndef __QU_MESSAGE_STORE_H___
#define __QU_MESSAGE_STORE_H___


#include <QuRect.h>
#include <stdint.h>

//!Stack for window compositor
typedef struct _msg_stack_ {

	struct _msg_stack_ *link;
}QuMessageStack;

extern void QuMessageStackPushMsg (QuRect *r);
extern QuRect * QuMessageStackGetMsg ();
extern uint32_t QuMessageStackGetMsgCount();
#endif