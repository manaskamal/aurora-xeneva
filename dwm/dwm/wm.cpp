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

#include <wm.h>
#include <dwmmsg.h>
#include <dwm.h>
#include <stack.h>
#include <allocator.h>


static winlist *window_list;
static window_t *focus_win = NULL;
static window_t *drag_win = NULL;
static window_t *window_head = NULL;
static window_t *window_last_focus = NULL;
static bool wm_window_paint = true;
static int wm_window_paint_count = 10;
static bool wm_user_area_update = false;
static int wm_window_user_paint_count = 0;
uint32_t * root_window_buffer = NULL;
bool root_window_present = false;


#define abs(a)  (((a) < 0)?-(a):(a))

void wm_initialize () {
	window_list = initialize_winlist ();
}


void wm_add_window(window_t *win) {
	win_list_add (window_list,win);
	//focus_win = win;
	focus_win = win;
	window_last_focus = win;
}


void wm_remove_window (window_t *win) {
	message_t msg;
  
	for (int i = 0; i < window_list->pointer; i++) {
		window_t *_win = (window_t*)win_list_get_at(window_list,i);
		if (_win == win) {
			win_list_remove (window_list, i);
		}
	}
	//window_count -= 1;
}

void subtract_rect (rect_t *s, rect_t* c) {
	if (c->y > s->y && c->y <= s->h) {
		rect_t *r = (rect_t*)dalloc(sizeof(rect_t));
		r->x = s->x; //top
		r->y = s->y; //left
		r->w = s->x;  //bottom
		r->h = c->y - 1; //right
		stack_push_rect (r);
	}

	if (c->x > s->x && c->x <= s->w) {
		rect_t *r = (rect_t*)dalloc(sizeof(rect_t));
		r->x = s->x - 1;
		r->y = s->y;
		r->w = c->x - 1;
		r->h = s->h;
		stack_push_rect(r);
	}
}
void wm_move_window(window_t *win, uint32_t mouse_x, uint32_t mouse_y) {
	message_t msg;
	
	if (win->draggable_update) {
		//wm_window_move_to_front(win);
		int oldx = focus_win->coord.x, oldy = focus_win->coord.y, oldh = focus_win->coord.h,
			oldw = focus_win->coord.w;
		rect_t curr_rect;
		focus_win->coord.x =  mouse_x - focus_win->drag_off_x;
		focus_win->coord.y =  mouse_y - focus_win->drag_off_y;
		int x = focus_win->coord.x, y = focus_win->coord.y;
		rect_t *rect1 = (rect_t*)dalloc(sizeof(rect_t));
		rect_t* rect2 = (rect_t*)dalloc(sizeof(rect_t));
		rect1->w = abs(x - oldx);
		rect2->h = abs(y - oldy);
		rect1->h = oldh - rect2->h;
		rect2->w = oldw;

		if (x > oldx) {
			rect1->x = oldx;
			rect2->x = oldx;
		} else {
			rect1->x = x + oldw;
			rect2->x = oldx;
		}

		if (y > oldy) {
			rect1->y = y;
			rect2->y = oldy;
		} else {
			rect1->y = oldy;
			rect2->y = y + oldh;
		}

		if (rect1->w != 0 && rect1->h != 0) {
			stack_push_rect (rect1);
		}

		if (rect2->w != 0 && rect2->h != 0) {
			stack_push_rect (rect2);
		}

		if (refresh_screen()) {
		msg.type = 2;
		msg.dword2 = focus_win->coord.x;
		msg.dword3 = focus_win->coord.y;
		msg.dword4 = focus_win->pid;
		msg.dword10 = focus_win->buffer;
		dwmmsg_send (&msg);
		memset (&msg,0,sizeof(message_t));
		sys_unblock_id(focus_win->pid);
		wm_paint_required(true);
		}
	}
}


void wm_set_focus_window (window_t *win) {
	if (focus_win == win)
		return;

	focus_win = win;
}

void wm_handle_mouse_event (uint32_t mouse_x, uint32_t mouse_y, bool clicked, int delta_x, int delta_y) {
	message_t msg;
	window_t *front_win;
	bool event_occured = 0;
//	if (clicked & 1){
	for (int i = 0; i < window_list->pointer; i++) {
		window_t* win = (window_t*)win_list_get_at(window_list, i);
			
		if (mouse_x >= win->coord.x && mouse_x < (win->coord.x + win->coord.w) &&
			mouse_y >= win->coord.y && mouse_y < (win->coord.y + 40)) {

		
				if (clicked & 1){
					if (drag_win != NULL){
						win->close = false;
						//Send Unfocused Message to last focused window
						msg.type = WIN_UNFOCUSED;
						msg.dword4 = window_last_focus->pid;
						dwmmsg_send (&msg);
						sys_unblock_id (window_last_focus->pid);
						window_last_focus->draggable_update = false;
						window_last_focus->focus = false;
						window_last_focus = drag_win;
						
						//!sleep for 2ms, let other application to update their changes
						sys_sleep(2);
						drag_win->focus = true;
						drag_win->drag_off_x = mouse_x - drag_win->coord.x;
						drag_win->drag_off_y = mouse_y - drag_win->coord.y;
						drag_win->draggable_update = true;
						break;
					} else {	
					    if (window_last_focus == NULL)
							window_last_focus = win;
						
						drag_win = win;
						
						wm_window_move_to_front(drag_win);
						break;
					}
				}
			}

		//!User Content Area!!!
		if (mouse_x >= win->coord.x && mouse_x <= (win->coord.x + win->coord.w) &&
			mouse_y >= win->coord.y + 35 && mouse_y <= (win->coord.y + win->coord.h)) {
				if (clicked & 1){
					//Handle the window mouse event
					//Send the mouse click event to dedicated window's thread
					event_occured = true;
				}
				
				if (focus_win == win) {
					win->focus = true;
					win->close = false;
					msg.type = 3;
					msg.dword2 = mouse_x;
					msg.dword3 = mouse_y;
					msg.dword4 = win->pid;
					msg.dword5 = event_occured;
					dwmmsg_send (&msg);
					memset (&msg,0,sizeof(message_t));
					sys_unblock_id(win->pid);
				}	
		}

			//!Close button
		if (mouse_x >= (win->coord.x + 20) && mouse_x <= (20 + 35) ) {
				if (focus_win == win) {
					win->close = true;
					wm_remove_window(win);
				}
		}
	}
	
//	}


	if (clicked == 0) {
		if (drag_win != NULL){
			drag_win->draggable_update = false;
		  
		}
		 drag_win = NULL;
		 event_occured = 0;
	}

	//!Dragging check
	if (drag_win != NULL) {
		if (drag_win->draggable_update) {
			wm_move_window(drag_win, mouse_x, mouse_y);	
		}
	}

	
}

void wm_paint_required (bool value) {
	wm_window_paint = value;
	wm_window_paint_count = 10;
}

void wm_paint_windows (rect_t *update_rect) {
	if (wm_window_paint) {
		//copy_to_screen2 ((uint32_t*)0x0000500000000000, update_rect);
	

win_paint:
		
		//! And now draw other windows except the root window
		for (int i = 0; i < window_list->pointer; i++) {
			window_t* win = (window_t*)win_list_get_at(window_list, i);	
			copy_to_screen2(win->buffer, &win->coord);  
			copy_to_screen ((uint32_t*)0x0000600000000000, &win->coord);
		}
		//! finally copy everything to screen
		
		if (wm_window_paint > 0)
			wm_window_paint_count--;

		
		if (wm_window_paint_count == 0)
			wm_window_paint = false;
		
	}

	//!send update command to GPU
	sys_fb_update();
	
}

void wm_window_move_to_front (window_t *win) {
    wm_set_focus_window(win);
	for (int i = 0; i < window_list->pointer; i++){
		window_t* win_ = (window_t*)win_list_get_at(window_list,i);
		if (win_ == win){
			win_list_remove(window_list, i);
			break;
		}
	}
	win_list_add(window_list, win);
	
}


window_t* wm_find_window_by_id (uint16_t id) {
	if (window_list->pointer > 0){
		for (int i = 0; i < window_list->pointer; i++){
			window_t* win_ = (window_t*)win_list_get_at(window_list,i);
			if (win_->pid == id){
				return win_;
			}
		}
	}
	return NULL;
}

window_t* wm_get_focused_window() {
	return focus_win;
}