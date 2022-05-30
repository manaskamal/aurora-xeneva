///! Copyright (C) Manas Kamal Choudhury 2021
///!
///! path2d.cpp -- Path drawing
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!============================================

#include <acrylic.h>
#include <path2d.h>
#include <string.h>
#include <limits.h>
#include <sys\_term.h>

path2d_t *acrylic_create_path (uint32_t color, float x, float y) {
	//path2d_t *p = (path2d_t*)malloc(sizeof(path2d_t));
	//p->color = color;
	//p->pos = 0;
	//p->new_start = true;
	//p->nextAlloc = 2;
	//p->edges[p->pos].start.x = x;
	//p->edges[p->pos].start.y = y;
	//p->lastpos = p->pos;
	return 0; //p;
}

void acrylic_path_move_to (canvas_t *canvas,path2d_t *p, float x, float y) {
	/*if (p->new_start != true && p->pos) {
		acrylic_path_line_to(canvas,p, p->edges[p->lastpos].start.x, p->edges[p->lastpos].start.y);
	}

	if (p->pos + 1 == p->nextAlloc) {
		p->nextAlloc *= 2;
		p = (path2d_t*)realloc (p, sizeof(path2d_t) + sizeof(edges_t) * (p->nextAlloc));
	}
	p->edges[p->pos].start.x = x;
	p->edges[p->pos].start.y = y;
	p->lastpos = p->pos;
	p->new_start = true;*/
}


void acrylic_path_line_to (canvas_t *canvas,path2d_t *p, float x, float y) {
	//if (p->new_start) {
	//	p->edges[p->pos].end.x = x;
	//	p->edges[p->pos].end.y = y;
	//	acrylic_draw_line(canvas,p->edges[p->pos].start.x,
	//		p->edges[p->pos].start.y,
	//	    p->edges[p->pos].end.x,
	//	    p->edges[p->pos].end.y,
	//	    p->color);
	//	p->new_start = false;
	//	p->pos++;
	//} else {
	//	if (p->pos + 1 == p->nextAlloc) {
	//		p->nextAlloc *= 2;
	//		p = (path2d_t*)realloc (p, sizeof(path2d_t) + sizeof(edges_t) * (p->nextAlloc));
	//	}
	//	p->edges[p->pos].start.x = p->edges[p->pos-1].end.x;
	//	p->edges[p->pos].start.y = p->edges[p->pos-1].end.y;
	//	p->edges[p->pos].end.x = x;
	//	p->edges[p->pos].end.y = y;
	//	acrylic_draw_line(canvas,p->edges[p->pos].start.x,
	//		p->edges[p->pos].start.y,
	//	    p->edges[p->pos].end.x,
	//	    p->edges[p->pos].end.y,
	//	    p->color);
	//	p->pos++;
	//	p->new_start = false;
	//}
	
}

void acrylic_path_curve_to (canvas_t *canvas,path2d_t *p, float x1, float y1, float x2, float y2, float x3, float y3) {
	//int x_c[4];
	//int y_c[4];
	//p->edges[p->pos].start.x = p->edges[p->pos-1].end.x;
	//p->edges[p->pos].start.y = p->edges[p->pos-1].end.y;
	//p->edges[p->pos].end.x = x3;
	//p->edges[p->pos].end.y = y3;
	//x_c[0] = p->edges[p->pos-1].end.x;
	//y_c[0] = p->edges[p->pos-1].end.y;
	//x_c[1] = x1;
	//y_c[1] = y1;
	//x_c[2] = x2;
	//y_c[2] = y2;
	//x_c[3] = x3;
	//y_c[3] = y3;
	//acrylic_draw_bezier (canvas,x_c, y_c, p->color);
	//p->pos++;
}
void acrylic_path_fill (canvas_t *canvas,path2d_t *p, uint32_t color) {
	/*int xi[512];
	memset(xi,0,512);
	float slope[512];
	memset(slope, 0, 512);
	int dx;
	int dy;
	int temp;
	int ymax = 0;

	for (int i = 0; i < p->pos; i++) {
		if (p->edges[i].start.y > ymax)
			ymax = p->edges[i].start.y;
	}

	for (int i = 0; i < p->pos; i++) {
		dx = p->edges[i].end.x - p->edges[i].start.x;
		dy = p->edges[i].end.y - p->edges[i].start.y;
		if (dy==0)slope[i] = 1.0;
		if (dx==0)slope[i] = 0.0;
		if (dx != 0 && dy != 0)
			slope[i]=(float)dx/dy;
	}


	for (int j = 0; j <= ymax; j++) {
		int k = 0;
		for (int i = 0; i < p->pos; i++) {
			if (((p->edges[i].start.y <= j) && (p->edges[i].end.y > j)) ||
				((p->edges[i].start.y > j) && (p->edges[i].end.y <= j))) {
					xi[k]= (int)(p->edges[i].start.x + slope[i]*(j- p->edges[i].start.y));
					k++;
			}
		}

		for (int m =0; m<k-1; m++) {
			for (int i = 0; i < k-1; i++) {
				if (xi[i]> xi[i+1]) {
					temp = xi[i];
					xi[i]=xi[i+1];
					xi[i+1]=temp;
				}
			}
			for (int i =0; i < k; i+=2) {
				acrylic_draw_line(canvas,xi[i], j, xi[i+1]+1,j,color);
			}
		}
	}*/

}

void acrylic_path_close (path2d_t* p) {
	//size_t size = p->pos + 1;
	//path2d_t tmp;
	//memcpy (&tmp,p,sizeof(path2d_t));

	//if (p->new_start){
	//	size--;
	//}else {
	//	p->edges[p->pos].start.x = p->edges[p->pos-1].end.x;
	//	p->edges[p->pos].start.y = p->edges[p->pos-1].end.y;
	//	p->edges[p->pos].end.x = p->edges[p->lastpos].start.x;
	//	p->edges[p->pos].end.y = p->edges[p->lastpos].start.y;
	//}

	//sys_print_text ("Closing path lp-> %d\n", p->lastpos);
	//sys_print_text ("Closing path pos -> %d\n", p->pos);

	//for (int i = 0; i < size; ++i) {
	//	if (p->edges[i].start.y < p->edges[i].end.y) {
	//		p->edges[i].direction = 1;  //! clockwise (left to right)
	//	}else {
	//		p->edges[i].direction = -1; //! anti-clockwise (right to left)
	//		point_t point = p->edges[i].start;
	//		p->edges[i].start = p->edges[i].end;
	//		p->edges[i].end = point;
	//	}
	//}

	////p->pos = size;
	//p->starty = INT_MAX;
	//p->lasty = INT_MIN;
	//p->startx = INT_MAX;
	//p->lastx = INT_MIN;

	//for (int i = 0; i < size; ++i) {
	//	if (p->edges[i].end.y + 1 > p->lasty) 
	//		p->lasty = p->edges[i].end.y + 1;
	//	if (p->edges[i].start.y + 1 > p->lasty)
	//		p->lasty = p->edges[i].start.y + 1;
	//	if (p->edges[i].end.y < p->starty)
	//		p->starty = p->edges[i].end.y;
	//	if (p->edges[i].start.y < p->starty) 
	//		p->starty = p->edges[i].start.y;

	//	if (p->edges[i].end.x + 2 > p->lastx)
	//		p->lastx = p->edges[i].end.x + 2;
	//	if (p->edges[i].start.x + 2 > p->lastx) 
	//		p->lastx = p->edges[i].start.x + 2;
	//	if (p->edges[i].end.x < p->startx)
	//		p->startx = p->edges[i].end.x;
	//	if (p->edges[i].start.x < p->startx)
	//		p->startx = p->edges[i].start.x;

	//}

	//if (p->lasty < p->starty) 
	//	p->starty = p->lasty;
	//if (p->lastx < p->startx)
	//	p->startx = p->lastx;

}
