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
 * @daisy_widget_slider -- daisy slider object
 *
 **/

#ifndef __DAISY_WIDGET_SLIDER_H__
#define __DAISY_WIDGET_SLIDER_H__

#include "daisy_widget.h"
#include "daisy_window.h"


/* slider type */
#define DAISY_SLIDER_HORIZONTAL  1
#define DAISY_SLIDER_VERTICAL    2


/* slider object */
typedef struct _daisy_widget_slider_ {
	daisy_widget_t base;
	int thumb_x;
	int thumb_y;
	int last_thumb_x;
	int last_thumb_y;
	int max;
	int min;
	int unit;
	int c_val;
	int progress; //slider object position
	int type;
}daisy_widget_slider_t;


/**
 * daisy_widget_create_slider -- creates a slider widget
 * @param slider_type -- type of the slider (DAISY_SLIDER_HORIZONTAL, 
 * DAISY_SLIDER_VERTICAL)
 */
extern daisy_widget_slider_t *daisy_widget_create_slider (int slider_type);

/**
 * daisy_widget_slider_set_dimension -- set slider object dimension
 * @param slider -- pointer to the self
 * @param x -- X coordinate of the slider
 * @param y -- Y coordinate of the slider
 * @param w -- Width of the slider
 * @param h -- Height of the slider
 */
extern void daisy_widget_slider_set_dimension (daisy_widget_slider_t *slider, int x, int y, int length);

#endif