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

#include <canvas.h>
#include <stdlib.h>
#include <sys\ioquery.h>
#include <sys\mmap.h>
#include <sys\_term.h>


canvas_t* canvas = NULL;
bool double_buffer = true;

void create_canvas () {
	uint32_t width = ioquery(IO_QUERY_SVGA,SVGA_GET_WIDTH,NULL);
	uint32_t height = ioquery(IO_QUERY_SVGA, SVGA_GET_HEIGHT, NULL);
	uint32_t bpp = ioquery(IO_QUERY_SVGA, SVGA_GET_BPP, NULL);
	uint16_t scanline = ioquery(IO_QUERY_SVGA, SVGA_GET_SCANLINE, NULL);

	if (double_buffer)
		for (int i = 0; i < (width * height * 32) / 4096; i++)
			valloc(0x0000600000000000 + i * 4096);


	canvas = (canvas_t*)malloc(sizeof(canvas_t));
	canvas->width = width;
	canvas->height = height;
	canvas->bpp = bpp;
	canvas->scanline = scanline;
	if (double_buffer)
		canvas->address = (uint32_t*)0x0000600000000000;

}

void canvas_set_double_buffer (bool enable) {
	double_buffer = enable;
}


bool canvas_is_double_buffered() {
	return double_buffer;
}

void canvas_set_address (uint32_t* address) {
	if (double_buffer == false)
		canvas->address = address;
}


void canvas_set_width (uint32_t width) {
	canvas->width = width;
}

void canvas_set_height (uint32_t height) {
	canvas->height = height;
}

uint32_t canvas_get_width () {
	return canvas->width;
}

uint32_t canvas_get_height () {
	return canvas->height;
}

void canvas_screen_update (uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
	uint32_t* lfb = (uint32_t*)0xFFFFF00000000000;

	for (int i=0; i < w; i++) {
		for (int j=0; j < h; j++){
			uint32_t color = canvas->address[(x + i) + (y + j) * canvas_get_scale()];
			lfb[(x + i) + (y + j) * canvas_get_scale()] = color;
		}
	}

	svga_io_query_t *query = (svga_io_query_t*)malloc(sizeof(svga_io_query_t));
	query->value = x;
	query->value2 = y;
	query->value3 = w;
	query->value4 = h;
	ioquery(IO_QUERY_SVGA, SVGA_UPDATE, query);
}


void canvas_draw_pixel (uint32_t x, uint32_t y, uint32_t color) {
	uint32_t *lfb =  canvas->address;      
	lfb[x + y * canvas_get_width()] = color;
}


uint32_t canvas_get_pixel (uint32_t x, uint32_t y) {
	uint32_t* lfb =  canvas->address; 
	return lfb[x + y * canvas_get_scale()];
}


void canvas_fill (uint32_t w, uint32_t h, uint32_t color) {
	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
			canvas_draw_pixel(0 + i,0 + j, color);
}


uint32_t* canvas_get_framebuffer () {
	return canvas->address;
}

uint16_t canvas_get_scanline () {
	return canvas->scanline;
}


uint32_t canvas_get_scale () {
	return canvas->scanline;
}




