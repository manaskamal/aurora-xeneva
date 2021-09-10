/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  ioquery.h -- IOQuery System call 
 *
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ==============================================
 */

#ifndef __IOQUERY_H__
#define __IOQUERY_H__

//!device ids
#define IO_QUERY_STDIN  0
#define IO_QUERY_STDOUT 1
#define IO_QUERY_STDERR 2
#define IO_QUERY_MOUSE 3
#define IO_QUERY_SVGA  4

extern "C" int ioquery (int devid, int code, void* arg);

#endif