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
 * @dock_base -- dock base class
 *
 **/

#include "dock_base.h"


void dock_refresh (dock_t *dock, canvas_t *ctx) {
	int x = dock->x;
	int y = dock->y;
	int w = dock->width;
	int h = dock->height;

	acrylic_draw_rect_filled(ctx,x + 0,y + 0,w,h,0xFFBDB9B9);
	acrylic_draw_horizontal_line (ctx,x + 0,y + 0,w,WHITE);
	acrylic_draw_horizontal_line (ctx,x + 0,y + 1,w,WHITE);
	acrylic_draw_horizontal_line (ctx,x + 0,y + 2,w,WHITE);

	acrylic_draw_horizontal_line (ctx,x + 0,y + 30-1,w,LIGHTBLACK);
	acrylic_draw_horizontal_line (ctx,x + 0,y + 30-2,w,LIGHTBLACK);

	if (dock->dock_buttons->pointer > 0) {
		for (int i = 0; i < dock->dock_buttons->pointer; i++) {
			dock_button_t *button = (dock_button_t*)list_get_at(dock->dock_buttons, i);
			button->refresh(button,dock->ctx);
		}
	}
}

/**
 * dock_create_dock_base -- create a new dock base
 * @param ctx -- canvas offscreen buffer
 * @param x -- x position
 * @param y -- y position
 * @param width -- width of the dock
 * @param height -- height of the dock
 */
dock_t *dock_create_dock_base(canvas_t *ctx, int x, int y, int width, int height) {
	dock_t *dock = (dock_t*)malloc(sizeof(dock_t));
	dock->ctx = ctx;
	dock->x = x;
	dock->y = y;
	dock->width = width;
	dock->height = height;
	dock->dock_buttons = list_init();
	dock->dock_refresh = dock_refresh;
	dock->buttons_padding = 0;
	dock->buttons_xoff = 0;
	return dock;
}

/**
 * dock_repaint -- repaints the entire dock window
 * @param dock -- pointer to the dock object
 */
void dock_repaint (dock_t *dock) {
	dock->dock_refresh (dock,dock->ctx);
}

/**
 * dock_add_button -- adds a dock button to the button list
 * @param dock -- pointer to the dock object
 * @param button -- dock button object
 */
void dock_add_button (dock_t *dock, dock_button_t *button) {
	list_add (dock->dock_buttons, button);
}


