///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuWindow.h -- Quince Window
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!================================================

#include <QuWindow.h>
#include <QuWindowControl.h>
#include <QuBase.h>
#include <stdlib.h>
#include <QuPanel.h>
#include <acrylic.h>
#include <string.h>
#include <color.h>
#include <sys\_ipc.h>
#include <QuContextMenu.h>
#include <QuMenubar.h>
#include <sys\_term.h>


QuWindow* root_win = NULL;
int old_mouse_x = 0;
int old_mouse_y = 0;

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
	obj->hover = false;
	obj->type = type;
	obj->restore = false;
	obj->ControlEvent = 0;
	return obj;
}

void QuWindowAddMinimizeButton (QuWindow *win) {
	QuWinControl *minimize = QuCreateControl(win->w - 43,2, 11,18, QU_WIN_CONTROL_MINIMIZE);
	minimize->ControlRedraw = QuMinimizeButtonDraw;
	QuListAdd (win->controls, minimize);
}

void QuWindowAddMaximizeButton (QuWindow *win) {
	QuWinControl *maximize = QuCreateControl (win->w - 28, 2, 11, 18, 
		QU_WIN_CONTROL_MAXIMIZE);
	maximize->ControlRedraw = QuMaximizeButtonDraw;
	QuListAdd (win->controls, maximize);
}

void QuWindowAddCloseButton(QuWindow *win) {
	QuWinControl *close = QuCreateControl (win->w - 13, 2, 11, 18,
		QU_WIN_CONTROL_CLOSE);
	close->ControlRedraw = QuCloseButtonDraw;
	QuListAdd (win->controls, close);
}


void QuWindowAddControlEvent (int type, void (*Event)(QuWinControl *control, QuWindow* win, bool bit)){
	for (int i = 0; i < root_win->controls->pointer; i++) {
		QuWinControl *control = (QuWinControl*)QuListGetAt(root_win->controls, i);
		if (control->type == type) {
			control->ControlEvent = Event;
			return;
		}
	}
}


void QuCreateWindow (int x, int y, int w, int h, uint32_t* info_data, char* title) {
	QuWindow* win = (QuWindow*)malloc(sizeof(QuWindow));
	win->x = x;
	win->y = y;
	win->w = w;
	win->h = h;	
	win->widgets = QuListInit();
	win->controls = QuListInit();
	win->win_info_data = info_data;
	win->title = title;
	win->decorate = true;
	win->focus_widget = NULL;
	win->draggable_widget = NULL;
	win->current_ctx_menu = NULL;
	QuWinInfo* info = (QuWinInfo*)win->win_info_data;
	//info->rect_count = 0;
	//QuWindowAddMinimizeButton(win);
	//QuWindowAddMaximizeButton(win);
	//QuWindowAddCloseButton(win);

	root_win = win;
}

void QuWindowEnableDecoration (bool value) {
	root_win->decorate = value;
}


void QuWindowSetCanvas (unsigned int* address) {
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
	root_win->focus_widget = widget;
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

	if (root_win->decorate) {
	for (int i = 0; i < 23; i++)
		acrylic_draw_horizontal_line(0, 0 + i,root_win->w,title_bar_colors[i]);


	uint32_t buttons_color = WHITE;
	for (int i = 0; i < root_win->controls->pointer; i++) {
		QuWinControl *to = (QuWinControl*)QuListGetAt(root_win->controls, i);
		to->ControlRedraw(to,root_win, false);
	}

	acrylic_draw_arr_string (root_win->w/2 - (strlen(root_win->title)*8)/2,
		 3, 
		root_win->title, WHITE);
	
	acrylic_draw_rect_unfilled (0, 0, root_win->w, root_win->h, SILVER);
	}
	
	QuPanelUpdate(root_win->x,root_win->y, root_win->w, root_win->h, true);
}


void QuWindowMove (int x, int y) {
	root_win->x = x;
	root_win->y = y;
}


void QuWindowRepaint() {
	for (int i = 0; i < root_win->widgets->pointer; i++) {
		QuWidget* wid = (QuWidget*)QuListGetAt(root_win->widgets, i);
		wid->Refresh(wid, root_win);
	}

	if (root_win->decorate) {
	for (int i = 0; i < 23; i++)
		acrylic_draw_horizontal_line(root_win->x, root_win->y + i,root_win->w,title_bar_colors[i]);


	uint32_t buttons_color = WHITE;
	for (int i = 0; i < root_win->controls->pointer; i++) {
		QuWinControl *to = (QuWinControl*)QuListGetAt(root_win->controls, i);
		to->ControlRedraw(to,root_win, false);
	}

	acrylic_draw_arr_string (root_win->x + root_win->w/2 - (strlen(root_win->title)*8)/2,
		root_win->y + 3, 
		root_win->title, WHITE);
	acrylic_draw_rect_unfilled (root_win->x, root_win->y, root_win->w, root_win->h, SILVER);
	}

	QuPanelUpdate(root_win->x, root_win->y, root_win->w, root_win->h, false);
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

void QuWindowSetPos (int x, int y) {
	root_win->x = x;
	root_win->y = y;
	QuMessage msg;
	msg.type = QU_CODE_WIN_CONFIG;
	msg.dword = QU_WIN_SET_POS;
	msg.dword2 = root_win->x;
	msg.dword3 = root_win->y;
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
	bool control_click = false;
	if (mouse_x > root_win->x && mouse_x < (root_win->x + root_win->w) &&
		mouse_y > root_win->y + 23 && mouse_y < (root_win->y + root_win->h)) {
	for (int i = 0; i < root_win->widgets->pointer; i++) {
		QuWidget *wid = (QuWidget*)QuListGetAt(root_win->widgets, i);
		if (mouse_x > (root_win->x + wid->x) && mouse_x < (root_win->x + wid->x + wid->width) &&
			mouse_y > (root_win->y + wid->y) && mouse_y < (root_win->y + wid->y + wid->height)) {

				//! Make the difference between left click and dragging here
				if (code == QU_CANVAS_MOUSE_LCLICKED /*&& old_mouse_x == mouse_x && old_mouse_y == mouse_y*/){
					clicked = true;
					root_win->focus_widget = wid;
				}

				wid->MouseEvent(wid, root_win, QU_EVENT_MOUSE_ENTER,clicked, mouse_x, mouse_y);
		} else {
			wid->MouseEvent (wid, root_win, QU_EVENT_MOUSE_LEAVE, clicked, mouse_x,mouse_y);
		}

	}

	if (root_win->current_ctx_menu) {
		clicked = false;
		QuContextMenu * ctx = (QuContextMenu*)root_win->current_ctx_menu;
		QuWidget *mb = (QuWidget*)root_win->current_menubar;
		if (code == QU_CANVAS_MOUSE_LCLICKED) {
			clicked = true;
		}

		QuContextMenuEventHandle(ctx,mb,root_win, mouse_x, mouse_y, clicked);
	}

	for (int i = 0; i < root_win->controls->pointer; i++) {
		QuWinControl *control = (QuWinControl*)QuListGetAt(root_win->controls, i);
		if (mouse_x > (root_win->x + control->x) && mouse_x < (root_win->x + control->x + control->w) &&
			mouse_y > (root_win->y + control->y) && mouse_y < (root_win->y + control->y + control->h)) {

				if (code == QU_CANVAS_MOUSE_LCLICKED /*&& old_mouse_x == mouse_x && old_mouse_y == mouse_y*/)
					control_click = true;
				control->hover = true;

				control->ControlRedraw (control, root_win, control_click);
		}else {
			control->ControlRedraw(control, root_win, false);
		}

	}
	old_mouse_x = mouse_x;
	old_mouse_y = mouse_y;
	}
}



void QuWindowHandleKey (int code) {
	for (int i = 0; i < root_win->widgets->pointer; i++) {
		QuWidget *wid = (QuWidget*)QuListGetAt(root_win->widgets, i);
		//! Make the difference between left click and dragging here
		if (root_win->focus_widget == wid && wid->KeyEvent != 0)
			wid->KeyEvent(wid, root_win,code);
	}
}
