///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuPopupMenu -- The Popup Menu
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!==================================================

#include <QuPanel.h>
#include <string.h>
#include <stdlib.h>
#include <QuPopupMenu.h>

QuPopupMenu *QuCreatePopupMenu (char* title) {
	QuPopupMenu *p = (QuPopupMenu*)malloc(sizeof(QuPopupMenu));
	p->title = title;
	p->m_w  = strlen(title)*8 + 1;
	p->m_h = 20;
	p->is_popup = false;
	p->m_x = 0;
	p->m_y = 0;
	return p;
}

