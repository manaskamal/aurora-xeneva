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
 * @daisy_widget_panel.cpp -- daisy panel widget user interface
 *
 **/

#include "daisy_widget_panel.h"
#include <stdlib.h>
#include <acrylic.h>
#include <color.h>
#include <sys/_term.h>

/**
 * daisy_widget_panel_refresh -- repaints the widget
 * @param widget -- panel widget
 * @param win -- reference window
 */
void daisy_widget_panel_refresh (daisy_widget_t *widget, daisy_window_t *win) {
	daisy_widget_panel_t *panel = (daisy_widget_panel_t*)widget;
	acrylic_draw_rect_filled (win->ctx,panel->base.x, panel->base.y, panel->base.width, panel->base.height,
		panel->color);

	acrylic_draw_rect_unfilled (win->ctx,panel->base.x, panel->base.y, panel->base.width, panel->base.height,BLACK);

	/* draw every child widget */
	for (int i = 0; i < panel->childs->pointer; i++) {
		daisy_widget_t *widget = (daisy_widget_t*)list_get_at(panel->childs, i);
		widget->refresh(widget,win);
	}
}

void daisy_widget_panel_mouse_event (daisy_widget_t *widget, daisy_window_t* win, int button, bool clicked, int x, int y) {
	daisy_widget_panel_t *panel = (daisy_widget_panel_t*)widget;
	daisy_win_info_t *info = daisy_get_window_info(win);

	/* redirect the mouse event to every child object */
	for (int i = 0; i < panel->childs->pointer; i++) {
		daisy_widget_t *widget = (daisy_widget_t*)list_get_at(panel->childs,i);
		if (x > info->x + widget->x && x < (info->x + widget->x + widget->width) &&
			y > info->y + widget->y && y < (info->y + widget->y + widget->height)) {
				if (widget->mouse_event)
					widget->mouse_event(widget, win,button,clicked,x, y);
		}
	}
}


void daisy_widget_panel_destroy (daisy_widget_t *widget) {
	daisy_widget_panel_t *panel = (daisy_widget_panel_t*)widget;
	if (panel->childs->pointer > 0) {
		for (int i = 0; i < panel->childs->pointer; i++) {
			daisy_widget_t *widget = (daisy_widget_t*)list_remove(panel->childs, i);
			widget->destroy (widget);
		}
	}
	free(panel->childs);
	free(panel);
}

/**
 * daisy_widget_create_panel -- create panel widget
 * @param width -- width of the panel
 * @param height -- height of the panel
 */
daisy_widget_panel_t *daisy_widget_create_panel (daisy_window_t* win, uint32_t color) {
	daisy_win_info_t *info = daisy_get_window_info(win);
	daisy_widget_panel_t *panel = (daisy_widget_panel_t*)malloc(sizeof(daisy_widget_panel_t));
	panel->base.x = 0;
	panel->base.y = 23;
	panel->base.width = info->width;
	panel->base.height = info->height - 23;
	panel->base.action_event = 0;
	panel->base.key_event = 0;
	panel->base.mouse_event = daisy_widget_panel_mouse_event;
	panel->base.refresh = daisy_widget_panel_refresh;
	panel->base.destroy = daisy_widget_panel_destroy;
	panel->base.scroll_event = 0;
	panel->color = color;
	panel->childs = list_init();
	return panel;
}


/**
 * daisy_widget_panel_add -- add a widget to panel
 * @param panel -- reference panel
 * @param widget -- widget to add
 */
void daisy_widget_panel_add (daisy_widget_panel_t *panel, daisy_widget_t *widget) {
	list_add (panel->childs, widget);
}




