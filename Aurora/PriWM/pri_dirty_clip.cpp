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
 * @pri_dirty_clip.cpp -- pri dirty clip rect manager
 *
 **/

#include "pri_dirty_clip.h"
#include <sys\_term.h>
#include <canvas.h>
#include <stdlib.h>

pri_dirty_clip_t *_top = NULL;
static uint32_t _dirty_count = 0;
pri_rect_t dirty_rect[512];


/**
 * pri_add_dirty_clip -- adds a dirty clip rect
 * @param r -- rect to add
 */
void pri_add_dirty_clip (int x, int y, int w, int h) {
	dirty_rect[_dirty_count].x = x;
	dirty_rect[_dirty_count].y = y;
	dirty_rect[_dirty_count].w = w;
	dirty_rect[_dirty_count].h = h;
	_dirty_count++;
}

/**
 * pri_dirty_rect_screen_update -- update every dirty areas
 * @param canvas -- offscreen canvas
 */
void  pri_dirty_rect_screen_update(canvas_t *canvas) {
	for (int i = 0; i < _dirty_count; i++) {
		canvas_screen_update(canvas, dirty_rect[i].x, dirty_rect[i].y, dirty_rect[i].w, dirty_rect[i].h);
	}
	
	_dirty_count = 0;
}

/**
 * pri_get_dirty_count -- get total dirty area
 * count
 * @return -- dirty area count
 */
uint32_t pri_get_dirty_count() {
	return _dirty_count;
}
