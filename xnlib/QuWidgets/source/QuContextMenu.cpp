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
#include <QuPanel.h>

QuContextMenu *QuCreateContextMenu(char *title) {
	QuContextMenu *ctx = (QuContextMenu*)malloc(sizeof(QuContextMenu));
	ctx->title = title;
	ctx->m_w = strlen(title)*8;
	ctx->m_h = 16;
	ctx->m_x = 0;   //assigned by menubar
	ctx->m_y = 0;   //assigned by menubar
	ctx->popup_list = QuListInit();
	ctx->current_popup = NULL;
	return ctx;
}

void QuContextMenuAdd (QuContextMenu *ctx, QuPopupMenu *p) {
	QuListAdd(ctx->popup_list, p);
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

	
	acrylic_draw_rect_filled (win->x + mb->x + ctx->m_x + (ctx->m_w/2), 
		win->y + mb->y + 20, menu_w, menu_h,SILVER);

	acrylic_draw_rect_unfilled (win->x + mb->x + ctx->m_x + (ctx->m_w/2), 
		win->y + mb->y + 20, menu_w, menu_h,GRAY);
	int m_y= 4;
	int m_x = (ctx->m_w/2) + 1;
	for (int i = 0; i < ctx->popup_list->pointer; i++) {
		QuPopupMenu *popup = (QuPopupMenu*)QuListGetAt(ctx->popup_list, i);
		acrylic_draw_arr_string (win->x + mb->x + ctx->m_x + (ctx->m_w/2) + 1, 
			win->y + mb->y + 20 + m_y, popup->title,BLACK);
		m_y += 15;
		if (popup->m_x == 0 && popup->m_y == 0){
			popup->m_x = m_x; 
			popup->m_y = m_y;
		}

	}

	QuPanelUpdate(win->x + mb->x + ctx->m_x + (ctx->m_w/2), 
		win->y + mb->y + 20, menu_w, menu_h, false);
}

