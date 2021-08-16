/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  console.h -- Virtual Console
 *
 *  /PROJECT - Aurora v1.0 {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *====================================================
 */

#include <console.h>
#include <stdio.h>

//! default kernel console
static uint16_t scanline = 0;
static uint16_t screen_width = 0;
static uint16_t screen_height = 0;
static uint32_t *fb = nullptr;
static int console_x = 0;
static int console_y = 0;
static uint8_t *psf_data = nullptr;

//! Initialize console device
void console_initialize (PKERNEL_BOOT_INFO info) {
	console_x = 0;
	console_y = 0;
	scanline = info->pixels_per_line;
	screen_width = info->X_Resolution;
	screen_height = info->Y_Resolution;
	fb = info->graphics_framebuffer;
	psf_data = info->psf_font_data;
}

//! Put a character to console output
void putc (char c) {
	psf2_t *font = (psf2_t*)psf_data;
    int x,y,kx=0,line,mask,offs;
    int bpl=(font->width+7)/8;
  
	
	unsigned char *glyph = (unsigned char*)psf_data + font->headersize + 
				(c>0&&c<font->numglyph?c:0)*font->bytesperglyph;
	offs = kx * (font->width + 1);// * 4);
	for(y=0;y<font->height;y++) {
		line=offs; mask=1<<(font->width-1);
		for(x=0;x<font->width;x++) {
			fb[line + console_x + console_y * screen_width ]=((int)*glyph) & (mask)?0xFFFFFF:0;
			mask>>=1; line+=1;
		}
		fb[line + console_x + console_y * screen_width]=0; glyph+=bpl; offs+=scanline;
	}
	console_x += font->width + 1;
}


void console_pixel(uint32_t col, unsigned x, unsigned y)
{
	fb[x + y * screen_width] = col;
}


//! Prints string to console output
void puts(char *s){
	
	psf2_t *font = (psf2_t*)psf_data;
    int x,y,line,mask,offs;
    int bpl=(font->width+7)/8;
    while(*s) {
		if (*s == '\n') {
			console_y += 16;
			console_x = 0;
		} else if (*s == '\b') {
			if (console_x > 0) {
				console_x--;
			}
		}else {
			unsigned char *glyph = (unsigned char*)psf_data + font->headersize + 
				(*s>0&&*s<font->numglyph?*s:0)*font->bytesperglyph;
			offs = console_x * (font->width + 1);// * 4);
			for(y=0;y<font->height;y++) {
				line=offs; mask=1<<(font->width-1);
				for(x=0;x<font->width;x++) {
					fb[line  + console_y * screen_width ]=((int)*glyph) & (mask)?0xFFFFFF:0;
					mask>>=1; line+=1;
				}
				fb[line  + console_y * screen_width]=0; glyph+=bpl; offs+=scanline;
			}
			console_x++;
		}
		s++; 
    }

	//!Scroll is needed
}

