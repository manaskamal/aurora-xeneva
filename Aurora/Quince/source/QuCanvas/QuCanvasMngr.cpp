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
#include <QuUtils\QuList.h>
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
QuList *canvas_list;
int dirty_r_count;

typedef struct _QuCanvasArea_ {
	uint16_t owner_id;
	uint64_t pos;
	uint32_t size;
	bool free;
}QuCanvasArea;

void QuCanvasMngr_Initialize() {
	memset(dirty_rect, 0, 512);
	dirty_r_count = 0;
	canvas_list = QuListInit();
}

//!Creates a canvas
uint32_t* QuCanvasCreate (uint16_t dest_pid, int w, int h) {
	
	uint32_t pos;
	uint64_t addr = 0;
	uint32_t size = w * h * 32;
	for (int i = 0; i < canvas_list->pointer; i++) {
		QuCanvasArea *ar = (QuCanvasArea*)QuListGetAt(canvas_list,i);
		if (ar->free) {
			addr = ar->pos;
			map_shared_memory(dest_pid,addr,size);
			//sys_print_text ("Reusing CA-> %x, %d\n", addr,ar->size);
			ar->free = false;
			ar->owner_id = dest_pid;
			break;
		}
		pos += ar->size;
	}
	uint32_t screen_res = canvas_get_width(QuGetCanvas()) * canvas_get_height(QuGetCanvas()) * 32;
	uint32_t diff = screen_res - size;
	if (addr == NULL) {
		QuCanvasArea *area = (QuCanvasArea*)malloc(sizeof(QuCanvasArea));
		map_shared_memory(dest_pid,QU_CANVAS_START + pos,size);
		area->pos = QU_CANVAS_START + pos;
		area->size = size + diff;
		area->owner_id = dest_pid;
		addr = area->pos;
		QuListAdd(canvas_list,area);
	}
	return (uint32_t*)(addr);
}

void QuCanvasRelease (uint16_t dest_pid, QuWindow *win) {
	QuCanvasArea *area = NULL;
	int i = 0;
	for (i = 0; i < canvas_list->pointer; i++) {
		area = (QuCanvasArea*)QuListGetAt(canvas_list,i);
		if (area->owner_id == dest_pid) 
			break;
	}
	uint32_t size = area->size;
	sys_unmap_sh_mem(dest_pid, (uint64_t)win->canvas, size);
	area->free = true;
}


void QuCanvasRemap (uint16_t dest_pid, void *canvas, int w, int h) {
	QuCanvasArea *area = NULL;
	uint64_t pos = 0;
	uint32_t size = w * h * 32;
	for (int i = 0; i < canvas_list->pointer; i++) {
		area = (QuCanvasArea*)QuListGetAt(canvas_list,i);
		if (area->owner_id == dest_pid && area->size== size) 
			return;
		pos += area->size;
	}

	for (int i = 0; i < canvas_list->pointer; i++) {
		area = (QuCanvasArea*)QuListGetAt(canvas_list,i);
		sys_unmap_sh_mem(dest_pid,(uint64_t)canvas, area->size);
		area->free = true;
		break;
	}
	QuCanvasArea *area_n = (QuCanvasArea*)malloc(sizeof(QuCanvasArea));
	area_n->free = false;
	area_n->size = size;
	area_n->pos = QU_CANVAS_START + pos;
	area_n->owner_id = dest_pid;
	map_shared_memory (dest_pid, (uint64_t)area_n->pos,size);
	QuListAdd(canvas_list,area_n);
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

				
				if (info->rect[k].x + info->rect[k].w >= win->width)
					wid  = win->width - info->rect[k].x;

				if (info->rect[k].y + info->rect[k].h>= win->height){
					info->rect[k].y = win->height - info->rect[k].y;
				}

				if (info->x + info->rect[k].x + info->rect[k].w > width)
					wid  = width - (info->x + info->rect[k].x);


				if (info->alpha) {
					for(int j = 0; j < he; j++)
						for(int i = 0; i < wid; i++)
							*(uint32_t*)(lfb + (info->y + ry + j)* width + (info->x + rx + i)) =
							alpha_blend(*(uint32_t*)(lfb + (info->y + ry + j)* width+ (info->x + rx + i)),
							*(uint32_t*)(win->canvas + (ry + j)*width + (rx + i)));
				}else {
					for (int i = 0; i < he; i++)  {
						fastcpy (lfb + (info->y + ry + i) * width + (info->x + rx),win->canvas + (ry + i) * width + rx, 
							wid * 4);
					}
				}

				QuScreenRectAdd(info->x + rx,info->y + ry, wid, he);
			}

			info->rect_count = 0;
		} else if (info->rect_count == 0){
			int wid = win->width;
			int he = win->height;
			int winx = info->x;
			int winy = info->y;

			if (winx - 5 < 0) {
				info->x = 5;
				winx = info->x;
			}

			if (winy - 5 < 0) {
				info->y = 5;
				winy = 5;
			}


			if (info->x + win->width >= width)
				wid  = width - info->x;

			if (info->y + win->height >= (height - 40)){
				info->y = (height - 40) - win->height;
				winy = info->y;
				he = (height - 40) - info->y;
			}

			if (win->drop_shadow && QuWindowMngrGetFocused() == win) {
				for(int j = 0; j < he + 5; j++)
                 for(int i = 0; i < wid + 5; i++)
					 *(uint32_t*)(lfb + (winy - 5 + j)* width + (winx - 5 + i)) =alpha_blend(*(uint32_t*)(lfb + (winy - 5 + j)* width+ (winx - 5 + i)),
					 *(uint32_t*)(win->drop_shadow->address + 
					 j*width + i));
			}

			
			if (info->alpha) {
				for(int j = 0; j < he; j++)
                 for(int i = 0; i < wid; i++)
					 *(uint32_t*)(lfb + (winy + j)* width + (winx + i)) =alpha_blend(*(uint32_t*)(lfb + (winy + j)* width+ (winx + i)),
					 *(uint32_t*)(win->canvas + 
					 j*width + i));
			} else {
				for (int i = 0; i < he; i++)  {
					fastcpy (lfb + (winy + i) * width + winx,win->canvas + (0 + i) * width + 0,
						wid * 4);	
			    }
			}
               
			QuScreenRectAdd(winx - 5, winy - 5, wid + 5, he + 5);
		}

		info->dirty = false;
	}

	if (win->mark_for_close) {
		QuDockRemove(win->dock);
		QuDockRepaint();

		uint16_t id = win->owner_id;
		QuCanvasRelease(win->owner_id, win);
		QuCanvasUpdate(info->x - 5, info->y - 5, win->width + 5, win->height + 5);
		QuScreenRectAdd(info->x - 5,info->y - 5, win->width + 5, win->height + 5);	
		//sys_unmap_sh_mem(id, (uint64_t)win->win_info_location, 8192);	

		QuWindowMngr_Remove(win);
		//QuCanvasSetUpdateBit(true);
		QuWindowMngr_DrawBehind(win);
		
	

		QuMessage msg;
		msg.to_id = id;
		msg.type = QU_CANVAS_DESTROYED;
		QuChannelPut(&msg,id);
	}


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

	canvas_screen_update(QuGetCanvas(),canvas_get_width(QuGetCanvas()) - 102, canvas_get_height(QuGetCanvas()) - 35,100,30);

 }