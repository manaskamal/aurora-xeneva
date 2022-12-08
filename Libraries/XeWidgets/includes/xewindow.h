/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2021, Manas Kamal Choudhury
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 **/

#ifndef __XE_WINDOW_H__
#define __XE_WINDOW_H__

#include <stdint.h>
#include <canvas.h>
#include <sys\_xeneva.h>
#include <list.h>
#include <xebase.h>
#include <xewidget.h>

#define XE_WIN_DEFAULT_WIDTH  400
#define XE_WIN_DEFAULT_HEIGHT 400


#define XE_GLBL_CNTRL_CLOSE 1
#define XE_GLBL_CNTRL_MAXIMIZE 2
#define XE_GLBL_CNTRL_MINIMIZE 3
#define XE_GLBL_CNTRL_USER 4


typedef struct _pri_rect_ {
	int x;
	int y;
	int w;
	int h;
}pri_rect_t;


typedef struct _xe_sh_win_ {
	pri_rect_t rect[256];
	int rect_count;
	bool dirty;
	int x;
	int y;
	int width;
	int height;
	bool alpha;
	bool anim_on;
	uint8_t anim_type;
	uint8_t anim_frame_cnt;
	uint8_t shared_prop;
}XESharedWin;


typedef struct _xe_win_ {
	uint8_t attrib;
	uint32_t *backbuff;
	void *shared_win;
	canvas_t *ctx;
	char* title;
	uint32_t color;
	bool first_time;
	XESharedWin *shwin;
	list_t* global_controls;
	list_t* widgets;
	XeApp *app;
	void (*paint)(_xe_win_ *win);
}XEWindow;


/*
 * XEWidget structure
 */
typedef struct _xe_widget_ {
	int x;
	int y;
	int w;
	int h;
	int last_mouse_x;
	int last_mouse_y;
	bool clicked;
	bool hover;
	bool hover_painted;
	bool kill_focus;
	void (*action_handler)(_xe_widget_ *widget, XEWindow *win);
	void (*mouse_event)(_xe_widget_ *widget, XEWindow *win, int x, int y, int button);
	void (*painter) (_xe_widget_ *widget, XEWindow *win);
	void (*destroy) (_xe_widget_ *widget, XEWindow *win);
}XEWidget;

/* 
 * XEGlobalControl -- Global Control
 * Buttons structure
 */
typedef struct _global_control_ {
	int x;
	int y;
	int w;
	int h;
	uint8_t type;
	bool hover;
	bool clicked;
	uint32_t fill_color;
	uint32_t outline_color;
	uint32_t hover_fill_color;
	uint32_t hover_outline_color;
	uint32_t clicked_fill_color;
	uint32_t clicked_outline_color;
	void (*mouse_event)(_global_control_ *g_ctrl,XEWindow *win,int x, int y, int button);
	void (*action_event) (_global_control_ *g_ctrl, XEWindow *win);
}XEGlobalControl;
	

/*
 * XECreateWindow -- Creates a new window with given properties
 * @param app -- Pointer to XEApp structure
 * @param attrib -- Window attributes
 * @param title -- window title
 * @param x -- X coord of the window
 * @param y -- Y coord of the window
 */
XE_EXTERN XE_EXPORT XEWindow * XECreateWindow (XeApp *app, canvas_t *canvas, uint8_t attrib, char* title, int x, int y);

/*
 * XEWindowSetXY -- Sets a new location for the window
 * @param win -- Pointer to the window structure
 * @param x -- X position
 * @param y -- Y position
 */
XE_EXTERN XE_EXPORT void XEWindowSetXY (XEWindow *win, int x, int y);


/*
 * XEWindowAddWidget -- Adds an widget to main activity window
 * @param window -- Pointer to main activity window
 * @param widget -- Pointer to widget
 */
XE_EXTERN XE_EXPORT void XEWindowAddWidget(XEWindow *window, XEWidget *widget);


/* XEUpdateWindow -- Updates a portion of the window
* @param win -- Pointer to the window
* @param x -- X Coordinate
* @param y -- Y Coordinate
* @param w -- Width of the rect
* @param h -- Height of the rect
* @param dirty -- is this update dirty?
*/
XE_EXTERN XE_EXPORT void XEUpdateWindow(XEWindow* win, int x, int y, int w, int h, bool dirty);

/*
 * XeShowWindow -- Sends a msg to PRIWM
 * to show the window
 */
XE_EXTERN XE_EXPORT void XEShowWindow(XEWindow *win);

/*
 * XEWindowMouseHandle -- Default Mouse handler for XEWindow
 * @param win -- Pointer to window
 * @param x -- X coord of mouse passed by window manager
 * @param y -- Y coord of mouse passed by window manager
 * @param button -- mouse button state passed by window manager
 */
XE_EXTERN XE_EXPORT void XEWindowMouseHandle(XEWindow *win, int x, int y, int button, int scroll);

/*
 * XEAddGlobalButton -- Adds Global Control button to window
 * @param win -- Pointer to window
 * @param x -- X Coordinate
 * @param y -- Y Coordinate
 * @param type -- button type
 */
XE_EXTERN XE_EXPORT XEGlobalControl* XEAddGlobalButton(XEWindow *win,int x, int y, int w, int h, uint8_t type);

/**
 * XERemoveGlobalButton -- Remove a particular global button
 * from application window
 * @param win -- Pointer to the application window
 * @param type -- Global Button type
 */
XE_EXTERN XE_EXPORT void XERemoveGlobalButton (XEWindow* win, uint8_t type);

/*
 * XEWindowHandleResize -- Handle new window resize events from window server
 * @param win -- Pointer to XEWindow
 * @param back_key -- Back Buffer key 
 * @param n_w -- new width
 * @param n_h -- new height
 */
XE_EXTERN XE_EXPORT void XEWindowHandleResize (XeApp *app, XEWindow *win, uint16_t back_key);

/*
 * XERedrawWindow -- Redraws the window 
 * @param win -- Pointer to window structure
 */
XE_EXTERN XE_EXPORT void XERedrawWindow (XEWindow *win);

/**
 * XERepaintWidgets -- Repaints all widgets
 * @param win -- Pointer to application window
 */
XE_EXTERN XE_EXPORT void XERepaindWidgets (XEWindow* win);

/*
 * XEResizeWindow -- Sends resize command to window server
 * for this window
 * @param w -- width
 * @param h -- height
 */
XE_EXTERN XE_EXPORT void XEResizeWindow (XEWindow* win,int w, int h) ;


/*
 * XEWindowSetAttrib -- Set window attributes/properties
 * @param attrib -- attribute value
 */
XE_EXTERN XE_EXPORT void XEWindowSetAttrib (XEWindow* win,uint8_t attrib);

/*
 * XEExitWindow -- Exits a graphical window
 * @param win -- Pointer to window
 */
XE_EXTERN XE_EXPORT void XEExitWindow (XEWindow* win);

#endif