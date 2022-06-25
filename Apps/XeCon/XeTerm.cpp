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

#include "XeTerm.h"
#include <stdlib.h>
#include <color.h>
#include <acrylic.h>

void XETermPainter (XEWidget *widget, XEWindow *win) {
	XETerm *term = (XETerm*)widget;
	acrylic_draw_rect_filled(win->ctx,widget->x, widget->y,widget->w, widget->h, term->back_color);
	acrylic_draw_arr_string(win->ctx, widget->x + 8, widget->y, "Hello World", WHITE);
}

void XETermMouseEvent (XEWidget *widget, XEWindow *win, int x, int y, int button) {

}



XETerm * XECreateTerm (int x, int y, int w, int h) {
	XETerm *term = (XETerm*)malloc(sizeof(XETerm));
	term->base.x = x;
	term->base.y = y;
	term->base.w = w;
	term->base.h = h;
	term->base.last_mouse_x = 0;
	term->base.last_mouse_y = 0;
	term->base.clicked = 0;
	term->base.hover = 0;
	term->base.hover_painted = 0;
	term->base.action_handler = 0;
	term->base.mouse_event = XETermMouseEvent;
	term->base.painter = XETermPainter;
	term->base.destroy = 0; 
	term->back_color = LIGHTBLACK;
	term->foreground_color = WHITE;
	term->cursor_x = 0;
	term->cursor_y = 0;
	term->ws_col = w / 8;
	term->ws_row = h / 16;
	term->ws_xpixels = w;
	term->ws_ypixels = h;
	return term;
}
