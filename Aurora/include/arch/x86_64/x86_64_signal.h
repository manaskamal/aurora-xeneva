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
 *
 **/

#ifndef __X86_64_SIGNAL_H__
#define __X86_64_SIGNAL_H__

#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <arch\x86_64\thread.h>

typedef struct _signal_ {
	int signum;
	RegsCtx_t *signal_stack2;
	thread_frame_t* signal_state;
	_signal_ *link;
}signal_t;


/*
 * AuAllocSignal -- Allocates a new signal 
 * @param dest_thread -- destination thread
 * @param signum -- signal number
 */
extern void AuAllocSignal (thread_t *dest_thread, int signum);

/*
 * x86_64_check_signal -- checks if there any pending signal is present
 * in signal queue
 * @param current_thread -- pointer to the thread
 * @param frame -- interrupt_stack_frame
 */
extern bool x86_64_check_signal (thread_t *current_thread, interrupt_stack_frame *frame);

/*
 * x86_64_get_signal -- picks any signal from the signal queue and
 * return it to the caller
 * @param current_thread -- pointer to the desired thread
 */
extern signal_t *x86_64_get_signal (thread_t* current_thread);

/*
 * x86_64_prepare_signal -- handles a given signal, basically it prepares the thread for
 * entering/jumping to signal handler, rest is handled by execute_thread function
 * @param current_thread -- pointer to current thread
 * @param frame -- interrupt stack frame
 * @param signal -- desired signal
 */
extern void x86_64_prepare_signal (thread_t* current_thread,interrupt_stack_frame *frame, signal_t* signal);

#endif