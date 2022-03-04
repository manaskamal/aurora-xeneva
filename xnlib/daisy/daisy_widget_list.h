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
 * @daisy_widget_list -- daisy widget list
 *
 **/

#ifndef __DAISY_WIDGET_LIST_H__
#define __DAISY_WIDGET_LIST_H__

#include "daisy.h"
#include "daisy_widget.h"
#include "daisy_scroll_view.h"
#include "daisy_window.h"
#include "list.h"

typedef struct _daisy_widget_list_ {
	daisy_widget_t base;
	int num_list_items;
	list_t *elements;
	int current_line;
	int current_col;
	daisy_scroll_view_t *sv;
}daisy_widget_list_t;

typedef struct _daisy_widget_list_elements_ {
	char* item_title;
}daisy_widget_list_elements_t;

/**
 * daisy_widget_create_list -- creates a new list widget
 */
extern daisy_widget_list_t *daisy_widget_create_list (daisy_scroll_view_t *sv);

/**
 * daisy_widget_list_create_element -- create a new element for the list
 * @param title -- title of the element
 */
extern daisy_widget_list_elements_t * daisy_widget_list_create_element(char *title);


/**
 * daisy_widget_list_add_element -- adds a new element to the list
 * @param list -- pointer to the list, where to add
 * @param win -- pointer to the window
 * @param elem -- element to add
 */
extern void daisy_widget_list_add_element(daisy_widget_list_t *list,daisy_window_t *win, daisy_widget_list_elements_t *elem);

/**
 * daisy_widget_list_set_dimension -- sets a new dimension to the list widget
 * @param list -- pointer to the list needs modification
 * @param x -- X coord
 * @param y -- Y coord
 * @param w -- Width of the list
 * @param h -- Height of the list
 */
extern void daisy_widget_list_set_dimension (daisy_widget_list_t *list, int x, int y, int w, int h);
#endif