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
#include <QuCanvas\QuScreenStack.h>
#include <QuWindow\QuWindowMngr.h>
#include <QuCanvas\QuScreenRectList.h>
#include <QuCursor.h>
#include <acrylic.h>
#include <string.h>
#include <fastcpy.h>
#include <QuWidget\QuWallpaper.h>
#include <QuWidget\QuDock.h>


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
uint32_t* QuCanvasCreate (uint16_t dest_pid, int w, int h) {
	uint32_t pos = cursor_pos;
	uint32_t size = w * h * 32;
	map_shared_memory(dest_pid,QU_CANVAS_START + pos,size);
	cursor_pos += size;
	return (uint32_t*)(QU_CANVAS_START + pos);
}

void QuCanvasRelease (uint16_t dest_pid, QuWindow *win) {
	uint32_t size = canvas_get_width(QuGetCanvas()) * canvas_get_height(QuGetCanvas()) * 32;
	sys_unmap_sh_mem(dest_pid, (uint64_t)win->canvas, size);
	cursor_pos -= size;
}



void QuCanvasBlit (QuWindow* win,unsigned int *canvas, unsigned x, unsigned y, unsigned w, unsigned h) {
	uint32_t* lfb = (uint32_t*)0x0000600000000000;
	uint32_t* wallp = (uint32_t*)0x0000600000000000;   //0x0000060000000000;
	int width = canvas_get_width(QuGetCanvas());
	int height = canvas_get_height(QuGetCanvas());
	int j = 0;

	//! No Auto-invalidation window 
	//! this is a normal window, it must contains dirty areas
	//! go through dirty areas and draw it
	QuWindowInfo *info = (QuWindowInfo*)win->win_info_location;
	if (info->dirty) {
		if (info->rect_count > 0) {
			for (int k = 0; k < info->rect_count; k++) {
				int wid = info->rect[k].w;
				int he = info->rect[k].h;
				int rx = info->rect[k].x;
				int ry = info->rect[k].y;

				if (rx < 0)
					rx = 0;

				if (ry < 0)
					ry = 0;


				if (info->rect[k].x + info->rect[k].w >= width)
					wid  = width - info->rect[k].x;

				if (info->rect[k].y + info->rect[k].h>= height - 40){
					info->y = height - win->height;
				}

				if (info->alpha) {
				}else {
					for (int i = 0; i < he; i++)  {
						fastcpy (lfb + (info->y + ry + i) * width + (info->x + rx),win->canvas + (ry + i) * width + rx, 
							wid * 4);
					}
				}

				//canvas_screen_update(QuGetCanvas(),info->x + rx,info->y + ry, wid, he);
				QuScreenRectAdd(info->x + rx,info->y + ry, wid, he);
			}

			info->rect_count = 0;
#ifdef SW_CURSOR
			//QuMoveCursor(QuCursorGetNewX(), QuCursorGetNewY());
#endif

		} else if (info->rect_count == 0){	
			int wid = win->width;
			int he = win->height;
			int winx = info->x;
			int winy = info->y;

			if (winx < 0) {
				info->x = 0;
				winx = info->x;
			}

			if (winy < 0) {
				info->y = 0;
				winy = 0;
			}


			if (info->x + win->width >= width)
				wid  = width - info->x;

			if (info->y + win->height >= (height - 40)){
				info->y = (height - 40) - win->height;
				winy = info->y;
				he = (height - 40) - info->y;
			}

			for (int i = 0; i < he; i++)  {
				fastcpy (lfb + (winy + i) * width + winx,win->canvas + (0 + i) * width + 0,
						wid * 4);	
			}

			QuScreenRectAdd(winx, winy, wid, he);
		//	QuTaskbarRepaint();
		}

		info->dirty = false;
		
	}

	if (win->mark_for_close) {
		//win->mark_for_close = false;
		uint16_t id = win->owner_id;
		QuCanvasRelease(win->owner_id, win);
		QuCanvasUpdate(info->x, info->y, win->width, win->height);
		QuScreenRectAdd(info->x, info->y, win->width, win->height);
		QuWindowMngr_Remove(win);
		QuCanvasSetUpdateBit(true);
		QuWindowMngr_DrawBehind(win);
		
		QuMessage msg;
		msg.to_id = id;
		msg.type = QU_CANVAS_DESTROYED;
		QuChannelPut(&msg,id);
	}


	/*if (info->maximize) {
		if (!win->maximize) {
			win->maximize = true;
	    	win->old_x = win->x;
		    win->old_y = win->y;
		    win->old_w = win->width;
		    win->old_h = win->height;
		    win->x = 0;
		    win->y = 0;
		    win->width = canvas_get_width();
		    win->height = canvas_get_height();
			info->dirty = 1;
			info->rect_count = 0;
		}
	}*/

}



void QuCanvasPutPixel (uint32_t *canvas, unsigned x, unsigned y, uint32_t color) {
	canvas[x + y * canvas_get_scale(QuGetCanvas())] = color;
}

uint32_t QuCanvasGetPixel (uint32_t *canvas, unsigned x, unsigned y) {
	return canvas[x + y * canvas_get_scale(QuGetCanvas())];
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
	int width = canvas_get_width(QuGetCanvas());
	int height = canvas_get_height(QuGetCanvas());

	if (x + w >= width)
		w = width - x;

	if (y + h >= height - 40)
		h = (height - 40) - y;


	for (int i=0; i < w; i++) {
		for (int j=0; j < h; j++){
			uint32_t color = wallp[(x + i) + (y + j) * canvas_get_scale(QuGetCanvas())];
			lfb[(x + i) + (y + j) * canvas_get_scale(QuGetCanvas())] = color;
			
		}
	}
}


void QuCanvasUpdateDirty() {
	for (int i = 0; i < dirty_r_count; i++) {
		QuCanvasUpdate(dirty_rect[i].x, dirty_rect[i].y, dirty_rect[i].w, dirty_rect[i].h);
		QuScreenRectAdd(dirty_rect[i].x, dirty_rect[i].y, dirty_rect[i].w, dirty_rect[i].h);
	}
	dirty_r_count = 0;
}

 void QuCanvasSetUpdateBit(bool value) {
	 update_bit = value;
 }

 bool QuCanvasGetUpdateBit() {
	 return update_bit;
 }


 void QuCanvasUpdateAll () {
	 uint32_t* lfb = (uint32_t*)0x0000600000000000;
	uint32_t* fb = (uint32_t*)0xFFFFF00000000000;
	uint32_t* wallp = (uint32_t*)0x0000600000000000;   //0x0000060000000000;
	int width = canvas_get_width(QuGetCanvas());
	int height = canvas_get_height(QuGetCanvas());
	 for (int i = 0; i < QuWindowMngr_GetList()->pointer; i++) {
		 QuWindow* win = (QuWindow*)QuListGetAt(QuWindowMngr_GetList(), i);
		 QuWindowInfo *info = (QuWindowInfo*)win->win_info_location;
		 info->dirty = 1;
		 info->rect_count = 0;
	 }
 }



 void QuRenderTime (uint8_t sec, uint8_t min, uint8_t hr) {
    acrylic_draw_rect_filled (QuGetCanvas(),canvas_get_width(QuGetCanvas()) - 102, canvas_get_height(QuGetCanvas()) - 35,100-2,30,0xD9C0C0C0);
	/*acrylic_draw_rect_unfilled (QuGetCanvas(),canvas_get_width(QuGetCanvas()) - 100, canvas_get_height(QuGetCanvas()) - 35, 100, 30,0xD9FFFFFF);*/

	char _sec[2];
	char _min[2];
	char _hour[2];
	memset (_sec, 0, 2);
	memset (_min, 0, 2);
	memset (_hour, 0, 2);

	if (hr > 12) {
		hr = hr - 12;
	}

	sztoa(sec,_sec,10);
	sztoa(min,_min, 10);
	sztoa(hr,_hour, 10);


	acrylic_draw_arr_string (QuGetCanvas(),canvas_get_width(QuGetCanvas()) - 100 + 100/2 - (strlen(_hour)*8)/2 - 16,
		canvas_get_height(QuGetCanvas()) - 35 + 30/2 - 12/2,
		_hour, 
		0xD9000000);

	acrylic_draw_arr_string (QuGetCanvas(),canvas_get_width(QuGetCanvas()) - 100 + 100/2 - (strlen(":")*8)/2 - 9,
		canvas_get_height(QuGetCanvas()) - 35 + 30/2 - 12/2,
		":", 
		0xD9000000);

	acrylic_draw_arr_string (QuGetCanvas(),canvas_get_width(QuGetCanvas()) - 100 + 100/2 - (strlen(_min)*8)/2,
		canvas_get_height(QuGetCanvas()) - 35 + 30/2 - 12/2,
		_min, 
		0xD9000000);

	acrylic_draw_arr_string (QuGetCanvas(),canvas_get_width(QuGetCanvas()) - 100 + 100/2 - (strlen(":")*8)/2 + 9,
		canvas_get_height(QuGetCanvas()) - 35 + 30/2 - 12/2,
		":", 
		0xD9000000);

	acrylic_draw_arr_string (QuGetCanvas(),canvas_get_width(QuGetCanvas()) - 100 + 100/2 - (strlen(_sec)*8)/2 + 19,
		canvas_get_height(QuGetCanvas()) - 35 + 30/2 - 12/2,
		_sec, 
		0xD9000000);

	canvas_screen_update(QuGetCanvas(),canvas_get_width(QuGetCanvas()) - 100, canvas_get_height(QuGetCanvas()) - 35,100,30);

 }