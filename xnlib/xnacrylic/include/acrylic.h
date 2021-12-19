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


extern void acrylic_draw_rect_filled (canvas_t * canvas,unsigned x, unsigned y, unsigned w, unsigned h, uint32_t color);
extern void acrylic_draw_vertical_line (canvas_t * canvas,unsigned x, unsigned y, unsigned length, uint32_t color);
extern void acrylic_draw_horizontal_line (canvas_t * canvas,unsigned x, unsigned y, unsigned length, uint32_t color);
extern void acrylic_draw_rect_unfilled (canvas_t * canvas,int x, int y, int width, int height, uint32_t color);
extern void acrylic_draw_filled_circle (canvas_t * canvas,int o_x, int o_y, int radius, uint32_t fill_color);
extern void acrylic_draw_image (canvas_t * canvas,Image *img, unsigned x, unsigned y);
extern void acrylic_draw_string (canvas_t * canvas,unsigned x, unsigned y, char *text, uint32_t b_color, uint32_t f_color);
extern void acrylic_draw_arr_font (canvas_t * canvas,unsigned x, unsigned y, char c, uint32_t color);
extern void acrylic_draw_arr_string (canvas_t * canvas,unsigned x, unsigned y, char *text, uint32_t color);
extern void acrylic_draw_line (canvas_t * canvas,int x0, int y0, int x1, int y1, uint32_t color);
extern void acrylic_draw_circle (canvas_t * canvas,int xc, int yc, int x, int y, uint32_t color);
extern void acrylic_circ_bres (canvas_t * canvas,int xc, int yc, int r, uint32_t color);
extern void acrylic_draw_bezier (canvas_t * canvas,int x[], int y[], uint32_t color);

//!AcrylicFX
extern void acrylic_set_tint (canvas_t * canvas,float value, uint32_t* img,int w, int h, int x, int y);
extern void acrylic_set_tone (canvas_t * canvas,uint32_t color, uint32_t *img, int x, int y, int w, int h);
extern void acrylic_box_blur (canvas_t * canvas,unsigned int* input, unsigned int* output, int cx, int cy, int w, int h);
extern void acrylic_blit_alpha (canvas_t * canvas,unsigned int* dest, unsigned int* src, int x, int y, int w, int h);
#endif