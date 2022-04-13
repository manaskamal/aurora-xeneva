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
 * @daisy_window.cpp -- daisy window object
 *
 **/

#include "daisy_window.h"
#include "daisy_priwm_window.h"
#include "daisy_window_painter.h"
#include "daisy_widget.h"
#include <stdlib.h>
#include <sys/_sleep.h>
#include <sys/_term.h>
#include <sys/_process.h>
#include <fastcpy.h>
#include <string.h>
#include <canvas.h>

/**
 * daisy_window_create -- create a new daisy window
 * @param x -- x coordinate
 * @param y -- y coordinate
 * @param w -- width of the window
 * @param h -- height of the window
 * @param attribute -- attributes of the window
 */
daisy_window_t* daisy_window_create (int x, int y, int w, int h, uint8_t attribute, char* title) {
	daisy_window_t *win = (daisy_window_t*)malloc(sizeof(daisy_window_t));
	_daisy_priwm_create_window_ (x, y, w, h, attribute, title);
	win->ctx = create_canvas (w, h);
	win->attribute = attribute;
	win->mouse_button_last = 0;
	while(1) {
		pri_event_t *e = daisy_get_gifts(true);
		if (e != NULL) {
			if (e->type == DAISY_GIFT_CANVAS) {
				win->backing_store = e->p_value;
				win->shared_win = e->p_value2;
				free(e);
				break;
			}
		}
	}

	win->paint = daisy_window_paint;
	win->title = title;
	win->widgets = list_init();
	win->first_time = true;
	win->theme = DAISY_THEME_DEFAULT;
	return win;
}

/**
 * daisy_get_window_info -- get windows informations
 * @param win -- desired window
 */
daisy_win_info_t * daisy_get_window_info (daisy_window_t* win) {
	daisy_win_info_t *info = (daisy_win_info_t*)win->shared_win;
	return info;
}


/**
 * daisy_window_move -- move the window to a new location
 * @param x -- new x location
 * @param y -- new y location
 */
void daisy_window_move (int x, int y) {
	_daisy_priwm_window_move_(x, y);
}

/**
 * daisy_window_set_theme -- sets a graphical theme for the UI
 * @param win -- pointer to the window object
 * @param theme -- theme id
 */
void daisy_window_set_theme (daisy_window_t *win, uint8_t theme) {
	win->theme = theme;
}
/**
 * daisy_window_handle_mouse -- handles mouse events within the
 * window
 * @param x -- mouse_x coordinate
 * @param y -- mouse_y coordinate
 * @param button -- button bit
 */
void daisy_window_handle_mouse (daisy_window_t *win,int x, int y, int button) {
	daisy_win_info_t *info = daisy_get_window_info(win);

	if (win->focused_widget) {
		if (win->focused_widget->mouse_event)
			win->focused_widget->mouse_event(win->focused_widget,win,button,button,x,y);
	}else {
		/**  loop through all widgets and check there
		**  bounds with current mouse location if they intersect **/
		for (int i = 0; i < win->widgets->pointer; i++) {
			daisy_widget_t *widget = (daisy_widget_t*)list_get_at(win->widgets,i);
			if (x > info->x + widget->x && x < (info->x + widget->x + widget->width) &&
				y > info->y + widget->y && y < (info->y + widget->y + widget->height)) {
					if (widget->mouse_event)
						widget->mouse_event(widget,win,button,button,x,y);
			}
		}
	}

	if (!button) {
		if (win->focused_widget) {
			win->focused_widget = NULL;
		}
	}
}


/**
 * daisy_window_service_event -- services system messages
 * @param e -- event message
 */
void daisy_window_service_event (daisy_window_t *win,pri_event_t *e){
	if (e != 0) {
		if (e->type == DAISY_CURSOR_MOVED) {
			daisy_window_handle_mouse(win,e->dword, e->dword2, e->dword3);
			free(e);
		}
		
		//if (e->type == DAISY_KEY_EVENT) {
		//	//Handle Key Events
		//	free(e);
		//}
	}
}


/**
 * daisy_window_update -- updates the content of double buffered canvas to 
 * real window framebuffer (backing store)
 * @param win -- window to update
 * @param x -- x coordinate
 * @param y -- y coordinate
 * @param w -- width of the bound box to use for update
 * @param h -- height of the bound box to use for update
 */
void daisy_window_update (daisy_window_t *win,int x, int y, int w, int h) {
	uint32_t* lfb = win->backing_store;
	uint32_t* dbl_canvas = win->ctx->address;   
	int width = canvas_get_width(win->ctx);
	int height = canvas_get_height(win->ctx);

	for (int i = 0; i < h; i++)
		fastcpy (lfb + (y + i) * width + x,dbl_canvas + (y + i) * width + x, w * 4);
}


/**
 * daisy_window_show -- make the final window visible
 * @param win -- window to make visible
 */
void daisy_window_show (daisy_window_t *win) {
	daisy_win_info_t *info = daisy_get_window_info(win);
	if (win->paint)
		win->paint(win);
	daisy_window_update (win, 0,0,info->width, info->height);
	if (win->first_time) {
		pri_event_t ev;
		ev.type = PRI_WIN_READY;
		ev.from_id = get_current_pid();
		priwm_send_event (&ev);
		win->first_time = false;
	}
}

/**
 * daisy_window_set_title -- set a suitable title to the window
 * @param win -- reference window
 * @param title -- title to use
 */
void daisy_window_set_title (daisy_window_t *win,char* title) {
	win->title = title;
}

/**
 * daisy_window_add_widget -- add a widget to daisy window
 * @param win -- reference window
 * @param widget -- widget to add
 */
void daisy_window_add_widget (daisy_window_t *win,daisy_widget_t *widget) {
	list_add (win->widgets,widget);
}

/** 
 * daisy_update_rect_area -- updates only selected regions of the given window
 * @param win -- window to be updated
 * @param x -- X coordinate
 * @param y -- Y coordinate
 * @param w -- Width of the rectangle
 * @param h -- Height of the rectangle
 */
void daisy_window_update_rect_area (daisy_window_t *win,uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
	daisy_window_update(win,x,y,w,h);
	daisy_win_info_t *info = daisy_get_window_info(win);
	info->rect[info->rect_count].x = x;
	info->rect[info->rect_count].y = y;
	info->rect[info->rect_count].w = w;
	info->rect[info->rect_count].h = h;
	info->rect_count++;
}

void daisy_window_set_back_color (daisy_window_t *win, uint32_t color) {
	win->color = color;
}

uint32_t daisy_window_get_back_color (daisy_window_t *win) {
	return win->color;
}

/**
 * daisy_window_destroy -- destroys a window and its childs
 * @param win -- window to be destroyed
 */
void daisy_window_destroy (daisy_window_t *win) {
	for (int i = 0; i < win->widgets->pointer; i++) {
		daisy_widget_t *widget = (daisy_widget_t*)list_remove(win->widgets, i);
		widget->destroy(widget);
	}

	free(win->widgets);
	canvas_close(win->ctx);
	free(win->ctx);
	free(win);
	
}


