///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuMenubar.h -- Quince Menubar Widget
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!===============================================

#include <QuMenubar.h>
#include <stdlib.h>
#include <color.h>
#include <acrylic.h>
#include <string.h>
#include <QuPanel.h>


void QuMenubarRefresh (QuWidget* wid, QuWindow *win) {
	QuMenubar *mb = (QuMenubar*)wid;


	acrylic_draw_rect_filled (win->x + wid->x, win->y + wid->y, wid->width, 20, SILVER);

	int x = 4;
	for (int i = 0; i < mb->CtxMenus->pointer; i++) {
		QuContextMenu *ctx = (QuContextMenu*)QuListGetAt(mb->CtxMenus, i);
		if (mb->focused != NULL && mb->focused == ctx) {
			acrylic_draw_rect_filled(win->x + wid->x + x + ((ctx->m_w/2)-2), win->y + wid->y,ctx->m_w,wid->height,BLUE);
			acrylic_draw_arr_string (win->x + wid->x + x + (ctx->m_w/2), 
			win->y + wid->y + (wid->height/2) - (12/2),ctx->title,WHITE);
			
			if (mb->popup_enable)
				QuContextMenuAppend(ctx,wid,win);

		} else {
			acrylic_draw_arr_string (win->x + wid->x + x + (ctx->m_w/2), 
				win->y + wid->y + (wid->height/2) - (12/2),ctx->title,LIGHTBLACK);
		}

		if (ctx->m_x == 0 && ctx->m_y == 0){
			ctx->m_x = x;
			ctx->m_y = (wid->height/2) - (12/2);
		}

		x += strlen(ctx->title)*8 + 4;
	}
}


void QuMenubarMouseEvent (QuWidget *wid, QuWindow *win, int code, bool clicked, int x, int y) {
	QuMenubar *mb = (QuMenubar*)wid;

	if (code == QU_EVENT_MOUSE_ENTER) {
		for (int i = 0; i < mb->CtxMenus->pointer; i++) {
			QuContextMenu *ctx = (QuContextMenu*)QuListGetAt(mb->CtxMenus, i);
			if (ctx->m_x != 0) {
				if (x > (win->x + wid->x + ctx->m_x) && x < (win->x + wid->x + ctx->m_x + ctx->m_w) &&
					y > (win->y + wid->y + ctx->m_y) && y < (win->y + wid->y + ctx->m_y + ctx->m_h)) {
						mb->focused = ctx;

						//! Reverse the bit
						if (clicked)
							mb->popup_enable = !mb->popup_enable;

						QuMenubarRefresh(wid, win);
						QuPanelUpdate (win->x + wid->x, win->y + wid->y, wid->width, wid->height,false);
						mb->update_required = true;
				}
			}
		}
	}

	if (code == QU_EVENT_MOUSE_LEAVE) {
		mb->focused = NULL;
		if (mb->update_required){
			QuMenubarRefresh(wid, win);
			QuPanelUpdate (win->x + wid->x, win->y + wid->y, wid->width, wid->height,false);
			mb->update_required = false;
		}
	}
}

void QuMenubarKeyEvent (QuWidget *wid, QuWindow *win, int code) {
}

QuMenubar *QuCreateMenubar () {
	QuMenubar *mb = (QuMenubar*)malloc(sizeof(QuMenubar));
	mb->wid.x = 1;
	mb->wid.y = 23;
	mb->wid.width = QuGetWindow()->w - 1;
	mb->wid.height = 20;
	mb->wid.ActionEvent = NULL;
	mb->wid.MouseEvent = QuMenubarMouseEvent;
	mb->wid.Refresh = QuMenubarRefresh;
	mb->wid.KeyEvent = QuMenubarKeyEvent;
	mb->wid.ScrollEvent = 0;
	mb->CtxMenus = QuListInit();
	mb->focused = NULL;
	mb->popup_enable = false;
	mb->update_required = false;
	return mb;
}

void QuMenubarAddMenu(QuMenubar *mb, QuContextMenu *menu) {
	QuListAdd (mb->CtxMenus, menu);
}

