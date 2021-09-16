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
#include <QuRect.h>
#include <stdlib.h>
#include <acrylic.h>
#include <color.h>
#include <sys\_term.h>

#define QUWIN_DEFAULT_WIDTH   500
#define QUWIN_DEFAULT_HEIGHT  500

QuWindow* QuWindowCreate (unsigned x, unsigned y, uint16_t owner_id) {
	QuWindow* win = (QuWindow*)malloc(sizeof(QuWindow));
	win->x = x;
	win->y = y;
	win->drag_x = 0;
	win->drag_y = 0;
	win->draggable = false;
	win->width = QUWIN_DEFAULT_WIDTH;
	win->height = QUWIN_DEFAULT_HEIGHT;
	win->visible = true;
	win->canvas = NULL;
	win->owner_id = owner_id;
	win->decorate = true;
	win->dirty_areas = QuListInit ();
	QuWindowMngr_Add (win);
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


void QuWindowDraw (QuWindow* win) {
	if (win->dirty_areas->pointer > 0) {
		for (int i = 0; i < win->dirty_areas->pointer; i++) {
			QuRect * r = (QuRect*)QuListGetAt(win->dirty_areas, i);
			QuCanvasBlit (win->canvas, r->x, r->y, r->w, r->h);
			QuWindowDrawTitlebar (win->x, win->y, win->width);
			canvas_screen_update(r->x, r->y, r->w , r->h);		
			QuListRemove(win->dirty_areas, i);
			free(r);
		}
	}
}

