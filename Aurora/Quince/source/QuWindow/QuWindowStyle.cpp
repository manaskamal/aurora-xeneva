///! 
///!   Copyright (C) Manas Kamal Choudhury 2021
///!   
///!  QuWindowStyle -- Quince Window Decoration
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!=================================================

#include <string.h>
#include <canvas.h>
#include <acrylic.h>
#include <QuWindow\QuWindowStyle.h>
#include <color.h>

uint32_t title_bar_colors[23] = {0xff59584f, 0xff5f5d53, 0xff58564e, 0xff57554d, 0xff56544c, 0xff55534b, \
    0xff54524a, 0xff525049, 0xff514f48, 0xff504e47, 0xff4e4c45, 0xff4e4c45, \
        0xff4c4a44, 0xff4b4943, 0xff4a4842, 0xff484741, 0xff46453f, 0xff45443f, \
        0xff44433e, 0xff43423d, 0xff42413c, 0xff403f3a, 0xff3f3e3a };



void QuWindowDrawTitlebar (unsigned x, unsigned y, unsigned w) {
	for (int i = 0; i < 23; i++) {
		acrylic_draw_horizontal_line (x, y + i, w, title_bar_colors[i]);
	}

	char* title = "Untitled";
	acrylic_draw_rect_filled(x + (w/2) - ((strlen(title)*8)/2), y + 2,strlen(title)*8,21,0xFF3b3931);
	acrylic_draw_string (x + (w/2) - ((strlen(title)*8)/2), y + 2, title, 0xFF3b3931, SILVER);
}


