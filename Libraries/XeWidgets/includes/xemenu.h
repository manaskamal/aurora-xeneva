/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2022, Manas Kamal Choudhury
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 **/

#ifndef __XE_MENU_H__
#define __XE_MENU_H__

#include <stdint.h>
#include <stdarg.h>
#include <acrylic.h>
#include <canvas.h>
#include <list.h>
#include <xewidget.h>
#include <xewindow.h>
#include <xequwindow.h>

/** =============================================================================
 **  The Design of XEMenu is
 **     |____ XEMENUBAR -----> contains XEMenu as "MENU_BUTTONS"
 **         |____  XEMENU --------> contains XE_MENUITEM_BUTTONS 
 **             |____  XE_MENUITEM_BUTTONS either holds Actions or Another XEMenu
 ** =============================================================================
 **/

typedef struct _xe_menu_ {
	XEWidget base;
	XEQuickWindow *quickwin;
	canvas_t *pixbuf;
	int menu_button_x;
	int menu_button_y;
	int menu_button_w;
	int menu_button_h;
	char* name;
	list_t *menu_items;
	bool visible;
	_xe_menu_ *parent_link;
	int menu_last_mx;
	int menu_last_my;
	bool calculated_metrics;
}XEMenu;


#define MENU_ITEM_BUTTON_HEIGHT 15

typedef struct _xe_menu_item_button_ {
	XEWidget base;
	char* name;
	XEMenu* parent;
	XEMenu *next_menu;
}XEMenuItemButton;


typedef struct _xe_menubar_ {
	XEWidget base;
	list_t *menu_list;
	uint8_t custom_color;
	XEMenu* active_menu;
	int mouse_last_x;
	int mouse_last_y;
}XEMenubar;

/*
 * XECreateMenubar -- Creates a menubar
 */
XE_EXTERN XE_EXPORT XEMenubar* XECreateMenubar (XEWindow *window);

/*
 * XECreateMenu -- Creates a menu
 * @param name -- menu name
 */
XE_EXTERN XE_EXPORT XEMenu *XECreateMenu (char* name);

XE_EXTERN XE_EXPORT void XEMenuCalculateItemMetrics (XEMenu *menu);

XE_EXTERN XE_EXPORT void XEMenuAddItem (XEMenu* menu, XEMenuItemButton* item);

/*
 * XEMenubarAdd -- Adds a menu to menubar list
 * @param menubar -- Pointer to menubar
 * @param menu -- Pointer to menu
 */
XE_EXTERN XE_EXPORT void XEMenubarAdd (XEMenubar *menubar, XEMenu* menu);

/*
 * XECreateMenuItem -- Creates a new menu item button
 * @param text -- Button text
 * @param next_menu -- links to next menu
 */
XE_EXTERN XE_EXPORT XEMenuItemButton * XECreateMenuItem (char* text,XEMenu *next_menu, XEMenu* parent);


#endif