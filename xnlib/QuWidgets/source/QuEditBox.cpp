///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuEditBox.cpp -- Quince Edit box widget
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!================================================


#include <QuEditbox.h>
#include <stdlib.h>
#include <acrylic.h>
#include <color.h>



void QuEditBoxRefresh (QuWidget *wid, QuWindow *win) {
	acrylic_draw_rect_filled (win->x + wid->x,win->y + wid->y, wid->width, wid->height, WHITE);
	acrylic_draw_rect_unfilled (win->x + wid->x,win->y + wid->y, wid->width, wid->height, GRAY);
}


void QuEditBoxMouseEvent (QuWidget *wid, QuWindow *win, int code, bool clicked, int m_x, int m_y) {
}


QuEditBox *QuCreateEditBox (int x, int y, int w, int h) {
	QuEditBox *eb = (QuEditBox*)malloc(sizeof(QuEditBox));
	eb->wid.x = x;
	eb->wid.y = y;
	eb->wid.width = w;
	eb->wid.height = h;
	eb->wid.Refresh = QuEditBoxRefresh;
	eb->wid.MouseEvent = QuEditBoxMouseEvent;
	eb->wid.KeyEvent = NULL;
	eb->wid.ActionEvent = NULL;
	return eb;
}