/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2022, Manas Kamal Choudhury
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * /PROJECT - Aurora's Xeneva v1.0
 * @init.cpp -- Main kernel entry 
 *
 **/

#ifndef __VIRTUAL_FILE_SYS_H__
#define __VIRTUAL_FILE_SYS_H__

#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <utils\lnklist.h>
#include <aurora.h>


/*
 * @example-- to create a empty directory 
 * vfs_file_t *file = (vfs_file_t*)kmalloc(sizeof(vfs_file_t));
 * file->flags = FS_FLAG_DIR;
 * vfs_node_t *node = vfs_mknode();
 * vfs_mkdir("/dirname", file, node);
 *
 * node is required because, every vfs_file with flag FS_FLAG_DIR
 * requires another link to a node, containing the list entries
 * of all the file and sub directories, that's why we link the file
 * structure with the node
 *
 * @example -- to remove a directory/file
 * vfs_remove_file("/dirname/filename");
 * if you also want to remove 'dirname'...
 * vfs_remove_file("/dirname");
 *
 * @example -- to mount or to create a file
 * vfs_file_t *file = (vfs_file_t*)kmalloc(sizeof(vfs_file_t));
 * file->flags = FS_FLAG_GEN;
 * vfs_mount("/yourdirname/filename", file);
 * @note -- you cannot mount it to '/' root dir because already
 * root file system needs that space
 */


#define  FS_FLAG_DIRECTORY  (1<<1)
#define  FS_FLAG_GENERAL    (1<<2)
#define  FS_FLAG_DEVICE     (1<<3)
#define  FS_FLAG_DELETED    0x3
#define  FS_FLAG_INVALID    FS_FLAG_DELETED

#define FS_STATUS_FOUND 0x4
struct _vfs_node_;


typedef _vfs_node_* (*open_callback) (_vfs_node_ *node, char* path);
typedef size_t (*read_callback) (_vfs_node_ *file, uint64_t* buffer,uint32_t length);
typedef size_t (*read_block_callback) (_vfs_node_ *file, uint64_t* buffer);
typedef void (*write_callback) (_vfs_node_ *file, uint64_t* buffer, uint32_t length);
typedef int (*ioquery_callback) (_vfs_node_ *file, int code, void *arg);

//! The File Node -- everything is file
typedef struct _vfs_node_ {
	char filename[32];
	uint32_t  size;
	uint8_t  eof;
	uint32_t  pos;
	uint32_t  current;  //inode -- in unix term
	uint8_t  flags; 
	uint8_t  status;
	void* device;
	open_callback open;
	read_callback read;
	write_callback write;
	read_block_callback read_blk;
	ioquery_callback ioquery;
}vfs_node_t;

//! Entry structure
typedef struct _vfs_entry_ {
	vfs_node_t *node;
	list_t *childs;
}vfs_entry;

//! User mode file structure
typedef struct _file_ {
	uint32_t  id;
	uint32_t  size;
	uint32_t  eof;
	uint32_t  pos;
	uint32_t  start_cluster;
	uint32_t  flags; 
	uint32_t  status;
}FILE;

extern void AuVFSInit ();
extern vfs_node_t* vfs_finddir (char *path);
/*
 * vfs_mkdir -- creates a virtual directory
 * @param path -- path to use
 * @param dir -- directory file
 * @param dir_node -- dir node
 */
AU_EXTERN AU_EXPORT void vfs_mkdir (char* path, vfs_node_t* dir, vfs_entry* dir_node);
AU_EXTERN AU_EXPORT vfs_entry * vfs_mkentry();
AU_EXTERN AU_EXPORT void vfs_mount (char *path, vfs_node_t *node, vfs_entry* ent);
extern void vfs_lsdir (char* path);
AU_EXTERN AU_EXPORT vfs_node_t* openfs (vfs_node_t *node, char* path);
AU_EXTERN AU_EXPORT size_t readfs (vfs_node_t *node, vfs_node_t *file, uint64_t* buffer, uint32_t length);
AU_EXTERN AU_EXPORT void writefs (vfs_node_t *node, vfs_node_t *file, uint64_t *buffer, uint32_t length);
AU_EXTERN AU_EXPORT size_t readfs_block (vfs_node_t* node, vfs_node_t *file,  uint64_t *buffer);
AU_EXTERN AU_EXPORT int  vfs_ioquery (vfs_node_t *node, int code, void* arg);
#endif