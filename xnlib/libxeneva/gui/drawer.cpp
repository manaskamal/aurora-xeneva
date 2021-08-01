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
#include <mm.h>

drawer_t draw_sys;

#define DRAWER_UPDATE  6

void drawer_register (int type,uint32_t x, uint32_t y,uint32_t gui_width, uint32_t gui_height) {
	draw_sys.screen_width = get_screen_width ();
	draw_sys.screen_height = get_screen_height ();
	draw_sys.scanline = sys_get_scanline();
	//! Now send a message to DWM for a buffer
	uint16_t id = get_current_pid();
	message_t msg;
	msg.type = 2;
	msg.dword = 1;
	msg.dword3 = id;
	msg.dword5 = type;
	msg.dword6 = gui_width;
	msg.dword7 = gui_height;
	msg.dword8 = x;
	msg.dword9 = y;
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

void draw_circle_corner (int x, int y, int radius, uint32_t corner, uint32_t color) {

	int f = 1 - radius;
	int ddf_x = 1;
	int ddf_y = -1 * radius;
	int i = 0;
	int j = radius;

	while (i < j) {
		if (f >= 0) {
			j--;
			ddf_y += 2;
			f += ddf_y;
		}
		i++;
		ddf_x += 2;
		f += ddf_x;
		if (corner & 0x4) {
			drawer_draw_pixel(x + i, y + j, color);
			drawer_draw_pixel(x + j, y + i, color);
		}

		if (corner & 0x2) {
			drawer_draw_pixel(x+i, y - j, color);
			drawer_draw_pixel(x + j, y - i, color);
		}
		if (corner & 0x8) {
			drawer_draw_pixel( x - j, y + i, color);
			drawer_draw_pixel (x - i, y + j, color);
		}

		if (corner & 0x1) {
			drawer_draw_pixel(x - j, y - i, color);
			drawer_draw_pixel(x - i, y - j, color);
		}
	}
}

void draw_h_line_rr (int dx, int x1, int y1, uint32_t color) {
	for (int i = 0; i < dx; i++)
		drawer_draw_pixel (x1 + i, y1, color);
}

void draw_v_line_rr (int dy, int x1, int y1, uint32_t color){
	for (int i = 0; i < dy; i++)
		drawer_draw_pixel (x1, y1 + i, color);
}


void draw_rounded_rect (int x, int y, int w, int h, int radius, uint32_t color) {
	
	draw_h_line_rr (w - 2 * radius, x + radius, y, color);
	draw_h_line_rr (w - 2 * radius, x + radius, y + h - 1, color);
	draw_v_line_rr (h - 2 * radius, x, y + radius, color);
	draw_v_line_rr (h - 2 * radius, x + w - 1, y + radius, color);

	draw_circle_corner (x + radius, y + radius, radius, 1, color);
	draw_circle_corner (x + w - radius - 1, y + radius, radius, 2, color);
	draw_circle_corner (x + w - radius - 1, y + h - radius - 1, radius, 4, color);
	draw_circle_corner (x + radius, y + h - radius - 1, radius, 8, color);

}

void drawer_update (int x, int y, int w, int h) {
	message_t msg;
	msg.type = DRAWER_UPDATE;
	msg.dword5 = x;
	msg.dword6 = y;
	msg.dword7 = w;
	msg.dword8 = h;
	msg.dword10 = draw_sys.framebuffer;
	message_send (1, &msg);
	memset(&msg, 0, sizeof(message_t));
}


void drawer_draw_image (unsigned char* buffer,uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
	uint8_t* data = buffer;
	for (int i = 0; i < h; i++) {
		for (int k = 0; k < w; k++) {
			int j = k + i * w;
			uint8_t r = data[j * 3];        //data[i * 3];
			uint8_t g = data[j * 3 + 1];        //data[i * 3 + 1];
			uint8_t b = data[j * 3 + 2];       //data[i * 3 + 2];
			uint32_t rgb =  ((r<<16) | (g<<8) | (b)) & 0x00ffffff;  //0xFF000000 | (r << 16) | (g << 8) | b;
			rgb = rgb | 0xff000000;
			drawer_draw_pixel (x + k, y + i,rgb);
			j++;
		}
	}
}




