/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  stdlib.h -- Standard Functions 
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ===========================================
 */

#ifndef __STDLIB_H__
#define __STDLIB_H__

#include <stdint.h>

//! Converts a given integer or hex-decimal value to string value
extern char* sztoa(size_t value, char* str, int base);

extern void atow(char* buf, const char* source);
#endif