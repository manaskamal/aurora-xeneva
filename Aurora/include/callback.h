/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  callback.h -- System Services Callback wrapper
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 */

#ifndef __CALLBACK_H__
#define __CALLBACK_H__

#include <stdint.h>
#include <string.h>
#include <drivers\vmmouse.h>
#include <vfs.h>

//!This is an interface layer between system service callbacks
//! wait sys
extern void wait();
extern void create__sys_process (const char* name);
extern void valloc (uint64_t pos);
extern void map_shared_memory (uint16_t dest_id,uint64_t pos, size_t size);
extern uint16_t get_thread_id ();
extern uint32_t* sys_get_fb_mem ();
extern void sys_fb_update ();
extern void sys_set_mouse_data ();
extern bool sys_get_mouse_pack (vm_mouse_packet *pack);
extern void sys_move_cursor (uint32_t visible, uint32_t x,uint32_t y);
extern void sys_unblock_id (uint16_t id);
extern void create_uthread (void (*entry) (void*));
extern void  sys_open_file (FILE *file, const char* filename);
extern void sys_read_file (FILE *file, unsigned char* buffer, int length);
extern uint64_t sys_get_used_ram ();
extern uint64_t sys_get_free_ram ();
extern void sys_sleep (uint64_t ms);
extern void sys_exit();
extern void sys_fb_move_cursor (uint32_t x, uint32_t y);
extern uint32_t fork ();
extern void exec (const char* filename, uint32_t pid);
#endif
