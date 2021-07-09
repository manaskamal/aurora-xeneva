/**
 * Copyright (C) Manas Kamal Choudhury 2021
 *
 * exception.h -- Processor trap gate
 *
 * /PROJECT - Aurora {Xeneva v1.0 }
 * /AUTHOR  - Manas Kamal Choudhury
 *
 *================================================
 */

#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <stdint.h>
#include <stdio.h>
#include <arch\x86_64\cpu.h>

//!Initializes all exception handlers
extern  void exception_init ();
#endif