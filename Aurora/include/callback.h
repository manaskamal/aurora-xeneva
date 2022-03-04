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
#include <drivers\rtc.h>

//!This is an interface layer between system service callbacks
//! wait sys
extern void wait();
extern int create__sys_process (const char* name,char* procnm);
extern void valloc (uint64_t pos);
extern void vfree (uint64_t pos);
extern void map_shared_memory (uint16_t dest_id,uint64_t pos, size_t size);
extern uint16_t get_thread_id ();
extern uint32_t* sys_get_fb_mem ();
extern void sys_fb_update ();
extern void sys_set_mouse_data ();
extern bool sys_get_mouse_pack (vm_mouse_packet *pack);
extern void sys_move_cursor (uint32_t visible, uint32_t x,uint32_t y);
extern void sys_unblock_id (uint16_t id);
extern void create_uthread (void (*entry) (void*), char* name);
extern int  sys_open_file (char* filename, FILE *f);
extern void sys_read_file (int fd, uint8_t* buffer, FILE *f);
extern void sys_write_file (int fd, unsigned char* buffer, FILE *ufile);
extern uint64_t sys_get_used_ram ();
extern uint64_t sys_get_free_ram ();
extern void sys_sleep (uint64_t ms);
extern void sys_exit();
extern void sys_fb_move_cursor (uint32_t x, uint32_t y);
extern uint32_t fork ();
extern void exec (const char* filename, uint32_t pid);
extern void ioquery (int devid, int code, void* arg);
extern void sys_get_current_time (sys_time *time);
extern uint32_t sys_get_system_tick ();
extern void sys_kill (int pid, int signo);
extern void sys_set_signal (int signo, sig_handler handler);
extern void unmap_shared_memory (uint16_t dest_id, uint64_t pos, size_t size);
extern void sys_attach_ttype (int id);
extern void copy_memory (uint16_t dest_id, uint64_t pos, size_t size);
#endif
