/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  sysmouse.cpp -- Mouse System Calls for acceleration
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ========================================================
 */

#include <drivers\svga\backdoor_def.h>
#include <drivers\svga\vmmouse_defs.h>
#include <drivers\svga\vmsvga.h>
#include <pmmngr.h>
#include <string.h>
#include <stdio.h>
#include <drivers\svga\rgba_arrow.h>

#ifdef HW_SVGA

void sys_set_mouse_data () {
	x64_cli();
	/*
	SVGAFifoCmdDefineAlphaCursor  cursor;
	cursor.id = 0;
	cursor.hotspotX = 1;
	cursor.hotspotY = 1;
	cursor.width = 36;
	cursor.height = 51;



	void *fifo_data = pmmngr_alloc();

	svga_write_reg (SVGA_REG_BITS_PER_PIXEL, 8);
	svga_begin_define_alpha_cursor (&cursor, &fifo_data);
	memcpy (fifo_data,(void*)mouse_data, sizeof(mouse_data));
	svga_fifo_commit_all();*/

	//svga_move_cursor (true,0, 0, SVGA_ID_INVALID);
}

bool sys_get_mouse_pack (vm_mouse_packet *pack) {
	x64_cli();
	return vmbackdoor_mouse_get_packet (pack);
}


void sys_move_cursor (uint32_t visible, uint32_t x,uint32_t y) {
	x64_cli ();
	svga_move_cursor (visible, x, y, SVGA_ID_INVALID);
}

#endif


