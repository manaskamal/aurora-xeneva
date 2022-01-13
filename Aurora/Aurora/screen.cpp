/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  screen.h -- Screen Interface for Aurora
 *
 *  Screen Interface manages every graphics devices registered to the
 *  system, it can be simple VESA, GOP or other hardware accelerated
 *  graphics card. Screen interface maps the framebuffer to specific
 *  virtual address and provides interfaces for application to draw 
 *  pixel
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *==============================================
 */

#include <screen.h>
#include <fs\vfs.h>
#include <arch\x86_64\mmngr\kheap.h>

//! Architecture specific
#ifdef ARCH_X64
#include <arch\x86_64\mmngr\vmmngr.h>
#endif

display_t display;

int screen_io_query (vfs_node_t* node, int code, void* arg);


/**
 * initialize_screen -- initialize the screen
 * @param info -- the boot information pointer passed by xnldr
 */
void initialize_screen (KERNEL_BOOT_INFO *info){
	display.buffer = info->graphics_framebuffer;
	display.width = info->X_Resolution;
	display.height = info->Y_Resolution;
	display.bpp = 32;
	display.scanline = info->pixels_per_line;
	display.size = info->fb_size;

	/**
	 * register the device node for screen interface
	 */
	vfs_node_t * svga = (vfs_node_t*)pmmngr_alloc(); 
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


/**
 * screen_set_configuration -- simply set the mode of the screen
 * and map the virtual address space to be used
 * @param width -- mode width
 * @param height -- mode height
 */
void screen_set_configuration (uint32_t width, uint32_t height) {
	display.width = width;
	display.height = height;
	//! Map a shared region for other processes to output
	for (int i = 0; i < display.size / 4096 ; i++)
		map_page ((uint64_t)display.buffer + i * 4096, 0xFFFFD00000200000 + i * 4096, PAGING_USER);

}

/**
 * get_screen_width -- returns the current width of the screen
 * @return -- width of the screen
 */
uint32_t get_screen_width () {
	return display.width;
}

/**
 * get_screen_height -- returns the current height of the screen
 * @return -- height of the screen
 */
uint32_t get_screen_height () {
	return display.height;
}

/**
 * get_framebuffer_addr -- returns the current framebuffer address of
 * the screen
 * @return -- framebuffer address
 */
uint32_t * get_framebuffer_addr () {
	return display.buffer;
}

/**
 * get_bpp -- returns the current bits per pixel
 * @return -- bits/pixel of the screen
 */
uint32_t get_bpp () {
	return display.bpp;
}

/**
 * get_screen_scanline -- return the current pixles per line of the screen
 * @return -- scanline of the screen
 */
uint16_t get_screen_scanline () {
	return display.scanline;
}

/**
 * get_fb_size -- returns the current framebuffer size of the screen in (bytes)
 * @return -- framebuffer size
 */
uint32_t get_fb_size () {
	return display.size;
}

/**
 * draw_pixel -- low level pixel drawing interface
 * @param x -- x position of the pixel
 * @param y -- y position of the pixel
 * @param color -- color of the pixel
 */
void draw_pixel (unsigned x, unsigned y, uint32_t color ) {
	display.buffer[x + y * display.width] = color;
}

/**
 * screen_io_query -- system call interface for more device feature
 * callbacks
 * @param node -- virtual file system object pointer
 * @param code -- code of the feature
 * @param arg -- extra arguments to use
 */
int screen_io_query (vfs_node_t* node, int code, void* arg) {
	int ret = 0;
	switch (code) {
	case SCREEN_GETWIDTH:{
		uint32_t width = display.width;
		ret = width;
		break;
	}
	case SCREEN_GETHEIGHT:{
		uint32_t height = display.height;
		ret = height;
		break;
	}
	case SCREEN_GETBPP:{
		uint32_t bpp = display.bpp;
		ret =  bpp;
		break;
	 }
	case SCREEN_GET_SCANLINE: {
		uint16_t scanline = display.scanline;
		ret =  scanline;
		break;
	}
	}

	return ret;
}