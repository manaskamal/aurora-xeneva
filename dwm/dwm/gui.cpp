/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  gui.cpp -- Graphics Drawing Functions
 *
 *  /PROJECT - Aurora Xeneva {DWM}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ==============================================
 */

#include <dwm.h>
#include <stdtypes.h>
#include <sys.h>

static int s_width = 0;
static int s_height = 0;

void initialize_screen () {
	s_width = get_screen_width ();
	s_height = get_screen_height ();
}
/**=====================================================
 *  G L O B A L   G R A P H I C S   F U N C T I O N S
 * =====================================================
 */
void draw_pixel (unsigned x, unsigned y, uint32_t color ) {
	uint32_t *lfb = (uint32_t*)0x0000600000000000;
	lfb[x + y * s_width] = color;
}

uint32_t get_pixel32bit (unsigned x, unsigned y)
{
	uint32_t* lfb = (uint32_t*)0x0000600000000000;
	return lfb[x + y * s_width];
}


void draw_pixel2 (unsigned x, unsigned y, uint32_t color ) {
	uint32_t *lfb = (uint32_t*)0xFFFFF00000000000;
	lfb[x + y * s_width] = color;
}

void draw_pixel3 (unsigned x, unsigned y, uint32_t color ) {
	uint32_t *lfb = (uint32_t*)0x0000500000000000;
	lfb[x + y * s_width] = color;
}









void copy_to_screen(uint32_t *buf, rect_t *r) {
	uint32_t* lfb = (uint32_t*)0xFFFFF00000000000;
	int width = get_screen_width();
	int height = get_screen_height();
	for (int i=0; i < r->w; i++) {
		for (int j=0; j < r->h; j++){
			uint32_t color = buf[(r->x + i) + (r->y + j) * width];
			lfb[(r->x + i) + (r->y + j) * width] = color;
		}
	}
}

void copy_to_screen2(uint32_t *buf, rect_t *r) {
	uint32_t* lfb = (uint32_t*)0x0000600000000000;
	int width = get_screen_width();
	int height = get_screen_height();
	for (int i=0; i < r->w; i++) {
		for (int j=0; j < r->h; j++){
			uint32_t color = buf[(r->x + i) + (r->y + j) * width] & 0xFFFFFF;
			lfb[(r->x + i) + (r->y + j) * width] = color;
		}
	}
}


