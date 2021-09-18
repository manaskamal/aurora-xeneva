///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuTitleBar -- QuWindow Titlebar object
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!===============================================

#ifndef __QU_TITLE_BAR_H__
#define __QU_TITLE_BAR_H__

#include <stdint.h>
#include <QuWindow\QuWindow.h>
#include <stdlib.h>

#define QU_TITLE_BAR_OBJ_MINIMIZE  1
#define QU_TITLE_BAR_OBJ_MAXIMIZE  2
#define QU_TITLE_BAR_OBJ_CLOSE  3
#define QU_TITLE_BAR_OBJ_OTHER  4


typedef struct _QuTitleBarObj_ {
	unsigned x;
	unsigned y;
	unsigned w;
	unsigned h;
	uint8_t type;
}QuTitleBarObject;

extern QuTitleBarObject *QuCreateTitleBarObject (unsigned x, unsigned y, unsigned w, unsigned h, uint8_t type);
extern void QuAddTitleBarObject (QuWindow* win, QuTitleBarObject *obj);
extern void QuRemoveTitleBarObject (QuWindow* win, QuTitleBarObject *obj);
extern void QuWindowDrawTitlebar (QuWindow* win, unsigned x, unsigned y, unsigned w);
extern void QuUpdateTitleBar (QuWindow *win);
#endif