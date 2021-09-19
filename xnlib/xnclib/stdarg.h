///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  stdarg.h -- Standard C Library
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!=============================================

#ifndef __STDARG_H__
#define __STDARG_H__

typedef void * va_list;

#define va_start(list, lastpar)  ((list) = &lastpar)
#define va_arg(list, type) *((type*)((list) += sizeof(int)))
#define va_end(list) do {} while (0)

#endif