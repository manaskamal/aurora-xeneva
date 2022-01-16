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
 * @pri_dirty_clip -- priyanshi's dirty clip manager
 *
 **/

#ifndef __PRI_DIRTY_CLIP_H__
#define __PRI_DIRTY_CLIP_H__

#include "priwm.h"

typedef struct _pri_dirty_clip_ {
	pri_rect_t *rect;
	_pri_dirty_clip_ *link;
}pri_dirty_clip_t;

/**
 * pri_add_dirty_clip -- adds a dirty clip rect
 * @param r -- rect to add
 */
extern void pri_add_dirty_clip (pri_rect_t *r);

/**
 * pri_get_dirty_rect -- pops a dirty rect from 
 * the list
 * @return -- dirty rectangle
 */
extern pri_rect_t * pri_get_dirty_rect();

/**
 * pri_get_dirty_count -- get total dirty area
 * count
 * @return -- dirty area count
 */
extern uint32_t pri_get_dirty_count();
#endif