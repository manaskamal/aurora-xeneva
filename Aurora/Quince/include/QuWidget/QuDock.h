///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuTaskbar -- Quince Taskbar Widget
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!--------------------------------------------------
///!===================================================

#ifndef __QU_TASKBAR_H__
#define __QU_TASKBAR_H__

#include <stdint.h>

typedef struct _qu_dock_ {
	char *icon_path;
	char* title;
	unsigned char* icon_data;
}QuDockEntry;


//! Initialize Quince Taskbar
extern void QuDockInit ();
extern void QuDockRepaint ();
extern void QuDockAdd (QuDockEntry *entry);
extern void QuDockRemove (QuDockEntry *entry);
extern void QuRamWidget ();
#endif