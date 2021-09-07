/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  string.cpp -- String
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ====================================================
 */

#include <string.h>

#define MAX_STRING_LENGTH 25

void memset(void *targ, uint8_t val, uint32_t len){
	uint8_t *t = (uint8_t*) targ;
	while (len--)
		*t++ = val;
}

int memcmp(const void *first, const void *second, size_t length)
{

	size_t count;
	for (count = 0; count < length; count++)
	{
		if (((unsigned char*)first)[count] != ((unsigned char *) second)[count])
		{
			if (((unsigned char*)first)[count] < ((unsigned char *)second)[count])
			{
				return (-1);
			}
			else
			{
				return (1);
			}
		}
	}

	return (0); //return successful code
}


int strcmp (const char* str1, const char* str2)
{
	int res=0;
	while (!(res = *(unsigned char*)str1 - *(unsigned char*)str2) && *str2)
		++str1, ++str2;

	if (res < 0)
		res = -1;
	if (res > 0)
		res = 1;

	return res;
}

char *strcpy(char *s1, const char *s2)
{
	char *s1_p = s1;
	while (*s1++ = *s2++);
	return s1_p;
}

size_t strlen (const char* str)
{
	size_t len=0;
	while (str[len++]);
	return len;
}


int strncmp(const char* s1, const char *s2, size_t n)
{
	while (n > 0 && *s1 != '\0' && *s1 == *s2) {
		n --, s1 ++, s2 ++;
	}

	return (n==0)? 0: (size_t)((unsigned char)*s1 - (unsigned char)*s2);
}

char *strncpy(char *destString, const char* sourceString, size_t maxLength)
{
	unsigned count;

	if ((destString == (char*) NULL) || (sourceString == (char*) NULL))
	{
		return (destString = NULL);
	}

	if (maxLength > MAX_STRING_LENGTH)
		maxLength = MAX_STRING_LENGTH;

	for (count = 0; count < maxLength; count++ )
	{
		destString[count] = sourceString[count];
		 
		if (sourceString[count] == '\0')
			break;
	}

	if (count >= MAX_STRING_LENGTH)
	{
		return (destString = NULL);
	}

	return (destString);
}

//! locates first occurance of character in string
char* strchr (char* str, int character) {

	do {
		if (*str == character)
			return (char*)str;
	}
	while (*str++);

	return 0;
}
