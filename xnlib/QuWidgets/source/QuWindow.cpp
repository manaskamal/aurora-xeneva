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


QuWinControl* QuCreateControl (unsigned x, unsigned y, unsigned w, unsigned h, uint8_t type) {
	QuWinControl *obj = (QuWinControl*)malloc(sizeof(QuWinControl));
	obj->x = x;
	obj->y = y;
	obj->w = w;
	obj->h = h;
	obj->type = type;
	return obj;
}

void QuWindowAddMinimizeButton (QuWindow *win) {
	QuWinControl *minimize = QuCreateControl(win->x + win->w - 43,win->y + 9, 11,18, QU_WIN_CONTROL_MINIMIZE);
	QuListAdd (win->controls, minimize);
}

void QuWindowAddMaximizeButton (QuWindow *win) {
	QuWinControl *maximize = QuCreateControl (win->x + win->w - 28, win->y + 9, 11, 18, 
		QU_WIN_CONTROL_MAXIMIZE);
	QuListAdd (win->controls, maximize);
}

void QuWindowAddCloseButton(QuWindow *win) {
	QuWinControl *close = QuCreateControl (win->x + win->w - 13, win->y + 9, 11, 18,
		QU_WIN_CONTROL_CLOSE);
	QuListAdd (win->controls, close);
}



void QuCreateWindow (int x, int y, int w, int h) {
	QuWindow* win = (QuWindow*)malloc(sizeof(QuWindow));
	win->x = x;
	win->y = y;
	win->w = w;
	win->h = h;	
	win->widgets = QuListInit();
	win->controls = QuListInit();

	//QuWindowAddMinimizeButton(win);
	//QuWindowAddMaximizeButton(win);
	//QuWindowAddCloseButton(win);

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

void QuWindowShowControls (QuWindow *win) {
	QuWindowAddMinimizeButton(win);
	QuWindowAddMaximizeButton(win);
	QuWindowAddCloseButton(win);
}

void QuWindowShow() {

	
	for (int i = 0; i < root_win->widgets->pointer; i++) {
		QuWidget* wid = (QuWidget*)QuListGetAt(root_win->widgets, i);
		wid->Refresh(wid, root_win);
	}

	for (int i = 0; i < 23; i++)
		acrylic_draw_horizontal_line(root_win->x, root_win->y + i,root_win->w,title_bar_colors[i]);

	uint32_t buttons_color = WHITE;
	for (int i = 0; i < root_win->controls->pointer; i++) {
		QuWinControl *to = (QuWinControl*)QuListGetAt(root_win->controls, i);
		if (to->type == QU_WIN_CONTROL_MINIMIZE)
			buttons_color = ORANGE;
		if (to->type == QU_WIN_CONTROL_MAXIMIZE)
			buttons_color = PALEGREEN;
		if (to->type == QU_WIN_CONTROL_CLOSE)
			buttons_color = RED;
		acrylic_draw_filled_circle(to->x, to->y, 6, buttons_color);
	}

	acrylic_draw_rect_unfilled (root_win->x, root_win->y, root_win->w, root_win->h, SILVER);
	//QuPanelUpdate(root_win->x, root_win->y, root_win->w, root_win->h);
}


void QuWindowMove (int x, int y) {
	root_win->x = x;
	root_win->y = y;


	//! Update controls coordinates
	for (int i = 0; i < root_win->controls->pointer; i++) {
		QuWinControl *to = (QuWinControl*)QuListGetAt(root_win->controls, i);
		if (to->type == QU_WIN_CONTROL_MINIMIZE){
			to->x = root_win->x + root_win->w - 43;
			to->y = root_win->y + 9;
		}if (to->type == QU_WIN_CONTROL_MAXIMIZE){
			to->x = root_win->x + root_win->w - 28;
			to->y = root_win->y + 9;
		}if (to->type == QU_WIN_CONTROL_CLOSE){
			to->x = root_win->x + root_win->w - 13;
			to->y = root_win->y + 9;
		}
	}

	for (int i = 0; i < root_win->widgets->pointer; i++) {
		QuWidget* wid = (QuWidget*)QuListGetAt(root_win->widgets,i);
		wid->Refresh(wid, root_win);
	}

	for (int i = 0; i < 23; i++)
		acrylic_draw_horizontal_line(root_win->x, root_win->y + i,root_win->w,title_bar_colors[i]);


	uint32_t buttons_color = WHITE;
	for (int i = 0; i < root_win->controls->pointer; i++) {
		QuWinControl *to = (QuWinControl*)QuListGetAt(root_win->controls, i);
		if (to->type == QU_WIN_CONTROL_MINIMIZE)
			buttons_color = ORANGE;
		if (to->type == QU_WIN_CONTROL_MAXIMIZE)
			buttons_color = PALEGREEN;
		if (to->type == QU_WIN_CONTROL_CLOSE)
			buttons_color = RED;
		acrylic_draw_filled_circle(to->x, to->y, 6, buttons_color);
	}

	acrylic_draw_rect_unfilled (root_win->x, root_win->y, root_win->w, root_win->h, SILVER);
}


void QuWindowSetAutoInvalidation (bool value) {
	message_t msg;
	msg.type = QU_CODE_WIN_CONFIG;
	msg.dword = QU_WIN_CONFIG_AUTO_INVALIDATE;
	msg.dword5 = QuGetAppId();
	message_send(2, &msg);
	/*QuMessage msg;
	msg.type = QU_CODE_WIN_CONFIG;
	msg.dword = QU_WIN_CONFIG_AUTO_INVALIDATE;*/
	//msg.dword5 = QuGetAppId();
	//message_send(2, &msg);
	//QuChannelPut (&msg, 2);
}

void QuWindowSetAutoInvalidateRegion (int x, int y, int w, int h) {
	QuMessage msg;
	msg.type = QU_CODE_WIN_CONFIG;
	msg.dword = QU_WIN_AUTO_INVALIDATE_RGN;
	msg.dword2 = x;
	msg.dword3 = y;
	msg.dword4 = w;
	msg.dword6 = h;
	QuChannelPut(&msg, 2);
}
void QuWindowSetSize (int width, int height) {
	root_win->w = width;
	root_win->h = height;
	QuMessage msg;
	msg.type = QU_CODE_WIN_CONFIG;
	msg.dword = QU_WIN_SET_SIZE;
	msg.dword2 = width;
	msg.dword3 = height;
	QuChannelPut(&msg, 2);
}

void QuWindowSetProperty (uint8_t prop) {
	QuMessage msg;
	msg.type = QU_CODE_WIN_CONFIG; 
	msg.dword =	QU_WIN_NON_DRAGGABLE;
	QuChannelPut(&msg, 2);
}


void QuWindowHandleMouse (int mouse_x, int mouse_y, int code) {
	bool clicked = false;
	for (int i = 0; i < root_win->widgets->pointer; i++) {
		QuWidget *wid = (QuWidget*)QuListGetAt(root_win->widgets, i);
		if (mouse_x > (root_win->x + wid->x) && mouse_x < (root_win->x + wid->x + wid->width) &&
			mouse_y > (root_win->y + wid->y) && mouse_y < (root_win->y + wid->y + wid->height)) {
				if (code == QU_CANVAS_MOUSE_LCLICKED)
					clicked = true;
				wid->MouseEvent(wid, root_win, QU_EVENT_MOUSE_ENTER,clicked);
		} else {
			wid->MouseEvent (wid, root_win, QU_EVENT_MOUSE_LEAVE, clicked);
		}
	}
}