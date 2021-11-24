/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  string.h -- String Library
 *
 *  /PROJECT - Aurora Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *===============================================
 */

#ifndef _STRING_H
#define _STRING_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
//!=====================================================
//! S T R I N G   G L O B A L   F U N C T I O N S
//!=====================================================
int strcmp (const char* str1, const char* str2);
char *strcpy(char *s1, const char *s2);
size_t strlen (const char* str);
size_t strnlen(const char *string, size_t maxlen);
int strncmp(const char* s1, const char *s2, size_t n);
char *strncpy(char *destString, const char* sourceString, size_t maxLength);
char* strchr (char* str, int character);
int strcasecmp(const char *, const char *);
int strncasecmp(const char *s1, const char *s2, size_t length);
char* strcasestr (const char*, const char*);
char* strcat(char *, const char*);
char *strncat(char *destString, const char *sourceString, size_t maxLength);
char* strdup(const char*);
char* strerror (int);
char* strrchr(const char*, int);
size_t strspn(const char*, const char*);
char* strtok (char*, const char*);
char* strtok_r (char*, const char*, char **);
char* strstr(const char* s1, const char* s2);

#define index(str, chr) strchr(str, chr)
#define rindex(str, chr) strrchr(str, chr)

//!=====================================================
//! M E M O R Y  G L O B A L   F U N C T I O N S
//!=====================================================
void* _cdecl memset(void *targ, unsigned char val, size_t len);

void *memcpy(void *targ, void *src, size_t len);
int memcmp(const void *first, const void *second, size_t length);
void bcopy(const void*, void*, size_t n);
void bzero(void *, size_t);
int ffs(int);
int fls(int);
size_t mbslen(const char*);
void* memmove (void* dest, void const *src, unsigned __int64 bytes);
void *memchr(const void *src, int c, size_t n);


#ifdef __cplusplus
}
#endif


#endif

