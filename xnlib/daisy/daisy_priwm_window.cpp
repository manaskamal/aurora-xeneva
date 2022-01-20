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
 * @daisy_priwm_window.h -- daisy priwm window manager
 *
 **/

#include "daisy_priwm_window.h"
#include "daisy.h"
#include <sys/_term.h>
#include <stdlib.h>

/**
 * _daisy_priwm_create_window_ -- creates a new window in server side
 * @param x -- x coordination
 * @param y -- y coordination
 * @param w -- width of the window
 * @param h -- height of the window
 * @param attribute -- window attributes
 */
void _daisy_priwm_create_window_ (int x, int y, int w, int h, uint8_t attribute) {
	pri_event_t e;
	e.type = PRI_WIN_CREATE;
	e.dword = x;
	e.dword2 = y;
	e.dword3 = w;
	e.dword4 = h;
	e.dword5 = attribute;
	priwm_send_event(&e);
}

/**
 * _daisy_priwm_window_move_ --moves a window to a new location
 * @param x -- x coordination
 * @param y -- y coordination
 */
void _daisy_priwm_window_move_ (int x, int y) {
	pri_event_t e;
	e.type = PRI_WIN_MOVE;
	e.dword = x;
	e.dword2 = y;
	priwm_send_event(&e);
}



