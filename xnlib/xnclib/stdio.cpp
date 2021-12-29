///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  stdio.h -- Standard C Library
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!===============================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys\_term.h>
#include <sys\_file.h>

int fprintf(UFILE f, const char* format, ...) {
	return -1;
}

int printf(const char *buf, ...){
	unsigned char* buffer = (unsigned char*)malloc(4096);
	memcpy(buffer, (void*)buf,4096);
	UFILE file;
	file.size = 4096;
	file.flags = 0;
	sys_write_file(1,buffer,&file);
	free(buffer);
	return -1;
}

FILE *fopen (const char* name, const char* mode) {
	FILE *f = (FILE*)malloc(sizeof(FILE));
	UFILE *uf = (UFILE*)malloc(sizeof(UFILE));
	char* fname = (char*)name;
	int fd = sys_open_file (fname,uf);
	f->base = 0;
	f->fd = fd;
	f->flags = 0;
	f->pos = 0;
	f->ptr = f->base;
	f->size = uf->size;
	f->eof =  uf->eof;
	f->status = uf->status;
	f->stream = uf;
    return f;
}


size_t fread (void* ptr, size_t size, size_t nmemb,FILE* stream) {
	stream->base = (unsigned char*)ptr;
	stream->ptr = stream->base;
	sys_read_file (stream->fd,(unsigned char*)ptr,stream->stream);
	return size;
}

long ftell (FILE *fp) {
	return (fp->pos - fp->base);
}


int fseek (FILE* fp, long int offset,  int pos) {
	int val = 0;
	switch (pos) {
	case SEEK_SET:
		fp->pos = fp->base;
		break;
	case SEEK_CUR:
		fp->pos = (fp->base + offset);
		break;
	case SEEK_END:
		fp->pos = (fp->base + fp->size-1);
		break;
	}

	return val;
}

int fgetc (FILE* fp) {
	int len = ftell(fp);
	if (len == fp->size) {
		fp->eof = 1;
		return 0;
	}

	return *(fp->pos++);
}

int fclose (FILE *fp) {
	free (fp->stream);
	free (fp);
	//also call xeneva sys_file_close func to 
	//unallocate the file descriptor/file handle
	return 1;
}

int vfprintf(FILE *stream, const char* format, va_list arg){
	//S
	return 1;
}

int sprintf(char *str, const char* string, ...) {
	return 1;
}




