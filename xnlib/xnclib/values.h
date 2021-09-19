///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  values.h -- Standard C Library
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!==================================================

#ifndef _VALUES_H
#define _VALUES_H

#include <limits.h>
#include <float.h>

#define CHARBITS        (sizeof(char) * CHAR_BIT)
#define SHORTBITS       (sizeof(short int) * CHAR_BIT)
#define INTBITS	        (sizeof(int) * CHAR_BIT)
#define LONGBITS        (sizeof(long int) * CHAR_BIT)
#define PTRBITS	        (sizeof(char *) * CHAR_BIT)
#define DOUBLEBITS      (sizeof(double) * CHAR_BIT)
#define FLOATBITS       (sizeof(float) * CHAR_BIT)

#define MINSHORT        SHRT_MIN
#define	MININT          INT_MIN
#define	MINLONG         LONG_MIN

#define	MAXSHORT        SHRT_MAX
#define	MAXINT          INT_MAX
#define	MAXLONG         LONG_MAX

#define HIBITS          MINSHORT
#define HIBITL          MINLONG

#define	MAXDOUBLE       DBL_MAX
#define	MAXFLOAT        FLT_MAX
#define	MINDOUBLE       DBL_MIN
#define	MINFLOAT        FLT_MIN
#define	DMINEXP         DBL_MIN_EXP
#define	FMINEXP         FLT_MIN_EXP
#define	DMAXEXP         DBL_MAX_EXP
#define	FMAXEXP         FLT_MAX_EXP
#define BITSPERBYTE     CHAR_BIT

#endif

