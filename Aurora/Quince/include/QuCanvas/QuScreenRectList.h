///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  /PROJECT - Aurora's Xeneva v1.0
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!=================================================

#ifndef __QU_SCREEN_RECT_LIST_H__
#define __QU_SCREEN_RECT_LIST_H__

#include <QuRect.h>
#include <QuWindow\QuWindow.h>

extern void QuScreenRectInit ();
extern void QuScreenRectAdd (int x, int y, int w, int h);
extern void QuScreenRectUpdate ();

#endif