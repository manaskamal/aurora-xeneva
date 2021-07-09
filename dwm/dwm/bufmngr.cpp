/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  bufmngr.cpp -- Shared Buffer Manager
 *
 *  /PROJECT - DWM { Desktop Window Manager }
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ===============================================
 */

#include <bufmngr.h>
#include <sys.h>

static uint32_t cursor = 0;
#define BUF_START  0x0000100000000000

void initialize_buffer_manager () {
	//int width = get_screen_width();
	//int height = get_screen_height();
	/*for (int i = 0; i < width * height * 32 / 4096; i++)
		valloc (BUF_START + i * 4096);*/
}

uint32_t *request_buffer (uint16_t dest_pid) {
	uint32_t pos = cursor;
	uint32_t size = get_screen_width() * get_screen_height() * 32;
	map_shared_memory(dest_pid,BUF_START + pos,size);
	cursor += size;
	return (uint32_t*)(BUF_START + pos);
}


