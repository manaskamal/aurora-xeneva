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
 * @daisy_widget_label.h -- daisy widget label
 *
 **/

#ifndef __DAISY_WIDGET_LABEL_H__
#define __DAISY_WIDGET_LABEL_H__

#include "daisy_widget.h"
#include "daisy_window.h"

/**
 * daisy_widget_label_t -- label widget 
 */
typedef struct _daisy_widget_label_ {
	daisy_widget_t base;
	char *text;
	int  font_size;
	uint32_t color;
}daisy_widget_label_t;


/**
 * daisy_widget_create_button -- create a button widget
 * @param width -- width of the button
 * @param height -- height of the button
 */
extern daisy_widget_label_t *daisy_widget_create_label (daisy_window_t* win);
/** 
 * daisy_widget_label_set_dimension -- set label widget dimension
 * @param label -- pointer to the label widget
 * @param x -- X coordinate
 * @param y -- Y coordinate
 * @param w -- Width of the label widget
 * @param h -- Height of the label widget
 */
extern void daisy_widget_label_set_dimension (daisy_widget_label_t *label, int x, int y, int w, int h);


/**
 * daisy_widget_label_set_text -- set a new text for the label
 * @param label -- pointer to the label widget
 * @param text -- text to be set
 */
extern void daisy_widget_label_set_text (daisy_widget_label_t *label, char* text);

/**
 * daisy_widget_label_set_font_size -- set a new font size for the label
 * @param label -- pointer to the label widget
 * @param size -- new size of the font
 */
extern void daisy_widget_label_set_font_size (daisy_widget_label_t *label, int size);


/**
 * daisy_widget_label_set_color -- set a new color to the label
 * @param label -- pointer to the label widget
 * @param color -- color for the label
 */
extern void daisy_widget_label_set_color (daisy_widget_label_t *label, uint32_t color);

#endif