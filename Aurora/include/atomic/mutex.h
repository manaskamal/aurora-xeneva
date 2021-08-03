/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  mutex.h -- Mutual Exclusion Lock for atomic operations
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *==========================================================
 */

#ifndef __MUTEX_H__
#define __MUTEX_H__

#include <hal.h>

/* Architecture specific */
#ifdef ARCH_X64
#include <arch\x86_64\thread.h>
#endif


//! Mutex structure
typedef struct {
	thread_t* owner_thread;
	uint16_t block_thread_num;
	uint32_t  blocks;
	int block_thread_id[50];
}mutex_t;

//!Create a mutex 
extern mutex_t* create_mutex ();
extern void mutex_lock (mutex_t* obj);
extern void mutex_unlock (mutex_t* obj);
extern void mutex_destroy (mutex_t* obj);
#endif