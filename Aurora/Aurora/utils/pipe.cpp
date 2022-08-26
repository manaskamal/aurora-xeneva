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
 * @pipe.cpp -- Pipes IPC
 *
 **/

#include <ipc\pipe.h>
#include <arch\x86_64\mmngr\kheap.h>
#include <arch\x86_64\thread.h>
#include <stdio.h>


#define MAX_PIPE_BUFFER_SZ   1024

/*
 * AuCreatePipe -- Create a pipe buffer
 */
pipe_t* AuCreatePipe () {
	unsigned char *p = (unsigned char*)malloc(MAX_PIPE_BUFFER_SZ);  //Main Buffer
	circ_buf_t *circ = circ_buf_init((unsigned char*)p,MAX_PIPE_BUFFER_SZ);
	pipe_t *pipe = (pipe_t*)malloc(sizeof(pipe_t));
	pipe->buf = circ;
	pipe->readers = 0;
	pipe->writers = 0;
	return pipe;
}


size_t pipe_read (vfs_node_t *file, uint64_t* buffer,uint32_t length) {
	pipe_t *p = (pipe_t*)file->device;
	for (int i = 0; i < length; i++)
		circular_buf_get (p->buf,(uint8_t*)&buffer[i]);

	return 1;
}


void pipe_write (vfs_node_t *file, uint64_t* buffer, uint32_t length) {
	pipe_t *p = (pipe_t*)file->device;
	for (int i = 0; i < length; i++) {
		circular_buf_put(p->buf, buffer[i]);
	}
}

/*
 * pipe_close -- closes a pipe and frees its node
 * @param file -- file node
 */
int pipe_close (vfs_node_t *file) {
	if (file->device)
		free(file->device);

	free(file);
	return 0;
}


/*
 * AuAllocAnonPipe -- Creates anonymous pipe
 * @param fd[2] -- area where two file descriptor
 * get stored, one for read end and other for
 * write end
 */
void AuAllocAnonPipe (int fd[2]) {

	pipe_t *p = AuCreatePipe();
	
	vfs_node_t *readn = (vfs_node_t*)malloc(sizeof(vfs_node_t));
	strcpy(readn->filename, "AuPipe");
	readn->size = 0;
	readn->eof = 0;
	readn->pos = 0;
	readn->current = 0;
	readn->flags = FS_FLAG_GENERAL | FS_FLAG_DEVICE;
	readn->status = 0;
	readn->open = 0;
	readn->device = p;
	readn->read = pipe_read;
	readn->write = 0;
	readn->read_blk = 0;
	readn->ioquery = 0;
	readn->close = pipe_close;

	vfs_node_t *writen = (vfs_node_t*)malloc(sizeof(vfs_node_t));
	strcpy(writen->filename, "AuPipe");
	writen->size = 0;
	writen->eof = 0;
	writen->pos = 0;
	writen->current = 0;
	writen->flags = FS_FLAG_GENERAL | FS_FLAG_DEVICE;
	writen->status = 0;
	writen->open = 0;
	writen->device = p;
	writen->write = pipe_write;
	writen->read = 0;
	writen->read_blk = 0;
	writen->ioquery = 0;
	writen->close = pipe_close;
	
	/* Read End */
	thread_t * t = get_current_thread();
	t->fd[t->fd_current] = readn;
	fd[0] = t->fd_current;
	t->fd_current++;

	/* Write End */
	t->fd[t->fd_current] = writen;
	fd[1] = t->fd_current;
	t->fd_current++;
	
}





