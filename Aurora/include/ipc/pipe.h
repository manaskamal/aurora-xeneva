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
 * @pipe.h -- Pipes IPC
 *
 **/

#ifndef __PIPE_H__
#define __PIPE_H__

#include <utils\circ_buf.h>
#include <fs\vfs.h>

typedef struct _pipe_ {
	circ_buf_t *buf;
	uint16_t readers;
	uint16_t writers;
}pipe_t;



/*
 * AuCreatePipe -- Create a pipe buffer
 */
extern pipe_t* AuCreatePipe ();
/*
 * AuAllocAnonPipe -- Creates anonymous pipe
 * @param fd[2] -- area where two file descriptor
 * get stored, one for read end and other for
 * write end
 */
extern void AuAllocAnonPipe (int fd[2]);
extern void pipe_write (vfs_node_t *file, uint8_t* buffer, uint32_t length);
extern void pipe_read (vfs_node_t *file, uint8_t* buffer,uint32_t length);
#endif