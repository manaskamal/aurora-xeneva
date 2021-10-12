///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   QuWallpaper.h -- Quince Wallpaper Manager
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///!
///! =================================================

#include <QuWidget\QuWallpaper.h>
#include <QuCanvas\QuCanvasMngr.h>
#include <canvas.h>
#include <stdlib.h>
#include <sys\_term.h>
#include <color.h>

QuWallpaper *wallpaper;


void QuWallpaperPixel (unsigned x, unsigned y, uint32_t color) {
	uint32_t *lfb = (uint32_t*)wallpaper->buffer;      
	lfb[x + y * canvas_get_scale()] = color;
}


Image* QuWallpaperInit (const char* filename) {

	wallpaper = (QuWallpaper*)malloc (sizeof(QuWallpaper));

	unsigned w = canvas_get_width  ();
	unsigned h = canvas_get_height ();

	for (int i = 0; i < (w * h * 32) / 4096; i++) 
		valloc(0x0000060000000000 + i * 4096);

	for (int i = 0; i < (w * h * 32) / 4096; i++) 
		valloc(0x0000060000400000 + i * 4096);

	wallpaper->buffer = (unsigned char*)0x0000060000000000;
	wallpaper->w = w;
	wallpaper->h = h;
    Image *img;
	if (filename != NULL) {
		img = LoadImage (filename,(uint8_t*) 0x0000060000400000);
		CallJpegDecoder(img);
	} else {
		for (int i = 0; i < w; i++)
			for (int j = 0; j < h; j++)
				QuWallpaperPixel (0,0,LIGHTSILVER);
		img = (Image*)malloc(sizeof(Image));
		img->data = NULL;
	}

	ImageResizeBilinear((uint8_t*) 0x0000060000400000,img->width, img->height,w,h,(uint8_t*)0x0000060000000000);
	return img;
}

void QuWallpaperChange (const char* filename, uint32_t color) {
	//wallpaper = (QuWallpaper*)malloc (sizeof(QuWallpaper));

	unsigned w = canvas_get_width  ();
	unsigned h = canvas_get_height ();
    Image *img;

	if (filename != NULL) {
		img = LoadImage (filename,(uint8_t*) 0x0000060000000000);
		CallJpegDecoder(img);
	} else {
		for (int i = 0; i < w; i++)
			for (int j = 0; j < h; j++)
				QuWallpaperPixel (0 + i,0 + j,color);
		img = (Image*)malloc(sizeof(Image));
		img->data = NULL;
	}

//	QuWallpaperDraw(img);
	QuWallpaperPresent();
	QuCanvasSetUpdateBit(true);
}


void QuWallpaperDraw (Image *img) {
	unsigned x = 0;
	unsigned y = 0;

	if (img->data != NULL){
		uint8_t* data = img->image;
		uint32_t w = img->width;
		uint32_t h = img->height;
		for (int i = 0; i < h; i++) {
			for (int k = 0; k < w; k++) {
				int j = k + i * w;
				uint8_t r = data[j * 3];        //data[i * 3];
				uint8_t g = data[j * 3 + 1];        //data[i * 3 + 1];
				uint8_t b = data[j * 3 + 2];       //data[i * 3 + 2];
				//uint8_t a = data[j * 3 + 3];
				uint32_t rgba =  ((r<<16) | (g<<8) | (b)) & 0x00ffffff;  //0xFF000000 | (r << 16) | (g << 8) | b;
				rgba = rgba | 0xff000000;
				QuWallpaperPixel (x + k, y + i,rgba);
				j++;
			}
		}
	}
}

void QuWallpaperPresent () {
	uint32_t* lfb = (uint32_t*)0x0000600000000000;
	uint32_t* wallp = (uint32_t*)wallpaper->buffer;
	for (int i=0; i < wallpaper->w; i++) {
		for (int j=0; j < wallpaper->h; j++){
			uint32_t color_a = wallp[(0 + i) + (0 + j) * canvas_get_width()];
			lfb[(0 + i) + (0 + j) * canvas_get_width()] = color_a;
		}
	}
}