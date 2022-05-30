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
#include <sys\_xeneva.h>

#ifdef __cplusplus
XE_EXTERN {
#endif
//!=====================================================
//! S T R I N G   G L O B A L   F U N C T I O N S
//!=====================================================
XE_EXPORT int strcmp (const char* str1, const char* str2);
XE_EXPORT char *strcpy(char *s1, const char *s2);
XE_EXPORT size_t strlen (const char* str);
XE_EXPORT size_t strnlen(const char *string, size_t maxlen);
XE_EXPORT int strncmp(const char* s1, const char *s2, size_t n);
XE_EXPORT char *strncpy(char *destString, const char* sourceString, size_t maxLength);
XE_EXPORT char* strchr (char* str, int character);
XE_EXPORT int strcasecmp(const char *, const char *);
XE_EXPORT int strncasecmp(const char *s1, const char *s2, size_t length);
XE_EXPORT char* strcasestr (const char*, const char*);
XE_EXPORT char* strcat(char *, const char*);
XE_EXPORT char *strncat(char *destString, const char *sourceString, size_t maxLength);
XE_EXPORT char* strdup(const char*);
XE_EXPORT char* strerror (int);
XE_EXPORT char* strrchr(const char*, int);
XE_EXPORT size_t strspn(const char*, const char*);
XE_EXPORT char* strtok (char*, const char*);
XE_EXPORT char* strtok_r (char*, const char*, char **);
XE_EXPORT char* strstr(const char* s1, const char* s2);

#define index(str, chr) strchr(str, chr)
#define rindex(str, chr) strrchr(str, chr)

//!=====================================================
//! M E M O R Y  G L O B A L   F U N C T I O N S
//!=====================================================
XE_EXPORT void* _cdecl memset(void *targ, unsigned char val, size_t len);

XE_EXPORT void *memcpy(void *targ, void *src, size_t len);
XE_EXPORT int memcmp(const void *first, const void *second, size_t length);
XE_EXPORT void bcopy(const void*, void*, size_t n);
XE_EXPORT void bzero(void *, size_t);
XE_EXPORT int ffs(int);
XE_EXPORT int fls(int);
XE_EXPORT size_t mbslen(const char*);
XE_EXPORT void* memmove (void* dest, void const *src, unsigned __int64 bytes);
XE_EXPORT void *memchr(const void *src, int c, size_t n);


#ifdef __cplusplus
}
#endif


#endif

