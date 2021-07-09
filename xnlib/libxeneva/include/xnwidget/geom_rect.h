/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  geom_rect.h -- Rectangle Geometry
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ================================================
 */

#ifndef __GEOM_RECT_H__
#define __GEOM_RECT_H__

#include <stdint.h>

typedef struct _rect_ {
	int x;  //top
	int y;  //left
	int w;  //right
	int h;  //bottom
}rect_t;

#endif