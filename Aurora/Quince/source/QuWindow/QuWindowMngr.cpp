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


QuList* WindowList = NULL;
QuWindow * focus_win = NULL;
QuWindow * draggable_win = NULL;
QuWindow * top_window = NULL;
bool UpdateWindows = false;
bool StreamEvent = true;

#define abs(a)  (((a) < 0)?-(a):(a))

void QuWindowMngr_Initialize () {
	WindowList = QuListInit ();
}


void QuWindowMngr_Add (QuWindow *window) {
	QuListAdd (WindowList, window);
	focus_win = window;
	draggable_win = window;
	//top_window = window;
}



void QuWindowMngr_Remove (QuWindow *win) {
	for (int i = 0; i < WindowList->pointer; i++) {
		QuWindow *_win = (QuWindow*)QuListGetAt(WindowList,i);
		if (_win == win) {
			QuListRemove(WindowList, i);
		}
	}
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
	QuWindowMngrSetFocus(win);

	if (top_window != win){
		QuWindowMngr_Remove(win);
		QuWindowMngr_Add(win);
		top_window = win;
		//QuWindowUpdateTitlebar(true);
	}
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


void QuWindowMngr_MoveFocusWindow (int x, int y) {

	QuRect *re = (QuRect*)malloc(sizeof(QuRect));
	re->x = draggable_win->x;
	re->y = draggable_win->y;
	re->w = draggable_win->width;
	re->h = draggable_win->height;
	QuCanvasAddDirty(re);
	//!Store Old Coordinates
	int oldx = draggable_win->x;
	int oldy = draggable_win->y;
	int oldw = draggable_win->width;
	int oldh = draggable_win->height;


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

	for (int i = 0; i < WindowList->pointer; i++) {
		QuWindow* win = (QuWindow*)QuListGetAt (WindowList,i);
		if (win == draggable_win)
			continue;
		if (draggable_win->x >= win->x || win->x >= draggable_win->x &&
			draggable_win->y >= win->y || win->y >= draggable_win->y &&
			(draggable_win->x + draggable_win->width) >= (win->x + win->width) ||
			(win->x + win->width) >= (draggable_win->x + draggable_win->width)) {

				QuWindowInfo *w_info = (QuWindowInfo*)win->win_info_location;
				w_info->dirty = 1;
				w_info->rect_count = 0;
		}
	}

	QuWindowInfo *info = (QuWindowInfo*)draggable_win->win_info_location;
	info->dirty = 1;
	info->rect_count = 0;


	QuMessage msg;
	msg.type = QU_CANVAS_MOVE;
	msg.dword = draggable_win->x;
	msg.dword2 = draggable_win->y;
	QuChannelPut(&msg, draggable_win->owner_id);
	sys_unblock_id (draggable_win->owner_id);

}


void QuWindowMngr_HandleMouse (int x, int y, bool clicked) {	
	if (WindowList->pointer > 0){
		for (int i = 0; i < WindowList->pointer; i++) {
			QuWindow* win = (QuWindow*)QuListGetAt(WindowList, i);
			if (x > win->x && x < (win->x + win->width) &&
				y > win->y && y < (win->y + 23)) {

					if (clicked) {
						if (draggable_win != NULL && draggable_win->attr != QU_WIN_NON_DRAGGABLE) {
							StreamEvent = false;
							draggable_win->drag_x = x - draggable_win->x;
							draggable_win->drag_y = y - draggable_win->y;
							draggable_win->draggable = true;
						}else {
							StreamEvent = false;
							if (draggable_win != win)
								draggable_win = win;
							QuWindowMngr_MoveFront(win);
						}
					}
			}

			///! Send the event to client
			/*if (x > win->x && x < (win->x + win->width) &&
				y > win->y + 23 && y < (win->y + win->height)) {
					if (focus_win == win) {
						QuWindowMngr_SendEvent (win, QU_CANVAS_MOUSE_MOVE, x, y, NULL);
					}
			}*/


			if (x >= (win->x + win->width - 40) && x < (win->x + win->width + 1) && 
				y >= (win->y + win->height - 50) && y < (win->y + win->height + 1)){
				
				if (clicked){
					if(focus_win != win)
						return;
					focus_win->draggable = false;
					focus_win->width += 10;
					focus_win->height += 10;

					QuMessage msg;
					msg.type = QU_CANVAS_RESIZE;
					msg.dword = focus_win->x;
					msg.dword2 = focus_win->y;
					QuChannelPut(&msg, focus_win->owner_id);
					sys_unblock_id(focus_win->owner_id);
				}
			}
		}
	}


	if (clicked) {
		if (draggable_win != NULL && draggable_win->attr != QU_WIN_NON_DRAGGABLE) {
			QuWindowMngr_MoveFocusWindow (x,y);	
		}
	}else {
		if (draggable_win)
			draggable_win = NULL;
		StreamEvent = true;
	}
}

void QuWindowMngr_HandleMouseUp (int x, int y) {
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


