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

#include <shbitmap.h>
#include <stdlib.h>
#include <canvas.h>
#include <fastcpy.h>
#include <sys\shm.h>

/*
 * create_shared_bitmap -- creates a shared bitmap buffer segment
 * @param key -- shm key
 * @param w -- width of the bitmap
 * @param h -- height of the bitmap
 */
XE_EXTERN XE_EXPORT shared_bitmap_t * create_sh_bitmap (uint32_t key,int w, int h) {
	shared_bitmap_t *shbitmap = (shared_bitmap_t*)malloc(sizeof(shared_bitmap_t));
	shbitmap->w = w;
	shbitmap->h = h;
	shbitmap->sh_key = key;
	uint32_t mem_id = sys_shmget(key,w*h*4,NULL);
	void* address = sys_shmat(mem_id,NULL, NULL);
	shbitmap->buffer = (uint32_t*)address;
	shbitmap->buf_unaligned = address;
	return shbitmap;
}

/*
 * sh_bitmap_open_from_file -- open the bitmap icon from file
 * supported format are .bmp & .jpg 
 * @param shbitmap -- pointer to shared bitmap
 * @param filename -- image file name
 */
XE_EXTERN XE_EXPORT void sh_bitmap_open_from_file (shared_bitmap_t* shbitmap,char* filename) {
	Image* image = LoadImage(filename,(uint8_t*)shbitmap->buf_unaligned);
	shbitmap->image = image;
}


/*
 * sh_bitmap_free_image -- frees an opened image from shared
 * memeory
 */
XE_EXTERN XE_EXPORT void sh_bitmap_free_image (shared_bitmap_t *shbitmap) {
	free(shbitmap->image);
}

/*
 * sh_bitmap_destroy -- destroys a shared bitmap buffer
 * @param shbitmap -- pointer to shared bitmap buffer
 */
XE_EXTERN XE_EXPORT void sh_bitmap_destroy (shared_bitmap_t* shbitmap) {
	sys_shm_unlink(shbitmap->sh_key);
	free(shbitmap);
}


/*
 * sh_bitmap_draw -- finally decode and draws the image into
 * shared memory buffer
 * @param canvas -- Pointer to system canvas
 * @param shbitmap -- Pointer to shbitmap
 */
void sh_bitmap_draw (canvas_t *canvas, shared_bitmap_t* shbitmap, int x, int y) {
	if (shbitmap->image != NULL){

		if (shbitmap->image->data == NULL)
			return;
		
		CallJpegDecoder(shbitmap->image);

		uint8_t* data = shbitmap->image->data;
		uint32_t w = shbitmap->image->width;
		uint32_t h = shbitmap->image->height;
		for (int i = 0; i < h; i++) {
			for (int k = 0; k < w; k++) {
				int j = k + i * w;
				uint8_t r = data[j * 3];        
				uint8_t g = data[j * 3 + 1];        
				uint8_t b = data[j * 3 + 2];       
			    uint8_t a = data[j * 3 + 3];
				uint32_t rgba =  ((r<<16) | (g<<8) | (b)) & 0x00ffffff;  //0xFF000000 | (r << 16) | (g << 8) | b;
				rgba = rgba | 0xff000000;
				canvas_draw_pixel(canvas,x + k, y + i,rgba);
				j++;
			}
		}
	}
}

/*
 * sh_bitmap_copy_to_canvas -- copies shared image data to canvas
 * @param canvas -- Pointer to canvas
 * @param shbitmap -- Pointer to shared bitmap structure
 * @param x -- X location relative to canvas plane
 * @param y -- Y location relative to canvas plane
 */
void sh_bitmap_copy_to_canvas (canvas_t* canvas, shared_bitmap_t *shbitmap, int x, int y) {
	for (int i = 0; i < shbitmap->h; i++)
		fastcpy (canvas->address + (y + i) * canvas->width + x,shbitmap->buffer + (0 + i) * shbitmap->w + 0, shbitmap->w * 4);
}