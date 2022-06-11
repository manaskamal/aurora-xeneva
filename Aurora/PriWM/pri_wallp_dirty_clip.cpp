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
 * @pri_wallp_dirty_clip.cpp -- pri wallpaper dirty clip rect manager
 *
 **/

#include "pri_wallp_dirty_clip.h"
#include <stdlib.h>

pri_wallp_dirty_clip_t *_wallp_top = NULL;
static uint32_t _wallp_dirty_count = 0;

pri_rect_t wallp_dirty_rect[256];

/**
 * pri_wallp_add_dirty_clip -- adds a dirty clip rect
 * @param r -- rect to add
 */
void pri_wallp_add_dirty_clip (int x, int y, int w, int h) {
	wallp_dirty_rect[_wallp_dirty_count].x = x;
	wallp_dirty_rect[_wallp_dirty_count].y = y;
	wallp_dirty_rect[_wallp_dirty_count].w = w;
	wallp_dirty_rect[_wallp_dirty_count].h = h;
	_wallp_dirty_count++;
}

/**
 * pri_wallp_get_dirty_rect -- pops a dirty rect from 
 * the list
 * @return -- dirty rectangle
 */
void pri_wallp_get_dirty_rect(int *x, int *y, int *w, int *h, int index) {
	*x = wallp_dirty_rect[index].x;
	*y = wallp_dirty_rect[index].y;
	*w = wallp_dirty_rect[index].w;
	*h = wallp_dirty_rect[index].h;
}

/**
 * pri_wallp_get_dirty_count -- get total dirty area
 * count
 * @return -- dirty area count
 */
uint32_t pri_wallp_get_dirty_count() {
	return _wallp_dirty_count;
}


void pri_wallp_dirty_count_reset() {
	_wallp_dirty_count = 0;
}
