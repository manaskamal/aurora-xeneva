///
///  Copyright (C) Manas Kamal Choudhury 2021
///
/// bmp_image -- Bitmap Image 
///
/// /PROJECT - Aurora's Xeneva
/// /AUTHOR  - Manas Kamal Choudhury
///
/// ==============================================

#ifndef __BMP_IMAGE_H__
#define __BMP_IMAGE_H__

#pragma pack (push, 1)
typedef struct _bmp_{
	unsigned short type;   //0x4d42
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

typedef struct _BITMAP_ {
	unsigned char* image_data;
	int width;
	int height;
}QuBitmap;

//!============================================
//! Draws Bitmap Image from files
//!
//! @param filename -- Path of the file
//!
//!============================================
extern void QuinceDrawBmp (const char* filename, unsigned x, unsigned y, QuBitmap *bmp);

#endif