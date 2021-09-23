///! 
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuScreenDirty -- Minimizes the whole screen to a specific rectangle
///!                   for smooth updates
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!========================================================================

#ifndef __QU_SCREEN_STACK_H__
#define __QU_SCREEN_STACK_H__

#include <stdint.h>
#include <stdlib.h>
#include <QuRect.h>

//!Stack for window compositor
typedef struct _dirty_stack_ {
	QuRect *rect;
	struct _dirty_stack_ *link;
}QuScreenStack;

extern void QuScreenStackPushRect (QuRect *r);
extern QuRect * QuScreenStackGetRect ();
extern uint32_t QuScreenStackGetRectCount();

#endif