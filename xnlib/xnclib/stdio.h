///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  stdio.h -- Standard C Library
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!===============================================

#ifndef __STDIO_H__
#define __STDIO_H__

#include <sys\_file.h>
#include <stdarg.h>


typedef struct _iobuf_ {
	unsigned char* base;
	unsigned char* pos;
	unsigned char* ptr;
	int flags;
    int fd;
	int eof;
	int status;
	int size;
	UFILE *stream;
}FILE;

#define SEEK_SET  0
#define SEEK_CUR  1
#define SEEK_END  2


#define stdin  FILE*
#define stdout FILE*
#define stderr  FILE*

extern int fprintf(FILE, const char *, ...);
extern int printf(const char *, ...);
extern FILE* fopen (const char* name, const char* mode);
extern size_t fread (void* ptr, size_t size, size_t nmemb,FILE* stream);
extern long ftell (FILE *fp);
extern int fseek (FILE* fp, long int offset,  int pos);
extern int fgetc (FILE *fp);
extern int fgetc (FILE* fp);
extern int fclose (FILE *fp);
extern int fclose (FILE *fp);

extern int vfprintf(FILE *stream, const char* format, va_list arg);
extern int sprintf(char *str, const char* string,...);
#endif