///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  font.h -- Font Registry class
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!=================================================

#ifndef __FONT_H__
#define __FONT_H__

#include <stdint.h>
#include <canvas.h>

typedef struct _font_ {
	uint8_t *data;
	char *name;
	int size;
	uint32_t width;
	uint32_t height;
	int fd;
}Font;

XE_EXTERN XE_EXPORT void acrylic_initialize_font ();
XE_EXTERN XE_EXPORT void acrylic_font_set_size (uint32_t sz);
XE_EXTERN XE_EXPORT void acrylic_font_draw_string (canvas_t *canvas, char* string, int x, int y, uint32_t sz,uint32_t color);
XE_EXTERN XE_EXPORT Font* acrylic_get_system_font ();
XE_EXTERN XE_EXPORT void acrylic_font_get_centering(char* string, int *c_w, int *c_h);
XE_EXTERN XE_EXPORT int acrylic_font_get_length (char* string);
XE_EXTERN XE_EXPORT int acrylic_font_get_height (char* string);
/**
 * acrylic_font_destroy -- destroys font
 */
XE_EXTERN XE_EXPORT void acrylic_close_font ();
#endif