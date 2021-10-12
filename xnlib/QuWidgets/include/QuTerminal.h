///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   QuTerminal.h -- Terminal Widget 
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///!
///!==================================================

#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#include <QuBase.h>
#include <QuWindow.h>

typedef struct _terminal_ {
	QuWidget wid;
	char buffer[512];
	int cursor_x;
	int cursor_y;
}QuTerminal;


extern QuTerminal * QuCreateTerminal (int x, int y, int w, int h);

#endif