/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  limits.h -- Standard limit header
 *
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ===============================================
 */

#ifndef _LIMITS_H
#define _LIMITS_H

#define CHAR_BIT     8                      // Bits in a char

#define SCHAR_MAX    127                    // Max value of a signed char
#define SCHAR_MIN    -128                   // Min value of a signed char

// Assumes that a char type is signed
#define CHAR_MAX     SCHAR_MAX              // Max value of a char
#define CHAR_MIN     SCHAR_MIN              // Min value of a char
#define UCHAR_MAX    255                    // Max value of an unsigned char

// Assumes that a short int type is 16 bits
#define SHRT_MAX     32767                  // Max value of a short int
#define SHRT_MIN     -32768                 // Min value of a short int
#define USHRT_MAX    65535                  // Max value of an unsigned short

// Assumes that an int type is 32 bits
#define INT_MAX      2147483647             // Max value of an int
#define INT_MIN      (-INT_MAX - 1)         // Min value of an int
#define UINT_MAX     4294967295U            // Max value of an unsigned int

// Assumes that a long int type is 32 bits
#define LONG_MAX     2147483647L            // Max value of a long int
#define LONG_MIN     (-LONG_MAX - 1L)       // Min value of a long int
#define ULONG_MAX    4294967295UL           // Max value of an unsigned long

// Maximum multibyte characters length
#define MB_LEN_MAX   4

#endif

