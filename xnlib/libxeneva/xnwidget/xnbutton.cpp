/**
 ** Copyright (C) Manas Kamal Choudhury 2021
 **
 ** xnbutton.h -- Xeneva Button Widget
 **
 ** /PROJECT - Aurora {Xeneva}
 ** /AUTHOR  - Manas Kamal Choudhury
 **
 ** ===========================================
 **/

#include <xnwidget\xnbutton.h>
#include <mm.h>
#include <xnsys.h>
#include <gui\font.h>


void xn_button_paint_handler (xn_widget *widget, xn_window_t *win) {
	xn_button_t * but = (xn_button_t*)widget->data_pointer;
	if (but->button_toogle) {
		drawer_draw_rect (win->x +  widget->x,win->y +  widget->y, widget->w, widget->h, LIGHTBLACK);
	    drawer_draw_rect (win->x +  widget->x,win->y +  widget->y, widget->w, widget->h /2,BLACK);	
		draw_string (but->text,win->x + widget->x + ((widget->w / 2) - ((strlen(but->text)*8)/2)),
			win->y + widget->y + (widget->h /2) - 3, LIGHTSILVER,LIGHTBLACK);
		
	}else {
		drawer_draw_rect (win->x + widget->x,win->y + widget->y, widget->w, widget->h, BLACK);
		drawer_draw_rect (win->x +  widget->x,win->y + widget->y, widget->w, widget->h /2,LIGHTBLACK);
		draw_string (but->text,win->x + widget->x + ((widget->w / 2) - ((strlen(but->text)*8) /2))
			, win->y + widget->y + (widget->h /2) - 4, WHITE,BLACK);
	}
	
}

void xn_button_mouse_event (xn_widget *widget, xn_window_t* win, uint32_t mouse_x, uint32_t mouse_y, bool button_state) {
	xn_button_t * but = (xn_button_t*)widget->data_pointer;

	if (button_state & 1){
		but->button_toogle = true;
	} else {
		but->button_toogle = false;
	}

	xn_button_paint_handler (widget,win);

    if (button_state & 1) {
		if (but->on_button_pressed)
			but->on_button_pressed(but);
	}


	drawer_update (win->x + but->base.x,win->y +  but->base.y, but->base.w, but->base.h);
}

xn_button_t * xn_create_button (int x, int y, int w, int h, char *title) {
	int title_len = strlen (title);
	xn_button_t *but = (xn_button_t*)malloc (sizeof(xn_button_t));
	but->base.x = x;
	but->base.y = y;
	but->base.w = w;
	but->base.h = h;
	but->base.type = WIDGET_CONTROL_BUTTON;
	but->base.data_pointer = but;
	but->base.paint_handler = xn_button_paint_handler;
	but->base.on_mouse_button = xn_button_mouse_event;
	but->on_button_pressed = 0;
	but->button_toogle = false;
	but->text = (char*)malloc(title_len);
	for (int i = 0; i < title_len; i++) 
		but->text[i] = title[i];
	return but;
}