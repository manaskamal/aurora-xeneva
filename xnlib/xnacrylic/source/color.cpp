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