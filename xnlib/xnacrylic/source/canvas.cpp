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
#include <string.h>
#include <buffer.h>
#include <sys\_file.h>
#include <fastcpy.h>

bool double_buffer = true;
int svga_fd = 0;

canvas_t *create_canvas (int width, int height) {
	svga_fd = sys_open_file ("/dev/svga", NULL);
	uint32_t s_width = ioquery(svga_fd,SVGA_GET_WIDTH,NULL);
	uint32_t s_height = ioquery(svga_fd, SVGA_GET_HEIGHT, NULL);
	uint32_t bpp = ioquery(svga_fd, SVGA_GET_BPP, NULL);
	uint16_t scanline = ioquery(svga_fd, SVGA_GET_SCANLINE, NULL);

	canvas_t *canvas = (canvas_t*)malloc(sizeof(canvas_t));
	uint32_t *address = NULL;
	if (double_buffer)
		address = acrylic_allocate_buffer(width * height * 32);
		/*for (int i = 0; i < (width * height * 32) / 4096; i++)
			valloc(0x0000600000000000 + i * 4096);*/

	canvas->width = s_width;
	canvas->height = s_height;
	canvas->bpp = bpp;
	canvas->scanline = scanline;
	canvas->ctx_width = width;
	canvas->ctx_height = height;
	if (double_buffer)
		canvas->address = address;   //0x0000600000000000;
	return canvas;
}

canvas_t* canvas_initialize (int width, int height) {
	return create_canvas (width, height);
}

void canvas_set_double_buffer (bool enable) {
	double_buffer = enable;
}


bool canvas_is_double_buffered() {
	return double_buffer;
}

void canvas_set_address (canvas_t * canvas,unsigned int* address) {
	if (double_buffer == false)
		canvas->address = address;
}


void canvas_set_width (canvas_t * canvas,uint32_t width) {
	canvas->width = width;
}

void canvas_set_height (canvas_t * canvas,uint32_t height) {
	canvas->height = height;
}

uint32_t canvas_get_width (canvas_t * canvas) {
	return canvas->width;
}

uint32_t canvas_get_height (canvas_t * canvas) {
	return canvas->height;
}

void canvas_screen_update (canvas_t * canvas,uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
	uint32_t* lfb = (uint32_t*)0xFFFFF00000000000;
	/*for (int i=0; i < w; i++) {	
		for (int j=0; j < h; j++){
			if (lfb[(x + i) + (y + j) * canvas_get_scale()] != canvas->address[(x + i) + (y + j) * canvas_get_scale()]) {
			uint32_t color = canvas->address[(x + i) + (y + j) * canvas_get_scale()];
			lfb[(x + i) + (y + j) * canvas_get_scale()] = color;
			}
		}
	}*/

	for (int i = 0; i < h; i++)
		fastcpy (lfb + (y + i) * canvas->width + x,canvas->address + (y + i) * canvas->width + x, w * 4);

	svga_io_query_t query; // = (svga_io_query_t*)malloc(sizeof(svga_io_query_t));
	query.value = x;
	query.value2 = y;
	query.value3 = w;
	query.value4 = h;
	ioquery(svga_fd, SVGA_UPDATE, &query);
	//free(query);
}


void canvas_draw_pixel (canvas_t * canvas,uint32_t x, uint32_t y, uint32_t color) {
	unsigned int *lfb =  canvas->address;      
	lfb[x + y * canvas_get_width(canvas)] = color;
}


uint32_t canvas_get_pixel (canvas_t * canvas,uint32_t x, uint32_t y) {
	unsigned int* lfb =  canvas->address; 
	return lfb[x + y * canvas_get_scale(canvas)];
}


void canvas_fill (canvas_t * canvas,uint32_t w, uint32_t h, uint32_t color) {
	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
			canvas_draw_pixel(canvas,0 + i,0 + j, color);
}


unsigned int* canvas_get_framebuffer (canvas_t * canvas) {
	return canvas->address;
}

uint16_t canvas_get_scanline (canvas_t * canvas) {
	return canvas->scanline;
}


uint32_t canvas_get_scale (canvas_t * canvas) {
	return canvas->width;
}

int canvas_get_fd () {
	return svga_fd;
}




