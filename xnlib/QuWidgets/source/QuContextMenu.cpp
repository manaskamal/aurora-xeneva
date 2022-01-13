///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuContextMenu.h -- Quince Context (Popup) Menu
///!
///!  /PROJECT - Aurora's Xeneva v1.0
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!====================================================

#include <QuContextMenu.h>
#include <stdlib.h>
#include <string.h>
#include <acrylic.h>
#include <color.h>
#include <clientctx.h>
#include <QuPanel.h>
#include <QuMenubar.h>
#include <font.h>

QuContextMenu *QuCreateContextMenu(char *title) {
	QuContextMenu *ctx = (QuContextMenu*)malloc(sizeof(QuContextMenu));
	ctx->title = title;
	ctx->m_w = strlen(title)*8;
	ctx->m_h = 16;
	ctx->m_x = 0;   //assigned by menubar
	ctx->m_y = 0;   //assigned by menubar
	ctx->popup_list = QuListInit();
	ctx->current_popup = NULL;
	ctx->data = 0;
	return ctx;
}

void QuContextMenuAdd (QuContextMenu *ctx, QuPopupMenu *p) {
	QuListAdd(ctx->popup_list, p);
}

void QuCtxMenuAllocateData (QuContextMenu *p, int w, int h) {
	if (p->data)
		return;
	p->ctx = create_canvas(w,h);
}


//!Krishna Nae Begane Baro
void QuContextMenuAppend (QuContextMenu *ctx, QuWidget *mb, QuWindow* win) {

	int menu_w = 0;
	int menu_h = 0;
	for (int i = 0; i < ctx->popup_list->pointer; i++) {
		QuPopupMenu *popup = (QuPopupMenu*)QuListGetAt(ctx->popup_list, i);
		if (popup->m_w > menu_w)
			menu_w = popup->m_w;
		menu_h += popup->m_h;
	}

	
	menu_h += 12;

	if (ctx->popup) {
		QuPanelDirectCopy(win->ctx,mb->x + ctx->m_x + (ctx->m_w/2), 
		mb->y + 20, menu_w, menu_h);
		ctx->popup = false;
		return;
	}

	QuCtxMenuAllocateData(ctx,menu_w, menu_h);
	acrylic_font_set_size(10);

	acrylic_draw_rect_filled (ctx->ctx, mb->x + ctx->m_x + (ctx->m_w/2), 
		 mb->y + 20, menu_w, menu_h,SILVER);

	acrylic_draw_rect_unfilled (ctx->ctx, mb->x + ctx->m_x + (ctx->m_w/2), 
		mb->y + 20, menu_w, menu_h,GRAY);
	int m_y= 16;
	int m_x = (ctx->m_w/2) + 1;
	
	for (int i = 0; i < ctx->popup_list->pointer; i++) {
		QuPopupMenu *popup = (QuPopupMenu*)QuListGetAt(ctx->popup_list, i);
		/*acrylic_draw_arr_string (ctx->ctx, mb->x + ctx->m_x + (ctx->m_w/2) + 1, 
			mb->y + 20 + m_y, popup->title,BLACK);*/
		acrylic_font_draw_string(ctx->ctx,popup->title,mb->x + ctx->m_x + (ctx->m_w/2) + 1, 
			mb->y + 20 + m_y,12,BLACK);
		int f_h = acrylic_font_get_height(popup->title);
		if (popup->m_x == 0 && popup->m_y == 0){
			popup->m_x = mb->x + ctx->m_x + m_x; 
			popup->m_y = mb->y + 20 + m_y;
		}
        m_y += 16;
	}
	
	ctx->popup = true;
	QuPanelDirectCopy(ctx->ctx,mb->x + ctx->m_x + (ctx->m_w/2), 
		mb->y + 20, menu_w, menu_h);
}


void QuContextMenuEventHandle(QuContextMenu *ctx, QuWidget *mb, QuWindow* win,int mouse_x, int mouse_y, bool clicked) {
	QuWinInfo* info = (QuWinInfo*)win->win_info_data;
	for (int i = 0; i < ctx->popup_list->pointer; i++) {
		QuPopupMenu *popup = (QuPopupMenu*)QuListGetAt(ctx->popup_list, i);
		if (mouse_x > info->x + popup->m_x && mouse_x < (info->x + popup->m_x + popup->m_w) &&
			mouse_y > info->y + popup->m_y && mouse_y < (info->y + popup->m_y + popup->m_h)) {
				if (clicked) {
					//Fire the action and context menu disapper here once again
					if (popup->Action) {
						QuContextMenuAppend(ctx,mb,win);
						popup->Action(popup);
					}
				}
		}
	}
}

