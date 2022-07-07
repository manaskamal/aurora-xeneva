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
 *
 **/

#include "xeradiobutton.h"
#include <stdlib.h>
#include <string.h>
#include <sys\_term.h>
#include <styles\XEDefaultRadioButtonStyle.h>

void XERadioButtonMouseEvent (XEWidget *widget, XEWindow *win, int x, int y, int button) {
	XERadioButton *rb = (XERadioButton*)widget;
	if (rb->is_true ){
		rb->base.painter(widget,win);
		XEUpdateWindow(win,widget->x, widget->y, widget->w, widget->h, true);
	}

}

void XERadioButtonDestroy (XEWidget *widget, XEWindow *win) {
	/* Not Required for now, as Aurora kernel destroys every
	 * objects allocated on heap, when application exits
	 */
}


/*
 * XECreateRadioButton -- creates a radio button 
 * @param x -- X location relative to window activity area
 * @param y -- Y location relative to window activity area
 * @param label -- label of the radio button
 */
XERadioButton *XECreateRadioButton (int x, int y, char* label) {
	XERadioButton *radio = (XERadioButton*)malloc(sizeof(XERadioButton));
	radio->base.x = x;
	radio->base.y = y;
	radio->base.w = 8;
	radio->base.h = 8;
	radio->base.last_mouse_x = 0;
	radio->base.last_mouse_y = 0;
	radio->base.clicked = 0;
	radio->base.hover = 0;
	radio->base.hover_painted = 0;
	radio->base.action_handler = 0;
	radio->base.mouse_event = XERadioButtonMouseEvent;
	radio->base.painter = XEDefaultRadioButtonPainter;
	radio->base.destroy = XERadioButtonDestroy;
	radio->style = 1;
	radio->bound_width = 0;
	radio->bound_height = 0;
	radio->label = (char*)malloc(strlen(label));
	radio->is_true = false;
	memset(radio->label, 0, strlen(label));
	strcpy(radio->label, label);
	sys_print_text ("Radio button created -> %x \r\n", radio);
	return radio;
}