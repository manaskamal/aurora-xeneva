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

typedef struct _QuWindow_ {
	unsigned x;
	unsigned y;
	unsigned width;
	unsigned height;
	unsigned drag_x;
	unsigned drag_y;
	bool draggable;
	bool visible;
	unsigned int *canvas;
	unsigned short owner_id;
	bool decorate;
	QuList *dirty_areas;
	struct _QuWindow_ *next;
	struct _QuWindow_ *prev;
}QuWindow;


extern QuWindow* QuWindowCreate (unsigned x, unsigned y, uint16_t owner_id);
extern void QuWindowSetSize (QuWindow* win, unsigned width, unsigned height);
extern void QuWindowSetCanvas(QuWindow* win, unsigned int *canvas);
extern void QuWindowSetVisible (QuWindow* win,bool visible);
extern void QuWindowAddDirtyArea (QuWindow* win, QuRect *dirty_rect);
extern void QuWindowDraw (QuWindow* win);


#endif