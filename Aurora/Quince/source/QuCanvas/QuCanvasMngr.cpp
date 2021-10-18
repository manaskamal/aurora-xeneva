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
#include <sys\ioquery.h>
#include <sys\_process.h>
#include <sys\_term.h>
#include <color.h>
#include <QuRect.h>
#include <stdlib.h>
#include <QuCanvas\QuDirtyStack.h>
#include <QuCanvas\QuScreenStack.h>
#include <QuWindow\QuWindowMngr.h>
#include <QuCursor.h>
#include <acrylic.h>
#include <string.h>

#define QU_CANVAS_START   0x0000100000000000

uint32_t cursor_pos = 0;
bool update_bit = false;
QuRect dirty_rect[512];
int dirty_r_count;

void QuCanvasMngr_Initialize() {
	memset(dirty_rect, 0, 512);
	dirty_r_count = 0;
	//dirty_list = QuListInit();
}

//!Creates a canvas
uint32_t* QuCanvasCreate (uint16_t dest_pid) {
	uint32_t pos = cursor_pos;
	uint32_t size = canvas_get_width() * canvas_get_height() * 32;
	map_shared_memory(dest_pid,QU_CANVAS_START + pos,size);
	cursor_pos += size;
	return (uint32_t*)(QU_CANVAS_START + pos);
}

void QuCanvasRelease (uint16_t dest_pid, QuWindow *win) {
	uint32_t size = canvas_get_width() * canvas_get_height() * 32;
	sys_unmap_sh_mem(dest_pid, (uint64_t)win->canvas, size);
	//cursor_pos -= size;
}


void QuCanvasCommit (uint32_t* canvas, uint16_t destid, unsigned x, unsigned y, unsigned w, unsigned h) {
	//sys_unblock_id (destid);
}

void QuCanvasBlit (QuWindow* win,uint32_t *canvas, unsigned x, unsigned y, unsigned w, unsigned h) {
	uint32_t* lfb = (uint32_t*)0x0000600000000000;
	uint32_t* fb = (uint32_t*)0xFFFFF00000000000;
	uint32_t* wallp = (uint32_t*)0x0000600000000000;   //0x0000060000000000;
	int width = canvas_get_width();
	int height = canvas_get_height();
	int j = 0;

	//! No Auto-invalidation window 
	//! this is a normal window, it must contains dirty areas
	//! go through dirty areas and draw it
	QuWindowInfo *info = (QuWindowInfo*)win->win_info_location;
	if (info->dirty) {
		if (info->rect_count > 0) {
			for (int k = 0; k < info->rect_count; k++) {
				for (int i=0; i < info->rect[k].w; i++) {
					for (int j=0; j < info->rect[k].h; j++){
						if (win->canvas[(info->rect[k].x + i) + (info->rect[k].y + j) * width] | 0x00000000){
							uint32_t color = win->canvas[(info->rect[k].x + i) + (info->rect[k].y + j) * width];
							uint32_t color_a = wallp[(info->rect[k].x + i) + (info->rect[k].y + j) * width];
							lfb[(info->rect[k].x + i) + (info->rect[k].y + j) * width] =  alpha_blend(color_a, color); //win->canvas[(win->x + i) + (win->y + j) * width];	
						}
					}
				}
				canvas_screen_update(info->rect[k].x, info->rect[k].y, info->rect[k].w, info->rect[k].h);
			}
#ifdef SW_CURSOR
			QuMoveCursor(QuCursorGetNewX(), QuCursorGetNewY());
#endif
			info->rect_count = 0;
		} else {
			

			for (int i=0; i < win->width; i++) {
				for (int j=0; j < win->height; j++){
					if (win->canvas[(win->x + i) + (win->y + j) * width] | 0x00000000){
						uint32_t color = win->canvas[(win->x + i) + (win->y + j) * width];
						uint32_t color_a = wallp[(win->x + i) + (win->y + j) * width];
						lfb[(win->x + i) + (win->y + j) * width] =  alpha_blend(color_a, color); //win->canvas[(win->x + i) + (win->y + j) * width];	
					}
				}
			}
			QuCanvasSetUpdateBit(true);
		}
#ifdef SW_CURSOR
		QuMoveCursor(QuCursorGetNewX(), QuCursorGetNewY());
#endif
		info->dirty = false;	
		
	}

	if (win->mark_for_close) {
		//win->mark_for_close = false;
		uint16_t id = win->owner_id;
		QuCanvasRelease(win->owner_id, win);
		QuCanvasUpdate(win->x, win->y, win->width, win->height);
		QuWindowMngr_Remove(win);
		QuCanvasSetUpdateBit(true);
		QuWindowMngr_DrawBehind(win);
		/*QuMessage msg;
		msg.type = QU_CANVAS_DESTROYED;
		QuChannelPut(&msg, id);*/
		sys_kill(id,2);
	}
  
}


void QuCanvasPutPixel (uint32_t *canvas, unsigned x, unsigned y, uint32_t color) {
	canvas[x + y * canvas_get_scale()] = color;
}

uint32_t QuCanvasGetPixel (uint32_t *canvas, unsigned x, unsigned y) {
	return canvas[x + y * canvas_get_scale()];
}


void QuCanvasAddDirty (int x, int y, int w, int h) {
	//QuStackPushRect(r);
	dirty_rect[dirty_r_count].x = x;
	dirty_rect[dirty_r_count].y = y;
	dirty_rect[dirty_r_count].w = w;
	dirty_rect[dirty_r_count].h = h;
	dirty_r_count++;
}


void QuCanvasUpdate (unsigned x, unsigned y, unsigned w, unsigned h) {
	
	uint32_t* lfb = (uint32_t*)0x0000600000000000;
	uint32_t* wallp = (uint32_t*)0x0000060000000000;
//	int width = canvas_get_width();
//	int height = canvas_get_height();
	for (int i=0; i < w; i++) {
		for (int j=0; j < h; j++){
			uint32_t color = wallp[(x + i) + (y + j) * canvas_get_scale()];
			lfb[(x + i) + (y + j) * canvas_get_scale()] = color;
			
		}
	}
}

void QuCanvasQuickPaint (uint32_t* canvas,int x, int y, int w,int h) {
	uint32_t* lfb = (uint32_t*)0x0000600000000000;

	for (int i=0; i < w; i++) {
		for (int j=0; j < h; j++){
			uint32_t color = canvas[(x + i) + (y + j) * canvas_get_scanline()];
			lfb[(x + i) + (y + j) * canvas_get_scanline()] = color;
			QuCanvasSetUpdateBit(true);
		}
	}
}


void QuCanvasCopyToFB(unsigned x, unsigned y, unsigned w, unsigned h) {
	uint32_t* lfb = (uint32_t*)0xFFFFF00000000000;
	uint32_t* canvas = (uint32_t*)0x0000600000000000;

	for (int i=0; i < w; i++) {
		for (int j=0; j < h; j++){
			uint32_t color = canvas[(x + i) + (y + j) * canvas_get_scanline()];
			lfb[(x + i) + (y + j) * canvas_get_scanline()] = color;
		}
	}
}


void QuCanvasUpdateDirty() {
	//if (QuStackGetRectCount() > 0) {
	//	QuRect* r = (QuRect*)QuStackGetRect();
	//	QuCanvasUpdate(r->x, r->y, r->w, r->h);
	//	//canvas_screen_update (r->x, r->y, r->w, r->h)
	//	free (r);
	//	//if (!QuCanvasGetUpdateBit())
	//	//QuCanvasSetUpdateBit(true);
	//	canvas_screen_update (r->x, r->y, r->w, r->h);
	//}
	for (int i = 0; i < dirty_r_count; i++) {
		QuCanvasUpdate(dirty_rect[i].x, dirty_rect[i].y, dirty_rect[i].w, dirty_rect[i].h);
	}
	dirty_r_count = 0;
}

 void QuCanvasSetUpdateBit(bool value) {
	 update_bit = value;
 }

 bool QuCanvasGetUpdateBit() {
	 return update_bit;
 }


 void QuCanvasQuery(unsigned x, unsigned y, unsigned w, unsigned h) {
	svga_io_query_t *query = (svga_io_query_t*)malloc(sizeof(svga_io_query_t));
	query->value = x;
	query->value2 = y;
	query->value3 = w;
	query->value4 = h;
	ioquery(IO_QUERY_SVGA, SVGA_UPDATE, query);
 }

 void QuRenderTime (uint8_t sec, uint8_t min, uint8_t hr) {
    acrylic_draw_rect_filled (canvas_get_width() - 100, canvas_get_height() - 35,100,30,0x8C3E3E3E);
	acrylic_draw_rect_unfilled (canvas_get_width() - 100, canvas_get_height() - 35, 100, 30,0xD9FFFFFF);

	char _sec[2];
	char _min[2];
	char _hour[2];

	sztoa(sec,_sec,10);
	sztoa(min,_min, 10);
	sztoa(hr,_hour, 10);


	acrylic_draw_arr_string (canvas_get_width() - 100 + 100/2 - (strlen(_hour)*8)/2 - 16,
		canvas_get_height() - 35 + 30/2 - 12/2,
		_hour, 
		0xD9FFFFFF);

	acrylic_draw_arr_string (canvas_get_width() - 100 + 100/2 - (strlen(":")*8)/2 - 9,
		canvas_get_height() - 35 + 30/2 - 12/2,
		":", 
		0xD9FFFFFF);

	acrylic_draw_arr_string (canvas_get_width() - 100 + 100/2 - (strlen(_min)*8)/2,
		canvas_get_height() - 35 + 30/2 - 12/2,
		_min, 
		0xD9FFFFFF);

	acrylic_draw_arr_string (canvas_get_width() - 100 + 100/2 - (strlen(":")*8)/2 + 9,
		canvas_get_height() - 35 + 30/2 - 12/2,
		":", 
		0xD9FFFFFF);

	acrylic_draw_arr_string (canvas_get_width() - 100 + 100/2 - (strlen(_sec)*8)/2 + 19,
		canvas_get_height() - 35 + 30/2 - 12/2,
		_sec, 
		0xD9FFFFFF);

	canvas_screen_update(canvas_get_width() - 100, canvas_get_height() - 35,100,30);

 }