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
extern void QuWindowMngr_HandleMouse (int x, int y, uint8_t button, int mouse_code);
extern void QuWindowMngr_HandleMouseUp (int x, int y);
extern void QuWindowMngr_SendEvent (QuWindow *win, int type, int x, int y, int code);
extern void QuWindowMngr_DrawBehind (QuWindow *current_win);
extern QuWindow* QuWindowMngrGetDraggable();
extern QuList *QuWindowMngr_GetList ();
extern bool QuWindowMngr_GetIntersections(QuWindow* win, QuWindow* current);
extern QuRect * QuWindowMngr_RectOverlap (QuWindow *win1, QuWindow *win2);
#endif