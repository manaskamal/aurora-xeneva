/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  amd_am79c973.h -- AMD PCNet FAST III card driver
 *
 *  /PROJECT - Aurora Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ========================================================
 */

#ifndef __AMD_AM79C973_H__
#define __AMD_AM79C973_H__

#include <stdint.h>
#include <drivers\pci.h>
#include <hal.h>

#define APROM0   0x00
#define APROM2    0x02
#define APROM4    0x04
#define RDP       0x10
#define RAP       0x12
#define RESET     0x14
#define BDP       0x16


extern void amd_pcnet_initialize ();
#endif