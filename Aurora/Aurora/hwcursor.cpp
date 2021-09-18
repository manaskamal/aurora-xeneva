///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  hwcursor.cpp -- Hardware accelerated cursor management
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!==============================================================

#include <hwcursor.h>
#include <_null.h>

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



void hw_move_cursor (uint32_t *mouse_image, uint32_t xcoord, uint32_t ycoord) {
	x64_cli();

	
	SVGAFifoCmdDefineAlphaCursor cursor;
	cursor.id = 0;
	cursor.hotspotX = 0;
	cursor.hotspotY = 0;
	if (mouse_image == NULL){
		cursor.width = 11;
		cursor.height = 18;
	}else{
		cursor.width = 24;
		cursor.height = 24;
	}


	uint32_t *and_data;
	svga_begin_define_alpha_cursor (&cursor, (void**)&and_data);

	for (int _y = 0; _y < cursor.height; _y++) {
		for ( int _x = 0; _x < cursor.width; _x++) {
			//if ( mouse_img_i[_y * 11 + _x] & 0xFF000000){
			if (mouse_image == NULL)
				*(and_data++) = mouse_img_i[_y * 11 + _x];
			else 
				*(and_data++) = mouse_image[_y * cursor.width + _x];
			//	*(xor_data++) = _y * 127;
			//}
		}
	}
    svga_move_cursor(true, xcoord,ycoord,0);
	svga_fifo_commit_all();
	
}