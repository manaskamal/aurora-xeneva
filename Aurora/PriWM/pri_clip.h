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
 * @priwm.h -- pri_window manager
 *
 **/

#ifndef __PRI_CLIP_H__
#define __PRI_CLIP_H__

/* Pri Clip -- Clip Manager */

#include "priwm.h"


/* Check if two rectangle intersects
 * @param r1 -- rectangle one
 * @param r2 -- rectangle two
 */
extern bool pri_check_intersect (pri_rect_t *r1, pri_rect_t *r2);

/*
 * pri_calculate_clip_rects -- calculate visible rectanlges of current window
 * @param sub_rect -- subject rectangle
 * @param cut_rect -- cutting rectangle
 * @param list -- pointer to the list, where to store all
 * visible rectangles
 * @param count -- number of rectangles stored in the list
 */
extern void pri_calculate_clip_rects (pri_rect_t *sub_rect, pri_rect_t* cut_rect, pri_rect_t *list, int *count);
#endif