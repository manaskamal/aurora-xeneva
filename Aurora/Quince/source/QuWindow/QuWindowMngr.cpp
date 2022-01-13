///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   QuWindowMngr -- Quince Window Manager
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///!
///!===================================================


#include <QuUtils\QuList.h>
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
QuWindow * resz_window = NULL;
uint8_t last_mouse_button = 0;

#define abs(a)  (((a) < 0)?-(a):(a))

void QuWindowMngr_Initialize () {
	WindowList = QuListInit ();
}


/**
 * QuWindowMngr_Add -- Adds a new window to window list
 * @param window -- new window address
 */
void QuWindowMngr_Add (QuWindow *window) {
	QuListAdd (WindowList, window);
	focus_win = window;
	draggable_win = window;
	top_window = window;
	prev_focused = window;
}


/**
 * QuWindowMngr_Remove -- Removes a window fro window list
 * @param win -- Window address to remove
 */
void QuWindowMngr_Remove (QuWindow *win) {
	for (int i = 0; i < WindowList->pointer; i++) {
		QuWindow *_win = (QuWindow*)QuListGetAt(WindowList,i);
		if (_win == win) {
			QuListRemove(WindowList, i);
			break;
		}
	}

	focus_win = NULL;
	draggable_win = NULL;
	top_window = NULL;
	prev_focused = NULL;
	resz_window = NULL;
}

/**
 * QuWindowMngr_GetList -- Returns the window list
 * @return -- Window List to return
 */
QuList *QuWindowMngr_GetList () {
	return WindowList;
}

/**
 * QuWindowMngrFindByID -- Finds a window by task id
 * @param id -- task id
 * @return win -- Resulted window to be returned
 */
QuWindow* QuWindowMngrFindByID (uint16_t id) {
	for (int i = 0; i < WindowList->pointer; i++) {
		QuWindow* win = (QuWindow*)QuListGetAt(WindowList, i);
		if (win->owner_id == id) {
			return win;
		}
	}
}

/**
 * QuWindowMngrSetFocus -- Set a window as focused window
 * @param win -- Window to be focused
 */
void QuWindowMngrSetFocus (QuWindow* win) {
	if (focus_win == win)
		return;
	focus_win = win;
}

QuWindow* QuWindowMngrGetFocused () {
	return focus_win;
}

QuWindow* QuWindowMngrGetDraggable() {
	return draggable_win;
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

	if (top_window != win || top_window == NULL) {
		QuWindowMngr_Remove(win);
		QuWindowMngr_Add(win);
		top_window = win;
	}

    focus_win = win;

	QuMessage msg;
	msg.type = QU_CANVAS_FOCUS_GAIN;
	msg.to_id = focus_win->owner_id;
	QuChannelPut (&msg, focus_win->owner_id);

	prev_focused = focus_win;
}


void QuWindowMngr_DrawAll () {	
	QuCanvasUpdateDirty();
	for (int i =  0; i < WindowList->pointer;  i++) {
		QuWindow* _win = (QuWindow*)QuListGetAt(WindowList, i);
		QuWindowDraw (_win);
	} 
}




void QuWindowMngr_MoveFocusWindow (int x, int y) {
	if (draggable_win == NULL)
		return;

	QuWindowInfo* info = (QuWindowInfo*)draggable_win->win_info_location;
	QuCanvasAddDirty(info->x - 5, info->y - 5, draggable_win->width + 5, draggable_win->height + 5);

	if (resz_window)
		resz_window = NULL;

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

	//!Store Old Coordinates
	for (int i = 0; i < WindowList->pointer; i++) {
		QuWindow* win_ = (QuWindow*)QuListGetAt (WindowList,i);
		//if (win_ == win) continue;
		QuWindowInfo *w_info = (QuWindowInfo*)win_->win_info_location;
		w_info->dirty = 1;
		w_info->rect_count=0;
	}

}

void QuWindowMngr_ResizeWindow(int x, int y) {
	if (resz_window == NULL)
		return;

	QuWindowInfo *info = (QuWindowInfo*)resz_window->win_info_location;
	QuCanvasAddDirty(info->x - 5, info->y - 5, resz_window->width + 5, resz_window->height + 5);

	resz_window->width = x - resz_window->resz_h;
	resz_window->height = y - resz_window->resz_v;

	for (int i = 0; i < WindowList->pointer; i++)  {
		QuWindow *win = (QuWindow*)QuListGetAt(WindowList, i);
		QuWindowInfo* info = (QuWindowInfo*)win->win_info_location;
		info->dirty =1;
		info->rect_count= 0;
	}

	QuMessage msg;
	msg.type = QU_CANVAS_RESIZE;
	msg.dword = resz_window->width;
	msg.dword2 = resz_window->height;
	QuChannelPut(&msg, resz_window->owner_id);
}

void QuWindowMngr_HandleMouse (int x, int y, uint8_t button, int mouse_code) {	
	//if (WindowList->pointer > 0){
	for (int i = WindowList->pointer - 1; i >= 0; i--) {
		QuWindow* win = (QuWindow*)QuListGetAt(WindowList, i);
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

			if (y >= (info->y + win->height - 10) && y < (info->y + win->height + 10)) {
				if (focus_win == win) {
					resz_window = win;
					resz_window->resz_h = x - resz_window->width;
					resz_window->resz_v = y - resz_window->height;	
				}
				break;
			}
		}
	}

	if (!button)  {
		draggable_win = NULL;
		resz_window = NULL;
	}

	/*if (draggable_win && button) {
		QuWindowMngr_MoveFocusWindow(x, y);
	}*/

	last_mouse_button = button;
}

void QuWindowMngr_HandleMouseUp (int x, int y) {
	if (draggable_win) {
		QuWindowMngr_MoveFocusWindow(x, y);
	}
	if (resz_window) {
		QuWindowMngr_ResizeWindow(x, y);
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
}


void QuWindowMngr_DrawBehind (QuWindow *current_win) {
	for (int i = 0; i < WindowList->pointer; i++) {
		QuWindow* win = (QuWindow*)QuListGetAt (WindowList,i);
		QuWindowInfo *info = (QuWindowInfo*)win->win_info_location;
		info->dirty = 1;
		info->rect_count = 0;
	}
}

bool QuWindowMngr_GetIntersections(QuWindow* win, QuWindow* current) {
	QuWindowInfo *wininfo = (QuWindowInfo*)win->win_info_location;
	QuWindowInfo *curinfo = (QuWindowInfo*)current->win_info_location;

	if ((wininfo->x > curinfo->x + current->width ) || (wininfo->x  + win->width < curinfo->x))
		return 0;
	if ((wininfo->y > curinfo->y + current->height) || (wininfo->y + win->height < curinfo->y))
		return 0;
	return 1;
}

QuRect * QuWindowMngr_RectOverlap (QuWindow *win1, QuWindow *win2) {
	QuRect * ret = (QuRect*)malloc(sizeof(QuRect));
	QuWindowInfo *win1info = (QuWindowInfo*)win1->win_info_location;
	QuWindowInfo *win2info = (QuWindowInfo*)win2->win_info_location;

	if (win1info->x + win1->width > win2info->x + win2->width) {
		ret->w = win2info->x + win2->width - max(win1info->x, win2info->x);
	}else {
		ret->w = win1info->x + win1->width - max(win1info->x, win2info->x);
	}

	ret->x = max(win1info->x, win2info->x);
	if (win1info->y + win1->height > win2info->y + win2->height) {
		ret->h = win2info->y + win2->height - max(win1info->y, win2info->y);
	}else {
		ret->h = win1info->y + win1->height - max(win1info->y, win2info->y);
	}
	ret->y = max(win1info->y, win2info->y); 
	return ret;
}