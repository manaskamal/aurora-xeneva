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
	p->data = (uint32_t*)malloc(w*h*32);
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
		QuPanelDirectCopy(canvas_get_framebuffer(),mb->x + ctx->m_x + (ctx->m_w/2), 
		mb->y + 20, menu_w, menu_h);
		ctx->popup = false;
		return;
	}

	QuCtxMenuAllocateData(ctx,menu_w, menu_h);


	cc_draw_rect_filled (ctx->data, mb->x + ctx->m_x + (ctx->m_w/2), 
		 mb->y + 20, menu_w, menu_h,SILVER);

	cc_draw_rect_unfilled (ctx->data, mb->x + ctx->m_x + (ctx->m_w/2), 
		mb->y + 20, menu_w, menu_h,GRAY);
	int m_y= 4;
	int m_x = (ctx->m_w/2) + 1;
	for (int i = 0; i < ctx->popup_list->pointer; i++) {
		QuPopupMenu *popup = (QuPopupMenu*)QuListGetAt(ctx->popup_list, i);
		cc_draw_arr_string (ctx->data, mb->x + ctx->m_x + (ctx->m_w/2) + 1, 
			mb->y + 20 + m_y, popup->title,BLACK);
		
		if (popup->m_x == 0 && popup->m_y == 0){
			popup->m_x = mb->x + ctx->m_x + m_x; 
			popup->m_y = mb->y + 20 + m_y;
		}
        m_y += 15;
	}
	
	ctx->popup = true;
	QuPanelDirectCopy(ctx->data,mb->x + ctx->m_x + (ctx->m_w/2), 
		mb->y + 20, menu_w, menu_h);
}


void QuContextMenuEventHandle(QuContextMenu *ctx, QuWidget *mb, QuWindow* win,int mouse_x, int mouse_y, bool clicked) {
	for (int i = 0; i < ctx->popup_list->pointer; i++) {
		QuPopupMenu *popup = (QuPopupMenu*)QuListGetAt(ctx->popup_list, i);
		if (mouse_x > QuGetWindow()->x + popup->m_x && mouse_x < (QuGetWindow()->x + popup->m_x + popup->m_w) &&
			mouse_y > QuGetWindow()->y + popup->m_y && mouse_y < (QuGetWindow()->y + popup->m_y + popup->m_h)) {
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

