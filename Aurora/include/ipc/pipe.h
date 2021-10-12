///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  pipe.h -- Pipe based IPC
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!=============================================

#ifndef __PIPE_H__
#define __PIPE_H__

#include <utils\circ_buf.h>

typedef struct _pipe_ {
	circ_buf_t *buf;
	uint32_t readers;
	uint32_t writers;
}pipe_t;

#endif