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

#ifndef __PRI_POPUP_H__
#define __PRI_POPUP_H__

#include "priwm.h"
#include <canvas.h>
#include "list.h"

#define POPUP_TYPE_MENU  (1<<0)
#define POPUP_TYPE_TOOLTIP  (1<<1)
#define POPUP_TYPE_TOAST_NOTIFICATION  (1<<2)

typedef struct _pri_popup_sh_win_ {
	int x;
	int y;
	int w;
	int h;
	bool dirty;
	bool close;
	bool hide;
	bool popuped;
	bool alpha;
}pri_popup_sh_win;

typedef struct _pri_popup_win_ {
	pri_popup_sh_win *shwin;
	uint32_t* buffer;
	uint8_t owner_id;
	uint16_t shwin_key;
	uint16_t buffer_win_key;
	_pri_popup_win_ *link;
}pri_popup_win_t;


/*
 * pri_create_popup_window -- create popup window
 * @param x -- x coordinate
 * @param y -- y coordinate
 * @param w -- width of the popup window
 * @param h -- height of the popup window
 */
pri_popup_win_t * pri_create_popup_window (int x, int y, int w, int h, uint16_t owner_id);

/*
 * pri_destroy_popup_window -- close & destroy popup window
 * @param popup -- pointer to popup window
 */
void pri_destroy_popup_window (pri_popup_win_t *popup);

/*
 * pri_popup_show -- make popup window visible
 * @param popup -- pointer to popup window
 */
void pri_popup_show (pri_popup_win_t *popup);

#endif