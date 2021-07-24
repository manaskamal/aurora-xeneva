/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  xnmenu.h -- XN Menu Object
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ================================================
 */

#ifndef __XNMENU_H__
#define __XNMENU_H__

#include <xnwidget\xnwidget.h>
#include <xnwidget\geom_rect.h>
#include <gui\drawer.h>
#include <gui\colors.h>
#include <gui\font.h>
#include <util\list.h>

typedef void (*menu_item_handler) (struct _xn_menu_item_ *item);

typedef struct _xn_menu_item_ {
	char *title;
	menu_item_handler *action_handler;
}xn_menu_item_t;


typedef struct _xn_menu_ {
	char *popup_title;
	int pos_x;
	int pos_y;
	bool clicked;
	bool over_effect;
	list_t *items;
}xn_menu_t;

extern xn_menu_t *xn_create_menu (char* popup_title);
extern void xn_menu_add_item (xn_menu_t* menu, xn_menu_item_t *menu_item);

#endif