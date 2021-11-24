/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  acrylic.h -- 2D graphics painting library
 *
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ------------------------------------------------
 */

#ifndef __ACRYLIC_H__
#define __ACRYLIC_H__


#include <canvas.h>
#include <stdint.h>
#include <stdlib.h>
#include <image.h>


extern void acrylic_draw_rect_filled (unsigned x, unsigned y, unsigned w, unsigned h, uint32_t color);
extern void acrylic_draw_vertical_line (unsigned x, unsigned y, unsigned length, uint32_t color);
extern void acrylic_draw_horizontal_line (unsigned x, unsigned y, unsigned length, uint32_t color);
extern void acrylic_draw_rect_unfilled (int x, int y, int width, int height, uint32_t color);
extern void acrylic_draw_filled_circle (int o_x, int o_y, int radius, uint32_t fill_color);
extern void acrylic_draw_image (Image *img, unsigned x, unsigned y);
extern void acrylic_draw_string (unsigned x, unsigned y, char *text, uint32_t b_color, uint32_t f_color);
extern void acrylic_draw_arr_font (unsigned x, unsigned y, char c, uint32_t color);
extern void acrylic_draw_arr_string (unsigned x, unsigned y, char *text, uint32_t color);
extern void acrylic_draw_line (int x0, int y0, int x1, int y1, uint32_t color);
extern void acrylic_draw_circle (int xc, int yc, int x, int y, uint32_t color);
extern void acrylic_circ_bres (int xc, int yc, int r, uint32_t color);
extern void acrylic_draw_bezier (int x[], int y[], uint32_t color);

//!AcrylicFX
extern void acrylic_set_tint (float value, uint32_t* img,int w, int h, int x, int y);
extern void acrylic_set_tone (uint32_t color, uint32_t *img, int x, int y, int w, int h);
extern void acrylic_box_blur (unsigned int* input, unsigned int* output, int cx, int cy, int w, int h);
#endif