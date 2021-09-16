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
extern int mblen (const char*, size_t);
extern size_t mbstowcs(wchar_t *, const char*, size_t);
extern int mbtowc (wchar_t*, const char*, size_t);
extern char* mkdtemp (char*);
extern char* mkstemp (char *);
extern int rand (void);
#define random() rand()


#endif