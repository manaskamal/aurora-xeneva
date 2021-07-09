/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  drawer.h -- Drawer system initializer and some simple
 *              shapes drawing functions
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * =======================================================
 */

#include <gui\drawer.h>
#include <xnsys.h>
#include <string.h>

drawer_t draw_sys;

void drawer_register () {
	draw_sys.screen_width = get_screen_width ();
	draw_sys.screen_height = get_screen_height ();
	draw_sys.scanline = sys_get_scanline();
	//! Now send a message to DWM for a buffer
	uint16_t id = get_current_pid();
	message_t msg;
	msg.type = 2;
	msg.dword = 1;
	msg.dword3 = id;
	message_send(1,&msg);
	memset(&msg,0,sizeof(message_t));

	while (1) {
		message_poll (&msg);
		if (msg.type == 1){
			draw_sys.framebuffer = msg.dword10;
			draw_sys.win_coord_x = msg.dword5;
			draw_sys.win_coord_y = msg.dword6;
			memset(&msg,0,sizeof(message_t));
			break;
		}
	}
}


uint32_t drawer_get_screen_width () {
	return draw_sys.screen_width;
}

uint32_t drawer_get_screen_height () {
	return draw_sys.screen_height;
}

uint32_t* drawer_get_framebuffer () {
	return draw_sys.framebuffer;
}

uint32_t drawer_get_win_coord_x () {
	return draw_sys.win_coord_x;
}

uint32_t drawer_get_win_coord_y () {
	return draw_sys.win_coord_y;
}

uint16_t drawer_get_scanline () {
	return draw_sys.scanline;
}

void drawer_draw_pixel (unsigned x, unsigned y, uint32_t color) {
	draw_sys.framebuffer[x + y * draw_sys.screen_width] = color;
}

void drawer_draw_rect (unsigned x, unsigned y, unsigned w, unsigned h, uint32_t col) {
	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
			drawer_draw_pixel(x + i, y + j, col);
}

void drawer_draw_vertical_line (unsigned x, unsigned y, unsigned length, uint32_t color) {
	drawer_draw_rect(x,y,1,length,color);
}

void drawer_draw_horizontal_line (unsigned x, unsigned y, unsigned length, uint32_t color) {
	drawer_draw_rect (x,y,length,1,color);
}


void drawer_draw_rect_unfilled (int x, int y, int width, int height, uint32_t color) {
	drawer_draw_horizontal_line ( x, y, width, color); //top
	drawer_draw_vertical_line( x, y+1, height -2, color); //left
	drawer_draw_horizontal_line(x, y + height - 1, width, color); //bottom
	drawer_draw_vertical_line (x + width - 1, y + 1, height - 2, color); //right
}


void drawer_draw_filled_circle (int o_x, int o_y, int radius, uint32_t fill_color) {
	for(int y = -radius; y <= radius; y++)
		for (int x = -radius; x <= radius; x++)
			if(x * x +y*y <= radius * radius)
				drawer_draw_pixel (o_x + x, o_y + y, fill_color);
}

void drawer_dirty_update (rect_t *r, uint32_t pixel) {
	for (int i=0; i < r->w; i++) {
		for (int j=0; j < r->h; j++){
			drawer_get_framebuffer()[(r->x + i) + (r->y + j) * drawer_get_screen_width()] = pixel;
		}
	}
}


