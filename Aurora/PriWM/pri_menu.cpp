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
#include <sys/_term.h>

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





