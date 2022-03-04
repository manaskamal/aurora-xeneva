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

#ifndef __DOCK_BASE_H__
#define __DOCK_BASE_H__

#include "dock_button.h"
#include <list.h>

typedef struct _dock_ {
	list_t *dock_buttons;
	canvas_t *ctx;
	int x;
	int y; 
	int width;
	int height;
	int buttons_padding;
	int buttons_xoff;
	void *focused_button;
	void (*dock_refresh) (_dock_ *dock,canvas_t *ctx);
}dock_t;


/**
 * dock_create_dock_base -- create a new dock base
 * @param ctx -- canvas offscreen buffer
 * @param x -- x position
 * @param y -- y position
 * @param width -- width of the dock
 * @param height -- height of the dock
 */
extern dock_t *dock_create_dock_base (canvas_t *canvas, int x, int y, int width, int height);

/**
 * dock_repaint -- repaints the entire dock window
 * @param dock -- pointer to the dock object
 */
extern void dock_repaint (dock_t *dock);

/**
 * dock_add_button -- adds a dock button to the button list
 * @param dock -- pointer to the dock object
 * @param button -- dock button object
 */
extern void dock_add_button (dock_t *dock, dock_button_t *button);

#endif