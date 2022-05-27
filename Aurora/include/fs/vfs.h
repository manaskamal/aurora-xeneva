///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  vfs.h -- Virtual File System
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!==============================================


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


#define  FS_FLAG_DIRECTORY  0x1
#define  FS_FLAG_GENERAL   0x2
#define  FS_FLAG_DELETED    0x3
#define  FS_FLAG_INVALID    FS_FLAG_DELETED

#define FS_STATUS_FOUND 0x4
struct _vfs_node_;


typedef _vfs_node_* (*open_callback) (_vfs_node_ *node, char* path);
typedef void (*read_callback) (_vfs_node_ *file, uint64_t* buffer,uint32_t length);
typedef void (*read_block_callback) (_vfs_node_ *file, uint64_t* buffer);
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
AU_EXTERN AU_EXPORT void readfs (vfs_node_t *node, vfs_node_t *file, uint64_t* buffer, uint32_t length);
AU_EXTERN AU_EXPORT void writefs (vfs_node_t *node, vfs_node_t *file, uint64_t *buffer, uint32_t length);
AU_EXTERN AU_EXPORT void readfs_block (vfs_node_t* node, vfs_node_t *file,  uint64_t *buffer);
AU_EXTERN AU_EXPORT int  vfs_ioquery (vfs_node_t *node, int code, void* arg);
#endif