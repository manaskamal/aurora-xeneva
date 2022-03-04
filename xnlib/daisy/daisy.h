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

#ifndef __DAISY_H__
#define __DAISY_H__

#include <stdint.h>
#include <sys/_ipc.h>
#include "daisy_event_stack.h"

/* Messages sends from client to server */
#define PRI_WIN_CREATE  100
#define PRI_WIN_MARK_FOR_CLOSE 102
#define PRI_WIN_MOVE 103
#define PRI_WIN_READY 104
#define PRI_REGISTER_DESKTOP_COMPONENT 105

/* Messages that are being send to client by server */
#define DAISY_WIN_MOVE  200
#define DAISY_CURSOR_MOVED 201
#define DAISY_GIFT_CANVAS 202
#define DAISY_GIFT_SHARED_WIN 203
#define DAISY_KEY_EVENT 204
#define DAISY_NEW_WINDOW_INFO 205
#define DAISY_NOTIFY_WIN_FOCUS_CHANGED 206


/**
 * daisy_register_for_gifts -- register a new pri_loop box
 * for event handling
 */
extern void daisy_application ();


/**
 * daisy_get_gifts -- polls for events
 */
extern pri_event_t *daisy_get_gifts (bool wait);

/**
 * priwm_send_event -- sends an event to priwm
 * @param event -- event structure to send
 */
void priwm_send_event (pri_event_t *event);


/**
 * daisy_get_event_fd -- returns event file descriptor
 */
extern int daisy_get_event_fd ();

#endif