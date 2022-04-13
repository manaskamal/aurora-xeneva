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

#include "daisy_widget_list.h"
#include "daisy_widget_scrollbar.h"
#include <stdlib.h>
#include <acrylic.h>
#include <color.h>
#include <font.h>

#include <sys/_term.h>
/**
 * daisy_list_refresh -- list refresh handler
 * @param widget -- pointer to self
 * @param win -- pointer to root window
 */
void daisy_list_refresh (daisy_widget_t *widget, daisy_window_t* win){
	daisy_widget_list_t *list = (daisy_widget_list_t*)widget;
	acrylic_draw_rect_filled (win->ctx, widget->x, widget->y, widget->width, widget->height, WHITE);
	acrylic_draw_rect_unfilled(win->ctx, widget->x, widget->y, widget->width, widget->height,GRAY);
	if (list->num_list_items > 0) {
		acrylic_font_set_size(10);
		int elem_y = widget->y;
		if (list->current_line != list->elements->pointer) {
			for (int i = list->current_line; i < list->elements->pointer; i++) {
				daisy_widget_list_elements_t *elem = (daisy_widget_list_elements_t*)list_get_at(list->elements,i);
				int font_h = acrylic_font_get_height(elem->item_title);
				acrylic_font_draw_string(win->ctx,elem->item_title,widget->x,elem_y + 14,11,BLACK);
				elem_y += 15;
			}
		}
	}
			
}

/**
 * daisy_list_mouse_event -- list event handler
 * @param widget -- pointer to self
 * @param win -- pointer to root window
 * @param button -- mouse button code
 * @param clicked -- boolean value for clicked/not clicked
 * @param x -- mouse x coordinate
 * @param y -- mouse y coordinate
 */
void daisy_list_mouse_event (daisy_widget_t *widget, daisy_window_t *win, int button, bool clicked, int x, int y){
}

/**
 * daisy_list_scroll_event -- list scroll event handler
 * @param widget -- pointer to self
 * @param scrollbar -- pointer to scrollbar
 * @param win -- pointer to root window
 */
void daisy_list_scroll_event (daisy_widget_t *widget, daisy_widget_t* scrollview, daisy_window_t * win){
	daisy_widget_list_t *list = (daisy_widget_list_t*)widget;
	daisy_scroll_view_t *sv = (daisy_scroll_view_t*)scrollview;
	list->current_line = sv->scroll_current_row;

}


void daisy_list_destroy (daisy_widget_t *widget) {
	daisy_widget_list_t *list = (daisy_widget_list_t*)widget;
	free(list);
}

/**
 * daisy_widget_create_list -- creates a new list widget
 */
daisy_widget_list_t *daisy_widget_create_list (daisy_scroll_view_t *sv) {
	daisy_widget_list_t *list = (daisy_widget_list_t*)malloc(sizeof(daisy_widget_list_t));
	list->base.x = 0;
	list->base.y = 23;
	list->base.width = 0;
	list->base.height = 0;
	list->base.action_event = 0;
	list->base.key_event = 0;
	list->base.mouse_event = daisy_list_mouse_event;
	list->base.scroll_event = daisy_list_scroll_event;
	list->base.refresh = daisy_list_refresh;
	list->base.destroy = daisy_list_destroy;
	list->num_list_items = 0;
	list->sv = sv;
	list->elements = list_init();
	sv->scroll_row_height = 15;
	return list;
}

/**
 * daisy_widget_list_create_element -- create a new element for the list
 * @param title -- title of the element
 */
daisy_widget_list_elements_t * daisy_widget_list_create_element(char *title) {
	daisy_widget_list_elements_t *elem = (daisy_widget_list_elements_t*)malloc(sizeof(daisy_widget_list_elements_t));
	elem->item_title = title;
	return elem;
}

/**
 * daisy_widget_list_add_element -- adds a new element to the list
 * @param list -- pointer to the list, where to add
 * @param elem -- element to add
 */
void daisy_widget_list_add_element(daisy_widget_list_t *list, daisy_window_t* win, daisy_widget_list_elements_t *elem) {
	list_add(list->elements,elem);
	list->num_list_items += 1;
	list->sv->scroll_num_rows += 1;
	if(list->sv->attached_scrollbar_h) {
		daisy_widget_scrollbar_t* scrollbar = (daisy_widget_scrollbar_t*)list->sv->attached_scrollbar_h;
		scrollbar->max_scroll_limit += 1 * list->sv->scroll_row_height;
	}else {
		daisy_widget_scrollbar_t* scrollbar = (daisy_widget_scrollbar_t*)list->sv->attached_scrollbar_v;
		scrollbar->max_scroll_limit += 1;
	}
	daisy_sv_update_scroll(list->sv, win,false);
}

/**
 * daisy_widget_list_set_dimension -- sets a new dimension to the list widget
 * @param list -- pointer to the list needs modification
 * @param x -- X coord
 * @param y -- Y coord
 * @param w -- Width of the list
 * @param h -- Height of the list
 */
void daisy_widget_list_set_dimension (daisy_widget_list_t *list, int x, int y, int w, int h) {
	list->base.x = x;
	list->base.y = y;
	list->base.width = w;
	list->base.height = h;
}
