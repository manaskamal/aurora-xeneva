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


void* malloc (size_t s) {
	return _malloc(s);
}

void free (void* ptr) {
	return _free(ptr);
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
	return (num_bytes;
}



//! NOT IMPLEMENTED
int rand () {
	return 1;
}



