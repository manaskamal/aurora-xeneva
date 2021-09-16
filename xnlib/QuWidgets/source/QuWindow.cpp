///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuWindow.h -- Quince Window
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!================================================

#include <QuWindow.h>
#include <QuBase.h>
#include <stdlib.h>

QuWindow* root_win = NULL;


void QuCreateWindow (unsigned x, unsigned y, unsigned w, unsigned h) {
	QuWindow* win = (QuWindow*)malloc(sizeof(QuWindow*));
	win->x = x;
	win->y = y;
	win->w = w;
	win->h = h;
	root_win = win;
}

void QuWindowSetCanvas (uint32_t* address) {
	root_win->canvas = address;
}

QuWindow* QuGetWindow () {
	return root_win;
}

unsigned QuWindowGetX() {
	return root_win->x;
}


unsigned QuWindowGetY() {
	return root_win->y;
}

unsigned QuWindowGetWidth () {
	return root_win->w;
}

unsigned QuWindowGetHeight () {
	return root_win->h;
}

