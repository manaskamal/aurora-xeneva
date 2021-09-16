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





