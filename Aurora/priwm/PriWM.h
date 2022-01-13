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
 * /PROJECT - Aurora's Xeneva v1.0
 * @PriyanshiWM.h -- Priyanshi Compositor Header
 *
 **/

#ifndef __PRIYANSHI_WINDOW_MANAGER_H__
#define __PRIYANSHI_WINDOW_MANAGER_H__


#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <sys\_ipc.h>
#include <sys\_kybrd.h>
#include <sys\_file.h>
#include <sys\_exit.h>


//! Messages code
//! Codes that are being send to PriWM
#define PRI_WIN_CREATE   100
#define PRI_WIN_DESTROY  101
#define PRI_WIN_MINIMIZE 102
#define PRI_WIN_MAXIMIZE 103
#define PRI_WIN_CONFIG   105
#define PRI_WIN_CLOSE    107
#define PRI_KEYBOARD_EVENT 3

//! Codes that are sent by PriWM to clients
#define PRI_CANVAS_READY  200
#define PRI_CANVAS_DESTROYED 201
#define PRI_CANVAS_MOVE  202
#define PRI_CANVAS_MOUSE_MOVE 203
#define PRI_CANVAS_MOUSE_LCLICKED 204
#define PRI_CANVAS_MOUSE_LRELEASE 205
#define PRI_CANVAS_KEY_PRESSED  206
#define PRI_CANVAS_KEY_RELEASED 207
#define PRI_CANVAS_RESIZE 208
#define PRI_CANVAS_REPAINT 209
#define PRI_CANVAS_FOCUS_LOST 210
#define PRI_CANVAS_FOCUS_GAIN 211


//! pri_rect -- priyanshi rectangle 
typedef struct _pri_rect_ {
	int x;
	int y;
	int w;
	int h;
}pri_rect;

//======================================================
//======================================================

//! pri_win_info -- shared window configuration 
//! space
typedef struct _pri_window_info_ {
	int x;
	int y;
	bool dirty;
	pri_rect rect[256];
	int rect_count;
	bool maximize;
	bool minimize;
	bool alpha;
	char data[50];
}pri_win_info;

/* pri_window -- priyanshi window structure */
typedef struct _pri_window_ {
	int width;
	int height;
	uint32_t *canvas;
	uint32_t *info_location;
	int drag_x;
	int drag_y;
	int resz_v;
	int resz_h;
	bool visible;
	bool mark_for_close;
	unsigned short owner_id;
	int old_w;
	int old_h;
	int old_x;
	int old_y;
	uint8_t attr;
	int id;
}pri_window_t;

#endif