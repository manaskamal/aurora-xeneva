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
#include <_null.h>
#include <stdint.h>
#include <aurora.h>

#define EOF (-1)

#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#ifndef SEEK_SET
#define SEEK_SET 1
#define SEEK_CUR 2
#define SEEK_END 3
#endif

typedef unsigned fpos_t;

extern int atoi (const char* s);
extern char* sztoa(size_t value, char* str, int base);
AU_EXTERN AU_EXPORT void printf(const char* format, ...);
extern int putchar (int);
extern int getchar ();
extern void *memmove (void* dest, const void* src, size_t n);
extern char* ftoa(float value, uint8_t decimal_places);

#endif