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

#include "daisy_widget_scrollbar.h"
#include "daisy_scroll_view.h"
#include <sys/_term.h>
#include <math.h>

/**
 * daisy_scrollbar_refresh -- scrollbar refresh handler
 * @param widget -- pointer to self
 * @param win -- pointer to root window
 */
void daisy_scrollbar_refresh (daisy_widget_t *widget, daisy_window_t* win) {
	daisy_widget_scrollbar_t *scrollbar = (daisy_widget_scrollbar_t*)widget;
	acrylic_draw_rect_unfilled(win->ctx,scrollbar->base.x, scrollbar->base.y, scrollbar->base.width, scrollbar->base.height,
		LIGHTBLACK);

	if (scrollbar->type == DAISY_SCROLLBAR_VERTICAL) {

		acrylic_draw_rect_filled(win->ctx,scrollbar->base.x, scrollbar->base.y, scrollbar->base.width, scrollbar->base.height,
			LIGHTSILVER);
		acrylic_draw_rect_unfilled(win->ctx,scrollbar->base.x, scrollbar->base.y, scrollbar->base.width, scrollbar->base.height,
		LIGHTBLACK);

		if (scrollbar->thumb_y == 0)
			scrollbar->thumb_y = 2;

		acrylic_draw_rect_filled (win->ctx,widget->x + 2,
			widget->y + scrollbar->thumb_y,	widget->width - 4,
			scrollbar->thumb_sz,GRAY); 

	} else if (scrollbar->type == DAISY_SCROLLBAR_HORIZONTAL) {

		acrylic_draw_rect_filled(win->ctx,scrollbar->base.x, scrollbar->base.y, scrollbar->base.width, scrollbar->base.height,
			LIGHTSILVER);

		acrylic_draw_rect_unfilled(win->ctx,scrollbar->base.x, scrollbar->base.y, scrollbar->base.width, scrollbar->base.height,
		LIGHTBLACK);

		if (scrollbar->thumb_x == 0)
			scrollbar->thumb_x = 2;

		acrylic_draw_rect_filled (win->ctx, widget->x + scrollbar->thumb_x,
			widget->y + 2, scrollbar->thumb_sz,widget->height - 4,GRAY);
	}
}

/**
 * daisy_scrollbar_mouse_event -- scrollbar event handler
 * @param widget -- pointer to self
 * @param win -- pointer to root window
 * @param button -- mouse button code
 * @param clicked -- boolean value for clicked/not clicked
 * @param x -- mouse x coordinate
 * @param y -- mouse y coordinate
 */
void daisy_scrollbar_mouse_event (daisy_widget_t *widget, daisy_window_t *win, int button, bool clicked, int x, int y){
	daisy_widget_scrollbar_t *scroll = (daisy_widget_scrollbar_t*)widget;
	daisy_win_info_t *info = daisy_get_window_info(win);

	if (button) {
		if (scroll->type == DAISY_SCROLLBAR_HORIZONTAL) {
			scroll->thumb_x = x - (info->x + widget->x + scroll->thumb_sz / 2);
			scroll->scroll_xoff = scroll->thumb_x;
			win->focused_widget = (daisy_widget_t*)scroll;
		}

		if (scroll->type == DAISY_SCROLLBAR_VERTICAL) {
			scroll->thumb_y = y - (info->y + widget->y + scroll->thumb_sz / 2);
			scroll->scroll_yoff = scroll->thumb_y;
			win->focused_widget = (daisy_widget_t*)scroll;
		}
	}

	if (win->focused_widget == (daisy_widget_t*)scroll) {
		if (scroll->type == DAISY_SCROLLBAR_HORIZONTAL) {
			if (info->x + widget->x + scroll->thumb_x + scroll->thumb_sz >= info->x + widget->width) {
				scroll->thumb_x = (info->x + widget->x + widget->width) - (info->x + widget->x + scroll->thumb_sz) - 2;
				scroll->scroll_xoff = scroll->thumb_x + 2;
			}

			if ((info->x + widget->x + scroll->thumb_x) < info->x + widget->x) {
				scroll->thumb_x = 2;
				scroll->scroll_xoff = 0;
			}

			if (scroll->scrollable_view)  {
				if (scroll->scrollable_view->scroll_event) 
					scroll->scrollable_view->scroll_event(scroll->scrollable_view,(daisy_widget_t*)scroll,win);
			}

			daisy_scrollbar_refresh(widget,win);
			daisy_window_update_rect_area(win,widget->x, widget->y, widget->width, 15);
		}

		if (scroll->type == DAISY_SCROLLBAR_VERTICAL) {
			if ((info->y + widget->y + scroll->thumb_y + scroll->thumb_sz) >= (info->y + widget->y + widget->height)) {
				scroll->thumb_y = (info->y + widget->y + widget->height) - (info->y + widget->y + scroll->thumb_sz) - 2;
				scroll->scroll_yoff = scroll->thumb_y + 2;
			}

			if ((info->y + widget->y + scroll->thumb_y) <= (info->y + widget->y)) {
				scroll->thumb_y = 2;
				scroll->scroll_yoff = 0;
			}

			if (scroll->scrollable_view) 
				if (scroll->scrollable_view->scroll_event)
					scroll->scrollable_view->scroll_event(scroll->scrollable_view,(daisy_widget_t*)scroll,win);

			daisy_scrollbar_refresh (widget, win);
			daisy_window_update_rect_area(win,widget->x, widget->y, widget->width, widget->height);
		}
	}

}

/**
 * daisy_widget_create_scrollbar -- creates a scrollbar for
 * a scrollable view
 * @param scroll_type -- type of the scrollbar {DAISY_SCROLLBAR_HORIZONTAL,
 * DAISY_SCROLLBAR_VERTICAL }
 */
daisy_widget_scrollbar_t *daisy_widget_create_scrollbar (int scroll_type) {
	daisy_widget_scrollbar_t *scrollbar = (daisy_widget_scrollbar_t*)malloc(sizeof(daisy_widget_scrollbar_t));
	scrollbar->base.x = 0;
	scrollbar->base.y = 23;
	scrollbar->base.width = 0;
	scrollbar->base.height = 0;
	scrollbar->base.key_event = 0;
	scrollbar->base.action_event = 0;
	scrollbar->base.mouse_event = daisy_scrollbar_mouse_event;
	scrollbar->base.refresh = daisy_scrollbar_refresh;
	scrollbar->base.scroll_event = 0;
	scrollbar->scrollable_view = 0;
	scrollbar->type = scroll_type;
	scrollbar->thumb_sz = 30;
	scrollbar->thumb_x = 0;
	scrollbar->thumb_y = 0;
	scrollbar->max_thumb_sz = 0;
	scrollbar->max_scroll_limit = 0;
	scrollbar->min_scroll_limit = 0;
	return scrollbar;
}

/**
 * daisy_widget_scrollbar_add_view -- adds a scrollable view to the window
 * @param scrollbar -- pointer to scrollbar where view will be added
 * @param sv -- pointer to scrollable view
 */
void daisy_widget_scrollbar_add_view (daisy_widget_scrollbar_t *scrollbar,daisy_scroll_view_t *sv) {
	scrollbar->scrollable_view = (daisy_widget_t*)sv;
	if (scrollbar->type == DAISY_SCROLLBAR_HORIZONTAL) {
		scrollbar->base.x = sv->base.x;
		scrollbar->base.y = sv->base.y + sv->base.height - 15;
		scrollbar->base.width = sv->base.width - 15;
		scrollbar->base.height = 15;
		scrollbar->max_thumb_sz = (sv->base.width - 15) - 2;
		sv->attached_scrollbar_h = (daisy_widget_t*)scrollbar;
	} else if (scrollbar->type == DAISY_SCROLLBAR_VERTICAL) {
		scrollbar->base.x = sv->base.x + sv->base.width - 15;
		scrollbar->base.y = sv->base.y;
		scrollbar->base.width = 15;
		scrollbar->base.height = sv->base.height - 15;
		scrollbar->max_thumb_sz = (sv->base.height - 15) - 2;
		sv->attached_scrollbar_v = (daisy_widget_t*)scrollbar;
	}
	scrollbar->thumb_sz = 0;
	daisy_widget_scrollbar_update_scroll(scrollbar,sv);
}

/**
 * daisy_widget_scrollbar_update_scroll -- updates the scroll thumbs  according to
 * views number of lines/column
 * @param scrollbar -- current scrollbar to update
 * @param sv -- current scrollview to use as reference
 */
void daisy_widget_scrollbar_update_scroll (daisy_widget_scrollbar_t *scrollbar, daisy_scroll_view_t* sv) {
	if (scrollbar->type == DAISY_SCROLLBAR_VERTICAL) {
		if ((sv->scroll_num_rows * sv->scroll_row_height) > sv->base.height) {
			scrollbar->thumb_sz = scrollbar->base.height - (sv->scroll_num_rows * sv->scroll_row_height - scrollbar->base.height) + 1;
			if (scrollbar->thumb_sz <= 30)
				scrollbar->thumb_sz = 30;
		}
	}else if (scrollbar->type == DAISY_SCROLLBAR_HORIZONTAL)
		scrollbar->thumb_sz = 0;
}