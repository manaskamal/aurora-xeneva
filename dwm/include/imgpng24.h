/**
 * Copyright (C) Manas Kamal Choudhury 2021
 *
 * imgpng24.h -- 24-Bit PNG Image decoder
 *
 * /PROJECT - DWM {Aurora Xeneva}
 * /AUTHOR  - Manas Kamal Choudhury
 *
 * ============================================
 */

#ifndef __IMG_PNG24_H__
#define __IMH_PNG24_H__

#include <stdtypes.h>

extern "C" size_t swap_byte (uint64_t value);

#pragma pack (push, 1)
typedef struct _png_chunk_ {
	uint32_t length;
	uint32_t type;
	uint8_t  data[4];
	uint32_t crc;
}png_chunk_t;


typedef struct _png_chunk_ihdr_ {
	png_chunk_t hdr;
	uint32_t    width;
	uint32_t    height;
	uint8_t     bit_depth;
	uint8_t     color_type;
	uint8_t     compression;
	uint8_t     filter;
	uint8_t     interlace;
} png_chunk_ihdr_t;

#pragma pack (pop)

#define PNG_CHUNK(a,b,c,d)  ((a) | ((b) << 8) | ((c) << 16) | ((d) << 24))
#define PNG_IHDR            PNG_CHUNK('I','H','D','R')
#define PNG_IDAT            PNG_CHUNK('I','D','A','T')
#define PNG_IEND            PNG_CHUNK('I','E','N','D')

extern png_chunk_ihdr_t * png_header (void *png_data);
#endif