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
 * @daisy_window_painter.cpp -- daisy window user interface
 *
 **/

#include "daisy_window_painter.h"
#include "daisy.h"
#include "daisy_widget.h"
#include <acrylic.h>
#include <canvas.h>
#include <font.h>
#include <color.h>

/**
 * daisy_window_paint -- draw the window with everything inside it
 * @param win -- window to draw
 */
void daisy_window_paint (daisy_window_t *win) {
	daisy_win_info_t *info = (daisy_win_info_t*)win->shared_win;

	if (win->theme == DAISY_THEME_DEFAULT) {

		/* draws a rectangle for the title bar */
		acrylic_draw_rect_filled (win->ctx, 0,0,info->width, 23, WHITE);
		/* draws a rectangular outline for the title bar */
		acrylic_draw_rect_unfilled (win->ctx, 0,0,info->width,23,LIGHTBLACK);

		/*set the font size */
		if (win->title) {
			acrylic_font_set_size(11);
			acrylic_font_draw_string (win->ctx,win->title,10,15,12,GRAY);
		}

		/* draw every widgets */
		for (int i = 0; i < win->widgets->pointer; i++) {
			daisy_widget_t *widget = (daisy_widget_t*)list_get_at(win->widgets, i);
			widget->refresh(widget,win);
		}
	} else if (win->theme == DAISY_THEME_90S) {
			/* draws a rectangle for the title bar */
		acrylic_draw_rect_filled (win->ctx, 0,0,info->width, 23, 0xFFBDB9B9);  //

		acrylic_draw_horizontal_line (win->ctx,0,1,info->width,WHITE);
		//acrylic_draw_horizontal_line (win->ctx, 0,2,info->width,WHITE);

		acrylic_draw_rect_filled (win->ctx,2,3,info->width-2,23-3,DESKBLUE);

		/* draws a rectangular outline for the title bar */
		acrylic_draw_rect_unfilled (win->ctx, 0,0,info->width,23,LIGHTBLACK);

		/*set the font size */
		if (win->title) {
			acrylic_font_set_size(11);
			acrylic_font_draw_string (win->ctx,win->title,10,15,12,WHITE);
		}

		/* draw every widgets */
		for (int i = 0; i < win->widgets->pointer; i++) {
			daisy_widget_t *widget = (daisy_widget_t*)list_get_at(win->widgets, i);
			widget->refresh(widget,win);
		}

		/* Draw the Window Border */
		acrylic_draw_horizontal_line (win->ctx, 0, info->height-1, info->width,0xFFBDB9B9);
		acrylic_draw_vertical_line (win->ctx, info->width-1,0, info->height,0xFFBDB9B9);
		acrylic_draw_vertical_line (win->ctx,1,23, info->height-23,0xFFBDB9B9);
	}
}
