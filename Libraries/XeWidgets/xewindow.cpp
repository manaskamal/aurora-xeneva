/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2021, Manas Kamal Choudhury
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

#include <xewindow.h>
#include <stdlib.h>
#include <styles\XEDefaultWinStyle.h>
#include <fastcpy.h>
#include <sys\_process.h>
#include <sys\_term.h>
#include <string.h>
#include <acrylic.h>
#include <color.h>
#include <xe_glblctrl_close.h>
#include <sys\shm.h>

/*
 * =========================================================================================
 *  XEWindow Default Action Handlers
 * =========================================================================================
 */
void XEGlobalControlMouseEvent(XEGlobalControl *ctrl, XEWindow *win, int x, int y, int button) {

	uint32_t fill_color = 0;
	uint32_t outline_color = 0;

	if (ctrl->hover){
		fill_color = ctrl->hover_fill_color;
		outline_color = ctrl->hover_outline_color;
	}else if (ctrl->clicked){
		fill_color = ctrl->clicked_fill_color;
		outline_color = ctrl->clicked_outline_color;
	}else {
		fill_color = ctrl->fill_color;
		outline_color = ctrl->outline_color;
	}

	if (ctrl->clicked) {
		fill_color = ctrl->clicked_fill_color;
		outline_color = ctrl->clicked_outline_color;
		ctrl->clicked = false;
	}

	acrylic_draw_filled_circle(win->ctx,ctrl->x+8, ctrl->y+8,8,fill_color);
	acrylic_draw_circle(win->ctx,ctrl->x+8, ctrl->y+8, 8,outline_color);
	XEUpdateWindow(win,ctrl->x, ctrl->y, ctrl->w, ctrl->h, true); 

	if (button)
		if (ctrl->action_event)
			ctrl->action_event(ctrl,win);
}

/*
 * XEAddGlobalButton -- Adds Global Control button to window
 * @param win -- Pointer to window
 * @param x -- X Coordinate
 * @param y -- Y Coordinate
 * @param type -- button type
 */
XE_EXTERN XE_EXPORT XEGlobalControl* XEAddGlobalButton(XEWindow *win,int x, int y, int w, int h, uint8_t type) {
	XEGlobalControl *glbl = (XEGlobalControl*)malloc(sizeof(XEGlobalControl));
	glbl->x = x;
	glbl->y = y;
	glbl->w = w;
	glbl->h = h;
	glbl->clicked = false;
	glbl->hover = false;
	glbl->type = type;
	list_add(win->global_controls, glbl);
	return glbl;
}
/*
 * XECreateWindow -- Creates a new window with given properties
 * @param app -- Pointer to XEApp structure
 * @param attrib -- Window attributes
 * @param title -- window title
 * @param x -- X coord of the window
 * @param y -- Y coord of the window
 */
XE_EXTERN XE_EXPORT XEWindow * XECreateWindow (XeApp *app, canvas_t *canvas, uint8_t attrib, char* title, int x, int y) {
	/*adjust the scanline */
	//canvas->scanline = 8;
	//canvas->ctx_width = 4;
	XEWindow *win = (XEWindow*)malloc(sizeof(XEWindow));
	win->attrib = attrib;
	win->backbuff = app->framebuffer;
	win->ctx = canvas;
	win->shared_win = app->shared_win_address;
	win->shwin = (XESharedWin*)win->shared_win;
	win->title = (char*)malloc(strlen(title));
	memset(win->title, 0, strlen(title));
	win->color = WHITE;
	win->shwin->x = x;
	win->shwin->y = y;
	win->first_time = true;
	win->global_controls = list_init();
	win->widgets = list_init();
	win->app = app;
	win->paint = XEDefaultWinPaint;
	strcpy(win->title, title);

	/*Add universal three global controls */

	/* Technical Details --> Global Control buttons appears as 
	 * circular widget whose radius is 8, but the widget takes its
	 * boundary as rectangle, so the width and height of the bound
	 * is just double of its radius i.e 16 (8*2)
	 */
	XEGlobalControl *close = XEAddGlobalButton(win,12,5,16,16,XE_GLBL_CNTRL_CLOSE);
	close->mouse_event = XEGlobalControlMouseEvent;
	close->fill_color = 0xFFDB4844;
	close->outline_color = 0xFF7A1A17;
	close->hover_fill_color = 0xFFC62520;
	close->hover_outline_color = 0xFF7A1A17;
	close->clicked_fill_color = 0xFFAF0505;
	close->clicked_outline_color = 0xFF7A1A17;
	close->action_event = XEGlobalControl_CloseHandler;
	XEGlobalControl *maxim = XEAddGlobalButton(win,34,5,16,16,XE_GLBL_CNTRL_MAXIMIZE);
	maxim->mouse_event = XEGlobalControlMouseEvent;
	maxim->fill_color = 0xFFE8CD56;
	maxim->outline_color = 0xFF78671F;
	maxim->hover_fill_color = 0xFFC6A826;
	maxim->hover_outline_color = 0xFF78671F;
	maxim->clicked_fill_color = 0xFFAA821D;
	maxim->clicked_outline_color = 0xFF78671F;
	maxim->action_event = 0;
	XEGlobalControl *minim = XEAddGlobalButton(win,54,5,16,16,XE_GLBL_CNTRL_MINIMIZE);
	minim->mouse_event = XEGlobalControlMouseEvent;
	minim->fill_color = 0xFF4ED629;
	minim->outline_color = 0xFF387428;
	minim->hover_fill_color = 0xFF44BA23;
	minim->hover_outline_color = 0xFF387428;
	minim->clicked_fill_color = 0xFF3FA225;
	minim->clicked_outline_color = 0xFF387428;
	minim->action_event = 0;
	return win;
}

/*
 * XEWindowSetXY -- Sets a new location for the window
 * @param win -- Pointer to the window structure
 * @param x -- X position
 * @param y -- Y position
 */
XE_EXTERN XE_EXPORT void XEWindowSetXY (XEWindow *win, int x, int y) {
	win->shwin->x = x;
	win->shwin->y = y;
}


/*
 * XEWindowAddWidget -- Adds an widget to main activity window
 * @param window -- Pointer to main activity window
 * @param widget -- Pointer to widget
 */
XE_EXTERN XE_EXPORT void XEWindowAddWidget(XEWindow *window, XEWidget *widget) {
	list_add(window->widgets, widget);
}


/* XEUpdateWindow -- Updates a portion of the window
* @param win -- Pointer to the window
* @param x -- X Coordinate
* @param y -- Y Coordinate
* @param w -- Width of the rect
* @param h -- Height of the rect
*/
XE_EXTERN XE_EXPORT void XEUpdateWindow(XEWindow* win, int x, int y, int w, int h, bool dirty) {
	uint32_t *lfb = win->backbuff;
	uint32_t* dbl_buf = win->ctx->address;
	int width = canvas_get_width(win->ctx);
	int height = canvas_get_height(win->ctx);

	for (int i = 0; i < h; i++)
		fastcpy(lfb + (y + i) * win->shwin->width + x, dbl_buf + (y + i) * win->shwin->width + x, w*4);

	if (dirty) {
		win->shwin->rect[win->shwin->rect_count].x = x;
		win->shwin->rect[win->shwin->rect_count].y = y;
		win->shwin->rect[win->shwin->rect_count].w = w;
		win->shwin->rect[win->shwin->rect_count].h = h;
		win->shwin->rect_count++;
		win->shwin->dirty = 1;
	}
}

/*
 * XeShowWindow -- Sends a msg to PRIWM
 * to show the window
 */
XE_EXTERN XE_EXPORT void XEShowWindow(XEWindow *win) {
	if (win->paint)
		win->paint(win);
	
	XEUpdateWindow(win, 0, 0, win->shwin->width, win->shwin->height, false);

	if (win->first_time) {
		pri_event_t e;
		e.type = PRIWM_WINDOW_SHOW;
		e.from_id = get_current_pid();
		XeSendEventPRIWM(&e);
		win->first_time = false;
	}
}

/*
 * XERedrawWindow -- Redraws the window 
 * @param win -- Pointer to window structure
 */
XE_EXTERN XE_EXPORT void XERedrawWindow (XEWindow *win) {
	if (win->paint)
		win->paint;
}


/*
 * XEWindowMouseHandle -- Default Mouse handler for XEWindow
 * @param win -- Pointer to window
 * @param x -- X coord of mouse passed by window manager
 * @param y -- Y coord of mouse passed by window manager
 * @param button -- mouse button state passed by window manager
 */
XE_EXTERN XE_EXPORT void XEWindowMouseHandle(XEWindow *win, int x, int y, int button, int scroll) {
	/* first check titlebar bound, cuz there are global control widgets 
	 * which needs seperate handling 
	 */
	if (y > win->shwin->y && y < win->shwin->y + 26) {
		for (int i = 0; i < win->global_controls->pointer; i++) {
			XEGlobalControl *ctrl = (XEGlobalControl*)list_get_at(win->global_controls, i);
			if (x > win->shwin->x + ctrl->x && x < (win->shwin->x + ctrl->x + ctrl->w) &&
				(y > win->shwin->y + ctrl->y && y < (win->shwin->y + ctrl->y + ctrl->h))) {
					ctrl->hover = true;
					if (button)
						ctrl->clicked = true;

					if (ctrl->mouse_event)
						ctrl->mouse_event(ctrl,win,x,y,button);
			}else {
				if (ctrl->hover){
					ctrl->hover = false;
					ctrl->clicked = false;
					if (ctrl->mouse_event)
						ctrl->mouse_event(ctrl,win,x,y,button);
				}
			}

		}	
	}

	/* Activitiy area */
	if (y > win->shwin->y + 26 && y < (win->shwin->y + 26 + win->shwin->height-26)) {
		for (int i = 0; i < win->widgets->pointer; i++) {
			XEWidget *widget = (XEWidget*)list_get_at(win->widgets, i);
			if (x > win->shwin->x + widget->x && x < (win->shwin->x + widget->x + widget->w) &&
				(y > win->shwin->y + widget->y && y < (win->shwin->y + widget->y + widget->h))) {
					widget->hover = true;
					widget->kill_focus = false;
					if (widget->mouse_event) 
						widget->mouse_event(widget, win, x, y, button);
			}else {
				if (widget->hover) {
					widget->hover = false;
					widget->kill_focus = true;
					if (widget->mouse_event)
						widget->mouse_event(widget, win, x, y, button);
				}
			}
		}
	}
}

/*
 * XEWindowHandleResize -- Handle new window resize events from window server
 * @param win -- Pointer to XEWindow
 * @param back_key -- Back Buffer key 
 * @param n_w -- new width
 * @param n_h -- new height
 */
XE_EXTERN XE_EXPORT void XEWindowHandleResize (XeApp *app, XEWindow *win, uint16_t back_key) {
	uint16_t id = sys_shmget(back_key, 0, 0);
	void* back_addr = sys_shmat(id,0, 0);
	app->framebuffer = (uint32_t*)back_addr;
	win->backbuff = (uint32_t*)back_addr;
	app->back_key = back_key;

}

/*
 * XEResizeWindow -- Sends resize command to window server
 * for this window
 * @param w -- width
 * @param h -- height
 */
XE_EXTERN XE_EXPORT void XEResizeWindow (int w, int h) {
	pri_event_t ev;
	ev.type = 108;
	ev.dword = w;
	ev.dword2 = h;
	XeSendEventPRIWM(&ev);
}





