///! 
///!   Copyright (C) Manas Kamal Choudhury 2021
///!   
///!  QuCanvasMngr -- Quince Canvas Manager
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!=================================================

#include <QuCanvas\QuCanvasMngr.h>
#include <QuCode.h>
#include <QuWindow\QuList.h>
#include <canvas.h>
#include <sys\mmap.h>
#include <ipc\QuChannel.h>
#include <sys\_ipc.h>
#include <stdint.h>
#include <sys\_process.h>
#include <sys\_term.h>
#include <color.h>
#include <QuRect.h>
#include <stdlib.h>

#define QU_CANVAS_START   0x0000100000000000

uint32_t cursor_pos = 0;
QuList * dirty_list = NULL;
bool update_bit = false;

void QuCanvasMngr_Initialize() {
	dirty_list = QuListInit();
}

//!Creates a canvas
uint32_t* QuCanvasCreate (uint16_t dest_pid) {
	uint32_t pos = cursor_pos;
	uint32_t size = canvas_get_width() * canvas_get_height() * 32;
	map_shared_memory(dest_pid,QU_CANVAS_START + pos,size);
	cursor_pos += size;
	return (uint32_t*)(QU_CANVAS_START + pos);
}


void QuCanvasCommit (uint32_t* canvas, uint16_t destid, unsigned x, unsigned y, unsigned w, unsigned h) {
	QuMessage msg;
	msg.type = QU_CANVAS_READY;
	msg.from_id = get_current_pid();
	msg.to_id = destid;
	msg.p_value = canvas;
	msg.dword = x;
	msg.dword2 = y;
	msg.dword3 = w;
	msg.dword4 = h;
	QuChannelPut(&msg,destid);
	//sys_unblock_id (destid);
}

void QuCanvasBlit (uint32_t *canvas, unsigned x, unsigned y, unsigned w, unsigned h) {
	uint32_t* lfb = (uint32_t*)0x0000600000000000;
	uint32_t* wallp = (uint32_t*)0x0000060000000000;
	int width = canvas_get_width();
	int height = canvas_get_height();
	for (int i=0; i < w; i++) {
		for (int j=0; j < h; j++){
			if (canvas[(x + i) + (y + j) * width] | 0x00000000){
			uint32_t color = canvas[(x + i) + (y + j) * width];
			//uint32_t color_a = wallp[(x + i) + (y + j) * width];
			lfb[(x + i) + (y + j) * width] = color; //alpha_blend(color_a, color);
			}
		}
	}
}


void QuCanvasPutPixel (uint32_t *canvas, unsigned x, unsigned y, uint32_t color) {
	canvas[x + y * canvas_get_scale()] = color;
}

uint32_t QuCanvasGetPixel (uint32_t *canvas, unsigned x, unsigned y) {
	return canvas[x + y * canvas_get_scale()];
}


void QuCanvasAddDirty (QuRect *r) {
	QuListAdd (dirty_list, r);
}

void QuCanvasUpdate (unsigned x, unsigned y, unsigned w, unsigned h) {
	
	uint32_t* lfb = (uint32_t*)0x0000600000000000;
	uint32_t* wallp = (uint32_t*)0x0000060000000000;
//	int width = canvas_get_width();
//	int height = canvas_get_height();
	for (int i=0; i < w; i++) {
		for (int j=0; j < h; j++){
			uint32_t color = wallp[(x + i) + (y + j) * canvas_get_scanline()];
			lfb[(x + i) + (y + j) * canvas_get_scanline()] = color;
		}
	}
}


void QuCanvasUpdateDirty() {
	if (dirty_list->pointer > 0) {
		for (int i = 0; i < dirty_list->pointer; i++) {
			QuRect* r = (QuRect*)QuListGetAt (dirty_list, i);
			QuCanvasUpdate(r->x, r->y, r->w, r->h);
			canvas_screen_update (r->x, r->y, r->w, r->h);
			QuListRemove(dirty_list, i);
			free(r);
			/*if (!update_bit)
				QuCanvasSetUpdateBit(true);*/
		}
	}
}

 void QuCanvasSetUpdateBit(bool value) {
	 update_bit = value;
 }

 bool QuCanvasGetUpdateBit() {
	 return update_bit;
 }