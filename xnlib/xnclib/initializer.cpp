/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  initializer -- Initializes all functions prior to the start of 
 *                 application
 *
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ===================================================================
 */

#include <stdlib.h>
#include <stdint.h>

void* __cdecl ::operator new(size_t size) {
	return malloc(size);
}

void* __cdecl operator new[] (size_t size) {
	return malloc(size);
}

void __cdecl operator delete (void* p) {
	free(p);
}

void __cdecl operator delete[] (void* p) {
	free(p);
}

