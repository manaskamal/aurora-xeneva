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
 * @daisy_widget_label.cpp -- daisy widget label
 *
 **/

#include "daisy_widget_label.h"
#include "daisy_window.h"
#include <font.h>
#include <canvas.h>
#include <acrylic.h>
#include <color.h>
#include <string.h>
#include <stdlib.h>


void daisy_label_refresh (daisy_widget_t *widget, daisy_window_t* win) {
	daisy_widget_label_t *label = (daisy_widget_label_t*)widget;
	if (label->text != NULL) {
		acrylic_font_set_size(label->font_size);
		int length = acrylic_font_get_length(label->text);
		int height = acrylic_font_get_height(label->text);
		acrylic_font_draw_string (win->ctx,label->text,widget->x + widget->width / 2 - length / 2,widget->y + widget->height / 2 - height / 2,
			64,label->color);
		daisy_window_update_rect_area(win,widget->x, widget->y, widget->width, widget->height);
	}
}

/**
 * daisy_label_mouse_event -- label event handler
 * @param widget -- pointer to self
 * @param win -- pointer to root window
 * @param button -- mouse button code
 * @param clicked -- boolean value for clicked/not clicked
 * @param x -- mouse x coordinate
 * @param y -- mouse y coordinate
 */
void daisy_label_mouse_event (daisy_widget_t *widget, daisy_window_t *win, int button, bool clicked, int x, int y){
}


/**
 * daisy_widget_create_button -- create a button widget
 * @param width -- width of the button
 * @param height -- height of the button
 */
daisy_widget_label_t *daisy_widget_create_label (daisy_window_t* win) {
	daisy_win_info_t *info = daisy_get_window_info(win);
	daisy_widget_label_t *label = (daisy_widget_label_t*)malloc(sizeof(daisy_widget_label_t));
	label->base.x = 0;
	label->base.y = 23;
	label->base.width = info->width;
	label->base.height = info->height - 23;
	label->base.action_event = 0;
	label->base.key_event = 0;
	label->base.mouse_event = daisy_label_mouse_event;
	label->base.refresh = daisy_label_refresh;
	label->base.scroll_event = 0;
	label->text = NULL;
	label->font_size = 14;
	label->color = GRAY;
	return label;
}

/** 
 * daisy_widget_label_set_dimension -- set label widget dimension
 * @param label -- pointer to the label widget
 * @param x -- X coordinate
 * @param y -- Y coordinate
 * @param w -- Width of the label widget
 * @param h -- Height of the label widget
 */
void daisy_widget_label_set_dimension (daisy_widget_label_t *label, int x, int y, int w, int h) {
	label->base.x = x;
	label->base.y = y;
	label->base.width = w;
	label->base.height = h;
}

/**
 * daisy_widget_label_set_text -- set a new text for the label
 * @param label -- pointer to the label widget
 * @param text -- text to be set
 */
void daisy_widget_label_set_text (daisy_widget_label_t *label, char* text) {
	label->text = text;
}

/**
 * daisy_widget_label_set_font_size -- set a new font size for the label
 * @param label -- pointer to the label widget
 * @param size -- new size of the font
 */
void daisy_widget_label_set_font_size (daisy_widget_label_t *label, int size) {
	label->font_size = size;
}

/**
 * daisy_widget_label_set_color -- set a new color to the label
 * @param label -- pointer to the label widget
 * @param color -- color for the label
 */
void daisy_widget_label_set_color (daisy_widget_label_t *label, uint32_t color) {
	label->color = color;
}