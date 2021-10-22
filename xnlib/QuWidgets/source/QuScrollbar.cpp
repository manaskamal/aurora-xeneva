///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   QuScrollbar.cpp -- Quince Scrollbars
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///!
///!=============================================

#include <QuScrollbar.h>
#include <stdlib.h>
#include <acrylic.h>
#include <color.h>
#include <QuPanel.h>


uint32_t scrollbox_col[14] = {0xff59584f, 0xff5f5d53, 0xff58564e, 0xff57554d, 0xff56544c, 0xff55534b, 
    0xff54524a, 0xff525049, 0xff514f48, 0xff504e47, 0xff4e4c45, 0xff4e4c45, 
	0xff4c4a44, 0xff4b4943 };

void QuScrollBarRefresh (QuWidget *wid, QuWindow* win) {
	QuScrollBar *scroll = (QuScrollBar*)wid;

	if (scroll->type == QU_SCROLLBAR_VERTICAL) {
		acrylic_draw_rect_filled (win->x + wid->x, win->y + wid->y, wid->width, wid->height,0xff787770);
		for (int i = 0; i < 14; i++)
			acrylic_draw_vertical_line(win->x + win->w - 14 + i,
			win->y + 23 + scroll->thumb_y,
			200,scrollbox_col[i]); 
	}

	if (scroll->type == QU_SCROLLBAR_HORIZONTAL) {
		acrylic_draw_rect_filled (win->x, win->y + win->h - 15, win->w, 15,0xff787770);

		if (scroll->thumb_x + scroll->thumb_sz >= win->w) 
			scroll->thumb_x = win->w - scroll->thumb_sz;

		if (scroll->thumb_x + scroll->thumb_sz < win->x) 
			scroll->thumb_x = win->x;
		
		for (int i = 0; i < 14; i++)
			acrylic_draw_horizontal_line(win->x + scroll->thumb_x,
			win->y +  win->h - 14 + i,
			200,scrollbox_col[i]); 
	}
}


void QuScrollbarMouseEvent (QuWidget* wid, QuWindow* win, int code,bool clicked, int x, int y) {
	QuScrollBar *scroll = (QuScrollBar*)wid;
	bool update = false;

	if (code == QU_EVENT_MOUSE_ENTER){
		//Horiz
		if (scroll->type == QU_SCROLLBAR_HORIZONTAL && clicked) {
			if ((x > win->x + wid->x + scroll->thumb_x) && 
				(x < (win->x + wid->x + scroll->thumb_x + scroll->thumb_sz)) &&
				(y > win->x + wid->y) &&
				(y < (win->y + wid->y + wid->height))) {
					scroll->thumb_drag_x = x - scroll->thumb_x;
					update = true;
			}
	
			if (!clicked)
				scroll->thumb_drag_x = 0;


			if (scroll->thumb_drag_x) {
					scroll->thumb_x = x - scroll->thumb_drag_x;
					QuScrollBarRefresh(wid, win);
					QuPanelUpdate(win->x, win->y + win->h - 15, win->w - 1, 14,false);
				}
			}
	
		
		if (scroll->type == QU_SCROLLBAR_VERTICAL){
			if ((x > win->x + wid->x) && x < wid->x + wid->x + wid->width &&
				(y > win->y + wid->y + scroll->thumb_y) && 
				(y < win->y + wid->y + scroll->thumb_y + scroll->thumb_sz)) {
					scroll->thumb_drag_y = y - scroll->thumb_y;
			}

			if (clicked) { 
				scroll->thumb_y = y - scroll->thumb_drag_y;
				QuScrollBarRefresh(wid, win);
				QuPanelUpdate(win->x + wid->x, win->y + wid->y, wid->width - 1, wid->height,false);
			}

		}
	}
}

QuScrollBar * QuCreateScrollbar (int type) {
	QuScrollBar *scr = (QuScrollBar*)malloc(sizeof(QuScrollBar));
	if (type == QU_SCROLLBAR_HORIZONTAL) {
		scr->wid.x = 0;
		scr->wid.y = QuGetWindow()->h - 15;
		scr->wid.width = QuGetWindow()->w;
		scr->wid.height = 15;
	}

	if (type == QU_SCROLLBAR_VERTICAL) {
		scr->wid.x = QuGetWindow()->w - 15;
		scr->wid.y = 23;
		scr->wid.width = 15;
		scr->wid.height = QuGetWindow()->h - 23;
	}
	scr->wid.Refresh = QuScrollBarRefresh;
	scr->wid.KeyEvent = NULL;
	scr->wid.MouseEvent = QuScrollbarMouseEvent;
	scr->wid.ActionEvent = NULL;
	scr->type = type;
	scr->thumb_x = 0;
	scr->thumb_y = 0;
	scr->thumb_sz = 200;
	scr->thumb_drag_x = 0;
	scr->thumb_drag_y = 0;
	return scr;
}


void QuScrollbar_SetThumbPos (QuScrollBar *scroll, int pos) {
	if (scroll->type == QU_SCROLLBAR_VERTICAL) {
		scroll->thumb_y = pos;
	}

	if (scroll->type == QU_SCROLLBAR_HORIZONTAL) {
		scroll->thumb_x = pos;
	}
}