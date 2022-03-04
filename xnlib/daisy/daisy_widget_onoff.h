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
 * @daisy_widget_onoff  -- daisy onoff widget user interface
 *
 **/

#ifndef __DAISY_WIDGET_ONOFF_H__
#define __DAISY_WIDGET_ONOFF_H__

#include "daisy.h"
#include "daisy_widget.h"
#include "daisy_window.h"


/* onoff widget structure */
typedef struct _daisy_widget_onoff_ {
	daisy_widget_t base;
	bool on;
	int last_m_x;
	int last_m_y;
	int thumb_w;
	int thumb_h;
	int thumb_x;
	int thumb_y;
}daisy_widget_onoff_t;


/**
 * daisy_widget_create_onoff -- creates onoff widget
 */
extern daisy_widget_onoff_t * daisy_widget_create_onoff ();
/**
 * daisy_widget_onoff_set_dimension -- sets onoff wigdet dimension
 * @param onoff -- pointer to self
 * @param x -- x coordination
 * @param y -- y coordination
 */
extern void daisy_widget_onoff_set_dimension (daisy_widget_onoff_t *onoff, int x, int y);

#endif