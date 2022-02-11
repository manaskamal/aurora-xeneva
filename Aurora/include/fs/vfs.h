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


#define  FS_FLAG_DIRECTORY  0x1
#define  FS_FLAG_GENERAL   0x2
#define  FS_FLAG_DELETED    0x3
#define  FS_FLAG_INVALID    FS_FLAG_DELETED

#define FS_STATUS_FOUND 0x4
struct _vfs_node_;


typedef _vfs_node_ (*open_callback) (_vfs_node_ *node, char* path);
typedef void (*read_callback) (_vfs_node_ *file, uint64_t* buffer,uint32_t length);
typedef void (*read_block_callback) (_vfs_node_ *file, uint64_t* buffer);
typedef void (*write_callback) (_vfs_node_ *file, uint8_t* buffer, uint32_t length);
typedef int (*ioquery_callback) (_vfs_node_ *file, int code, void *arg);

//! The File Node -- everything is file
typedef struct _vfs_node_ {
	char filename[32];
	uint32_t  size;
	uint32_t  eof;
	uint32_t  pos;
	uint32_t  current;  //inode -- in unix term
	uint32_t  flags; 
	uint32_t  status;
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
	_vfs_entry_ *next;
	_vfs_entry_ *prev;
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

extern void vfs_init ();
extern vfs_node_t* vfs_finddir (char *path);
extern void vfs_mount (char *path, vfs_node_t *node);
extern vfs_node_t openfs (vfs_node_t *node, char* path);
extern void readfs (vfs_node_t *node, vfs_node_t *file, uint64_t* buffer, uint32_t length);
extern void writefs (vfs_node_t *node, vfs_node_t *file, uint8_t *buffer, uint32_t length);
extern void readfs_block (vfs_node_t* node, vfs_node_t *file,  uint64_t *buffer);
extern int  vfs_ioquery (vfs_node_t *node, int code, void* arg);
#endif