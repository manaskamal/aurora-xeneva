/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  psf.h -- PC Screen Font
 *
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ==================================================
 */

#ifndef __PSF_FONT_H__
#define __PSF_FONT_H__

#include <stdint.h>

typedef struct {
    uint32_t magic;
    uint32_t version;
    uint32_t headersize;
    uint32_t flags;
    uint32_t numglyph;
    uint32_t bytesperglyph;
    uint32_t height;
    uint32_t width;
    uint8_t glyphs;
}psf2_t;

extern void psf_register_font_lib ();
extern void psf_draw_string (const char *s,int pos_x, int pos_y, uint32_t f_color, uint32_t b_color);

#endif