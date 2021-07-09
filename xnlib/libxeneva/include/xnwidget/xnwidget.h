/**
 ** Copyright (C) Manas Kamal Choudhury 2021
 **
 ** xnwidget.h -- Xeneva Widget Library Base header
 **
 ** /PROJECT - Aurora {Xeneva}
 ** /AUTHOR  - Manas Kamal Choudhury
 **
 ** ===================================================
 **/

#ifndef __XN_WIDGET_H__
#define __XN_WIDGET_H__

#include <stdint.h>
#include <gui\drawer.h>
#include <gui\colors.h>

//!XENEVA MESSAGE TYPES
#define CLIENT_READY                    1
#define CLIENT_MOVE_WIN                 2
#define CLIENT_EXIT_WIN                 3
#define CLIENT_MINIMIZE_WIN             4
#define CLIENT_MAXIMIZE_WIN             5
#define CLIENT_DRAG_WIN   CLIENT_MOVE_WIN


typedef struct _xn_widget_ {
	uint32_t x;
	uint32_t y;
	uint32_t w;
	uint32_t h;
	void *data_pointer;
	void (*paint_handler) (struct _xn_widget_*,struct _xn_win_ *win);
	void (*on_mouse_button) (struct _xn_widget_*, struct _xn_win_ *win, bool button_state);
}xn_widget;


#endif