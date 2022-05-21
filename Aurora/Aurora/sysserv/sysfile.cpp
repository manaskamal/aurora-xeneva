/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2021, Manas Kamal Choudhury
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
#include <hal.h>
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

    int fd = 0;
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
		vfs_node_t file = openfs(node, filename);
		if (ufile) {
			ufile->id = fd;
			ufile->size = file.size;
			ufile->eof = file.eof;
			ufile->pos = file.pos;
			ufile->start_cluster = file.current;
			ufile->flags = file.flags; 
			ufile->status = file.status;
		}

		vfs_node_t *file_ = (vfs_node_t*)malloc(sizeof(vfs_node_t));
		memcpy(file_, &file, sizeof(vfs_node_t));
		get_current_thread()->fd[get_current_thread()->fd_current] = file_;
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
void sys_read_file (int fd, uint8_t* buffer, FILE *ufile) {
	x64_cli ();
	vfs_node_t *file = NULL; 

	vfs_node_t *node = NULL;

	/* if UFILE->size is greater than 0, it's a
	 * file system based file descriptor, so get
	 * the root file system file */
	if (ufile->size > 0){
		node = vfs_finddir("/");
		file = get_current_thread()->fd[fd];
		if (node == NULL)
			return;
		for (int i=0; i < ufile->size; i++){
			if (file->eof) {
				ufile->eof = 1;
				break;
			}
			uint64_t* buff = (uint64_t*)p2v((size_t)AuPmmngrAlloc());
			memset(buff, 0, 4096);
			readfs_block (node,file,(uint64_t*)v2p((size_t)buff));
			memcpy (buffer,buff,4096);
			buffer += 4096;
			AuPmmngrFree((void*)v2p((size_t)buff));
		}

	}else if (ufile == NULL) {
		/* So this fd is non-file system based fd
		 * get it from fd table */
		node = get_current_thread()->fd[fd];
		if (node == NULL)
			return;

		readfs(node, node, (uint64_t*)buffer, file->size);
	}

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
	file.size = ufile->size;
	file.eof = ufile->eof;
	file.pos = ufile->pos;
	file.current = ufile->start_cluster;
	file.flags = ufile->flags;
	file.status = ufile->status;
	file.open = 0;
	file.read = 0;
	file.read_blk = 0;
	file.write = 0;
	file.ioquery  = 0;

	vfs_node_t *node = get_current_thread()->fd[fd];
	if (node == NULL) {
		return;
	}

	if (ufile->flags) {
		writefs(node, &file,buffer,file.size);
	}else {
		writefs(node, node, buffer,file.size);
	}
}

