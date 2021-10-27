/**
 *   Copyright (C) Manas Kamal Choudhury 2021
 *
 *  acrylic.cpp -- Acrylic 2d Graphics library
 *
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ==============================================
 */

#include <acrylic.h>
#include <image.h>
#include <color.h>
#include <psf\psf.h>
#include <arrayfont.h>

void acrylic_draw_rect_filled (unsigned x, unsigned y, unsigned w, unsigned h, uint32_t col) {
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			canvas_draw_pixel(x + i, y + j, col);
		}
		
	}
}


void acrylic_draw_vertical_line (unsigned x, unsigned y, unsigned length, uint32_t color) {
	acrylic_draw_rect_filled(x,y,1,length,color);
}

void acrylic_draw_horizontal_line (unsigned x, unsigned y, unsigned length, uint32_t color) {
	acrylic_draw_rect_filled (x,y,length,1,color);
}

void acrylic_draw_rect_unfilled (int x, int y, int width, int height, uint32_t color) {
	acrylic_draw_horizontal_line ( x, y, width, color); //top
	acrylic_draw_vertical_line( x, y+1, height -2, color); //left
	acrylic_draw_horizontal_line(x, y + height - 1, width, color); //bottom
	acrylic_draw_vertical_line (x + width - 1, y + 1, height - 2, color); //right
}


void acrylic_draw_filled_circle (int o_x, int o_y, int radius, uint32_t fill_color) {
	for(int y = -radius; y <= radius; y++)
		for (int x = -radius; x <= radius; x++)
			if(x * x +y*y <= radius * radius)
				canvas_draw_pixel (o_x + x, o_y + y, fill_color);
}


void acrylic_draw_image (Image *img, unsigned x, unsigned y) {
	uint8_t* data = img->image;
	uint32_t w = img->width;
	uint32_t h = img->height;
	for (int i = 0; i < h; i++) {
		for (int k = 0; k < w; k++) {
			int j = k + i * w;
			uint8_t r = data[j * 3];        //data[i * 3];
			uint8_t g = data[j * 3 + 1];        //data[i * 3 + 1];
			uint8_t b = data[j * 3 + 2];       //data[i * 3 + 2];
			//uint8_t a = data[j * 3 + 3];
			uint32_t rgba =  ((r<<16) | (g<<8) | (b)) & 0x00ffffff;  //0xFF000000 | (r << 16) | (g << 8) | b;
			rgba = rgba | 0xff000000;
			canvas_draw_pixel (x + k, y + i,rgba);
			j++;
		}
	}
}

void acrylic_draw_string (unsigned x, unsigned y, char *text, uint32_t b_color, uint32_t f_color) {
	psf_draw_string (text, x, y, f_color, b_color);
}


void acrylic_draw_arr_font (unsigned x, unsigned y, char c, uint32_t color) {
	uint8_t shift_line;
	for (int i = 0; i < 12; i++) { //h
		shift_line = font_array[i * 128 + c];
		
		for (int j = 0; j < 8; j++) { //w

			if (shift_line & 0x80)
				canvas_get_framebuffer()[(i + y) * canvas_get_width() + (j + x)] = color;
			shift_line <<= 1;
		}
	}

}

void acrylic_draw_arr_string (unsigned x, unsigned y, char *text, uint32_t color) {
	for (; *text; x += 8)
		acrylic_draw_arr_font(x, y, *(text)++, color);
}

