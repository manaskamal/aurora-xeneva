///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuPopupMenu.h -- Popup Menu for Context Menus
///!
///!  /PROJECT - Aurora's Xeneva v1.0
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!==================================================

#ifndef __QU_POPUP_MENU_H__
#define __QU_POPUP_MENU_H__

#include <stdint.h>
#include <QuWindow.h>

typedef struct _qu_popup_menu_ {
	char *title;
	int m_w;
	int m_h;
	int m_x;
	int m_y;
	bool is_popup;
	uint32_t *data;
	void (*Action) (_qu_popup_menu_ *menu);
}QuPopupMenu;

extern QuPopupMenu* QuCreatePopupMenu(char* title);
#endif