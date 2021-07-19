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
static window_t *window_head = NULL;
static window_t *window_last_focus = NULL;
window_t windows[100] = {0};
int window_count = 0;

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
		focus_win->coord.x =  mouse_x - focus_win->drag_off_x;
		focus_win->coord.y =  mouse_y - focus_win->drag_off_y;
		msg.type = 2;
		msg.dword2 = focus_win->coord.x;
		msg.dword3 = focus_win->coord.y;
		msg.dword4 = focus_win->pid;
		msg.dword10 = focus_win->buffer;
		dwmmsg_send (&msg);
		memset (&msg,0,sizeof(message_t));
		sys_unblock_id(focus_win->pid);
	}
}


void wm_handle_mouse_event (uint32_t mouse_x, uint32_t mouse_y, bool clicked, int delta_x, int delta_y) {
	message_t msg;
	window_t *front_win;
	int picker = 0;
	if (clicked) {
		//for (int i = window_count - 1; i >= 0;i--) {
		for (int i = 0; i < window_list->pointer; i++) {
			window_t* win = (window_t*)win_list_get_at(window_list, i);
			/*window_t * win = &windows[i];
			win->close = false;*/
			if (mouse_x > win->coord.x && mouse_x < (win->coord.x + win->coord.w)) {
				if (mouse_y > win->coord.y && mouse_y < (win->coord.y + 40)) {

					win->close = false;
					//Send Unfocused Message to last focused window
					msg.type = WIN_UNFOCUSED;
					msg.dword4 = window_last_focus->pid;
					dwmmsg_send (&msg);
					sys_unblock_id (window_last_focus->pid);
					window_last_focus->draggable_update = false;
					window_last_focus->focus = false;
					window_last_focus = win;
					//!sleep for 2ms, let other application to update their changes
					sys_sleep(2);

					win->focus = true;
					wm_window_move_to_front(win);
	                win->drag_off_x = mouse_x - win->coord.x;
	                win->drag_off_y = mouse_y - win->coord.y;
	                win->draggable_update = true;
	                focus_win = win;
					break;
				}
			}  

			//!User Content Area!!!
			if ( mouse_x >= win->coord.x && mouse_x <= (win->coord.x + win->coord.w) &&
				mouse_y >= win->coord.y + 35 && mouse_y <= (win->coord.y + win->coord.h)) {
					//Handle the window mouse event
					//Send the mouse click event to dedicated window's thread
					if (focus_win == win){
					win->focus = true;
					win->close = false;
					msg.type = 3;
					msg.dword2 = mouse_x;
					msg.dword3 = mouse_y;
					msg.dword4 = focus_win->pid;
					msg.dword5 = clicked;
					dwmmsg_send (&msg);
					memset (&msg,0,sizeof(message_t));
					sys_unblock_id(win->pid);
					win->draggable_update = false;
					}
					
			}

			//!Close button
			if (mouse_x <= (win->coord.x + 20) && mouse_y <= (win->coord.y + 20)) {
					win->close = true;
					wm_remove_window(win);
			}
		}
	}

	if (clicked != 1) {
		if (focus_win->draggable_update){
			focus_win->draggable_update = false;
		}
	}

	//!Dragging check
	if (focus_win->draggable_update && focus_win->focus) {
	   wm_move_window(focus_win, mouse_x, mouse_y);				
	}

}

void wm_paint_windows () {

	/*for (int i = window_count - 1; i >= 0;i--) {
		window_t *win = &windows[i];
		copy_to_screen2(win->buffer,&win->coord);
	}*/
	for (int i = 0; i < window_list->pointer; i++) {
		window_t* win = (window_t*)win_list_get_at(window_list, i);
		copy_to_screen2(win->buffer, &win->coord);
	}
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