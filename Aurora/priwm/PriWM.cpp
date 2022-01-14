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
 * @priwm.h -- priyanshi's window manager header
 *
 **/

#include "priwm.h"
#include "list.h"

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

/* backing store & shared win start address */
#define BACKING_STORE_START   0x0000100000000000
#define SHARED_WIN_START      0x00000A0000000000

/* global variables */
canvas_t* canvas;
pri_bmp_image *arrow_cursor;
pri_bmp_image *spin_cursor;
uint32_t* cursor_back;

/* mouse coordinations */
uint32_t mouse_x, mouse_y;
uint32_t prev_x = 0, prev_y = 0;


/* data structures */
list_t *window_list;
list_t *backing_store_list;
list_t *shared_win_space_list;



/**
 * create_new_backing_store -- creates new backing store
 * for server and client to share
 * @param owner_id -- owner id to serve the backing store
 * @param size -- size of the backing store
 * @return -- return the new backing store
 */
void* create_new_backing_store (uint16_t owner_id, int size) {
	uint32_t* addr = (uint32_t*)BACKING_STORE_START;
	uint32_t cursor = 0;

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
	map_shared_memory (owner_id, (uint64_t)addr, size);
	backing_store_t *new_back_store = (backing_store_t*)malloc(sizeof(backing_store_t));
	new_back_store->addr = addr;
	new_back_store->size = size;
	new_back_store->free = false;
	new_back_store->owner_id = owner_id;
	list_add (backing_store_list, new_back_store);
	return addr;
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

	sys_unmap_sh_mem (_store->owner_id,(uint64_t)_store->addr,_store->size);
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
uint32_t* create_new_shared_win (uint16_t owner_id) {
	int cursor_pos = 0;
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

	uint32_t *addr = (uint32_t)SHARED_WIN_START;
	addr += cursor_pos;
	shared_win_t* sh = (shared_win_t*)malloc(sizeof(shared_win_t));
	sh->free = false;
	sh->owner_id = owner_id;
	sh->win_info_location = addr;
	list_add(shared_win_space_list, sh);
	return addr;
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

	sys_unmap_sh_mem(sh->owner_id, (uint64_t)sh->win_info_location,8192);
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
void load_cursor (char* filename, unsigned char* addr,pri_bmp_image *bmp) {
	UFILE file;
	int fd = sys_open_file (filename, &file);

	unsigned char* buffer = (unsigned char*)addr;
	sys_read_file (fd, buffer, &file);

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
	mouse_message_t *tmsg = (mouse_message_t*)0xFFFFFFFFB0000000;
	if (tmsg->type != 0) {
		memcpy (msg,tmsg,sizeof(mouse_message_t));
	}
	memset ((void*)0xFFFFFFFFB0000000, 0, sizeof(mouse_message_t));
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
			canvas_draw_pixel(canvas,x+w,y+h,cursor_back[h * 24+ w]);
		}
	}

	//! flash the content to the framebuffer
	canvas_screen_update(canvas, x, y, 24, 24);
}

/* initialize the window list */
void window_list_init () {
	window_list = list_init ();
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
pri_window_t * window_create (int x, int y, int w, int h, uint8_t attr, uint16_t owner_id) {
	pri_window_t *win = (pri_window_t*)malloc(sizeof(pri_window_t));
	win->attribute = attr;
	win->backing_store = (uint32_t*)create_new_backing_store(owner_id, w*h*4);
	win->owner_id = owner_id;
	win->pri_win_info_loc = create_new_shared_win(owner_id);
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
 * compose_frame -- draw everything in an optimized waythat needs 
 * to be displayed on the screen
 */
void compose_frame () {
	/* draw previously stored occluded area by cursor */
	cursor_draw_back(prev_x, prev_y);
	/* now store the new occluded area by cursor */
	cursor_store_back(mouse_x, mouse_y);

	//----Here goes composing of all window buffers ---//


	/* draw the new cursor on the backing store */
	draw_cursor (canvas, arrow_cursor, mouse_x, mouse_y); 
	/* finally blit the cursor to framebuffer from backing store */
	canvas_screen_update(canvas, mouse_x, mouse_y, 24,24);
	/*store current mouse coord as prev coord */
	prev_x = mouse_x;
	prev_y = mouse_y;
}



/*
 * main -- the main entry point of priwm
 */
int main (int argc, char* argv[]) {
	int svga_fd = sys_open_file ("/dev/fb", NULL);
	
	uint32_t s_width = ioquery(svga_fd,SCREEN_GETWIDTH,NULL);
	uint32_t s_height = ioquery(svga_fd, SCREEN_GETHEIGHT, NULL);
	
	/*
	 * create the main backing store
	 */
	canvas = create_canvas (s_width,s_height);
	int w = canvas_get_width(canvas);
	int h = canvas_get_height(canvas);

	//! load cursor library
	cursor_init ();
	load_cursor ("/cursor.bmp",(unsigned char*)0x0000070000000000, arrow_cursor);
	load_cursor ("/spin.bmp", (unsigned char*)0x0000070000001000, spin_cursor);
	
	/* initialize window list */
	window_list_init();
	backing_store_list = list_init();
	shared_win_space_list = list_init();
	/*
	 * initialize font 
	 */
	acrylic_initialize_font();

	/*
	 * clear the backing store to light black
	 * and display the priwm version name
	 */
	acrylic_draw_rect_filled (canvas, 0,0,s_width, s_height, LIGHTBLACK);
	acrylic_font_set_size (64);
	int length = acrylic_font_get_length("Priyanshi Compz");
	int height = acrylic_font_get_height("Priyanshi Compz");
	acrylic_font_draw_string (canvas, "Priyanshi Compz",s_width / 2 - length / 2,s_height/ 2 - height / 2,64,SILVER);
	canvas_screen_update(canvas, 0, 0, s_width, s_height);
    cursor_store_back(0, 0);


	uint32_t frame_tick;
	uint32_t diff_tick;
	mouse_message_t mouse;
	while (1) {
		mouse_get (&mouse);

        frame_tick = sys_get_system_tick();

		/**
		 * mouse movement
		 */
		if (mouse.type == MOUSE_MOVE) {
			mouse_x = mouse.dword;
			mouse_y = mouse.dword2;
			
			memset(&mouse, 0, sizeof(mouse_message_t));
		}

		//1 draw everything
		compose_frame();


		diff_tick = sys_get_system_tick();
		int delta = diff_tick - frame_tick;
		if (delta < 1000/60) {
			//! it will sleep for 16 ms
			sys_sleep (1000/60 - delta);
		}
	}
}