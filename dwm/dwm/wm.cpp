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


static winlist *window_list;
static window_t *focus_win = NULL;
static window_t *window_head = NULL;
static window_t *window_last = NULL;
window_t windows[100] = {0};
int window_count = 0;

void wm_initialize () {
	window_list = initialize_winlist ();
}


void wm_add_window(window_t *win) {
	//win_list_add (window_list,win);
	//focus_win = win;
	windows[window_count] = *win;
	window_count++;
	focus_win = win;
	//wm_window_move_to_front(win);
}


void wm_remove_window (window_t *win) {

	for (int i = 0; i < window_list->pointer; i++) {
		window_t *_win = (window_t*)win_list_get_at(window_list,i);
		if (_win == win) {
			win_list_remove (window_list, i);
			return;
		}
	}

}


void copy_to_screen55(uint32_t *buf, rect_t *r) {
	uint32_t* lfb = (uint32_t*)0x0000600000000000;
	int width = get_screen_width();
	int height = get_screen_height();
	for (int i=0; i < r->w; i++) {
		for (int j=0; j < r->h; j++){
			uint32_t color = buf[(r->x + i) + (r->y + j) * width] & 0xFFFFFF;
			lfb[(r->x + i) + (r->y + j) * width] = color;
		}
	}
}

void wm_handle_mouse_event (uint32_t mouse_x, uint32_t mouse_y, bool clicked, int delta_x, int delta_y) {
	message_t msg;
	window_t *front_win;
	int picker = 0;
	if (clicked) {
		for (int i = window_count - 1; i >= 0;i--) {
			window_t * win = &windows[i];
			if (mouse_x >= win->coord.x && mouse_x < (win->coord.x + win->coord.w)) {
				if (mouse_y >= win->coord.y && mouse_y < (win->coord.y + 40)) {
				
					if (focus_win != win) 
						focus_win = win;
					win->drag_off_x = mouse_x - win->coord.x;
					win->drag_off_y = mouse_y - win->coord.y;
					win->draggable_update = true;
					//copy_to_screen55(win->buffer,&win->coord);
				}
			}  
			if ( mouse_x >= win->coord.x && mouse_x < (win->coord.x + win->coord.w) &&
				mouse_y >= win->coord.y + 35 && mouse_y < (win->coord.y + win->coord.h)) {
					//Handle the window mouse event
					//Send the mouse click event to dedicated window's thread
					if (focus_win != win)
						focus_win = win;

					msg.type = 3;
		            msg.dword2 = mouse_x;
		            msg.dword3 = mouse_y;
		            msg.dword4 = focus_win->pid;
					msg.dword5 = clicked;
		            dwmmsg_send (&msg);
					memset (&msg,0,sizeof(message_t));
					sys_unblock_id(win->pid);
					win->draggable_update = false;
					wm_window_move_to_front(focus_win);
			}
		}
	}


	if (clicked == 0) {
		if (focus_win->draggable_update) {
			focus_win->draggable_update = false;
		}
	}

	if (focus_win->draggable_update) {
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
		wm_window_move_to_front(focus_win);
	}
	
}

void wm_paint_windows () {
	//if (once_paint == false) {
		/*for (int i = 0; i < window_list->pointer; i++) {
			window_t *win = (window_t*)win_list_get_at(window_list,i);
			copy_to_screen55(win->buffer,&win->coord);
		}*/
	//}
	for (int i = window_count - 1; i >= 0;i--) {
		window_t *win = &windows[i];
		copy_to_screen55(win->buffer,&win->coord);
	}
}

void wm_window_move_to_front (window_t *win) {
	window_t move_window = *win;
	int win_pos = win - windows;
	for (int i =win_pos; i >= 0; i--) {
		windows[i] = windows[i-1];
	}

	windows[0] = move_window;
}