/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  iodev.h -- Input Output Device Specific system call
 *
 *  /PROJECT - Aurora Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ==========================================================
 */

#ifndef __IODEV_H__
#define __IODEV_H__

#include <stdint.h>
#include <string.h>

extern void iodev (int function, int code, void* arg);

#endif