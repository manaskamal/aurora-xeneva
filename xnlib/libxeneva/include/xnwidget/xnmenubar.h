/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  xnmenubar.h -- XN Menubar Widget
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *=================================================
 */

#ifndef __XN_MENUBAR_H__
#define __XN_MENUBAR_H__

#include <gui\drawer.h>
#include <gui\font.h>
#include <gui\colors.h>
#include <xnwidget\geom_rect.h>
#include <xnwidget\xnwindow.h>
#include <xnwidget\xnwidget.h>
#include <xnwidget\xnmenu.h>
#include <util\list.h>
#include <mm.h>

typedef void (*menubar_action) (struct _xn_menubar_ *button);

typedef struct _xn_menubar_ {
	xn_widget base;
	menubar_action on_button_pressed;
	bool button_toogle;
	list_t *menus;
	xn_menu_t *active_menu;
	xn_menu_t *last_active_menu;
}xn_menubar_t;

extern xn_menubar_t* xn_create_menubar (xn_window_t *win);
extern void xn_menubar_add (xn_menubar_t * menubar, xn_menu_t *menu);
#endif