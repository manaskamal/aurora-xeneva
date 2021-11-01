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
#include <font.h>
#include <color.h>
#include <sys\_term.h>

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


void cc_font_draw_string (uint32_t* canvas, char* string, int x, int y, uint32_t color) {
	Font *font = acrylic_get_system_font();
	int xoff = x;
	int yoff = y;

	while(*string) {
		char c = *string++;

		const uint8_t* charData = (uint8_t*)(font->data + font->offsetTable[(int)c - 32]);
		const uint8_t width = charData[0];
		const uint8_t height = charData[1];

		for (uint8_t px = 0; px < width; px++) {
			for (uint8_t py = 0; py < height; py++) {

				uint8_t d = charData[py * width + px + 2];

				/*if (d == 0)
					continue;*/

			//	if (d == 255)
					//cc_draw_pixel (canvas,px + xoff, py + yoff, color);
				/*else*/
					cc_draw_pixel (canvas,px + xoff, py + yoff, alpha_blend(color,WHITE));
				//}
			}
		}
		xoff += width;
	}
}

void cc_font_draw_char (uint32_t* canvas, char string, int x, int y, uint32_t color) {
	Font *font = acrylic_get_system_font();
	int xoff = x;
	int yoff = y;


	const uint8_t* charData = (uint8_t*)(font->data + font->offsetTable[(int)string - 32]);
	const uint8_t width = charData[0];
	const uint8_t height = charData[1];

	for (uint8_t px = 0; px < width; px++) {
		for (uint8_t py = 0; py < height; py++) {

			uint8_t d = charData[py * width + px + 2];
			
			if (d == 0)
				continue;
          //  sys_print_text ("D Value -> %d\n", d);
			/*if (d == 255)*/
				cc_draw_pixel (canvas,px + xoff, py + yoff, color);
			/*else*/
				//cc_draw_pixel (canvas,px + xoff, py + yoff, alpha_blend(WHITE, color));
				//}
		}
	}
}




