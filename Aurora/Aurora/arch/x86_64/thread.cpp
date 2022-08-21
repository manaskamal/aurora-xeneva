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

#include <arch\x86_64\thread.h>
#include <arch\x86_64\user64.h>
#include <arch\x86_64\kstack.h>
#include <arch\x86_64\x86_64_signal.h>
#include <timer.h>
#include <stdio.h>
#include <atomic\mutex.h>
#include <utils\lnklist.h>
#include <string.h>
#include <serial.h>
#include <arch\x86_64\pcpu.h>

/**
 ** E X T E R N A L  S T A T I C  S Y M B O L S
 **/
extern "C" void x64_hlt();
extern "C" void force_sched_pic ();
extern "C" void force_sched_apic ();
extern "C" void x64_sse_test ();
/** ============================================
 ** Global initializers
 ** ============================================
 **/
extern void debug_print (const char* text, ...);
 
bool  scheduler_enable = false;
bool  scheduler_initialized = false;    
uint16_t task_id = 0;

//list_t *blocked_list;
thread_t *task_list_head = NULL;
thread_t *task_list_last = NULL;

thread_t *blocked_thr_head = NULL;
thread_t *blocked_thr_last = NULL;

uint32_t system_tick;
extern "C" thread_t *current_thread = NULL;

/**
 * Insert a thread to thread list
 * @param new_task -- new thread address
 */
void thread_insert (thread_t* new_task ) {
	new_task->next = NULL;
	new_task->prev = NULL;

	if (task_list_head == NULL) {
		task_list_last = new_task;
		task_list_head = new_task;
		current_thread = task_list_last;
	} else {
		task_list_last->next = new_task;
		new_task->prev = task_list_last;
	}
	task_list_last = new_task;
}

/**
 * remove a thread from thread list
 * @param thread -- thread address to remove
 */
void task_delete (thread_t* thread) {

	if (task_list_head == NULL)
		return;

	if (thread == task_list_head) {
		task_list_head = task_list_head->next;
	} else {
		thread->prev->next = thread->next;
	}

	if (thread == task_list_last) {
		task_list_last = thread->prev;
	} else {
		thread->next->prev = thread->prev;
	}

	/* donot free the thread, cuz when thread needs
	 * to move from runnable queue to blocked queue
	 * same address is used, rather call 'free' 
	 * externally 
	 */
}


/**
 * Insert a thread to thread list
 * @param new_task -- new thread address
 */
void thread_insert_block (thread_t* new_task ) {
	new_task->next = NULL;
	new_task->prev = NULL;

	if (blocked_thr_head == NULL) {
		blocked_thr_last = new_task;
		blocked_thr_head = new_task;
	} else {
		blocked_thr_last->next = new_task;
		new_task->prev = blocked_thr_last;
	}
	blocked_thr_last = new_task;
}

/**
 * remove a thread from thread list
 * @param thread -- thread address to remove
 */
void thread_delete_block (thread_t* thread) {

	if (blocked_thr_head == NULL)
		return;

	if (thread == blocked_thr_head) {
		blocked_thr_head = blocked_thr_head->next;
	} else {
		thread->prev->next = thread->next;
	}

	if (thread == blocked_thr_last) {
		blocked_thr_last = thread->prev;
	} else {
		thread->next->prev = thread->prev;
	}
}
/*=========================================================================================*/
/*=========================================================================================*/
/*=========================================================================================*/

/**
 * ! Creates a kernel mode thread
 *  @param entry -- Entry point address
 *  @param stack -- Stack address
 *  @param cr3 -- the top most page map level address
 *  @param name -- name of the thread
 *  @param priority -- (currently unused) thread's priority
 **/
thread_t* create_kthread (void (*entry) (void), uint64_t stack,uint64_t cr3, char name[8], uint8_t priority)
{
	thread_t *t = (thread_t*)malloc(sizeof(thread_t));//pmmngr_alloc();
	memset(t, 0, sizeof(thread_t));
	t->frame.ss = 0x10;
	t->frame.rsp = (uint64_t)stack;
	t->frame.rflags = 0x202;
	t->frame.cs = 0x08;
	t->frame.rip = (uint64_t)entry;
	t->frame.rax = 0;
	t->frame.rbx = 0;
	t->frame.rcx = 0;
	t->frame.rdx = 0;
	t->frame.rsi = 0;
	t->frame.rdi = 0;
	t->frame.rbp = (uint64_t)t->frame.rsp;
	t->frame.r8 = 0;
	t->frame.r9 = 0;
	t->frame.r10 = 0;
	t->frame.r11 = 0;
	t->frame.r12 = 0;
	t->frame.r13 = 0;
	t->frame.r14 = 0;
	t->frame.r15 = 0;
	t->frame.ds = 0x10;
	t->frame.es = 0x10;
	t->frame.fs = 0x10;
	t->frame.gs = 0x10;
	t->frame.kern_esp = stack;
	t->user_stack = stack;
	t->_is_user = 0;
	t->frame.cr3 = cr3;
	t->name = name;
	t->id = task_id++;
	t->quanta = 0;
	t->priviledge = THREAD_LEVEL_KERNEL;
	t->state = THREAD_STATE_READY;
	//t->priority = priority;
	t->fd_current = 3;
	t->fx_state = (uint8_t*)malloc(512);
	memset(t->fx_state, 0, 512);
	t->mxcsr = 0x1f80;
	/* Signal not supported for kernel threads */
	t->signal_queue = NULL;
	t->pending_signal_count = 0;
	thread_insert(t);
	return t;
}

/**
 *  Creates a user mode thread
 *  @param entry -- Entry point address
 *  @param stack -- Stack address
 *  @param cr3 -- the top most page map level address
 *  @param name -- name of the thread
 *  @param priority -- (currently unused) thread's priority
 */
thread_t* create_user_thread (void (*entry) (void*),uint64_t stack,uint64_t cr3, char name[8], uint8_t priority)
{
	thread_t *t = (thread_t*)malloc(sizeof(thread_t));//pmmngr_alloc();
	memset (t, 0, sizeof(thread_t));
	t->frame.ss = SEGVAL(GDT_ENTRY_USER_DATA,3); 
	t->frame.rsp = (uint64_t)stack;
	t->frame.rflags = 0x286;
	t->frame.cs = SEGVAL (GDT_ENTRY_USER_CODE,3);
	t->frame.rip = (uint64_t)entry;
	t->frame.rax = 0;
	t->frame.rbx = 10;
	t->frame.rcx = 0;
	t->frame.rdx = 0;
	t->frame.rsi = 10;
	t->frame.rdi = 0;
	t->frame.rbp = (uint64_t)t->frame.rsp;
	t->frame.r8 = 0;
	t->frame.r9 = 0;
	t->frame.r10 = 0;
	t->frame.r11 = 0;
	t->frame.r12 = 0;
	t->frame.r13 = 0;
	t->frame.r14 = 0;
	t->frame.r15 = 0;

	/** Kernel stack is important for syscall or interruption in the system **/
	t->frame.kern_esp = (uint64_t)allocate_kstack((uint64_t*)cr3);
	t->user_stack = stack;
	t->frame.ds = 0x23;
	t->frame.es = 0x23;
	t->frame.fs = 0x23;
	t->frame.gs = 0x23;
	t->frame.cr3 = v2p(cr3);
	t->name = name;
	t->id = task_id++;
	t->quanta = 0;
	t->msg_box = (uint64_t*)p2v((size_t)AuPmmngrAlloc());
	/** Map the thread's msg box to a virtual address, from where the process will receive system messages **/
	AuMapPageEx((uint64_t*)p2v(t->frame.cr3),v2p((size_t)t->msg_box),(uint64_t)0x400000, PAGING_USER);

	t->fx_state = (uint8_t*)malloc(512);
	memset(t->fx_state, 0, 512);
	t->mxcsr = 0x1f80;
	t->_is_user = 1;
	t->priviledge = THREAD_LEVEL_USER;
	t->state = THREAD_STATE_READY;
	t->priority = priority;
	t->fd_current = 3;
	/*for (int i = 0; i < 1024*1024 / 4096; i++)
		AuMapPageEx((uint64_t*)cr3,(uint64_t)AuPmmngrAlloc(), 0x0000700000400000 + i * 4096, PAGING_USER); 
	t->signal_stack = (0x0000700000400000 + 1024*1024 - 256);*/
	t->signal_queue = NULL;
	t->pending_signal_count = 0;
	thread_insert (t);
	return t;
}

/*
 * create_child_thread -- creates child user thread
 * @param parent -- parent thread
 * @param entry -- entry point of the thread
 * @param stack -- thread stack
 * @param cr3 -- Parent user address space
 * @param name[8] -- Current thread name
 */
thread_t* create_child_thread (thread_t *parent, void (*entry)(void*),uint64_t stack, char name[8]) {
	thread_t *t = (thread_t*)malloc(sizeof(thread_t));
	memset(t, 0, sizeof(thread_t));
	t->frame.ss = SEGVAL(GDT_ENTRY_USER_DATA,3); 
	t->frame.rsp = (uint64_t)stack;
	t->frame.rflags = 0x286;
	t->frame.cs = SEGVAL (GDT_ENTRY_USER_CODE,3);
	t->frame.rip = (uint64_t)entry;
	t->frame.rax = 0;
	t->frame.rbx = 10;
	t->frame.rcx = 0;
	t->frame.rdx = 0;
	t->frame.rsi = 10;
	t->frame.rdi = 0;
	t->frame.rbp = (uint64_t)t->frame.rsp;
	t->frame.r8 = 0;
	t->frame.r9 = 0;
	t->frame.r10 = 0;
	t->frame.r11 = 0;
	t->frame.r12 = 0;
	t->frame.r13 = 0;
	t->frame.r14 = 0;
	t->frame.r15 = 0;

	/** Kernel stack is important for syscall or interruption in the system **/
	t->frame.kern_esp = (uint64_t)allocate_kstack_child((uint64_t*)p2v((size_t)parent->frame.cr3));
	t->user_stack = stack;
	t->frame.ds = 0x23;
	t->frame.es = 0x23;
	t->frame.fs = 0x23;
	t->frame.gs = 0x23;
	t->frame.cr3 = parent->frame.cr3;
	t->name = name;
	t->id = task_id++;
	t->quanta = 0;
	t->msg_box = NULL; //parent->msg_box;
	t->fx_state = (uint8_t*)malloc(512);
	memset(t->fx_state, 0, 512);
	t->mxcsr = 0x1f80;
	t->_is_user = 1;
	t->priviledge = THREAD_LEVEL_USER;
	t->state = THREAD_STATE_READY;
	t->priority = 1;
	t->fd_current = 3;
	thread_insert (t);
	return t;
}

//! the main idle thread
void idle_thread () {
	while(1) {
		//x64_hlt();
	}
}


//! Initialize the scheduler engine and its core
//! data structure
void AuInitializeScheduler () {
	//blocked_list = initialize_list();
	scheduler_enable = true;
	scheduler_initialized = true;
	task_id = 0;
	/** Here create the first thread, the idle thread which never gets
	    blocked nor get destroyed untill the system turns off **/
	thread_t *idle_ = create_kthread (idle_thread,(uint64_t)p2v((uint64_t)AuPmmngrAlloc() + 4096),x64_read_cr3(),"Idle",1);
	current_thread = idle_;
	AuPCPUSetCurrentThread(current_thread);
}


/**
 *  next_task() -- switches ready stated tasks for execution
 *  this function gets called from the sceduler isr to check and
 *  get the next ready stated task from the thread list. Also this
 *  function manages the sleep stated task for decreasing its sleep
 *  counts
 * 
 *  @output  current_thread = next ready stated thread
 */
void next_task (cpu_t *pcpu) {
	thread_t* task = (thread_t*)pcpu->au_current_thread;//current_thread;
	do {
		if (task->state == THREAD_STATE_SLEEP) {
			if (task->quanta == 0) {
				task->state = THREAD_STATE_READY;
			}
			task->quanta--;
		}
		task = task->next;
		if (task == NULL) {
			task = task_list_head;
		}
	}while (task->state != THREAD_STATE_READY);

end:
	//AuPCPUSetCurrentThread(task);
	pcpu->au_current_thread = (uint64_t*)task;
	current_thread = (thread_t*)pcpu->au_current_thread;//AuPCPUGetCurrentThread(); //task;
}




void sig_loop () {
	for(;;) {
		//_debug_print_ ("Loop    ");
		x64_cli();
	}
}

/** ===============================================
 **  Scheduler Isr | Scheduler Isr
 ** ===============================================
 **/
void scheduler_isr (size_t v, void* param) {
	x64_cli();
	interrupt_stack_frame *frame = (interrupt_stack_frame*)param;
	
	/* check for enable bit, if yes than proceed for 
	   multitasking */
	if (scheduler_enable == false)
		goto sched_end;
	
	cpu_t* pcpu = AuPCPUGetCpu(x86_64_cpu_get_id());
	TSS *ktss = pcpu->kernel_tss;
	//mutex_lock (scheduler_mutex);
	/** save currently running thread contexts */
	if (save_context(current_thread,ktss) == 0) {
		current_thread->frame.cr3 = x64_read_cr3();

		
		/* check if the thread is user mode thread, if yes
		   than store the kernel esp */
		if (current_thread->priviledge == THREAD_LEVEL_USER) {
			//current_thread->kern_esp = ktss->rsp[0];
			current_thread->frame.kern_esp = x64_get_kstack(ktss);
		}


		/* 
		 * check for pending signal and make current_thread prepared
		 * for handling the signal (((**********BBBBBUUUUUGGGGGGYYYYYYY*******)))
		 */
		if (x86_64_check_signal(current_thread, frame)) {
			signal_t *sig = x86_64_get_signal(current_thread);
			x86_64_prepare_signal(current_thread,frame,sig);
		}


		if (is_cpu_fxsave_supported())
			x64_fxsave(current_thread->fx_state);

		/* now get the next runnable task from the thread list */
		next_task(pcpu);

		/*
		  Here increase the system tick and
		  fire the timer
		  */
		system_tick++;
		timer_fire();
#ifdef USE_APIC
	    apic_local_eoi();
#endif
#ifdef USE_PIC
		AuInterruptEnd (0);
#endif
		
		/** now return to the new task last stored instruction */


		if (current_thread->priviledge == THREAD_LEVEL_USER){
			//ktss->rsp[0] = current_thread->kern_esp;
			x64_set_kstack(ktss,current_thread->frame.kern_esp);
		}

		if (is_cpu_fxsave_supported())
			x64_fxrstor(current_thread->fx_state);

		x64_ldmxcsr(&current_thread->mxcsr);


		//
		//mutex_unlock (scheduler_mutex);
		execute_idle (current_thread,ktss);
		
	}

sched_end:
#ifdef USE_APIC
	apic_local_eoi();
#endif
#ifdef USE_PIC
	AuInterruptEnd(0);
#endif
}


//! Start the scheduler engine
void AuSchedulerStart () {
#ifdef USE_APIC
	setvect(0x40, scheduler_isr);
#endif
#ifdef USE_PIC
	AuInterruptSet(0,scheduler_isr,0, false);
#endif
	execute_idle(current_thread,get_kernel_tss());
}


//! Enable or disable multi tasking
void set_multi_task_enable (bool value) {
	if (scheduler_enable == value)
		return;

	scheduler_enable = value;
}

void set_current_thread (thread_t *thread) {
	current_thread = thread;
}



//! check if multi tasking is previously enabled
bool is_multi_task_enable () {
	return scheduler_enable;
}


//! Blocks a running thread 
void block_thread (thread_t *thread) {
	thread->state = THREAD_STATE_BLOCKED;
	task_delete (thread);
	//list_add (blocked_list,thread);
	thread_insert_block(thread);
}



//! Iterate through block list and find a specific thread
thread_t* thread_iterate_block_list (int id) {
	if (blocked_thr_head != NULL)
		for (thread_t *thr = blocked_thr_head; thr != NULL; thr = thr->next) {
			if (thr->id == id) {
				return thr;
		}
	}
	return NULL;
}

//! Iterate through ready list and find a specific thread
thread_t * thread_iterate_ready_list (uint16_t id) {
	for (thread_t *it = task_list_head; it != NULL; it = it->next) {
		if (it->id == id) {
			return it;
		}
	}
	return NULL;
}

//!Get thread id by its name
uint16_t thread_get_id_by_name (char* name) {
	uint16_t id = 0;
	for (thread_t *it = task_list_head; it != NULL; it = it->next) {
		if (it->name == name) {
			id = it->id;
			break;
		}
	}

	if (id > 0)
		return id;
	else{
		if (blocked_thr_head != NULL)
			for (thread_t *thr = blocked_thr_head; thr != NULL; thr = thr->next) {
				if (thr->name == name) 
					return thr->id;
			}
	}

	return NULL;
}

//!unblock a thread
void unblock_thread (thread_t *t) {
	//x64_cli();
	t->state = THREAD_STATE_READY;
	for (thread_t *thr = blocked_thr_head; thr != NULL; thr = thr->next) {
		if (thr == t) 
			thread_delete_block(thr);
	}
	thread_insert (t);
}


/**
 * sleep_thread (t,ms) -- cause a thread to sleep for a given msec
 * @param t -- thread address
 * @param ms -- millisecond
 */
void sleep_thread (thread_t *t, uint64_t ms) {
	t->quanta = ms;
	t->state = THREAD_STATE_SLEEP;
}

//! get_current_thread() -- returns currently running thread
thread_t * get_current_thread () {
	return current_thread;
}

//!force scheduler
void force_sched () {
#ifdef USE_APIC
	force_sched_apic();
#elif USE_PIC
	force_sched_pic();
#endif
}

/**
 * is_scheduler_initialized() -- check and return
 * the scheduler_initialized bit
 */
bool is_scheduler_initialized () {
	return scheduler_initialized;
}

/**
 * sched_get_tick -- return system tick incremented
 */
uint32_t sched_get_tick() {
	return system_tick;
}


