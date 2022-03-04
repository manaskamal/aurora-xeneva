/**
 * Copyright (C) Manas Kamal Choudhury 2021
 *
 * svga_screen.h -- SVGA Screen util
 *
 * /PROJECT - Aurora {Xeneva}
 * /AUTHOR  - Manas Kamal Choudhury
 *
 * ===========================================
 */

#ifndef __SVGA_SCREEN_UTIL_H__
#define __SVGA_SCREEN_UTIL_H__

#include <stdint.h>
#include <drivers\svga\vmsvga.h>
#include <drivers\svga\gmr.h>

#ifdef HW_SVGA

#define TILE_SIZE   64
#define TILE_BUFFER_PIXELS  (TILE_SIZE * TILE_SIZE)
#define TILE_BUFFER_BYTES   (TILE_BUFFER_PIXELS * sizeof(uint32))

#define MAX_FONT_SIZE  200000

#define BACKGROUND_COLOR  0x000000
#define MARGIN_SIZE   10

#define TILE_OTHER  0
#define TILE_FILL   1
#define TILE_CHECKERBOARD 2

typedef struct {
	uint8_t width;
	uint8_t height;
	uint8_t reserved[2];
	uint32_t offset;
} char_metrics;


typedef struct _screen_console_ {
	SVGASignedPoint position;
	uint32_t screen_id;
	uint32_t screen_width;
	uint32_t screen_height;

	SVGAGuestPtr  tile_ptr;
	uint32_t *tile_buffer;
	SVGAGuestPtr  font_ptr;
	char_metrics *metrics;

	uint32_t   tile_fence;
	struct {
		uint32_t type;
		uint32_t  color;
	}tile_usage;
} svga_screen_console;

extern void svga_screen_console_init (uint32_t gmr_id);
extern void svga_screen_console_set (uint32_t screen_id, int width, int height);
extern void svga_screen_console_rect (int left, int top, int right, int bottom, uint32_t col);
#endif

#endif