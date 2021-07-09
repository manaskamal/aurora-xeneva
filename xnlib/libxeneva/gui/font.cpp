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

#include <gui\font.h>
#include <mm.h>
#include <gui\drawer.h>

uint8_t* font_data = nullptr;

void register_font_lib (){
	valloc(0xFFFFFFFFA0000000);
	font_data = (uint8_t*)0xFFFFFFFFA0000000;
	FILE file;
	sys_open_file (&file, "font.psf");
	sys_read_file (&file,font_data,file.size);
}

//! Put a character to console output
void draw_string (const char *s,int pos_x, int pos_y, uint32_t f_color, uint32_t b_color) {
	psf2_t *font = (psf2_t*)font_data;
    int x,y,kx=0,line,mask,offs;
    int bpl=(font->width+7)/8;
  
	while(*s) {
		unsigned char *glyph = (unsigned char*)font_data + font->headersize + 
				(*s>0&&*s<font->numglyph?*s:0)*font->bytesperglyph;
		offs = kx * (font->width + 1);
		for(y=0;y<font->height;y++) {
			line=offs; mask=1<<(font->width-1);
			for(x=0;x<font->width;x++) {
				drawer_get_framebuffer()[line + pos_x + pos_y* drawer_get_screen_width() ]=((int)*glyph) & (mask)?f_color:b_color;
				mask>>=1; line+=1;
			}
			drawer_get_framebuffer()[line + pos_x + pos_y * drawer_get_screen_width()]=b_color; glyph+=bpl; offs+=drawer_get_scanline();
		}
		s++; 
		pos_x++;
		kx++;
    }
}


