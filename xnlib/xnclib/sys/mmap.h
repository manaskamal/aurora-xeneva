/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  mmap.h -- Memory Mapping functions callbacks
 *
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ==============================================
 */

#ifndef __MMAP_H__
#define __MMAP_H__

#include <stdint.h>


//! Direct callback to the syscall wrapper
//! local and global mapping are same as MAP_PRIVATE | MAP_SHARED
//! in unix systems
#define MAP_LOCAL    1    //Local gives access to only mapping process
#define MAP_GLOBAL   2    //global gives access to every processes in the proc list

//! Security Attributes
#define ATTRIBUTE_READ  3
#define ATTRIBUTE_WRITE 4
#define ATTRIBUTE_USER  5
extern "C" void* mmap (uint64_t address, uint32_t length, uint8_t attribute);
extern "C" void munmap (void* addr, uint32_t length);
extern "C" void valloc (unsigned long long pos);


#endif