///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuWindow.h -- Quince Window
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!================================================

#include <QuWindow.h>
#include <QuBase.h>
#include <stdlib.h>
#include <QuPanel.h>
#include <acrylic.h>
#include <string.h>
#include <color.h>
#include <sys\_ipc.h>


QuWindow* root_win = NULL;


uint32_t title_bar_colors[23] = {0xff59584f, 0xff5f5d53, 0xff58564e, 0xff57554d, 0xff56544c, 0xff55534b, \
    0xff54524a, 0xff525049, 0xff514f48, 0xff504e47, 0xff4e4c45, 0xff4e4c45, \
        0xff4c4a44, 0xff4b4943, 0xff4a4842, 0xff484741, 0xff46453f, 0xff45443f, \
        0xff44433e, 0xff43423d, 0xff42413c, 0xff403f3a, 0xff3f3e3a };


void QuCreateWindow (int x, int y, int w, int h) {
	QuWindow* win = (QuWindow*)malloc(sizeof(QuWindow));
	win->x = x;
	win->y = y;
	win->w = w;
	win->h = h;	
	win->widgets = QuListInit();
	root_win = win;
}

void QuWindowSetCanvas (uint32_t* address) {
	root_win->canvas = address;
}

QuWindow* QuGetWindow () {
	return root_win;
}

int QuWindowGetX() {
	return root_win->x;
}


int QuWindowGetY() {
	return root_win->y;
}

int QuWindowGetWidth () {
	return root_win->w;
}

int QuWindowGetHeight () {
	return root_win->h;
}

void QuWindowSetBound(int w, int h) {
	root_win->w = w;
	root_win->h = h;
}

void QuWindowAdd (QuWidget *widget) {
	QuListAdd(root_win->widgets, widget);
}

void QuWindowShow() {

	for (int i = 0; i < root_win->widgets->pointer; i++) {
		QuWidget* wid = (QuWidget*)QuListGetAt(root_win->widgets, i);
		wid->Refresh(wid, root_win);
	}

	for (int i = 0; i < 23; i++)
		acrylic_draw_horizontal_line(root_win->x, root_win->y + i,root_win->w,title_bar_colors[i]);

	
	QuPanelUpdate(root_win->x, root_win->y, root_win->w, root_win->h);
}


void QuWindowMove (int x, int y) {
	root_win->x = x;
	root_win->y = y;

	for (int i = 0; i < root_win->widgets->pointer; i++) {
		QuWidget* wid = (QuWidget*)QuListGetAt(root_win->widgets,i);
		wid->Refresh(wid, root_win);
	}

	for (int i = 0; i < 23; i++)
		acrylic_draw_horizontal_line(root_win->x, root_win->y + i,root_win->w,title_bar_colors[i]);
}


void QuWindowSetAutoInvalidation (bool value) {
	message_t msg;
	msg.type = QU_CODE_WIN_CONFIG;
	msg.dword = QU_WIN_CONFIG_AUTO_INVALIDATE;
	msg.dword5 = QuGetAppId();
	message_send(2, &msg);
}

void QuWindowSetAutoInvalidateRegion (int x, int y, int w, int h) {
	message_t msg;
	msg.type = QU_CODE_WIN_CONFIG;
	msg.dword = QU_WIN_AUTO_INVALIDATE_RGN;
	msg.dword2 = x;
	msg.dword3 = y;
	msg.dword4 = w;
	msg.dword6 = h;
	msg.dword5 = QuGetAppId();
	message_send (2, &msg);
}
void QuWindowSetSize (int width, int height) {
	root_win->w = width;
	root_win->h = height;
	message_t msg;
	msg.type = QU_CODE_WIN_CONFIG;
	msg.dword = QU_WIN_SET_SIZE;
	msg.dword5 = QuGetAppId();
	msg.dword2 = width;
	msg.dword3 = height;
	message_send(2, &msg);
}
