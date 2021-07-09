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

file_system_t sys;

void initialize_vfs () {
	
	//! By default FAT32 is recommended
#ifdef ARCH_X64
	initialize_fat32();
	memcpy(sys.name,"FAT32",5);
	sys.sys_open = fat32_open;
	sys.sys_read = fat32_read_file;
	sys.sys_read_blk = fat32_read;
#endif
}

FILE open (const char* filename) {
	return sys.sys_open(filename);
}
void read (FILE *pfile, unsigned char* buffer,unsigned int count) {
    sys.sys_read (pfile,buffer,count);
}

void read_blk (FILE *pfile, unsigned char *buffer) {
	sys.sys_read_blk(pfile,buffer);
}



