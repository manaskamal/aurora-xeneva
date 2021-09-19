//!  Copyright (C) Manas Kamal Choudhury 2021
//!  
//! /PROJECT - Aurora's Xeneva
//! /AUTHOR  - Manas Kamal Choudhury
//!
//! =============================================

#ifndef _STDDEF_H
#define _STDDEF_H

#ifndef NULL
	#define NULL	0
#endif

typedef int       	ptrdiff_t;
#ifdef SIZE_T
typedef unsigned  	size_t;
#endif
typedef int       	ssize_t;
typedef unsigned	wint_t;

#if !defined(__cplusplus)
typedef unsigned	wchar_t;
#endif

#endif

