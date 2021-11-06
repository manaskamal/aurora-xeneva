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
#include <stdlib.h>
#include <values.h>

#define MAX_STRING_LENGTH 25

void memset(void *targ, uint8_t val, uint32_t len){
	uint8_t *t = (uint8_t*) targ;
	while (len--)
		*t++ = val;
}

int memcmp(const void *vl, const void *vr, size_t n)
{
	const unsigned char *l = (unsigned char*)vl, *r=(unsigned char*)vr;
	for (; n && *l == *r; n--, l++, r++);
	return n ? *l-*r : 0;
}

void *memcpy(void *dest, void *src, size_t count) {
	const char *sp = (const char*)src;
	char *dp = (char*)dest;
	for(; count != 0; count--) *dp++ = *sp++;
	return dest;
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

size_t strnlen(const char *string, size_t maxlen)
{
	size_t count = 0;

	if (!string)
	{
		//errno = ERR_NULLPARAMETER;
		return (count = 0);
	}

	while ((string[count] != '\0') && (count <= MAX_STRING_LENGTH) &&
		 (count < maxlen))
	{
		count ++;
	}

	// If this is true, then we probably have an unterminated string
	// constant.  Checking for a string that exceeds MAXSTRINGLENGTH will
	// help to prevent the function from running off too far into memory.
	if (count > MAX_STRING_LENGTH)
	{
		//errno = ERR_BOUNDS;
		return (count = 0);
	}

	return (count);
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


int strcasecmp (const char* s1, const char *s2) {
	int count = 0;
	for (count = 0; count < MAX_STRING_LENGTH; count++) {
		if ((s1[count] == '\0') && (s2[count] == '\0'))
			return 0;
		else if ((s1[count] >= (char)97) &&
			(s1[count] <= (char) 122) &&
			(s2[count] == (s1[count] - (char)32))) {
				continue;
		}
		else if (s1[count] != s2[count]) {
			if (s1[count] == '\0')
				return -1;
			else if (s2[count] == '\0')
				return 1;

			return (s1[count] - s2[count]);
		}
	}

	return 0;
}


int strncasecmp(const char *s1, const char *s2, size_t length)
{
	int result = 0;

	// Go through the strings, counting as we go.  If we get to the end, or
	// "length" and everything matches, we return 0.  Otherwise, if the strings
	// match partially, we return the count at which they diverge.  If they
	// don't match at all, we return -1

	for (result = 0; ((result < MAX_STRING_LENGTH) &&
		((unsigned) result < length)); result ++)
	{
		if ((s1[result] == '\0') && (s2[result] == '\0'))
			return (result = 0);

		// Is the ascii code a lowercase alphabet character?
		else if ((s1[result] >= (char) 97) &&
			(s1[result] <= (char) 122) &&
			(s2[result] == (s1[result] - (char) 32)))
		{
			// We call it a match
			continue;
		}

		// Is the ascii code an uppercase alphabet character?
		else if ((s1[result] >= (char) 65) &&
			(s1[result] <= (char) 90) &&
			(s2[result] == (s1[result] + (char) 32)))
		{
			// We call it a match
			continue;
		}
		else if (s1[result] != s2[result])
		{
			if (!result)
				return (result = -1);

			else
				return (result);
		}
	}

	// If we fall through to here, we matched as many as we could
	return (result = 0);
}

char* strcasestr(const char* s1, const char* s2) {

	int count = 0;
	char *ptr = NULL;
	int s1_length = strlen(s1);
	int s2_length = strlen(s2);

	ptr = (char*)s1;

	for (count = 0; count < s1_length; count++) {
		if (!strncasecmp(ptr, s2, s2_length))
			return (ptr);
		else
			ptr++;
	}

	return (ptr = NULL);
}


char *strcat(char *destString, const char *sourceString)
{
	int count1, count2;

	// Find the end of the first String
	for (count1 = 0; count1 < MAX_STRING_LENGTH; )
	{
		if (!destString[count1])
			break;

		count1 += 1;
	}

	// If this is true, then we possibly have an unterminated string constant.
	// Checking for a string that exceeds MAXSTRINGLENGTH will help to prevent
	// the function from running off too far into memory.
	if (count1 >= MAX_STRING_LENGTH)
	{
		//errno = ERR_BOUNDS;
		return (destString = NULL);
	}

	// Now copy the source string into the dest until the source is a NULL
	// character.
	for (count2 = 0; count1 < MAX_STRING_LENGTH; count1 ++, count2 ++)
	{
		destString[count1] = sourceString[count2];

		if (!sourceString[count2])
			break;
	}

	return (destString);
}


char *strncat(char *destString, const char *sourceString, size_t maxLength)
{
	unsigned count1, count2;
	int endFlag = 0;
	char sourceChar;

	// Find the end of the first String
	for (count1 = 0; count1 < MAX_STRING_LENGTH; )
	{
		if (destString[count1] == '\0')
			break;
		else
			count1++;
	}

	// If this is true, then we probably have an unterminated string
	// constant.  Checking for a string that exceeds MAXSTRINGLENGTH will
	// help to prevent the function from running off too far into memory.
	if (count1 >= MAX_STRING_LENGTH)
	{
		//errno = ERR_BOUNDS;
		return (destString = NULL);
	}

	// Now copy the source string into the dest.  If source is shorter than
	// maxLength, pad dest with NULL characters.
	for (count2 = 0; count2 < maxLength; )
	{
		if ((sourceString[count2] == '\0') || (endFlag == 1))
		{
			endFlag = 1;
			sourceChar = (char) NULL;
		}
		else
		{
			sourceChar = sourceString[count2];
		}

		destString[count1] = sourceChar;
		count1++; count2++;
	}

	// Make sure there's a NULL at the end
	destString[count1] = NULL;

	// Return success
	return (destString);
}

char *strdup(const char *srcString)
{
	// I don't like this function.  Anyway, it makes a copy of the string.

	int length = 0;
	char *destString = NULL;

	// Check params
	if (!srcString)
	{
		return (destString = NULL);
	}


	length = strnlen(srcString, MAX_STRING_LENGTH);

	destString = (char*)malloc(length + 1);
	if (!destString)
	{
		//errno = ERR_MEMORY;
		return (destString = NULL);
	}

	strncpy(destString, srcString, length);
	destString[length] = '\0';

	// Return success
	return (destString);
}


char* strerror (int error) {
	char* impl = (char*)"Not implemented yet.";
	return impl;
}


char *strrchr(const char *string, int character)
{
	char *strptr = NULL;

	// Check params
	if (!string)
		return ((char *) string);

	strptr = (char *)(string + strlen(string) - 1);

	while (strptr >= string)
	{
		if (strptr[0] == (char) character)
			return (strptr);

		strptr -= 1;
	}

	// Return failure
	return (NULL);
}


size_t strspn(const char *s1, const char *s2)
{
	// The strspn() function calculates the length of the initial segment of
	// s1 which consists entirely of characters in s2.

	int match = 0;
	int s1_length = strlen(s1);
	int s2_length = strlen(s2);
	int count;

	for (count = 0; ((count < s1_length) && (count < s2_length)); count ++)
	{
		if (s1[count] != s2[count])
			break;

		match++;
	}

	return (match);
}


char* strstr(const char* s1, const char* s2) {
	int count = 0;
	int s2Len = strlen(s2);

	for (count = 0; s1[0]; count++){
		if (!strncmp(s1,s2,s2Len))
			return ((char*)s1);
		else
			s1++;
	}

	return NULL;
}



static char* saveptr = NULL;
char *strtok(char *string, const char *delim)
{
	// The strtok() function parses a string into a sequence of tokens.  The
	// string to be parsed is passed to the first call of the function along
	// with a second string containing delimiter characters.

	char *token = NULL;

	// Check params
	if (!string)
	{
		if (!saveptr)
			return (saveptr = NULL);
	}
	else
	{
		// This is the first call with this string
		saveptr = string;
	}

	if (!delim)
	{
		// We need delimiters
		return (saveptr = NULL);
	}

	// Skip any leading delimiter characters
	while (saveptr[0] && strchr((char*)delim, saveptr[0]))
		saveptr += 1;

	if (!saveptr[0])
	{
		// Nothing left
		return (saveptr = NULL);
	}

	// Remember the start of the token.  This will be our return value.
	token = saveptr;

	// Move our save pointer along to the next delimiter or NULL
	while (saveptr[0] && !strchr((char*)delim, saveptr[0]))
		saveptr += 1;

	if (saveptr[0])
	{
		// Insert a NULL at the delimiter
		saveptr[0] = '\0';

		// Move to the next char.  We don't care what it is (NULL, delimiter,
		// etc) because the next call will deal with that.
		saveptr += 1;
	}

	return (token);
}


char *strtok_r(char *string, const char *delim, char **saveptr)
{
	// The strtok_r() function parses a string into a sequence of tokens.  The
	// string to be parsed is passed to the first call of the function along
	// with a second string containing delimiter characters, and a third
	// pointer for saving state between calls.  This is a reentrant version of
	// strtok().

	char *token = NULL;

	// Check params
	if (!saveptr)
	{
		return (token = NULL);
	}
	if (!string)
	{
		if (!*saveptr)
			return (*saveptr = NULL);
	}
	else
	{
		// This is the first call with this string
		*saveptr = string;
	}

	if (!delim)
	{
		// We need delimiters
		return (*saveptr = NULL);
	}

	// Skip any leading delimiter characters
	while (*saveptr[0] && strchr((char*)delim, *saveptr[0]))
		*saveptr += 1;

	if (!*saveptr[0])
	{
		// Nothing left
		return (*saveptr = NULL);
	}

	// Remember the start of the token.  This will be our return value.
	token = *saveptr;

	// Move our save pointer along to the next delimiter or NULL
	while (*saveptr[0] && !strchr((char*)delim, *saveptr[0]))
		*saveptr += 1;

	if (*saveptr[0])
	{
		// Insert a NULL at the delimiter
		*saveptr[0] = '\0';

		// Move to the next char.  We don't care what it is (NULL, delimiter,
		// etc) because the next call will deal with that.
		*saveptr += 1;
	}

	return (token);
}


//!===========================================================
//!==========================================================
//! Memory Functions
//!===========================================================
//!-----------------------------------------------------------


void bzero(void *string, size_t number)
{
	// The description from the GNU man page reads as follows:
	// The bzero() function sets the first n bytes of the byte string to zero.
	// The bzero() function returns no value.
	memset(string, 0, number);
	return;
}


void bcopy(const void *src, void *dest, size_t len)
{
	// The bcopy() function copies the first n bytes of the source string src
	// to the destination string dest.  If len is zero, no bytes are copied.

	size_t count = 0;

	for (count = 0; count < len; count ++)
		((char *) dest)[count] = ((char *) src)[count];

	return;
}

int ffs(int i)
{
	// Returns the least significant bit set in the word.

	int count;

	if (!i)
		return (0);

	for (count = 1; !(i & 1) && (count <= (int) INTBITS); count ++)
		i >>= 1;

	return (count);
}












