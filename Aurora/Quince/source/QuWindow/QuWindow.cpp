///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   QuWindow -- Quince Window
///!
///!   /PROJECT -- Aurora's Xeneva
///!   /AUTHOR  -- Manas Kamal Choudhury 
///!
///!=================================================

#include <QuWindow\QuWindow.h>
#include <QuWindow\QuWindowMngr.h>
#include <QuWindow\QuWindowStyle.h>
#include <QuCanvas\QuCanvasMngr.h>
#include <QuWindow\QuTitleBar.h>
#include <QuCanvas\QuScreenStack.h>
#include <QuRect.h>
#include <stdlib.h>
#include <acrylic.h>
#include <color.h>
#include <sys\_term.h>

#define QUWIN_DEFAULT_WIDTH   500
#define QUWIN_DEFAULT_HEIGHT  500

static bool UpdateToolbar = false;

QuWindow* QuWindowCreate (int x, int y, uint16_t owner_id, uint8_t attr) {
	QuWindow* win = (QuWindow*)malloc(sizeof(QuWindow));
	win->x = x;
	win->y = y;
	win->drag_x = 0;
	win->drag_y = 0;
	win->draggable = false;
	win->width = QUWIN_DEFAULT_WIDTH;
	win->height = QUWIN_DEFAULT_HEIGHT;
	win->visible = true;
	win->invalidate = true;
	win->canvas = NULL;
	win->owner_id = owner_id;
	win->decorate = true;
	win->attr = attr;
	win->dirty_areas = QuListInit ();
	win->titlebar_object = QuListInit ();
	QuWindowMngr_Add (win);
	
	QuWindowAddMinimizeButton(win);
	QuWindowAddMaximizeButton(win);
	QuWindowAddCloseButton(win);
	return win;
}

void QuWindowSetSize (QuWindow* win, unsigned width, unsigned height) {
	win->width = width;
	win->height = height;
}

void QuWindowSetCanvas(QuWindow* win, uint32_t *canvas) {
	win->canvas = canvas;
}

void QuWindowSetVisible (QuWindow* win,bool visible) {
	win->visible = visible;
}


void QuWindowAddDirtyArea (QuWindow* win, QuRect *dirty_rect) {
	QuListAdd (win->dirty_areas, dirty_rect);
}



void QuWindowRemoveDirtyArea (QuWindow* win, QuRect* dirty_rect) {
	for (int i = 0; i < win->dirty_areas->pointer; i++) {
		QuRect * r = (QuRect*)QuListGetAt(win->dirty_areas, i);
		if (r == dirty_rect)
			QuListRemove(win->dirty_areas, i);
	}
}

void QuWindowAddMinimizeButton (QuWindow *win) {
	QuTitleBarObject *minimize = QuCreateTitleBarObject(win->x + win->width - 43,win->y + 9, 11,18, QU_TITLE_BAR_OBJ_MINIMIZE);
	QuAddTitleBarObject(win, minimize);
}

void QuWindowAddMaximizeButton (QuWindow *win) {
	QuTitleBarObject *maximize = QuCreateTitleBarObject (win->x + win->width - 28, win->y + 9, 11, 18, 
		QU_TITLE_BAR_OBJ_MAXIMIZE);
	QuAddTitleBarObject(win, maximize);
}

void QuWindowAddCloseButton(QuWindow *win) {
	QuTitleBarObject *close = QuCreateTitleBarObject (win->x + win->width - 13, win->y + 9, 11, 18,
		QU_TITLE_BAR_OBJ_CLOSE);
	QuAddTitleBarObject (win, close);
}

void QuWindowDraw (QuWindow* win) {
	
	QuCanvasBlit (win,win->canvas, win->x, win->y + 23, win->width,win->height - 23);
	if (UpdateToolbar){
		QuWindowDrawTitlebar (win, win->x, win->y, win->width);
		UpdateToolbar = false;
	}

		
}

void QuWindowUpdateTitlebar (bool value) {
	UpdateToolbar = value;
}

bool QuWindowGetUpdateTitlebar() {
	return UpdateToolbar;
}

