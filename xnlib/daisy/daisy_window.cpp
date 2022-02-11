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
 * @daisy_window.cpp -- daisy window object
 *
 **/

#include "daisy_window.h"
#include "daisy_priwm_window.h"
#include "daisy_window_painter.h"
#include "daisy_widget.h"
#include <stdlib.h>
#include <sys/_sleep.h>
#include <sys/_term.h>
#include <fastcpy.h>

/**
 * daisy_window_create -- create a new daisy window
 * @param x -- x coordinate
 * @param y -- y coordinate
 * @param w -- width of the window
 * @param h -- height of the window
 * @param attribute -- attributes of the window
 */
daisy_window_t* daisy_window_create (int x, int y, int w, int h, uint8_t attribute) {
	daisy_window_t *win = (daisy_window_t*)malloc(sizeof(daisy_window_t));
	_daisy_priwm_create_window_ (x, y, w, h, attribute);
	win->ctx = create_canvas (w, h);
	win->attribute = attribute;
	win->mouse_button_last = 0;
	while(1) {
		pri_event_t *e = daisy_get_gifts();
		if (e != NULL) {
			if (e->type == DAISY_GIFT_CANVAS) {
				win->backing_store = e->p_value;
				win->shared_win = e->p_value2;
				break;
			}
		}
	}

	win->paint = daisy_window_paint;
	win->title = NULL;
	win->widgets = list_init();
	return win;
}

/**
 * daisy_get_window_info -- get windows informations
 * @param win -- desired window
 */
daisy_win_info_t * daisy_get_window_info (daisy_window_t* win) {
	daisy_win_info_t *info = (daisy_win_info_t*)win->shared_win;
	return info;
}


/**
 * daisy_window_move -- move the window to a new location
 * @param x -- new x location
 * @param y -- new y location
 */
void daisy_window_move (int x, int y) {
	_daisy_priwm_window_move_(x, y);
}

/**
 * daisy_window_handle_mouse -- handles mouse events within the
 * window
 * @param x -- mouse_x coordinate
 * @param y -- mouse_y coordinate
 * @param button -- button bit
 */
void daisy_window_handle_mouse (daisy_window_t *win,int x, int y, int button) {
	daisy_win_info_t *info = daisy_get_window_info(win);

	/**  loop through all widgets and check there
	 **  bounds with current mouse location if they intersect **/
	for (int i = 0; i < win->widgets->pointer; i++) {
		daisy_widget_t *widget = (daisy_widget_t*)list_get_at(win->widgets,i);
		if (x > info->x + widget->x && x < (info->x + widget->x + widget->width) &&
			y > info->y + widget->y && y < (info->y + widget->y + widget->height)) {
				if (widget->mouse_event)
					widget->mouse_event(widget,win,button,button,x,y);
		}
	}
}
/**
 * daisy_window_service_event -- services system messages
 * @param e -- event message
 */
void daisy_window_service_event (daisy_window_t *win,pri_event_t *e){
	if (e != NULL) {
		if (e->type == DAISY_CURSOR_MOVED) {
			daisy_window_handle_mouse(win,e->dword, e->dword2, e->dword3);
			free(e);
		}
	}
}


/**
 * daisy_window_update -- updates the content of double buffered canvas to 
 * real window framebuffer (backing store)
 * @param win -- window to update
 * @param x -- x coordinate
 * @param y -- y coordinate
 * @param w -- width of the bound box to use for update
 * @param h -- height of the bound box to use for update
 */
void daisy_window_update (daisy_window_t *win,int x, int y, int w, int h) {
	uint32_t* lfb = win->backing_store;
	uint32_t* dbl_canvas = win->ctx->address;   
	int width = canvas_get_width(win->ctx);
	int height = canvas_get_height(win->ctx);

	for (int i = 0; i < h; i++)
		fastcpy (lfb + (y + i) * width + x,dbl_canvas + (y + i) * width + x, w * 4);
}


/**
 * daisy_window_show -- make the final window visible
 * @param win -- window to make visible
 */
void daisy_window_show (daisy_window_t *win) {
	daisy_win_info_t *info = daisy_get_window_info(win);
	win->paint(win);
	daisy_window_update (win, 0,0,info->width, info->height);
}

/**
 * daisy_window_set_title -- set a suitable title to the window
 * @param win -- reference window
 * @param title -- title to use
 */
void daisy_window_set_title (daisy_window_t *win,char* title) {
	win->title = title;
}

/**
 * daisy_window_add_widget -- add a widget to daisy window
 * @param win -- reference window
 * @param widget -- widget to add
 */
void daisy_window_add_widget (daisy_window_t *win,daisy_widget_t *widget) {
	list_add (win->widgets,widget);
}

