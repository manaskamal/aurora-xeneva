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
#include <proc.h>

//! Architecture specific
#ifdef ARCH_X64
#include <arch\x86_64\mmngr\paging.h>
#endif

display_t *display;

int screen_io_query (vfs_node_t* node, int code, void* arg);


/**
 * AuInitializeScreen -- initialize the screen
 * @param info -- the boot information pointer passed by xnldr
 */
void AuInitializeScreen (KERNEL_BOOT_INFO *info){
	display = (display_t*)malloc(sizeof(display_t));
	memset(display, 0, sizeof(display_t));
	display->buffer = info->graphics_framebuffer;
	display->width = info->X_Resolution;
	display->height = info->Y_Resolution;
	display->bpp = 32;
	display->scanline = info->pixels_per_line;
	display->pitch = 4*info->pixels_per_line;
	display->size = info->fb_size;
	display->screen_mngr_pid = -1;

	/**
	 * register the device node for screen interface
	 */
	vfs_node_t * svga = (vfs_node_t*)malloc(sizeof(vfs_node_t)); //AuPmmngrAlloc(); 
	strcpy (svga->filename, "fb");
	svga->size = 0;
	svga->eof = 0;
	svga->pos = 0;
	svga->current = 0;
	svga->flags = FS_FLAG_GENERAL | FS_FLAG_DEVICE;
	svga->status = 0;
	svga->open = 0;
	svga->read = 0;
	svga->write = 0;
	svga->read_blk = 0;
	svga->ioquery = screen_io_query;
	vfs_mount ("/dev/fb", svga, 0);

	/* clear the screen */
	for (int w = 0; w < info->X_Resolution; w++) {
		for (int h = 0; h < info->Y_Resolution; h++) {
			info->graphics_framebuffer[w + h * info->X_Resolution] = 0x00000000;
		}
	}

	AuScreenMap(info->X_Resolution, info->Y_Resolution);
}


/**
 * screen_set_configuration -- simply set the mode of the screen
 * and map the virtual address space to be used
 * @param width -- mode width
 * @param height -- mode height
 */
void AuScreenMap (uint32_t width, uint32_t height) {
	display->width = width;
	display->height = height;
	//! Map a shared region for other processes to output
	for (int i = 0; i < display->size / 4096; i++)
		AuMapPage((uint64_t)display->buffer + i * 4096, 0xFFFFD00000200000 + i * 4096, PAGING_USER);

	display->buffer = (uint32_t*)0xFFFFD00000200000;
}

/**
 * AuGetScreenWidth -- returns the current width of the screen
 * @return -- width of the screen
 */
uint32_t AuGetScreenWidth () {
	return display->width;
}

/**
 * AuGetScreenHeight -- returns the current height of the screen
 * @return -- height of the screen
 */
uint32_t AuGetScreenHeight () {
	return display->height;
}

/**
 * AuGetFramebuffer -- returns the current framebuffer address of
 * the screen
 * @return -- framebuffer address
 */
uint32_t * AuGetFramebuffer () {
	return display->buffer;
}

/**
 * AuGetScreenBPP -- returns the current bits per pixel
 * @return -- bits/pixel of the screen
 */
uint32_t AuGetScreenBPP () {
	return display->bpp;
}

/**
 * get_screen_scanline -- return the current pixles per line of the screen
 * @return -- scanline of the screen
 */
uint16_t AuGetScreenScanline() {
	return display->scanline;
}

/**
 * AuGetFramebufferSize -- returns the current framebuffer size of the screen in (bytes)
 * @return -- framebuffer size
 */
uint32_t AuGetFramebufferSize() {
	return display->size;
}

/**
 * AuDrawPixel -- low level pixel drawing interface
 * @param x -- x position of the pixel
 * @param y -- y position of the pixel
 * @param color -- color of the pixel
 */
void AuDrawPixel (unsigned x, unsigned y, uint32_t color ) {
	display->buffer[x + y * display->width] = color;
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
		uint32_t width = display->width;
		ret = width;
		break;
	}
	case SCREEN_GETHEIGHT:{
		uint32_t height = display->height;
		ret = height;
		break;
	}
	case SCREEN_GETBPP:{
		uint32_t bpp = display->bpp;
		ret =  bpp;
		break;
	 }
	case SCREEN_GET_SCANLINE: {
		uint16_t scanline = display->scanline;
		ret =  scanline;
		break;
	}
	case SCREEN_GET_PITCH:
		ret = display->pitch;
		break;

	case SCREEN_REGISTER_MNGR: {
		if (display->screen_mngr_pid == -1) {
			thread_t* thr = get_current_thread();
			display->screen_mngr_pid = thr->id;
		}
		break;
    }
	}
	return ret;
}

/*
 * AuGetScreenMngrID -- returns screen manager process
 * id 
 */
uint16_t AuGetScreenMngrID () {
	return display->screen_mngr_pid;
}