/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2022, Manas Kamal Choudhury
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * /PROJECT - Aurora's Xeneva v1.0
 * @priwm.h -- pri_window manager
 *
 **/

#include "priwm.h"
#include "list.h"
#include "pri_event.h"
#include "pri_dirty_clip.h"
#include "pri_wallp_dirty_clip.h"

#include <stdint.h>
#include <string.h>
#include <acrylic.h>
#include <canvas.h>
#include <font.h>
#include <color.h>

#include <sys/_wait.h>
#include <sys/_xeneva.h>
#include <sys/_file.h>
#include <sys/ioquery.h>
#include <sys/_term.h>
#include <sys/mmap.h>
#include <sys/_ipc.h>
#include <sys/_sleep.h>
#include <sys/_time.h>
#include <sys/_process.h>
#include <sys/_kybrd.h>
#include <sys/pe.h>
#include <sys/shm.h>
#include <sys/sse2.h>
#include <fastcpy.h>

#include <xebase.h>

/* backing store & shared win start address */
#define BACKING_STORE_START   0x0000100000000000
#define SHARED_WIN_START      0x00000A0000000000
#define PRI_WM_RECEIVER       0xFFFFD00000000000

/* global variables */
canvas_t* canvas;
pri_wallpaper_t *wallpaper;
pri_bmp_image *arrow_cursor;
pri_bmp_image *spin_cursor;
uint32_t* cursor_back;
int pri_loop_fd;
bool _window_update_all_ = false;
bool _window_broadcast_mouse_ = true;

/* mouse coordinations */
uint32_t mouse_x, mouse_y;
uint32_t prev_x = 0, prev_y = 0;
int last_mouse_button = 0;
uint32_t shared_win_key_prefix = 100;
uint32_t backing_store_key_prefix = 400;

/* data structures */
list_t *window_list;
list_t *backing_store_list;
list_t *shared_win_space_list;
list_t *desktop_component_list;

/**
 * window bits
 */
pri_window_t *focused_win = NULL;
pri_window_t *top_window = NULL;
pri_window_t *dragg_win = NULL;
pri_window_t *resz_win = NULL;

/**
 * pri_create_rect -- create a new rectangle
 * @param x -- x coordinate (related to device)
 * @param y -- y coordinate
 * @param w -- width of the rect
 * @param h -- height of the rect
 */
pri_rect_t *pri_create_rect (int x, int y, int w, int h) {
	pri_rect_t* r = (pri_rect_t*)malloc(sizeof(pri_rect_t));
	r->x = x;
	r->y = y;
	r->w = w;
	r->h = h;
	return r;
}

/**
 * pri_add_clip -- add a clip rect
 * @param x -- x coordinate (related to device)
 * @param y -- y coordinate
 * @param w -- width of the rect
 * @param h -- height of the rect
 */
void pri_add_clip (int x, int y, int w, int h) {
	pri_add_dirty_clip(x, y, w, h);
}

/**
 * pri_wm_get_message -- pops out a message from its
 * receiver
 * @param event -- pointer to store current message
 */
void pri_wm_get_message (pri_event_t *ev) {
   void* addr = (void*)PRI_WM_RECEIVER;	 
   pri_event_t* data = (pri_event_t*)addr;
   uint16_t to_id = get_current_pid ();

   if (data->type != 0){
	   memcpy (ev, data, sizeof(pri_event_t));
	   memset(addr, 0, 4096);
   }
}


/**
 * create_new_backing_store -- creates new backing store
 * for server and client to share
 * @param owner_id -- owner id to serve the backing store
 * @param size -- size of the backing store
 * @return -- return the new backing store
 */
void* create_new_backing_store (uint16_t owner_id, int size, uint16_t *key) {
	uint32_t* addr = (uint32_t*)BACKING_STORE_START;
	uint32_t cursor = 0;
	uint32_t key_prefix = backing_store_key_prefix + owner_id;
	/* check, every backing store slots for free slot */
	for (int i = 0; i < backing_store_list->pointer; i++) {
		backing_store_t *store = (backing_store_t*)list_get_at(backing_store_list, i);
		if (store) {
			/* check if any backing store slot is free, 
			 * if yes, than use that rather than populating
			 * virtual addresses
			 */
			if (store->free) {
				map_shared_memory (owner_id, (uint64_t)store->addr, size);
				store->owner_id = owner_id;
				store->free = false;
				return store->addr;
			} else {
				/* increase the cursor pos for better address
				 * alignment
				 */
				cursor += store->size;
			}
		}
	}

	/* no free backing store slot was found, create one */
	addr += cursor;
	//map_shared_memory (owner_id, (uint64_t)addr, size);
	int id = sys_shmget(key_prefix,size,0);
	void* ptr = sys_shmat(id,0,NULL);
	*key = key_prefix;
	backing_store_key_prefix += 10;
	backing_store_t *new_back_store = (backing_store_t*)malloc(sizeof(backing_store_t));
	new_back_store->addr = (uint32_t*)ptr;
	new_back_store->size = size;
	new_back_store->free = false;
	new_back_store->owner_id = owner_id;
	list_add (backing_store_list, new_back_store);	
	return ptr;
}

/**
 * free_backing_store -- make it available for others usage
 * @param store -- the desired backing_store slot
 */
void free_backing_store (uint16_t owner_id) {
	backing_store_t *_store = 0;
	for (int i = 0; i < backing_store_list->pointer; i++) {
		_store = (backing_store_t*)list_get_at(backing_store_list, i);
		if (_store->owner_id == owner_id) {
			break;
		}
	}

	//sys_unmap_sh_mem (_store->owner_id,(uint64_t)_store->addr,_store->size);
	//sys_shm_unlink(store
	_store->free = true;
	_store->owner_id = 0;
}


/**
 * remove_backing_store -- finally totally remove the backing store
 * from the list
 * @param store -- desired backing store to remove
 */
void remove_backing_store (uint16_t owner_id) {
	for (int i = 0; i < backing_store_list->pointer; i++) {
		backing_store_t *_store = (backing_store_t*)list_get_at(backing_store_list, i);
		if (_store->owner_id == owner_id) {
			list_remove (backing_store_list, i);
			free(_store);
			return;
		}
	}
}


/**
 * create_new_shared_win -- creates a new shared window space
 * @param owner_id -- owner of the shared window space
 */
uint32_t* create_new_shared_win (uint16_t *sh_key, uint16_t owner_id) {
	int cursor_pos = 0;
	uint32_t key = shared_win_key_prefix + owner_id;
	shared_win_key_prefix++;

	for (int i = 0; i < shared_win_space_list->pointer; i++) {
		shared_win_t *sh = (shared_win_t*)list_get_at(shared_win_space_list, i);
		if (sh->free) {
			map_shared_memory(owner_id, (uint64_t)sh->win_info_location,8192);
			sh->owner_id = owner_id;
			sh->free = false;
			return sh->win_info_location;
		}else
			cursor_pos += 8192;
	}

	int id = sys_shmget(key,8192,0);
	void* addr = sys_shmat(id,NULL,0);
	*sh_key = key; 
	shared_win_t* sh = (shared_win_t*)malloc(sizeof(shared_win_t));
	sh->free = false;
	sh->owner_id = owner_id;
	sh->win_info_location = (uint32_t*)addr;
	list_add(shared_win_space_list, sh);
	return sh->win_info_location;
}

/**
 * free_shared_win -- free up a shared window space for future use
 * @param sh -- shared window slot to be freed
 */
void free_shared_win (uint16_t owner_id) {
	shared_win_t *sh;
	for (int i = 0; i < shared_win_space_list->pointer; i++) {
		sh = (shared_win_t*)list_get_at(shared_win_space_list, i);
		if (sh->owner_id == owner_id) 
			break;
	}

	//sys_unmap_sh_mem(sh->owner_id, (uint64_t)sh->win_info_location,8192);
	sh->free = true;
	sh->owner_id = 0;
}

/**
 * cursor_init -- initializes the cursor library
 */
void cursor_init () {
	arrow_cursor = (pri_bmp_image*)malloc(sizeof(pri_bmp_image));
	spin_cursor = (pri_bmp_image*)malloc(sizeof(pri_bmp_image));
	cursor_back = (uint32_t*)malloc(8192);
	valloc(0x0000070000000000);
	valloc(0x0000070000001000);
}



/**
 * load_cursor -- loads a new cursor image to library
 * @param filename -- cursor file path
 * @param bmp -- bmp library to use
 */
void load_cursor (char* filename, uint8_t* addr,pri_bmp_image *bmp) {
	UFILE file;
	int fd = sys_open_file (filename, &file);
	sys_read_file (fd, addr, &file);
	uint8_t* buffer = (uint8_t*)addr;

	bitmap_img* file_header = (bitmap_img*)buffer;
	unsigned int offset = file_header->off_bits;

	bitmap_info *info = (bitmap_info*)(buffer + sizeof(bitmap_img));
	int width = info->biWidth;
	int height = info->biHeight;
	
	int bpp = info->biBitCount;

	void* image_bytes = (void*)(buffer + offset);
	int j=0;
	
    uint8_t *image = (uint8_t*)image_bytes;
	bmp->image_data = image;
	bmp->width = width;
	bmp->height = height;
}


/**
 * mouse_get -- get mouse movement info from kernel
 * @param msg -- the mouse msg pointer to store the
 * retreived data
 */
void mouse_get (mouse_message_t *msg) {
	mouse_message_t *tmsg = (mouse_message_t*)0x400000; //0xFFFFFFFFB0000000;
	if (tmsg->type != 0) {
		memcpy (msg,tmsg,sizeof(mouse_message_t));
	}
	memset ((void*)0x400000, 0, sizeof(mouse_message_t));
}


/**
 * draw_cursor -- draws the loaded cursor 
 * @param canvas -- backing store, where to draw
 * @param bmp -- the bitmap image to draw
 * @param x -- x coordinate
 * @param y -- y coordinate
 */
void draw_cursor (canvas_t *canvas, pri_bmp_image *bmp,unsigned x, unsigned y) {
	int width = bmp->width;
	int height = bmp->height;
	int j = 0;
	uint8_t* image = bmp->image_data;
	for(int i=0; i < height; i++) {
		char* image_row = (char*)image + (height - i - 1) * (width * 4);
		int h = height -1 - i;
		j = 0;
		for (int k = 0; k < width; k++) {
			uint32_t b = image_row[j++] & 0xff;
			uint32_t g = image_row[j++] & 0xff;
			uint32_t r = image_row[j++] & 0xff;
			uint32_t a = image_row[j++] & 0xff;
			uint32_t rgb = ((a<<24) | (r<<16) | (g<<8) | (b));
			if (rgb & 0xFF000000)
				canvas_draw_pixel(canvas,x + k,y +  i,rgb);
		}
	}
}



/**
 * cursor_store_back -- stores the occluded area by cursor
 * @param x -- occluded x
 * @param y -- occluded y
 */
void cursor_store_back (unsigned x, unsigned y) {
	for (int w = 0; w < 24; w++) {
		for (int h = 0; h < 24; h++) {
			cursor_back[h * 24 + w] = canvas_get_pixel(canvas,x+ w,y+ h); 
		}
	}
}



/**
 * cursor_draw_back -- draws the previously occluded area
 * @param x -- occluded x
 * @param y -- occluded y
 */
void cursor_draw_back (unsigned x, unsigned y) {
	for (int w = 0; w < 24; w++) {
		for (int h = 0; h < 24; h++) {
			canvas_draw_pixel(canvas,x+w,y+h,cursor_back[h * 24 + w]);
		}
	}
}

/*
 * pri_wallp_pixel -- draws the pixels from wallpaper buffer
 * to wallpaper backing store
 * @param x -- x coordination to start from
 * @param y -- y coordination to start from
 */
void pri_wallp_pixel (unsigned x, unsigned y, uint32_t color) {
	uint32_t *lfb = (uint32_t*)wallpaper->buffer;      
	lfb[x + y * canvas_get_width(canvas)] = color;
}

/**
 * pri_load_wallpaper -- loads an wallpaper to pri_wallpaper
 * @param filename -- file path of the wallpaper
 */
Image *pri_load_wallpaper (char *filename) {
	wallpaper = (pri_wallpaper_t*)malloc(sizeof(pri_wallpaper_t));
	for (int i = 0; i < (canvas->width * canvas->height * 32) / 4096; i++) 
		valloc(0x0000060000000000 + i * 4096);

	Image *img = LoadImage (filename, (uint8_t*)0x0000060000000000);
	wallpaper->buffer = (uint8_t*)0x0000060000000000;
	wallpaper->img = img;
	/* finally call the jpeg decoder and draw the
	 * image to wallpapers backing store
	 */
	if (img != NULL) {
		CallJpegDecoder(img);
		wallpaper->w = img->width;
		wallpaper->h = img->height;
	}

	return img;
}


/**
 * pri_wallpaper_change -- change the wallpaper 
 * @param wallp -- pointer to the system wallpaper structure
 * @param filename -- path and file name of the new wallpaper
 */
void pri_wallpaper_change (pri_wallpaper_t *wallp,char* filename) {
	UFILE f;
	int fd = sys_open_file (filename, &f);
	
	sys_read_file (fd,wallp->buffer, &f);
	sys_print_text ("F.SIZE -> %d, fd -> %d\n", f.size, fd);
	wallp->img->width = 0;
	wallp->img->height = 0;
	wallp->img->size = f.size;
	sys_print_text ("Calling JPEG Decoder \n");
	CallJpegDecoder(wallp->img);
	
}


/**
 * pri_wallpaper_draw -- draw the wallpaper to backing store
 * @param img -- img to draw 
 */
void pri_wallpaper_draw (Image *img) {
	unsigned x = 0;
	unsigned y = 0;
	if (img != NULL){

		if (img->data == NULL)
			pri_wallpaper_draw(NULL);

		uint8_t* data = img->image;
		uint32_t w = img->width;
		uint32_t h = img->height;
		for (int i = 0; i < h; i++) {
			for (int k = 0; k < w; k++) {
				int j = k + i * w;
				uint8_t r = data[j * 3];        
				uint8_t g = data[j * 3 + 1];        
				uint8_t b = data[j * 3 + 2];       
				//uint8_t a = data[j * 3 + 3];
				uint32_t rgba =  ((r<<16) | (g<<8) | (b)) & 0x00ffffff;  //0xFF000000 | (r << 16) | (g << 8) | b;
				rgba = rgba | 0xff000000;
				pri_wallp_pixel(x + k, y + i,rgba);
				j++;
			}
		}
	} else{
		for (int i = 0; i < canvas->width; i++) {
			for (int j = 0; j < canvas->height; j++) {
				pri_wallp_pixel(0 + i, 0 + j, LIGHTBLACK);
			}
		}
	}

}



/**
 * pri_wallpaper_present -- present the wallpaper to screen
 */
void pri_wallpaper_present () {
	uint32_t* lfb = (uint32_t*)canvas->address;
	uint32_t* wallp = (uint32_t*)wallpaper->buffer;
	/* draw the entire wallpaper */
	for (int i=0; i < wallpaper->w; i++) {
		for (int j=0; j < wallpaper->h; j++){
			uint32_t color_a = wallp[(0 + i) + (0 + j) * canvas_get_width(canvas)];
			lfb[(0 + i) + (0 + j) * canvas_get_width(canvas)] = color_a;
		}
	}
}

/**
 * pri_wallpaper_present_rect -- present the wallpaper to screen in
 * a specific geometry
 * @param x -- x coordinate
 * @param y -- y coordinate
 * @param w -- width of the rect
 * @param h -- height of the rect
 */
void pri_wallpaper_present_rect (int x, int y, int w, int h) {
	uint32_t* lfb = (uint32_t*)canvas->address;
	uint32_t* wallp = (uint32_t*)wallpaper->buffer;

	/* draw the entire wallpaper */
	for (int j=0; j < h; j++){
		fastcpy (canvas->address + (y + j) * canvas->width + x,wallp + (y + j) * canvas->width + x,
					w * 32);	
	}
}


/* initialize the window list */
void window_list_init () {
	window_list = list_init ();
}

/**
 * desktop_component_list_init -- initialize the desktop
 * component list
 */
void desktop_component_list_init () {
	desktop_component_list = list_init();
}


/**
 * pri_add_desktop_component -- adds a desktop component to the 
 * component list 
 * @param id -- process id
 */
void pri_add_desktop_component (uint16_t id) {
	desktop_component_t *component = (desktop_component_t*)malloc(sizeof(desktop_component_t));
	component->process_id = id;
	list_add(desktop_component_list, component);
}

/**
 * pri_notify_win_create -- notifies desktop components about 
 * new window
 */
void pri_notify_win_create (char *win_title, uint16_t win_id) {
	pri_event_t e;
	memset(&e, 0, sizeof(pri_event_t));
	e.type = DAISY_NEW_WINDOW_INFO;
	e.dword = win_id;
	strcpy(e.char_values, win_title);
	e.to_id = 3;
	e.from_id = get_current_pid();
	ioquery(pri_loop_fd, PRI_LOOP_PUT_EVENT, &e);

}

/**
 * pri_notify_win_destroyed -- notifies desktop components about 
 * window being destroyed
 */
void pri_notify_win_destroyed (uint16_t win_id) {
	pri_event_t e;
	memset(&e, 0, sizeof(pri_event_t));
	e.type = DAISY_NOTIFY_WIN_REMOVE;
	e.dword = win_id;
	e.to_id = 3;
	e.from_id = get_current_pid();
	ioquery(pri_loop_fd, PRI_LOOP_PUT_EVENT, &e);
	sys_print_text ("Notified \r\n");
}


/**
 * pri_send_quit -- notify the window owner to quit
 */
void pri_send_quit (uint16_t owner_id) {
	pri_event_t e;
	memset(&e, 0, sizeof(pri_event_t));
	e.type = DAISY_WINDOW_CLOSED;
	e.to_id = owner_id;
	e.from_id = get_current_pid();
	ioquery(pri_loop_fd, PRI_LOOP_PUT_EVENT, &e);
}

/*
 * pri_remove_desktop_component -- removes a desktop component
 * from component list
 * @param id -- process id to remove
 */
void pri_remove_desktop_component (uint16_t id) {
	for (int i = 0; i < desktop_component_list->pointer; i++) {
		desktop_component_t *component = (desktop_component_t*)list_get_at(desktop_component_list, i);
		if (component)
			list_remove(desktop_component_list, i);
	}
}

/**
 * window_create -- create a new window and allocate its resources
 * @param x -- x coordinate
 * @param y -- y coordinate
 * @param w -- width of the window
 * @param h -- height of the window
 * @param attr -- window attributes
 * @param owner_id -- owner thread id of the window
 * @return win -- newly created window pointer
 */
pri_window_t * window_create (int x, int y, int w, int h, uint8_t attr, uint16_t owner_id, char* title) {
	uint16_t sh_key = 0;
	uint16_t back_store_key = 0;
	pri_window_t *win = (pri_window_t*)malloc(sizeof(pri_window_t));
	win->attribute = attr;
	win->backing_store = (uint32_t*)create_new_backing_store(owner_id, w*h*4, &back_store_key);
	win->owner_id = owner_id;
	win->pri_win_info_loc = create_new_shared_win(&sh_key,owner_id);
	win->sh_win_key = sh_key;
	win->backing_store_key = back_store_key;
	win->title = title;
	win->anim = false;
	win->anim_x = 0;
	win->anim_y = 0;
	pri_win_info_t *info = (pri_win_info_t*)win->pri_win_info_loc;
	info->x = x;
	info->y = y;
	info->width = w;
	info->height = h;
	info->dirty = 0;
	info->rect_count = 0;
	list_add (window_list, win);
	return win;
}


/**
 * window_remove -- remove a window from window list
 * and frees its resources
 * @param win -- window to be freed
 */
void window_remove (pri_window_t *win) {
	int i = 0;
	for (i = 0; i < window_list->pointer; i++) {
		pri_window_t *_win = (pri_window_t*)list_get_at (window_list, i);
		if (_win == win)
			break;
	}

	free_backing_store(win->owner_id);
	free_shared_win (win->owner_id);
	list_remove(window_list, i);
	free(win);
}


/**
 * pri_win_find_by_id -- find a window by its owner id
 * @param owner_id -- owner id to search for
 */
pri_window_t * pri_win_find_by_id (uint16_t owner_id) {
	for (int i = 0; i < window_list->pointer; i++) {
		pri_window_t *win = (pri_window_t*)list_get_at(window_list, i);
		if (win != NULL && win->owner_id == owner_id)
			return win;
	}

	return NULL;
}

/**
 * pri_window_make_top -- brings a window to top
 * @param win -- window to make top
 */
void pri_window_make_top (pri_window_t *win) {
	int i = 0;
	for (i = 0; i < window_list->pointer; i++) {
		pri_window_t* _win = (pri_window_t*)list_get_at(window_list, i);
		if (_win == win)
			break;
	}

	list_remove (window_list,i);
	list_add(window_list, win);
}

/**
 * pri_window_set_focused -- make window focused
 * @param win -- window to make focused
 */
void pri_window_set_focused (pri_window_t * win, bool notify) {
	/* check if it is already focused */
	if (focused_win == win)
		return;

	/* here we need to notify old focused window
	   that focus has been changed to focus lost */
	focused_win = win;

	/* Notify the dock about focus change event */
	if (notify) {
		pri_event_t e;
		e.type = DAISY_NOTIFY_WIN_FOCUS_CHANGED;
		e.dword = focused_win->owner_id;
		e.to_id = 3;
		e.from_id = get_current_pid();
		ioquery(pri_loop_fd, PRI_LOOP_PUT_EVENT, &e);
	}

	/*
	 * here notify the new window that focus is gained
	 */
	//! now let us bring the focus window in top
	pri_window_make_top(win);
}


/**
 * pri_window_move -- moves a window to a new location
 * @param win -- window to move
 * @param x -- new x location relative to device coord
 * @param y -- new y location relative to device coord
 */
void pri_window_move (pri_window_t *win, int x, int y) {
	if (win->attribute & PRI_WIN_STATIC)
		return;

	if (focused_win != win) 
		pri_window_set_focused(win, true);

	pri_win_info_t* info = (pri_win_info_t*)win->pri_win_info_loc;

	int wx = info->x;
	int wy = info->y;
	int ww = info->width;
	int wh = info->height;

	if (info->x + info->width >= canvas->width)
		ww = canvas->width - info->x;

	if (info->y + info->height >= canvas->height){
		wh = canvas->height - info->y;
	}

	pri_rect_t *r = pri_create_rect(wx, wy,ww, wh);
	pri_wallp_add_dirty_clip(r);
	info->x = x;
	info->y = y;
	_window_update_all_ = true;
}

/**
 * pri_window_resize -- resize a window to new dimension
 * @param win -- window to resize
 * @param n_w -- new width of the window
 * @param n_h -- new height of the window
 */
void pri_window_resize (pri_window_t *win, int n_w,int n_h) {
	pri_win_info_t* info = (pri_win_info_t*)win->pri_win_info_loc;
	pri_rect_t *r = pri_create_rect(info->x, info->y, info->width + 100, info->height + 100);
	pri_wallp_add_dirty_clip(r);
	info->width = n_w;
	info->height = n_h;
	// (--BUGGY---)
}


/**
 * compose_frame -- draw everything in an optimized waythat needs 
 * to be displayed on the screen
 */
void compose_frame () {
	/* draw previously stored occluded area by cursor */
	cursor_draw_back(prev_x, prev_y);
	pri_add_clip(prev_x, prev_y, 24,24);
	
	bool animation_on = false;
	int window_opacity = 255;

	//!--Here goes the drawing of all wallpaper dirty areas
	for (int i = 0; i < pri_wallp_get_dirty_count(); i++) {
		pri_rect_t *r = pri_wallp_get_dirty_rect();
		pri_wallpaper_present_rect(r->x, r->y, r->w, r->h);
		pri_add_clip(r->x, r->y, r->w, r->h);
		free(r);
	}

	//----Here goes composing of all window buffers ---//
	for (int i = 0; i < window_list->pointer; i++) {
		pri_window_t *win = (pri_window_t*)list_get_at(window_list, i);
		pri_win_info_t *info = (pri_win_info_t*)win->pri_win_info_loc;

		if (win != NULL && win->anim)
			_window_update_all_ = true;
		/*  only update those portion that has been modified for smoothness */
		if (win != NULL && info->rect_count > 0) {
			//for (int k = 0; k < info->rect_count; k++) {
			//	int wid = info->rect[k].w;
			//	int he = info->rect[k].h;
			//	int rx = info->rect[k].x;
			//	int ry = info->rect[k].y;

			//	if (rx < 0)
			//		rx = 0;
			//	if (ry < 0)
			//		ry = 0;
			//	
			//	if (info->rect[k].x + info->rect[k].w >= canvas->width)
			//		wid  = canvas->width - info->rect[k].x;

			//	if (info->rect[k].y + info->rect[k].h>= canvas->height){
			//		info->rect[k].y = canvas->height - info->rect[k].y;
			//	}

			//	if (info->x + info->rect[k].x + info->rect[k].w > canvas->width)
			//		wid  = canvas->width - (info->x + info->rect[k].x);

			//	for (int i = 0; i < he; i++)  {
			//		fastcpy (canvas->address + (info->y + ry + i) * canvas->width + (info->x + rx),win->backing_store + (ry + i) * canvas->width + rx, 
			//				wid * 4);
			//	}

			//	/* finally add a clip area */
			//	pri_add_clip(info->x + rx,info->y + ry, wid,he);
			//	info->rect_count = 0;
			//	_window_update_all_ = false;
			//}
			info->rect_count = 0;
			_window_update_all_ = true;
		}

		/* update entire window */
		if (win != NULL && _window_update_all_) {
			int winx = 0;
			int winy = 0;

			winx = info->x;
			winy = info->y;

			int wid = info->width;
			int he = info->height;
			int bkstore_xoff = 0;
			int bkstore_yoff = 0;
			/* calculate desktop bounds */
			if (info->x < 0) {
				info->x = 5;
				winx = info->x;
			}

			if (info->y < 0) {
				info->y = 5;
				winy = info->y;
			}



			if (info->x + info->width >= canvas->width)
				wid  = canvas->width - info->x;

			if (info->y + info->height >= canvas->height){
				he = canvas->height - info->y;
			}

			for (int i = 0; i < he; i++)  {
				fastcpy (canvas->address + (winy + i) * canvas->width + winx,win->backing_store + (0 + i) * 4 + 0,
				wid * 4);	
			}
			/* add the clip region */
			pri_add_clip (winx, winy, wid, he);
		}
	}
	
	/* now store the new occluded area by cursor */
	cursor_store_back(mouse_x, mouse_y);
	/* draw the new cursor on the backing store */
	draw_cursor (canvas, arrow_cursor, mouse_x, mouse_y); 
	pri_add_clip(mouse_x, mouse_y, 24, 24);


	/** finally blit every dirty area to framebuffer **/
	pri_dirty_rect_screen_update(canvas);
	
	if (_window_update_all_ && ! animation_on)
		_window_update_all_ = false;

	/*store current mouse coord as prev coord */
	prev_x = mouse_x;
	prev_y = mouse_y;
}

/**
 * pri_win_send_mouse_event -- sends mouse event to focused
 * @param x -- mouse_x
 * @param y -- mouse_y
 * @param button -- mouse button click
 */
void pri_win_send_mouse_event (pri_window_t* win,int x, int y, int button) {
	pri_event_t e;
	memset(&e, 0, sizeof(pri_event_t));
	e.type = DAISY_CURSOR_MOVED;
	e.dword = x;
	e.dword2 = y;
	e.dword3 = button;
	e.to_id = win->owner_id;
	ioquery(pri_loop_fd,PRI_LOOP_PUT_EVENT, &e);
}

/**
 * pri_win_send_key_event -- sends key event to focused
 * @param code -- keyboard code
 */
void pri_win_send_key_event (pri_window_t* win,int code) {
	pri_event_t e;
	memset(&e, 0, sizeof(pri_event_t));
	e.type = DAISY_KEY_EVENT;
	e.dword = code;
	e.to_id = win->owner_id;
	ioquery(pri_loop_fd,PRI_LOOP_PUT_EVENT, &e);
}

/**
 * pri_win_check_draggable -- checks if a window is draggable or not
 * @param x -- mouse x coordinate
 * @param y -- mouse y coordinate
 * @param button -- button state
 */
void pri_win_check_draggable (int x, int y, int button) {

	/** loop through the window list **/
	for (int i = window_list->pointer - 1; i >= 0; i--) {
		pri_window_t* win = (pri_window_t*)list_get_at(window_list, i);
		pri_win_info_t *info = (pri_win_info_t*)win->pri_win_info_loc;

		/** Bound check the mouse cursor **/
		if (!(x >= info->x && x < (info->x + info->width) &&
			y >= info->y && y < (info->y + info->height))) 
			continue;

		/**  check if button is depressed or not **/
		if (button && !last_mouse_button) {
			//! Only a limited portion is available for dragging purpose
			if (y >= info->y && y < (info->y + 23)) {  
				pri_window_set_focused(win, true);
				dragg_win = win;
				dragg_win->drag_x = x - info->x;
				dragg_win->drag_y = y - info->y;
		        break;
			}

			/*RESIZEING of WINDOW is disabled for now*/
			/*if (y >= (info->y + info->height - 10) && y < (info->y + info->height + 10)) {
				resz_win = win;
				resz_win->resz_h = x - info->width;
				resz_win->resz_v = y - info->height;	
				break;
			}*/
		}
	}
	 /**  check if a draggable window is present or not **/
	if (dragg_win) {
		_window_broadcast_mouse_ = false;
		pri_win_info_t *wininfo = (pri_win_info_t*)dragg_win->pri_win_info_loc;
		int posx = x - dragg_win->drag_x;
		int posy = y - dragg_win->drag_y;
		pri_window_move(dragg_win,posx, posy);
	}

	/** check if a resizable window is present or not,
	    RESIZEING of WINDOW is disabled for now **/
	/*if (resz_win) {
		int n_width = x - resz_win->resz_h;
		int n_height = y - resz_win->resz_v;
		pri_window_resize(resz_win, n_width, n_height);
	}*/

	/** button released **/
	if (!button)  {
		dragg_win = NULL;
		resz_win = NULL;
		_window_broadcast_mouse_ = true;
	}
	
	/* store the last mouse_button */
	last_mouse_button = button;
}


/*
 * main -- the main entry point of priwm
 */
XE_EXTERN int XeMain (int argc, char* argv[]) {
	
	int svga_fd = sys_open_file ("/dev/fb", NULL);
	
	uint32_t s_width = ioquery(svga_fd,SCREEN_GETWIDTH,NULL);
	uint32_t s_height = ioquery(svga_fd, SCREEN_GETHEIGHT, NULL);

	sys_print_text ("XeMain PRIWM \n");
	/*
	 * create the main backing store
	 */
	canvas = create_canvas (s_width,s_height);
	sys_print_text ("Created canvas -> %x \n", canvas);

	int w = canvas_get_width(canvas);
	int h = canvas_get_height(canvas);

	//! load cursor library
	cursor_init ();
	sys_print_text ("Reading cursor files \n");
	load_cursor ("/cursor.bmp",(uint8_t*)0x0000070000000000, arrow_cursor);
	load_cursor ("/spin.bmp", (uint8_t*)0x0000070000001000, spin_cursor);
	Image* wallp = pri_load_wallpaper ("/winne1.jpg");
	pri_wallpaper_draw(NULL);

	/* initialize window list */
	window_list_init();
	backing_store_list = list_init();
	shared_win_space_list = list_init();

	/*
	 * initialize desktop component list
	 */
	desktop_component_list_init();

	/*
	 * clear the backing store to light black
	 * and display the priwm version name
	 */
	acrylic_draw_rect_filled (canvas, 0,0,s_width, s_height, LIGHTBLACK);
	pri_wallpaper_present();

	acrylic_initialize_font();
	acrylic_font_set_size(64);
	acrylic_font_draw_string(canvas, "Hello! Xeneva", 450,450,32, WHITE);


	canvas_screen_update(canvas, 0, 0, s_width, s_height);

    cursor_store_back(0, 0);
    
	pri_loop_fd = sys_open_file ("/dev/pri_loop",NULL);
	uint32_t frame_tick;
	uint32_t diff_tick;
	pri_event_t event;
	mouse_message_t mouse;
	message_t key_msg;

	int mouse_fd = sys_open_file("/dev/mouse", NULL);
	ioquery(mouse_fd, MOUSE_REGISTER_WM,NULL);

	while (1) {
		mouse_get (&mouse);

		pri_wm_get_message (&event);
		message_receive(&key_msg);
		//frame_tick = sys_get_system_tick();
		//1 draw everything
		compose_frame();

		/**
		 * mouse movement
		 */
		if (mouse.type == MOUSE_MOVE) {
			mouse_x = mouse.dword;
			mouse_y = mouse.dword2;
			int button = mouse.dword4;
			int button2 = mouse.dword4;
			pri_win_check_draggable(mouse_x, mouse_y,button); 
			/* send the mouse event to focused window */
			if (focused_win && _window_broadcast_mouse_) {
				pri_win_send_mouse_event(focused_win, mouse_x,mouse_y, button2);
			}

			memset(&mouse, 0, sizeof(mouse_message_t));
		}

		if(key_msg.type == KEY_PRESSED) {
			if (focused_win) {
				pri_win_send_key_event(focused_win, key_msg.dword);
			}
			
			if (key_msg.dword == KEY_W) {
				pri_wallpaper_change(wallpaper,"/madhu.jpg");
				pri_wallpaper_draw(wallpaper->img);
				pri_wallpaper_present();
				 cursor_store_back(mouse_x, mouse_y);
				canvas_screen_update(canvas,0,0,s_width,s_height);
				_window_update_all_ = true;
			}

			if (key_msg.dword == KEY_I) {
				pri_wallpaper_change(wallpaper,"/winne1.jpg");
				pri_wallpaper_draw(wallpaper->img);
				pri_wallpaper_present();
				 cursor_store_back(mouse_x, mouse_y);
				canvas_screen_update(canvas,0,0,s_width,s_height);
				_window_update_all_ = true;
			}

			if (key_msg.dword == KEY_M) {
				uint64_t mb = sys_get_used_ram();
				sys_print_text ("USED Ram -> %d MB \r\n", mb / 1024 / 1024);
			}

			if (key_msg.dword == KEY_A) {
				create_process("/ptest.exe", "ptest");
			}
			memset(&key_msg, 0, sizeof(message_t));
		}

               		
		/* PRI_WIN_CREATE -- handles window 
		 * creation message */
		if (event.type == PRI_WIN_CREATE) {
			/* create the new window */
			int x = event.dword;
			int y = event.dword2;
			int w = event.dword3;
			int h = event.dword4;
			uint8_t attribute = event.dword5;
			char *title = (char*)malloc(100) ;
			memset(title,0,100);

			strcpy(title,event.char_values);

			pri_window_t *win = window_create (x,y,w,h,attribute,event.from_id, title);
			pri_window_set_focused(win, false);


			/* Send the new gift message to client */
			pri_event_t e;
			e.type = DAISY_GIFT_CANVAS;
			e.dword = win->sh_win_key; //sh_win_key
			e.dword2 = win->backing_store_key;   //shared win key  win->pri_win_info_loc;
			e.to_id = event.from_id;
			ioquery(pri_loop_fd,PRI_LOOP_PUT_EVENT, &e);

			memset (&event, 0, sizeof(pri_event_t));
		}

		/**
		 * PRI_CHANGE_WALLPAPER -- changes wallpaper
		 */
		if (event.type == PRI_CHANGE_WALLPAPER) {
			char* filename = (char*)malloc(100);
			memset(filename, 0, 100);
			strcpy(filename,event.char_values);
			pri_wallpaper_change(wallpaper,filename);
			pri_wallpaper_draw(wallpaper->img);
			pri_wallpaper_present();
			cursor_store_back(mouse_x, mouse_y);
			canvas_screen_update(canvas,0,0,s_width,s_height);
			_window_update_all_ = true;

			free(filename);

			memset(&event, 0, sizeof(pri_event_t));
		}


		/* PRI_WIN_READY -- this messages are from clients
		 * telling the window manager that it's ready to 
		 * show up on the screen */
		if (event.type == PRI_WIN_READY) {
			pri_window_t *win = NULL;
			for (int i = 0; i < window_list->pointer; i++) {
				win = (pri_window_t*)list_get_at(window_list,i);
				if (win->owner_id == event.from_id) {
					break;
				}
			}

			_window_update_all_ = true;

			pri_notify_win_create(win->title, win->owner_id);
			memset (&event, 0, sizeof(pri_event_t));
		}

		/**
		 *	PRI_WIN_MOVE -- moves a window to new
		 *  location
		 */
		if (event.type == PRI_WIN_MOVE) {
			int x = event.dword;
			int y = event.dword2;
			pri_window_t *win = pri_win_find_by_id(event.from_id);
			if (win != NULL) {
				pri_window_move (win, x, y);
			}
			memset(&event, 0, sizeof(pri_event_t));
		}


		if (event.type == PRI_WIN_MARK_FOR_CLOSE) {
			int x = 0;
			int y = 0;
			int w = 0;
			int h = 0;
			uint16_t owner_id = event.from_id;
			//pri_notify_win_destroyed(owner_id);
			for (int i = 0; i < window_list->pointer; i++) {
				pri_window_t *win = (pri_window_t*)list_get_at(window_list, i);
				if (win->owner_id == event.from_id)  {
					pri_win_info_t *info = (pri_win_info_t*)win->pri_win_info_loc;
					x = info->x;
					y = info->y;
					w = info->width;
					h = info->height;

					sys_shm_unlink(win->sh_win_key);
					sys_shm_unlink(win->backing_store_key);
				
					list_remove(window_list, i);
					free(win);
					
					break;
				}
			}
           
			pri_send_quit(owner_id);
			focused_win = NULL;

			if (x != 0 && y != 0 && w != 0 && h != 0) 
				pri_wallp_add_dirty_clip(pri_create_rect(x,y,w,h));

			memset(&event, 0, sizeof(pri_event_t));
		}



		//diff_tick = sys_get_system_tick();
		//int delta = diff_tick - frame_tick;
		//if (delta < 1000/60) {
			//! it will sleep for 16 ms
			//sys_sleep (1000/60 - delta);
		//}
		sys_sleep(16);
	}
}