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
#include <string.h>
#include <canvas.h>


QuList* WindowList = NULL;
QuWindow * focus_win = NULL;
QuWindow * draggable_win = NULL;

#define abs(a)  (((a) < 0)?-(a):(a))

void QuWindowMngr_Initialize () {
	WindowList = QuListInit ();
}


void QuWindowMngr_Add (QuWindow *window) {
	QuListAdd (WindowList, window);
	focus_win = window;
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


void QuWindowMngr_DrawAll () {
    QuCanvasUpdateDirty();
	if (WindowList->pointer > 0) {
		for (int i = 0; i < WindowList->pointer; i++) {
			QuWindow* _win = (QuWindow*)QuListGetAt(WindowList, i);
			QuWindowDraw (_win);
		}
	}	
}


void QuWindowMngr_MoveFocusWindow (unsigned x, unsigned y) {
	//!Store Old Coordinates
	unsigned oldx = focus_win->x;
	unsigned oldy = focus_win->y;
	unsigned oldw = focus_win->width;
	unsigned oldh = focus_win->height;

	focus_win->x = x - focus_win->drag_x;
	focus_win->y = y - focus_win->drag_y;

	unsigned new_x = focus_win->x;
	unsigned new_y = focus_win->y;
	//!Dirty Fillup
	QuRect* r1 = (QuRect*)malloc(sizeof(QuRect));
	QuRect *r2 = (QuRect*)malloc(sizeof(QuRect));
	memset (r1, 0, sizeof(QuRect));
	memset (r2, 0, sizeof(QuRect));

	if (oldx > new_x)
		r1->w = oldx - new_x;
	else
		r1->w = new_x - oldx;
	//sys_print_text ("R1 -> w -.> %d\n", r1->w);
	if (oldy > new_y)
		r2->h = oldy - new_y;
	else 
		r2->h = new_y - oldy;

	r1->h = oldh - r2->h;
	r2->w = oldw;

	if (new_x > oldx) {
		r1->x = oldx;
		r2->x = oldx;
	} else {
		r1->x = new_x + oldw;
		r2->x = oldx;
	}

	if (new_y > oldy) {
		r1->y = new_y;
		r2->y = oldy;
	} else {
		r1->y = oldy;
		r2->y = new_y + oldh;
	}

	if (r1->w != 0 && r1->h != 0) {
		QuCanvasAddDirty(r1);
	}

	if (r2->w != 0 && r2->h != 0) {
		QuCanvasAddDirty(r2);
	}

	QuUpdateTitleBar(focus_win);

	QuRect *r = (QuRect*)malloc(sizeof(QuRect));
	r->x = focus_win->x;
	r->y = focus_win->y;
	r->w = focus_win->width;
	r->h = focus_win->height;
	QuWindowAddDirtyArea(focus_win, r);

	for (int i = 0; i < WindowList->pointer; i++) {
		QuWindow* win = (QuWindow*)QuListGetAt (WindowList,i);
		if (win == focus_win) 
			continue;
		if (focus_win->x > win->x && focus_win->x < (win->x + win->width + 1) &&
			focus_win->y > win->y && focus_win->y < (win->y + win->height + 1) ||
			win->x > focus_win->x && win->x < (focus_win->x + focus_win->width + 1) &&
			win->y > focus_win->y && win->y < (focus_win->y + focus_win->height + 1)) {

				QuRect *r = (QuRect*)malloc(sizeof(QuRect));
				if (win->x + win->width > focus_win->x + focus_win->width) {
					r->w = focus_win->x + focus_win->width - max(win->x, focus_win->x) + 50;
				}else {
					r->w = win->x + win->width - max (win->x, focus_win->x) + 50;
				}

				r->x = max(win->x, oldx) - 50;
				if (win->y + win->height > focus_win->y + focus_win->height) {
					r->h = focus_win->y + focus_win->height - max(win->y, focus_win->y) + 50;
				}else {
					r->h = win->y + win->height - max(win->y, focus_win->y) + 50;
				}

				r->y = max(win->y, oldy) - 50;
				QuWindowAddDirtyArea(win, r);
		}
	}
}

void QuWindowMngr_HandleMouseDown (unsigned x, unsigned y) {
	if (x >= focus_win->x && x < (focus_win->x + focus_win->width) &&
		y >= focus_win->y && y < (focus_win->y + 23)) {
			focus_win->drag_x = x - focus_win->x;
			focus_win->drag_y = y - focus_win->y;
			focus_win->draggable = true;
	}

}

void QuWindowMngr_HandleMouseUp (unsigned x, unsigned y) {
	QuWindowMngr_MoveFocusWindow (x,y);
}


