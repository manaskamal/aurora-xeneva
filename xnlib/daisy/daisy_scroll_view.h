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
 * @daisy_scroll_view -- daisy scrollable view
 *
 **/

#ifndef __DAISY_SCROLL_VIEW_H__
#define __DAISY_SCROLL_VIEW_H__

#include "daisy.h"
#include "daisy_widget.h"
#include "daisy_window.h"

typedef struct _daisy_scroll_view__ {
	daisy_widget_t base;
	int scroll_row_height;
	int scroll_num_rows;
	int scroll_content_height;
	int scroll_content_width;
	int scroll_current_row;
	int scroll_current_col;
	daisy_widget_t *scrollable_widget;
	daisy_widget_t* attached_scrollbar_h;
	daisy_widget_t* attached_scrollbar_v;
}daisy_scroll_view_t;


/**
 * daisy_widget_create_scroll_view -- creates new scroll view
 * @return scroll -- scroll view created
 */
extern daisy_scroll_view_t * daisy_widget_create_scroll_view ();

/**
 * daisy_sv_set_dimension -- sets scroll view dimension
 * @param view -- pointer to the scrollview
 * @param x -- Scroll View x position
 * @param y -- Scroll View y position
 * @param w -- Scroll View width
 * @param h -- Scroll View height
 */
extern void daisy_sv_set_dimension (daisy_scroll_view_t *view, int x, int y, int w, int h);

/**
 * daisy_sv_add_component -- adds a scrollable component to scroll view
 * @param view -- scrollview
 * @param scrollable_component -- scrollable widget
 */
extern void daisy_sv_add_component (daisy_scroll_view_t *view, daisy_widget_t* scrollable_component);

extern void daisy_sv_update_scroll(daisy_scroll_view_t *view, daisy_window_t* win,bool repaint);

#endif