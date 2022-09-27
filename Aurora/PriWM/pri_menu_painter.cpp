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

#include "pri_menu_painter.h"
#include <acrylic.h>
#include <font.h>
#include <color.h>


void pri_menu_painter_paint (pri_menu_t *menu) {
	/*pri_popup_win_t *win = menu->window;
	acrylic_draw_rect_filled(win->pixbuf, 0,0, win->w, win->h, SILVER);
	acrylic_font_set_size(13);
	int font_y = 20;
	for (int i = 0; i < menu->menu_items->pointer; i++) {
		pri_menu_item_t *item = (pri_menu_item_t*)list_get_at(menu->menu_items, i);
		int f_h = acrylic_font_get_height(item->string);
		font_y += f_h;
		int f_w = acrylic_font_get_length(item->string);

		acrylic_font_draw_string(win->pixbuf, item->string, win->w / 2 - f_w/2,font_y,13,BLACK);
		font_y += 20;
	}
	acrylic_draw_rect_unfilled(win->pixbuf, 0, 0, win->w, win->h, DESKBLUE);*/
}