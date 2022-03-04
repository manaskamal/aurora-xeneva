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

#include <drivers\svga\svga_screen_util.h>
#include <drivers\svga\svga3d_reg.h>
#include <drivers\svga\svga_screen.h>
#include <string.h>

#ifdef HW_SVGA

svga_screen_console g_screen;

void svga_screen_console_init (uint32_t gmr_id) {
	
	const uint32_t gmr_size = TILE_BUFFER_BYTES + MAX_FONT_SIZE;
	ppn gmr_pages = gmr_define_contiguous (gmr_id, (gmr_size + PAGE_MASK) / PAGE_SIZE);
	printf ("GMR Pages -> %x\n", gmr_pages);
	g_screen.tile_ptr.gmrId = gmr_id;
	g_screen.tile_ptr.offset = 0;
	g_screen.tile_buffer = (uint32_t*)PPN_POINTER(gmr_pages);
	printf ("Tile buffer -> %x\n", g_screen.tile_buffer);
}

void svga_screen_console_set (uint32_t screen_id, int width, int height) {
	g_screen.screen_id = screen_id;
	g_screen.screen_width = width;
	g_screen.screen_height = height;
}


void svga_draw_tile_rect (int left, int top, int right, int bottom) {

	static const SVGAGMRImageFormat format = {{{32, 24}}};
	svga_screen_define_gmrfb(g_screen.tile_ptr, TILE_SIZE * sizeof(uint32_t), format);

	static const SVGASignedPoint src_origin = {0, 0};
	SVGASignedRect dest_rect;

	for (dest_rect.top = top; dest_rect.top < bottom; dest_rect.top += TILE_SIZE) {
		dest_rect.bottom = MIN (bottom, dest_rect.top + TILE_SIZE);

		for (dest_rect.left = left; dest_rect.left < right; dest_rect.left += TILE_SIZE) {
			dest_rect.right = MIN (right, dest_rect.left + TILE_SIZE);

			if (g_screen.tile_usage.type == TILE_FILL) {
				SVGAColorBGRX color;
				color.value = g_screen.tile_usage.color;
				svga_screen_annotate_fill (color);
			}

			svga_screen_blit_from_gmrfb (&src_origin, &dest_rect, g_screen.screen_id);
		}
	}

	g_screen.tile_fence = svga_insert_fence();
}


void svga_screen_console_rect (int left, int top, 
							   int right, int bottom, uint32_t color) {

								   printf ("Drawing rect\n");
	if (g_screen.tile_usage.type != TILE_FILL || g_screen.tile_usage.color != color) {
		svga_sync_to_fence (g_screen.tile_fence);
		g_screen.tile_usage.type = TILE_FILL;
		g_screen.tile_usage.color = color;
		memset (g_screen.tile_buffer, color, TILE_BUFFER_PIXELS);
	}

	svga_draw_tile_rect (left, top, right, bottom);
}

#endif
