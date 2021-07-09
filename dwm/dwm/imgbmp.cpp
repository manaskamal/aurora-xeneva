/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  imgbmp.cpp -- 24-bit bitmap image decoder
 *
 *  /PROJECT - DWM {Aurora Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *================================================
 */

#include <imgbmp.h>
#include <sys.h>

static int bmp_width = 0;
static int bmp_height = 0;

void draw_pixel3_wallp (unsigned x, unsigned y, uint32_t color ) {
	uint32_t *lfb = (uint32_t*)0x0000500000000000;
	lfb[x + y * get_screen_width()] = color;
}


void draw_bmp_image (unsigned char* data, int x, int y) {
	bitmap_img* file_header = (bitmap_img*)data;
	unsigned int offset = file_header->off_bits;

	bitmap_info *info = (bitmap_info*)(data + sizeof(bitmap_img));
	int width = info->biWidth;
	int height = info->biHeight;
	bmp_width = width;
	bmp_height = height;

	int bpp = info->biBitCount;

	void* image_bytes = (void*)(data + offset);
	int j=0;
	
    uint8_t *image = (uint8_t*)image_bytes;
	
	
	for(int i=0; i < height; i++) {
		char* image_row = (char*)image + (height - i - 1) * (width * 3);
		//uint32_t* fb_row = (uint32_t*)get_framebuffer() + (height - 1 - i ) * (width*3);
		int h = height -1 - i;
		j = 0;
		for (int k = 0; k < width; k++) {
			uint32_t b = image_row[j++] & 0xff;
			uint32_t g = image_row[j++] & 0xff;
			uint32_t r = image_row[j++] & 0xff;
			uint32_t rgb = ((r<<16) | (g<<8) | (b)) & 0x00ffffff;
			rgb = rgb | 0xff000000;
			//fb_row[100 + 100] = rgb;
			draw_pixel3_wallp(x + k,y +  i,rgb);
		}
	}

}


int bmp_get_width () {
	return bmp_width;
}

int bmp_get_height () {
	return bmp_height;
}
