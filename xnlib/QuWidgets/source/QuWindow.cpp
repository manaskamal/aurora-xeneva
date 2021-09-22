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
#include <QuPanel.h>


QuWindow* root_win = NULL;


void QuCreateWindow (int x, int y, int w, int h) {
	QuWindow* win = (QuWindow*)malloc(sizeof(QuWindow));
	win->x = x;
	win->y = y;
	win->w = w;
	win->h = h;	
	win->widgets = QuListInit();
	root_win = win;
}

void QuWindowSetCanvas (uint32_t* address) {
	root_win->canvas = address;
}

QuWindow* QuGetWindow () {
	return root_win;
}

int QuWindowGetX() {
	return root_win->x;
}


int QuWindowGetY() {
	return root_win->y;
}

int QuWindowGetWidth () {
	return root_win->w;
}

int QuWindowGetHeight () {
	return root_win->h;
}

void QuWindowSetBound(int w, int h) {
	root_win->w = w;
	root_win->h = h;
}

void QuWindowAdd (QuWidget *widget) {
	QuListAdd(root_win->widgets, widget);
}

void QuWindowShow() {
	for (int i = 0; i < root_win->widgets->pointer; i++) {
		QuWidget* wid = (QuWidget*)QuListGetAt(root_win->widgets, i);
		wid->Refresh(wid, root_win);
	}

	QuPanelUpdate(root_win->x, root_win->y, root_win->w, root_win->h);
}


void QuWindowMove (int x, int y) {
	root_win->x = x;
	root_win->y = y;

	for (int i = 0; i < root_win->widgets->pointer; i++) {
		QuWidget* wid = (QuWidget*)QuListGetAt(root_win->widgets,i);
		wid->Refresh(wid, root_win);
	}

}

