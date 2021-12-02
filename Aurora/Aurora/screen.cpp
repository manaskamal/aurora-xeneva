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
#include <fs\vfs.h>
#include <mm.h>

//! Architecture specific
#ifdef ARCH_X64
#include <arch\x86_64\mmngr\vmmngr.h>
#endif

display_t display;

int screen_io_query (vfs_node_t* node, int code, void* arg);


void initialize_screen (KERNEL_BOOT_INFO *info){
	display.buffer = info->graphics_framebuffer;
	display.width = info->X_Resolution;
	display.height = info->Y_Resolution;
	display.bpp = 32;
	display.scanline = info->pixels_per_line;
	display.size = info->fb_size;

	vfs_node_t * svga = (vfs_node_t*)malloc(sizeof(vfs_node_t));
	strcpy (svga->filename, "fb");
	svga->size = 0;
	svga->eof = 0;
	svga->pos = 0;
	svga->current = 0;
	svga->flags = FS_FLAG_GENERAL;
	svga->status = 0;
	svga->open = 0;
	svga->read = 0;
	svga->write = 0;
	svga->read_blk = 0;
	svga->ioquery = screen_io_query;
	vfs_mount ("/dev/fb", svga);
}

void screen_set_configuration (uint32_t width, uint32_t height) {
	display.width = width;
	display.height = height;
	//! Map a shared region for other processes to output
	for (int i = 0; i < display.size / 4096 ; i++)
		map_page ((uint64_t)display.buffer + i * 4096, 0xFFFFD00000200000 + i * 4096, PAGING_USER);

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

uint32_t get_fb_size () {
	return display.size;
}

void draw_pixel (unsigned x, unsigned y, uint32_t color ) {
	display.buffer[x + y * display.width] = color;
}


int screen_io_query (vfs_node_t* node, int code, void* arg) {
	switch (code) {
	case SCREEN_GETWIDTH:{
		uint32_t width = display.width;
		return width;
		break;
	}
	case SCREEN_GETHEIGHT:{
		uint32_t height = display.height;
		return height;
		break;
	}
	case SCREEN_GETBPP:{
		uint32_t bpp = display.bpp;
		return bpp;
		break;
	 }
	case SCREEN_GET_SCANLINE: {
		uint16_t scanline = display.scanline;
		return scanline;
		break;
	}
	}
}