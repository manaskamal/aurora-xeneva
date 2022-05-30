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

#include <sys\_xeneva.h>

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
#define SVGA_UPDATE_FB  0x208

//! Mouse Code
#define MOUSE_IOCODE_DISABLE   300
#define MOUSE_IOCODE_ENABLE    301
#define MOUSE_REGISTER_WM      302


//! Standard codes for svga driver
#define SCREEN_SETMODE     0x100
#define SCREEN_GETWIDTH    0x101
#define SCREEN_GETHEIGHT   0x102
#define SCREEN_GETBPP      0x103
#define SCREEN_SETBPP      0x104
#define SCREEN_UPDATE      0x105
#define SCREEN_MOVE_CURSOR  0x106
#define SCREEN_GET_SCANLINE 0x107
#define SCREEN_UPDATE_FB  0x108

/* Pri Loop codes */
#define PRI_LOOP_CREATE    401
#define PRI_LOOP_DESTROY   402
#define PRI_LOOP_PUT_EVENT 403
#define PRI_LOOP_GET_EVENT 404

#define SOUND_REGISTER_MEDIAPLAYER 100
#define SOUND_START_OUTPUT  102
#define SOUND_STOP_OUTPUT  103
#define SOUND_START_INPUT  104
#define SOUND_STOP_INPUT  105


extern "C" XE_EXPORT int ioquery (int devid, int code, void* arg);

#endif