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

#ifndef __SHARED_BITMAP_H__
#define __SHARED_BITMAP_H__

#include <stdint.h>
#include <canvas.h>
#include <image.h>
#include <sys/_xeneva.h>


#define ICON_TYPE_BMP   1
#define ICON_TYPE_JPG   2

typedef struct _icon_file_ {
	int fildesc;
	uint32_t size;
	uint8_t type;
	uint8_t* buffer;
}icon_file;
/*
 * icon_t -- icon bitmap 
 * structure
 */
typedef struct _icon_ {
	int w;
	int h;
	int bpp;
	icon_file* file;
}icon_t;


/*
 * create_icon_bitmap -- creates an icon
 * @param key -- shm key
 * @param w -- width of the icon
 * @param h -- height of the icon
 */
XE_EXTERN XE_EXPORT icon_t * create_icon (int w, int h);

/*
 * icon_open_from_file -- open the icon from file
 * supported format are .bmp & .jpg 
 * @param icon -- pointer to icon
 * @param filename -- image file name
 */
XE_EXTERN XE_EXPORT void icon_open_from_file (icon_t* icon,char* filename);


/*
 * icon_free_image -- frees an opened icon from shared
 * memeory
 */
XE_EXTERN XE_EXPORT void icon_free_file (icon_t *icon);

/*
 * icon_destroy -- destroys an icon buffer
 * @param icon -- pointer to icon
 */
XE_EXTERN XE_EXPORT void icon_destroy (icon_t* icon);

/*
 * icon_draw_jpg -- finally decode jpeg and draws the image into
 *  buffer
 * @param icon -- Pointer to icon
 */
XE_EXTERN XE_EXPORT void icon_draw_jpg (canvas_t *canvas,icon_t* icon, int x, int y);

/*
 * icon_draw_bmp -- finally decode bmp images and draws the image into
 * icon memory buffer
 * @param canvas -- Pointer to system canvas
 * @param icon -- Pointer to icon
 */
XE_EXTERN XE_EXPORT void icon_draw_bmp (canvas_t *canvas, icon_t* icon, int x, int y);



#endif