/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  /PROJECT - Aurora Xeneva v1.0
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ==============================================
 */

#ifndef __STDLIB_H__
#define __STDLIB_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>


#define max(a, b)  ((a) > (b) ? (a) : (b))
#define min(a, b)  ((a) < (b) ? (a) : (b))
#define offsetof(type, field)  ((unsigned long) &(((type *)0L)->field))

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define RAND_MAX  (0x7fffffff)

int atoi (const char*);
long atol (const char*);
long atoll (const char *);
double atof (const char*);
int abs (int);
void* malloc(unsigned int);
void free(void* ptr);
void* realloc (void* address, unsigned int new_size);
void* calloc(unsigned long long num, unsigned long long size);
int mblen (const char*, size_t);
size_t mbstowcs(wchar_t *, const char*, size_t);
int mbtowc (wchar_t*, const char*, size_t);
char* mkdtemp (char*);
char* mkstemp (char *);
int rand (void);
#define random() rand()
size_t wcstombs (char*, const wchar_t *, size_t);
int wctomb (char*, wchar_t);
void qsort(void* base, size_t num, size_t size, int (*comparator)(const void*, const void*));

char* sztoa(size_t value, char* str, int base);
char* getenv(const char*);
void exit (int errno);

int vsprintf(char *str, const char *format, va_list ap);
long strtol(const char* nptr, char** endptr, int base);
unsigned long strtoul(const char* nptr, char** endptr, int base);


#ifdef __cplusplus
}
#endif


#endif