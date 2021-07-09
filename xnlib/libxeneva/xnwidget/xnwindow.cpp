/**
 ** Copyright (C) Manas Kamal Choudhury 2021
 **
 ** xnwindow.h -- Xeneva Application Window
 **
 ** /PROJECT - Aurora {Xeneva}
 ** /AUTHOR  - Manas Kamal Choudhury 
 **
 ** ===============================================
 **/

#include <xnwidget\xnwindow.h>
#include <xnsys.h>
#include <xnwidget\xnwidget.h>
#include <mm.h>
#include <gui\font.h>
#include <xnwidget\geom_rect.h>

xn_window_t * xn_create_window (uint32_t x, uint32_t y, uint32_t w, uint32_t h, char* title) {
	int title_len = strlen (title);
	xn_window_t * win = (xn_window_t*)malloc (sizeof (xn_window_t));
	win->x = x;
	win->y = y;
	win->w = w;
	win->h = h;
	win->title = (char*)malloc(title_len);
	win->xn_widget = initialize_list ();
	win->dirty_rects = initialize_list ();
	for (int i = 0; i < title_len; i++) 
		win->title[i] = title[i];

	return win;
}

void xn_paint_titlebar (xn_window_t* win, bool default_min, bool default_max, bool default_close) {
	uint32_t color_close = ORANGE;
	uint32_t color_max = PALEGREEN;
	uint32_t color_min = YELLOW;
	if (default_min)
		color_min = GOLD;
	if (default_max)
		color_max = DARKGREEN;
	if (default_close)
		color_close = RED;

	drawer_draw_filled_circle (win->x + 20, win->y + 20,10,color_close);
	drawer_draw_filled_circle (win->x + 45, win->y + 20, 10, color_max);
	drawer_draw_filled_circle (win->x + 70, win->y + 20, 10, color_min);
	draw_string (win->title, win->x + (win->w/2) - 50, win->y + 10,LIGHTSILVER,0x2F2F2F);
}

void xn_paint_window (xn_window_t* win) {
	drawer_draw_rect_unfilled(win->x,win->y,win->w,win->h,0x000000);
	drawer_draw_rect(win->x + 1, win->y + 1, win->w -2, win->h-2,0xFFFFFF);
	drawer_draw_rect(win->x + 1, win->y + 1, win->w - 2, 35,  0x2F2F2F);
	
	xn_paint_titlebar (win,false,false,false);
	
	for (int i = 0; i < win->xn_widget->pointer; i++) {
		xn_widget *widget = (xn_widget*)list_get_at (win->xn_widget,i);
		widget->paint_handler (widget, win);
	}
}



void xn_show_window (xn_window_t *win) {
	xn_paint_window (win);
}

void xn_move_window (xn_window_t *win) {
	xn_paint_window (win);
}


void xn_window_add (xn_window_t *win, xn_widget *widget) {
	list_add  (win->xn_widget, widget);
}

void xn_handle_mouse (xn_window_t *win, int mouse_x, int mouse_y, bool button_state) {
	
	for (int i = 0; i < win->xn_widget->pointer; i++) {
		xn_widget * wid = (xn_widget*)list_get_at(win->xn_widget,i);
		if (mouse_x >= (win->x + wid->x)  && mouse_x < (win->x + wid->x + wid->w) &&
			mouse_y >= (win->y + wid->y) && mouse_y < (win->y + wid->y + wid->h)) {
				wid->on_mouse_button(wid,win,button_state);
		}
	}	
}



void xn_handle_close_button (xn_window_t* win) { 
	xn_paint_titlebar (win,false, false, true);
}