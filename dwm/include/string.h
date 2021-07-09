/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  string.h -- String and memory management
 *
 *  /PROJECT - DWM { Desktop Window Manager }
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * =============================================
 */

#ifndef __STRING_H__
#define __STRING_H__

#include <stdtypes.h>


extern void *memcpy(void *dest, void *src, size_t count);
extern void memset(void *targ, uint8_t val, uint32_t len);


#endif