///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   stream.h -- Memory Stream for Standard input, output & errors
///!
///!   /PROJECT - Aurora's Xeneva v1.0
///!   /AUTHOR  - Manas Kamal Choudhury
///!
///!=====================================================================

#ifndef __STREAM_H__
#define __STREAM_H__

#include <stdint.h>

typedef struct _stream_ {
	char in[32];
	char out[32];
	char err[32];
}stream_t;

extern stream_t * allocate_stream ();
extern void stream_init ();


#endif