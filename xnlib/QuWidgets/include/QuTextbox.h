///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   QuTextbox -- Quince Textbox widget
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury 
///!
///!==================================================

#ifndef __QU_TEXTBOX_H__
#define __QU_TEXTBOX_H__

#include <stdint.h>
#include <acrylic.h>
#include <QuBase.h>
#include <QuWindow.h>

//! Single Line Text box
typedef struct _QuTextbox_ {
	QuWidget wid;
	bool editable;
	char text[512];
	int cursor_pos_x;
	bool hover;
	bool clicked;
	bool text_paint;
}QuTextbox;


///! QuCreateTextbox -- Create a new Textbox
///!
///! @param x -- X coord
///! @param y -- Y coord
///! @param width -- Width of the textbox
///! @param height -- Height of the textbox
extern QuTextbox * QuCreateTextbox (int x, int y, int width, int height);

///! QuEnterText -- Enter some text into the textbox
///!
///! @param tb -- QuTextbox pointer
///! @param text -- Text to enter
extern void QuEnterText (QuTextbox *tb,char *text);


///!  QuTextboxInvalidate -- Invalidate the textbox
///!
///! @param tb -- Pointer to the textbox
///! @param win -- Pointer to the root window rect
extern void QuTextboxInvalidate (QuTextbox *tb, QuWindow* win);

///! QuTextboxRefresh -- Refresh the textbox
///!
///! @param tb -- Pointer to the textbox
///! @param win -- Pointer to the root window
///!
void QuTextboxRefresh (QuTextbox *tb, QuWindow* win);

extern void QuTextboxAppendText (QuTextbox *tb, char* text);
#endif