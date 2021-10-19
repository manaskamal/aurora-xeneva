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


#define TERM_WIDTH 74
#define TERM_HEIGHT 26

typedef struct _terminal_ {
	QuWidget wid;
	char text[TERM_WIDTH*TERM_HEIGHT];   //User should map and provide the buffer
	int cursor_x;
	int cursor_y;
	int xpos;
	int ypos;
}QuTerminal;


extern QuTerminal * QuCreateTerminal (int x, int y, int w, int h);
extern void QuTermPrint (QuTerminal *term , char s, uint32_t col);
extern void QuTermFlush (QuTerminal *term, QuWindow* win);
#endif