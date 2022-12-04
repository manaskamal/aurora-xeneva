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
 **/

#include "XEGoButton.h"
#include <sys/_term.h>
#include <stdlib.h>
#include <acrylic.h>
#include <font.h>
#include <color.h>
#include <string.h>

/*
 * XEGoButtonPainter -- Paint handler for XEGoButton
 * @param widget -- Pointer to GOButton [System parameter]
 * @param win -- Pointer to application window [System parameter]
 */
void XEGoButtonPainter (XEWidget* widget, XEWindow* win) {
	XEGoButton *gobut = (XEGoButton*)widget;
	uint32_t color_bg = 0xFF292322;
	uint32_t color_out = GRAY;

	if (widget->hover) {
		color_bg = 0xFF5F5858;
	}

	if (widget->clicked) {
		color_bg = 0xFF191919;
	}

	acrylic_draw_rect_filled(win->ctx, widget->x, widget->y, widget->w, widget->h,color_bg);
	acrylic_draw_rect_unfilled(win->ctx, widget->x, widget->y, widget->w, widget->h, color_out);
	icon_draw_bmp(win->ctx,gobut->logo_icon, widget->x + widget->w/2 - 45/2, widget->y);
}

/*
 * XEGoButtonMouseEvent -- Mouse Event handler for Go Button
 * @param widget -- Pointer to button widget [System parameter]
 * @param win -- Pointer to Application window [System parameter]
 * @param x -- X coord
 * @param y -- Y coord
 * @param button -- Mouse button
 */
void XEGoButtonMouseEvent (XEWidget* widget, XEWindow* win, int x, int y, int button) {
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

/**
 * XECreateGoButton -- Create GOButton
 * @param x -- X location
 * @param y -- Y location
 * @param w -- Width of the button
 * @param h -- Height of the button
 * @param icon_file -- logo icon file
 */

XEGoButton * XECreateGoButton (int x, int y, int w, int h, char* title, char* icon_file) {
	XEGoButton *gobut = (XEGoButton*)malloc(sizeof(XEGoButton));
	gobut->logo_icon = create_icon(NULL, 45,30);
	icon_open_from_file(gobut->logo_icon, icon_file);
	gobut->base.x = x;
	gobut->base.y = y;
	gobut->base.w = w;
	gobut->base.h = h;
	gobut->base.last_mouse_x = 0;
	gobut->base.last_mouse_y = 0;
	gobut->base.clicked = 0;
	gobut->base.hover = 0;
	gobut->base.hover_painted = 0;
	gobut->base.action_handler = 0;
	gobut->base.mouse_event = XEGoButtonMouseEvent;
	gobut->base.painter = XEGoButtonPainter;
	gobut->base.destroy = 0;
	gobut->color_scheme = 0;
	gobut->title = (char*)malloc(strlen(title)+1);
	memset(gobut->title, 0, strlen(title));
	strcpy(gobut->title, title);
	return gobut;
}