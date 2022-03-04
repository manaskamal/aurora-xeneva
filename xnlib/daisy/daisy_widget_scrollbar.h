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
 * @daisy_widget_scrollbar -- daisy widget scrollbar
 *
 **/

#ifndef __DAISY_WIDGET_SCROLLBAR_H__
#define __DAISY_WIDGET_SCROLLBAR_H__

#include <stdlib.h>
#include <stdint.h>
#include "daisy_widget.h"
#include "daisy_window.h"
#include "daisy_scroll_view.h"

#include <acrylic.h>
#include <color.h>

/* Scrollbar types */
#define DAISY_SCROLLBAR_HORIZONTAL  0x1
#define DAISY_SCROLLBAR_VERTICAL    0x2

/* Daisy Widget Scrollbar */
typedef struct _daisy_widget_scrollbar_ {
	daisy_widget_t base;
	int type;
	daisy_widget_t *scrollable_view;
	int thumb_x;
	int thumb_y;
	int thumb_sz;
	int max_thumb_sz;
	int scroll_xoff;
	int scroll_yoff;
	int max_scroll_limit;
	int min_scroll_limit;
}daisy_widget_scrollbar_t;


/**
 * daisy_widget_create_scrollbar -- creates a scrollbar for
 * a scrollable view
 * @param scroll_type -- type of the scrollbar {DAISY_SCROLLBAR_HORIZONTAL,
 * DAISY_SCROLLBAR_VERTICAL }
 */
extern daisy_widget_scrollbar_t *daisy_widget_create_scrollbar (int scroll_type);


/**
 * daisy_widget_scrollbar_add_view -- adds a scrollable view to the window
 * @param scrollbar -- pointer to scrollbar where view will be added
 * @param sv -- pointer to scrollable view
 */
extern void daisy_widget_scrollbar_add_view (daisy_widget_scrollbar_t *scrollbar,daisy_scroll_view_t *sv);

/**
 * daisy_widget_scrollbar_update_scroll -- updates the scroll thumbs  according to
 * views number of lines/column
 * @param scrollbar -- current scrollbar to update
 * @param sv -- current scrollview to use as reference
 */
extern void daisy_widget_scrollbar_update_scroll (daisy_widget_scrollbar_t *scrollbar, daisy_scroll_view_t* sv);

#endif