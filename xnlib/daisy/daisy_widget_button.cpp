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
 * @daisy_widget_button.cpp -- daisy buttton widget user interface
 *
 **/

#include "daisy_widget_button.h"
#include <stdlib.h>
#include <acrylic.h>
#include <color.h>
#include <font.h>
#include <sys/_term.h>


void daisy_button_refresh (daisy_widget_t *widget, daisy_window_t* win) {
	daisy_widget_button_t * button = (daisy_widget_button_t*)widget;
	uint32_t fill_color = SILVER;
	if (button->clicked) {
		fill_color = GRAY;
	}

	acrylic_draw_rect_filled (win->ctx, button->base.x, button->base.y, button->base.width, button->base.height,fill_color);
	acrylic_draw_rect_unfilled (win->ctx,button->base.x, button->base.y, button->base.width + 1, button->base.height + 1,BLACK);
	
	if (button->text) {
		acrylic_font_set_size (11);
		int mid_w = acrylic_font_get_length (button->text);
		int mid_h = acrylic_font_get_height (button->text);
		acrylic_font_draw_string (win->ctx,button->text,button->base.x + button->base.width/2 - mid_w/2,
			button->base.y + button->base.height/2 - mid_h/2,11,BLACK);
	}
}

void daisy_button_mouse_event (daisy_widget_t *widget, daisy_window_t *win, int button, bool clicked, int x, int y) {
	daisy_widget_button_t *button_w = (daisy_widget_button_t*)widget;

	if (button && button_w->last_mouse_x == x &&
		button_w->last_mouse_y == y) {
		button_w->clicked = true;
		daisy_button_refresh(widget,win);
		daisy_window_update (win,widget->x,widget->y,widget->width,widget->height);
	}else {
		if (button_w->clicked) {
			button_w->clicked = false;
			daisy_button_refresh(widget,win);
			daisy_window_update (win,widget->x,widget->y,widget->width,widget->height);
		}
	}

	button_w->last_mouse_button = button;
	button_w->last_mouse_x = x;
	button_w->last_mouse_y = y;
}
/**
 * daisy_widget_create_button -- create a button widget
 * @param width -- width of the button
 * @param height -- height of the button
 */
daisy_widget_button_t *daisy_widget_create_button (daisy_window_t* win, char* text) {
	daisy_win_info_t *info = daisy_get_window_info(win);
	daisy_widget_button_t *button = (daisy_widget_button_t*)malloc(sizeof(daisy_widget_button_t));
	button->base.x = 0;
	button->base.y = 23;
	button->base.width = info->width;
	button->base.height = info->height - 23;
	button->base.action_event = 0;
	button->base.key_event = 0;
	button->base.mouse_event = daisy_button_mouse_event;
	button->base.refresh = daisy_button_refresh;
	button->base.scroll_event = 0;
	button->text = text;
	button->last_mouse_button = 0;
	button->clicked = 0;
	return button;
}

/**
 * daisy_widget_button_set_dimension -- set a specific dimension to 
 * the widget
 * @param button -- reference button
 * @param x -- x coordinate 
 * @param y -- y coordinate
 * @param w -- width 
 * @param h -- height
 */
void daisy_widget_button_set_dimension (daisy_widget_button_t* button,int x, int y,int w, int h) {
	button->base.x = x;
	button->base.y = y;
	button->base.width = w;
	button->base.height = h;
}