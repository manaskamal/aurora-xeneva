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

void xn_draw_popup_menu (xn_menu_t *menu, xn_window_t *win) {
	uint32_t menu_bk_color = LIGHTBLACK;
	int h = 26;
	xn_menu_item_t *item_0 = (xn_menu_item_t*)list_get_at(menu->items, 0);
	int w = (strlen (item_0->title) * 8) + 2;
	for (int i = 0; i < menu->items->pointer; i++) {
		xn_menu_item_t *item = (xn_menu_item_t*)list_get_at(menu->items, i);
		if ((strlen(item->title) * 8) + 2 > w)
			w = strlen (item->title) * 8 + 2;
	}

	for (int i = 0; i < menu->items->pointer; i++) {
		xn_menu_item_t *item = (xn_menu_item_t*)list_get_at(menu->items, i);

		drawer_draw_rect (menu->pos_x, win->y + 35 + h, w + 90,25, menu_bk_color); 
		draw_string (item->title, menu->pos_x + 4, win->y + 35 + h + 1, LIGHTSILVER ,menu_bk_color);
		h += 25;
	}
	drawer_update(win->x, win->y, win->w, win->h);
}


void xn_menubar_paint_handler (xn_widget *widget, xn_window_t *win) {
	xn_menubar_t * menubar = (xn_menubar_t*)widget->data_pointer;
	drawer_draw_rect (win->x, win->y + 35, menubar->base.w, menubar->base.h, LIGHTBLACK);
	
	int menu_pos_x = 10;
	uint32_t focus_color = 0;
	for (int i = 0; i < menubar->menus->pointer; i++) {
		xn_menu_t *menu = (xn_menu_t*)list_get_at (menubar->menus, i);
		menu->pos_x = win->x + menu_pos_x;
		menu->pos_y = win->y + 35 + 3;
		if (menu->clicked){
			drawer_draw_rect(win->x +  menu_pos_x - 2, win->y + 35, (strlen(menu->popup_title)* 8 + 4),25, BLACK);
			focus_color = BLACK;
			if (menu->items->pointer != 0)
				xn_draw_popup_menu (menu,win);
			menu->clicked = false;
		} else{
			focus_color = LIGHTBLACK;
		}

		if (menu->over_effect) {
			drawer_draw_rect_unfilled(win->x + menu_pos_x - 2, win->y + 35, (strlen(menu->popup_title)*8 + 4), 25, LIGHTSILVER);
			drawer_update (win->x + menu_pos_x - 2, win->y + 35, (strlen(menu->popup_title)*8 + 4), 25);
			drawer_update (win->x, win->y + 35, menubar->base.w, menubar->base.h);
			menu->over_effect = false;
		}
		draw_string (menu->popup_title,win->x +  menu_pos_x, win->y + 35 + 3,LIGHTSILVER, focus_color);
	
		menu_pos_x += strlen (menu->popup_title) * 8 + 20;  //55
	}
}


void xn_menubar_mouse_event (xn_widget *widget, xn_window_t* win,uint32_t mouse_x, uint32_t mouse_y, bool button_state) {
	//NOTHING TO DO NOW
	xn_menubar_t * menubar = (xn_menubar_t*)widget->data_pointer;
	if (button_state & 1) {
		if (menubar->active_menu != NULL) {
			xn_move_window(win);
		}


		for (int i = 0; i < menubar->menus->pointer; i++) {
		xn_menu_t *menu = (xn_menu_t*)list_get_at (menubar->menus, i);
		if (mouse_x >= menu->pos_x && mouse_x <= (menu->pos_x + (strlen(menu->popup_title)* 8 + 20)) &&
			mouse_y >= menu->pos_y && mouse_y <= (menu->pos_y + 35 + 3)){
				menu->clicked = true;
				menubar->active_menu = menu;
				//xn_menubar_paint_handler(widget, win);
				break;
		}
		}
	}
	else {
		for (int i = 0; i < menubar->menus->pointer; i++) {
			xn_menu_t *menu = (xn_menu_t*)list_get_at (menubar->menus, i);
			if (mouse_x >= menu->pos_x && mouse_x <= (menu->pos_x + (strlen(menu->popup_title)* 8 + 20)) &&
				mouse_y >= menu->pos_y && mouse_y <= (menu->pos_y + 35 + 3)){
					menu->over_effect = true;
					break;
			}
		}
	}

	xn_menubar_paint_handler(widget, win);
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
	menubar->active_menu = NULL;
	menubar->last_active_menu = NULL;
	menubar->on_button_pressed = 0;
	menubar->button_toogle = false;
	menubar->menus = initialize_list();
	return menubar;
}

void xn_menubar_add (xn_menubar_t *menubar, xn_menu_t *menu) {
	list_add (menubar->menus, menu);
}