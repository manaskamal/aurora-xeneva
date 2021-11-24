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
		acrylic_draw_rect_filled (wid->x, wid->y, wid->width, wid->height,0xff787770);

		for (int i = 0; i < 14; i++)
			acrylic_draw_vertical_line(wid->x + i,
			wid->y + scroll->thumb_y,
			scroll->thumb_sz,scrollbox_col[i]); 
	}

	///! Horizontal Scrollbar
	if (scroll->type == QU_SCROLLBAR_HORIZONTAL) {
		acrylic_draw_rect_filled (wid->x,wid->y, wid->width, 15,0xff787770);

		for (int i = 0; i < 14; i++)
			acrylic_draw_horizontal_line(wid->x + scroll->thumb_x,
			wid->y + 1 + i,
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
				scroll->scroll_xoff = scroll->thumb_x;
				win->draggable_widget = (QuWidget*)scroll;
			}
	

			if (!clicked)
				win->draggable_widget = NULL;


			
		}

	
		/** Vertical Scrollbar */
		if (scroll->type == QU_SCROLLBAR_VERTICAL){
			if (clicked) {
				scroll->thumb_y = y - (win->y + wid->y + scroll->thumb_sz / 2);
				scroll->scroll_yoff = scroll->thumb_y;
				win->draggable_widget = (QuWidget*)scroll;
			}

			if (!clicked) 
				win->draggable_widget = NULL;


		}
	
	if (win->draggable_widget) { 
				//scroll->thumb_y = y - scroll->thumb_drag_y;
		if (scroll->type == QU_SCROLLBAR_HORIZONTAL) {
			if (win->x + wid->x + scroll->thumb_x + scroll->thumb_sz >= win->x + wid->width/*win->w*/)  {
				scroll->thumb_x = (win->x + wid->x + wid->width) - (win->x + wid->x + scroll->thumb_sz);
				scroll->scroll_xoff = scroll->thumb_x;
			}

			if ((win->x + wid->x + scroll->thumb_x) < win->x + wid->x)  {
				scroll->thumb_x = 0;
				scroll->scroll_xoff = 0;
			}

			scroll->last_thumb_x = scroll->thumb_x;
			QuScrollBarRefresh(wid, win);

			if (scroll->content)
				QuPanelUpdate(scroll->content->x,
				scroll->content->y, 
				scroll->content->width, scroll->content->height, false);
			else
				QuPanelUpdate(wid->x , wid->y, wid->width, 15,false);
		}


		if (scroll->type == QU_SCROLLBAR_VERTICAL) {

			if ((win->y + wid->y + scroll->thumb_y + scroll->thumb_sz) >= (win->y + wid->y + wid->height)){
				scroll->thumb_y = (wid->y + wid->height )- (win->y + wid->y + scroll->thumb_sz);
				scroll->scroll_yoff = scroll->thumb_y;
			}

			//! if scroll thumb < window y pos
			if ((win->y + wid->y + scroll->thumb_y) <= (win->y + wid->y)) {
				scroll->thumb_y = 0;
				scroll->scroll_yoff = 0;
			}

			scroll->last_thumb_y = scroll->thumb_y;
			QuScrollBarRefresh(wid, win);

			if (scroll->content)
				QuPanelUpdate(scroll->content->x, 
					scroll->content->y, 
					scroll->content->width, scroll->content->height, false);
			else
				QuPanelUpdate(wid->x + 1, wid->y, wid->width, wid->height,false);
		}

		//! Call the scroll event of the content
		if (scroll->content) {
			if (scroll->content->ScrollEvent) {
				scroll->content->ScrollEvent (scroll->content,wid,win);
			}
		}
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
			scr->wid.y = content->y + content->height - 15;
			scr->wid.width = content->width - 15;
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
			scr->wid.x = content->x + content->width - 15;
			scr->wid.y = content->y;
			scr->wid.width = 15;
			scr->wid.height = content->height - 15;
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
	scr->wid.ScrollEvent = NULL;
	scr->type = type;
	scr->thumb_x = 0;
	scr->thumb_y = 0;
	scr->thumb_sz = 200;
	scr->last_thumb_x = 0;
	scr->last_thumb_y = 0;
	scr->scroll_xoff = 0;
	scr->scroll_yoff = 0;
	scr->content = content;
	scr->update_off = true;
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