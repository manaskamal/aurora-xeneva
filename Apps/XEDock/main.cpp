/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2022, Manas Kamal Choudhury
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 **/

/*
 * Init process -- init process starts all the system services
 * and required background processes
 */

#include <sys/_term.h>
#include <sys/_process.h>
#include <sys/_wait.h>
#include <sys/shm.h>
#include <sys/mmap.h>
#include <sys/_file.h>
#include <stdlib.h>
#include <string.h>
#include <canvas.h>
#include <sys/ioquery.h>
#include <image.h>
#include <xebase.h>
#include <sys\_xeneva.h>
#include <sys\_sleep.h>

#include <xewidget.h>
#include <acrylic.h>
#include <color.h>

#define DOCK_HEIGHT  20

typedef struct _wallpaper_ {
	uint8_t* buffer;
	Image* img;
	int w;
	int h;
}Wallpaper_t;

Wallpaper_t *wallpaper = NULL;
canvas_t *canvas;

uint32_t screen_width = 0;
uint32_t screen_height = 0;



/**
 * pri_load_wallpaper -- loads an wallpaper to pri_wallpaper
 * @param filename -- file path of the wallpaper
 */
Image *load_wallpaper (char *filename) {
	wallpaper = (Wallpaper_t*)malloc(sizeof(Wallpaper_t));
	for (int i = 0; i < (screen_width * screen_height * 4) / 4096; i++) 
		valloc(0x0000060000000000 + i * 4096);

	Image *img = LoadImage (filename, (uint8_t*)0x0000060000000000);
	wallpaper->buffer = (uint8_t*)0x0000060000000000;
	wallpaper->img = img;
	/* finally call the jpeg decoder and draw the
	 * image to wallpapers backing store
	 */
	if (img != NULL) {
		CallJpegDecoder(img);
		wallpaper->w = img->width;
		wallpaper->h = img->height;
	}

	return img;
}

/**
 * pri_wallpaper_draw -- draw the wallpaper to backing store
 * @param img -- img to draw 
 */
void pri_wallpaper_draw (Image *img) {
	unsigned x = 0;
	unsigned y = 0;
	if (img != NULL){

		if (img->data == NULL)
			pri_wallpaper_draw(NULL);

		uint8_t* data = img->image;
		uint32_t w = img->width;
		uint32_t h = img->height;
		for (int i = 0; i < h; i++) {
			for (int k = 0; k < w; k++) {
				int j = k + i * w;
				uint8_t r = data[j * 3];        
				uint8_t g = data[j * 3 + 1];        
				uint8_t b = data[j * 3 + 2];       
				//uint8_t a = data[j * 3 + 3];
				uint32_t rgba =  ((r<<16) | (g<<8) | (b)) & 0x00ffffff;  //0xFF000000 | (r << 16) | (g << 8) | b;
				rgba = rgba | 0xff000000;
				canvas_draw_pixel(canvas,x + k, y + i,rgba);
				j++;
			}
		}
	} else{
		for (int i = 0; i < canvas->width; i++) {
			for (int j = 0; j < canvas->height; j++) {
				canvas_draw_pixel(canvas,0 + i, 0 + j, LIGHTBLACK);
			}
		}
	}

}





void DockPaint (XEWindow* win) {
	acrylic_draw_vertical_gradient(win->ctx, 0,0,win->shwin->width,screen_height, LIGHTSILVER, GRAY);
	pri_wallpaper_draw(wallpaper->img);
}

/*
 * main -- the main entry point of init
 */
XE_EXTERN XE_EXPORT int XeMain (int argc, char* argv[]) {
	int svga_fd = sys_open_file ("/dev/fb", NULL);
	screen_width = ioquery(svga_fd,SCREEN_GETWIDTH,NULL);
	screen_height = ioquery(svga_fd, SCREEN_GETHEIGHT, NULL);

	XESetRequestBufferSize(screen_width, screen_height);

	XeApp *app = XeStartApplication(argc, argv);
	int event_fd = app->event_fd;
	

	

	canvas = create_canvas(screen_width, screen_height);


	XEWindow *win = XECreateWindow(app,canvas,(1<<1) ,"Dock",0,0);
	win->shwin->width = screen_width;
	win->shwin->height = screen_height;
	win->color = LIGHTCORAL;
	win->paint = DockPaint;

	Image *img = load_wallpaper("/kati.jpg");
	
	XEWindowSetAttrib(win,(1<<1));
	XEShowWindow(win);


	pri_event_t ev;
	int ret_code = 0;
	while(1) {
		ret_code = ioquery(event_fd,PRI_LOOP_GET_EVENT, &ev);
		if (ev.type != NULL) {
			if (ev.type == 201) {
				//XEWindowMouseHandle(win,ev.dword,ev.dword2,ev.dword3,0);
				memset(&ev, 0, sizeof(pri_event_t));
			}
		}

		if (ret_code == -1)
			sys_wait();
	}
	return 0;
}