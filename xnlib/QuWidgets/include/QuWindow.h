///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuWindow.h -- Quince Window
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!================================================

#ifndef __QU_WINDOW_H__
#define __QU_WINDOW_H__

#include <stdint.h>
#include <QuBase.h>
#include <QuUtils\QuList.h>




typedef struct _QU_WIN_ {
	int x;
	int y;
	int w;
	int h;
	uint32_t*  canvas;
	QuList* widgets;
}QuWindow;

typedef struct _QuWidget_ {
	int x;
	int y;
	int width;
	int height;
	void (*Refresh) (struct _QuWidget_ *, QuWindow* win);
}QuWidget;

extern void QuCreateWindow (int x, int y, int w,int h);
extern void QuWindowSetCanvas (uint32_t* address);
extern QuWindow* QuGetWindow ();
extern int QuWindowGetX();
extern int QuWindowGetY();
extern int QuWindowGetWidth ();
extern int QuWindowGetHeight ();
extern void QuWindowSetBound (int width, int height);
extern void QuWindowAdd (QuWidget* wid);
extern void QuWindowShow();
extern void QuWindowMove (int x, int y);
#endif