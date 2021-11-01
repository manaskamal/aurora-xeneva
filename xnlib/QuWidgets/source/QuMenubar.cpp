///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuMenubar.h -- Quince Menubar Widget
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!===============================================

#include <QuMenubar.h>
#include <stdlib.h>
#include <color.h>
#include <acrylic.h>
#include <string.h>

void QuMenubarRefresh (QuWidget* wid, QuWindow *win) {
	QuMenubar *mb = (QuMenubar*)wid;


	acrylic_draw_rect_filled (win->x + wid->x, win->y + wid->y, wid->width, 20, SILVER);

	int x = 4;
	for (int i = 0; i < mb->CtxMenus->pointer; i++) {
		QuContextMenu *ctx = (QuContextMenu*)QuListGetAt(mb->CtxMenus, i);
		acrylic_draw_arr_string (win->x + wid->x + x, 
			win->y + wid->y + (wid->height/2) - (12/2),ctx->title,LIGHTBLACK);
		x += strlen(ctx->title)*8 + 4;
	}
}


void QuMenubarMouseEvent (QuWidget *wid, QuWindow *win, int code, bool clicked, int x, int y) {
}

void QuMenubarKeyEvent (QuWidget *wid, QuWindow *win, int code) {
}

QuMenubar *QuCreateMenubar () {
	QuMenubar *mb = (QuMenubar*)malloc(sizeof(QuMenubar));
	mb->wid.x = 1;
	mb->wid.y = 23;
	mb->wid.width = QuGetWindow()->w - 1;
	mb->wid.height = 20;
	mb->wid.ActionEvent = NULL;
	mb->wid.MouseEvent = QuMenubarMouseEvent;
	mb->wid.Refresh = QuMenubarRefresh;
	mb->wid.KeyEvent = QuMenubarKeyEvent;
	mb->wid.ScrollEvent = 0;
	mb->CtxMenus = QuListInit();
	return mb;
}

void QuMenubarAddMenu(QuMenubar *mb, QuContextMenu *menu) {
	QuListAdd (mb->CtxMenus, menu);
}

