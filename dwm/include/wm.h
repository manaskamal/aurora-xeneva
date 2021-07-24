/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  wm.h -- Window Manager : specially keeps tracks of windows
 *
 *  /PROJECT - DWM {Desktop Window Manager}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ========================================================
 */

#ifndef __WM_H__
#define __WM_H__

#include <stdtypes.h>
#include <window.h>
#include <allocator.h>
#include <dwm.h>
#include <winlist.h>

//!Window Manager FUNCTIONS
extern void wm_initialize ();
extern void wm_add_window (window_t *win);
extern void wm_remove_window (window_t *win);
extern void wm_handle_mouse_event (uint32_t mouse_x, uint32_t mouse_y, bool clicked, int delta_x, int delta_y);
extern void wm_paint_windows (rect_t *update_rect);
extern void wm_window_move_to_front (window_t *win);
extern window_t* wm_find_window_by_id (int id);
extern window_t* wm_get_focused_window();
extern void wm_paint_required (bool value);
extern void wm_user_area_paint (window_t *win);
extern void wm_paint_user_area_required (bool value);
#endif