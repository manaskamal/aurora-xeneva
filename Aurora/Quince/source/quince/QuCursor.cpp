///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!  
///!  QuCursor -- Quince Cursor
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!==============================================

#include <QuCursor.h>
#include <stdint.h>
#include <canvas.h>
#include <bmp_image.h>
#include <stdlib.h>

uint32_t *CursorBack;//[24*24];
unsigned char* MouseData = NULL;
unsigned QuOldX, QuOldY = 0;
unsigned QuNewX, QuNewY = 0;
QuBitmap *bmp;

void QuCursorInit (unsigned x, unsigned y, int type) {
	bmp = (QuBitmap*)malloc(sizeof(QuBitmap));
	CursorBack = (uint32_t*)malloc(8192);
	//! Store Current pixels
	for (int w = 0; w < 24; w++) {
		for (int h = 0; h < 24; h++) {
			CursorBack[h * 24 + w] = canvas_get_pixel(x+ w,y+ h);
		}
	}

	if (type == QU_CURSOR_ARROW)
		QuinceDrawBmp ("a:cursor.bmp", x, y, bmp);
	else 
		QuinceDrawBmp ("a:cursor.bmp", x, y, bmp);

	MouseData = (unsigned char*)0x0000070000000000;

	QuCursorCoord (x, y);
}


void QuCursorCoord (unsigned x, unsigned y) {
	QuOldX = x;
	QuOldY = y;
}


void QuPutBackStore (unsigned x, unsigned y) {
	
	  for (int w = 0; w < 24; w++) {
		  for (int h = 0; h < 24; h++) {
			   canvas_draw_pixel(x+w,y+h,CursorBack[h * 24+ w]);
		  }
	  }
}

void QuStoreBack (unsigned x, unsigned y) {
	for (int w = 0; w < 24; w++) {
		for (int h = 0; h < 24; h++) {
			CursorBack[h * 24 + w] = canvas_get_pixel(x+ w,y+ h);
		}
	}
}


void QuDrawCursor (QuBitmap *bmp, unsigned x, unsigned y) {
	int width = bmp->width;
	int height = bmp->height;
	int j = 0;
	uint8_t* image = bmp->image_data;
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

void QuMoveCursor (unsigned x, unsigned y) {
	QuPutBackStore (QuOldX, QuOldY);
	canvas_screen_update(QuOldX, QuOldY, 24,24);
	QuCursorCoord (x, y);
	QuStoreBack (x, y);
	QuDrawCursor (bmp, x, y);
	QuNewX = x;
	QuNewY = y;
	//canvas_screen_update(x, y, 24, 24);
}


unsigned QuCursorGetNewX() {
	return QuNewX;
}


unsigned QuCursorGetNewY() {
	return QuNewY;
}