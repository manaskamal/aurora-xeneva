///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuBlur.h -- Blur effect implementation
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!==============================================

#ifndef __QU_BLUR_H__
#define __QU_BLUR_H__

#include <stdint.h>

extern void QuBlur (unsigned char* input, unsigned char* output,int x, int y, int w, int h);
#endif