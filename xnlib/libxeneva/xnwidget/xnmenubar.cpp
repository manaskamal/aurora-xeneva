/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  xnmenubar.cpp -- XN Menubar Widget
 *
 *  /PROJECT - Aurora Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ================================================
 */

#include <xnwidget\xnmenubar.h>

void xn_menubar_paint_handler (xn_widget *widget, xn_window_t *win) {
	xn_menubar_t * menubar = (xn_menubar_t*)widget->data_pointer;
	drawer_draw_rect (win->x, win->y + 35, menubar->base.w, menubar->base.h, LIGHTBLACK);

	int menu_pos_x = 10;
	for (int i = 0; i < menubar->menus->pointer; i++) {
		xn_menu_t *menu = (xn_menu_t*)list_get_at (menubar->menus, i);
		draw_string (menu->popup_title,win->x +  menu_pos_x, win->y + 35 + 3,LIGHTSILVER, LIGHTBLACK);
		menu_pos_x += strlen (menu->popup_title) * 8 + 20;  //55
	}
}


void xn_menubar_mouse_event (xn_widget *widget, xn_window_t* win, bool button_state) {
	//NOTHING TO DO NOW
	xn_menubar_t * menubar = (xn_menubar_t*)widget->data_pointer;
//	drawer_draw_rect (win->x, win->y + 35 ,100, win->h + 10, LIGHTSILVER);
}


xn_menubar_t *xn_create_menubar (xn_window_t* win) {
	xn_menubar_t *menubar = (xn_menubar_t*)malloc (sizeof(xn_menubar_t));
	menubar->base.x = 0;
	menubar->base.y = 35;
	menubar->base.w = win->w;
	menubar->base.h = 25;
	menubar->base.type = WIDGET_CONTROL_MENU;
	menubar->base.data_pointer = menubar;
	menubar->base.paint_handler = xn_menubar_paint_handler;
	menubar->base.on_mouse_button = xn_menubar_mouse_event;
	menubar->on_button_pressed = 0;
	menubar->button_toogle = false;
	menubar->menus = initialize_list();
	return menubar;
}

void xn_menubar_add (xn_menubar_t *menubar, xn_menu_t *menu) {
	list_add (menubar->menus, menu);
}