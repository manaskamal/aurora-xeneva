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
#ifndef __XE_BASE_H__
#define __XE_BASE_H__


#include <sys\_xeneva.h>
#include <stdint.h>
#include <sys\_ipc.h>

#define PRIWM_REQUEST_WINDOW  100
#define PRIWM_WINDOW_SHOW  104

/* ADDITIONAL WIN CREATE */
#define PRIWM_POPUP_WIN_CREATE    110
#define PRIWM_DIALOG_WIN_CREATE   111
#define PRIWM_POPUP_WIN_CLOSE     112
#define PRIWM_DIALOG_WIN_CLOSE    113


#define XE_MOUSE_EVENT    201
#define XE_CREATE_WINDOW  202
#define XE_RESIZE_WINDOW  208
#define XE_KEY_EVENT      204

typedef struct _xe_app_ {
	int event_fd;
	int sh_key;
	int back_key;
	uint32_t *framebuffer;
	void* shared_win_address;
	int buffer_width;
	int buffer_height;
}XeApp;



/*
 * XeSendEventPRIWM -- Sends a message to PRIWM
 * @param event -- message body
 */
XE_EXTERN XE_EXPORT void XeSendEventPRIWM (pri_event_t *event);
/*
 * XeStartApplication -- Initializes all the required stuffs
 * for GUI Application
 */
XE_EXTERN XE_EXPORT XeApp* XeStartApplication(int argc, char* argv[]);

/* XECloseApplication -- Closes the application 
 * @param app -- Pointer to app structure
 */
XE_EXTERN XE_EXPORT void XECloseApplication (XeApp *app);

/*
 * XESetRequestBufferSize -- Set requesting buffer width and height size in px
 * @param buffer_width -- buffer width to request
 * @param buffer_height -- buffer height to request
 */
XE_EXTERN XE_EXPORT void XESetRequestBufferSize (int buffer_width, int buffer_height);

#endif