///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   QuStack -- Stack List for Canvas dirty updates
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///!
///!=====================================================

#ifndef __QU_DIRTY_STACK_H__
#define __QU_DIRTY_STACK_H__


#include <QuRect.h>
#include <stdint.h>

//!Stack for window compositor
typedef struct _stack_ {
	QuRect *rect;
	struct _stack_ *link;
}QuStack;

extern void QuStackPushRect (QuRect *r);
extern QuRect * QuStackGetRect ();
extern uint32_t QuStackGetRectCount();

#endif