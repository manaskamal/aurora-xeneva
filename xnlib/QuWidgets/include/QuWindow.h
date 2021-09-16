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

typedef struct _QU_WIN_ {
	unsigned x;
	unsigned y;
	unsigned w;
	unsigned h;
	uint32_t*  canvas;
}QuWindow;


extern void QuCreateWindow (unsigned x, unsigned y, unsigned w, unsigned h);
extern void QuWindowSetCanvas (uint32_t* address);
extern QuWindow* QuGetWindow ();
extern unsigned QuWindowGetX();
extern unsigned QuWindowGetY();
extern unsigned QuWindowGetWidth ();
extern unsigned QuWindowGetHeight ();

#endif