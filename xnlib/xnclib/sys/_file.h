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
#include <sys\_xeneva.h>

typedef struct _file_ {
	//char filename[32];
	uint32_t  id;
	uint32_t  size;
	uint32_t  eof;
	uint32_t  pos;
	uint32_t  start_cluster;
	uint32_t  flags; 
	uint32_t  status;
}UFILE;

#ifdef __cplusplus
XE_EXTERN {
#endif
XE_EXPORT int sys_open_file (char* filename, UFILE *stream);
XE_EXPORT size_t sys_read_file (int fd, unsigned char* buffer,UFILE *f);
XE_EXPORT void sys_write_file (int fd, uint64_t* buffer, UFILE *f);
XE_EXPORT void sys_close_file (int fd);
XE_EXPORT int sys_copy_fd(int task_id, int master_fd, int dest_fd);
#ifdef __cplusplus
}
#endif


#endif