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
 * @daisy_widget_slider -- daisy slider object
 *
 **/

#include "daisy_widget_slider.h"
#include <acrylic.h>
#include <canvas.h>
#include <font.h>
#include <color.h>

#include <sys/_term.h>

/**
 * daisy_slider_refresh -- refresh the slider object
 * @param widget -- pointer to self
 * @param win -- pointer to the root window
 */
void daisy_slider_refresh (daisy_widget_t *wid, daisy_window_t* win) {
	daisy_widget_slider_t *slider = (daisy_widget_slider_t*)wid;

	//* The Vertical slider *//
	if (slider->type == DAISY_SLIDER_VERTICAL) {
		acrylic_draw_rect_filled (win->ctx,wid->x, wid->y, wid->width, wid->height, LIGHTSILVER);
		acrylic_draw_rect_unfilled (win->ctx,wid->x,  wid->y, wid->width, wid->height, GRAY);

		///!Progress
		if (slider->progress != 0) {
			/*acrylic_draw_rect_filled (win->ctx,wid->x + 1,wid->y + slider->progress,
			9,(wid->y + wid->height) - (wid->y + slider->progress),DESKBLUE );*/
			linear_gradient (win->ctx,wid->x + 1,  wid->y + slider->progress,9,
				( wid->y + wid->height) - (wid->y + slider->progress), 
				0xFF84898C, 0xFF4D555A);
		}

		///!Slider Thumb
		acrylic_draw_rect_filled (win->ctx,wid->x,   //X
			wid->y + slider->thumb_y  /*+ wid->height - 15*/,               //Y
			wid->width, 15,LIGHTBLACK);
		acrylic_draw_rect_unfilled (win->ctx,wid->x,   //X
			wid->y +slider->thumb_y /*+ wid->height - 15*/,               //Y
			wid->width, 15,GRAY);
	}


	//* The Horizontal Slider *//
	if (slider->type == DAISY_SLIDER_HORIZONTAL) {
		acrylic_draw_rect_filled (win->ctx,wid->x, wid->y, wid->width, wid->height, LIGHTSILVER);
		//acrylic_draw_rect_filled (win->ctx, wid->x,  wid->y, wid->width, wid->height, LIGHTSILVER);
		acrylic_draw_rect_unfilled (win->ctx,wid->x, wid->y, wid->width, wid->height, GRAY);

		///!Progress
		if (slider->progress != 0){
			/*acrylic_draw_rect_filled (win->ctx,wid->x,wid->y + 1,
			(wid->x + slider->progress) - (wid->x),9, DESKBLUE );*/
			linear_gradient (win->ctx,wid->x, wid->y + 1,(wid->x + slider->progress) - ( wid->x),
				9,0xFF84898C, 0xFF4D555A);

		}

		///!Slider Thumb
		acrylic_draw_rect_filled (win->ctx,wid->x + slider->thumb_x,   //X
			 wid->y  /*+ wid->height - 15*/,               //Y
			15, wid->height,LIGHTBLACK);
		acrylic_draw_rect_unfilled (win->ctx,wid->x + slider->thumb_x,   //X
			wid->y/*+ wid->height - 15*/,               //Y
			15, wid->height,GRAY);
	}
}


/**
 * daisy_slider_mouse_event -- slider event handler
 * @param widget -- pointer to self
 * @param win -- pointer to root window
 * @param button -- mouse button code
 * @param clicked -- boolean value for clicked/not clicked
 * @param x -- mouse x coordinate
 * @param y -- mouse y coordinate
 */
void daisy_slider_mouse_event (daisy_widget_t *wid, daisy_window_t *win, int button, bool clicked, int x, int y) {
	daisy_win_info_t *info = daisy_get_window_info(win);
	daisy_widget_slider_t *slider = (daisy_widget_slider_t*)wid;

	if (button) {
		win->focused_widget = wid;
		/* for vertical everything is upside down */
		if (slider->type == DAISY_SLIDER_VERTICAL) {
			slider->thumb_y = y - (info->y + wid->y + 15 / 2);
			slider->progress = slider->thumb_y;

			//! Update the current values
			if (slider->thumb_y < slider->last_thumb_y){
				slider->c_val += slider->unit;
				if (slider->c_val == slider->max)
					slider->c_val = slider->max;
			}else if (slider->last_thumb_y < slider->thumb_y) {
				slider->c_val -= slider->unit;
				if (slider->c_val == slider->min)
						slider->c_val = slider->min;
			}


			if ((info->y + wid->y + slider->thumb_y) <= (info->y + wid->y)){
				slider->thumb_y = 0;
			}

			if ((info->y + wid->y + slider->thumb_y + 15) >= (info->y + wid->y + wid->height)){
				slider->thumb_y = (info->y + wid->y + wid->height) - (info->y + wid->y + 15);
				slider->progress = 0;
			}

			slider->last_thumb_y = slider->thumb_y;
			daisy_slider_refresh(wid, win);
			daisy_window_update_rect_area(win,slider->base.x,slider->base.y, slider->base.width, slider->base.height);
		}

		/* normal horizontal slider */
		if (slider->type == DAISY_SLIDER_HORIZONTAL) {
			slider->thumb_x = x - (info->x + wid->x + 15 / 2);
			slider->progress = slider->thumb_x;

			/**
			 *  Update the current values
			 */
			if (slider->thumb_x > slider->last_thumb_x) {
				slider->c_val += slider->unit;
				if (slider->c_val == slider->max)
					slider->c_val = slider->max;
			}else if (slider->last_thumb_x > slider->thumb_x) {
				slider->c_val -= slider->unit;
				if (slider->c_val == slider->min)
					slider->c_val = slider->min;
			}

			//! Limit the slider's thumb here
			if ((info->x + wid->x + slider->thumb_x) <= (info->x + wid->x)){
				slider->thumb_x = 0;
				slider->progress = 0;
			}

			if ((info->x + wid->x + slider->thumb_x + 15) >= (info->x + wid->x + wid->width)) {
				slider->thumb_x = (info->x + wid->x + wid->width) - (info->x + wid->x + 15);
			}

			//! update the last thum pos
			slider->last_thumb_x = slider->thumb_x;
			//! Refresh
			daisy_slider_refresh(wid, win);
			daisy_window_update_rect_area(win,slider->base.x,slider->base.y, slider->base.width, slider->base.height);
		}
	}
}


void daisy_widget_slider_destroy (daisy_widget_t *widget) {
	daisy_widget_slider_t *slider = (daisy_widget_slider_t*)widget;
	free(slider);
}


/**
 * daisy_widget_create_slider -- creates a slider widget
 * @param slider_type -- type of the slider (DAISY_SLIDER_HORIZONTAL, 
 * DAISY_SLIDER_VERTICAL)
 */
daisy_widget_slider_t *daisy_widget_create_slider (int slider_type) {
	daisy_widget_slider_t *slider = (daisy_widget_slider_t*)malloc(sizeof(daisy_widget_slider_t));
	slider->base.x = 0;
	slider->base.y = 23;
	slider->base.width = 0;
	slider->base.height = 0;
	slider->thumb_x = 0;
	slider->thumb_y = 0;
	slider->base.mouse_event = daisy_slider_mouse_event;
	slider->base.key_event = 0;
	slider->base.action_event = 0;
	slider->base.refresh = daisy_slider_refresh;
	slider->base.scroll_event = 0;
	slider->base.destroy = daisy_widget_slider_destroy;
	slider->max = 0;
	slider->min = 0;
	slider->progress = 0;
	slider->type = slider_type;
	slider->c_val = 0;
	slider->unit = 0;
	slider->last_thumb_x = 0;
	slider->last_thumb_y = 0;
	return slider;
}


/**
 * daisy_widget_slider_set_dimension -- set slider object dimension
 * @param slider -- pointer to the self
 * @param x -- X coordinate of the slider
 * @param y -- Y coordinate of the slider
 * @param w -- Width of the slider
 * @param h -- Height of the slider
 */
void daisy_widget_slider_set_dimension (daisy_widget_slider_t *slider, int x, int y, int length) {
	if (slider->type == DAISY_SLIDER_VERTICAL) {
		slider->base.x = x;
		slider->base.y = y;
		slider->base.width = 10;
		slider->base.height = length;
		slider->thumb_y = slider->base.height - 15;
	}else if (slider->type == DAISY_SLIDER_HORIZONTAL) {
		slider->base.x = x;
		slider->base.y = y;
		slider->base.width = length;
		slider->base.height = 10;
		slider->thumb_x = 0;
	}
}