///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuWindowMngr -- The Main Quince Window Manager
///!  
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!====================================================

#ifndef __QU_WINDOW_MNGR_H__
#define __QU_WINDOW_MNGR_H__

#include <QuWindow\QuWindow.h>

extern void QuWindowMngr_Initialize ();
extern void QuWindowMngr_Add (QuWindow *window);
extern void QuWindowMngr_Remove (QuWindow *win);
extern void QuWindowMngr_DrawAll ();
extern QuWindow* QuWindowMngrFindByID (uint16_t id);
extern void QuWindowMngrSetFocus (QuWindow* win);
extern QuWindow* QuWindowMngrGetFocused ();
extern void QuWindowMngr_HandleMouse (int x, int y, bool clicked);
extern void QuWindowMngr_HandleMouseUp (int x, int y);
extern void QuWindowMngr_DisplayWindow();
extern void QuWindowMngr_UpdateWindow (bool value);
extern bool QuWindowMngr_GetUpdateBit();
extern void QuWindowMngr_SendEvent (QuWindow *win, int type, int x, int y, int code);
extern void QuWindowMngr_EventStreamEnable (bool value);
#endif