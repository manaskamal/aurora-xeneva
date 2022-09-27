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

#include "styles\XEMenubarDefaultStyle.h"
#include <acrylic.h>
#include "xemenu.h"
#include <color.h>
#include <font.h>


void XEDefaultMenubarPainter (XEWidget *widget, XEWindow *window) {
	XEMenubar* menubar = (XEMenubar*)widget;
	acrylic_draw_vertical_gradient(window->ctx,menubar->base.x, menubar->base.y, menubar->base.w, menubar->base.h,
		SILVER, GRAY);

	acrylic_font_set_size(10);
	int x = 10;
	int y = menubar->base.y + 5;
	for (int i = 0; i < menubar->menu_list->pointer; i++) {
		XEMenu *menu = (XEMenu*)list_get_at(menubar->menu_list, i);
		int font_width = acrylic_font_get_length(menu->name);
		int font_height = acrylic_font_get_height(menu->name);
		acrylic_font_draw_string(window->ctx, menu->name, x, y + menubar->base.h/2 - font_height/2 , 10, BLACK);
		
		/* Now assign the geometry for each menu button inside
		 * menubar
		 */
		if (menu->menu_button_x == 0 && menu->menu_button_y == 0 &&
			menu->menu_button_w == 0 && menu->menu_button_h == 0) {
				menu->menu_button_x = x;
				menu->menu_button_y = y;
				menu->menu_button_w = font_width + 10;
				menu->menu_button_h = menubar->base.h - 10;
		}

		if (menu->base.x == 0 && menu->base.y == 0 ) {
			menu->base.x = x;
			menu->base.y = menubar->base.h;
		}

	    x += font_width + 10;
	}
}

