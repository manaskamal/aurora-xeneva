///! Copyright (C) Manas Kamal Choudhury 2021
///! 
///! QuPanel -- Main Client Area where GUI Object sits
///!
///! /PROJECT - Aurora's Xeneva
///! /AUTHOR  - Manas Kamal Choudhury
///!
///!====================================================

#include <QuPanel.h>
#include <stdlib.h>
#include <QuWindow.h>
#include <QuRect.h>
#include <canvas.h>
#include <QuBase.h>
#include <sys\_ipc.h>
#include <sys\_process.h>
#include <acrylic.h>
#include <color.h>
#include <sys\_term.h>
#include <sys\_sleep.h>

bool panel_update = false;

void QuPanelMouseEvent (QuWidget *widget, QuWindow* win, int code, bool clicked) {
	//! No Effect
}

void QuPanelActionEvent (QuWidget *widget, QuWindow* win) {
}

QuPanel* QuCreatePanel () {
	QuPanel* panel = (QuPanel*)malloc(sizeof(QuPanel));
	panel->base.x = 0;
	panel->base.y = 0;
	panel->base.width = QuGetWindow()->w;
	panel->base.height = QuGetWindow()->h;
	panel->base.Refresh = QuPanelRefresh;
	panel->base.MouseEvent = QuPanelMouseEvent;
	panel->base.ActionEvent = QuPanelActionEvent;
	panel->color = 0xFFFFFFFF;
	return panel;
}


void QuPanelSetBackground (QuPanel* panel,uint32_t color) {
	panel->color = color;
}

void QuPanelRefresh (QuWidget *wid, QuWindow* win) {
	QuPanel *panel = (QuPanel*)wid;
	acrylic_draw_rect_filled(win->x + wid->x, win->y + wid->y, wid->width, wid->height,panel->color);
}


void QuPanelUpdate(int x, int y, int w, int h) {
	if (canvas_is_double_buffered()){
	uint32_t* lfb = (uint32_t*)QuGetWindow()->canvas;
	uint32_t* dbl_canvas = (uint32_t*)0x0000600000000000;
	int width = canvas_get_width();
	int height = canvas_get_height();
	for (int i=0; i < w; i++) {
		for (int j=0; j < h; j++){
			uint32_t color = dbl_canvas[(x + i) + (y + j) * width];
			lfb[(x + i) + (y + j) * width] = color;
		}
	}
	}

	QuMessage msg;
	msg.type = QU_CODE_DIRTY_UPDATE;
	msg.dword = x;
	msg.dword2 = y;
	msg.dword3 = w;
	msg.dword4 = h;
	QuChannelPut(&msg, 2);
	//message_t msg;
	//msg.type = QU_CODE_DIRTY_UPDATE;
	//msg.dword = x;
	//msg.dword2 = y;
	//msg.dword3 = w;
	//msg.dword4 = h;
	//msg.dword5 = get_current_pid();
	//message_send(2, &msg);
}


void QuPanelRepaint (int x, int y, int w, int h) {
	QuMessage msg;
	msg.type = QU_CODE_REPAINT;
	msg.dword = x;
	msg.dword2 = y;
	msg.dword3 = w;
	msg.dword4 = h;
	QuChannelPut(&msg, 2);
}


void QuPanelUpdateRequired (bool value) {
	panel_update = value;
}

void QuPanelContentUpdate(int x, int y, int w, int h) {
	if (panel_update) {
	uint32_t* lfb = (uint32_t*)QuGetWindow()->canvas;
	uint32_t* dbl_canvas = (uint32_t*)0x0000600000000000;
	/*int width = canvas_get_width();
	int height = canvas_get_height();*/
	for (int i=0; i < w; i++) {
		for (int j=0; j < h; j++){
			uint32_t color = dbl_canvas[(x + i) + (y + j) * canvas_get_width()];
			lfb[(x + i) + (y + j) * canvas_get_width()] = color;
		}
	}
	panel_update = false;
	}
}