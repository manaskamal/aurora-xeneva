/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  xnmenu.cpp -- XN Menu Object
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ==============================================
 */

#include <xnwidget\xnmenu.h>
#include <mm.h>


xn_menu_t * xn_create_menu (char * title) {
	int title_length = strlen (title);
	xn_menu_t *menu = (xn_menu_t*)malloc(sizeof(xn_menu_t));
	menu->popup_title = (char*)malloc(title_length);
	for (int i = 0; i < title_length ; i++)
		menu->popup_title[i] = title[i];
	return menu;
}