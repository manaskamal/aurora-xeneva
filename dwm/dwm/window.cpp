/**
 * Copyright (C) Manas Kamal Choudhury 2021
 *
 * window.cpp -- Window Structure
 *
 * /PROJECT - DWM {Desktop Window Manager}
 * /AUTHOR  - Manas Kamal Choudhury
 *
 * =========================================
 */

#include <window.h>
#include <wm.h>


window_t* create_window (uint16_t id, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
	window_t *win = (window_t*)dalloc (sizeof(window_t));
	uint32_t* buffer = (uint32_t*)request_buffer(id);
	win->coord.x = x;
	win->coord.y = y;
	win->coord.w = w;
	win->coord.h = h;
	win->buffer = buffer;
	win->pid = id; 
	win->drag_off_x = 0;
	win->drag_off_y = 0;
	wm_add_window (win);
	return win;
}

