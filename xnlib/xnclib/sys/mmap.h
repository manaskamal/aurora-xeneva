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
extern "C" void* sys_mmap (void* address, size_t length, void* params);
extern "C" void sys_munmap (void* addr, uint32_t length);
extern "C" void valloc (unsigned long long pos);
extern "C" void vfree (unsigned long long pos);
extern "C" void map_shared_memory (uint16_t dest_id, uint64_t pos, size_t size);
extern "C" void sys_unmap_sh_mem (uint16_t dest_id, uint64_t pos, size_t size);
extern "C" void sys_copy_mem(uint16_t dest_id, uint64_t pos, size_t size);

/**
 * au_mmap -- memory map
 * @param address -- starting address
 * @param length -- length of the mappings
 * @param protect -- protection flags
 * @param flags -- memory map flags
 * @param filedesc -- file descriptor to map
 * @param offset -- offset from where to begin, it should be multiple of PAGE_SIZE
 */
extern void* mmap (void* address, size_t length, int protect, int flags, int filedesc, uint64_t offset);
#endif