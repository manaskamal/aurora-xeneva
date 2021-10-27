///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  clientctx.cpp -- Client Context used for double buffer painting
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!======================================================================


#include <clientctx.h>
#include <canvas.h>

extern uint8_t font_array[] ;

void cc_draw_pixel (uint32_t* canvas, int x, int y, uint32_t color) {
	uint32_t *lfb =  canvas;      
	lfb[x + y * canvas_get_width()] = color;
}

void cc_draw_arr_font (uint32_t *canvas,unsigned x, unsigned y, char c, uint32_t color) {
	uint8_t shift_line;
	for (int i = 0; i < 12; i++) { //h
		shift_line = font_array[i * 128 + c];
		
		for (int j = 0; j < 8; j++) { //w

			if (shift_line & 0x80)
				canvas[(i + y) * canvas_get_width() + (j + x)] = color;
			shift_line <<= 1;
		}
	}

}

void cc_draw_arr_string (uint32_t *canvas,unsigned x, unsigned y, char *text, uint32_t color) {
	for (; *text; x += 8)
		cc_draw_arr_font(canvas, x, y, *(text)++, color);
}



