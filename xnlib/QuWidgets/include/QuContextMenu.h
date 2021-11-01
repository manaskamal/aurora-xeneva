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
#include <QuWindow.h>

typedef struct _qu_ctx_menu_ {
	char *title;
}QuContextMenu;

extern QuContextMenu *QuCreateContextMenu(char *title);
#endif