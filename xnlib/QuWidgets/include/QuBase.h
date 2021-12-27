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
 *   /PROJECT - Aurora's Xeneva v1.0
 *   @QuBase.h -- QuWidget Library initializer
 *
 **/

#ifndef __QU_BASE_H__
#define __QU_BASE_H__

#include <stdint.h>
#include <QuWindow.h>

//! Codes that are being send to Quince
#define QU_CODE_WIN_CREATE   100
#define QU_CODE_WIN_DESTROY  101
#define QU_CODE_WIN_MINIMIZE 102
#define QU_CODE_WIN_MAXIMIZE 103
#define QU_CODE_DIRTY_UPDATE 104
#define QU_CODE_WIN_CONFIG   105
#define QU_CODE_REPAINT      106
#define QU_CODE_WIN_CLOSE    107

//! Codes that are sent by Quince to clients
#define QU_CANVAS_READY  200
#define QU_CANVAS_DESTROYED 201
#define QU_CANVAS_MOVE  202
#define QU_CANVAS_MOUSE_MOVE 203
#define QU_CANVAS_MOUSE_LCLICKED 204
#define QU_CANVAS_MOUSE_LRELEASE 205
#define QU_CANVAS_KEY_PRESSED  206
#define QU_CANVAS_KEY_RELEASED 207
#define QU_CANVAS_RESIZE 208
#define QU_CANVAS_REPAINT 209
#define QU_CANVAS_FOCUS_LOST 210
#define QU_CANVAS_FOCUS_GAIN 211


#define QU_CHANNEL_ADDRESS   0xFFFFD00000000000  //Client Send address
#define QU_CHANNEL_RECEIVER  0xFFFFFD0000000000  //Client receiver address

/**
 * QuMessage : Message format that get transferred
 * to and from Server / Client
 */
typedef struct __QuMessage__ {
	uint8_t type;
	uint8_t to_id;
	uint8_t from_id;
	uint32_t dword;
	uint32_t dword2;
	uint32_t dword3;
	uint32_t dword4;
	uint32_t dword5;
	uint32_t dword6;
	uint32_t dword7;
	uint32_t dword8;
	uint32_t *p_value;
	uint32_t *p_value2;
	char *value;
	unsigned char* value2;
}QuMessage;


typedef struct _QuObject_ {
	int x;
	int y;
	int w;
	int h;
}QuObject;

/**
 * QuChannelPut -- Put a message for Window Manager
 * @param msg -- Message address
 * @param to_id -- Window Manager id
 */
extern void QuChannelPut (QuMessage *msg, uint16_t to_id);

/**
 * QuChannelGet -- Get a message from Window Manager
 * @param msg -- Message address
 */
extern void QuChannelGet (QuMessage *msg);

/**
 * QuRegisterApplication -- Register current application as GUI
 * @param win -- Window Address
 */
extern void QuRegisterApplication (QuWindow* win);

/**
 * QuGetAppId -- Returns current application id
 * @return -- current application id
 */
extern uint16_t QuGetAppId();


extern void QuApplicationRegisterWindow (QuWindow *win);
extern QuWindow* QuApplicationWindowGet (int id);
#endif