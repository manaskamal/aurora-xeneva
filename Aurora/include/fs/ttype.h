///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  ttype.h -- Tele type device file
///!
///!  /PROJECT - Aurora's Xeneva v1.0
///!  /AUTHOR  - Manas Kamal Choudhury 2021
///!  
///!=================================================

#ifndef __TTYPE_H__
#define __TTYPE_H__

#include <stdint.h>
#include <fs\vfs.h>


typedef struct _tele_type_ {
	uint8_t id;
	char m_path[32];
	char s_path[32];
	unsigned char in_buffer[32];
	unsigned char out_buffer[32];
	struct _tele_type_ *next;
	struct _tele_type_ *prev;
}ttype_t;


extern void ttype_create (int* master_fd, int* slave_fd);
extern ttype_t * get_ttype (int id);
#endif