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

#include "pri_menu.h"
#include <stdlib.h>
#include <string.h>
#include "pri_menu_painter.h"


pri_menu_t * root_menu;
pri_menu_t * last_menu;
uint8_t menu_id = 0;

void pri_add_menu (pri_menu_t* menu) {
	menu->next = NULL;
	menu->prev = NULL;

	if (root_menu == NULL) {
		root_menu = menu;
		last_menu = root_menu;
	}else{
		last_menu->next = menu;
		menu->prev = last_menu;
		last_menu = menu;
	}
}


void pri_remove_menu (pri_menu_t* menu) {
	if (root_menu == NULL)
		return;

	if (menu == root_menu) {
		root_menu = root_menu->next;
	} else {
		menu->prev->next = menu->next;
	}

	if (menu == last_menu) {
		last_menu = menu->prev;
	} else {
		menu->next->prev = menu->prev;
	}
}


void pri_initialize_menu_system () {
	menu_id = 0;
	root_menu = NULL;
	last_menu = NULL;
}


pri_menu_t * pri_create_menu (pri_popup_win_t *win) {
	pri_menu_t *menu = (pri_menu_t*)malloc(sizeof(pri_menu_t));
	menu->id = menu_id;
	menu->menu_items = list_init();
	menu->window = win;
	menu->next = NULL;
	menu->prev = NULL;
	menu->popup = false;
	menu_id++;
	pri_add_menu(menu);
	return menu;
}

void pri_menu_add_item (pri_menu_t* menu, pri_menu_item_t* item) {
	if (menu->menu_items == NULL)
		return;

	list_add(menu->menu_items, item);
}

pri_menu_item_t* pri_create_menu_item (char* string) {
	pri_menu_item_t *menu_i = (pri_menu_item_t*)malloc(sizeof(pri_menu_item_t));
	int string_l = strlen(string)+1;
	menu_i->string = (char*)malloc(string_l);
	strcpy (menu_i->string, string);
	menu_i->sub_menu = NULL;
	return menu_i;
}

void pri_destroy_menu_item (pri_menu_item_t* menu_i) {
	free(menu_i->string);

	if (menu_i->sub_menu)
		free(menu_i->sub_menu);

	free(menu_i);
}

void pri_complete_destroy_menu (pri_menu_t *menu) {
	if (menu->menu_items) {
		for (int i = 0; i < menu->menu_items->pointer; i++) {
			pri_menu_item_t *menu_i = (pri_menu_item_t*)list_get_at(menu->menu_items,i);
			pri_destroy_menu_item(menu_i);
		}
	}

	pri_remove_menu(menu);
	free(menu);
}

void pri_menu_show (pri_menu_t *menu) {
	pri_menu_painter_paint(menu);
}




