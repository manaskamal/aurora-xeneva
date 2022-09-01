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

#define DOCK_HEIGHT  30


void DockPaint (XEWindow* win) {
	acrylic_draw_vertical_gradient(win->ctx, 0,0,win->shwin->width,DOCK_HEIGHT, LIGHTSILVER, TITLEBAR_DARK);
}

/*
 * main -- the main entry point of init
 */
XE_EXTERN XE_EXPORT int XeMain (int argc, char* argv[]) {
	XeApp *app = XeStartApplication(argc, argv);
	int event_fd = app->event_fd;
	

	int svga_fd = sys_open_file ("/dev/fb", NULL);
	uint32_t screen_width = ioquery(svga_fd,SCREEN_GETWIDTH,NULL);
	uint32_t screen_height = ioquery(svga_fd, SCREEN_GETHEIGHT, NULL);

	canvas_t * canvas = create_canvas(screen_width, DOCK_HEIGHT);


	XEWindow *win = XECreateWindow(app,canvas,(1<<1) ,"Dock",0,screen_height - DOCK_HEIGHT);
	win->shwin->width = screen_width;
	win->shwin->height = DOCK_HEIGHT;
	win->color = LIGHTCORAL;
	win->paint = DockPaint;
	
	XEWindowSetAttrib((1<<1));
	XEShowWindow(win);

	while(1) {
		sys_wait();
	}
	return 0;
}