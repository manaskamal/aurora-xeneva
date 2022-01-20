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
 * @daisy_window.h -- daisy window object
 *
 **/

#ifndef __DAISY_WINDOW_H__
#define __DAISY_WINDOW_H__

#include "daisy.h"
#include "daisy_widget.h"
#include "list.h"
#include <canvas.h>


typedef struct _pri_rect_ {
	int x;
	int y;
	int w;
	int h;
}pri_rect_t;

typedef struct _daisy_win_ {
	uint8_t attribute;
	uint32_t *backing_store;
	uint32_t *shared_win;
	canvas_t *ctx; 
	int mouse_button_last;
	char *title;
	list_t *widgets;
	void (*paint) (_daisy_win_ *win);
}daisy_window_t;

typedef struct _daisy_win_info_ {
	pri_rect_t rect[256];
	int rect_count;
	bool dirty;
	int x;
	int y;
	int width;
	int height;
}daisy_win_info_t;


/**
 * daisy_window_create -- create a new daisy window
 * @param x -- x coordinate
 * @param y -- y coordinate
 * @param w -- width of the window
 * @param h -- height of the window
 * @param attribute -- attributes of the window
 */
extern daisy_window_t* daisy_window_create (int x, int y, int w, int h, uint8_t attribute);

/**
 * daisy_get_window_info -- get windows informations
 * @param win -- desired window
 */
extern daisy_win_info_t * daisy_get_window_info (daisy_window_t* win);

/**
 * daisy_window_move -- move the window to a new location
 * @param x -- new x location
 * @param y -- new y location
 */
extern void daisy_window_move (int x, int y);

/**
 * daisy_window_service_event -- services system messages
 * @param e -- event message
 */
extern void daisy_window_service_event (daisy_window_t *win,pri_event_t *e);

/**
 * daisy_window_update -- updates the content of double buffered canvas to 
 * real window framebuffer (backing store)
 * @param win -- window to update
 * @param x -- x coordinate
 * @param y -- y coordinate
 * @param w -- width of the bound box to use for update
 * @param h -- height of the bound box to use for update
 */
extern void daisy_window_update (daisy_window_t *win,int x, int y, int w, int h);

/**
 * daisy_window_show -- make the final window visible
 * @param win -- window to make visible
 */
extern void daisy_window_show (daisy_window_t *win);

/**
 * daisy_window_set_title -- set a suitable title to the window
 * @param win -- reference window
 * @param title -- title to use
 */
extern void daisy_window_set_title (daisy_window_t *win,char* title);

/**
 * daisy_window_add_widget -- add a widget to daisy window
 * @param win -- reference window
 * @param widget -- widget to add
 */
extern void daisy_window_add_widget (daisy_window_t *win,daisy_widget_t *widget);

#endif