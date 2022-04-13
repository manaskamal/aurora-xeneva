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

#include "daisy_scroll_view.h"
#include "daisy_widget_scrollbar.h"
#include <stdint.h>
#include <stdlib.h>
#include <acrylic.h>
#include <canvas.h>
#include <font.h>
#include <color.h>

#include <sys/_term.h>

/**
 * daisy_sv_refresh -- scroll view refresh handler
 * @param widget -- pointer to self
 * @param win -- pointer to root window
 */
void daisy_sv_refresh (daisy_widget_t *widget, daisy_window_t* win)  {
	daisy_scroll_view_t *sv = (daisy_scroll_view_t*)widget;
	acrylic_draw_rect_unfilled(win->ctx,sv->base.x, sv->base.y, sv->base.width, sv->base.height,GRAY);

	acrylic_draw_rect_filled(win->ctx,widget->x, widget->y, widget->width- 15, widget->height - 15, LIGHTSILVER);
	int sc_y = widget->y;
	/*if (sv->num_scroll_lines > 0) {
		for (int i = sv->current_scroll_line; i < sv->num_scroll_lines;  i++) {
			acrylic_draw_rect_unfilled(win->ctx,widget->x,sc_y,widget->width,15,GRAY);
			sc_y += 15;
		}
	}*/

	if (sv->scrollable_widget) {
		if (sv->scrollable_widget->refresh) {
			sv->scrollable_widget->refresh(sv->scrollable_widget,win);
		}
	}
}

/**
 * daisy_sv_mouse_event -- scroll view mouse handler
 * @param widget -- pointer to self
 * @param win -- pointer to root window
 * @param button -- mouse button code
 * @param clicked -- boolean value for clicked/not clicked
 * @param x -- mouse x coordinate
 * @param y -- mouse y coordinate
 */
void daisy_sv_mouse_event (daisy_widget_t *widget, daisy_window_t *win, int button, bool clicked, int x, int y) {
	daisy_scroll_view_t *sv = (daisy_scroll_view_t*)widget;
	if (sv->scrollable_widget) {
		if (sv->scrollable_widget->mouse_event) {
			sv->scrollable_widget->mouse_event(sv->scrollable_widget,win,button,button,x, y);
		}
	}
}

/**
 * daisy_sv_scroll_event -- scroll view scroll event handler
 * @param widget -- pointer to self
 * @param scrollbar -- pointer to scrollbar
 * @param win -- pointer to root window
 */
void daisy_sv_scroll_event (daisy_widget_t *widget, daisy_widget_t* scrollbar, daisy_window_t * win) {
	daisy_widget_scrollbar_t *scroll = (daisy_widget_scrollbar_t*)scrollbar;
	daisy_scroll_view_t *sv = (daisy_scroll_view_t*)widget;


	if (scroll->type == DAISY_SCROLLBAR_VERTICAL) {
		if ((sv->scroll_num_rows * sv->scroll_row_height) < sv->base.height)
			return;

		sv->scroll_current_row = scroll->scroll_yoff;

		daisy_sv_refresh(widget,win);

		if (sv->scrollable_widget) {
			if(sv->scrollable_widget->scroll_event) {
				sv->scrollable_widget->scroll_event(sv->scrollable_widget,(daisy_widget_t*)sv,win);
			}
		}
		daisy_window_update_rect_area(win,sv->base.x, sv->base.y, sv->base.width, sv->base.height);
	} 

	if (scroll->type == DAISY_SCROLLBAR_HORIZONTAL) {
		sv->scroll_current_col = scroll->scroll_xoff;
	}
}


void daisy_sv_destroy (daisy_widget_t* widget) {
	daisy_scroll_view_t *sv = (daisy_scroll_view_t*)widget;
	free(sv);
}

/**
 * daisy_widget_create_scroll_view -- creates new scroll view
 * @return scroll -- scroll view created
 */
daisy_scroll_view_t * daisy_widget_create_scroll_view () {
	daisy_scroll_view_t *scroll = (daisy_scroll_view_t*)malloc(sizeof(daisy_scroll_view_t));
	scroll->base.width = 200;
	scroll->base.height = 200;
	scroll->base.key_event = 0;
	scroll->base.mouse_event = daisy_sv_mouse_event;
	scroll->base.refresh = daisy_sv_refresh;
	scroll->base.scroll_event = daisy_sv_scroll_event;
	scroll->base.destroy = daisy_sv_destroy;
	scroll->base.x = 0;
	scroll->base.y = 23;
	scroll->base.action_event = 0;
	scroll->scroll_num_rows = 0;
	scroll->scroll_row_height = 0;
	scroll->scroll_content_height = 0;
	scroll->scroll_content_width = 0;
	scroll->scrollable_widget = 0;
	scroll->attached_scrollbar_h = 0;
	scroll->attached_scrollbar_v = 0;
	return scroll;
}

/**
 * daisy_sv_set_dimension -- sets scroll view dimension
 * @param view -- pointer to the scrollview
 * @param x -- Scroll View x position
 * @param y -- Scroll View y position
 * @param w -- Scroll View width
 * @param h -- Scroll View height
 */
void daisy_sv_set_dimension (daisy_scroll_view_t *view, int x, int y, int w, int h) {
	view->base.x = x;
	view->base.y = y;
	view->base.width = w;
	view->base.height = h;
}


void daisy_sv_update_scroll(daisy_scroll_view_t *view, daisy_window_t *win,bool repaint) {
	if (view->attached_scrollbar_h) {
		daisy_widget_scrollbar_update_scroll((daisy_widget_scrollbar_t*)view->attached_scrollbar_h,view);
		if (repaint) {
			if (view->attached_scrollbar_h->refresh) {
				view->attached_scrollbar_h->refresh(view->attached_scrollbar_h, win);
			}
		}
	}

	if (view->attached_scrollbar_v) {
		daisy_widget_scrollbar_update_scroll((daisy_widget_scrollbar_t*)view->attached_scrollbar_v,view);
		if (repaint) {
			if (view->attached_scrollbar_v->refresh) {
				view->attached_scrollbar_v->refresh(view->attached_scrollbar_v, win);
			}
		}
	}

}

/**
 * daisy_sv_add_component -- adds a scrollable component to scroll view
 * @param view -- scrollview
 * @param scrollable_component -- scrollable widget
 */
void daisy_sv_add_component (daisy_scroll_view_t *view, daisy_widget_t* scrollable_component) {
	view->scrollable_widget = scrollable_component;
}

