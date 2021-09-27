///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   QuButton.h -- Quince Button object
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///!
///!=================================================

#include <QuButton.h>
#include <acrylic.h>
#include <stdlib.h>
#include <string.h>
#include <color.h>


uint32_t button_colors[30] = {0xff59584f, 0xff5f5d53, 0xff58564e, 0xff57554d, 0xff56544c, 0xff55534b, \
    0xff54524a, 0xff525049, 0xff514f48, 0xff504e47, 0xff4e4c45, 0xff4e4c45, \
        0xff4c4a44, 0xff4b4943, 0xff4a4842, 0xff484741, 0xff46453f, 0xff45443f, \
        0xff44433e, 0xff43423d, 0xff42413c, 0xff403f3a, 0xff3f3e3a,  0xff3f3e3a, 0xff3f3e3a, \
        0xff3f3e3a,  0xff3f3e3a,  0xff3f3e3a,  0xff3f3e3a,  0xff3f3e3a};


void QuButtonRefresh (QuWidget *wid, QuWindow* win) {
	QuButton *but = (QuButton*)wid;
	for (int i = 0; i < 30; i++)
		acrylic_draw_horizontal_line (win->x + wid->x, win->y + wid->y + i,but->widget.width, button_colors[i]);

	acrylic_draw_arr_string (win->x + wid->x + (wid->width/2) - ((strlen(but->text)*8)/2),
		win->y + wid->y + (wid->height/2) - 12/2
		,(char*)but->text, WHITE);
}


QuButton * QuCreateButton(int x, int y) {
	QuButton *but = (QuButton*)malloc(sizeof(QuButton));
	but->widget.x = x;
	but->widget.y = y;
	but->widget.width = QU_BUTTON_DEFAULT_WIDTH;
	but->widget.height = QU_BUTTON_DEFAULT_HEIGHT;
	but->widget.Refresh = QuButtonRefresh;
	but->text = NULL;
	return but;
}

void QuButtonSetText (QuButton* but, const char* text) {
	but->text = text;
}

