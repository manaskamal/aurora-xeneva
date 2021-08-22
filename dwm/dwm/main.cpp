/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  dwm.cpp -- Desktop Window Manager v1.0
 *
 *  /PROJECT - DWM {Desktop Window Manager}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *===================================================
 */

#include <stdtypes.h>
#include <string.h>
#include <sys.h>
#include <dwm.h>
#include <allocator.h>
#include <bufmngr.h>
#include <dwmmsg.h>
#include <wm.h>
#include <window.h>
#include <imgbmp.h>
#include <color.h>
#include <imgpng24.h>
#include <imgjpg.h>
#include "jpeg_decoder.h"
#include <dwm.h>
#include <menubar.h>
#include <stack.h>

/* =======================================================
 *  CPP STANDARD
 * ======================================================= */
 
extern "C" int _fltused = 1;
void* __cdecl ::operator new(size_t size) {
	return dalloc(size);
}

void* __cdecl operator new[] (size_t size) {
	return dalloc(size);
}


static int win_coord_x = 400;
static int win_coord_y = 400;


/******************************************************
 **THE CURSOR
 ******************************************************
 */
#define CA 0xFF000000
#define CB 0xFFFFFFFF
#define CD 0x00000000
unsigned int mouse_img_i[11*18] = {
    CA, CD, CD, CD, CD, CD, CD, CD, CD, CD, CD,
    CA, CA, CD, CD, CD, CD, CD, CD, CD, CD, CD,
    CA, CB, CA, CD, CD, CD, CD, CD, CD, CD, CD,
    CA, CB, CB, CA, CD, CD, CD, CD, CD, CD, CD,
    CA, CB, CB, CB, CA, CD, CD ,CD, CD, CD, CD,
    CA, CB, CB, CB, CB, CA, CD, CD, CD, CD, CD,
    CA, CB, CB, CB, CB, CB, CA, CD, CD, CD, CD,
    CA, CB, CB, CB, CB, CB, CB, CA, CD, CD, CD,
    CA, CB, CB, CB, CB, CB, CB, CB, CA, CD, CD,
    CA, CB, CB, CB, CB, CB, CB, CB, CB, CA, CD,
    CA, CB, CB, CB, CB, CB, CB, CB, CB, CB, CA,
    CA, CA, CA, CA, CB, CB, CB, CA, CA, CA, CA,
    CD, CD, CD, CD, CA, CB, CB, CA, CD, CD, CD,
    CD, CD, CD, CD, CA, CB, CB, CA, CD, CD, CD,
    CD, CD, CD, CD, CD, CA, CB, CB, CA, CD, CD,
    CD, CD, CD, CD, CD, CA, CB, CB, CA, CD, CD,
    CD, CD, CD, CD, CD, CD, CA, CB, CA, CD, CD,
    CD, CD, CD, CD, CD, CD, CD, CA, CA, CD, CD 
};

static unsigned int mouse_x = 0;
static unsigned int mouse_y = 0;
static unsigned int mouse_x_old = 0;
static unsigned int mouse_y_old = 0;


/* ========================================================================
 *  Main Entry Point
 * ========================================================================
 */
void main () {
	int width = get_screen_width();
	int height = get_screen_height();

	

	initialize_screen ();

	//! Map the DWM Internal Buffer
	for (int i = 0; i < width * height * 32 / 4096; i++)
		valloc (0x0000600000000000 + i * 4096);

	for (int i = 0; i < width * height *32 / 4096; i++)
		valloc (0x0000500000000000 + i * 4096);


	//!Initialize DWM internal allocator
	initialize_dwm_allocator (256);

	//!initialize the shared buffer manager
	initialize_buffer_manager();

	//!initialize internal window manager
	wm_initialize ();

	//!register font class
	register_font_library();

	//!initialize dirty list
	initialize_dirty_list();

	//!initialize system menubar
	initialize_system_menubar();

	//! Internal Buffer Pointer
	uint32_t* buffer = (uint32_t*)0x0000600000000000;



	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
			draw_pixel3(0 + i, 0 + j, CHARCOAL);/*0x5B7492*/

	message_t msg;
	rect_t update_rect;
	update_rect.x = 0;
	update_rect.y = 0;
	update_rect.w = width;
	update_rect.h = height;

	FILE f;
	sys_open_file (&f, "nature.jpg");
	unsigned char* buffer_i = (unsigned char*)0x0000500000000000;
	sys_read_file (&f,buffer_i,f.size);

	Jpeg::Decoder *decoder = new Jpeg::Decoder(buffer_i, f.size, dalloc, dfree);
	if (decoder->GetResult() != Jpeg::Decoder::OK) {
		print_text ("JPEG:Decoder Error\n");
	}
	
	uint8_t* data = decoder->GetImage();
	for (int i = 0; i < decoder->GetHeight(); i++) {
		for (int k = 0; k < decoder->GetWidth(); k++) {
			int j = k + i * decoder->GetWidth();
			uint8_t r = data[j * 3];        //data[i * 3];
			uint8_t g = data[j * 3 + 1];        //data[i * 3 + 1];
			uint8_t b = data[j * 3 + 2];       //data[i * 3 + 2];
			uint32_t rgb =  ((r<<16) | (g<<8) | (b)) & 0x00ffffff;  //0xFF000000 | (r << 16) | (g << 8) | b;
			rgb = rgb | 0xff000000;
			draw_pixel3(0 + k, 0 + i,rgb);
			j++;
		}
	}

	//!Draw the wallpaper
	copy_to_screen ((uint32_t*)0x0000500000000000,&update_rect);
	copy_to_screen2 ((uint32_t*)0x0000500000000000,&update_rect);
	sys_fb_update ();


	rect_t cur_rect;
	cur_rect.w = 11;
	cur_rect.h = 18;

	//add_dirty_rect(&update_rect);
	uint32_t* lfb = (uint32_t*)0x0000600000000000;           //)0xFFFFF00000000000; 
	dwm_message_t dwm_msg;
	while(1) {
		message_receive (&msg);
		dwm_dispatch_message (&dwm_msg);
	
		if (dwm_msg.type == DWM_MOUSE_MOVE) {
			mouse_x = dwm_msg.dword;
			mouse_y = dwm_msg.dword2;
			

			/* Handle Left Button Click  event */
			//if (dwm_msg.dword4 == 1) {
			wm_handle_mouse_event (mouse_x, mouse_y, dwm_msg.dword4, dwm_msg.dword5, dwm_msg.dword6);
			//dwm_msg.dword4 = 0;
			//}
	
			/* Draw dirty pixels for mouse update */
			//copy_to_screen ((uint32_t*)0x0000600000000000, &cur_rect);
			/* Store Dirty Pixels for mouse update */
			//sys_unblock_id(3);
			memset (&dwm_msg,0,sizeof(dwm_message_t));
		}

		//***********************************************************
		//! Handle DWM_CREATE_WIN Message
		//!**********************************************************
		if (msg.type == DWM_CREATE_WIN) {
			win_coord_x -= 40;
			win_coord_y -= 40;

			if (win_coord_x == 0 && win_coord_y == 0) {
				win_coord_x = 500;
				win_coord_y = 500;
			}
			int type = msg.dword5;
			if (type == WIN_TYPE_ROOT) {
				win_coord_x = 0;
				win_coord_y = 0;
			}
			if (msg.dword5 & 16) {
				msg.dword8 = win_coord_x;
				msg.dword9 = win_coord_y;
			}
			window_t *win = create_window (msg.dword3,msg.dword8,msg.dword9,msg.dword6,msg.dword7, type);
			message_t msg1;
			msg1.type = 1;
			msg1.dword4 = win->pid;
			msg1.dword10 = win->buffer;
			msg1.dword5 = win->coord.x;
			msg1.dword6 = win->coord.y;
			dwmmsg_send (&msg1);
			//enable_update(true);
			wm_paint_required(true);
			memset (&msg, 0, sizeof (message_t));
		}

		if (msg.type == DWM_KEY_EVENT) {
			//Process Key Events
			window_t *win = wm_get_focused_window();
			if (win != NULL) {
			message_t msg1;
			msg1.type = 15;
			msg1.dword4 = win->pid;
			msg1.dword5 = msg.dword;  //scancode
			dwmmsg_send (&msg1);
			sys_unblock_id (win->pid);
			}
			memset (&msg, 0, sizeof (message_t));
		}

		if (msg.type == DWM_CREATE_MENU) {
			int id = msg.dword3;
			window_t* win = wm_find_window_by_id(id);
			menu_t *menu = (menu_t*)dalloc(sizeof(menu_t));
			int length = strlen(msg.buffer);
			menu->title = (char*)dalloc(length);
			//print_text ("Msg Buffer message %s\n", msg.buffe
			for (int i = 0; i < length; i++)
				menu->title[i] = msg.buffer[i];
			sys_menubar_add_menu (win, menu);
			memset (&msg, 0, sizeof(message_t));
		}

		//! Update a dirty area
		if (msg.type == DWM_UPDATE) {
			rect_t *r = (rect_t*)dalloc(sizeof(rect_t));
			r->x = msg.dword5;
			r->y = msg.dword6;
			r->w = msg.dword7;
			r->h = msg.dword8;
			//stack_push_rect(r);
			copy_to_screen2 (msg.dword10,r);
			copy_to_screen((uint32_t*)0x0000600000000000, r);
			dfree(r);
			memset(&msg, 0, sizeof(message_t));
		}

		if (msg.type == DWM_CLOSE)  {
			window_t *win = wm_find_window_by_id(msg.dword4);
			if (win != NULL)
				wm_remove_window(win);
			memset(&msg, 0, sizeof(message_t));
			copy_to_screen2 ((uint32_t*)0x0000500000000000, &win->coord);
			copy_to_screen ((uint32_t*)0x0000600000000000, &win->coord);
			//wm_paint_required(true);
		}


		//prepare_screen(&update_rect);
		
		wm_paint_windows(&update_rect);
		//refresh_screen();
		sys_fb_move_cursor (mouse_x, mouse_y);
		sys_fb_update();
	
		//!Render at 1000 Frames / Second -> 1ms
		sys_sleep (1);
		//sys_fb_update();
        //!Store mouse old position
     	
	}
}