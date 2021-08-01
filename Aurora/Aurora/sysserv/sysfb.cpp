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


#define CA 0xFF000000
#define CB 0xFFFFFFFF
#define CD 0x00000000
unsigned int mouse_img_i[11*18] = {
    CA, CD, CD, CD, CD, CD, CD, CD, CD, CD, CD,
    CA, CA, CD, CD, CD, CD, CD, CD, CD, CD, CD,
    CA, CB, CA, CD, CD, CD, CD, CD, CD, CD, CD,
    CA, CB, CB, CA, CD, CD, CD, CD, CD, CD, CD,
    CA, CB, CB, CB, CA, CD, CD ,CD, CD, CD, CD,
    CA, CB, CB, CB, CB, CA, CD, CD, CD, CD, CD,
    CA, CB, CB, CB, CB, CB, CA, CD, CD, CD, CD,
    CA, CB, CB, CB, CB, CB, CB, CA, CD, CD, CD,
    CA, CB, CB, CB, CB, CB, CB, CB, CA, CD, CD,
    CA, CB, CB, CB, CB, CB, CB, CB, CB, CA, CD,
    CA, CB, CB, CB, CB, CB, CB, CB, CB, CB, CA,
    CA, CA, CA, CA, CB, CB, CB, CA, CA, CA, CA,
    CD, CD, CD, CD, CA, CB, CB, CA, CD, CD, CD,
    CD, CD, CD, CD, CA, CB, CB, CA, CD, CD, CD,
    CD, CD, CD, CD, CD, CA, CB, CB, CA, CD, CD,
    CD, CD, CD, CD, CD, CA, CB, CB, CA, CD, CD,
    CD, CD, CD, CD, CD, CD, CA, CB, CA, CD, CD,
    CD, CD, CD, CD, CD, CD, CD, CA, CA, CD, CD 
};

uint32_t* sys_get_fb_mem () {
	x64_cli();
	return svga_get_fb_mem();
}


void sys_fb_update () {
	x64_cli();
	svga_update (0,0,get_screen_width(),get_screen_height());
}

void sys_fb_move_cursor (uint32_t x, uint32_t y) {
	x64_cli();
	
	SVGAFifoCmdDefineAlphaCursor cursor;
	cursor.id = 0;
	cursor.hotspotX = 0;
	cursor.hotspotY = 0;
	cursor.width = 11;
	cursor.height = 18;
	uint32_t *and_data;
	svga_begin_define_alpha_cursor (&cursor, (void**)&and_data);

	/*SVGAFifoCmdDefineCursor cursor;
	cursor.id = 0;
	cursor.hotspotX = 24;
	cursor.hotspotY = 24;
	cursor.width = 11;
	cursor.height = 18;
	cursor.andMaskDepth = 1;
	cursor.xorMaskDepth = 1;*/

	

	/*for (int y = 0; y< 100; y++){
		for (int x = 0; x< 100; x++){
			uint8_t alpha = y * 255 / 10;
			uint8_t luma = alpha;
			*(data++) = (alpha << 24) | (luma << 16) | (luma << 8) | luma;
		}
	}*/

	//svga_begin_define_cursor (&cursor, (void**)&and_data, (void**)&xor_data);

	for (int _y = 0; _y < cursor.height; _y++) {
		for ( int _x = 0; _x < cursor.width; _x++) {
			//if ( mouse_img_i[_y * 11 + _x] & 0xFF000000){
				*(and_data++) = mouse_img_i[_y * 11 + _x];
			//	*(xor_data++) = _y * 127;
			//}
		}
	}
    svga_move_cursor(true, x,y,0);
	svga_fifo_commit_all();
	
}