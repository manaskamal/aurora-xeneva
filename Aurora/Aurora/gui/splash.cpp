///!   
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   splash.cpp -- Splash Screen
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///!
///!================================================

#include <gui\splash.h>
#include <screen.h>
#include <vfs.h>
#include <mm.h>
#include <drivers\svga\vmsvga.h>

void gui_draw_pixels (unsigned x, unsigned y, uint32_t color) {
	uint32_t *lfb = get_framebuffer_addr();
	lfb[x + y * get_screen_width()] = color;
}

void start_boot_screen () {
	x64_cli();
	FILE f = open("a:bs.jpg");
	for (int i = 0; i < (48*1024)/4096; i++)
		map_page((uint64_t)pmmngr_alloc(), 0x0000000060000000 + i * 4096);
	unsigned char* buffer_i = (unsigned char*)0x0000000060000000;
	read (&f,buffer_i,f.size, f.id);

	Jpeg::Decoder *decoder = new Jpeg::Decoder(buffer_i, f.size, malloc, mfree);
	if (decoder->GetResult() != Jpeg::Decoder::OK) {
		printf ("JPEG:Decoder Error\n");
	}
	//
	//uint8_t* data = decoder->GetImage();
	//for (int i = 0; i < decoder->GetHeight(); i++) {
	//	for (int k = 0; k < decoder->GetWidth(); k++) {
	//		int j = k + i * decoder->GetWidth();
	//		uint8_t r = data[j * 3];        //data[i * 3];
	//		uint8_t g = data[j * 3 + 1];        //data[i * 3 + 1];
	//		uint8_t b = data[j * 3 + 2];       //data[i * 3 + 2];
	//		uint32_t rgb =  ((r<<16) | (g<<8) | (b)) & 0x00ffffff;  //0xFF000000 | (r << 16) | (g << 8) | b;
	//		rgb = rgb | 0xff000000;

	//		gui_draw_pixels(0 + k, 0 + i,rgb);
	//		j++;
	//	}
	//}

	//svga_update(0,0,get_screen_width(), get_screen_height());
	x64_sti();
}