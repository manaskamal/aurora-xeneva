/** 
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  xnlabel.cpp -- XNLabel widget
 *
 *  /PROJECT - Aurora Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ===================================================
 */

#include <xnwidget\xnlabel.h>
#include <mm.h>

void xn_label_paint_handler (xn_widget *widget, xn_window_t *win) {
	xn_label_t * label = (xn_label_t*)widget->data_pointer;
	if (label->outline_type == LABEL_OUTLINE_FILLED)
		drawer_draw_rect_unfilled (win->x + label->base.x,win->y + label->base.y, label->base.w + strlen (label->label), 
		                           label->base.h,GRAY);
	draw_string (label->label, win->x + label->base.x + (label->base.w/2) - (strlen(label->label)*8/2),
		win->y + label->base.y + (label->base.h / 2),LIGHTBLACK,WHITE);
}

void xn_label_mouse_event (xn_widget *widget, xn_window_t* win, bool button_state) {
}

xn_label_t *xn_create_label (int x, int y, int w, int h,int outline_type, char* label_string) {
	int title_len = strlen (label_string);
	xn_label_t *label = (xn_label_t*)malloc (sizeof(xn_label_t));
	label->base.x = x;
	label->base.y = y;
	label->base.w = w;
	label->base.h = h;
	label->base.type = WIDGET_CONTROL_LABEL;
	label->base.data_pointer = label;
	label->base.paint_handler = xn_label_paint_handler;
	label->base.on_mouse_button = xn_label_mouse_event;
	label->label = (char*)malloc(title_len);
	label->outline_type = outline_type;
	for (int i = 0; i < title_len; i++) 
		label->label[i] = label_string[i];

	return label;
}