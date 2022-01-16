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
#endif