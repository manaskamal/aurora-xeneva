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
#include <fs\vfs.h>
#include <arch\x86_64\mmngr\kheap.h>
#include <stream.h>
#include <pe.h>
#include <ipc\signals.h>

typedef void (*main_thread) (void*);

///! Future use!! Current vfs system is not sufficient

//!Process structure
typedef struct _process_ {
	uint32_t pid_t;
	char *name;
	main_thread entry_point;
	thread_t * thread_data_pointer; //a pointer to the thread data structure
	size_t   image_size;
	uint64_t* cr3;
	uint64_t image_base;
	uint64_t stack;
	uint64_t mmap_sz;
	struct _process_ *next;
	struct _process_ *prev;
	struct _process_ *parent;
}process_t;

/**
 * create_user_stack -- creates a 2mb user mode threads stack
 * @param cr3 -- the destination top level paging structure, where to create
 * the stack
 */
extern uint64_t *create_user_stack (uint64_t* cr3);

/**
 * create_inc_stack -- not used for now
 */
extern uint64_t* create_inc_stack (uint64_t* cr3);

/**
 * create_process -- creates a thread with executable image entry point
 * address
 * @param filename -- executable file path
 * @param procname -- processname
 * @return -- created thread id
 */
extern int AuCreateProcess(const char* filename, char* procname);

/**
 * kill_process -- kills the current process
 */
extern void kill_process ();

/**
 * kill_process_by_id -- kills a process by its id
 * @param id -- the id of the thread to be killed
 */
extern void kill_process_by_id (uint16_t id);

/**
 * get_num_process -- returns the number of process
 * @return -- number of process
 */
extern uint32_t get_num_process ();


/** 
 * get_current_process -- returns the current active process
 * @return -- current active process address
 */
extern process_t * get_current_process ();

/**
 * find_process_by_id -- Finds a process by its pid
 * @param pid -- process id
 */
extern process_t *find_process_by_id (uint32_t pid);

/**
 * find_process_by_thread -- Finds a process by its thread address
 * @param thread -- thread address
 */
extern process_t *find_process_by_thread (thread_t *thread);

extern void process_list_initialize ();
#endif