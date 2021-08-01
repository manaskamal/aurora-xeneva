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

#include <stack.h>
#include <allocator.h>

static stack_t *top = NULL;

//! Push a rect to the stack
void stack_push_rect (rect_t *r) {
	stack_t * s= (stack_t*)dalloc(sizeof(stack_t));
	s->rect = r;
	s->link = top;
	top = s;
}

//! Get a rect from stack
rect_t * stack_get_rect(uint32_t *id) {
	if (top == NULL)
		return NULL;

	rect_t *r;
	stack_t *temp;
	
	temp = top;
	top = top->link;
	temp->link = NULL;
	r = temp->rect;
	dfree(temp);
	return r;
}
