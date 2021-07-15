/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  sysserv.h -- System Call Services
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ===========================================
 */

#ifndef __SYSSERV_H__
#define __SYSSERV_H__

#include <stdio.h>
#include <screen.h>
#include <ipc\message.h>
#include <callback.h>
#include <ipc\dwm_ipc.h>


//! List of available services in Aurora
static void* _syscalls[] = {
	printf,            //0
	wait,              //1
	create__sys_process, //2
	get_screen_width,    //3
	get_screen_height, ///4
	valloc,            ///5
	message_send,      //6
	message_receive,   //7
	map_shared_memory, //8
	get_thread_id, //9
	dwm_put_message, //10
	dwm_dispatch_message, //11
	sys_get_fb_mem, //12
	sys_fb_update, //13
	sys_set_mouse_data, //14
	sys_get_mouse_pack, //15
	sys_move_cursor, //16
	sys_unblock_id, //17
	create_uthread, //18
	sys_open_file, //19
	sys_read_file, //20
	get_screen_scanline, //21
	sys_get_used_ram, //22
	sys_get_free_ram, //23
	sys_sleep, //24
	0
};


#endif