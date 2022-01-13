///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   QuWindow -- Quince Window
///!
///!   /PROJECT -- Aurora's Xeneva
///!   /AUTHOR  -- Manas Kamal Choudhury 
///!
///!=================================================

#ifndef __QU_WINDOW_H__
#define __QU_WINDOW_H__

#include <stdint.h>
#include <QuUtils\QuList.h>
#include <QuRect.h>
#include <ipc\QuChannel.h>
#include <canvas.h>
#include <QuWidget\QuDock.h>

//! Window Attributes
#define QU_WIN_MINIMIZABLE   1
#define QU_WIN_MAXIMIZABLE   2
#define QU_WIN_CLOSABLE      3
#define QU_WIN_NON_DRAGGABLE 4
#define QU_WIN_DRAGGABLE  5

#define QU_WIN_FULL (QU_WIN_MINIMIZABLE | QU_WIN_MAXIMIZABLE | \
	QU_WIN_CLOSABLE | QU_WIN_DRAGGABLE)

#define QU_WIN_CONFIG_AUTO_INVALIDATE 6
#define QU_WIN_SET_SIZE  7
#define QU_WIN_AUTO_INVALIDATE_RGN 8
#define QU_WIN_SET_ICON 9
#define QU_WIN_SET_POS  14



#define QU_WIN_INFO_START   0x00000A0000000000

typedef struct _QuWinInfo_ {
	bool dirty;
	int x;
	int y;
	QuRect rect[256];
	int rect_count;
	bool maximize;
	bool minimize;
	bool alpha;
	char data[50];
}QuWindowInfo;

typedef struct _QuWindow_ {
	//int x;
	//int y;
	int width;
	int height;
	int drag_x;
	int drag_y;
	int resz_v;
	int resz_h;
	bool visible;
	bool mark_for_close;
	unsigned int *canvas;
	unsigned short owner_id;
	int old_w;
	int old_h;
	int old_x;
	int old_y;
	uint8_t attr;
	int id;
	uint32_t *win_info_location;
	canvas_t *drop_shadow;
	QuDockEntry *dock;
}QuWindow;


extern QuWindow* QuWindowCreate (int x, int y, uint16_t owner_id, unsigned int* canvas);
extern void QuWindowSetSize (QuWindow* win, int width, int height);
extern void QuWindowSetCanvas(QuWindow* win, unsigned int *canvas);
extern void QuWindowSetVisible (QuWindow* win,bool visible);
extern void QuWindowDraw (QuWindow* win);

#endif