///! Copyright (C) Manas Kamal Choudhury 2021
///! 
///! QuPanel -- Main Client Area where GUI Object sits
///!
///! /PROJECT - Aurora's Xeneva
///! /AUTHOR  - Manas Kamal Choudhury
///!
///!====================================================

#ifndef __QU_PANEL_H__
#define __QU_PANEL_H__

#include <stdint.h>
#include <QuBase.h>
#include <QuWindow.h>

typedef struct _QuPanel_ {
	QuWidget base;
}QuPanel;

extern QuPanel *QuCreatePanel();
extern void QuPanelUpdate(int x, int y, int w, int h);
extern void QuPanelContentUpdate(int x, int y, int w, int h);
extern void QuPanelRefresh (QuWidget *wid, QuWindow *win);
extern void QuPanelUpdateRequired (bool value);
#endif