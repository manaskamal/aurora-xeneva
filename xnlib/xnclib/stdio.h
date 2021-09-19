///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  stdio.h -- Standard C Library
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!===============================================

#ifndef __STDIO_H__
#define __STDIO_H__

#define _FILE    int

#define stdin  0
#define stdout 1
#define stderr  2

extern int fprintf(_FILE, const char *, ...);
extern int printf(const char *, ...);
#endif