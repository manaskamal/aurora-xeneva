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
#include <sys/_term.h>


void  XEMenubarMouseEvent (XEWidget *widget, XEWindow *window, int mouse_x, int mouse_y, int button) {
	XEMenubar *menubar = (XEMenubar*)widget;

	for (int i = 0; i < menubar->menu_list->pointer; i++) {
		XEMenu* menu = (XEMenu*)list_get_at(menubar->menu_list, i);
		if (mouse_x >= window->shwin->x + menu->menu_button_x &&
			mouse_x < (window->shwin->x + menu->menu_button_x + menu->menu_button_w) &&
			mouse_y >= window->shwin->y + menu->menu_button_y && 
			mouse_y < (window->shwin->y + menu->menu_button_y + menu->menu_button_h)) {
				
				/* check for button click, if true then show the menu */
				if (button) {

					if (menubar->active_menu && menubar->active_menu != menu &&
						menubar->active_menu->visible == true) {
						XEQuickWindowClose(menubar->active_menu->quickwin);
						menubar->active_menu->visible = false;
						//menubar->active_menu->quickwin->server->hide = true;
						menubar->active_menu = NULL;
					}

					if (menu->visible) {
						XEQuickWindowClose(menu->quickwin);
						//menu->quickwin->server->hide = true;
						menu->visible = false;
					}else {
						if (menu->quickwin == NULL) {
							XEQuickWindow *qu = XECreateQuickWindow(window->app,window->shwin->x + menubar->base.x + menu->base.x, 
								window->shwin->y + menubar->base.y + menu->base.y,310,100,"Menu");
							menu->quickwin = qu;
							menu->visible = true;
						}else {
							menu->quickwin->server->dirty = true;
						}
						menubar->active_menu = menu;
						}
					}
				}

		}
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
	return menu;
}