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
#include <list.h>
#include <acrylic.h>
#include <color.h>
#include "XEDesktop.h"
#include "XEGoButton.h"

#define DOCK_HEIGHT  20




canvas_t *canvas;

uint32_t screen_width = 0;
uint32_t screen_height = 0;

/*
 * XEDockRegister -- Register the dock as
 * a desktop component
 * @param app -- Pointer to XEApp
 */
void XEDockRegister (XeApp *app) {
	pri_event_t ev;
	ev.type = 105;
	XeSendEventPRIWM(&ev, app->event_fd);
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
	win->paint = XEDesktopPaint;

	/* Dock do not require global controls, so free it */
	XERemoveGlobalButton(win, XE_GLBL_CNTRL_MINIMIZE);
	XERemoveGlobalButton(win, XE_GLBL_CNTRL_MAXIMIZE);
	XERemoveGlobalButton(win, XE_GLBL_CNTRL_CLOSE);

	XEGoButton *gobut = XECreateGoButton(10, screen_height - 40, 60, 30, "Xeneva", "/xelogo.bmp");
	XEWindowAddWidget(win, (XEWidget*)gobut);


	Image *img = load_wallpaper(screen_width,screen_height,"/flora.jpg");
	
	XEWindowSetAttrib(win,(1<<1));
	XEShowWindow(win);

	XEDockRegister(app);

	pri_event_t ev;
	int ret_code = 0;
	while(1) {
		ret_code = ioquery(event_fd,PRI_LOOP_GET_EVENT, &ev);
		if (ev.type != NULL) {
			if (ev.type == 201) {
				XEWindowMouseHandle(win,ev.dword,ev.dword2,ev.dword3,0);
				memset(&ev, 0, sizeof(pri_event_t));
			}
		}

		if (ret_code == -1)
			sys_wait();
	}
	return 0;
}