/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  font.h -- Font Library for XNWidget and XNGui
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ==================================================
 */

#ifndef __FONT_H__
#define __FONT_H__


#include <xnsys.h>


#pragma pack (push, 1)
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
#pragma pack (pop)


extern void register_font_lib ();
extern void draw_string (const char *string,int pos_x, int pos_y, uint32_t f_color, uint32_t b_color);

#endif