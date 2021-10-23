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
}QuEditBox;


extern QuEditBox *QuCreateEditBox (int x, int y, int w, int h);
#endif