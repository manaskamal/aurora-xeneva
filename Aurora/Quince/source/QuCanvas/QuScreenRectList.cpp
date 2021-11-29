///!  
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuScreenRectList.cpp -- Entire screen rectangle
///!  
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!======================================================


#include <QuCanvas\QuScreenRectList.h>
#include <QuCanvas\QuCanvasMngr.h>
#include <acrylic.h>

QuRect scr_rect[512];
int scr_rect_count;

void QuScreenRectInit() {
	scr_rect_count = 0;
}

void QuScreenRectAdd (int x, int y, int w, int h) {
	scr_rect[scr_rect_count].x = x;
	scr_rect[scr_rect_count].y = y;
	scr_rect[scr_rect_count].w = w;
	scr_rect[scr_rect_count].h = h;
	scr_rect_count++;
}

void QuScreenRectUpdate  () {
	for (int i = 0; i < scr_rect_count; i++) {
		canvas_screen_update (QuGetCanvas(),scr_rect[i].x, scr_rect[i].y, scr_rect[i].w, scr_rect[i].h);
	}
	scr_rect_count = 0;
}