/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  xnview.cpp -- XNView widget
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ====================================================
 */

#include <xnwidget\xnview.h>
#include <mm.h>
#include <xnwidget\xnwindow.h>
#include <gui\drawer.h>
#include <imaging\jpeg.h>

void xn_view_painter (xn_widget *wid, xn_window_t *win) {
	xn_view_t *v = (xn_view_t*)wid->data_pointer;
	if (v->type == XN_VIEW_IMAGE) {
		drawer_draw_image (v->image_data,win->x + wid->x, win->y + wid->y, v->base.w, v->base.h);
	} else {
		drawer_draw_rect (win->x + wid->x,win->y + wid->y,wid->w, wid->h, LIGHTSILVER);
	}
	drawer_update (win->x + wid->x, win->y + wid->y, wid->w, wid->h);
}

xn_view_t * xn_create_view (uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t type, unsigned char* data){
	xn_view_t *view = (xn_view_t*)malloc(sizeof(xn_view_t));
	view->base.x = x;
	view->base.y = y;
	view->base.w = w;
	view->base.h = h;
	view->base.data_pointer = view;
	view->base.on_mouse_button = NULL;
	view->base.paint_handler = xn_view_painter;
	view->base.type = WIDGET_CONTROL_VIEW;
	view->image_data = data;
	view->type = type;
	return view;
}
