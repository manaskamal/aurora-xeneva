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
#include <QuScrollbar.h>
#include <QuPanel.h>
#include <sys\mmap.h>


void CopyToFB (QuWidget* wid, QuWindow* win, int x, int y, int w, int h) {
	uint32_t *lfb = (uint32_t*)QuGetWindow()->canvas;
	uint32_t *dbl_buffer = (uint32_t*)0x0000600000000000;
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			uint32_t color = dbl_buffer[(x + i) + (y + j) * canvas_get_width()];
			dbl_buffer[(win->x + wid->x + i) + (win->y + wid->y + j) * canvas_get_width()] = color;
		}
	}
}


void QuEditBoxRefresh (QuWidget *wid, QuWindow *win) {
	acrylic_draw_rect_filled (win->x + wid->x,win->y + wid->y, wid->width, wid->height, WHITE);
	acrylic_draw_rect_unfilled (win->x + wid->x,win->y + wid->y, wid->width, wid->height, GRAY);
}


void QuEditBoxMouseEvent (QuWidget *wid, QuWindow *win, int code, bool clicked, int m_x, int m_y) {
}

void QuEditBoxScrollEvent (QuWidget *wid, QuWidget *scroll, QuWindow *win) {
	QuScrollBar *sb = (QuScrollBar*)scroll;
	QuEditBox *eb = (QuEditBox*)wid;
	int sc_x = 0;
	if (sb->thumb_x > eb->last_scroll_diffx) 
		sc_x = 32;
	else
		sc_x -= 32;

	CopyToFB (wid,win,win->x,win->y,wid->width, wid->height);
	QuPanelUpdate (win->x + wid->x, win->y + wid->y, wid->width, wid->height, false);
	eb->last_scroll_diffx = sb->thumb_x;
}


QuEditBox *QuCreateEditBox (int x, int y, int w, int h) {
	uint32_t location = 0x0000070000000000; 
	for (int i = 0; i < canvas_get_width() * canvas_get_height() * 32 / 4096; i++) 
		valloc (location + i * 4096);

	QuEditBox *eb = (QuEditBox*)malloc(sizeof(QuEditBox));
	eb->wid.x = x;
	eb->wid.y = y;
	eb->wid.width = w;
	eb->wid.height = h;
	eb->wid.Refresh = QuEditBoxRefresh;
	eb->wid.MouseEvent = QuEditBoxMouseEvent;
	eb->wid.KeyEvent = NULL;
	eb->wid.ActionEvent = NULL;
	eb->wid.ScrollEvent = QuEditBoxScrollEvent;
	eb->content = (uint32_t*)location;
	eb->last_scroll_diffx = 0;
	eb->last_scroll_diffy = 0;
	return eb;
}