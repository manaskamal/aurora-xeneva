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

#ifndef __VFS_H__
#define __VFS_H__

#include <stdint.h>


#define  FILE_FLAG_DIRECTORY  0x1
#define  FILE_FLAG_GENERAL   0x2
#define  FILE_FLAG_DELETED    0x3
#define  FILE_FLAG_INVALID    FILE_FLAG_DELETED

#define  FILE_STATUS_FOUND   0x1


typedef struct _file_ {
	char filename[32];
	uint32_t  id;
	uint32_t  size;
	uint32_t  eof;
	uint32_t  pos;
	uint32_t  start_cluster;
	uint32_t  flags; 
	uint32_t  status;
}FILE;


typedef struct _file_system_ {
	char name[8];
	FILE (*sys_open)  (const char* filename);
	void (*sys_read)  (FILE* pfile, unsigned char * buffer, int length);
	void (*sys_read_blk) (FILE *file, unsigned char* buffer);
} file_system_t;



extern void initialize_vfs ();
extern FILE open (const char* filename);
extern void read (FILE *f, unsigned char* buffer, unsigned int length);
extern void read_blk (FILE *f, unsigned char* buffer);
#endif