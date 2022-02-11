/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  console.h -- Virtual Console
 *
 *  /PROJECT - Aurora v1.0 {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *====================================================
 */

#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <_xnboot.h>
#include <pmmngr.h>
#include <arch\x86_64\mmngr\vmmngr.h>



#pragma pack (push, 1)
typedef struct {
    uint32_t magic;
    uint32_t version;
    uint32_t headersize;
    uint32_t flags;
    uint32_t numglyph;
    uint32_t bytesperglyph;
    uint32_t height;
    uint32_t width;
    uint8_t glyphs;
}psf2_t;
#pragma pack (pop)

//! initialize console
extern void console_initialize (PKERNEL_BOOT_INFO info);

//! print string to console
extern void puts (char* str);

//! print character to console output
extern void putc (char c);

//! returns true if the console is initialized
extern bool is_console_initialized ();
#endif