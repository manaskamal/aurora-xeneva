/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  sysfb.cpp -- Framebuffer system call
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ==================================================
 */

#include <stdint.h>
#include <arch\x86_64\mmngr\vmmngr.h>
#include <drivers\svga\vmsvga.h>
#include <hwcursor.h>
#include <screen.h>



uint32_t* sys_get_fb_mem () {
	x64_cli();
#ifdef HW_SVGA
	return svga_get_fb_mem();
#else
	return 0;
#endif
}


void sys_fb_update () {
	x64_cli();
#ifdef HW_SVGA
	svga_update (0,0,get_screen_width(),get_screen_height());
#endif
}

void sys_fb_move_cursor (uint32_t x, uint32_t y) {
	x64_cli();
#ifdef HW_SVGA
	hw_move_cursor (NULL, x, y);
#endif
}