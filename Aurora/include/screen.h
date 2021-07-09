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

#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <_xnboot.h>
#include <stdint.h>
#include <stdio.h>

//! Display structure
typedef struct __display__ {
	uint32_t width;
	uint32_t height;
	uint32_t *buffer;
	uint32_t bpp;
	uint16_t scanline;
}display_t;

//!Simple Display Interface for User mode applications
extern void initialize_screen (KERNEL_BOOT_INFO *info);
extern void screen_set_configuration (uint32_t width, uint32_t height);
extern uint32_t  get_screen_width ();
extern uint32_t  get_screen_height ();
extern uint32_t *get_framebuffer_addr();
extern uint32_t  get_bpp ();
extern uint16_t get_screen_scanline ();
extern void draw_pixel(unsigned x, unsigned y, uint32_t color);

#endif