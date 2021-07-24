/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  menubar.cpp -- System Menubar
 *
 *  /PROJECT - Aurora Xeneva {DWM}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * =================================================
 */

#include <menubar.h>
#include <dwm.h>
#include <string.h>
#include <allocator.h>
#include <window.h>
#include <wm.h>


menubar_t *menubar = NULL;
void initialize_system_menubar () {
	menubar = (menubar_t*)dalloc(sizeof(menubar_t));
	menubar->menu_list = initialize_winlist();
}


void sys_menubar_add_menu (window_t * win, menu_t *menu) {
	win_list_add (win->menu_list, menu);
}


void draw_menubar () {
	int menu_pos_x = 10;
	draw_rect (0,0,dwm_get_screen_width(), 25, 0x3E3E3E);
	window_t * win = wm_get_focused_window();
	if (win->menu_list->pointer > 0) {
		for (int i = 0; i < win->menu_list->pointer; i++) {
			menu_t *menu = (menu_t*)win_list_get_at(win->menu_list, i);
			draw_string (menu->title,menu_pos_x,6,0xD9D9D9, 0x3E3E3E);
			menu_pos_x += strlen (menu->title) * 8 + 20;  //55
		}
	}

}