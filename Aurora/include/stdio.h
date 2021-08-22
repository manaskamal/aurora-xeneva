/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  stdio.h -- standard input output 
 *
 *  /PROJECT - Aurora v1.0 {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *====================================================
 */


#ifndef __STDIO_H__
#define __STDIO_H__


#include <string.h>
#include <console.h>
#include <stdint.h>
#include <serial.h>

extern char* sztoa(size_t value, char* str, int base);
extern void printf(const char* format, ...);
#endif