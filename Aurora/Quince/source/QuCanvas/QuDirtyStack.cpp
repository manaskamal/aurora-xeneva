///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   QuStack -- Stack List for Canvas dirty updates
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///!
///!=====================================================

#include <QuCanvas\QuDirtyStack.h>
#include <stdlib.h>


static QuStack *top = NULL;
static uint32_t rect_count = 0;

//! Push a rect to the stack
void QuStackPushRect (QuRect *r) {
	QuStack * s= (QuStack*)malloc(sizeof(QuStack));
	s->rect = r;
	s->link = top;
	top = s;
	rect_count++;
}

//! Get a rect from stack
QuRect * QuStackGetRect() {
	if (top == NULL)
		return NULL;

	QuRect *r;
	QuStack *temp;
	
	temp = top;
	top = top->link;
	temp->link = NULL;
	r = temp->rect;
	free(temp);
	rect_count--;
	return r;
}

uint32_t QuStackGetRectCount () {
	return rect_count;
}

