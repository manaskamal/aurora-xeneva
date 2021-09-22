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

//! Canvas format
typedef struct _canvas_ {
	uint32_t width;
	uint32_t height;
	uint32_t bpp;
	uint16_t scanline;
	uint32_t* address;
}canvas_t;


typedef struct _svga_io_query_struct_ {
	uint32_t value;
	uint32_t value2;
	uint32_t value3;
	uint32_t value4;
	uint32_t value5;
	uint32_t value6;
}svga_io_query_t;

extern void create_canvas ();
extern void canvas_set_double_buffer (bool enable);
extern void canvas_set_address (uint32_t* address);
extern bool canvas_is_double_buffered();
extern void canvas_set_width (uint32_t width);
extern uint32_t canvas_get_width ();
extern void canvas_set_height (uint32_t height);
extern uint32_t canvas_get_height ();
extern void canvas_screen_update (uint32_t x, uint32_t y, uint32_t w, uint32_t h);
extern void canvas_draw_pixel (uint32_t x, uint32_t y, uint32_t color);
extern uint32_t canvas_get_pixel (uint32_t x, uint32_t y);
extern void canvas_fill (uint32_t w, uint32_t h, uint32_t color);
extern uint32_t* canvas_get_framebuffer ();
extern uint16_t canvas_get_scanline ();
extern uint32_t canvas_get_scale();
#endif