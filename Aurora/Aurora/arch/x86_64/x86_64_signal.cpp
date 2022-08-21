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

#include <arch\x86_64\x86_64_signal.h>
#include <arch\x86_64\thread.h>
#include <arch\x86_64\mmngr\kheap.h>


extern "C" void sig_ret();


/*
 * AuAllocSignal -- Allocates a new signal 
 * @param dest_thread -- destination thread
 * @param signum -- signal number
 */
void AuAllocSignal (thread_t* dest_thread,int signum) {
	signal_t *signal = (signal_t*)malloc(sizeof(signal_t));
	memset(signal, 0, sizeof(signal_t));
	signal->signum = signum;
	signal->signal_stack2 = (RegsCtx_t*)malloc(sizeof(RegsCtx_t));
	signal->signal_state = (thread_frame_t*)malloc(sizeof(thread_frame_t));

	signal_queue *queue = (signal_queue*)malloc(sizeof(signal_queue));
	memset(queue, 0, sizeof(signal_queue));
	queue->signal = signal;
	queue->link = dest_thread->signal_queue;
	dest_thread->signal_queue = queue;
	dest_thread->pending_signal_count++;
}


/*
 * x86_64_check_signal -- checks for pending signal to handle
 * @param current_thread -- thread to look for
 * @param frame -- Top of the kernel stack
 */
bool x86_64_check_signal (thread_t *current_thread, interrupt_stack_frame *frame) {
	/*if (current_thread->pending_signal > 0 && frame->cs == SEGVAL(GDT_ENTRY_USER_CODE,3)) {
		return true;
	}*/

	if (!current_thread->signal_queue)
		return false;

	if (current_thread->pending_signal_count > 0 && frame->cs == SEGVAL(GDT_ENTRY_USER_CODE,3)) 
		return true;

	return false;
}

/*
 * x86_64_get_signal -- picks any signal from the signal queue and
 * return it to the caller
 * @param current_thread -- pointer to the desired thread
 */
signal_t *x86_64_get_signal (thread_t* current_thread) {
	if (!current_thread->signal_queue)
		return NULL;

	signal_t *sig;
	signal_queue *temp;
	temp = current_thread->signal_queue;
	current_thread->signal_queue = current_thread->signal_queue->link;
	temp->link = NULL;
	sig = (signal_t*)temp->signal;
	free(temp);
	current_thread->pending_signal_count--;

	current_thread->returnable_signal = sig;

	if (!sig)
		return NULL;
	return sig;
}

/*
 * x86_64_prepare_signal -- prepare a given signal, basically it prepares the thread for
 * entering/jumping to signal handler, rest is handled by execute_thread function
 * @param current_thread -- pointer to current thread
 * @param frame -- interrupt stack frame
 * @param signal -- desired signal
 */
void x86_64_prepare_signal (thread_t* current_thread,interrupt_stack_frame *frame, signal_t* signal) {

	RegsCtx_t *ctx = (RegsCtx_t*)(current_thread->frame.kern_esp - sizeof(RegsCtx_t));
	uint64_t* rsp_ = (uint64_t*)current_thread->user_stack;

	/* Store the current kernel stack information to seperate memory location */
	memcpy (signal->signal_stack2, ctx,sizeof(RegsCtx_t));

	/* Store the return address */
	rsp_ -= 8;
	for (int i = 0; i < 2; i++)
		AuMapPage((uint64_t)AuPmmngrAlloc(), 0x700000 + i * 4096, PAGING_USER);
	memcpy((void*)0x700000,&sig_ret, 8192);
	*rsp_ = 0x700000;

	memcpy (signal->signal_state,&current_thread->frame,sizeof(thread_frame_t));
			

	frame->rsp = (uint64_t)rsp_;
	current_thread->frame.rbp = (uint64_t)rsp_;
	current_thread->frame.rcx = 10;
	current_thread->frame.rip = (uint64_t)current_thread->signals[signal->signum];
	current_thread->frame.rsp = frame->rsp;
	frame->rip = current_thread->frame.rip;
	frame->rflags = 0x286;
	current_thread->frame.rflags = 0x286;
	current_thread->returnable_signal = signal;
}

