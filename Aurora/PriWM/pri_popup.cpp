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

#include "pri_popup.h"
#include <acrylic.h>
#include <canvas.h>
#include <stdlib.h>
#include <color.h>
#include <sys/mmap.h>


#define POPUP_WIN_MIN_WIDTH  310

void popup_default_draw_handler (pri_popup_win_t *win) {
	acrylic_draw_rect_filled(win->pixbuf, 0,0,win->w,win->h, WHITE);
	
}

/*
 * pri_create_popup_window -- create popup window
 * @param x -- x coordinate
 * @param y -- y coordinate
 * @param w -- width of the popup window
 * @param h -- height of the popup window
 * @param type -- type of the popup window
 */
pri_popup_win_t *pri_create_popup_window (int x, int y, int w, int h, uint8_t type) {
	pri_popup_win_t * popup = (pri_popup_win_t*)malloc(sizeof(pri_popup_win_t));
	popup->x = x;
	popup->y = y;

	/* width cannot be less than 310 */
	if (w < 310)
		w = 310;

	popup->w = w;
	popup->h = h;
	popup->type = type;
	popup->visible = false;
	popup->dirty = false;
	size_t length = popup->w *popup->h * 4;

	popup->pixbuf = create_canvas(popup->w, popup->h);
	popup->popup_draw = popup_default_draw_handler;
	return popup;
}

/*
 * pri_destroy_popup_window -- close & destroy popup window
 * @param popup -- pointer to popup window
 */
void pri_destroy_popup_window (pri_popup_win_t *popup) {
	canvas_close(popup->pixbuf);
	free(popup);
}

/*
 * pri_popup_show -- make popup window visible
 * @param popup -- pointer to popup window
 */
void pri_popup_show (pri_popup_win_t *popup) {
	popup->popup_draw(popup);
}