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
#include <allocator.h>


static winlist *window_list;
static window_t *focus_win = NULL;
static window_t *drag_win = NULL;
static window_t *window_head = NULL;
static window_t *window_last_focus = NULL;
static bool wm_window_paint = true;
static int wm_window_paint_count = 0;
static bool wm_user_area_update = false;
static int wm_window_user_paint_count = 0;


void wm_initialize () {
	window_list = initialize_winlist ();
}


void wm_add_window(window_t *win) {
	win_list_add (window_list,win);
	//focus_win = win;
	/*windows[window_count] = *win;
	window_count++;*/
	focus_win = win;
	window_last_focus = win;
	//wm_window_move_to_front(win);
}


void wm_remove_window (window_t *win) {
	message_t msg;


	msg.type = 13;
	msg.dword4 = win->pid;
	dwmmsg_send (&msg);
	memset (&msg,0,sizeof(message_t));
	sys_unblock_id(win->pid);
	win->close = false;
		//!sleep for 2ms, let other application to update their changes
	sys_sleep(10);

	//window_t move_window = *win;
	//int win_pos = win - windows;
	//for (int i =win_pos; i >= 0; i--) {
	//	windows[i] = windows[i+1];
	//}
  
	for (int i = 0; i < window_list->pointer; i++) {
		window_t *_win = (window_t*)win_list_get_at(window_list,i);
		if (_win == win) {
			win_list_remove (window_list, i);
		}
	}
	//window_count -= 1;
}


void wm_move_window(window_t *win, uint32_t mouse_x, uint32_t mouse_y) {
	message_t msg;
	
	if (win->draggable_update) {
		//copy_to_screen2((uint32_t*)0x0000500000000000, &focus_win->coord);
		add_dirty_rect(&focus_win->coord);
		//copy_to_screen((uint32_t*)0x0000600000000000, &focus_win->coord);
		focus_win->coord.x =  mouse_x - focus_win->drag_off_x;
		focus_win->coord.y =  mouse_y - focus_win->drag_off_y;
		//copy_to_screen2((uint32_t*)0x0000500000000000, &focus_win->coord);
		//add_dirty_rect (&focus_win->coord);
		msg.type = 2;
		msg.dword2 = focus_win->coord.x;
		msg.dword3 = focus_win->coord.y;
		msg.dword4 = focus_win->pid;
		msg.dword10 = focus_win->buffer;
		dwmmsg_send (&msg);
		memset (&msg,0,sizeof(message_t));
		sys_unblock_id(focus_win->pid);

		//for (int i = 0; i < window_list->pointer;i++) {
		//	window_t * behind = (window_t*)win_list_get_at(window_list, i);
		//	if (behind == win) 
		//		continue;
		//	if ((win->coord.x + win->coord.w) >= behind->coord.x &&
		//		(behind->coord.x + behind->coord.w) >= win->coord.x &&
		//		win->coord.y <= (behind->coord.y + behind->coord.h) &&
		//		(win->coord.y + win->coord.h) >= behind->coord.y) {
		//			//add_dirty_rect(&behind->coord);
		//		//kprintf("Intersected");
		//	}
		//}
		enable_update(true);
		wm_paint_required(true);
	}
}


void wm_set_focus_window (window_t *win) {
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
						//wm_set_focus_window (win);
						//!sleep for 2ms, let other application to update their changes
						sys_sleep(2);
						drag_win->focus = true;
						drag_win->drag_off_x = mouse_x - drag_win->coord.x;
						drag_win->drag_off_y = mouse_y - drag_win->coord.y;
						drag_win->draggable_update = true;
						break;
					} else {
						wm_set_focus_window(win);
						add_dirty_rect (&win->coord);
						drag_win = win;
						
						if (window_last_focus == NULL)
							window_last_focus = win;
						wm_window_move_to_front(drag_win);
						break;
					}
				}
			}

		//!User Content Area!!!
		if (mouse_x >= win->coord.x && mouse_x <= (win->coord.x + win->coord.w) &&
			mouse_y >= win->coord.y + 35 && mouse_y <= (win->coord.y + win->coord.h)) {
				//wm_paint_required(true);
				wm_paint_user_area_required(true);
				//enable_update(true);
				if (clicked & 1){
					//Handle the window mouse event
					//Send the mouse click event to dedicated window's thread
					event_occured = true;
				}
				//enable_update (true);
					//focus_win == win;
					//drag_win = win;
				
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
					    //win->draggable_update = false;
					/*else {
						drag_win = win;
						wm_set_focus_window(win);
					}*/

				//}
				
		}

			//!Close button
		if (mouse_x >= (win->coord.x + 20) && mouse_x <= (20 + 35) && 
			mouse_y >= (win->coord.y + 20) && mouse_y <= (20 + 10)) {
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
			//focus_win = NULL;
			//drag_win = NULL;
		}
		//drag_win = NULL;
	}

	
}


void wm_paint_required (bool value) {
	wm_window_paint = value;
	wm_window_paint_count = 10;
}

void wm_paint_user_area_required (bool value) {
	wm_user_area_update = value;
	wm_window_user_paint_count = 10;
}


void wm_user_area_paint (window_t *win) {
	/*if (win->dirty_rect->pointer > 0) {
		for (int i = 0; i < win->dirty_rect->pointer; i++) {
			rect_t *r = (rect_t*)win_list_get_at (win->dirty_rect, i);
			copy_to_screen2 (win->buffer, r);
		}
	}*/

	/*rect_t *r = (rect_t*)dalloc(sizeof(rect_t));
	r->x = win->coord.x;
	r->y = win->coord.y + 35;
	r->w = win->coord.w;
	r->h = win->coord.h - 35;*/
	copy_to_screen2(win->buffer, &win->coord);
	//dfree(r);
}

void wm_paint_windows (rect_t *update_rect) {

	/*for (int i = window_count - 1; i >= 0;i--) {
		window_t *win = &windows[i];
		copy_to_screen2(win->buffer,&win->coord);
	}*/
	if (wm_window_paint) {
		for (int i = 0; i < window_list->pointer; i++) {
			window_t* win = (window_t*)win_list_get_at(window_list, i);
			copy_to_screen2(win->buffer, update_rect);
			//copy_to_screen((uint32_t*)0x0000600000000000, &win->coord);
			//print_text ("Win Coord -> X-. %d\n", win->coord.x);
			//print_text("Win Coord ->  y-> %d\n", win->coord.y);
			//add_dirty_rect (&win->coord);	//copy_to_screen((uint32_t*)0x0000600000000000, &win->coord);
		}

		if (wm_window_paint_count > 0) {
			wm_window_paint_count--;
		}else {
			wm_paint_required (false);
		}
	}

	if (wm_user_area_update) {
		for (int i = 0; i < window_list->pointer; i++) {
			window_t* win = (window_t*)win_list_get_at(window_list, i);
			wm_user_area_paint(win);
		}
		if (wm_window_user_paint_count > 0){
			wm_window_user_paint_count--;
		}else {
			wm_paint_user_area_required(false);
		}
	}
	//enable_update(true);
}

void wm_window_move_to_front (window_t *win) {
	/*window_t move_window = *win;
	int win_pos = win - windows;
	for (int i =win_pos; i >= 0; i--) {
		windows[i] = windows[i-1];
	}

	windows[0] = move_window;*/
	for (int i = 0; i < window_list->pointer; i++){
		window_t* win_ = (window_t*)win_list_get_at(window_list,i);
		if (win_ == win){
			win_list_remove(window_list, i);
			break;
		}
	}

	win_list_add(window_list, win);

}


window_t* wm_find_window_by_id (int id) {
	for (int i = 0; i < window_list->pointer; i++){
		window_t* win_ = (window_t*)win_list_get_at(window_list,i);
		if (win_->pid == id){
			return win_;
		}
	}

}

window_t* wm_get_focused_window() {
	return focus_win;
}