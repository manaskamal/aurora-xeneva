/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * =============================================
 */

#include <image.h>
#include <sys\_file.h>
#include <stdlib.h>
#include <jpg\jpeg_decoder.h>
#include <sys\_term.h>


Image* LoadImage (const char* filename, unsigned char* data) {
	Image *img = (Image*)malloc (sizeof(Image));
	FILE f;
	sys_open_file (&f,filename);
	sys_read_file (&f, data, f.size);
	img->width = 0;
	img->height = 0;
	img->size = f.size;
	img->data = data;
	img->image = NULL;
	return img;
}


void FillImageInfo (Image *img, uint32_t w, uint32_t h) {
	img->width = w;
	img->height = h;
}


		
void  CallJpegDecoder (Image *img) {
	Jpeg::Decoder *decoder = new Jpeg::Decoder(img->data, img->size, malloc, free);
	if (decoder->GetResult() != Jpeg::Decoder::OK) {
		sys_print_text ("Decoder error\n");
	   return;
	}
	FillImageInfo (img, decoder->GetWidth(), decoder->GetHeight());
	img->image = decoder->GetImage();
}

void ImageResizeBilinear (uint8_t* src,int src_w, int src_h, int new_w, int new_h, uint8_t* new_img) {
	int a, b, c, d, x, y, index;

	float x_ratio = ((float)(src_w - 1))/new_w;
	float y_ratio = ((float)(src_h - 1))/new_h;

	float x_diff, y_diff, blue, red, green;

	int offset = 0;
	for (int i = 0; i < new_h; i++) {
		for (int j = 0; j < new_w; j++) {
			x = (int)(x_ratio * j);
			y = (int)(y_ratio * i);
			x_diff = (x_ratio * j) - x;
			y_diff = (y_ratio * i) - y;
			index = (y*src_w+x);

			a = src[index];
			b = src[index+1];
			c = src[index+src_w];
			d = src[index+src_w+1];

			 // blue element
            // Yb = Ab(1-w)(1-h) + Bb(w)(1-h) + Cb(h)(1-w) + Db(wh)
            blue = (a&0xff)*(1-x_diff)*(1-y_diff) + (b&0xff)*(x_diff)*(1-y_diff) +
                   (c&0xff)*(y_diff)*(1-x_diff)   + (d&0xff)*(x_diff*y_diff);

            // green element
            // Yg = Ag(1-w)(1-h) + Bg(w)(1-h) + Cg(h)(1-w) + Dg(wh)
            green = ((a>>8)&0xff)*(1-x_diff)*(1-y_diff) + ((b>>8)&0xff)*(x_diff)*(1-y_diff) +
                    ((c>>8)&0xff)*(y_diff)*(1-x_diff)   + ((d>>8)&0xff)*(x_diff*y_diff);

            // red element
            // Yr = Ar(1-w)(1-h) + Br(w)(1-h) + Cr(h)(1-w) + Dr(wh)
            red = ((a>>16)&0xff)*(1-x_diff)*(1-y_diff) + ((b>>16)&0xff)*(x_diff)*(1-y_diff) +
                  ((c>>16)&0xff)*(y_diff)*(1-x_diff)   + ((d>>16)&0xff)*(x_diff*y_diff);

        /*    #if BILINEAR_ALPHA
            alpha = ((a>>24)&0xff)*(1-x_diff)*(1-y_diff) + ((b>>24)&0xff)*(x_diff)*(1-y_diff) +
                    ((c>>24)&0xff)*(y_diff)*(1-x_diff)   + ((d>>24)&0xff)*(x_diff*y_diff);

            result[offset++] = 
                    ((((int)alpha)<<24)&0xff000000) |
                    ((((int)red)<<16)&0xff0000) |
                    ((((int)green)<<8)&0xff00) |
                    ((int)blue);
            #else*/
            new_img[offset++] = 
                    0xff000000 | // hardcode alpha
                    ((((int)red)<<16)&0xff0000) |
                    ((((int)green)<<8)&0xff00) |
                    ((int)blue);
		}
	}
}





