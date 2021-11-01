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


typedef struct _font_ {
	uint8_t *data;
	char *name;
	int size;
	uint8_t width;
	uint8_t height;
	uint32_t* offsetTable;
}Font;

extern void acrylic_initialize_font ();
extern void acrylic_font_draw_string ( char* string, int x, int y, uint32_t color);
extern Font* acrylic_get_system_font ();
#endif