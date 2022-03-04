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
 * @dock_button -- dock buttons header
 *
 **/

#include "dock_button.h"

/**
 * dock_button_refresh -- refresh handler of the button
 * @param button -- pointer to self
 * @param ctx -- canvas off-screen buffer
 */
void dock_button_refresh (dock_button_t *button, canvas_t *ctx) {
	int x = button->x;
	int y = button->y;
	int w = button->width;
	int h = button->height;
	char* title = button->label;

	if (button->focused) {
		acrylic_draw_rect_filled(ctx,x,y,w,h,0xFFA09999);
		acrylic_draw_horizontal_line (ctx,x,y,w,LIGHTBLACK);
		acrylic_draw_horizontal_line (ctx,x,y + 1,w,LIGHTBLACK);
		acrylic_draw_horizontal_line (ctx,x,y + 2,w,LIGHTBLACK);

		acrylic_draw_horizontal_line (ctx,x,h-1,w,0xFFCAC5C5);
		acrylic_draw_horizontal_line (ctx,x,h-2,w,0xFFCAC5C5);

		acrylic_font_set_size(12);
		int font_h = acrylic_font_get_height (title);
		int font_l = acrylic_font_get_length(title);
		acrylic_font_draw_string(ctx,title, x + w/2 - font_l / 2,y + h / 2 + 5, 12,BLACK);
		acrylic_draw_rect_unfilled(ctx,x,y,w,h,BLACK);
	}else {
		acrylic_draw_rect_filled(ctx,x,y,w,h,0xFFA8A6A6);
		acrylic_draw_horizontal_line (ctx,x,y,w,WHITE);
		acrylic_draw_horizontal_line (ctx,x,y + 1,w,WHITE);
		acrylic_draw_horizontal_line (ctx,x,y + 2,w,WHITE);

		acrylic_draw_horizontal_line (ctx,x,h-1,w,LIGHTBLACK);
		acrylic_draw_horizontal_line (ctx,x,h-2,w,LIGHTBLACK);

		acrylic_font_set_size(12);
		int font_h = acrylic_font_get_height (title);
		int font_l = acrylic_font_get_length(title);
		acrylic_font_draw_string(ctx,title, x + w/2 - font_l / 2,y + h / 2 + 5, 12,BLACK);
		acrylic_draw_rect_unfilled(ctx,x,y,w,h,BLACK);
	}
}

/**
 * dock_create_button -- creates a dock button 
 * @param canvas -- canvas buffer, where to draw
 * @param x -- x coord
 * @param y -- y coord
 * @param width -- width of the button
 * @param height -- height of the button
 * @param title -- label of the button
 */
dock_button_t * dock_create_button (int x, int y, int width, int height, char* title){
	dock_button_t *button = (dock_button_t*)malloc(sizeof(dock_button_t));
	button->x = x;
	button->y = y;
	button->width = width;
	button->height = height;
	button->label = title;
	button->refresh = dock_button_refresh;
	button->mouse_event = 0;
	return button;
}