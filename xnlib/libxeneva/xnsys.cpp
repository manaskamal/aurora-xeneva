/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  xnsys.cpp -- Xeneva System functions
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * =============================================
 */

#include <xnsys.h>
#include <mm.h>
#include <gui\drawer.h>
#include <gui\font.h>

static uint16_t id = 0;


extern "C" int _fltused = 1;
void* __cdecl ::operator new(size_t size) {
	return malloc(size);
}

void* __cdecl operator new[] (size_t size) {
	return malloc(size);
}


void message_poll (message_t *msg) {

	uint64_t* data = (uint64_t*)0xFFFFD00000000000;
	
	if (data[11] != 0){
		if (data[3] == id) {
			msg->dword = data[0];
			msg->dword2 = data[1];
			msg->dword3 = data[2];
			msg->dword4 = data[3];
			msg->dword5 = data[4]; 
			msg->dword6 = data[5];
			msg->dword7 = data[6];
			msg->dword8 = data[7];
			msg->dword9 = data[8];
			msg->dword10 = (uint32_t*)data[9]; 
			msg->quad = data[10];
			msg->type = data[11];
			memset (data, 0, 4096);
		}
	}
}

void register_xn_application (int type,uint32_t x, uint32_t y, uint32_t gui_width, uint32_t gui_height) {
	id = get_current_pid ();
	initialize_allocator (0x10);	
	for (int i = 0; i < get_screen_width()*get_screen_height()*32/4096; i++) 
		valloc (0x0000600000000000 + i * 4096);
	drawer_register(type,x, y, gui_width, gui_height);
	register_font_lib();


}
