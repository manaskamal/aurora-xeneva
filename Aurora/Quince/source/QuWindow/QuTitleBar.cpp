///! Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuTitleBar.cpp -- QuWindow Title bar objects
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury 
///!
///!==================================================

#include <QuWindow\QuTitleBar.h>
#include <QuWindow\QuWindow.h>
#include <acrylic.h>
#include <string.h>
#include <color.h>


uint32_t title_bar_colors[23] = {0xff59584f, 0xff5f5d53, 0xff58564e, 0xff57554d, 0xff56544c, 0xff55534b, \
    0xff54524a, 0xff525049, 0xff514f48, 0xff504e47, 0xff4e4c45, 0xff4e4c45, \
        0xff4c4a44, 0xff4b4943, 0xff4a4842, 0xff484741, 0xff46453f, 0xff45443f, \
        0xff44433e, 0xff43423d, 0xff42413c, 0xff403f3a, 0xff3f3e3a };



QuTitleBarObject* QuCreateTitleBarObject (unsigned x, unsigned y, unsigned w, unsigned h, uint8_t type) {
	QuTitleBarObject *obj = (QuTitleBarObject*)malloc(sizeof(QuTitleBarObject));
	obj->x = x;
	obj->y = y;
	obj->w = w;
	obj->h = h;
	obj->type = type;
	return obj;
}


void QuAddTitleBarObject (QuWindow *win, QuTitleBarObject *obj) {
	QuListAdd (win->titlebar_object, obj);
}


void QuRemoveTitleBarObject (QuWindow* win, QuTitleBarObject *obj) {
	for (int i = 0; i < win->titlebar_object->pointer; i++) {
		QuTitleBarObject *object = (QuTitleBarObject*)QuListGetAt(win->titlebar_object, i);
		if (object == obj)
			QuListRemove(win->titlebar_object, i);
	}
}

void QuUpdateTitleBar (QuWindow *win) {
	for (int i = 0; i < win->titlebar_object->pointer; i++) {
		QuTitleBarObject *to = (QuTitleBarObject*)QuListGetAt(win->titlebar_object, i);
		if (to->type == QU_TITLE_BAR_OBJ_MINIMIZE){
			to->x = win->x + win->width - 43;
			to->y = win->y + 9;
		}if (to->type == QU_TITLE_BAR_OBJ_MAXIMIZE){
			to->x = win->x + win->width - 28;
			to->y = win->y + 9;
		}if (to->type == QU_TITLE_BAR_OBJ_CLOSE){
			to->x = win->x + win->width - 13;
			to->y = win->y + 9;
		}
	}
}

void QuWindowDrawTitlebar (QuWindow* win, unsigned x, unsigned y, unsigned w) {
	for (int i = 0; i < 23; i++) {
		acrylic_draw_horizontal_line (x, y + i, w, title_bar_colors[i]);
	}

	char* title = "Untitled";
	acrylic_draw_rect_filled(x + (w/2) - ((strlen(title)*8)/2), y + 2,strlen(title)*8,21,0xFF3b3931);
	acrylic_draw_string (x + (w/2) - ((strlen(title)*8)/2), y + 2, title, 0xFF3b3931, SILVER);

	uint32_t buttons_color = WHITE;
	for (int i = 0; i < win->titlebar_object->pointer; i++) {
		QuTitleBarObject *to = (QuTitleBarObject*)QuListGetAt(win->titlebar_object, i);
		if (to->type == QU_TITLE_BAR_OBJ_MINIMIZE)
			buttons_color = ORANGE;
		if (to->type == QU_TITLE_BAR_OBJ_MAXIMIZE)
			buttons_color = PALEGREEN;
		if (to->type == QU_TITLE_BAR_OBJ_CLOSE)
			buttons_color = RED;
		acrylic_draw_filled_circle(to->x, to->y, 6, buttons_color);
	}

}