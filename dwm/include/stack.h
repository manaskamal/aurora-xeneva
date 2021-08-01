/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  stack.h -- Stack data structure for dwm
 *
 *  /PROJECT - Aurora Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ===============================================
 */

#ifndef __STACK_H__
#define __STACK_H__

#include <sys.h>
#include "dwm.h"


//!Stack for window compositor
typedef struct _stack_ {
	rect_t *rect;
	struct _stack_ *link;
}stack_t;

extern void stack_push_rect (rect_t *r);
extern rect_t * stack_get_rect(uint32_t *id);

#endif