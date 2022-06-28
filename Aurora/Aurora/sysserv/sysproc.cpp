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
 * @sysproc.cpp -- system call implementation for process management
 *
 **/

#include <proc.h>
#include <fs\ttype.h>
#include <drivers\mouse.h>
#include <serial.h>

/**
 * create__sys_process -- creates a process and returns its id
 * @param name -- filepath of the process
 * @param procnm -- name of the process
 * @return id -- id of the newly created process
 */
int create__sys_process (const char* name, char* procnm) {
	x64_cli();
	int id = AuCreateProcess (name, procnm);
	return id;
}

/**
 * sys_exit -- kills current process and switch to next
 * process from the schedule
 */
void sys_exit () {
	x64_cli();	
	kill_process();
	_debug_print_ ("***Process killed \r\n");
	_debug_print_ ("*** Current used RAM -> %d MB / total -> %d MB \r\n", pmmngr_get_used_ram() / 1024 / 1024, pmmngr_get_total_ram() / 1024 / 1024);
	force_sched();
}


/**
 * sys_kill -- sends a signal to a process
 * @param pid -- destination process id
 * @param signo -- signal number
 */
void sys_kill (int pid, int signo) {
	x64_cli();
	thread_t *current_thread = thread_iterate_ready_list(pid);
	if (current_thread == NULL) 
		current_thread = thread_iterate_block_list(pid);

	current_thread->pending_signal = signo;

	/* Signal Not Implemented for now */
}

/**
 * sys_set_signal -- setup a signal handler for a process
 * @param signo -- signal number
 * @param handler -- signal handler address
 */
void sys_set_signal (int signo, sig_handler handler) {
	x64_cli();
	get_current_thread()->signals[signo] = handler;
}

/**
 * sys_sigreturn -- return from a signal handler
 */
void sys_sigreturn () {
	x64_cli();
	
	/* Signal Not implemented for now */
}