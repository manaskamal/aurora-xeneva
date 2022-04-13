/**
 *  Copyright (C) Manas Kamal Choudhury 2022
 *
 *  console.cpp -- Console widget
 *
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ===============================================
 */

#include "console.h"
#include <acrylic.h>
#include <color.h>
#include <stdlib.h>
#include <font.h>
#include <string.h>
#include "keyconvert.h"
#include <sys/_term.h>

void console_refresh (daisy_widget_t *widget, daisy_window_t *win) {
	console_t *con = (console_t*)widget;
	daisy_win_info_t *info = daisy_get_window_info(win);
	acrylic_draw_rect_filled (win->ctx,con->base.x,con->base.y,con->base.width,con->base.height, BLACK);

	int xoff = 0;
	int yoff = 0;
	int font_x = con->base.x;
	int font_y = con->base.y;
	for (int j = 0; j < NUMBER_OF_ROW; j++) {
		for (int i = 0; i < NUMBER_OF_COLUMN; i++) {
			char c = con->buffer[yoff * NUMBER_OF_COLUMN + xoff];
			acrylic_draw_arr_font(win->ctx, font_x, font_y, c,WHITE);
			font_x += 8;
			xoff++;
		}
		font_y += 12;
		yoff++;
	}
	
	//char c = con->buffer[yoff * NUMBER_OF_COLUMN + xoff];
	//acrylic_draw_arr_font(win->ctx,con->font_x, con->font_y,c,WHITE);
	//con->font_x += 8;
	sys_print_text ("Terminal refreshed \r\n");
}

void console_mouse_event (daisy_widget_t *widget, daisy_window_t *win,int button, bool clicked, int x, int y) {
}

void console_key_event (daisy_widget_t *widget, daisy_window_t *win, int code) {
	daisy_win_info_t *info = daisy_get_window_info(win);
	console_t *con = (console_t*)widget;
	char c = key_convert_to_ascii (code);
	con->buffer[con->cursor_y * NUMBER_OF_COLUMN + con->cursor_x] = c;
	con->cursor_x++;
	console_refresh(widget,win);
	daisy_window_update_rect_area(win,0,0,info->width, info->height);
}

void console_destroy (daisy_widget_t *widget) {
	console_t *c = (console_t*)widget;
	free(c);
}

console_t * create_console_widget (int x, int y, int w, int h) {
	console_t *c = (console_t*)malloc(sizeof(console_t));
	c->base.x = x;
	c->base.y = y;
	c->base.width = w;
	c->base.height = h;
	c->base.action_event = 0;
	c->base.destroy = console_destroy;
	c->base.mouse_event = console_mouse_event;
	c->base.refresh = console_refresh;
	c->base.scroll_event = 0;
	c->base.key_event = console_key_event;
	c->buffer = (char*)malloc(DEFAULT_BUF_SZ);
	memset(c->buffer, 0, DEFAULT_BUF_SZ);
	c->cell_width = 10;
	c->cell_height = 10;
	c->cursor_x = 0;
	c->cursor_y = 0;
	c->font_x = x;
	c->font_y = y;
	return c;
}