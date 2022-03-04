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
 * @daisy_widget_onoff  -- daisy onoff widget user interface
 *
 **/

#include "daisy_widget_onoff.h"
#include "daisy.h"
#include <acrylic.h>
#include <canvas.h>
#include <color.h>

/**
 * daisy_onoff_refresh -- onoff refresh handler
 * @param widget -- pointer to self
 * @param win -- pointer to root window
 */
void daisy_onoff_refresh (daisy_widget_t *widget, daisy_window_t* win)  {
	daisy_widget_onoff_t *onoff = (daisy_widget_onoff_t*)widget;
	
	acrylic_draw_rect_unfilled (win->ctx, onoff->base.x, onoff->base.y, onoff->base.width, onoff->base.height, GRAY);
	
	if (onoff->on) {
		linear_gradient (win->ctx,widget->x + 1,  widget->y + 1, widget->width - 1, widget->height - 1,
			PALEGREEN, GREEN);
		acrylic_draw_rect_unfilled (win->ctx,widget->x + onoff->thumb_x, widget->y + 1,onoff->thumb_w - 1, onoff->thumb_h - 1,GRAY);
		acrylic_draw_rect_filled (win->ctx,widget->x + onoff->thumb_x + 1, widget->y + 1,onoff->thumb_w - 2, onoff->thumb_h - 2,LIGHTBLACK);
	}else {
		acrylic_draw_rect_filled (win->ctx, onoff->base.x + 1, onoff->base.y + 1, onoff->base.width - 1, onoff->base.height - 1, SILVER);
				acrylic_draw_rect_unfilled (win->ctx,widget->x + onoff->thumb_x, widget->y + 1,onoff->thumb_w - 1, onoff->thumb_h - 1,BLACK);
				acrylic_draw_rect_filled (win->ctx,widget->x + onoff->thumb_x  + 1, widget->y + 1, onoff->thumb_w - 2, onoff->thumb_h - 2,LIGHTBLACK);
	}
}

/**
 * daisy_onoff_mouse_event -- onoff event handler
 * @param widget -- pointer to self
 * @param win -- pointer to root window
 * @param button -- mouse button code
 * @param clicked -- boolean value for clicked/not clicked
 * @param x -- mouse x coordinate
 * @param y -- mouse y coordinate
 */
void daisy_onoff_mouse_event (daisy_widget_t *widget, daisy_window_t *win, int button, bool clicked, int x, int y){
	daisy_widget_onoff_t *onoff = (daisy_widget_onoff_t*)widget;

	if (button && onoff->last_m_x == x &&
		onoff->last_m_y == y) {

			if (onoff->on) {
				onoff->on = false;
				onoff->thumb_x = 0;
				daisy_onoff_refresh(widget,win);
				daisy_window_update_rect_area(win,widget->x, widget->y, widget->width, widget->height);
			}else  {
				onoff->on = true;
				onoff->thumb_x = widget->width / 2;
				daisy_onoff_refresh(widget,win);
				daisy_window_update_rect_area(win,widget->x, widget->y, widget->width, widget->height);
			}
			win->focused_widget = widget;
	}

	onoff->last_m_x = x;
	onoff->last_m_y = y;
}

/**
 * daisy_widget_create_onoff -- creates onoff widget
 */
daisy_widget_onoff_t * daisy_widget_create_onoff () {
	daisy_widget_onoff_t *onoff = (daisy_widget_onoff_t*)malloc(sizeof(daisy_widget_onoff_t));
	onoff->base.x = 0;
	onoff->base.y = 23;
	onoff->base.width = 30;
	onoff->base.height = 15;
	onoff->base.action_event = 0;
	onoff->base.mouse_event = daisy_onoff_mouse_event;
	onoff->base.key_event = 0;
	onoff->base.scroll_event = 0;
	onoff->base.refresh = daisy_onoff_refresh;
	onoff->on = false;
	onoff->last_m_x = 0;
	onoff->last_m_y = 0;
	onoff->thumb_w = 30/2;
	onoff->thumb_h = onoff->base.height;
	onoff->thumb_x = 0;
	onoff->thumb_y = 0;
	return onoff;
}

/**
 * daisy_widget_onoff_set_dimension -- sets onoff wigdet dimension
 * @param onoff -- pointer to self
 * @param x -- x coordination
 * @param y -- y coordination
 */
void daisy_widget_onoff_set_dimension (daisy_widget_onoff_t *onoff, int x, int y) {
	onoff->base.x = x;
	onoff->base.y = y;
}
	