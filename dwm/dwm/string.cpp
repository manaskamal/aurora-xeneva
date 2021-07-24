/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  string.cpp -- String manipulation and memory 
 *
 *  /PROJECT - Desktop Window Manager { DWM }
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ================================================
 */

#include <string.h>

void *memcpy(void *dest, void *src, size_t count) {
	const char *sp = (const char*)src;
	char *dp = (char*)dest;
	for(; count != 0; count--) *dp++ = *sp++;
	return dest;
}


void memset(void *targ, uint8_t val, uint32_t len){
	uint8_t *t = (uint8_t*) targ;
	while (len--)
		*t++ = val;
}


size_t strlen (const char* str)
{
	size_t len=0;
	while (str[len++]);
	return len;
}

char *strcpy(char *s1, const char *s2)
{
	char *s1_p = s1;
	while (*s1++ = *s2++);
	return s1_p;
}

