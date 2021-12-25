/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  acrylic.h -- 2D graphics painting and fx library
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

/**
 * acrylic_draw_rect_filled -- draw a rectangle with filled inside
 * @param canvas -- selected canvas to draw to
 * @param x -- starting x position
 * @param y -- starting y position
 * @param w -- rectangle width
 * @param h -- rectangle height
 * @param color -- color to fill
 */
extern void acrylic_draw_rect_filled (canvas_t * canvas,unsigned x, unsigned y, unsigned w, unsigned h, uint32_t color);

/**
 * acrylic_draw_vertical_line -- draw a vertical line 
 * @param canvas -- selected canvas to draw to
 * @param x -- start x position
 * @param y -- start y position 
 * @param length -- line length
 * @param color -- line color
 */
extern void acrylic_draw_vertical_line (canvas_t * canvas,unsigned x, unsigned y, unsigned length, uint32_t color);

/**
 * acrylic_draw_horizontal_line -- draw a horizontal line 
 * @param canvas -- selected canvas to draw to
 * @param x -- start x position
 * @param y -- start y position
 * @param length -- line length
 * @param color -- line color
 */
extern void acrylic_draw_horizontal_line (canvas_t * canvas,unsigned x, unsigned y, unsigned length, uint32_t color);

/**
 * acrylic_draw_rect_unfilled -- draws an outlined rectangle without filled inside
 * @param canvas -- selected canvas to draw to
 * @param x -- start x position
 * @param y -- start y position
 * @param width -- rectangle width
 * @param height -- rectangle height
 * @param color -- rectangle outline colors
 */
extern void acrylic_draw_rect_unfilled (canvas_t * canvas,int x, int y, int width, int height, uint32_t color);

/**
 * acrylic_draw_filled_circle -- draws a filled circle
 * @param canvas -- selected canvas to draw to
 * @param o_x -- starting x position
 * @param o_y -- starting y position
 * @param radius -- radius of the circle
 * @param fill_color -- color to fill
 */
extern void acrylic_draw_filled_circle (canvas_t * canvas,int o_x, int o_y, int radius, uint32_t fill_color);

/**
 * acrylic_draw_image -- draws a given image to canvas
 * @param canvas -- selected canvas to use for drawing
 * @param img -- address of the Image to draw
 * @param x -- starting x position 
 * @param y -- starting y position
 */
extern void acrylic_draw_image (canvas_t * canvas,Image *img, unsigned x, unsigned y);

/**
 * acrylic_draw_string -- draws a string using psf font (currently unused in xeneva)
 * @param canvas -- selected canvas to use for drawing
 * @param x -- starting x position
 * @param y -- starting y position
 * @param text -- actual text to draw
 * @param b_color -- background color 
 * @param f_color -- foreground color (glyph bitmaps color)
 */
extern void acrylic_draw_string (canvas_t * canvas,unsigned x, unsigned y, char *text, uint32_t b_color, uint32_t f_color);

/**
 * acrylic_draw_arr_font -- draws a character using bitmap array font 
 * @param canvas -- selected canvas to use for drawing
 * @param x -- starting x position
 * @param y -- starting y position
 * @param c -- character to draw (ANSI)
 * @param color -- color to use to draw bitmaps (glyph)
 */
extern void acrylic_draw_arr_font (canvas_t * canvas,unsigned x, unsigned y, char c, uint32_t color);

/**
 * acrylic_draw_arr_string -- draws a string using bitmap font
 * @param canvas -- selected canvas to use for drawing
 * @param x -- starting x position
 * @param y -- starting y position
 * @param text -- string to draw 
 * @param color -- color to use to draw bitmaps (glyph)
 */
extern void acrylic_draw_arr_string (canvas_t * canvas,unsigned x, unsigned y, char *text, uint32_t color);

/**
 * acrylic_draw_line -- draws a line using line algorithm
 * @param canvas -- selected canvas to use for drawing
 * @param x0 -- starting x position of the line
 * @param y0 -- starting y position of the line
 * @param x1 -- ending x position of the line
 * @param y1 -- ending y position of the line
 */
extern void acrylic_draw_line (canvas_t * canvas,int x0, int y0, int x1, int y1, uint32_t color);

/**
 * acrylic_draw_circle -- draws outlined circle without filling
 * @param canvas -- selected canvas to use for drawing
 * @param xc -- starting x position
 * @param yc -- starting y position
 * @param x -- ending x position
 * @param y -- ending y position
 * @param color -- outline color
 */
extern void acrylic_draw_circle (canvas_t * canvas,int xc, int yc, int x, int y, uint32_t color);

extern void acrylic_circ_bres (canvas_t * canvas,int xc, int yc, int r, uint32_t color);

/**
 * acrylic_draw_bezier -- draws a quadratic bezier curve 
 * @param canvas -- selected canvas to use for drawing
 * @param x -- arrays of x position
 * @param y -- arrays of y position
 * @param color -- curve outline color
 */
extern void acrylic_draw_bezier (canvas_t * canvas,int x[], int y[], uint32_t color);

//!AcrylicFX -- not ready yet
extern void acrylic_set_tint (canvas_t * canvas,float value, uint32_t* img,int w, int h, int x, int y);
extern void acrylic_set_tone (canvas_t * canvas,uint32_t color, uint32_t *img, int x, int y, int w, int h);
/**
 * acrylic_box_blur -- Adds box blur filter to a given image using 3x3 matrix kernel
 * @param canvas -- current canvas where to draw
 * @param input -- input image buffer
 * @param output -- output image buffer
 * @param cx -- current x position to focus
 * @param cy -- current y position to focus
 * @param w -- box boundary width 
 * @param h -- box boundary height
 */
extern void acrylic_box_blur (canvas_t * canvas,unsigned int* input, unsigned int* output, int cx, int cy, int w, int h);

//! [UNUSED FOR NOW]
extern void acrylic_blit_alpha (canvas_t * canvas,unsigned int* dest, unsigned int* src, int x, int y, int w, int h, int sx, int sy);

#endif