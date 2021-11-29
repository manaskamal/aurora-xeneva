/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  screen.h -- Screen Interface for Aurora
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *==============================================
 */

#include <screen.h>

//! Architecture specific
#ifdef ARCH_X64
#include <arch\x86_64\mmngr\vmmngr.h>
#endif

display_t display;


void initialize_screen (KERNEL_BOOT_INFO *info){
	display.buffer = info->graphics_framebuffer;
	display.width = info->X_Resolution;
	display.height = info->Y_Resolution;
	display.bpp = 32;
	display.scanline = info->pixels_per_line;
#ifdef ARCH_X64
	

	//!map a shared page for fast IPC
	//map_page ((uint64_t)pmmngr_alloc(),0xFFFFD00000000000, PAGING_USER);
#endif


}

void screen_set_configuration (uint32_t width, uint32_t height) {
	display.width = width;
	display.height = height;

	//! Map a shared region for other processes to output
	for (int i = 0; i < display.width * display.height * 32 / 4096; i++)
		map_page ((uint64_t)display.buffer + i * 4096,0xFFFFF00000000000 + i * 4096, PAGING_USER);
}

uint32_t get_screen_width () {
	return display.width;
}

uint32_t get_screen_height () {
	return display.height;
}

uint32_t * get_framebuffer_addr () {
	return display.buffer;
}

uint32_t get_bpp () {
	return display.bpp;
}

uint16_t get_screen_scanline () {
	return display.scanline;
}


void draw_pixel (unsigned x, unsigned y, uint32_t color ) {
	display.buffer[x + y * display.width] = color;
}