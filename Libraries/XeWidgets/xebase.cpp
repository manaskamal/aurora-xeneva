/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2021, Manas Kamal Choudhury
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
 *
 **/

#include <sys\_xeneva.h>
#include <xebase.h>
#include <xeloop.h>
#include <sys\_process.h>
#include <string.h>
#include <sys\_sleep.h>
#include <sys\ioquery.h>
#include <sys\_wait.h>
#include <sys\shm.h>
#include <xebasewin.h>
#include <stdlib.h>


#define PRI_WM_RECEIVER       0xFFFFD00000000000

/*
 * XeSendEventPRIWM -- Sends a message to PRIWM
 * @param event -- message body
 */
void XeSendEventPRIWM (pri_event_t *event) {
	void* address = (void*)PRI_WM_RECEIVER;
	pri_event_t *data = (pri_event_t*)address;
check:
	if (data->type != 0) {
		sys_sleep(6);
		goto check;
	}else {
		event->from_id = get_current_pid();
		memcpy(address, event, sizeof(pri_event_t));
	}
}

/*
 * XeStartApplication -- Initializes all the required stuffs
 * for GUI Application
 */
XeApp* XeStartApplication(int argc, char* argv[]) {
	int event_fd = XePriLoopCreate();

	XeApp *app = (XeApp*)malloc(sizeof(XeApp));
	memset(app, 0, sizeof(XeApp));

	/* Request a new Window from the server */
	pri_event_t e;
	e.type = PRIWM_REQUEST_WINDOW;
	e.dword = 0;
	e.dword2 = 0;
	e.dword3 = XE_WIN_DEFAULT_WIDTH;
	e.dword4 = XE_WIN_DEFAULT_HEIGHT;
	e.dword5 = 0;
	XeSendEventPRIWM(&e);
	memset(&e, 0, sizeof(pri_event_t));
	int sh_key, back_key = 0;

	while(1){
		ioquery(event_fd, PRI_LOOP_GET_EVENT, &e);
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
				xe_win_info_t *info = (xe_win_info_t*)sh_win_addr;
				uint16_t back_id = sys_shmget(back_key, 0, 0);
				void* backing_store = sys_shmat(back_id, 0, 0);
				uint32_t *fb = (uint32_t*)backing_store;
				
				/* Fill the buffer with white color */
				for (int i = 0; i < info->width; i++) 
					for (int j = 0; j < info->height; j++)
						fb[i+j*4] = 0xffffffff;

				/* Fill up the 'app' structure */
				app->sh_key = sh_key;
				app->back_key = back_key;
				app->event_fd = event_fd;
				app->framebuffer = fb;
				app->shared_win_address = sh_win_addr;
				app->buffer_width = XE_WIN_DEFAULT_WIDTH;
				app->buffer_height = XE_WIN_DEFAULT_HEIGHT;

				memset(&e, 0, sizeof(pri_event_t));
				break;
			}
		}
		sys_wait();
	}

	return app;
}
