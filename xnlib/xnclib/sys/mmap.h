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
#include <sys\_xeneva.h>

//! Direct callback to the syscall wrapper
//! local and global mapping are same as MAP_PRIVATE | MAP_SHARED
//! in unix systems
#define MAP_LOCAL    1    //Local gives access to only mapping process
#define MAP_GLOBAL   2    //global gives access to every processes in the proc list

//! Security Attributes
#define ATTRIBUTE_READ  3
#define ATTRIBUTE_WRITE 4
#define ATTRIBUTE_USER  5
extern "C" XE_EXPORT void* sys_mmap (void* address, size_t length, int protect, int flags, int filedesc, uint64_t offset);
extern "C" XE_EXPORT void sys_munmap (void* addr, uint32_t length);
extern "C" XE_EXPORT void valloc (unsigned long long pos);
extern "C" XE_EXPORT void vfree (unsigned long long pos);
extern "C" XE_EXPORT void map_shared_memory (uint16_t dest_id, uint64_t pos, size_t size);
extern "C" XE_EXPORT void sys_copy_mem(uint16_t dest_id, uint64_t pos, size_t size);
extern "C" XE_EXPORT void* sys_proc_heap_brk(uint64_t pages);

/**
 * au_mmap -- memory map
 * @param address -- starting address
 * @param length -- length of the mappings
 * @param protect -- protection flags
 * @param flags -- memory map flags
 * @param filedesc -- file descriptor to map
 * @param offset -- offset from where to begin, it should be multiple of PAGE_SIZE
 */
XE_EXTERN XE_EXPORT void* mmap (void* address, size_t length, int protect, int flags, int filedesc, uint64_t offset);
#endif