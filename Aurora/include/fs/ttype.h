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
 * /PROJECT - Aurora's Xeneva v1.0
 * @ttype.h -- tele type driver
 *
 **/

#ifndef __TTYPE_H__
#define __TTYPE_H__

#include <stdint.h>
#include <fs\vfs.h>
#include <utils\circ_buf.h>

typedef struct _tele_type_ {
	uint8_t id;
	char m_path[32];
	char s_path[32];
	/*unsigned char in_buffer[512];
	unsigned char out_buffer[512];*/
	circ_buf_t *in_buffer;
	circ_buf_t *out_buffer;
	bool consumed;
	uint16_t blocked_pid;
	uint32_t written;
	uint16_t pid;
	struct _tele_type_ *next;
	struct _tele_type_ *prev;
}ttype_t;


extern void ttype_create (int* master_fd, int* slave_fd);
extern ttype_t * get_ttype (int id);
extern void ttype_dup_master (int task_id, int master_fd);
#endif