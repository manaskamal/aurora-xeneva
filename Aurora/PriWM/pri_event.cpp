/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2022, Manas Kamal Choudhury
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * /PROJECT - Aurora's Xeneva v1.0
 * @pri_event.cpp -- priyanshi's window manager event handler
 *
 **/

#include "pri_event.h"
#include <stdlib.h>


static pri_event_gift_t *_top = NULL;
static uint32_t _gift_count = 0;

//! Push a rect to the stack
void push_event_gift (pri_event_t *r) {
	pri_event_gift_t * s= (pri_event_gift_t*)malloc(sizeof(pri_event_gift_t));
	s->event = r;
	s->link = _top;
	_top = s;
	_gift_count++;
}

//! Get a rect from stack
pri_event_t * pri_get_event() {
	if (_top == NULL)
		return NULL;

	pri_event_t *r;
	pri_event_gift_t *temp;
	
	temp = _top;
	_top = _top->link;
	temp->link = NULL;
	r = temp->event;
	free(temp);
	_gift_count--;
	return r;
}

uint32_t pri_get_gift_count() {
	return _gift_count;
}