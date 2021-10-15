///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   QuWindowControl.h -- Window Controls {Minimize, Maximize, Close} buttons
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///!
///!=================================================================================

#ifndef __QU_WINDOW_CONTROL_H__
#define __QU_WINDOW_CONTROL_H__

#include <acrylic.h>
#include <QuPanel.h>

extern void QuMinimizeButtonDraw (QuWinControl *control, QuWindow *win, bool clicked);
extern void QuMaximizeButtonDraw (QuWinControl *control, QuWindow *win, bool clicked);
extern void QuCloseButtonDraw (QuWinControl *control, QuWindow *win, bool clicked);

#endif