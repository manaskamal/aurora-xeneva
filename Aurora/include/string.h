/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  string.h -- string 
 *
 *  /PROJECT - Aurora v1.0 {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ===========================================
 */

#ifndef __STRING_H__
#define __STRING_H__


#include <stdint.h>
#include <aurora.h>

//!=====================================================
//! S T R I N G   G L O B A L   F U N C T I O N S
//!=====================================================
AU_EXTERN AU_EXPORT int strcmp (const char* str1, const char* str2);
AU_EXTERN AU_EXPORT char *strcpy(char *s1, const char *s2);
AU_EXTERN AU_EXPORT size_t strlen (const char* str);
AU_EXTERN AU_EXPORT int strncmp(const char* s1, const char *s2, size_t n);
AU_EXTERN AU_EXPORT char *strncpy(char *destString, const char* sourceString, size_t maxLength);
AU_EXTERN AU_EXPORT char* strchr (char* str, int character);

//!=====================================================
//! M E M O R Y  G L O B A L   F U N C T I O N S
//!=====================================================
AU_EXTERN AU_EXPORT void memset(void *targ, uint8_t val, uint32_t len);
AU_EXTERN AU_EXPORT void  memcpy(void *targ, void *src, size_t len);
AU_EXTERN AU_EXPORT  int memcmp(const void *first, const void *second, size_t length);
AU_EXTERN AU_EXPORT void* memmove (void*, const void*, size_t);


#endif