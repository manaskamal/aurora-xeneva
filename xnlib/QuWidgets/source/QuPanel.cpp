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
#include <string.h>
#include <fastcpy.h>

bool panel_update = false;

void QuPanelMouseEvent (QuWidget *widget, QuWindow* win, int code, bool clicked, int x, int y) {
	//! No Effect
}

void QuPanelActionEvent (QuWidget *widget, QuWindow* win) {
}

QuPanel* QuCreatePanel (QuWindow *win) {
	QuPanel* panel = (QuPanel*)malloc(sizeof(QuPanel));
	panel->base.x = 0;
	panel->base.y = 0;
	panel->base.width = win->w;
	panel->base.height = win->h;
	panel->base.Refresh = QuPanelRefresh;
	panel->base.MouseEvent = QuPanelMouseEvent;
	panel->base.KeyEvent = 0;
	panel->base.ActionEvent = QuPanelActionEvent;
	panel->base.ScrollEvent = NULL;
	panel->color = 0xFFFFFFFF;
	return panel;
}


void QuPanelSetBackground (QuPanel* panel,uint32_t color) {
	panel->color = color;
}

void QuPanelRefresh (QuWidget *wid, QuWindow* win) {
	QuPanel *panel = (QuPanel*)wid;
	acrylic_draw_rect_filled(win->ctx,wid->x,wid->y, wid->width, wid->height,panel->color);
}


void QuPanelUpdate(QuWindow *win,int x, int y, int w, int h, bool move) {

	uint32_t* lfb = win->canvas;
	uint32_t* dbl_canvas = win->ctx->address;   //0x0000600000000000;
	int width = canvas_get_width(win->ctx);
	int height = canvas_get_height(win->ctx);

	if (move) {
		x = 0;
		y = 0;
	}

	for (int i = 0; i < h; i++)
		fastcpy (lfb + (y + i) * width + x,dbl_canvas + (y + i) * width + x, w * 4);
	 
	QuWinInfo *info = (QuWinInfo*)win->win_info_data;
	info->dirty = 1;
	if (move){
		info->rect_count = 0;
	}else {
		info->rect[info->rect_count].x = x;
		info->rect[info->rect_count].y = y;
		info->rect[info->rect_count].w = w;
		info->rect[info->rect_count].h = h;
		info->rect_count++;
	}
	
}

void QuPanelDirectCopy(canvas_t *canvas, int x, int y, int w, int h) {
	uint32_t* lfb = (uint32_t*)QuGetWindow()->canvas;

	int width = canvas_get_width(canvas);
	int height = canvas_get_height(canvas);

	for (int i = 0; i < h; i++)
		fastcpy (lfb + (y + i) * width + x,canvas->address + (y + i) * width + x, w * 4);

	QuWinInfo *info = (QuWinInfo*)QuGetWindow()->win_info_data;
	info->dirty = 1;
	info->rect[info->rect_count].x = x;
	info->rect[info->rect_count].y = y;
	info->rect[info->rect_count].w = w;
	info->rect[info->rect_count].h = h;
	info->rect_count++;
}


void QuPanelRepaint (int x, int y, int w, int h) {
	uint32_t* lfb = (uint32_t*)QuGetWindow()->canvas;
	uint32_t* dbl_canvas = (uint32_t*)0x0000600000000000;
	int width = canvas_get_width(QuGetWindow()->ctx);
	int height = canvas_get_height(QuGetWindow()->ctx);
	/*for (int i=0; i < w; i++) {
		for (int j=0; j < h; j++){
			uint32_t color = dbl_canvas[(x + i) + (y + j) * width];
			lfb[(x + i) + (y + j) * width] = color;
		}
	}*/
	for (int i = 0; i < h; i++)
		fastcpy (lfb + (y + i) * width + x,dbl_canvas + (y + i) * width + x, w * 4);
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
			uint32_t color = dbl_canvas[(x + i) + (y + j) * canvas_get_width(QuGetWindow()->ctx)];
			lfb[(x + i) + (y + j) * canvas_get_width(QuGetWindow()->ctx)] = color;
		}
	}
	panel_update = false;
	}
}