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

			sum = input[(cx + i -1)+(cy+j-1)*canvas_get_width()] +
				  input[(cx+i+0)+(cy+j-1)*canvas_get_width()] +
				  input[(cx+i+1)+(cy+j-1)*canvas_get_width()] +
				  input[(cx+i-1)+(cy+j+0)*canvas_get_width()] +
				  input[(cx+i+0)+(cy+j+0)*canvas_get_width()] +
				  input[(cx+i+1)+(cy+j+0)*canvas_get_width()] +
				  input[(cx+i-1)+(cy+j+1)*canvas_get_width()] +
				  input[(cx+i+0)+(cy+j+1)*canvas_get_width()] +
				  input[(cx+i+1)+(cy+j+1)*canvas_get_width()] ;

			//SET_ALPHA(sum,0xFF);
	        output[(cx + i) +(cy + j) *canvas_get_width() ]= sum/9;
		}
	
	}

}