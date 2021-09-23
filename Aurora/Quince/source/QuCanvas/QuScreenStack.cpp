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

#ifndef __QU_SCREEN_DIRTY_H__
#define __QU_SCREEN_DIRTY_H__

#include <QuCanvas\QuScreenStack.h>



static QuScreenStack *_top = NULL;
static uint32_t _rect_count = 0;

//! Push a rect to the stack
void QuScreenStackPushRect (QuRect *r) {
	QuScreenStack * s= (QuScreenStack*)malloc(sizeof(QuScreenStack));
	s->rect = r;
	s->link = _top;
	_top = s;
	_rect_count++;
}

//! Get a rect from stack
QuRect * QuScreenStackGetRect() {
	if (_top == NULL)
		return NULL;

	QuRect *r;
	QuScreenStack *temp;
	
	temp = _top;
	_top = _top->link;
	temp->link = NULL;
	r = temp->rect;
	free(temp);
	_rect_count--;
	return r;
}

uint32_t QuScreenStackGetRectCount () {
	return _rect_count;
}


#endif