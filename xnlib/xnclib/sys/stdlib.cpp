//**
//**   Copyright (C) Manas Kamal Choudhury 2021
//!
//!
//! /PROJECT - Aurora's Xeneva
//! /AUTHOR  - Manas Kamal Choudhury
//!
//!======================================================

#include <stdlib.h>
#include <ctype.h>
#include <heap.h>
#include <sys/utf.h>
#include <string.h>
#include <limits.h>

#define MB_CUR_MAX   MB_LEN_MAX

int abs (int i) {
	if (i < 0)
		return (-i);
	else
		return (i);
}


int atoi (const char* s) {
	
	int n = 0, neg =0;
	while (isspace(*s)) s++;
	switch (*s) {
	case '-': neg=1;
	case '+': s++;
	}

	while (isdigit(*s))
		n = 10*n - (*s++ - '0');
	return neg ? n : -n;
}


void* malloc (uint32_t s) {
	return _malloc(s);
}

void free (void* ptr) {
	return _free(ptr);
}

void* realloc (void* address, unsigned int new_size) {
	return _realloc(address, new_size);
}

void* calloc (unsigned long long num, unsigned long long size) {
	return _calloc(num, size);
}

int mblen (const char* s, size_t n) {
	if (!s)
		return 0;

	if ((n>=1) && UTF8_IS_1BYTE(s)) {
		if (s[0])
			return 1;
		else
			return 0;
	} else if ((n >=2) && UTF8_IS_2BYTE(s)) {
		return 2;
	} else if ((n >= 3) && UTF8_IS_3BYTE(s)) {
		return 3;
	} else if ((n >= 4) && UTF8_IS_4BYTE(s)) {
		return 4;
	} else {
		return (-1);
	}
}

size_t mbstowcs (wchar_t *dest,const char* src, size_t n) {

	int num_bytes = 0;
	int max_bytes = (n * MB_CUR_MAX);
	size_t count;

	for (count = 0; (!dest || (count < n));  count++) {
		if (dest)
			num_bytes = mbtowc(dest, src, max_bytes);
		else 
			num_bytes = mblen (src, max_bytes);

		if (num_bytes < 0)
			return (-1);

		if (*src == '\0')
			return count;

		dest+= 1;
		src += num_bytes;
		max_bytes -= num_bytes;
	}

	return n;
}


int mbtowc (wchar_t *wc, const char* bytes, size_t n) {
	
	int num_bytes = 0;

	if (!bytes)
		return 0;

	num_bytes = mblen (bytes, n);
	if (num_bytes < 0)
		return -1;

	if (wc) 
		*wc = (wchar_t) utf8CharToUnicode (bytes, n);
	return (num_bytes);
}



//! NOT IMPLEMENTED
int rand () {
	return 1;
}


int wctomb(char *s, wchar_t wc){

	int numBytes = 0;

	if (!s)
		// Stateless
		return (0);

	numBytes = utf8CodeWidth(wc);
	if (!numBytes)
		// Too large
		return (-1);

	unicodeToUtf8Char(wc, (unsigned char *) s, sizeof(wchar_t) /* assumed */);

	return (numBytes);
}


size_t wcstombs(char *dest, const wchar_t *src, size_t n) {
	size_t out_bytes = 0;
	int num_bytes = 0;

	while (!dest || (out_bytes < n)) {
		if (dest) 
			num_bytes = wctomb(dest, *src);
		else
			num_bytes = utf8CodeWidth(*src);

		if (num_bytes <= 0)
			return -1;

		if (*src == L'\0')
			break;

		dest += num_bytes;
		src += 1;
		out_bytes += num_bytes;
	}

	return out_bytes;
}

static void swap(void* a, void* b, size_t size) {
	if (a == b) 
		return;

	char temp[32];
	memcpy (temp, a, size);
	memcpy (a, b, size);
	memcpy (b, temp, size);
}

void qsort(void* base, size_t num, size_t size, int (*comparator)(const void*, const void*)) {
	if (num < 2) {
		return;
	}

	size_t left = 1, right = num - 1;

	while (left <= right) {
		while ((left <= right) && (comparator(base, (const unsigned*)base + left * size) > 0)) {
			++left;
		}

		while ((left < right) && (comparator (base, &base + right * size) <= 0)) {
			--right;
		}

		if (left >= right) {
			break;
		}

		swap(&base + left * size, &base + right * size, size);
		++left;
		--right;
	}

	right = left--;

	swap(&base, &base + left *size, size);

	qsort(base, left, size, comparator);

	qsort (&base + right * size, num - right, size, comparator);
}


static char* chars = "0123456789ABCDEF";

char* sztoa(size_t value, char* str, int base)
{
	if (base < 2 || base > 16)
		return nullptr;
	unsigned int i = 0;
	do 
	{
		str[++i] = chars[value%base];
		value /= base;
	} while (value != 0);
	str[0] = '\0';
	for (unsigned int z = 0; z < i; ++z, --i)
	{
		char tmp = str[z];
		str[z] = str[i];
		str[i] = tmp;
	}
	return str;
}



