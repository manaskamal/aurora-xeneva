/**
 * Copyright (C) Manas Kamal Choudhury 2021
 *
 * QuBmpImage -- Bitmap Image (24 bit)
 *
 * /PROJECT - Aurora's Xeneva v1.0
 * /AUTHOR  - Manas Kamal Choudhury
 *
 */

#ifndef __QU_BMP_IMAGE_H__
#define __QU_BMP_IMAGE_H__

#include <stdint.h>
#include <canvas.h>


typedef struct _QuBmpImage_ {
	unsigned char* raw_data;
	int w;
	int h;
}QuBmpImage;

/**
 * QuGetBmp -- returns pointer to the actual image
 * @param data -- the data from where to read
 */
QuBmpImage* QuGetBMP(unsigned char* data);

/**
 * QuDrawBMP -- Draws the actual image to given canvas
 * @param canvas -- the canvas to use for drawing
 * @param image -- The bitmap image
 * @param x -- the x coordinate
 * @param y -- the y coordinate
 */
void QuDrawBMP (canvas_t *canvas, QuBmpImage* image, int x, int y);

#endif