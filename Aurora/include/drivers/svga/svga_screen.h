/**
 * Copyright (C) Manas Kamal Choudhury 2021
 *
 * svga_screen -- VMware svga screen object
 *
 * /PROJECT - Aurora {Xeneva}
 * /AUTHOR  - Manas Kamal Choudhury
 *
 * ==============================================
 */

#ifndef __SVGA_SCREEN_H__
#define __SVGA_SCREEN_H__

#include <drivers\svga\vmsvga.h>
#include <drivers\svga\svga_reg.h>


extern void svga_screen_init ();
extern void svga_screen_create (SVGAScreenObject *screen);
extern void svga_screen_define (const SVGAScreenObject *screen);
extern void svga_destroy (uint32_t id);

extern void svga_screen_define_gmrfb (SVGAGuestPtr ptr, uint32_t bytes_per_line, SVGAGMRImageFormat format);
extern void svga_screen_blit_from_gmrfb (const SVGASignedPoint *srcOrigin, const SVGASignedRect *destRect,
										 uint32_t destScreen);
extern void svga_screen_blit_to_gmrfb (const SVGASignedPoint *destOrigin, const SVGASignedRect *srcRect,
									   uint32_t srcScreen);

extern void svga_screen_annotate_fill (SVGAColorBGRX color);
extern void svga_annotate_copy (const SVGASignedPoint *srcOrigin, uint32_t srcScreen);

extern void svga_paint_screen (uint32_t color, int x, int y,int width, int height);

#endif