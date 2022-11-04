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

#include <xequwindow.h>
#include <sys/ioquery.h>
#include <sys/shm.h>
#include <sys/_term.h>
#include <sys/_wait.h>
#include <sys/_sleep.h>
#include <stdlib.h>
#include <fastcpy.h>
#include <color.h>

XEQuickWindow * XECreateQuickWindow (XeApp *app, int x, int y, int w, int h, char* title) {

	XEQuickWindow *quickw = NULL;

	/* Request a new Window from the server */
	pri_event_t e;
	e.type = PRIWM_POPUP_WIN_CREATE;
	e.dword = x;
	e.dword2 = y;
	e.dword3 = w;
	e.dword4 = h;
	XeSendEventPRIWM(&e, app->event_fd);

	memset(&e, 0, sizeof(pri_event_t));
	int sh_key, back_key = 0;
	int ret_code = 0;
	while(1){
		ret_code = ioquery(app->event_fd, PRI_LOOP_GET_EVENT, &e);
		if (e.type != 0){
			/* And we got a window from the server 
			 * Server provides 4 parameters ->    
			 *    (1)  Shared Window Buffer Key    
			 *    (2)  Back Buffer Memory Key
			 *    (3)  Shared Window Buffer
			 *    (4)  Back Buffer
			 */
			if (e.type == XE_CREATE_WINDOW) {
				sh_key = e.dword;
				back_key = e.dword2;
				uint16_t id = sys_shmget(sh_key, 0, 0);
				void* sh_win_addr = sys_shmat(id,0, 0);
				uint16_t back_id = sys_shmget(back_key, 0, 0);
				void* backing_store = sys_shmat(back_id, 0, 0);
				uint32_t *fb = (uint32_t*)backing_store;

				quickw = (XEQuickWindow*)malloc(sizeof(XEQuickWindow));
				quickw->title = (char*)malloc(strlen(title)+1);
				strcpy(quickw->title, title);
				quickw->widget_list = list_init();


				quickw->server = (XEQuickServer*)sh_win_addr;
				quickw->buffer = (uint32_t*)backing_store;
				quickw->server_win_key = sh_key;
				quickw->buffer_key = back_key;

				for (int i = 0; i < w; i++)
					for (int j = 0; j < h; j++)
						quickw->buffer[i + j * quickw->server->w] = LIGHTSILVER;

				quickw->server->dirty = true;
				memset(&e, 0, sizeof(pri_event_t));
				break;
			}
			
		}
		if (ret_code == -1)
			sys_wait();
	}
	return quickw;
}


/*
 * XEQuickWindowUpdate -- Update canvas contents to Quick Window buffer
 * @param quickw -- Pointer to	QuickWindow
 * @param canvas -- Pointer to canvas
 * @param x -- X location
 * @param y -- Y location
 * @param w -- Width of the update region
 * @param h -- Height of the update region
 */
 void XEQuickWindowUpdate (XEQuickWindow *quickw, canvas_t* canvas, int x, int y, int w, int h) {
	 for (int i = 0; i < h; i++)
		 fastcpy(quickw->buffer + (y + i) * quickw->server->w + x, canvas->address + (y + i) * quickw->server->w + x, w*4);
 }
/*
 * XEQuickWindowClose -- Closes opened quick window
 * @param quickw -- Pointer to XEQuickWindow
 */
void XEQuickWindowClose (XEQuickWindow *quickw, XEWindow* win) {
	quickw->server->close = true;
	free(quickw->title);
	sys_shm_unlink(quickw->server_win_key);
	sys_shm_unlink(quickw->buffer_key);
	
	pri_event_t e;
	memset(&e, 0, sizeof(pri_event_t));
	e.type = PRIWM_POPUP_WIN_CLOSE;
	XeSendEventPRIWM(&e,win->app->event_fd);
}

/*
 * XEQuickWindowAdd -- Adds a widget to quick window widget list
 * @param win -- Pointer to XEQuickWindow
 * @param widget -- Pointer to XEWidget
 */
void XEQuickWindowAdd (XEQuickWindow *win, XEWidget* widget) {
	list_add(win->widget_list, widget);
}
