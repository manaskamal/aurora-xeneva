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

#include <vfs.h>
#include <arch\x86_64\cpu.h>
#include <string.h>
#include <stdio.h>

void  sys_open_file (UFILE* file, const char* filename) {
	x64_cli();
	open_call (file,filename);
	//memcpy (file, &f, sizeof(FILE));
	//return;
}

void sys_read_file (UFILE *file, unsigned char* buffer, int length) {
	x64_cli ();
	FILE f;
	memset(f.filename, 0, 32);
	f.eof = file->eof;
	f.flags = file->flags;
	f.id = file->id;
	f.pos = file->pos;
	f.size = file->size;
	f.start_cluster = file->start_cluster;
	f.status = file->status;
	read (&f,buffer,length,file->id);
}