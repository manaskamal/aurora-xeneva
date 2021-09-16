///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuRect.h -- Quince Rectangle
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!===============================================

#ifndef __QU_RECT_H__
#define __QU_RECT_H__

#include <stdint.h>


typedef struct __QU_RECT__ {
	uint32_t x;
	uint32_t y;
	uint32_t w;
	uint32_t h;
}QuRect;


#endif