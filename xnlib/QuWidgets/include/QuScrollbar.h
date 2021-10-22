///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuScrollbar.h -- Quince Scrollbars 
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!==============================================

#ifndef __QU_SCROLLBAR_H__
#define __QU_SCROLLBAR_H__

#include <stdint.h>
#include <QuWindow.h>
#include <QuBase.h>

#define QU_SCROLLBAR_HORIZONTAL  1
#define QU_SCROLLBAR_VERTICAL    2

typedef struct _qu_scrollbar_ {
	QuWidget wid;
	int type;
	int thumb_x;
	int thumb_y;
	int thumb_sz;
	int thumb_drag_x;
	int thumb_drag_y;
}QuScrollBar;

extern QuScrollBar * QuCreateScrollbar (int type);
extern void QuScrollbar_SetThumbPos (QuScrollBar *scroll, int pos);
#endif