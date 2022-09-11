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
 * @priwm.h -- priyanshi's window manager header
 *
 **/

#ifndef __PRI_WM_H__
#define __PRI_WM_H__

#include <stdint.h>
#include <canvas.h>
#include <acrylic.h>


/* Messages sends from client to server */
#define PRI_WIN_CREATE  100
#define PRI_WIN_MARK_FOR_CLOSE 102
#define PRI_WIN_MOVE 103
#define PRI_WIN_READY 104
#define PRI_REGISTER_DESKTOP_COMPONENT 105
#define PRI_CHANGE_WALLPAPER 106
#define PRI_RESIZE_ACK  107  //!! Resize acknowledgement send to server by clients
#define PRI_WIN_RESIZE  108
#define PRI_WIN_SET_PROPERTIES 109

/* Messages that are being send to client by server */
#define DAISY_WIN_MOVE  200
#define DAISY_CURSOR_MOVED 201
#define DAISY_GIFT_CANVAS 202
#define DAISY_GIFT_SHARED_WIN 203
#define DAISY_KEY_EVENT  204
#define DAISY_NEW_WINDOW_INFO 205
#define DAISY_NOTIFY_WIN_FOCUS_CHANGED 206
#define DAISY_NOTIFY_WIN_REMOVE 207
#define DAISY_WINDOW_CLOSED 208
#define DAISY_WINDOW_RESIZE 209

/* Resize codes */
#define DAISY_WINDOW_RESIZE_VERTICAL 1
#define DAISY_WINDOW_RESIZE_HORIZONTAL 2
#define DAISY_WINDOW_RESIZE_VERTICAL_TOP 3
#define DAISY_WINDOW_RESIZE_HORIZONTAL_LEFT 4
#define DAISY_WINDOW_RESIZE_ALL  5


#define PRI_WM_XCOORD_FOLLOW_MOUSE  (1<<1)
#define PRI_WM_YCOORD_FOLLOW_MOUSE  (1<<2)


typedef struct _pri_rect_ {
	int x;
	int y;
	int w;
	int h;
}pri_rect_t;

typedef struct _pri_rect_2_ {
	int top;
	int left;
	int bottom;
	int right;
} pri_rect_2;

#pragma pack (push, 1)
typedef struct _bmp_{
	unsigned short type;   //0x4d42
	unsigned int size;
	unsigned short resv1;
	unsigned short resv2;
	unsigned int off_bits;
} bitmap_img;


typedef struct _info_ {
	unsigned int biSize;
	long biWidth;
	long biHeight;
	unsigned short biPlanes;
	unsigned short biBitCount;
	unsigned int biCompression;
	unsigned int biSizeImage;
	long biXPelsPerMeter;
	long biYPelsPerMeter;
	unsigned int biClrUsed;
	unsigned int biClrImportant;
} bitmap_info;

#pragma pack(pop)

typedef struct _image_ {
	unsigned char* image_data;
	int width;
	int height;
}pri_bmp_image;



//! MOUSE CODES
#define MOUSE_MOVE  1
#define KEY_PRESSED 3
typedef struct _dwm_message_ {
	uint16_t type;
	uint32_t dword;
	uint32_t dword2;
	uint32_t dword3;
	uint32_t dword4;
	uint32_t dword5;
	uint32_t dword6;
}mouse_message_t;

/*
 * backing store structure
 */
typedef struct _backing_store_ {
	uint32_t *addr;
	uint32_t size;
	uint16_t owner_id;
	bool free;
}backing_store_t;

typedef struct _shared_win_struct_ {
	uint32_t *win_info_location;
	bool free;
	uint16_t owner_id;
}shared_win_t;

/** ============================================
 ** Window is composed of two strucutre
 **  
 **     --------------------------------
 **    |        PRI_WIN_INFO            |
 **    |--------------------------------|
 **    |  PRI_WINDOW SERVER/CLIENT      |
 **    |________________________________|
 **/
/**
 * pri_win_info_t -- window internal datas
 * that are being shared between clients and
 * server
 */
typedef struct _pri_win_info_ {
	pri_rect_t rect[256];
	int rect_count;
	bool dirty;
	int x;
	int y;
	int width;
	int height;
	bool alpha;
}pri_win_info_t;


#define PRI_WIN_MOVABLE   (1<<0)
#define PRI_WIN_STATIC   (1<<1)
#define PRI_WIN_ALWAYS_ON_TOP  (1<<2)
#define PRI_WIN_NON_RESIZABLE  (1<<3)

#define PRI_WIN_ANIM_POSITIVE 0x1
#define PRI_WIN_ANIM_NEGATIVE 0x2
/**
 * pri_window_t -- window structure
 */
typedef struct _pri_win_ {
	bool anim;
	uint8_t attribute;
	uint16_t owner_id;
	uint32_t *backing_store;
	uint32_t *pri_win_info_loc;
	uint16_t sh_win_key;
	uint16_t backing_store_key;
	int drag_x;
	int drag_y;
	int resz_h;
	int resz_v;
	int anim_x;
	int anim_y;
	int anim_dir;
	canvas_t *shadow;
	char* title;
	bool mark_for_close;
	_pri_win_ *next;
	_pri_win_ *prev;
}pri_window_t;

/*
 * pri_wallpaper_t -- wallpaper structure
 */
typedef struct _pri_wallp_ {
	uint8_t *buffer;
	int w;
	int h;
	Image *img;
}pri_wallpaper_t;

/*
 * desktop component structure
 */
typedef struct _desktop_component_ {
	uint16_t process_id;
}desktop_component_t;
#endif