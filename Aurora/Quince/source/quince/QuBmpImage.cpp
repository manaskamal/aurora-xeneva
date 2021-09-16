//!
//!  Copyright (C) Manas Kamal Choudhury 2021
//!
//!  QuBmpImage -- Quince Bitmap Image File
//! 
//!  /PROJECT - Aurora's Xeneva
//!  /AUTHOR  - Manas Kamal Choudhury
//!
//! ==============================================

#include <bmp_image.h>
#include <sys\_file.h>
#include <sys\mmap.h>
#include <acrylic.h>
#include <canvas.h>

void QuinceDrawBmp (const char* filename, unsigned x, unsigned y, QuBitmap *bmp){
	 FILE f;
	 sys_open_file (&f, filename);
	 valloc(0x0000070000000000);
	 unsigned char* data = (unsigned char*)0x0000070000000000;
	 sys_read_file (&f,data, f.size);

	bitmap_img* file_header = (bitmap_img*)data;
	unsigned int offset = file_header->off_bits;

	bitmap_info *info = (bitmap_info*)(data + sizeof(bitmap_img));
	int width = info->biWidth;
	int height = info->biHeight;
	

	int bpp = info->biBitCount;

	void* image_bytes = (void*)(data + offset);
	int j=0;
	
    uint8_t *image = (uint8_t*)image_bytes;
	bmp->image_data = image;
	bmp->width = width;
	bmp->height = height;
	
	for(int i=0; i < height; i++) {
		char* image_row = (char*)image + (height - i - 1) * (width * 4);
		//uint32_t* fb_row = (uint32_t*)get_framebuffer() + (height - 1 - i ) * (width*3);
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
				canvas_draw_pixel(x + k,y +  i,rgb);
		}
	}

 }