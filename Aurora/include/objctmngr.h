/**
 *  Copyright (C) Manas Kamal Choudhury
 *
 *  objctmngr.h -- Everything is object in Xeneva {"Everything is file in unix"}
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ====================================================
 */

#ifndef __OBJCT_MNGR_H__
#define __OBJCT_MNGR_H__

#include <stdint.h>
#include <hal.h>

/*
 * Object Manager manages everything like an object
 * like opened files, process, device, null objects, ..etc
 *
 * Object Manager is also responsible for handling page 
 * swapping for specific process objects
 *
 * memory_map function also depends on objects
 * for an instance, if object handle is defined is
 * not null in memory_map, while memory_unmap every
 * data of that specific object handle will be commited
 * to disk, this will help in swapping pages
 *
 * TODO: implementation, future
 *
 */

//!incomplete object structure
/*typedef struct _object_ {
	void (*obj_write) (unsigned char* buffer, size_t length);
	void (*obj_read) (unsigned char* buffer);
	void (*iodev_call) (int req_code, void* arg);
}object;*/

#endif