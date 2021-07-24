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

#ifndef __XN_WINDOW_H__
#define __XN_WINDOW_H__

#include <xnwidget\xnwidget.h>
#include <util\list.h>
//#include <xnwidget\xnmenubar.h>


typedef struct _xn_win_ {
	uint32_t x;
	uint32_t y;
	uint32_t w;
	uint32_t h;
	char *title;
	bool focus;
	list_t *xn_widget;
	list_t *dirty_rects;
	//xn_menubar_t *menubar;
}xn_window_t;

extern xn_window_t* xn_create_window (uint32_t x, uint32_t y, uint32_t w, uint32_t h, char* title);
extern void xn_show_window (xn_window_t* win);
extern void xn_move_window (xn_window_t *win);
extern void xn_window_add (xn_window_t* win, xn_widget *widget);
extern void xn_handle_mouse (xn_window_t *win, int mouse_x, int mouse_y, bool button_state);
extern void xn_handle_close_button (xn_window_t* win);
extern void xn_update_old (xn_window_t *win);
//extern void xn_set_menubar (xn_window_t* win, xn_menubar_t *menubar);

#endif