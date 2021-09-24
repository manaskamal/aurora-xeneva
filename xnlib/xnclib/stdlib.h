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


#define max(a, b)  ((a) > (b) ? (a) : (b))
#define min(a, b)  ((a) < (b) ? (a) : (b))
#define offsetof(type, field)  ((unsigned long) &(((type *)0L)->field))

extern int atoi (const char*);
extern long atol (const char*);
extern long atoll (const char *);
extern double atof (const char*);
extern int abs (int);
extern void* malloc(unsigned int);
extern void free(void* ptr);
extern void* realloc (void* address, unsigned int new_size);
extern void* calloc(unsigned long long num, unsigned long long size);
extern int mblen (const char*, size_t);
extern size_t mbstowcs(wchar_t *, const char*, size_t);
extern int mbtowc (wchar_t*, const char*, size_t);
extern char* mkdtemp (char*);
extern char* mkstemp (char *);
extern int rand (void);
#define random() rand()
extern size_t wcstombs (char*, const wchar_t *, size_t);
extern int wctomb (char*, wchar_t);
extern void qsort(void* base, size_t num, size_t size, int (*comparator)(const void*, const void*));

extern char* sztoa(size_t value, char* str, int base);
#endif