///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuMenubar.h -- Quince Menubar Widget
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!===============================================

#ifndef __QU_MENUBAR_H__
#define __QU_MENUBAR_H__

#include <QuWindow.h>
#include <QuBase.h>
#include <QuUtils\QuList.h>
#include <QuContextMenu.h>

typedef struct _qu_menubar_h_ {
	QuWidget wid;
	QuList *CtxMenus;
	QuContextMenu *focused;
	bool update_required;
	bool popup_enable;
}QuMenubar;

extern QuMenubar *QuCreateMenubar ();
extern void QuMenubarAddMenu(QuMenubar *mb, QuContextMenu *menu);
#endif