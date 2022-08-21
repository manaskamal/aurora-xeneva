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

#ifndef __PRI_RECT_H__
#define __PRI_RECT_H__

#include "priwm.h"

/*
 * pri_rect_set_left -- set a new left edge value to 
 * the given rect
 * @param rect -- pointer to the rect structure
 * @param new_left -- new left edge value
 */
extern int pri_rect_set_left (pri_rect_t* rect, int new_left);

/*
 * pri_rect_set_right -- sets a new right edge value to
 * the given rect
 * @param rect -- pointer to the rect structure
 * @param new_right -- new right value
 */
extern int pri_rect_set_right (pri_rect_t * rect, int new_right);

/*
 * pri_rect_set_top -- set a new top edge value to the given
 * rectangle
 * @param rect -- pointer to the rect structure
 * @param new_top -- top edge value
 */
extern int pri_rect_set_top (pri_rect_t *rect, int new_top);

/*
 * pri_rect_set_bottom -- set a new bottom edge value to the given
 * rectangle
 * @param rect -- pointer to the rect structure
 * @param new_bottom -- new bottom edge value 
 */
extern int pri_rect_set_bottom (pri_rect_t *rect, int new_bottom);

/*
 * pri_rect_get_left -- returns the left edge value
 * @param rect -- pointer to the rect structure
 */
extern int pri_rect_get_left (pri_rect_t *rect);

/*
 * pri_rect_get_right -- returns the right edge value
 * @param rect -- pointer to the rect structure
 */
extern int pri_rect_get_right (pri_rect_t *rect);

/*
 * pri_rect_get_top -- returns the top edge value
 * @param rect -- pointer to the rect structure
 */
extern int pri_rect_get_top (pri_rect_t *rect);

/*
 * pri_rect_get_bottom -- returns the bottom edge value
 * @param rect -- pointer to the rect structure
 */
extern int pri_rect_get_bottom (pri_rect_t *rect);


#endif