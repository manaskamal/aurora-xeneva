/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  sysfile.cpp -- System Calls for file handling
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury 2021
 *
 * =====================================================
 */

#include <fs\vfs.h>

#include <arch\x86_64\cpu.h>
#include <string.h>
#include <stdio.h>
#include <proc.h>

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


	vfs_node_t *node = vfs_finddir(filename);
	get_current_thread()->fd[get_current_thread()->fd_current] = node;
    int fd = get_current_thread()->fd_current;

	if (!(strcmp(pathname, "dev") == 0)) {
		vfs_node_t file = openfs(node, filename);
		ufile->id = fd;
		ufile->size = file.size;
		ufile->eof = file.eof;
		ufile->pos = file.pos;
		ufile->start_cluster = file.current;
		ufile->flags = file.flags; 
		ufile->status = file.status;
	}
	get_current_thread()->fd_current++;
	return fd;
}

void sys_read_file (int fd, unsigned char* buffer, FILE *ufile) {
	x64_cli ();
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
	readfs(node,&file,buffer,file.size);
}