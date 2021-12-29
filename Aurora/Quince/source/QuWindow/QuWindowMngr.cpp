///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   QuWindowMngr -- Quince Window Manager
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///!
///!===================================================


#include <QuWindow\QuList.h>
#include <QuWindow\QuWindowMngr.h>
#include <QuCursor.h>
#include <stdlib.h>
#include <QuCanvas\QuCanvasMngr.h>
#include <sys\_term.h>
#include <sys\_process.h>
#include <string.h>
#include <canvas.h>
#include <ipc\QuChannel.h>
#include <acrylic.h>
#include <color.h>
#include <QuCode.h>
#include <sys\_sleep.h>


QuList* WindowList = NULL;
QuWindow * focus_win = NULL;
QuWindow * prev_focused = NULL;
QuWindow * draggable_win = NULL;
QuWindow * top_window = NULL;
bool UpdateWindows = false;
bool StreamEvent = true;
uint8_t last_mouse_button = 0;

#define abs(a)  (((a) < 0)?-(a):(a))

void QuWindowMngr_Initialize () {
	WindowList = QuListInit ();
}


void QuWindowMngr_Add (QuWindow *window) {
	QuListAdd (WindowList, window);
	focus_win = window;
	draggable_win = window;
	top_window = window;
	prev_focused = window;
}



void QuWindowMngr_Remove (QuWindow *win) {
	for (int i = 0; i < WindowList->pointer; i++) {
		QuWindow *_win = (QuWindow*)QuListGetAt(WindowList,i);
		if (_win == win) {
			QuListRemove(WindowList, i);
		}
	}

	focus_win = NULL;
	draggable_win = NULL;
	top_window = NULL;
	prev_focused = NULL;
}


QuList *QuWindowMngr_GetList () {
	return WindowList;
}


QuWindow* QuWindowMngrFindByID (uint16_t id) {
	for (int i = 0; i < WindowList->pointer; i++) {
		QuWindow* win = (QuWindow*)QuListGetAt(WindowList, i);
		if (win->owner_id == id) {
			return win;
		}
	}
}

void QuWindowMngrSetFocus (QuWindow* win) {
	if (focus_win == win)
		return;
	focus_win = win;
}

QuWindow* QuWindowMngrGetFocused () {
	return focus_win;
}


void QuWindowMngr_MoveFront (QuWindow *win) {
	if (top_window == win)
		return;

	if (prev_focused != NULL) {
	QuMessage msg;
	msg.type = QU_CANVAS_FOCUS_LOST;
	msg.to_id = prev_focused->owner_id;
	QuChannelPut (&msg, prev_focused->owner_id);
	}


	if (top_window != win || top_window == NULL){
		QuWindowMngr_Remove(win);
		QuWindowMngr_Add(win);
		top_window = win;
		//QuWindowUpdateTitlebar(true);
	}

	//if (prev_focused != NULL) {
	//	QuMessage msg;
	//	msg.type = QU_CANVAS_FOCUS_LOST;
	//	msg.to_id = prev_focused->owner_id;
	//	QuChannelPut (&msg, prev_focused->owner_id);
	//}

    focus_win = win;

	QuMessage msg;
	msg.type = QU_CANVAS_FOCUS_GAIN;
	msg.to_id = focus_win->owner_id;
	QuChannelPut (&msg, focus_win->owner_id);

	prev_focused = focus_win;
}

bool QuWindowMngr_CheckTop (QuWindow *win) {
	QuWindow* win_ = (QuWindow*)QuListGetAt(WindowList, 1);
	if (win_ == win)
		return true;
	return false;
}

void QuWindowMngr_DrawAll () {	
     QuCanvasUpdateDirty();
	//if (WindowList->pointer > 0) {
		for (int i = 0; i < WindowList->pointer; i++) {
			QuWindow* _win = (QuWindow*)QuListGetAt(WindowList, i);
			QuWindowDraw (_win);
		}
	//} 
		
}

/*
 * Some specific clients will say to render whole frame in every frame update
 * this functions will only needed for that specific purpose
 */
void QuWindowMngr_DisplayWindow() {
	for (int i = 0; i < WindowList->pointer; i++) {
		QuWindow* _win = (QuWindow*)QuListGetAt(WindowList, i);
		QuWindowInfo *info = (QuWindowInfo*)_win->win_info_location;
			canvas_screen_update(QuGetCanvas(),info->x, info->y, _win->width, _win->height);	
		
	} 
}


void QuWindowMngr_UpdateWindow (bool value) {
	UpdateWindows = value;
}

bool QuWindowMngr_GetUpdateBit() {
	return UpdateWindows;
}



void QuWindowMngr_MoveFocusWindow (int x, int y) {
	QuWindowInfo* info = (QuWindowInfo*)draggable_win->win_info_location;

	QuCanvasAddDirty(info->x, info->y, draggable_win->width, draggable_win->height);
	//!Store Old Coordinates

	int oldx = info->x, oldy = info->y, oldh = draggable_win->height,
		oldw = draggable_win->width;

	info->x = x - draggable_win->drag_x;
	info->y = y - draggable_win->drag_y;

	
	if (info->x < 0)
		info->x = 0;

	if (info->y < 0)
		info->y = 0;

	/*if (draggable_win->x + draggable_win->width >= canvas_get_width())
		draggable_win->x  = canvas_get_width() - draggable_win->width;

	if (draggable_win->y + draggable_win->height >= canvas_get_height())
		draggable_win->y = canvas_get_height() - draggable_win->height;*/

	for (int i = 0; i < WindowList->pointer; i++) {
		QuWindow* win = (QuWindow*)QuListGetAt (WindowList,i);
		//if (win == draggable_win) continue;
		QuWindowInfo *w_info = (QuWindowInfo*)win->win_info_location;
		w_info->dirty = 1;
		w_info->rect_count=0;
	}

}


void QuWindowMngr_HandleMouse (int x, int y, uint8_t button, int mouse_code) {	
	//if (WindowList->pointer > 0){
	QuWindow* win;
	for (int i = 0; i < WindowList->pointer; i++) {
		win = (QuWindow*)QuListGetAt(WindowList, i);
		QuWindowInfo *info = (QuWindowInfo *)win->win_info_location;
		if (!(x >= info->x && x < (info->x + win->width) &&
			y >= info->y && y < (info->y + win->height))) 
			continue;
		
		
		if (button && !last_mouse_button) {
			//! Only a limited portion is available for dragging purpose
			if (y >= info->y && y < (info->y + 23)) {  
				draggable_win = win;
				draggable_win->drag_x = x - info->x;
				draggable_win->drag_y = y - info->y;
		        QuWindowMngr_MoveFront(win);
		        break;
			}
		//}
		}
	}

	if (!button) 
		draggable_win = NULL;

	/*if (draggable_win && button) {
		QuWindowMngr_MoveFocusWindow(x, y);
	}*/

	last_mouse_button = button;
}

void QuWindowMngr_HandleMouseUp (int x, int y) {
	if (draggable_win) {
		QuWindowMngr_MoveFocusWindow(x, y);
	}
}


void QuWindowMngr_SendEvent (QuWindow *win, int type, int x, int y, int code) {
	QuMessage msg;
	msg.type = type;
	msg.from_id = get_current_pid();
	msg.to_id = win->owner_id;
	msg.dword4 = win->id;
	if (type == QU_CANVAS_MOUSE_MOVE) {
		msg.dword = x;
		msg.dword2 = y;
		msg.dword3 = code;
	}else if (type == QU_CANVAS_KEY_PRESSED) {
		msg.dword = code;
	}
	QuChannelPut(&msg,win->owner_id);
	//sys_unblock_id(win->owner_id);
}

void QuWindowMngr_EventStreamEnable (bool value) {
	StreamEvent = value;
}



void QuWindowMngr_DrawBehind (QuWindow *current_win) {
	for (int i = 0; i < WindowList->pointer; i++) {
		QuWindow* win = (QuWindow*)QuListGetAt (WindowList,i);
		QuWindowInfo *info = (QuWindowInfo*)win->win_info_location;
		info->dirty = 1;
		info->rect_count = 0;
	}
}