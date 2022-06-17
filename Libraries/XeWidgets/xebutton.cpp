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

#include <xebutton.h>
#include <string.h>
#include <stdlib.h>
#include <styles\XEDefaultButtonStyle.h>
#include <sys\_term.h>

void XEButtonMouseEvent (XEWidget *widget, XEWindow *win, int x, int y, int button) {
	if (button && !widget->kill_focus) {
		widget->clicked = true;
	}

	/* check for kill focus bit */
	if (widget->kill_focus)
		widget->clicked = false;
	
	/* if hover is not painted and hover bit is on,
	   we need to repaint button as hover enabled */
	if (!widget->hover_painted && widget->hover){
		if (widget->painter) 
			widget->painter(widget, win);
		XEUpdateWindow(win,widget->x, widget->y, widget->w, widget->h, true);
		widget->hover_painted = true;
	}

	/* if hover bit is not enabled and click bit is off,
	   paint the button as normal button
	   */
	if (!widget->hover && widget->clicked == false){
		widget->hover_painted = false;
		if (widget->painter)
			widget->painter(widget, win);
		XEUpdateWindow(win,widget->x, widget->y, widget->w, widget->h, true);
	}

	/* Finally, if button is click fire the action also paint the button as
	 * clicked
	 */
	if (widget->clicked && widget->last_mouse_x == x && widget->last_mouse_y == y) {
		if (widget->painter) 
			widget->painter(widget, win);
		XEUpdateWindow(win,widget->x, widget->y, widget->w, widget->h, true);
		
		/* Call the action handler */
		if (widget->action_handler)
			widget->action_handler(widget, win);

		widget->hover_painted = false;
		widget->clicked = false;

	}


	widget->last_mouse_x = x;
	widget->last_mouse_y = y;
}


void XEButtonDestroy (XEWidget *widget, XEWindow *win) {
	XEButton *but = (XEButton*)widget;
	free(but->title);
}


/* XECreateButton -- Creates an Xeneva button
 * @param x -- X coordinate
 * @param y -- y coordinate
 * @param w -- width of the button
 * @param h -- height of the button
 * @param style -- style of the button
 * @param text -- label of the button
 */
XE_EXTERN XE_EXPORT XEButton * XECreateButton (int x, int y, int w, int h, uint8_t style, char *text) {
	XEButton *button = (XEButton*)malloc(sizeof(XEButton));
	button->base.x = x;
	button->base.y = y;
	button->base.w = w;
	button->base.h = h;
	button->base.last_mouse_x = 0;
	button->base.last_mouse_y = 0;
	button->base.clicked = 0;
	button->base.hover = 0;
	button->base.hover_painted = 0;
	button->base.action_handler = 0;
	button->base.mouse_event = XEButtonMouseEvent;
	button->base.painter = XEDefaultButtonPainter;
	button->base.destroy = XEButtonDestroy;
	button->style = style;
	button->title = (char*)malloc(strlen(text));
	memset(button->title, 0, strlen(text));
	strcpy(button->title, text);
	return button;
}