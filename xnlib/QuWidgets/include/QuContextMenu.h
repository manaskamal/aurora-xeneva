///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuContextMenu.h -- Quince Context (Popup) Menu
///!
///!  /PROJECT - Aurora's Xeneva v1.0
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!====================================================

#ifndef __QU_CONTEXT_MENU_H__
#define __QU_CONTEXT_MENU_H__

#include <stdint.h>
#include <QuUtils\QuList.h>
#include <QuWindow.h>
#include <QuPopupMenu.h>

typedef struct _qu_ctx_menu_ {
	char *title;
	//! bounding box
	int m_x; 
	int m_y;
	int m_w;
	int m_h;
	QuList *popup_list;
	QuPopupMenu *current_popup;
}QuContextMenu;

extern QuContextMenu *QuCreateContextMenu(char *title);
extern void QuContextMenuAdd (QuContextMenu *ctx, QuPopupMenu *p);
extern void QuContextMenuAppend (QuContextMenu *ctx, QuWidget *mb, QuWindow* win);
#endif