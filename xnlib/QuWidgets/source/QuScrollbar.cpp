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

///! Scrollbox Colors
uint32_t scrollbox_col[14] = {0xff59584f, 0xff5f5d53, 0xff58564e, 0xff57554d, 0xff56544c, 0xff55534b, 
    0xff54524a, 0xff525049, 0xff514f48, 0xff504e47, 0xff4e4c45, 0xff4e4c45, 
	0xff4c4a44, 0xff4b4943 };


/*
 * Refresh function -- Called many times when it wants to repaint the widget
 */
void QuScrollBarRefresh (QuWidget *wid, QuWindow* win) {
	QuScrollBar *scroll = (QuScrollBar*)wid;
	//! Check the type of scrollbar
	if (scroll->type == QU_SCROLLBAR_VERTICAL) {
		acrylic_draw_rect_filled (win->x + wid->x, win->y + wid->y, wid->width, wid->height,0xff787770);

		for (int i = 0; i < 14; i++)
			acrylic_draw_vertical_line(win->x + wid->x + i,
			win->y + wid->y + scroll->thumb_y,
			scroll->thumb_sz,scrollbox_col[i]); 
	}

	///! Horizontal Scrollbar
	if (scroll->type == QU_SCROLLBAR_HORIZONTAL) {
		acrylic_draw_rect_filled (win->x + wid->x, win->y + wid->y, wid->width, 15,0xff787770);

		for (int i = 0; i < 14; i++)
			acrylic_draw_horizontal_line(win->x + wid->x + scroll->thumb_x,
			win->y + wid->y + i,
			scroll->thumb_sz,scrollbox_col[i]); 
	}
}


//! MouseEvent func -- Called when mouse event occurs for this particular widget
void QuScrollbarMouseEvent (QuWidget* wid, QuWindow* win, int code,bool clicked, int x, int y) {
	QuScrollBar *scroll = (QuScrollBar*)wid;
	bool update = false;

	if (code == QU_EVENT_MOUSE_ENTER){
		/* For Horizontal Scrollbar */
		if (scroll->type == QU_SCROLLBAR_HORIZONTAL) {
			if (clicked){
				scroll->thumb_x = x - (win->x + wid->x + scroll->thumb_sz/2);//scroll->thumb_x;
				win->draggable_widget = (QuWidget*)scroll;
			}
	

			if (!clicked)
				win->draggable_widget = NULL;


			
		}

	
		/** Vertical Scrollbar */
		if (scroll->type == QU_SCROLLBAR_VERTICAL){
			if (clicked) {
				scroll->thumb_y = y - (win->y + wid->y + scroll->thumb_sz / 2);
				win->draggable_widget = (QuWidget*)scroll;
			}

			if (!clicked) 
				win->draggable_widget = NULL;


		}
	}

	if (win->draggable_widget) { 
				//scroll->thumb_y = y - scroll->thumb_drag_y;
		if (scroll->type == QU_SCROLLBAR_HORIZONTAL) {
			if (win->x + wid->x + scroll->thumb_x + scroll->thumb_sz >= win->x + wid->width/*win->w*/) 
				scroll->thumb_x = (win->x + wid->x + wid->width) - (win->x + wid->x + scroll->thumb_sz);

			if ((win->x + wid->x + scroll->thumb_x) < win->x + wid->x) 
				scroll->thumb_x = 0;

			QuScrollBarRefresh(wid, win);
			QuPanelUpdate(win->x + wid->x + 1, win->y + wid->y, wid->width, 13,false);
		}


		if (scroll->type == QU_SCROLLBAR_VERTICAL) {

			if ((win->y + wid->y + scroll->thumb_y + scroll->thumb_sz) >= (win->y + wid->y + wid->height))
				scroll->thumb_y = (win->y + wid->y + wid->height )- (win->y + wid->y + scroll->thumb_sz);

			//! if scroll thumb < window y pos
			if ((win->y + wid->y + scroll->thumb_y + scroll->thumb_sz) < (win->y + wid->y)) 
				scroll->thumb_y = win->y + wid->y;

			QuScrollBarRefresh(wid, win);
			QuPanelUpdate(win->x + wid->x + 1, win->y + wid->y, wid->width, wid->height,false);
		}
	}

}

/**
 * Create the scrollbar 
 *
 * @param type -- Type of the scrollbar
 */
QuScrollBar * QuCreateScrollbar (QuWidget *content, int type) {
	QuScrollBar *scr = (QuScrollBar*)malloc(sizeof(QuScrollBar));
	if (type == QU_SCROLLBAR_HORIZONTAL) {
		if (content){
			scr->wid.x = content->x;
			scr->wid.y = content->y + content->height - 14;
			scr->wid.width = content->width;
			scr->wid.height = 15;
		}else {
			scr->wid.x = 0;
			scr->wid.y = QuGetWindow()->h - 14;
			scr->wid.width = QuGetWindow()->w;
			scr->wid.height = 15;
		}
	}

	if (type == QU_SCROLLBAR_VERTICAL) {
		if (content) {
			scr->wid.x = content->width - 15;
			scr->wid.y = content->y;
			scr->wid.width = 15;
			scr->wid.height = content->height;
		}else {
			scr->wid.x = QuGetWindow()->w - 15;
			scr->wid.y = 23;
			scr->wid.width = 15;
			scr->wid.height = QuGetWindow()->h - 23;
		}
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
	scr->content = content;
	return scr;
}


void QuScrollbar_SetContent (QuScrollBar *scroll, QuWidget *content) {
	scroll->content = content;
}



void QuScrollbar_SetThumbPos (QuScrollBar *scroll, int pos) {
	if (scroll->type == QU_SCROLLBAR_VERTICAL) {
		scroll->thumb_y = pos;
	}

	if (scroll->type == QU_SCROLLBAR_HORIZONTAL) {
		scroll->thumb_x = pos;
	}
}