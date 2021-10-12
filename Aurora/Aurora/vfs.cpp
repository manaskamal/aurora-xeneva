/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  vfs.h -- Virtual File System Interface
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * =============================================
 */

#include <fs\fat32.h>
#include <vfs.h>
#include <string.h>
#include <stdio.h>
#include <console.h>
#include <mm.h>


#define MAX_FILE_DESC  256

file_system_t *sys[MAX_FILE_DESC];


void initialize_vfs () {
	//! By default FAT32 is recommended for boot disk
#ifdef ARCH_X64
	initialize_fat32();
	fat32_self_register();
#endif
}

FILE open (const char* filename) {
	FILE file;
	unsigned char device;
	int device_id = 0;

	char* fname = (char*)filename;
	if (filename[1] == ':') {
		device = filename[0];
		filename += 2;
	}
	if (device == 'a' || device == 'A')
		device_id = 10;
	else if (device =='c' || device == 'C')
		device_id = 11;

	file = sys[device_id]->sys_open(filename);
	return file;
}

void open_call (UFILE *f, const char* filename) {
	FILE file;
	unsigned char device;
	int device_id = 0;

	char* fname = (char*)filename;
	if (filename[1] == ':') {
		device = filename[0];
		filename += 2;
	}
	if (device == 'a' || device == 'A')
		device_id = 10;
	else if (device =='c' || device == 'C')
		device_id = 11;
	file = sys[device_id]->sys_open(filename);
	f->id = file.id;
	f->size = file.size;
	f->eof = file.eof;
	f->pos = file.pos;
	f->start_cluster = file.start_cluster;
	f->flags = file.flags; 
	f->status = file.status;
}

void read (FILE *f, unsigned char* buffer,unsigned int count, int device_id) {
    sys[device_id]->sys_read (f,buffer,count);
}

void read_blk (FILE *f, unsigned char *buffer, int device_id) {
	sys[device_id]->sys_read_blk(f,buffer);
}

void vfs_io_query (int device_id, int code, void* arg) {

	//! INVALID device id code
	if (device_id < 0)
		return;

	sys[device_id]->ioquery(code, arg);
}

void vfs_register (int id, file_system_t *fsys) {
	sys[id]  = fsys;
}

file_system_t * vfs_get_file_system (int id) {
	return sys[id];
}





