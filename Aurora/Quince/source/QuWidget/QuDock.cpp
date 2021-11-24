///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///! 
///!  QuTaskbar.cpp --- Quince Taskbar
///! 
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!================================================

#include <QuWidget\QuDock.h>
#include <acrylic.h>
#include <stdint.h>
#include <canvas.h>
#include <color.h>
#include <math.h>
#include <string.h>

int pos_x = 20;

void QuTaskbarInit () {


	QuTaskbarRepaint();
}




void QuTaskbarRepaint () {
	uint32_t color = 0xD9C0C0C0;
	uint32_t *wallp = (uint32_t*)0x0000060000000000;
	for (int i = 0; i < canvas_get_width(); i++){
		for (int j = 0; j < 50; j++) {
			uint32 alpha = wallp[(0 + i) + (canvas_get_height() - 50+j) * canvas_get_width()];
			uint32_t col = alpha_blend(alpha, color);
			canvas_draw_pixel(0 + i, (canvas_get_height() - 50 + j),col);
		}
	}
//	acrylic_draw_rect_filled (0 + (600/2), canvas_get_height() - 50,600,50,LIGHTBLACK);
	acrylic_draw_rect_unfilled (0, canvas_get_height() -50,canvas_get_width(), 50,BLACK);
	canvas_screen_update(0, canvas_get_height() -50,canvas_get_width(), 50);
}