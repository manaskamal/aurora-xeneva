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
#define CLIENT_DESTROY   11

//!Widget Control Types
#define WIDGET_CONTROL_BUTTON  1
#define WIDGET_CONTROL_LABEL   2
#define WIDGET_CONTROL_MENU    3
#define WIDGET_CONTROL_TOOLBAR 4
#define WIDGET_CONTROL_VIEW 5

typedef struct _xn_widget_ {
	uint32_t x;
	uint32_t y;
	uint32_t w;
	uint32_t h;
	int type;
	void *data_pointer;
	void (*paint_handler) (struct _xn_widget_*,struct _xn_win_ *win);
	void (*on_mouse_button) (struct _xn_widget_*, struct _xn_win_ *win,uint32_t mouse_x, uint32_t mouse_y,  bool button_state);
}xn_widget;


#endif