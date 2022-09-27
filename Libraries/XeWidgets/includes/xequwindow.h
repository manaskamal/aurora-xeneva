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

#ifndef __XE_QU_WINDOW_H__
#define __XE_QU_WINDOW_H__

#include <stdint.h>
#include <string.h>
#include <xewidget.h>
#include <xebase.h>
#include <list.h>


typedef struct _xequickserver_ {
	int x;
	int y;
	int w;
	int h;
	bool dirty;
	bool close;
	bool hide;
}XEQuickServer;

typedef struct _xequick_win_ {
	XEQuickServer *server;
	uint32_t* buffer;
	char* title;
	uint16_t server_win_key;
	uint16_t buffer_key;
	list_t *widget_list;
}XEQuickWindow;


/*
 * XECreateQuickWindow -- Creates Quick (POPUP) Window 
 * @param x -- X coordinate
 * @param y -- Y coordinate
 * @param w -- Width of the window
 * @param h -- Height of the window
 * @param title -- title of the window
 */
XE_EXTERN XE_EXPORT XEQuickWindow* XECreateQuickWindow (XeApp *app,int x, int y, int w, int h, char* title);

/*
 * XEQuickWindowClose -- Closes opened quick window
 * @param quickw -- Pointer to XEQuickWindow
 */
XE_EXTERN XE_EXPORT void XEQuickWindowClose (XEQuickWindow *quickw);


/*
 * XEQuickWindowAdd -- Adds a widget to quick window widget list
 * @param win -- Pointer to XEQuickWindow
 * @param widget -- Pointer to XEWidget
 */
XE_EXTERN XE_EXPORT void XEQuickWindowAdd (XEQuickWindow *win, XEWidget* widget);

#endif