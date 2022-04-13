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
 * /PROJECT - Aurora's Xeneva v1.0
 * @daisy.h -- daisy base header
 *
 **/

#include "daisy.h"
#include <stdlib.h>
#include <string.h>
#include <sys/_file.h>
#include <sys/_ipc.h>
#include <sys/_thread.h>
#include <sys/_wait.h>
#include <sys/ioquery.h>
#include <sys/_term.h>
#include <sys/_process.h>
#include <sys/_sleep.h>
#include <fastcpy.h>
#include <acrylic.h>
#include <font.h>

int event_fd;


#define PRI_WM_RECEIVER       0xFFFFD00000000000


/**
 *daisy_application -- creates a new daisy application
 */
void daisy_application () {

	/* create an instance of pri_loop and register
	   to this application */
	event_fd = sys_open_file ("/dev/pri_loop", NULL);
	ioquery (event_fd, PRI_LOOP_CREATE, NULL);
	acrylic_initialize_font();
}


/**
 * daisy_get_gifts -- polls for events
 */
pri_event_t *daisy_get_gifts (bool wait) {
	pri_event_t *ev = NULL;
	bool needs_processing = false;
	

	pri_event_t *e = (pri_event_t*)malloc(sizeof(pri_event_t));
	memset (e, 0, sizeof(pri_event_t));
	ioquery (event_fd, PRI_LOOP_GET_EVENT, e);
	if (e->type != 0) {
		daisy_push_gift (e);
	} 

	if (daisy_get_gift_count() > 0) {
		ev = daisy_gift_get_event();
		needs_processing = true;
	}

	if (e->type == 0) {
		free(e);
	}
	/* check if the daisy_msg_stack is empty and
       no event is also pending in pri_loop box,
	   if yes than wait for a message */
	if (!needs_processing) {
		sys_wait();  
	}

	return ev;
}



/**
 * priwm_send_event -- sends an event to priwm
 * @param event -- event structure to send
 */
void priwm_send_event (pri_event_t *event) {
	void* address = (void*)PRI_WM_RECEIVER;
	pri_event_t *data = (pri_event_t*)address;
check:
	if (data->type != 0) {
		sys_sleep(16);
		goto check;
	} else {
		event->from_id = get_current_pid();
		memcpy (address, event, sizeof(pri_event_t));
	}
}


/**
 * daisy_get_event_fd -- returns event file descriptor
 */
int daisy_get_event_fd () {
	return event_fd;
}

/**
 * daisy_application_exit -- exits an application
 * @param exitcode -- exitcode 
 */
void daisy_application_exit (int exitcode) {
	pri_event_t e;
	e.type = PRI_WIN_MARK_FOR_CLOSE;
	e.from_id = get_current_pid();
	priwm_send_event(&e);

	while(1) {
		ioquery (event_fd,PRI_LOOP_GET_EVENT,&e);
		if (e.type != 0) {
			if (e.type == DAISY_WINDOW_CLOSED) {
				acrylic_font_destroy();

				ioquery(event_fd, PRI_LOOP_DESTROY,NULL);
				memset(&e, 0, sizeof(pri_event_t));
				exit(exitcode);
			}
		}
	}
}

