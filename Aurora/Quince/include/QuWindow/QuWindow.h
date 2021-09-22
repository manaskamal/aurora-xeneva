///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   QuWindow -- Quince Window
///!
///!   /PROJECT -- Aurora's Xeneva
///!   /AUTHOR  -- Manas Kamal Choudhury 
///!
///!=================================================

#ifndef __QU_WINDOW_H__
#define __QU_WINDOW_H__

#include <stdint.h>
#include <QuWindow\QuList.h>
#include <QuRect.h>

//! Window Attributes
#define QU_WIN_MINIMIZABLE   1
#define QU_WIN_MAXIMIZABLE   2
#define QU_WIN_CLOSABLE      3
#define QU_WIN_NON_DRAGGABLE 4
#define QU_WIN_DRAGGABLE  5

#define QU_WIN_FULL (QU_WIN_MINIMIZABLE | QU_WIN_MAXIMIZABLE | \
	QU_WIN_CLOSABLE | QU_WIN_DRAGGABLE)


typedef struct _QuWindow_ {
	int x;
	int y;
	int width;
	int height;
	int drag_x;
	int drag_y;
	bool draggable;
	bool visible;
	unsigned int *canvas;
	unsigned short owner_id;
	bool decorate;
	QuList *dirty_areas;
	QuList *titlebar_object;
	uint8_t attr;
	struct _QuWindow_ *next;
	struct _QuWindow_ *prev;
}QuWindow;


extern QuWindow* QuWindowCreate (int x, int y, uint16_t owner_id, uint8_t attr = QU_WIN_FULL);
extern void QuWindowSetSize (QuWindow* win, int width, int height);
extern void QuWindowSetCanvas(QuWindow* win, unsigned int *canvas);
extern void QuWindowSetVisible (QuWindow* win,bool visible);
extern void QuWindowAddDirtyArea (QuWindow* win, QuRect *dirty_rect);
extern void QuWindowDraw (QuWindow* win);
extern void QuWindowAddMinimizeButton (QuWindow *win);
extern void QuWindowAddMaximizeButton (QuWindow *win);
extern void QuWindowAddCloseButton(QuWindow *win);

#endif