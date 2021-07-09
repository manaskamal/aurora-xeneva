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
#include <screen.h>

uint32_t* sys_get_fb_mem () {
	x64_cli();
	return svga_get_fb_mem();
}


void sys_fb_update () {
	x64_cli();
	svga_update (0,0,get_screen_width(),get_screen_height());
}