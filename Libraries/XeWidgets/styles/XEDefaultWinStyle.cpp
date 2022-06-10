/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2021, Manas Kamal Choudhury
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

#include <styles\XEDefaultWinStyle.h>
#include <xewindow.h>
#include <color.h>
#include <acrylic.h>
#include <canvas.h>
#include <sys\_term.h>
#include <font.h>
#include <string.h>

/*
 * XEDefaultPaintTitlebar -- Paints the titlebar 
 * @param win -- Pointer to the window structure
 */
void XEDefaultPaintTitlebar(XEWindow *win) {
	acrylic_draw_vertical_gradient(win->ctx, 0,0,win->shwin->width,26, LIGHTSILVER, SILVER);

	for (int i = 0; i < win->global_controls->pointer; i++) {
		XEGlobalControl *control = (XEGlobalControl*)list_get_at(win->global_controls, i);
		acrylic_draw_filled_circle(win->ctx,control->x+8, control->y+8,8,control->fill_color);
		acrylic_draw_circle(win->ctx,control->x+8, control->y+8, 8,control->outline_color);
	}

	/* Now draw the title */
	acrylic_font_set_size(10);
	int font_width = acrylic_font_get_length(win->title);
	int font_height = acrylic_font_get_height(win->title);
	acrylic_font_draw_string(win->ctx, win->title, win->shwin->width/2 - font_width/2, 26/2 + 4, 16,BLACK);

	/* Fill the titlebar with outline */
	acrylic_draw_rect_unfilled(win->ctx, 2, 0, win->shwin->width - 1, 26, GRAY);
}
/*
 * XEDefaultWinPaint -- Default Window style painter
 * @param win -- Pointer to window object
 */
void XEDefaultWinPaint(XEWindow *win) {
	acrylic_draw_rect_filled(win->ctx, 0, 0, win->shwin->width, win->shwin->height, WHITE);
	XEDefaultPaintTitlebar(win);
}