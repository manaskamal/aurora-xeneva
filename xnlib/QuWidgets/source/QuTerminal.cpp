///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   QuTerminal.h -- Terminal Widget 
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///!
///!==================================================

#include <QuTerminal.h>
#include <stdlib.h>
#include <ctype.h>
#include <acrylic.h>
#include <color.h>
#include <string.h>


void QuTermPrint (QuTerminal *term , char p) {
	term->buffer[term->cursor_x] = p;
	term->cursor_x++;
}


void QuTermMouse (QuWidget* wid, QuWindow *win, int code, bool clicked, int x, int y) {
}


void QuTermRefresh (QuWidget* wid, QuWindow *win) {
	QuTerminal *term = (QuTerminal*)wid;
	acrylic_draw_rect_filled(win->x + wid->x, win->y + wid->y, wid->width, wid->height, BLACK);
	acrylic_draw_arr_string(win->x + wid->x, win->y + wid->y,term->buffer, WHITE);
}


void QuTermKeyEvent (QuWidget* wid, QuWindow *win, int code){
	QuTerminal *term = (QuTerminal*)wid;
	if (isascii(code)) {
		QuTermPrint(term, code);
		QuTermRefresh(wid, win);
	}
}




QuTerminal * QuCreateTerminal (int x, int y, int w, int h) {
	QuTerminal *term = (QuTerminal*)malloc(sizeof(QuTerminal));
	term->wid.x = x;
	term->wid.y = y;
	term->wid.width = w;
	term->wid.height = h;
	term->wid.MouseEvent = QuTermMouse;
	term->wid.KeyEvent = QuTermKeyEvent;
	term->wid.Refresh = QuTermRefresh;
	memset(term->buffer, 0, 512);
	term->cursor_x = 0;
	term->cursor_y = 0;
	return term;
}