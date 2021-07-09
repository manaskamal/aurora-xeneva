/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  imgbmp.h -- Bitmap Image reader
 *
 *  /PROJECT - Aurora {Xeneva} DWM
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *==============================================
 */

#ifndef __IMG_BMP_H__
#define __IMG_BMP_H__

#include <stdtypes.h>

#pragma pack (push, 1)
typedef struct _bmp_{
	uint16_t type;   //0x4d42
	unsigned int size;
	unsigned short resv1;
	unsigned short resv2;
	unsigned int off_bits;
} bitmap_img;


typedef struct _info_ {
	unsigned int biSize;
	long biWidth;
	long biHeight;
	unsigned short biPlanes;
	unsigned short biBitCount;
	unsigned int biCompression;
	unsigned int biSizeImage;
	long biXPelsPerMeter;
	long biYPelsPerMeter;
	unsigned int biClrUsed;
	unsigned int biClrImportant;
} bitmap_info;

#pragma pack(pop)

extern void draw_bmp_image (unsigned char* data, int x, int y);
extern int bmp_get_width ();
extern int bmp_get_height ();
#endif
