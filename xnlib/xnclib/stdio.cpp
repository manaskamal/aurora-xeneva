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


int printf(const char *format, ...){
	unsigned char* buffer = (unsigned char*)malloc(4096);
	size_t loc = 0;
	size_t i;
	va_list args;
	va_start(args,format);

	for (i = 0; i <= strlen(format); i++, loc++) {
		switch(format[i]) {
		case '%' :
			switch (format[i+1]) {
			case 'c': {
				char c = va_arg(args,char);
				buffer[loc] = c;
				i++;
				break;
					  }

			case 'd':
			case 'i': {
				int c = va_arg(args,int);
				char s[32];
				itoa_s (c, 10, s);
				strcpy ((char*)&buffer[loc],s);
				loc += strlen(s)-2;
				i++;
				break;
					  }

			case 'X':
			case 'x': {
				int c = va_arg(args, int);
				char s[32];
				itoa_s(c, 16, s);
				strcpy ((char*)&buffer[loc], s);
				i++;
				loc += strlen(s)-2;
				break;
					  }
			case 's': {
				int c = (int&)va_arg(args,char);
				char s[32];
				strcpy (s, (const char*)c);
				strcpy ((char*)&buffer[loc], s);
				i++;
				loc += strlen(s)-2;
				break;
				}
			default: {
				va_end(args);
				return 1;
			}
			}
			break;
		default:
			buffer[loc] = format[i];
			break;
		}
	}

	va_end(args);
	_term_putchar_(buffer);
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




