///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   Path2d -> Vector based path drawing
///!
///!   /PROJECT - Aurora's Xeneva v1.0
///!   /AUTHOR  - Manas Kamal Choudhury
///!
////!================================================

#ifndef __PATH_2D_H__
#define __PATH_2D_H__

#include <stdint.h>
#include <stdlib.h>

typedef struct _point_ {
	float x;
	float y;
}point_t;


typedef struct _edges_ {
	point_t start;
	point_t end;
	uint8_t direction;
}edges_t;

typedef struct _path_ {
	uint32_t color;
	bool new_start;
	int pos;
	int lastpos;
	int startx;
	int lastx;
	int starty;
	int lasty;
	size_t nextAlloc;
	edges_t edges[];
}path2d_t;


XE_EXTERN XE_EXPORT path2d_t *acrylic_create_path (uint32_t color, float x, float y);
XE_EXTERN XE_EXPORT void acrylic_path_move_to (canvas_t *canvas,path2d_t *p, float x, float y);
XE_EXTERN XE_EXPORT void acrylic_path_curve_to (canvas_t *canvas,path2d_t *p, float x1, float y1, float x2, float y2, float x3, float y3);
XE_EXTERN XE_EXPORT void acrylic_path_line_to (canvas_t *canvas,path2d_t *p, float x, float y);
XE_EXTERN XE_EXPORT void acrylic_path_fill (canvas_t *canvas,path2d_t *p, uint32_t color);
XE_EXTERN XE_EXPORT void acrylic_path_close (path2d_t* p);
#endif