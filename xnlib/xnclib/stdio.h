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
#include <sys\_xeneva.h>

#ifdef __cplusplus
XE_EXTERN {
#endif


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

XE_EXPORT int fprintf(FILE, const char *, ...);
XE_EXPORT int printf(const char *, ...);
XE_EXPORT FILE* fopen (const char* name, const char* mode);
XE_EXPORT size_t fread (void* ptr, size_t size, size_t nmemb,FILE* stream);
XE_EXPORT long ftell (FILE *fp);
XE_EXPORT int fseek (FILE* fp, long int offset,  int pos);
XE_EXPORT int fgetc (FILE *fp);
XE_EXPORT int fgetc (FILE* fp);
XE_EXPORT int fclose (FILE *fp);
XE_EXPORT int fclose (FILE *fp);

XE_EXPORT int vfprintf(FILE *stream, const char* format, va_list arg);
XE_EXPORT int sprintf(char *str, const char* string,...);


#ifdef __cplusplus
}
#endif


#endif