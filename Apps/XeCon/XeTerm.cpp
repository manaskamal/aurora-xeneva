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
#include <sys\_term.h>
#include <acrylic.h>

/**
 * XETermShowCellGrid -- Shows terminal cell grid
 * @param widget -- Pointer to terminal widget
 * @param win -- Pointer to application window
 */
void XETermShowCellGrid (XEWidget* widget, XEWindow* win) {
	XETerm *term = (XETerm*)widget;

	for (int i = 0; i < term->ws_col; i++) 
		acrylic_draw_vertical_line (win->ctx, i * 8, 24, win->shwin->height - 24, GRAY);

	int __y = 24;
	for (int i = 0; i < term->ws_row; i++) {
		acrylic_draw_horizontal_line (win->ctx, 1, __y, win->shwin->width - 1, GRAY);
		__y += 1 * 16;
	}
}


void XETermDrawCell (XEWindow* win, XEWidget* widget, int x, int y) {
	XETerm *term = (XETerm*)widget;
	cell_t *cell = (cell_t*)(term->buffer + y * term->ws_col + x);
	acrylic_draw_rect_filled (win->ctx, x, y, 8, 16, cell->bg_color);
}

/*
 * XETermSetCellData -- Set a specific cell with character and other properties
 * @param widget -- Pointer to terminal widget
 * @param x -- Cell x location
 * @param y -- Cell y location
 * @param bg -- Background color
 * @param fg -- Foreground color
 */
void XETermSetCellData (XEWidget* widget, int x, int y, uint8_t c, uint32_t bg, uint32_t fg) {
	XETerm *term = (XETerm*)widget;
	cell_t *cell = (cell_t*)(term->buffer + y * term->ws_col + x);
	cell->c = c;
	cell->bg_color = bg;
	cell->fg_color = fg;
}
/*
 * XEDrawCursor -- Draws the terminal cursor at given position
 * @param win -- Pointer to application window
 * @param x -- X location
 * @param y -- Y location
 */
void XETermDrawCursor (XEWindow* win, int x, int y) {
	acrylic_draw_horizontal_line (win->ctx, x, y + 16 - 2, 8, WHITE);
	acrylic_draw_horizontal_line (win->ctx, x, y + 16 - 1, 8, WHITE);
}

void XETermPainter (XEWidget *widget, XEWindow *win) {
	XETerm *term = (XETerm*)widget;

	XETermDrawCursor (win, 0, 24);
	
	if (term->show_cell_grid)
		XETermShowCellGrid(widget, win);

	/*for (int x = 0; x < term->ws_col; x++)
		XETermDrawCell (win, widget, */

	int _x = term->cursor_x + 2; 
	int _y = term->cursor_y + 23;
	int count = 0;
	for (int j = 0; j < term->ws_row; j++) {
		char c = term->buffer[count];
		sys_print_text ("%c", c);
		acrylic_draw_arr_font (win->ctx,_x * 8, _y, c, WHITE);
		_x++;
		count++;
	}
	
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
	term->show_cell_grid = false;
	term->cursor_x = 0;
	term->cursor_y = 0;
	term->ws_col = w / 8;
	term->ws_row = h / 16;
	term->ws_xpixels = w;
	term->ws_ypixels = h;
	term->buffer = (uint8_t*)malloc(term->ws_col * term->ws_row * sizeof(cell_t));
	return term;
}
