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
 **/

#include <xeloop.h>
#include <stdint.h>
#include <sys\_ipc.h>
#include <sys\ioquery.h>
#include <sys\_file.h>
#include <sys\_wait.h>

/*
 * XePriLoopCreate -- Creates a new priloop
 * @return -- event file descriptor
 */
int XePriLoopCreate () {
	int event_fd = sys_open_file("/dev/pri_loop", NULL);
	ioquery(event_fd, PRI_LOOP_CREATE, NULL);
	return event_fd;
}

/* XePriLoopDestroy -- Destroys selected priloop
 * @param event_fd -- event file descriptor
 */
void XePriLoopDestroy (int event_fd) {
	ioquery(event_fd,PRI_LOOP_DESTROY, NULL);
}

/*
 * XeLoop -- Start the Xeneva Loop
 * @param event_fd -- selected event file descriptor
 * @param e -- user event message pointer
 */
void XeLoop(int event_fd, pri_event_t *e) {
	pri_event_t xe;
	while(1) {
		ioquery(event_fd, PRI_LOOP_GET_EVENT, &xe);
		if (xe.type != 0) {
			//Handle messages
		}
		sys_wait();
	}
}