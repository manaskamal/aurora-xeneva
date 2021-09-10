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

void  sys_open_file (FILE *file, const char* filename) {
	x64_cli ();
	FILE f = open (filename);
	if (f.status == FILE_FLAG_INVALID) {
		printf ("File not found\n");
	}
	memcpy (file, &f, sizeof(FILE));
}

void sys_read_file (FILE *file, unsigned char* buffer, int length) {
	x64_cli ();
	read (file,buffer,length,10);
}