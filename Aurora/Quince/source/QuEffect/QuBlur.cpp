///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  QuBlur.cpp -- Blur effect
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!================================================

#include <QuEffect\QuBlur.h>
#include <canvas.h>
#include <color.h>

void QuShiftImage (unsigned char* img, int s_x, int s_y ,int w, int h) {
	for (int j = 0; j < h; ++j) {
		int mod = (j + s_y) % h;
		for (int i = 0; i < w; ++i) {
			int imod = (i + s_x) % w;
			img[mod * w + imod] = img[j * w + i];
		}
	}
}


///!  QuBlur -- Blurs an image 
///!
///!  @param input -- The input image buffer
///!  @param output -- The output image buffer
///!  @param w -- The width of the image
///!  @param h -- The height of the image
void QuBlur (unsigned char* input, unsigned char* output,int cx, int cy, int w, int h) {
	int red, green, blue = 0;

	uint64_t sum = 0;
	for (int j = 0; j <h;j++) {
		for (int i = 0;i < w;i++) {

			if (i < 1 || j < 1 || i + 1 == w || j + 1 == h)
				continue;

			sum = input[(cx + i -1)+(cy+j-1)*w] +
				  input[(cx+i+0)+(cy+j-1)*w] +
				  input[(cx+i+1)+(cy+j-1)*w] +
				  input[(cx+i-1)+(cy+j+0)*w] +
				  input[(cx+i+0)+(cy+j+0)*w] +
				  input[(cx+i+1)+(cy+j+0)*w] +
				  input[(cx+i-1)+(cy+j+1)*w] +
				  input[(cx+i+0)+(cy+j+1)*w] +
				  input[(cx+i+1)+(cy+j+1)*w] ;

			//SET_ALPHA(sum,0xFF);
	        output[(cx + i) +(cy + j)*w]= sum/9;
		}
	
	}

}

void QuIntensitySet (float value,unsigned char *img,int x, int y, int w, int h) {
	float invDiv = 1 / value;
	for (int i = 0; i <  h; i++) {
		for (int j = 0; j < w*4; j++)
			img[((y + i) * w + x + j)] *= invDiv;
	}
}