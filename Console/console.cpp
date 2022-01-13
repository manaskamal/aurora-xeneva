///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   console.cpp --- Console Control
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///!
///!=================================================

#include "console.h"
#include <color.h>

void ConsoleRefresh (QuWidget *wid, QuWindow *win) {
	acrylic_draw_rect_filled(win->ctx,0,0, win->w, win->h, BLACK);
}


void ConsoleMouseEvent (QuWidget *wid,QuWindow* win,int code, bool clicked,int x, int y){
}


ConsoleWidget* create_console (int x, int y, int w, int h) {
	ConsoleWidget *con = (ConsoleWidget*)malloc (sizeof(ConsoleWidget));
	con->wid.x = x;
	con->wid.y = y;
	con->wid.width = w;
	con->wid.height = h;
	con->wid.KeyEvent = 0;
	con->wid.MouseEvent = ConsoleMouseEvent;
	con->wid.ActionEvent = 0;
	con->wid.Refresh = ConsoleRefresh;
	con->cursor_x = 0;
	con->cursor_y = 0;
	return con;
}