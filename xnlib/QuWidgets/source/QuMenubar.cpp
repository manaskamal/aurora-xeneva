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
#include <sys\_term.h>
#include <QuPanel.h>
#include <font.h>


void QuMenubarRefresh (QuWidget* wid, QuWindow *win) {
	QuMenubar *mb = (QuMenubar*)wid;


	acrylic_draw_rect_filled (win->ctx,wid->x,  wid->y, wid->width, 20, SILVER);

	int x = 4;
	for (int i = 0; i < mb->CtxMenus->pointer; i++) {
		QuContextMenu *ctx = (QuContextMenu*)QuListGetAt(mb->CtxMenus, i);
		/*if (mb->focused != NULL && mb->focused == ctx) {
			acrylic_draw_rect_filled(wid->x + x + ((ctx->m_w/2)-2),  wid->y,ctx->m_w,wid->height,BLUE);
			acrylic_draw_arr_string (wid->x + x + (ctx->m_w/2), 
			 wid->y + (wid->height/2) - (12/2),ctx->title,WHITE);

		} else {*/
		/*	acrylic_draw_arr_string (win->ctx,wid->x + x + (ctx->m_w/2), 
				 wid->y + (wid->height/2) - (12/2),ctx->title,LIGHTBLACK);*/
			acrylic_font_set_size(15);
			acrylic_font_draw_string (win->ctx,ctx->title,wid->x + x + 15/*(ctx->m_w/2)*/, 
				 wid->y + 15/*(wid->height/2)- 15*/,15,LIGHTBLACK);

		//}

		if (ctx->m_x == 0 && ctx->m_y == 0){
			ctx->m_x = x;
			ctx->m_y = (wid->height/2) - (12/2);
		}

		x += strlen(ctx->title)*8 + 4;
	}
}


void QuMenubarMouseEvent (QuWidget *wid, QuWindow *win, int code, bool clicked, int x, int y) {
	QuWinInfo *info = (QuWinInfo*)win->win_info_data;
	QuMenubar *mb = (QuMenubar*)wid;

	if (code == QU_EVENT_MOUSE_ENTER) {
		mb->focused = NULL;
		for (int i = 0; i < mb->CtxMenus->pointer; i++) {
			QuContextMenu *ctx = (QuContextMenu*)QuListGetAt(mb->CtxMenus, i);
			if (ctx->m_x != 0) {
				if (x > (info->x + wid->x + ctx->m_x) && x < (info->x + wid->x + ctx->m_x + ctx->m_w) &&
					y > (info->y + wid->y + ctx->m_y) && y < (info->y + wid->y + ctx->m_y + ctx->m_h)) {
						mb->focused = ctx;

						//! Make the difference between clicking and dragging
						if (clicked && mb->m_x == x && mb->m_y == y) {
							//!Make previous menu disappear
							if (mb->last_focused != NULL && mb->last_focused != ctx) {
								mb->last_focused->popup = true;
								QuContextMenuAppend(mb->last_focused,wid,win);
								mb->last_focused = NULL;
							}
							//Make new menu appear
							QuContextMenuAppend(ctx,wid,win);
							mb->last_focused = ctx;
							win->current_ctx_menu = ctx;
						}


						QuMenubarRefresh(wid, win);
						QuPanelUpdate (win,wid->x,wid->y, wid->width, wid->height,false);
						mb->update_required = true;
						
				}
			}
		}

	}

	if (code == QU_EVENT_MOUSE_LEAVE) {
		///*mb->focused = NULL;*/
		//if (mb->update_required){
		//	mb->popup_enable = false;
		//	QuMenubarRefresh(wid, win);
		//	QuPanelUpdate (wid->x,wid->y, wid->width, wid->height,false);
		//	mb->update_required = false;
		//}
	}

	/*
	 * Store the mouse coord
	 * next mouse events
	 */
	mb->m_x = x;
	mb->m_y = y;
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
	mb->last_focused = NULL;
	QuGetWindow()->current_menubar = mb;
	return mb;
}

void QuMenubarAddMenu(QuMenubar *mb, QuContextMenu *menu) {
	QuListAdd (mb->CtxMenus, menu);
}

