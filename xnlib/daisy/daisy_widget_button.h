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
 * @daisy_widget_button.h -- daisy buttton widget user interface
 *
 **/
#ifndef __DAISY_WIDGET_BUTTON_H__
#define __DAISY_WIDGET_BUTTON_H__


#include "daisy_widget.h"
#include "daisy_window.h"
#include "daisy.h"
#include "list.h"

/**
 * daisy_widget_button_t -- button widget 
 */
typedef struct _daisy_widget_button_ {
	daisy_widget_t base;
	char *text;
	int last_mouse_button;
	bool clicked;
	int last_mouse_x;
	int last_mouse_y;
}daisy_widget_button_t;


/**
 * daisy_widget_create_button -- create a button widget
 * @param width -- width of the button
 * @param height -- height of the button
 */
extern daisy_widget_button_t *daisy_widget_create_button (daisy_window_t* win, char* text);

/**
 * daisy_widget_button_set_dimension -- set a specific dimension to 
 * the widget
 * @param button -- reference button
 * @param x -- x coordinate 
 * @param y -- y coordinate
 * @param w -- width 
 * @param h -- height
 */
extern void daisy_widget_button_set_dimension (daisy_widget_button_t* button,int x, int y,int w, int h);
#endif