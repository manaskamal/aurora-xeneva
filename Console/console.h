///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   console.cpp --- Console Control
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///!
///!=================================================


#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <stdint.h>
#include <string.h>
#include <QuWindow.h>
#include <stdlib.h>
#include <acrylic.h>


typedef struct _console_ {
	QuWidget wid;
    int cursor_x;
    int cursor_y;
}ConsoleWidget;


extern ConsoleWidget* create_console (int x, int y, int w, int h);
extern void ConsoleRefresh (QuWidget *wid, QuWindow *win);
#endif