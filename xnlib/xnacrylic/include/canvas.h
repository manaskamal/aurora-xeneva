/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  canvas.h -- Main Backing Store for all graphics stuff
 *
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * =======================================================
 */

#ifndef __CANVAS_H__
#define __CANVAS_H__

//!Acrylic library namespace


#include <stdint.h>
#include <sys\_xeneva.h>

//! Canvas format
typedef struct _canvas_ {
	uint32_t width;
	uint32_t height;
	uint32_t bpp;
	uint16_t scanline;
	uint32_t pitch;
	uint32_t ctx_width;
	uint32_t ctx_height;
	unsigned int* address;
}canvas_t;


typedef struct _svga_io_query_struct_ {
	uint32_t value;
	uint32_t value2;
	uint32_t value3;
	uint32_t value4;
	uint32_t value5;
	uint32_t value6;
}svga_io_query_t;

XE_EXTERN XE_EXPORT canvas_t * canvas_initialize (int width, int height);
XE_EXTERN XE_EXPORT canvas_t *  create_canvas (int width, int height);
XE_EXTERN XE_EXPORT void canvas_set_double_buffer (bool enable);
XE_EXTERN XE_EXPORT void canvas_set_address (canvas_t * canvas,unsigned int* address);
XE_EXTERN XE_EXPORT bool canvas_is_double_buffered();
XE_EXTERN XE_EXPORT void canvas_set_width (canvas_t * canvas,uint32_t width);
XE_EXTERN XE_EXPORT uint32_t canvas_get_width (canvas_t * canvas);
XE_EXTERN XE_EXPORT void canvas_set_height (canvas_t * canvas,uint32_t height);
XE_EXTERN XE_EXPORT uint32_t canvas_get_height (canvas_t * canvas);
XE_EXTERN XE_EXPORT void canvas_screen_update (canvas_t * canvas,uint32_t x, uint32_t y, uint32_t w, uint32_t h);
XE_EXTERN XE_EXPORT void canvas_draw_pixel (canvas_t * canvas,uint32_t x, uint32_t y, uint32_t color);
XE_EXTERN XE_EXPORT uint32_t canvas_get_pixel (canvas_t * canvas,uint32_t x, uint32_t y);
XE_EXTERN XE_EXPORT void canvas_draw_pixel_to_mem (canvas_t* sys_canvas, uint32_t* lfb, uint32_t x, uint32_t y, uint32_t color);
XE_EXTERN XE_EXPORT uint32_t canvas_get_pixel_from_mem (canvas_t* sys_canvas, uint32_t* lfb, uint32_t x, uint32_t y);
XE_EXTERN XE_EXPORT void canvas_fill (canvas_t * canvas,uint32_t w, uint32_t h, uint32_t color);
XE_EXTERN XE_EXPORT unsigned int* canvas_get_framebuffer (canvas_t * canvas);
XE_EXTERN XE_EXPORT uint16_t canvas_get_scanline (canvas_t * canvas);
XE_EXTERN XE_EXPORT uint32_t canvas_get_scale(canvas_t * canvas);
XE_EXTERN XE_EXPORT int canvas_get_fd ();
XE_EXTERN XE_EXPORT void canvas_close (canvas_t *canvas);

#endif