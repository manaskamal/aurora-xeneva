/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  user64.h -- User Level code for arch x86_64 
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *====================================================
 */

#ifndef __USER64_H__
#define __USER64_H__

#include <stdint.h>
#include <stdio.h>
#include <arch\x86_64\cpu.h>


#define IA32_EFER 0xC0000080
#define IA32_STAR 0xC0000081
#define IA32_LSTAR 0xC0000082
#define IA32_CSTAR 0xC0000083
#define IA32_SFMASK 0xC0000084

#define IA32_SYSENTER_CS 0x174
#define IA32_SYSENTER_ESP 0x175
#define IA32_SYSENTER_EIP 0x176

#define IA32_EFLAGS_INTR (1<<9)
#define IA32_EFLAGS_DIRF (1<<10)

extern void initialize_syscall ();
extern void initialize_user_land (size_t bit);
extern "C" TSS* get_kernel_tss ();
#endif