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
 * @daisy_widgets.h -- daisy widget object
 *
 **/

#ifndef __DAISY_WIDGET_H__
#define __DAISY_WIDGET_H__

#include <stdint.h>
#include "daisy.h"

struct _daisy_win_;

/**
 * daisy_widget_t -- daisy widget structure 
 */
typedef struct _daisy_widget_ {
	int x;
	int y;
	int width;
	int height;
	void (*refresh) (struct _daisy_widget_ *, _daisy_win_* win);
	void (*mouse_event) (struct _daisy_widget_*, _daisy_win_* win, int button,bool clicked, int x, int y);
	void (*key_event) (struct _daisy_widget_*, _daisy_win_ *win, int button);
	void (*action_event) (struct _daisy_widget_*,_daisy_win_* win);
	void (*scroll_event) (struct _daisy_widget_*, struct _daisy_widget_*, _daisy_win_* win);
	void (*destroy) (struct _daisy_widget_*);
}daisy_widget_t;

#endif