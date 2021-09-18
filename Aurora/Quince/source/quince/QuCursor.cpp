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
#include <QuCanvas\QuCanvasMngr.h>
#include <stdint.h>
#include <canvas.h>
#include <bmp_image.h>
#include <stdlib.h>
#include <sys\mmap.h>
#include <sys\ioquery.h>
#include <string.h>

uint32_t *CursorBack;//[24*24];
unsigned char* MouseData = NULL;
unsigned QuOldX, QuOldY = 0;
unsigned QuNewX, QuNewY = 0;
QuBitmap *bmp;

void QuHwDrawCursor (unsigned x, unsigned y, uint32_t color) {
	uint32_t *lfb =  (uint32_t*)0x0000070000001000;      
	lfb[x + y * 24] = color;
}


void QuHwCursorPrepare () {
	valloc (0x0000070000001000);

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
				QuHwDrawCursor(0 + k,0 +  i,rgb);
		}
	}
}


void QuCursorInit (unsigned x, unsigned y, int type) {
	bmp = (QuBitmap*)malloc(sizeof(QuBitmap));
	CursorBack = (uint32_t*)malloc(8192);
	//! Store Current pixels
	for (int w = 0; w < 24; w++) {
		for (int h = 0; h < 24; h++) {
			CursorBack[h * 24 + w] = canvas_get_pixel(x+ w,y+ h); //QuCanvasGetPixel((uint32_t*)0x0000600000000000, x, y); //
		}
	}

	if (type == QU_CURSOR_ARROW)
		QuinceDrawBmp ("a:cursor.bmp", x, y, bmp);
	else 
		QuinceDrawBmp ("a:cursor.bmp", x, y, bmp);

	MouseData = (unsigned char*)0x0000070000000000;

#ifdef HW_CURSOR
	QuHwCursorPrepare();
	QuMoveCursor(0,0);
#endif
}


void QuCursorCoord (unsigned x, unsigned y) {
	QuOldX = x;
	QuOldY = y;
}


void QuPutBackStore (unsigned x, unsigned y) {
	
	  for (int w = 0; w < 24; w++) {
		  for (int h = 0; h < 24; h++) {
			  canvas_draw_pixel(x+w,y+h,CursorBack[h * 24+ w]);//CursorBack[h * 24+ w]
			 // QuCanvasPutPixel ((uint32_t*)0x0000600000000000, x, y, CursorBack[h * 24 + w]);
		  }
	  }
}


void QuStoreBack (unsigned x, unsigned y) {
	for (int w = 0; w < 24; w++) {
		for (int h = 0; h < 24; h++) {
			CursorBack[h * 24 + w] =  canvas_get_pixel(x + w, y + h);//QuCanvasGetPixel((uint32_t*)0x0000600000000000, x+ w,y+ h);
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

void QuCursorNewCoord (unsigned x, unsigned y) {
	QuNewX = x;
	QuNewY = y;
}

void QuMoveCursor (unsigned x, unsigned y) {
#ifdef SW_CURSOR
	QuPutBackStore (QuOldX, QuOldY);
	canvas_screen_update(QuOldX, QuOldY, 24,24);
	QuCursorCoord (x, y);
	QuStoreBack (x, y);
	QuDrawCursor (bmp, x, y);
	QuNewX = x;
	QuNewY = y;
#endif

#ifdef HW_CURSOR
	svga_io_query_t ioq;
	ioq.value = x;
	ioq.value2 = y;
	ioq.value6 = QU_CURSOR_ARROW;
	ioquery(IO_QUERY_SVGA, SVGA_MOVE_CURSOR, &ioq);
#endif
}


unsigned QuCursorGetNewX() {
	return QuNewX;
}


unsigned QuCursorGetNewY() {
	return QuNewY;
}