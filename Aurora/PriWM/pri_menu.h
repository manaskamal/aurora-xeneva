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
 **/

#ifndef __PRI_MENU_H__
#define __PRI_MENU_H__

#include <stdint.h>
#include <list.h>
#include "pri_popup.h"


typedef struct _menu_ {
	uint8_t id;
	list_t *menu_items;
	pri_popup_win_t *window;
	bool popup;
	_menu_ *next;
	_menu_ *prev;
}pri_menu_t;


typedef struct _menu_item_ {
	char* string;
	pri_menu_t* sub_menu;
	bool selected;
	bool hovered;
	bool disabled;
}pri_menu_item_t;


extern pri_menu_t * pri_create_menu (pri_popup_win_t *win);
extern void pri_menu_add_item (pri_menu_t* menu, pri_menu_item_t* item);
extern pri_menu_item_t* pri_create_menu_item (char* string);
extern void pri_destroy_menu_item (pri_menu_item_t* menu_i);
extern void pri_complete_destroy_menu (pri_menu_t *menu);
extern void pri_menu_show (pri_menu_t *menu);


#endif