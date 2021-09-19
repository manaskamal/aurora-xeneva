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
//!=====================================================
//! S T R I N G   G L O B A L   F U N C T I O N S
//!=====================================================
extern int strcmp (const char* str1, const char* str2);
extern char *strcpy(char *s1, const char *s2);
extern size_t strlen (const char* str);
extern size_t strnlen(const char *string, size_t maxlen);
extern int strncmp(const char* s1, const char *s2, size_t n);
extern char *strncpy(char *destString, const char* sourceString, size_t maxLength);
extern char* strchr (char* str, int character);
extern int strcasecmp(const char *, const char *);
extern int strncasecmp(const char *s1, const char *s2, size_t length);
extern char* strcasestr (const char*, const char*);
extern char* strcat(char *, const char*);
extern char *strncat(char *destString, const char *sourceString, size_t maxLength);
extern char* strdup(const char*);
extern char* strerror (int);
extern char* strrchr(const char*, int);
extern size_t strspn(const char*, const char*);
extern char* strtok (char*, const char*);
extern char* strtok_r (char*, const char*, char **);

#define index(str, chr) strchr(str, chr)
#define rindex(str, chr) strrchr(str, chr)

//!=====================================================
//! M E M O R Y  G L O B A L   F U N C T I O N S
//!=====================================================
extern void  memset(void *targ, uint8_t val, uint32_t len);
extern void *memcpy(void *targ, void *src, size_t len);
extern int memcmp(const void *first, const void *second, size_t length);
extern void bcopy(const void*, void*, size_t n);
extern void bzero(void *, size_t);
extern int ffs(int);
extern int fls(int);
extern size_t mbslen(const char*);



#endif

