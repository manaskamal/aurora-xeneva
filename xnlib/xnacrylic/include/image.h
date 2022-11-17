/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * =============================================
 */

#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <stdint.h>
#include <sys\_xeneva.h>

#pragma pack (push, 1)
typedef struct _bmp_img_{
	unsigned short type;   //0x4d42
	unsigned int size;
	unsigned short resv1;
	unsigned short resv2;
	unsigned int off_bits;
} bitmap_img_t;


typedef struct _bmp_info_ {
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
} bitmap_info_t;

#pragma pack(pop)


typedef struct _IMAGE_ {
	uint32_t width;
	uint32_t height;
	uint32_t size;
	uint8_t* data;
	uint8_t* image;
	int file_desc;
}Image;


XE_EXTERN XE_EXPORT Image* LoadImage (char* filename, uint8_t* address);
XE_EXTERN XE_EXPORT void FillImageInfo (Image *img, uint32_t w, uint32_t h);
XE_EXTERN XE_EXPORT void CallJpegDecoder (Image *img);
XE_EXTERN XE_EXPORT void ImageResizeBilinear (uint8_t* src,int src_w, int src_h, int new_w, int new_h, uint8_t* new_img);

#endif