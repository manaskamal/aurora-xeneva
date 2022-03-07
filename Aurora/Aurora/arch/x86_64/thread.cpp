/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  thread.cpp -- Multitasking for Aurora
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *=============================================
 */

#include <arch\x86_64\thread.h>
#include <arch\x86_64\user64.h>
#include <arch\x86_64\kstack.h>
#include <timer.h>
#include <stdio.h>
#include <atomic\mutex.h>
#include <utils\lnklist.h>
#include <string.h>
#include <serial.h>

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

list_t *blocked_list;
thread_t *task_list_head = NULL;
thread_t *task_list_last = NULL;

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

	//pmmngr_free (thread);
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
	t->ss = 0x10;
	t->rsp = (uint64_t*)stack;
	t->rflags = 0x202;
	t->cs = 0x08;
	t->rip = (uint64_t)entry;
	t->rax = 0;
	t->rbx = 0;
	t->rcx = 0;
	t->rdx = 0;
	t->rsi = 0;
	t->rdi = 0;
	t->rbp = (uint64_t)t->rsp;
	t->r8 = 0;
	t->r9 = 0;
	t->r10 = 0;
	t->r11 = 0;
	t->r12 = 0;
	t->r13 = 0;
	t->r14 = 0;
	t->r15 = 0;
	t->ds = 0x10;
	t->es = 0x10;
	t->fs = 0x10;
	t->gs = 0x10;
	t->kern_esp = stack;
	t->ttype = 0;
	t->_is_user = 0;
	t->cr3 = cr3;
	t->name = name;
	t->id = task_id++;
	t->quanta = 0;
	t->priviledge = THREAD_LEVEL_KERNEL;
	t->state = THREAD_STATE_READY;
	//t->priority = priority;
	t->fd_current = 0;
	t->fx_state = (uint32_t*)pmmngr_alloc();
	//printf ("FX State addr-> %x\n", t->fx_state);
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
	memset (t, 0, 4096);
	t->ss = SEGVAL(GDT_ENTRY_USER_DATA,3); 
	t->rsp = (uint64_t*)stack;
	t->rflags = 0x286;
	t->cs = SEGVAL (GDT_ENTRY_USER_CODE,3);
	t->rip = (uint64_t)entry;
	t->rax = 0;
	t->rbx = 10;
	t->rcx = 0;
	t->rdx = 0;
	t->rsi = 10;
	t->rdi = 0;
	t->rbp = (uint64_t)t->rsp;
	t->r8 = 0;
	t->r9 = 0;
	t->r10 = 0;
	t->r11 = 0;
	t->r12 = 0;
	t->r13 = 0;
	t->r14 = 0;
	t->r15 = 0;

	/** Kernel stack is important for syscall or interruption in the system **/
	t->kern_esp = (uint64_t)allocate_kstack((uint64_t*)cr3);

	t->ds = 0x23;
	t->es = 0x23;
	t->fs = 0x23;
	t->gs = 0x23;
	t->cr3 = cr3;
	t->name = name;
	t->id = task_id++;
	t->quanta = 0;
	t->ttype = 0;
	t->msg_box = (uint64_t*)pmmngr_alloc();
	/** Map the thread's msg box to a virtual address, from where the process will receive system messages **/
	map_page_ex((uint64_t*)t->cr3,(uint64_t)t->msg_box,(uint64_t)0xFFFFFFFFB0000000, PAGING_USER);

	t->_is_user = 1;
	t->priviledge = THREAD_LEVEL_USER;
	t->state = THREAD_STATE_READY;
	t->priority = priority;
	t->fd_current = 0;
	thread_insert (t);
	return t;
}

//! the main idle thread
void idle_thread () {
	while(1) {
		x64_hlt();
	}
}


//! Initialize the scheduler engine and its core
//! data structure
void initialize_scheduler () {
	blocked_list = initialize_list();
	scheduler_enable = true;
	scheduler_initialized = true;
	task_id = 0;
	/** Here create the first thread, the idle thread which never gets
	    blocked nor get destroyed untill the system turns off **/
	thread_t *idle_ = create_kthread (idle_thread,(uint64_t)pmmngr_alloc(),x64_read_cr3(),"Idle",1);
	current_thread = idle_;
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
void next_task () {
	thread_t* task = current_thread;
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
	current_thread = task;
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

	//mutex_lock (scheduler_mutex);
   
	/** save currently running thread contexts */
	if (save_context(current_thread,get_kernel_tss()) == 0) {
		current_thread->cr3 = x64_read_cr3();

		/* check if the thread is user mode thread, if yes
		   than store the kernel esp */
		if (current_thread->priviledge == THREAD_LEVEL_USER)
			current_thread->kern_esp = get_kernel_tss()->rsp[0];

		/* now get the next runnable task from the thread list */
		next_task();

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
		interrupt_end (0);
#endif
		
		/** now return to the new task last stored instruction */


		if (current_thread->priviledge == THREAD_LEVEL_USER){
			get_kernel_tss()->rsp[0] = current_thread->kern_esp;
		}

		//x64_write_cr3 (current_thread->cr3);
		//mutex_unlock (scheduler_mutex);
		execute_idle (current_thread,get_kernel_tss());
	}

sched_end:
#ifdef USE_APIC
	apic_local_eoi();
#endif
#ifdef USE_PIC
	interrupt_end(0);
#endif
	//x64_sti();
	
}


//! Start the scheduler engine
void scheduler_start () {
	x64_cli();
#ifdef USE_APIC
	setvect(0x40, scheduler_isr);
#endif
#ifdef USE_PIC
	interrupt_set(0,scheduler_isr,0);
#endif
	x64_sti();
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
	list_add (blocked_list,thread);
}



//! Iterate through block list and find a specific thread
thread_t* thread_iterate_block_list (int id) {
	if (blocked_list->pointer >0)
		for (int i = 0; i < blocked_list->pointer; i++) {
			thread_t*  t = (thread_t*)list_get_at (blocked_list,i);
			if (t->id == id) {
				return t;
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
		if (blocked_list->pointer >0)
			for (int i = 0; i < blocked_list->pointer; i++) {
				thread_t*  t = (thread_t*)list_get_at (blocked_list,i);
				if (t->name == name) {
					return t->id;
				}
			}
	}

	return NULL;
}

//!unblock a thread
void unblock_thread (thread_t *t) {
	x64_cli();
	t->state = THREAD_STATE_READY;
	thread_insert (t);
	for (int i = 0; i < blocked_list->pointer; i++) {
		thread_t *thr = (thread_t*)list_get_at(blocked_list,i);
		if (thr == t) 
			list_remove (blocked_list,i);
	}
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

