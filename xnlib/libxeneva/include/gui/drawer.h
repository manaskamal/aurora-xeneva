/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  drawer.h -- Drawer system initializer and some simple
 *              shapes drawing functions
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * =======================================================
 */

#ifndef __DRAWER_H__
#define __DRAWER_H__

#include <stdint.h>
#include <xnwidget\geom_rect.h>


//!Drawer struct
typedef struct _drawer_struct_ {
	uint32_t* framebuffer;
	uint32_t  screen_width;
	uint32_t  screen_height;
	uint32_t  bpp;
	uint16_t  scanline;
	uint32_t  win_coord_x;
	uint32_t  win_coord_y;
} drawer_t;

//! initialize the drawer stuffs
extern void drawer_register ();
extern uint32_t drawer_get_screen_width ();
extern uint32_t drawer_get_screen_height ();
extern uint16_t drawer_get_scanline ();
extern uint32_t * drawer_get_framebuffer ();
extern uint32_t drawer_get_win_coord_x ();
extern uint32_t drawer_get_win_coord_y ();
extern void drawer_draw_pixel (unsigned x, unsigned y, uint32_t color);
extern void drawer_draw_rect (unsigned x,unsigned y, unsigned w, unsigned h, uint32_t color);
extern void drawer_draw_vertical_line (unsigned x, unsigned y, unsigned length, uint32_t color);
extern void drawer_draw_horizontal_line (unsigned x, unsigned y, unsigned length, uint32_t color);
extern void drawer_draw_rect_unfilled (int x, int y, int width, int height, uint32_t color);
extern void drawer_draw_filled_circle (int o_x, int o_y, int radius, uint32_t fill_color);
extern void drawer_dirty_update (rect_t *rect, uint32_t pixel);
extern void draw_rounded_rect (int x, int y, int w, int h, int radius, uint32_t color);
#endif