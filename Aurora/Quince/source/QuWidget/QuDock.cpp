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
#include <QuCanvas\QuCanvasMngr.h>
#include <string.h>
#include <sys\mmap.h>
#include <sys\_xeneva.h>

int pos_x = 20;

void QuTaskbarInit () {


	QuTaskbarRepaint();
}




void QuTaskbarRepaint () {
	uint32_t color = 0x8CC0C0C0;  //D9
	uint32_t *wallp = (uint32_t*)0x0000060000000000;
	for (int i = 0; i < canvas_get_width(QuGetCanvas()); i++){
		for (int j = 0; j < 40; j++) {
			uint32 alpha = wallp[(0 + i) + (canvas_get_height(QuGetCanvas()) - 40 +j) * canvas_get_width(QuGetCanvas())];
			uint32_t col = alpha_blend(alpha, color);
			canvas_draw_pixel(QuGetCanvas(),0 + i, (canvas_get_height(QuGetCanvas()) - 40 + j),col);
		}
	}
//	acrylic_draw_rect_filled (0 + (600/2), canvas_get_height() - 50,600,50,LIGHTBLACK);
//	acrylic_draw_rect_unfilled (QuGetCanvas(),0, canvas_get_height(QuGetCanvas()) - 40,canvas_get_width(QuGetCanvas())-2, 40,BLACK);
	
	canvas_screen_update(QuGetCanvas(),0, canvas_get_height(QuGetCanvas()) -40,canvas_get_width(QuGetCanvas())-2, 40);
}


void QuRamWidget () {
	char used_ram [10];
	memset (used_ram , 0, 10);

	uint32_t u_r = sys_get_used_ram() / 1024 / 1024;

	sztoa (u_r, used_ram, 10);

	acrylic_draw_rect_filled (QuGetCanvas(), 20,canvas_get_height(QuGetCanvas()) -40,100,40,0x8CC0C0C0);
	acrylic_draw_arr_string (QuGetCanvas(),20,canvas_get_height(QuGetCanvas()) -40,used_ram,BLACK);
	acrylic_draw_arr_string (QuGetCanvas(),80,canvas_get_height(QuGetCanvas()) -40,"MB", BLACK);
	canvas_screen_update(QuGetCanvas(),0, canvas_get_height(QuGetCanvas()) -40,200, 40);
}