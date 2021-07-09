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
#endif