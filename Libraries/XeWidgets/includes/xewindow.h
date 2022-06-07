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

#ifndef __XE_WINDOW_H__
#define __XE_WINDOW_H__

#include <stdint.h>
#include <canvas.h>
#include <sys\_xeneva.h>
#include <xebase.h>

#define XE_WIN_DEFAULT_WIDTH  400
#define XE_WIN_DEFAULT_HEIGHT 400



typedef struct _pri_rect_ {
	int x;
	int y;
	int w;
	int h;
}pri_rect_t;


typedef struct _xe_sh_win_ {
	pri_rect_t rect[256];
	int rect_count;
	bool dirty;
	int x;
	int y;
	int width;
	int height;
}XESharedWin;
	
typedef struct _xe_win_ {
	uint8_t attrib;
	uint32_t *backbuff;
	void *shared_win;
	canvas_t *ctx;
	char* title;
	uint32_t color;
	bool first_time;
	XESharedWin *shwin;
	void (*paint)(_xe_win_ *win);
}XEWindow;

/*
 * XECreateWindow -- Creates a new window with given properties
 * @param app -- Pointer to XEApp structure
 * @param attrib -- Window attributes
 * @param title -- window title
 * @param x -- X coord of the window
 * @param y -- Y coord of the window
 */
XE_EXTERN XE_EXPORT XEWindow * XECreateWindow (XeApp *app, canvas_t *canvas, uint8_t attrib, char* title, int x, int y);

/*
 * XEWindowSetXY -- Sets a new location for the window
 * @param win -- Pointer to the window structure
 * @param x -- X position
 * @param y -- Y position
 */
XE_EXTERN XE_EXPORT void XEWindowSetXY (XEWindow *win, int x, int y);



/* XEUpdateWindow -- Updates a portion of the window
* @param win -- Pointer to the window
* @param x -- X Coordinate
* @param y -- Y Coordinate
* @param w -- Width of the rect
* @param h -- Height of the rect
*/
XE_EXTERN XE_EXPORT void XEUpdateWindow(XEWindow* win, int x, int y, int w, int h);

/*
 * XeShowWindow -- Sends a msg to PRIWM
 * to show the window
 */
XE_EXTERN XE_EXPORT void XEShowWindow(XEWindow *win);


#endif