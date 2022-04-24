/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  console.h -- Virtual Console
 *
 *  /PROJECT - Aurora v1.0 {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *====================================================
 */

#include <console.h>
#include <stdio.h>
#include <string.h>
#include <arch\x86_64\mmngr\kheap.h>
#include <fs\vfs.h>
#include <fs\fat\fat.h>
#include <screen.h>

//! default kernel console
static uint16_t scanline = 0;
static uint16_t screen_width = 0;
static uint16_t screen_height = 0;
static uint32_t *fb = nullptr;
static int console_x = 0;
static int console_y = 0;
static uint64_t *psf_data = nullptr;
static bool _console_initialized_ = false;


void fb_write (_vfs_node_ *file, uint8_t* buffer, uint32_t length){
	memcpy (fb,buffer,length);
}

int fb_io_query (vfs_node_t* node, int code, void* arg) {

	return 1;
}




//! Initialize console device
void AuConsoleInitialize (PKERNEL_BOOT_INFO info) {
	console_x = 0;
	console_y = 0;
	scanline = info->pixels_per_line;
	screen_width = info->X_Resolution;
	screen_height = info->Y_Resolution;
	fb =  AuGetFramebuffer();//info->graphics_framebuffer;


	uint64_t* buffer = (uint64_t*)p2v((size_t)AuPmmngrAllocBlocks(2));
	memset(buffer, 0, 8192);
	vfs_node_t file = fat32_open(NULL, "/font.psf");
	fat32_read_file (&file,(uint64_t*)v2p((size_t)buffer),file.size);
	psf_data = buffer;
	_console_initialized_ = true;
}

//! Put a character to console output
void putc (char c) {
	if (psf_data == NULL)
		return;

	psf2_t *font = (psf2_t*)psf_data;
    int x,y,kx=0,line,mask,offs;
    int bpl=(font->width+7)/8;
  
	
	unsigned char *glyph = (unsigned char*)psf_data + font->headersize + 
				(c>0&&c<font->numglyph?c:0)*font->bytesperglyph;
	offs = kx * (font->width + 1);// * 4);
	for(y=0;y<font->height;y++) {
		line=offs; mask=1<<(font->width-1);
		for(x=0;x<font->width;x++) {
			fb[line + console_x + console_y * screen_width ]=((int)*glyph) & (mask)?0xFFFFFF:0;
			mask>>=1; line+=1;
		}
		fb[line + console_x + console_y * screen_width]=0; glyph+=bpl; offs+=scanline;
	}
	console_x += font->width + 1;
}


void console_pixel(uint32_t col, unsigned x, unsigned y)
{
	fb[x + y * screen_width] = col;
}


//! Prints string to console output
void puts(char *s){
	if (psf_data == NULL)
		return;

	psf2_t *font = (psf2_t*)psf_data;
    int x,y,line,mask,offs;
    int bpl=(font->width+7)/8;
    while(*s) {
		if (*s == '\n') {

            console_y += 16;
			console_x = 0;
			////!Scroll
			if (console_y + 1 > screen_height) {
				for (int i = 16; i < screen_height * screen_width; i++) {
					fb[i] = fb[i + screen_width * 16];
				}
				console_y--;
			}

		} else if (*s == '\b') {
			if (console_x > 0) {
				console_x--;
			}
		}else {
			unsigned char *glyph = (unsigned char*)psf_data + font->headersize + 
				(*s>0&&*s<font->numglyph?*s:0)*font->bytesperglyph;
			offs = console_x * (font->width + 1);// * 4);
			for(y=0;y<font->height;y++) {
				line=offs; mask=1<<(font->width-1);
				for(x=0;x<font->width;x++) {
					fb[line  + console_y * screen_width ]=((int)*glyph) & (mask)?0xFFFFFF:0;
					mask>>=1; line+=1;
				}
				fb[line  + console_y * screen_width]=0; glyph+=bpl; offs+=scanline;
			}
			console_x++;
		}
		s++; 
    }

	
}


////! Prints a char to console output
//void putc(char s){
//	if (psf_data == NULL)
//		return;
//
//	psf2_t *font = (psf2_t*)psf_data;
//    int x,y,line,mask,offs;
//    int bpl=(font->width+7)/8;
// 
//	unsigned char *glyph = (unsigned char*)psf_data + font->headersize + 
//			(s>0&&s<font->numglyph?s:0)*font->bytesperglyph;
//	offs = console_x * (font->width + 1);// * 4);
//	for(y=0;y<font->height;y++) {
//		line=offs; mask=1<<(font->width-1);
//		for(x=0;x<font->width;x++) {
//			fb[line  + console_y * screen_width ]=((int)*glyph) & (mask)?0xFFFFFF:0;
//				mask>>=1; line+=1;
//			}
//			fb[line  + console_y * screen_width]=0; glyph+=bpl; offs+=scanline;
//	}
//	console_x++;
//}

    


bool AuIsConsoleInitialized () {
	return _console_initialized_;
}
