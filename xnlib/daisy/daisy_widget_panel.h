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
 * @daisy_widget_panel.h -- daisy panel widget user interface
 *
 **/

#ifndef __DAISY_WIDGET_PANEL_H__
#define __DAISY_WIDGET_PANEL_H__

#include "daisy_widget.h"
#include "daisy_window.h"
#include "daisy.h"
#include "list.h"

/**
 * daisy_widget_panel_t -- panel widget 
 */
typedef struct _daisy_widget_panel_ {
	daisy_widget_t base;
	uint32_t color;
	list_t *childs;
}daisy_widget_panel_t;


/**
 * daisy_widget_create_panel -- create panel widget
 * @param width -- width of the panel
 * @param height -- height of the panel
 */
extern daisy_widget_panel_t *daisy_widget_create_panel (daisy_window_t* win, uint32_t color);

/**
 * daisy_widget_panel_add -- add a widget to panel
 * @param panel -- reference panel
 * @param widget -- widget to add
 */
extern void daisy_widget_panel_add (daisy_widget_panel_t *panel, daisy_widget_t *widget);

/**
 * daisy_widget_panel_destroy -- destroys a panel widget
 * @param panel -- reference panel
 */
extern void daisy_widget_panel_destroy (daisy_widget_panel_t *panel);


#endif