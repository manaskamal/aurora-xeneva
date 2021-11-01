///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///! clientctx.h -- Client Context used for double buffered drawing
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///! =================================================================

#ifndef __CLIENT_CONTEXT_H__
#define __CLIENT_CONTEXT_H__

#include <stdint.h>


extern void cc_draw_pixel (uint32_t* canvas, int x, int y, uint32_t color);
extern void cc_draw_arr_font (uint32_t *canvas,unsigned x, unsigned y, char c, uint32_t color);
extern void cc_draw_arr_string (uint32_t *canvas,unsigned x, unsigned y, char *text, uint32_t color);
extern void cc_font_draw_string (uint32_t*canvas, char* string, int x, int y, uint32_t color);
extern void cc_font_draw_char (uint32_t* canvas, char string, int x, int y, uint32_t color);

#endif