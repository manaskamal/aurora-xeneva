/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  sys.h -- System Functions
 *
 *  /PROJECT - DWM { Desktop Window Manager }
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *================================================
 */

#ifndef __SYS_H__
#define __SYS_H__

#include <stdint.h>
#include <string.h>


//! Message format
typedef struct _message_ {
	uint32_t dword;
	uint32_t dword2;
	uint32_t dword3;
	uint32_t dword4;
	uint32_t dword5;
	uint32_t dword6;
	uint32_t dword7;
	uint32_t dword8;
	uint32_t dword9;
	uint32_t *dword10;
	uint64_t quad;
	uint16_t type;
	char buffer[50];
}message_t;




typedef struct _dwm_message_ {
	uint16_t type;
	uint32_t dword;
	uint32_t dword2;
	uint32_t dword3;
	uint32_t dword4;
	uint32_t dword5;
	uint32_t dword6;
}dwm_message_t;

typedef struct _mouse_packet_ {
	uint32_t flags;
	uint32_t buttons;
	int x, y, z;
}mouse_packet;

typedef struct _file_ {
	char filename[32];
	uint32_t  id;
	uint32_t  size;
	uint32_t  eof;
	uint32_t  pos;
	uint32_t  start_cluster;
	uint32_t  flags; 
	uint32_t  status;
}FILE;


#define APPLICATION_TYPE_ROOT 14
#define APPLICATION_TYPE_NORMAL 15

extern "C" void print_text(const char* text, ...);
extern "C" void sched_wait ();
extern "C" void create_process (const char * name);
extern "C" void mutex_test ();
extern "C" uint32_t get_screen_width();
extern "C" uint32_t get_screen_height();
extern "C" void message_send (uint16_t dest_id, message_t *msg);
extern "C" void message_receive (message_t *msg);
extern "C" void valloc (unsigned long long pos);
extern "C" void map_shared_memory (uint16_t dest_id, uint64_t pos, size_t size);
extern "C" uint16_t get_current_pid ();
extern "C" void dwm_put_message (dwm_message_t *msg);
extern "C" void dwm_dispatch_message (dwm_message_t *msg);
extern "C" uint32_t* sys_get_fb_mem ();
extern "C" void sys_fb_update ();
extern "C" void sys_set_mouse_data ();
extern "C" bool sys_get_mouse_pack (mouse_packet *pack);
extern "C" void sys_move_cursor (uint32_t visible, uint32_t x,uint32_t y);
extern "C" void sys_open_file (FILE *file, const char* filename);
extern "C" void sys_read_file (FILE *file, unsigned char* buffer, int length);
extern "C" uint16_t sys_get_scanline ();
extern "C" uint64_t sys_get_used_ram ();
extern "C" uint64_t sys_get_free_ram ();
extern "C" void sys_sleep (uint64_t ms);
extern void message_poll (message_t *msg);
extern void register_xn_application (int app_type,uint32_t x, uint32_t y,uint32_t gui_width, uint32_t gui_height);
extern "C" void sys_exit();
#endif