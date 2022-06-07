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
	win->title = title;
	win->color = 0;
	win->shwin->x = x;
	win->shwin->y = y;
	win->first_time = true;
	win->paint = XEDefaultWinPaint;
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


/* XEUpdateWindow -- Updates a portion of the window
* @param win -- Pointer to the window
* @param x -- X Coordinate
* @param y -- Y Coordinate
* @param w -- Width of the rect
* @param h -- Height of the rect
*/
XE_EXTERN XE_EXPORT void XEUpdateWindow(XEWindow* win, int x, int y, int w, int h) {
	uint32_t *lfb = win->backbuff;
	uint32_t* dbl_buf = win->ctx->address;
	int width = canvas_get_width(win->ctx);
	int height = canvas_get_height(win->ctx);

	for (int i = 0; i < h; i++)
		fastcpy(lfb + (y + i) * width + x, dbl_buf + (y + i) * width + x, w*4);
}

/*
 * XeShowWindow -- Sends a msg to PRIWM
 * to show the window
 */
XE_EXTERN XE_EXPORT void XEShowWindow(XEWindow *win) {
	if (win->paint)
		win->paint(win);
	sys_print_text("Showing window -> %d %d \r\n",win->shwin->width, win->shwin->height);
	XEUpdateWindow(win, 0, 0, win->shwin->width, win->shwin->height);

	if (win->first_time) {
		pri_event_t e;
		e.type = PRIWM_WINDOW_SHOW;
		e.from_id = get_current_pid();
		XeSendEventPRIWM(&e);
		win->first_time = false;
	}
}





