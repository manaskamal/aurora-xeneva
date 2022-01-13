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
#include <font.h>
#include <QuUtils\QuList.h>
#include <QuImage\QuBmpImage.h>
#include <sys\_file.h>

int pos_x = 0;

QuList *dock_list;
void QuDockInit () {
	dock_list = QuListInit();
	QuDockRepaint();
}

void QuDockAdd (QuDockEntry *entry) {
	QuListAdd(dock_list,entry);
	UFILE file;
	int fd = sys_open_file(entry->icon_path,&file);
	unsigned char* image_data = (unsigned char*)malloc(file.size);
	sys_read_file (fd,image_data,&file);
	entry->icon_data = image_data;
}

void QuDockRemove (QuDockEntry *entry) {
	int index =0; 
	for(index = 0; index < dock_list->pointer; index++){
		QuDockEntry *_ent = (QuDockEntry*)QuListGetAt(dock_list,index);
		if(_ent == entry)
			break;
	}

	if(index != -1)
		QuListRemove(dock_list,index);
	pos_x -= 50;
}


void QuDockRepaint () {
	uint32_t color = 0x8C4D4C47;  //8C
	uint32_t *wallp = (uint32_t*)0x0000060000000000;

	//Blur 4 times for good glass effect
	acrylic_box_blur (QuGetCanvas(),wallp, wallp,0,canvas_get_height(QuGetCanvas()) -40,canvas_get_width(QuGetCanvas())-2,40);
	acrylic_box_blur (QuGetCanvas(),wallp, wallp,0,canvas_get_height(QuGetCanvas()) -40,canvas_get_width(QuGetCanvas())-2,40);
	acrylic_box_blur (QuGetCanvas(),wallp, wallp,0,canvas_get_height(QuGetCanvas()) -40,canvas_get_width(QuGetCanvas())-2,40);
	acrylic_box_blur (QuGetCanvas(),wallp, wallp,0,canvas_get_height(QuGetCanvas()) -40,canvas_get_width(QuGetCanvas())-2,40);

	for (int i = 0; i < canvas_get_width(QuGetCanvas()); i++){
		for (int j = 0; j < 40; j++) {
			uint32 alpha = wallp[(0 + i) + (canvas_get_height(QuGetCanvas()) - 40 +j) * canvas_get_width(QuGetCanvas())];
			uint32_t col = alpha_blend(alpha, color);
			canvas_draw_pixel(QuGetCanvas(),0 + i, (canvas_get_height(QuGetCanvas()) - 40 + j),col);
		}
	}

	int xpos = 0;
	for (int i = 0; i < dock_list->pointer; i++) {
		QuDockEntry *entry = (QuDockEntry*)QuListGetAt(dock_list, i);
		QuBmpImage *bmp = QuGetBMP(entry->icon_data);
		QuDrawBMP(QuGetCanvas(),bmp,xpos,canvas_get_height(QuGetCanvas())- 40);
		xpos += 50;
	}


	canvas_screen_update(QuGetCanvas(),0, canvas_get_height(QuGetCanvas()) -40,canvas_get_width(QuGetCanvas())-2, 40);
}


void QuRamWidget () {
	char used_ram [10];
	memset (used_ram , 0, 10);

	uint32_t u_r = sys_get_used_ram() / 1024 / 1024;

	sztoa (u_r, used_ram, 10);
	
	acrylic_font_set_size(16);
	acrylic_draw_rect_filled (QuGetCanvas(), 20,canvas_get_height(QuGetCanvas()) -40,100,40,0x8C4D4C47);
	acrylic_draw_arr_string (QuGetCanvas(),20,canvas_get_height(QuGetCanvas()) -40,used_ram,WHITE);
	acrylic_draw_arr_string (QuGetCanvas(),60,canvas_get_height(QuGetCanvas()) -40,"MB", WHITE);
	canvas_screen_update(QuGetCanvas(),0, canvas_get_height(QuGetCanvas()) -40,200, 40);
}