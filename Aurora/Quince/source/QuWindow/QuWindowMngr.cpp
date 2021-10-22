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
#include <QuWindow\QuTitleBar.h>
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
	if (focus_win == win)
		return;


	if (top_window != win || top_window == NULL){
		QuWindowMngr_Remove(win);
		QuWindowMngr_Add(win);
		top_window = win;
		//QuWindowUpdateTitlebar(true);
	}

	focus_win = win;
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
			canvas_screen_update(_win->x, _win->y, _win->width, _win->height);	
		
	} 
}


void QuWindowMngr_UpdateWindow (bool value) {
	UpdateWindows = value;
}

bool QuWindowMngr_GetUpdateBit() {
	return UpdateWindows;
}

int QuWindowMngr_CheckOverlap(QuWindow* win1, QuWindow *win2) {
	if ((win1->x > win2->x + win2->width + 70) || (win1->x + win1->width + 70 < win2->x))
		return 0;

	if ((win1->y > win2->y + win2->height + 70) || (win1->y + win1->height + 70 < win2->y))
		return 0;

	return 1;
}


void QuWindowMngr_MoveFocusWindow (int x, int y) {
	QuCanvasAddDirty(draggable_win->x, draggable_win->y, draggable_win->width, draggable_win->height);
	//!Store Old Coordinates

	int oldx = draggable_win->x, oldy = draggable_win->y, oldh = draggable_win->height,
		oldw = draggable_win->width;

	draggable_win->x = x - draggable_win->drag_x;
	draggable_win->y = y - draggable_win->drag_y;

	
	if (draggable_win->x < 0)
		draggable_win->x = 0;

	if (draggable_win->y < 0)
		draggable_win->y = 0;

	if (draggable_win->x + draggable_win->width >= canvas_get_width())
		draggable_win->x  = canvas_get_width() - draggable_win->width;

	if (draggable_win->y + draggable_win->height >= canvas_get_height())
		draggable_win->y = canvas_get_height() - draggable_win->height;


	QuMessage msg;
	msg.type = QU_CANVAS_MOVE;
	msg.dword = draggable_win->x;
	msg.dword2 = draggable_win->y;
	QuChannelPut(&msg, draggable_win->owner_id);
	sys_unblock_id (draggable_win->owner_id);


	sys_sleep(1);

	QuWindowInfo *info = (QuWindowInfo*)draggable_win->win_info_location;
	info->dirty = 1;
	info->rect_count = 0;

	for (int i = 0; i < WindowList->pointer; i++) {
		QuWindow* win = (QuWindow*)QuListGetAt (WindowList,i);
		if (win == draggable_win) continue;
		if (win == draggable_win) continue;
		if (QuWindowMngr_CheckOverlap(draggable_win, win)){
			QuWindowInfo *info = (QuWindowInfo*)win->win_info_location;
			info->dirty = 1;
			info->rect_count=0;
			//break;
		}
	}

}


void QuWindowMngr_HandleMouse (int x, int y, uint8_t button, int mouse_code) {	
	//if (WindowList->pointer > 0){
	QuWindow* win;
	for (int i = 0; i < WindowList->pointer; i++) {
		win = (QuWindow*)QuListGetAt(WindowList, i);

		if (!(x >= win->x && x < (win->x + win->width) &&
			y >= win->y && y < (win->y + win->height))) 
			continue;
		
		
		if (button && !last_mouse_button) {
			//! Only a limited portion is available for dragging purpose
			if (y >= win->y && y < (win->y + 23)) {  
				draggable_win = win;
				draggable_win->drag_x = x - draggable_win->x;
				draggable_win->drag_y = y - draggable_win->y;
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
	if (!StreamEvent)
		return;

	QuMessage msg;
	msg.type = type;
	msg.from_id = get_current_pid();
	msg.to_id = win->owner_id;
	if (type == QU_CANVAS_MOUSE_MOVE) {
		msg.dword = x;
		msg.dword2 = y;
		msg.dword3 = code;
	}else if (type == QU_CANVAS_KEY_PRESSED) {
		msg.dword = code;
	}

	QuChannelPut(&msg,win->owner_id);
	sys_unblock_id(win->owner_id);
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