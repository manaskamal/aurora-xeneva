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
 * @sysfile.cpp -- system call implementation for file management
 *
 **/

#include <fs\vfs.h>

#include <arch\x86_64\cpu.h>
#include <string.h>
#include <stdio.h>
#include <proc.h>
#include <arch\x86_64\cpu.h>
#include <serial.h>
#include <error.h>
#include <hal.h>
#include <atomic\mutex.h>

/**
 * sys_open_file -- opens a file 
 * @param filename -- file path 
 * @param ufile -- user mode file structure to write opened
 * file information
 * @return fd -- opened file entry in file descriptor table
 */
int sys_open_file (char* filename, FILE *ufile) {
	x64_cli();
	char* p = strchr (filename, '/');
	if (p)
		p++;


	char pathname[16];
	int i;
	for (i = 0; i < 16; i++) {
		if ( p[i] == '/'  || p[i] == '\0')
			break;
		pathname[i] = p[i];
	}

	pathname[i] = 0;

	int fd = AU_INVLD_FD;
	vfs_node_t *node = vfs_finddir(filename);

	bool fd_found = false;
	if (node) {
		for (int i = 0; i < 60; i++) {
			vfs_node_t *_node = get_current_thread()->fd[i];
			if (_node == node) {
				fd = i;
				fd_found = true;
				break;
			}
		}
	}

	if (!(strcmp(pathname, "dev") == 0)) {
		vfs_node_t *file = openfs(node, filename);
		if (ufile) {
			ufile->id = fd;
			ufile->size = file->size;
			ufile->eof = file->eof;
			ufile->pos = file->pos;
			ufile->start_cluster = file->current;
			ufile->flags = file->flags; 
			ufile->status = file->status;
		}

		get_current_thread()->fd[get_current_thread()->fd_current] = file;
		fd = get_current_thread()->fd_current;
		get_current_thread()->fd_current++;
	}else {
		if (!fd_found){
			get_current_thread()->fd[get_current_thread()->fd_current] = node;
			fd = get_current_thread()->fd_current;
			get_current_thread()->fd_current++;
		}
	}
	
	//! return the allocated fd number
	return fd;
}

/**
 * sys_read_file -- reads an opened file to a buffer
 * @param fd -- file descriptor
 * @param buffer -- buffer to write the content to
 * @param ufile -- user mode file structure
 */
size_t sys_read_file (int fd, uint8_t* buffer, FILE *ufile) {
	x64_cli ();
	vfs_node_t *file = NULL; 
	size_t byte_read = AU_INVALID;
	vfs_node_t *node = NULL;

	/* if UFILE->size is greater than 0, it's a
	 * file system based file descriptor, so get
	 * the root file system file */
	if (ufile){
		node = vfs_finddir("/");
		file = get_current_thread()->fd[fd];
		if (file == NULL)
			return byte_read;

		if (node == NULL)
			return byte_read;
		for (int i=0; i < ufile->size; i++){
			if (file->eof) {
				ufile->eof = 1;
				break;
			}
			uint64_t* buff = (uint64_t*)p2v((size_t)AuPmmngrAlloc());
			memset(buff, 0, 4096);
			size_t read_ = readfs_block (node,file,(uint64_t*)v2p((size_t)buff));
			memcpy (buffer,buff,4096);
			buffer += 4096;
			AuPmmngrFree((void*)v2p((size_t)buff));
			byte_read += read_;
		}

	}else if (ufile == NULL) {
		/* So this fd is non-file system based fd
		 * get it from fd table */
		node = get_current_thread()->fd[fd];
		if (node == NULL)
			return byte_read;

		size_t read_ = readfs(node, node, (uint64_t*)buffer, node->size);
		byte_read += read_;
	}

	return byte_read;
}


/**
 * sys_write_file -- Writes to an opened file
 * @param fd -- file descriptor number of the opened file
 * @param buffer - buffer from where to write
 * @param ufile -- user mode file structure
 */
void sys_write_file (int fd, uint64* buffer, FILE *ufile) {
	x64_cli();
	vfs_node_t file;
	memset(&file, 0, sizeof(vfs_node_t));
	if (ufile) {
		file.size = ufile->size;
		file.eof = ufile->eof;
		file.pos = ufile->pos;
		file.current = ufile->start_cluster;
		file.flags = ufile->flags;
		file.status = ufile->status;
	}

	vfs_node_t *node = get_current_thread()->fd[fd];
	if (node == NULL) {
		return;
	}

	if (ufile) {
		if (ufile->flags){
			writefs(node, &file,buffer,file.size);
		}
	}else {
		writefs(node, node, buffer,4096);
	}
}

/*
 * sys_close_file -- closes opened file
 */
void sys_close_file (int fd) {
	x64_cli();
	/* If already it's freed by someone, so
	 * just return from the system call
	 */
	if (get_current_thread()->fd[fd] == 0)
		return;

	vfs_node_t *node = get_current_thread()->fd[fd];
	get_current_thread()->fd[fd] = 0;
	if ((node->flags & FS_FLAG_DEVICE)){

		if (node->close)
			node->close(node);
		return;
	}else{

		if (node->close)
			node->close(node);
		else
			free(node);
	}

}

/* sys_copy_fd -- copies a file descriptor to another process main thread
 * @param tid -- thread id
 * @param fd -- file descriptor to copy
 */
int sys_copy_fd (int tid, int fd, int dest_fd) {
	x64_cli();
	vfs_node_t *node = get_current_thread()->fd[fd];
	thread_t *t = thread_iterate_block_list(tid);
	if (t == NULL)
		t = thread_iterate_ready_list(tid);

	if (t == NULL)
		return AU_FAILURE;

	if (t->fd[dest_fd] != NULL){
		return AU_FAILURE;
	}else{
		t->fd[dest_fd] = node;
	}
	return AU_SUCCESS;
}

