///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   QuButton.h -- Quince Button object
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///!
///!=================================================

#ifndef __QU_BUTTON_H__
#define __QU_BUTTON_H__

#include <stdint.h>
#include <QuWindow.h>

#define QU_BUTTON_DEFAULT_WIDTH 140
#define QU_BUTTON_DEFAULT_HEIGHT 30


typedef struct _QuButton_ {
	QuWidget widget;
	const char* text;
}QuButton;

extern QuButton * QuCreateButton (int x, int y);
extern void QuButtonSetText (QuButton *but, const char* text);

#endif