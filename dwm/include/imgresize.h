/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  imgresize.h -- Resize algorithm
 *
 *  /PROJECT - Aurora Xeneva {DWM}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ===============================================
 */

#ifndef __IMAGE_RESIZE_H__
#define __IMAGE_RESIZE_H__

#include <stdtypes.h>

extern void resize_bilinear (uint32_t result_buffer, uint8_t* source_data, int new_width, int new_height);
#endif