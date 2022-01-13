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
#include <font.h>
#include <QuBase.h>


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
	minimize->ControlRearrange = QuMinimizeButtonRearrange;
	QuListAdd (win->controls, minimize);
}

void QuWindowAddMaximizeButton (QuWindow *win) {
	QuWinControl *maximize = QuCreateControl (win->w - 28, 2, 11, 18, 
		QU_WIN_CONTROL_MAXIMIZE);
	maximize->ControlRedraw = QuMaximizeButtonDraw;
	maximize->ControlRearrange = QuMaximizeButtonRearrange;
	QuListAdd (win->controls, maximize);
}

void QuWindowAddCloseButton(QuWindow *win) {
	QuWinControl *close = QuCreateControl (win->w - 13, 2, 11, 18,
		QU_WIN_CONTROL_CLOSE);
	close->ControlRedraw = QuCloseButtonDraw;
	close->ControlRearrange = QuCloseButtonRearrange;
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


QuWindow* QuCreateWindow (int x, int y, int w, int h, char* title) {
	QuWindow* win = (QuWindow*)malloc(sizeof(QuWindow));
	win->temp_x = x;
	win->temp_y = y;
	win->w = w;
	win->h = h;	
	win->widgets = QuListInit();
	win->controls = QuListInit();
	win->win_info_data = NULL;
	win->title = title;
	win->decorate = true;
	win->focus_widget = NULL;
	win->draggable_widget = NULL;
	win->current_ctx_menu = NULL;
	win->winid = 0;
	win->maximized = false;
	QuRegisterApplication(win);
	win->ctx = NULL;
	return win;
}

void QuSetRootWindow (QuWindow *win) {
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
	QuWinInfo *info = (QuWinInfo*)root_win->win_info_data;
	return info->x;
}


int QuWindowGetY() {
	QuWinInfo *info = (QuWinInfo*)root_win->win_info_data;
	return info->y;
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

void QuWindowAdd (QuWindow* win,QuWidget *widget) {
	QuListAdd(win->widgets, widget);
	win->focus_widget = widget;
}

void QuWindowShowControls (QuWindow *win) {
	QuWindowAddMinimizeButton(win);
	QuWindowAddMaximizeButton(win);
	QuWindowAddCloseButton(win);
}


/**
 * QuWindowShow -- The Main Window Drawing stuff
 *                 it first iterates through all widgets,
 *                 draws it one by one than decorate the
 *                 window
 * @param win -- Reference to the window, which needs to draw
 */
void QuWindowShow(QuWindow *win) {
	QuWinInfo *info = (QuWinInfo*)win->win_info_data;

	/**
	* Draw every widgets in stacking order 
	 */
	for (int i = 0; i < win->widgets->pointer; i++) {
		QuWidget* wid = (QuWidget*)QuListGetAt(win->widgets, i);
		wid->Refresh(wid, win);
	}

	/**
	 * If decorate is true, than draw the title bar
	 **/
	if (win->decorate) {
		for (int i = 0; i < 23; i++)
			acrylic_draw_horizontal_line(win->ctx,0, 0 + i,win->w,title_bar_colors[i]);


	/**
	 * Control buttons
	 * draw the three control button 
	 */
		uint32_t buttons_color = WHITE;
		for (int i = 0; i < win->controls->pointer; i++) {
			QuWinControl *to = (QuWinControl*)QuListGetAt(win->controls, i);
		    to->ControlRedraw(to,win, false);
		}


		//! Finally draw the title in the midle of titlebar
		acrylic_font_set_size(13);
		int title_length = acrylic_font_get_length(win->title);
		acrylic_font_draw_string(win->ctx,win->title,win->w/2 - title_length/2,15,0,WHITE);
	
		///! Draw a boundary
		acrylic_draw_rect_unfilled (win->ctx,0, 0, win->w, win->h, SILVER);
	}

	/**
	 * Update the content to main canvas of the window
	 */
	QuPanelUpdate(win,info->x,info->y, win->w + 10, win->h + 10, true);
}


void QuWindowMove (QuWindow *win,int x, int y) {
	/*win->x = x;
	win->y = y;*/
}


void QuWindowRepaint(QuWindow * win) {
	for (int i = 0; i < win->controls->pointer; i++) {
			QuWinControl *to = (QuWinControl*)QuListGetAt(win->controls, i);
			to->ControlRearrange(to,win);
	}
	QuWindowShow(win);
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
	QuWinInfo *info = (QuWinInfo*)root_win->win_info_data;
	info->x = x;
	info->y = y;
}

void QuWindowSetIcon (int icon_type) {
	QuWindow *win = root_win;
	QuMessage *msg = (QuMessage*)malloc(sizeof(QuMessage));
	msg->type = QU_CODE_WIN_CONFIG;
	msg->dword = QU_WIN_SET_ICON;
	msg->dword2 = icon_type;
	QuChannelPut(msg,2);
	free(msg);
}

void QuWindowSetProperty (uint8_t prop) {
	QuMessage msg;
	msg.type = QU_CODE_WIN_CONFIG; 
	msg.dword =	QU_WIN_NON_DRAGGABLE;
	QuChannelPut(&msg, 2);
}


void QuWindowHandleMouse (int mouse_x, int mouse_y, int code) {
	QuWinInfo *info = (QuWinInfo*)root_win->win_info_data;
	bool clicked = false;
	bool control_click = false;

	if (mouse_x > info->x && mouse_x < (info->x + root_win->w) &&
		mouse_y > info->y + 23 && mouse_y < (info->y + root_win->h)) {
			for (int i = 0; i < root_win->widgets->pointer; i++) {
				QuWidget *wid = (QuWidget*)QuListGetAt(root_win->widgets, i);
				if (mouse_x > (info->x + wid->x) && mouse_x < (info->x + wid->x + wid->width) &&
					mouse_y > (info->y + wid->y) && mouse_y < (info->y + wid->y + wid->height)) {

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
	
	}

	for (int i = 0; i < root_win->controls->pointer; i++) {
		QuWinControl *control = (QuWinControl*)QuListGetAt(root_win->controls, i);
		if (mouse_x > (info->x + control->x) && mouse_x < (info->x + control->x + control->w) &&
			mouse_y > (info->y + control->y) && mouse_y < (info->y + control->y + control->h)) {

				if (code == QU_CANVAS_MOUSE_LCLICKED /*&& old_mouse_x == mouse_x && old_mouse_y == mouse_y*/)
					control_click = true;
				control->hover = true;

				control->ControlRedraw (control,root_win, control_click);
		}else {
			control->ControlRedraw(control, root_win, false);
		}

	}
	
	old_mouse_x = mouse_x;
	old_mouse_y = mouse_y;
}



void QuWindowHandleKey (int code) {
	for (int i = 0; i < root_win->widgets->pointer; i++) {
		QuWidget *wid = (QuWidget*)QuListGetAt(root_win->widgets, i);
		//! Make the difference between left click and dragging here
		if (root_win->focus_widget == wid && wid->KeyEvent != 0)
			wid->KeyEvent(wid, root_win,code);
	}
}


void QuWindowSetTransparency (bool bit) {
	QuWinInfo *info = (QuWinInfo*)root_win->win_info_data;
	info->alpha = true;
}