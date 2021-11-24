///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  pipe.h -- Pipe based IPC
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!=============================================

#ifndef __PIPE_H__
#define __PIPE_H__

#include <utils\circ_buf.h>
#include <fs\vfs.h>

typedef struct _pipe_ {
	circ_buf_t *buf;
	uint32_t readers;
	uint32_t writers;
}pipe_t;

extern pipe_t* pipe_create ();
extern void allocate_pipe (int *fd, char* name);
extern void pipe_write (vfs_node_t *file, uint8_t* buffer, uint32_t length);
extern void pipe_read (vfs_node_t *file, uint8_t* buffer,uint32_t length);
#endif