/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  proc.h -- Process Creation 
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *===============================================
 */

#ifndef __PROC_H__
#define __PROC_H__

#include <arch\x86_64\thread.h>
#include <stdio.h>
#include <arch\x86_64\cpu.h>
#include <vfs.h>
#include <mm.h>
#include <pe.h>


typedef void (*main_thread) (void*);

//!Process structure
typedef struct _process_ {
	char *name;
	main_thread entry_point;
	//uint64_t* mailbox;
	thread_t * thread_data_pointer; //a pointer to the thread data structure
	size_t   image_size;
	uint64_t* cr3;
	uint64_t image_base;
	uint64_t stack;
	struct _process_ *next;
	struct _process_ *prev;
}process_t;

extern uint64_t *create_user_stack (uint64_t* cr3);
extern void create_process(const char* filename, char* procname, uint8_t priority);
extern void kill_process ();
#endif