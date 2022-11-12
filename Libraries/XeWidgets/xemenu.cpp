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

#include "xemenu.h"
#include <xequwindow.h>
#include <stdlib.h>
#include <styles\XEMenubarDefaultStyle.h>
#include <styles\XEDefaultMenuStyle.h>
#include <sys/_term.h>
#include <sys/_sleep.h>
#include <font.h>

void  XEMenubarMouseEvent (XEWidget *widget, XEWindow *window, int mouse_x, int mouse_y, int button) {
	XEMenubar *menubar = (XEMenubar*)widget;

	for (int i = 0; i < menubar->menu_list->pointer; i++) {
		XEMenu* menu = (XEMenu*)list_get_at(menubar->menu_list, i);
		if (mouse_x >= window->shwin->x + menu->menu_button_x &&
			mouse_x < (window->shwin->x + menu->menu_button_x + menu->menu_button_w) &&
			mouse_y >= window->shwin->y + menu->menu_button_y && 
			mouse_y < (window->shwin->y + menu->menu_button_y + menu->menu_button_h)) {
				
				/* check for button click, if true then show the menu */
				if (button && menu->menu_last_mx == mouse_x && menu->menu_last_my == mouse_y) {

					/* Check if any popup menu was closed corruptedly,
						 * due to moving window, resizing window or any
						 * events which killed the focus of this window
						 */
					if (menu->quickwin) {
						if (menu->quickwin->server->close) {
							
							menu->quickwin->server->close = false;
							menu->quickwin->server->popuped = false;
							menu->visible = false;

							/* Give some time to compositor */
							sys_sleep(2);
						}
					}

					/* Check if previous menu was already visible while clicking
					 * on new menu for visibility, if true then hide the previous 
					 * one 
					 */
					if (menubar->active_menu && menubar->active_menu != menu &&
						menubar->active_menu->visible == true) {
						//XEQuickWindowClose(menubar->active_menu->quickwin, window);
						menubar->active_menu->visible = false;
						menubar->active_menu->quickwin->server->hide = true;
						menubar->active_menu->quickwin->server->popuped = false;
						menubar->active_menu = NULL;
					}

					/* if this menu was already visible, then hide it */
					if (menu->visible) {
						menu->quickwin->server->hide = true;
						menu->visible = false;
						menu->quickwin->server->popuped = false;
						/*Let the compositor update it's internal data
						 *structure 
						 */
						sys_sleep(2);
					}else {

						/* Here check for quick window, if it's already created */
						if (menu->quickwin == NULL) {
							int menu_w = 100;
							int menu_h = 0;
							if ((menu->menu_items->pointer * 20) > 100)
								menu_h += menu->menu_items->pointer * 20;
							else
								menu_h = 100;

							menu_h += 10;

							XEQuickWindow *qu = XECreateQuickWindow(window->app,window->shwin->x + menubar->base.x + menu->base.x, 
								window->shwin->y + menubar->base.y + menu->base.y,menu_w,menu_h,"Menu");
							menu->quickwin = qu;
						
							menu->pixbuf = create_canvas(menu_w,menu_h);
							menu->base.painter((XEWidget*)menu,window);
							XEQuickWindowUpdate(qu, menu->pixbuf, 0,0,menu_w,menu_h);
							menu->quickwin->server->popuped = true;
						}else {
							menu->quickwin->server->x = window->shwin->x + menubar->base.x + menu->base.x;
							menu->quickwin->server->y = window->shwin->y + menubar->base.y + menu->base.y;
							menu->quickwin->server->dirty = true;
							menu->quickwin->server->popuped = true;
							/*Let the compositor update it's internal data
							 *structure */
							sys_sleep(2);
						}
						menu->visible = true;
						menubar->active_menu = menu;
					}
					
				}
				menu->menu_last_mx = mouse_x;
				menu->menu_last_my = mouse_y;
				
			}

		}

	menubar->mouse_last_x = mouse_x;
	menubar->mouse_last_y = mouse_y;
	}



/*
 * XECreateMenubar -- Creates a menubar widget
 * @param win -- Pointer to main activity window
 */
XEMenubar *XECreateMenubar(XEWindow* win) {
	XEMenubar *menubar = (XEMenubar*)malloc(sizeof(XEMenubar));
	menubar->menu_list = list_init();
	menubar->custom_color = NULL;
	menubar->base.x = 0;
	menubar->base.y = 26;
	menubar->base.w = win->shwin->width;
	menubar->base.h = 22;
	menubar->base.mouse_event = XEMenubarMouseEvent;
	menubar->base.action_handler = NULL;
	menubar->base.destroy = NULL;
	menubar->base.hover = false;
	menubar->base.hover_painted = false;
	menubar->base.painter = XEDefaultMenubarPainter;
	menubar->mouse_last_x = 0;
	menubar->mouse_last_y = 0;
	return menubar;
}


/*
 * XEMenubarAdd -- Adds a menu to menubar list
 * @param menubar -- Pointer to menubar
 * @param menu -- Pointer to menu
 */
void XEMenubarAdd (XEMenubar *menubar, XEMenu* menu) {
	list_add(menubar->menu_list, menu);
}

/*
 * XECreateMenu -- Creates a menu
 * @param name -- menu name
 */
XEMenu *XECreateMenu (char* name) {
	XEMenu *menu = (XEMenu*)malloc(sizeof(XEMenu));

	/* By default Geometry of menu
	 * is null, either XEMenubar sets its
	 * geometry or popup menu
	 */
	menu->base.x = 0;
	menu->base.y = 0;
	menu->base.w = 0;
	menu->base.h = 0;
	menu->base.painter = XEDefaultMenuPainter;
	menu->menu_button_x = 0;
	menu->menu_button_y = 0;
	menu->menu_button_w = 0;
	menu->menu_button_h = 0;
	menu->menu_items = list_init();
	menu->name = (char*)malloc(strlen(name)+1);
	strcpy(menu->name, name);
	menu->parent_link = NULL;
	menu->pixbuf = NULL;
	menu->visible = false;
	menu->calculated_metrics = false;
	return menu;
}


void XEMenuCalculateItemMetrics (XEMenu *menu) {
	int _menu_y_ = 10;
	int _menu_x_ = 10;
	for (int i = 0; i < menu->menu_items->pointer; i++) {
		XEMenuItemButton *item_button = (XEMenuItemButton*)list_get_at(menu->menu_items, i);
		item_button->base.x = _menu_x_;
		item_button->base.y = _menu_y_;
		item_button->base.w = menu->base.w;
		_menu_y_ += item_button->base.h + 5;
	}

	menu->calculated_metrics = true;
}

void XEMenuAddItem (XEMenu* menu, XEMenuItemButton* item) {
	list_add(menu->menu_items, item);
}

XEMenuItemButton * XECreateMenuItem (char* text,XEMenu *next_menu, XEMenu* parent) {
	XEMenuItemButton *menu_item = (XEMenuItemButton*)malloc(sizeof(XEMenuItemButton));
	menu_item->base.x = 0;
	menu_item->base.y = 0;
	menu_item->base.w = 0;
	menu_item->base.h = MENU_ITEM_BUTTON_HEIGHT;
	menu_item->base.painter = XEDefaultMenuItemPainter;
	menu_item->name = (char*)malloc(strlen(text)+1);
	strcpy(menu_item->name, text);
	menu_item->next_menu = next_menu;
	menu_item->parent = parent;
	return menu_item;
}
