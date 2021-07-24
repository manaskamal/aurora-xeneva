/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  window.h -- Windowing System in DWM
 *
 *  /PROJECT - DWM { Desktop Window Manager }
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * =================================================
 */

#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <stdtypes.h>
#include <allocator.h>
#include <sys.h>
#include <bufmngr.h>
#include <winlist.h>
#include <dwm.h>

#define WIN_FOCUSED 10
#define WIN_UNFOCUSED 11
//! Window Structure
typedef struct _window_ {
	rect_t coord;
	int drag_off_x;
	int drag_off_y;
	uint32_t  *buffer;
	uint16_t pid;
	bool draggable_update;
	bool focus;
	bool close;
	winlist * menu_list;
	winlist * dirty_rect;
	struct _window_ *next;
	struct _window_ *prev;
}window_t;

//!create window
extern window_t* create_window (uint16_t id,uint16_t x, uint16_t y, uint16_t w, uint16_t h);

#endif