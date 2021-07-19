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
uint32_t color[1024];
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

	//! Internal Buffer Pointer
	uint32_t* buffer = (uint32_t*)0x0000600000000000;



	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
			draw_pixel3(0 + i, 0 + j, LIGHTBLACK);/*0x5B7492*/

	//*Store every thing
	for (int w = 0; w < 11; w++) {
		for (int h = 0; h < 18; h++) {
			color[h * 20 + w] = get_pixel32bit(mouse_x_old+ w,mouse_y_old+ h);
		}
	}

	FILE file;
	sys_open_file (&file, "cover.jpg");

	for (int i = 0; i < 3076096/4096; i++){
		valloc (0xFFFFD00000200000 + i * 4096);
	}
	unsigned char *buffer_i = (unsigned char*)0xFFFFD00000200000;
	sys_read_file (&file,buffer_i, file.size);


	Jpeg::Decoder *decoder = new Jpeg::Decoder(buffer_i, file.size, dalloc, dfree);
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
		   // wallpaper_buffer[i] = 0xFF000000 | (r << 16) | (g << 8) | b;
			draw_pixel3 (0 + k, 0 + i,rgb);
			j++;
		}
	}

	message_t msg;
	rect_t update_rect;
	update_rect.x = 0;
	update_rect.y = 0;
	update_rect.w = width;
	update_rect.h = height;
	uint32_t* lfb = (uint32_t*)0x0000600000000000;
	dwm_message_t dwm_msg;
	while(1) {
		message_receive (&msg);
		dwm_dispatch_message (&dwm_msg);
	
		if (dwm_msg.type == DWM_MOUSE_MOVE) {
			mouse_x = dwm_msg.dword;
			mouse_y = dwm_msg.dword2;
			

			/* Handle Left Button Click  event */
			if (dwm_msg.dword4 == 1) {
				wm_handle_mouse_event (mouse_x, mouse_y, dwm_msg.dword4, dwm_msg.dword5, dwm_msg.dword6);
				dwm_msg.dword4 = 0;
			}
	
			/* Draw dirty pixels for mouse update */
			for (int w = 0; w < 11; w++) 
				for (int h = 0; h < 18; h++) 
					draw_pixel(mouse_x_old+w,mouse_y_old+h,color[h * 20+ w]);

			/* Store Dirty Pixels for mouse update */
			for (int w = 0; w < 11; w++) 
				for (int h = 0; h < 18; h++) 
					color[h * 20 + w] = get_pixel32bit(mouse_x+ w,mouse_y+ h);

			mouse_x_old = mouse_x;
		    mouse_y_old = mouse_y;

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

			window_t *win = create_window (msg.dword3,win_coord_x,win_coord_y,500,500);
			message_t msg1;
			msg1.type = 1;
			msg1.dword4 = win->pid;
			msg1.dword10 = win->buffer;
			msg1.dword5 = win_coord_x;
			msg1.dword6 = win_coord_y;
			dwmmsg_send (&msg1);
			memset (&msg, 0, sizeof (message_t));
		}

		if (msg.type == DWM_KEY_EVENT) {
			memset (&msg, 0, sizeof (message_t));
		}

		copy_to_screen2 ((uint32_t*)0x0000500000000000,&update_rect);
		/*********************************************************
		! If no event, simply composite everything and
		! prepare the screen for user
	    copy_to_screen2((uint32_t*)0x0000100000000000, &up_r);*/
		wm_paint_windows();
		/**********************************************************
		**        Draw The Cursor
		**********************************************************/
		
		for (int x = 0; x < 11; x++)
			for (int y=0; y < 18; y++)
				if (mouse_img_i[y* 11 + x] & 0xFF000000)
					lfb[(y + mouse_y) * width + (x + mouse_x)] = mouse_img_i[y * 11 + x];
		
		copy_to_screen((uint32_t*)0x0000600000000000,&update_rect);
		//!Store mouse old position
     	sys_fb_update();

		//!Render at 60 Frames / Second
		sys_sleep (16);
	}
}