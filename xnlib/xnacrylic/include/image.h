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

typedef struct _IMAGE_ {
	uint32_t width;
	uint32_t height;
	uint32_t size;
	uint8_t* data;
	uint8_t* image;
}Image;


extern Image* LoadImage (char* filename, unsigned char* address);
extern void FillImageInfo (Image *img, uint32_t w, uint32_t h);
extern void CallJpegDecoder (Image *img);
extern void ImageResizeBilinear (uint8_t* src,int src_w, int src_h, int new_w, int new_h, uint8_t* new_img);

#endif