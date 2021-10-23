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
#include <QuCanvas\QuCanvasMngr.h>
#include <QuCanvas\QuScreenStack.h>
#include <QuRect.h>
#include <stdlib.h>
#include <acrylic.h>
#include <color.h>
#include <sys\_term.h>
#include <sys\mmap.h>

#define QUWIN_DEFAULT_WIDTH   500
#define QUWIN_DEFAULT_HEIGHT  500

static bool UpdateToolbar = true;

QuWindow* QuWindowCreate (int x, int y, uint16_t owner_id, uint32_t* canvas) {
	QuWindow* win = (QuWindow*)malloc(sizeof(QuWindow));
	win->x = x;
	win->y = y;
	win->drag_x = 0;
	win->drag_y = 0;
	win->draggable = false;
	win->width = QUWIN_DEFAULT_WIDTH;
	win->height = QUWIN_DEFAULT_HEIGHT;
	win->visible = true;
	win->canvas = canvas; //NULL;
	win->owner_id = owner_id;
	win->decorate = true;
	win->mark_for_close = false;
	win->attr = QU_WIN_FULL; //attr;
    QuWindowMngr_Add (win);
	return win;
}

void QuWindowSetSize (QuWindow* win, int width, int height) {
	win->width = width;
	win->height = height;
}

void QuWindowSetCanvas(QuWindow* win, uint32_t *canvas) {
	win->canvas = canvas;
}

void QuWindowSetVisible (QuWindow* win,bool visible) {
	win->visible = visible;
}


void QuWindowDraw (QuWindow* win) {

	QuCanvasBlit (win,win->canvas, win->x, win->y, win->width,win->height);	
}

void QuWindowUpdateTitlebar (bool value) {
	UpdateToolbar = value;
}

bool QuWindowGetUpdateTitlebar() {
	return UpdateToolbar;
}

