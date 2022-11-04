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

#include "styles\XEDefaultMenuStyle.h"
#include <canvas.h>
#include <acrylic.h>
#include <color.h>
#include <xemenu.h>
#include <sys/_term.h>
#include <font.h>

void XEDefaultMenuPainter (XEWidget *widget, XEWindow* window) {
	XEMenu *menu = (XEMenu*)widget;

	acrylic_draw_rect_filled(menu->pixbuf, 0,0,menu->quickwin->server->w,menu->quickwin->server->h-1,WHITE);

	if (!menu->calculated_metrics) 
		XEMenuCalculateItemMetrics(menu);


	for (int i = 0; i < menu->menu_items->pointer; i++) {
		XEMenuItemButton *button = (XEMenuItemButton*)list_get_at(menu->menu_items, i);
		if (button->base.painter)
			button->base.painter((XEWidget*)button,window);
	}

	acrylic_draw_rect_unfilled(menu->pixbuf, 0,0,menu->quickwin->server->w,menu->quickwin->server->h-1,BLACK);

}

void XEDefaultMenuItemPainter (XEWidget* widget, XEWindow* window) {
	XEMenuItemButton *menu_item = (XEMenuItemButton*)widget;
	acrylic_font_set_size(10);
	if (menu_item->parent) {
		int font_h = acrylic_font_get_height(menu_item->name);
		int font_w = acrylic_font_get_length(menu_item->name);
		acrylic_font_draw_string(menu_item->parent->pixbuf, menu_item->name,menu_item->base.x, 
			menu_item->base.y + menu_item->base.h/2 - font_h/2, 10, BLACK);
	}
}