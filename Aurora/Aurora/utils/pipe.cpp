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
#include <mm.h>
#include <vfs.h>

pipe_t *root_pipe;

void pipe_write () {
}

void pipe_read (FILE* pfile, unsigned char * buffer, int length) {
}

void init_pipe () {
	root_pipe = (pipe_t*)malloc(sizeof(pipe_t));
	char* buf = (char*)pmmngr_alloc();
	root_pipe->buf= circ_buf_init(buf,4096);
	root_pipe->readers = 0;
	root_pipe->writers = 0;
}