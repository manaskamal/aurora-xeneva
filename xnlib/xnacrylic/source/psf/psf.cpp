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


#include <psf\psf.h>
#include <sys\mmap.h>
#include <sys\_file.h>
#include <sys\_term.h>
#include <stdlib.h>
#include <string.h>
#include <canvas.h>


uint8_t *font_data = nullptr;


void psf_register_font_lib (){
	font_data = (uint8_t*)malloc(4096);
	FILE file;
	sys_open_file (&file, "a:font.psf");
	sys_read_file (&file,font_data,file.size);
	sys_print_text ("Font opened\n");
}

//! Put a character to console output
void psf_draw_string (const char *s,int pos_x, int pos_y, uint32_t f_color, uint32_t b_color) {
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
				canvas_get_framebuffer()[line + pos_x + pos_y* canvas_get_scale()/*canvas_get_width()*/ ]=((int)*glyph) & (mask)?f_color:b_color;
				mask>>=1; line+=1;
			}
			canvas_get_framebuffer()[line + pos_x + pos_y * canvas_get_scale()/*canvas_get_width()*/]=b_color; glyph+=bpl; offs+=canvas_get_scanline();
		}
		s++; 
		pos_x++;
		kx++;
    }
}