///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuWindow.h -- Quince Window
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!================================================

#ifndef __QU_WINDOW_H__
#define __QU_WINDOW_H__

#include <stdint.h>
#include <QuBase.h>
#include <QuRect.h>
#include <QuUtils\QuList.h>

#define QU_WIN_CONFIG_AUTO_INVALIDATE 6
#define QU_WIN_SET_SIZE 7
#define QU_WIN_AUTO_INVALIDATE_RGN 8
#define QU_WIN_SET_POS  14

//! Window Attributes
#define QU_WIN_MINIMIZABLE   1
#define QU_WIN_MAXIMIZABLE   2
#define QU_WIN_CLOSABLE      3
#define QU_WIN_NON_DRAGGABLE 4
#define QU_WIN_DRAGGABLE  5

//!Standard Control
#define QU_WIN_CONTROL_MINIMIZE  1
#define QU_WIN_CONTROL_MAXIMIZE  2
#define QU_WIN_CONTROL_CLOSE  3
#define QU_WIN_CONTROL_OTHER  4

struct _QU_WIN_ ;
struct _QuWidget_;

typedef struct _QuWinControl_ {
	int x;
	int y;
	int w;
	int h;
	uint8_t type;
	bool hover;
	bool restore;
	void (*ControlRedraw)(_QuWinControl_ *ctrl, _QU_WIN_ *win, bool bit);
	void (*ControlEvent) (_QuWinControl_ *ctrl, _QU_WIN_ *win, bool bit);
}QuWinControl;

typedef struct _QuWinInfo_ {
	bool dirty;
	QuRect rect[256];
	int rect_count;
}QuWinInfo;

typedef struct _QU_WIN_ {
	int x;
	int y;
	int w;
	int h;
	uint32_t*  canvas;
	uint32_t*  win_info_data;
	QuList* widgets;
	QuList* controls;
	_QuWidget_* focus_widget;
	_QuWidget_ *draggable_widget;
	bool decorate;
	char *title;
}QuWindow;

typedef struct _QuWidget_ {
	int x;
	int y;
	int width;
	int height;
	void (*Refresh) (struct _QuWidget_ *, QuWindow* win);
	void (*MouseEvent) (struct _QuWidget_*, QuWindow* win, int code,bool clicked, int x, int y);
	void (*KeyEvent) (struct _QuWidget_*, QuWindow *win, int code);
	void (*ActionEvent) (struct _QuWidget_*, QuWindow* win);
	void (*ScrollEvent) (struct _QuWidget_*, struct _QuWidget_*, QuWindow* win);
}QuWidget;

extern void QuCreateWindow (int x, int y, int w,int h, uint32_t* info_data, char* title);
extern void QuWindowEnableDecoration (bool value);
extern void QuWindowSetCanvas (uint32_t* address);
extern QuWindow* QuGetWindow ();
extern int QuWindowGetX();
extern int QuWindowGetY();
extern int QuWindowGetWidth ();
extern int QuWindowGetHeight ();
extern void QuWindowSetBound (int width, int height);
extern void QuWindowAdd (QuWidget* wid);
extern void QuWindowShow();
extern void QuWindowMove (int x, int y);
extern void QuWindowSetAutoInvalidation (bool value);
extern void QuWindowSetAutoInvalidateRegion (int x, int y, int w, int h);
extern void QuWindowSetSize (int width, int height);
extern void QuWindowSetPos (int x, int y);
extern void QuWindowHandleMouse (int mouse_x, int mouse_y, int code);
extern void QuWindowSetProperty (uint8_t prop);
extern void QuWindowShowControls (QuWindow *win);
extern void QuWindowAddControlEvent (int type, void (*Event)(QuWinControl *control, QuWindow* win, bool bit));
extern void QuWindowHandleKey (int code);
#endif