/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  map.h -- Memory Mapping functions for device, file and free memory
 *           mapping
 *
 *  /PROJECT - Aurora Xeneva 
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * =======================================================================
 */

#ifndef __MAP_H__
#define __MAP_H__

#include <stdint.h>
#include <arch\x86_64\mmngr\paging.h>

//! local and global mapping are same as MAP_PRIVATE | MAP_SHARED
//! in unix systems
#define MAP_LOCAL    1    //Local gives access to only mapping process
#define MAP_GLOBAL   2    //global gives access to every processes in the proc list

//! Security Attributes
#define ATTRIBUTE_READ  3
#define ATTRIBUTE_WRITE 4
#define ATTRIBUTE_USER  5

//! Given an address do memory mapping
extern void *map_memory (uint64_t address, uint32_t length, uint8_t attribute);
//! unmap a given memory region
extern void unmap_memory (void* addr, uint32_t length);
#endif