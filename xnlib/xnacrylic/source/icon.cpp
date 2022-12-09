/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2022, Manas Kamal Choudhury
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 **/

#include <icon.h>
#include <stdlib.h>
#include <canvas.h>
#include <fastcpy.h>
#include <sys\_term.h>
#include <sys\shm.h>
#include <sys\_file.h>
#include <jpg\jpeg_decoder.h>
#include <image.h>
/*
 * create_icon -- creates a icon bitmap buffer segment
 * @param w -- width of the bitmap
 * @param h -- height of the bitmap
 */
XE_EXTERN XE_EXPORT icon_t * create_icon (int w, int h) {
	icon_t *icon = (icon_t*)malloc(sizeof(icon_t));
	icon->w = w;
	icon->h = h;
	return icon;
}

/*
 * icon_open_from_file -- open the bitmap icon from file
 * supported format are .bmp & .jpg 
 * @param icon -- pointer to icon
 * @param filename -- image file name
 */
XE_EXTERN XE_EXPORT void icon_open_from_file (icon_t* icon,char* filename) {
	icon_file *file = (icon_file*)malloc(sizeof(icon_t));
	UFILE ustream;
	int fd = sys_open_file (filename,&ustream);
	file->fildesc = fd;
	file->buffer = (uint8_t*)malloc(ustream.size);
	file->size = ustream.size;
	file->type = ICON_TYPE_BMP;
	icon->file = file;
	sys_read_file (fd, file->buffer,&ustream);
}


/*
 * icon_free_file -- frees an opened image file 
 * @param icon -- pointer to icon image structure
 */
XE_EXTERN XE_EXPORT void icon_free_file (icon_t *icon) {
	sys_close_file(icon->file->fildesc);
	free(icon->file->buffer);
	free(icon->file);
	icon->file = NULL;
}

/*
 * sh_bitmap_destroy -- destroys a shared bitmap buffer
 * @param shbitmap -- pointer to shared bitmap buffer
 */
XE_EXTERN XE_EXPORT void icon_destroy (icon_t* icon) {
	free(icon);
}




/*
 * icon_draw_jpg -- finally decode jpg and draws the image into
 * icon buffer
 * @param canvas -- Pointer to system canvas
 * @param icon -- Pointer to icon
 */
void icon_draw_jpg (canvas_t *canvas, icon_t* icon, int x, int y) {
	if (icon->file->buffer != NULL){
		
		Jpeg::Decoder *decoder = new Jpeg::Decoder(icon->file->buffer, icon->file->size, malloc, free);
		if (decoder->GetResult() != Jpeg::Decoder::OK) {
			sys_print_text ("JPEG: Decoder error\n");
			return;
		}

		uint8_t* data = icon->file->buffer;
		uint32_t w = decoder->GetWidth();
		uint32_t h = decoder->GetHeight();

		//sys_print_text ("JPG: W -> %d, H -> %d \r\n", w, h);
		for (int i = 0; i < h; i++) {
			for (int k = 0; k < w; k++) {
				int j = k + i * w;
				uint8_t r = data[j * 3];   
				uint8_t g = data[j * 3 + 1];        
				uint8_t b = data[j * 3 + 2];       
			   // uint8_t a = data[j * 3 + 3];
				uint32_t rgba =  ((r<<16) | (g<<8) | (b)) & 0x00ffffff;  //0xFF000000 | (r << 16) | (g << 8) | b;
				rgba = rgba | 0xff000000;
				canvas_draw_pixel(canvas, x + k, y + i,rgba);
				j++;
			}
		}
	}
}

/*
 * icon_draw_bmp -- finally decode bmp images and draws the image into
 * icon buffer
 * @param canvas -- Pointer to system canvas
 * @param icon -- Pointer to icon
 */
void icon_draw_bmp (canvas_t *canvas, icon_t* icon, int x, int y) {

	bitmap_img_t* file_header = (bitmap_img_t*)icon->file->buffer;
	unsigned int offset = file_header->off_bits;

	if (file_header->type != 0x4d42) {
		sys_print_text ("BMP Type -> %x \r\n", file_header->type);
		return;
	}
	

	bitmap_info_t *info = (bitmap_info_t*)(icon->file->buffer + sizeof(bitmap_img_t));
	uint32_t width = info->biWidth;
	uint32_t height = info->biHeight;
	
	int bpp = info->biBitCount;

	icon->w = width;
	icon->h = height;
	icon->bpp = bpp;

	uint8_t* image = (uint8_t*)(icon->file->buffer + offset);
	
	int j = 0;

	//uint8_t* image = bmp->image_data;
	for(int i=0; i < height; i++) {
		char* image_row = (char*)image + (height - i - 1) * (width * 4);
		int h = height -1 - i;
		j = 0;
		for (int k = 0; k < width; k++) {
			uint32_t b = image_row[j++] & 0xff;
			uint32_t g = image_row[j++] & 0xff;
			uint32_t r = image_row[j++] & 0xff;
			uint32_t a = image_row[j++] & 0xff;
			uint32_t rgb = ((a<<24) | (r<<16) | (g<<8) | (b));
			if (rgb & 0xFF000000)
				canvas_draw_pixel (canvas,x + k,y +  i,rgb);
		}
	}
}
