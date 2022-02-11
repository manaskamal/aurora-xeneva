///!!  Copyright (C) Manas Kamal Choudhury 2021
///!!
///!!  pipe.cpp -- Pipes
///!!
///!!  /PROJECT - Aurora's Xeneva
///!!  /AUTHOR  - Manas Kamal Choudhury
///!!
///!!  needs completion
///!!==============================================

#include <ipc\pipe.h>
#include <arch\x86_64\mmngr\kheap.h>
#include <arch\x86_64\thread.h>
#include <stdio.h>

int pipe_count = 0;


pipe_t* pipe_create () {
	unsigned char *p = (unsigned char*)pmmngr_alloc();  //Main Buffer
	circ_buf_t *circ = circ_buf_init((unsigned char*)p,4096);
	pipe_t *pipe = (pipe_t*)pmmngr_alloc();
	pipe->buf = circ;
	pipe->readers = 0;
	pipe->writers = 0;
	return pipe;
}


void pipe_read (vfs_node_t *file, uint64_t* buffer,uint32_t length) {
	pipe_t *p = (pipe_t*)file->device;
	for (int i = 0; i < length; i++)
		circular_buf_get (p->buf,(uint8_t*)&buffer[i]);
}


void pipe_write (vfs_node_t *file, uint8_t* buffer, uint32_t length) {
	pipe_t *p = (pipe_t*)file->device;
	for (int i = 0; i < length; i++) {
		circular_buf_put(p->buf, buffer[i]);
	}
}



void allocate_pipe (int *fd, char* name) {

	///!=========================================
	///!  Allocate new node for read
	///!=========================================
	pipe_t *p = pipe_create();
	char p_value[2];
	sztoa(pipe_count, p_value,10);

	char pipe_name[10];
	if (name)
		strcpy(pipe_name, name);
	else {
		strcpy(pipe_name, "pipe");
		strcpy (pipe_name + strlen(pipe_name)-1, p_value);
	}
	

	char path_name[10];
	strcpy(path_name, "/dev/");
	strcpy (path_name + strlen(path_name)-1, pipe_name);

	
	vfs_node_t *readn = (vfs_node_t*)malloc(sizeof(vfs_node_t));
	strcpy(readn->filename, pipe_name);
	readn->size = 0;
	readn->eof = 0;
	readn->pos = 0;
	readn->current = 0;
	readn->flags = FS_FLAG_GENERAL;
	readn->status = 0;
	readn->open = 0;
	readn->device = p;
	readn->read = pipe_read;
	readn->write = pipe_write;
	readn->read_blk = 0;
	readn->ioquery = 0;
	vfs_mount (path_name, readn);

	thread_t * t = get_current_thread();
	t->fd[t->fd_current] = readn;
	*fd = t->fd_current;
	t->fd_current++;
	
	pipe_count++;
}





