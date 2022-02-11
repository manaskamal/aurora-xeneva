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


//!=====================================================
//! S T R I N G   G L O B A L   F U N C T I O N S
//!=====================================================
extern int strcmp (const char* str1, const char* str2);
extern char *strcpy(char *s1, const char *s2);
extern size_t strlen (const char* str);
extern int strncmp(const char* s1, const char *s2, size_t n);
extern char *strncpy(char *destString, const char* sourceString, size_t maxLength);
extern char* strchr (char* str, int character);

//!=====================================================
//! M E M O R Y  G L O B A L   F U N C T I O N S
//!=====================================================
extern void memset(void *targ, uint8_t val, uint32_t len);
extern void  memcpy(void *targ, void *src, uint32_t len);
extern  int memcmp(const void *first, const void *second, size_t length);
extern void* memmove (void*, const void*, size_t);



#endif