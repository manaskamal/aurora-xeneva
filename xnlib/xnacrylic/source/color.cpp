///
///   Copyright (C) Manas Kamal Choudhury 2021
///
///   color.cpp -- Color functions
///
///   /PROJECT - Aurora's Xeneva
///   /AUTHOR  - Manas Kamal Choudhury
///
///===============================================

#include <color.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <canvas.h>

static const int AMASK = 0xFF000000;
static const int RBMASK = 0x00FF00FF;
static const int GMASK = 0x0000FF00;
static const int AGMASK = AMASK | GMASK;
static const int ONEALPHA = 0x01000000;

uint32_t alpha_blend (uint32_t color1, uint32_t color2) {

	uint32_t a = (color2 & AMASK) >> 24;

	if (a == 0)
		return color1;
	else if (a == 255)
		return color2;
	else {
		uint32_t na = 255 - a;
		uint32_t rb = ((na * (color1 & RBMASK)) + (a * (color2 & RBMASK))) >> 8;
		uint32_t ag = (na * ((color1 & AGMASK) >> 8)) + (a * (ONEALPHA | ((color2 & GMASK) >> 8)));

		return ((rb & RBMASK) | (ag & AGMASK));
	}
}

uint32_t make_col (uint8_t red, uint8_t green, uint8_t blue) {
	red = max(red, 0);
	red = min(red, 255);
	green = max(green, 0);
	green = min(green, 255);
	blue = max(blue, 0);
	blue = min(blue, 255);

	uint32_t ret = (red << 16) | (green << 8) | (blue << 0);
	return ret;

}


uint32_t trans_color (uint32_t c1, uint32_t c2, float d) {
	if (d < 0) d = 0;
	if (d > 1) d = 1;
	return make_col (
		((c1 >> 16 & 0x000000FF) * (1 - d))+ ((c2 >> 16 & 0x000000FF) * d),
		((c1 >> 8 & 0x000000FF) * (1 - d)) + ((c2 >> 8 & 0x000000FF) * d),
		((c1 >> 0 & 0x000000FF) * (1 - d)) + ((c2 >> 0 & 0x000000FF) * d));
}


float pifdist (int x1, int y1, int x2, int y2) {
	float x = x1 - x2;
	float y = y1 - y2;
	return sqrtf (x * x + y * y);
}

void radial_gradient (int g_w, int g_h, uint32_t c1, uint32_t c2, int x1, int y1, float r) {
	int x_step = g_w / 200.0;
	int y_step = g_h / 200.0;
	if (x_step < 1) x_step = 1;
	if (y_step < 1) y_step = 1;

	for (uint32_t y = 0; y < g_h; y+= y_step) {
		for (uint32_t x = 0; x < g_w; x += x_step) {
			uint32_t c = trans_color (c1, c2, pifdist(x1, y1, x, y) / r);
			for (int i = 0; i < x_step; i++) {
				for (int j = 0; j < y_step; j++) {
					canvas_draw_pixel (x+i, y+j, c);
				}
			}
		}
	}
}

void linear_gradient (int x1, int y1, int x2, int y2, uint32_t col1, uint32_t col2) {
	float d= 0.0f;
	for (int j = 0; j < y2; j++) {
		for (int i= 0; i < x2; i++) {
			uint32_t c = trans_color (col1, col2, d);
			canvas_draw_pixel (x1+i, y1+j, c);
		}
		d+= 0.1f;
	}
}