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

	int sum;
	for (int i = 1; i <w; i++) {
		for (int j = 1;j < h; j++) {
			sum = input[(cx + i -1)*canvas_get_width()+(cy+j+1)] +
				  input[(cx+i+0)*canvas_get_width()+(cy+j+1)] +
				  input[(cx+i+1)*canvas_get_width()+(cy+j+1)] +
				  input[(cx+i-1)*canvas_get_width()+(cy+j+0)] +
				  input[(cx+i+0)*canvas_get_width()+(cy+j+0)] +
				  input[(cx+i+1)*canvas_get_width()+(cy+j+0)] +
				  input[(cx+i-1)*canvas_get_width()+(cy+j-1)] +
				  input[(cx+i+0)*canvas_get_width()+(cy+j-1)] +
				  input[(cx+i+1)*canvas_get_width()+(cy+j-1)] ;

	        output[(cx+ i + 1)  *canvas_get_width() +(cy+j+1)]= sum /9;
			
		}
	
	}


}