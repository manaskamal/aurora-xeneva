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
 * @sysserv.h -- system call services 
 *
 **/


#ifndef __SYSSERV_H__
#define __SYSSERV_H__

#include <stdio.h>
#include <screen.h>
#include <ipc\message.h>
#include <callback.h>
#include <ipc\dwm_ipc.h>
#include <arch\x86_64\mmngr\map.h>
#include <fs\ttype.h>
#include <ipc\pipe.h>
#include <timer.h>


//! List of available services in Aurora
static void* _syscalls[] = {
	printf,            //0
	wait,              //1
	create__sys_process, //2
	0,    //3
	0, ///4
	valloc,            ///5
	message_send,      //6
	message_receive,   //7
	map_shared_memory, //8
	get_thread_id, //9
	create_timer, //10
	destroy_timer, //11
	0, //12
	ttype_create, //13
	start_timer , //14
	pause_timer, //15
	allocate_pipe, //16
	sys_unblock_id, //17
	create_uthread, //18
	sys_open_file, //19
	sys_read_file, //20
	ttype_dup_master, //21
	sys_get_used_ram, //22
	sys_get_free_ram, //23
	sys_sleep, //24
	sys_exit, //25
	sys_attach_ttype, //26
	fork, //27
	exec, //28
	map_memory, //29
	unmap_memory, //30
	ioquery, //31
	sys_get_current_time, //32
	sys_get_system_tick, //33
	sys_kill, //34
	sys_set_signal, //35
	unmap_shared_memory, //36
	sys_write_file, //37
	vfree, //38
	0
};


#endif