/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  dwm.h -- Desktop Window Manager {DWM}
 *
 *  /PROJECT - DWM { Desktop Window Manager}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *===============================================
 */

#ifndef __DWM_H__
#define __DWM_H__

#include <stdtypes.h>

//!rectangle structure
typedef struct _rect_ {
	uint32_t x;
	uint32_t y;
	uint32_t w;
	uint32_t h;
}rect_t;



//!Messages
#define DWM_MOUSE_MOVE 1
#define DWM_CREATE_WIN 2
#define DWM_KEY_EVENT  3

//!Window Messages to send
#define WM_CLOSE 6
#define WM_MAXIMIZE 7
#define WM_MINIMIZE 8

extern void initialize_screen ();
extern void draw_pixel (unsigned x, unsigned y, uint32_t color );
extern uint32_t get_pixel32bit (unsigned x, unsigned y);
extern void draw_pixel2 (unsigned x, unsigned y, uint32_t color );
extern void draw_pixel3 (unsigned x, unsigned y, uint32_t color );
extern void copy_to_screen(uint32_t *buf, rect_t *r);
extern void copy_to_screen2(uint32_t *buf, rect_t *r);
#endif