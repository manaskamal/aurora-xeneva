/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  _file.h -- File Header
 *
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *=================================================
 */

#ifndef __FILE_H__
#define __FILE_H__

#include <stdint.h>

typedef struct _file_ {
	//char filename[32];
	uint32_t  id;
	uint32_t  size;
	uint32_t  eof;
	uint32_t  pos;
	uint32_t  start_cluster;
	uint32_t  flags; 
	uint32_t  status;
}FILE;

extern "C" int sys_open_file (char* filename, FILE *stream);
extern "C" void sys_read_file (int fd, unsigned char* buffer,FILE *f);


#endif