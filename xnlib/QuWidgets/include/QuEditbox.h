///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   QuEditbox.h -- Multiline Edit box
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///!
///!===============================================

#ifndef __QU_EDITBOX_H__
#define __QU_EDITBOX_H__

#include <QuWindow.h>

typedef struct _qu_edit_box_ {
	QuWidget wid;
	int last_scroll_diffx;
	int last_scroll_diffy;
	int cursor_x;
	int cursor_y;
	int xpos;
	int ypos;
	uint8_t *buffer;
	uint8_t *backstore;
}QuEditBox;


extern QuEditBox *QuCreateEditBox (int x, int y, int w, int h);
extern void QuEditBoxSetVisible (QuEditBox *eb);
extern void QuEditBoxSetChar (QuEditBox *eb, char s, uint32_t color);
extern void QuEditSetText (QuEditBox *eb, char* string);
#endif