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
	focus_win = win;
}

QuWindow* QuWindowMngrGetFocused () {
	return focus_win;
}


void QuWindowMngr_MoveFront (QuWindow *win) {
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
	if (WindowList->pointer > 0) {
		for (int i = 0; i < WindowList->pointer; i++) {
			QuWindow* _win = (QuWindow*)QuListGetAt(WindowList, i);
			QuWindowDraw (_win);
		}
	} 
	
}


void QuWindowMngr_DisplayWindow() {
	if (WindowList->pointer > 0) {
		if (UpdateWindows){
			for (int i = 0; i < WindowList->pointer; i++) {
				QuWindow* _win = (QuWindow*)QuListGetAt(WindowList, i);
				if (_win->invalidate){
					canvas_screen_update(_win->x, _win->y, _win->width, _win->height);	
					_win->invalidate = false;
				}
				
			}
		   UpdateWindows = false;
		}		
	} 
}


void QuWindowMngr_UpdateWindow (bool value) {
	UpdateWindows = value;
}

bool QuWindowMngr_GetUpdateBit() {
	return UpdateWindows;
}


void QuWindowMngr_MoveFocusWindow (int x, int y) {

	QuRect re;
	re.x = draggable_win->x;
	re.y = draggable_win->y;
	re.w = draggable_win->width;
	re.h = draggable_win->height;
	QuCanvasAddDirty(&re);

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


	QuUpdateTitleBar(focus_win);

	QuRect *r = (QuRect*)malloc(sizeof(QuRect));
	r->x = draggable_win->x;
	r->y = draggable_win->y;
	r->w = draggable_win->width;
	r->h = draggable_win->height;
	QuWindowAddDirtyArea(focus_win, r);

	for (int i = 0; i < WindowList->pointer; i++) {
		QuWindow* win = (QuWindow*)QuListGetAt (WindowList,i);
		if (win == draggable_win)
			continue;
		if (draggable_win->x >= win->x || win->x >= draggable_win->x &&
			draggable_win->y >= win->y || win->y >= draggable_win->y &&
			(draggable_win->x + draggable_win->width) >= (win->x + win->width) ||
			(win->x + win->width) >= (draggable_win->x + draggable_win->width)) {

				QuRect *r = (QuRect*)malloc(sizeof(QuRect));
				r->x = win->x;
				r->y = win->y;
				r->w = win->width;
				r->h = win->height;
				/*if (win->x + win->width > draggable_win->x + draggable_win->width) {
					r->w = draggable_win->x + draggable_win->width - max(win->x, draggable_win->x) + 50;
				}else {
					r->w = win->x + win->width - max (win->x, draggable_win->x) + 50;
				}

				r->x = max(win->x, oldx) - 50;
				if (win->y + win->height > draggable_win->y + draggable_win->height) {
					r->h = draggable_win->y + draggable_win->height - max(win->y, draggable_win->y) + 50;
				}else {
					r->h = win->y + win->height - max(win->y, draggable_win->y) + 50;
				}

				r->y = max(win->y, oldy) - 50;*/
				QuWindowAddDirtyArea(win, r);
		}
	}

	QuMessage msg;
	msg.type = QU_CANVAS_MOVE;
	msg.dword = draggable_win->x;
	msg.dword2 = draggable_win->y;
	QuChannelPut(&msg, draggable_win->owner_id);
	sys_unblock_id (draggable_win->owner_id);

}


void QuWindowMngr_HandleMouse (int x, int y, bool clicked) {
	if (WindowList->pointer > 0) {
	for (int i = 0; i < WindowList->pointer; i++) {
		QuWindow* win = (QuWindow*)QuListGetAt(WindowList, i);

		if (x > win->x && x < (win->x + win->width) &&
			y > win->y && y < (win->y + 40)) {

				if (clicked) {
					if (draggable_win != NULL) {
						draggable_win->drag_x = x + 12 - draggable_win->x;
						draggable_win->drag_y = y + 12 - draggable_win->y;
						draggable_win->draggable = true;
					//draggable_win = win;
					} else {
						if (draggable_win != win)
							draggable_win = win;
						if (focus_win != win)
							focus_win = win;
						QuWindowMngr_MoveFront(win);
					}
				}
		}

		if (x >= (win->x + win->width - 40) && x < (win->x + win->width + 1) && 
			y >= (win->y + win->height - 50) && y < (win->y + win->height + 1)){
				
				if (clicked){
					if(focus_win != win)
						focus_win = win;
					focus_win->draggable = false;
					focus_win->width += 10;
					focus_win->height += 10;
					QuRect *r = (QuRect*)malloc(sizeof(QuRect));
					r->x = focus_win->x;
					r->y = focus_win->y;
					r->w = focus_win->width;
					r->h = focus_win->height;
					QuWindowAddDirtyArea(focus_win, r);

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

	if (clicked)
		if (draggable_win) {
			QuWindowMngr_MoveFocusWindow (x,y);	
			draggable_win = NULL;
		}
	
}

void QuWindowMngr_HandleMouseUp (int x, int y) {
	/*if (draggable_win)
		draggable_win = NULL;*/
	
	
}


