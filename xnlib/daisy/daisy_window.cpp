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
#include <stdlib.h>
#include <sys/_sleep.h>
#include <sys/_term.h>

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

