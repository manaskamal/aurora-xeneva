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
}Font;

extern void acrylic_initialize_font ();
extern void acrylic_font_set_size (uint32_t sz);
extern void acrylic_font_draw_string (canvas_t *canvas, char* string, int x, int y, uint32_t sz,uint32_t color);
extern Font* acrylic_get_system_font ();
extern void acrylic_font_get_centering(char* string, int *c_w, int *c_h);
extern int acrylic_font_get_length (char* string);
extern int acrylic_font_get_height (char* string);
#endif