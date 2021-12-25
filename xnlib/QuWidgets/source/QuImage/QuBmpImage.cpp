/**
 * Copyright (C) Manas Kamal Choudhury 2021
 *
 * QuBmpImage -- Bitmap Image (24 bit)
 *
 * /PROJECT - Aurora's Xeneva v1.0
 * /AUTHOR  - Manas Kamal Choudhury
 *
 */

#include <QuImage\QuBmpImage.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys\_term.h>

/**
 * Bitmap Image Format
 */
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


/**
 * QuGetBmp -- returns pointer to the actual image
 * @param data -- the data from where to read
 */
QuBmpImage* QuGetBMP (unsigned char* data) {
	QuBmpImage *bmp = (QuBmpImage*)malloc(sizeof(QuBmpImage));

	bitmap_img* file_header = (bitmap_img*)data;
	unsigned int offset = file_header->off_bits;

	bitmap_info *info = (bitmap_info*)(data + sizeof(bitmap_img));
	int width = info->biWidth;
	int height = info->biHeight;
	

	int bpp = info->biBitCount;

	void* image_bytes = (void*)(data + offset);
	int j=0;
	
    uint8_t *image = (uint8_t*)image_bytes;
	bmp->raw_data = image;
	bmp->w = width;
	bmp->h = height;
	return bmp;
}


/**
 * QuDrawBMP -- Draws the actual image to given canvas
 * @param canvas -- the canvas to use for drawing
 * @param image -- The bitmap image
 * @param x -- the x coordinate
 * @param y -- the y coordinate
 */
void QuDrawBMP (canvas_t *canvas, QuBmpImage *image, int x, int y) {
	int width = image->w;
	int height = image->h;
	int j = 0;
	for(int i=0; i < height; i++) {
		char* image_row = (char*)image->raw_data + (height - i - 1) * (width * 4);
		int h = height -1 - i;
		j = 0;
		for (int k = 0; k < width; k++) {
			uint32_t b = image_row[j++] & 0xff;
			uint32_t g = image_row[j++] & 0xff;
			uint32_t r = image_row[j++] & 0xff;
			uint32_t a = image_row[j++] & 0xff;
			uint32_t rgb = ((a<<24) | (r<<16) | (g<<8) | (b));
			//rgb = rgb | 0xff000000;
			//fb_row[100 + 100] = rgb;
			if (rgb & 0xFF000000)
				canvas_draw_pixel(canvas,x + k,y +  i,rgb);
		}
	}
}
