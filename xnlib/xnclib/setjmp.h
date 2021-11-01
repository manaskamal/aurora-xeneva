///! Copyright (C) Manas Kamal Choudhury 2021
///!
///! setjmp.h -- setjmp implementation
///!
///! /PROJECT - Aurora's Xeneva
///! /AUTHOR - Manas Kamal Choudhury
///!

#ifndef __SETJMP_H__
#define __SETJMP_H__



typedef long long int __jmp_buf[8];


typedef struct __jmp_buf_tag {
	__jmp_buf __jb;
	unsigned long __fl;
	unsigned long __ss[128/sizeof(long)];
} jmp_buf[1];

extern int setjmp (jmp_buf);
extern void longjmp(jmp_buf, int);

#endif