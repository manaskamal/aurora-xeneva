/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  menubar.h -- System Menubar
 *
 *  /PROJECT - Aurora Xeneva {DWM}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ================================================
 */

#ifndef __MENUBAR_H__
#define __MENUBAR_H__

#include <stdtypes.h>
#include <winlist.h>
#include <window.h>


typedef struct _menu_ {
	char *title;
}menu_t;


typedef struct _menubar_ {
	winlist *menu_list;
}menubar_t;

extern void initialize_system_menubar ();
extern void sys_menubar_add_menu (window_t* win ,menu_t *menu);
extern void draw_menubar ();
#endif