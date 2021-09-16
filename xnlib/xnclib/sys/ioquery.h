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


//!code
#define SVGA_GET_WIDTH  0x201
#define SVGA_GET_HEIGHT  0x202
#define SVGA_SET_MODE   0x200
#define SVGA_GET_BPP    0x203
#define SVGA_UPDATE     0x205
#define SVGA_MOVE_CURSOR  0x206
#define SVGA_GET_SCANLINE 0x207

extern "C" int ioquery (int devid, int code, void* arg);

#endif