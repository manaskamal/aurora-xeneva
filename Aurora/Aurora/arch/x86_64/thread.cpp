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
#include <stdio.h>
#include <atomic\mutex.h>
#include <utils\lnklist.h>

/**
 ** E X T E R N A L  S T A T I C  S Y M B O L S
 **/
extern "C" void x64_hlt();
extern "C" void force_sched_pic ();
extern "C" void force_sched_apic ();
/** ============================================
 ** Global initializers
 ** ============================================
 **/


bool  scheduler_enable = false;
mutex_t * block_mutex;
mutex_t * scheduler_mutex;
bool  scheduler_initialized = false;
uint16_t task_id = 0;

list_t *blocked_list;
thread_t *task_list_head = NULL;
thread_t *task_list_last = NULL;
extern "C" thread_t *current_thread = NULL;


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

	pmmngr_free (thread);
}
/*=========================================================================================*/
/*=========================================================================================*/
/*=========================================================================================*/

/**
 * ! Creates a kernel mode thread
 **/
thread_t* create_kthread (void (*entry) (void), uint64_t stack,uint64_t cr3, char name[8], uint8_t priority)
{
	thread_t *t = (thread_t*)pmmngr_alloc();
	t->ss = 0x10;
	t->rsp = stack;
	t->rflags = 0x202;
	t->cs = 0x08;
	t->rip = (uint64_t)entry;
	t->rax = 0;
	t->rbx = 0;
	t->rcx = 0;
	t->rdx = 0;
	t->rsi = 0;
	t->rdi = 0;
	t->rbp = t->rsp;
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
	t->_is_user = 0;
	t->cr3 = cr3;
	t->name = name;
	t->id = task_id++;
	t->quanta = 0;
	t->priviledge = THREAD_LEVEL_KERNEL;
	t->state = THREAD_STATE_READY;
	t->priority = priority;
	thread_insert(t);
	return t;
}

/**
 *  Creates a user mode thread
 */
thread_t* create_user_thread (void (*entry) (void*),uint64_t stack,uint64_t cr3, char name[8], uint8_t priority)
{
	thread_t *t = (thread_t*)pmmngr_alloc();
	t->ss = SEGVAL(GDT_ENTRY_USER_DATA,3);//0x23;
	t->rsp = stack;
	t->rflags = 0x286;
	t->cs = SEGVAL (GDT_ENTRY_USER_CODE,3);// 0x2b;
	t->rip = (uint64_t)entry;
	t->rax = 0;
	t->rbx = 10;
	t->rcx = 0;
	t->rdx = 0;
	t->rsi = 10;
	t->rdi = 0;
	t->rbp = t->rsp;
	t->r8 = 0;
	t->r9 = 0;
	t->r10 = 0;
	t->r11 = 0;
	t->r12 = 0;
	t->r13 = 0;
	t->r14 = 0;
	t->r15 = 0;
	t->kern_esp = (uint64_t)pmmngr_alloc();
	t->ds = 0x23;
	t->es = 0x23;
	t->fs = 0x23;
	t->gs = 0x23;
	t->cr3 = cr3;
	t->name = name;
	t->id = task_id++;
	t->quanta = 0;
	t->blocked_stack_resv = 0;
	t->mouse_box = (uint64_t*)pmmngr_alloc();
	t->_is_user = 1;
	t->priviledge = THREAD_LEVEL_USER;
	t->state = THREAD_STATE_READY;
	t->priority = priority;
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
	block_mutex = create_mutex();
	scheduler_mutex = create_mutex ();
	scheduler_enable = true;
	thread_t *idle_ = create_kthread (idle_thread,(uint64_t)pmmngr_alloc(),x64_read_cr3(),"Idle",1);
	current_thread = idle_;
}

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

	//if (task->state == THREAD_STATE_BLOCKED) {
	//	task = task->next;

	//	if (task == NULL) {
	//		task = task_list_head;
	//	}
	//	goto end;
	//}

	//if (task->next != NULL) {
	//	task = task->next;
	//} else {
	//	task = task_list_head;
	//}

end:
	current_thread = task;
}
/** ===============================================
 **  Scheduler Isr | Scheduler Isr
 ** ===============================================
 **/
void scheduler_isr (size_t v, void* param) {
	x64_cli();
	//interrupt_stack_frame *frame = (interrupt_stack_frame*)param;
	if (scheduler_enable == false)
		goto sched_end;
	mutex_lock (scheduler_mutex);
   
	if (save_context(current_thread,get_kernel_tss()) == 0) {
		current_thread->cr3 = x64_read_cr3();
		if (current_thread->priviledge == THREAD_LEVEL_USER)
			current_thread->kern_esp = get_kernel_tss()->rsp[0];
#ifdef USE_APIC
		apic_local_eoi();
#endif
#ifdef USE_PIC
		interrupt_end (0);
#endif
		next_task();
		if (current_thread->priviledge == THREAD_LEVEL_USER){
			get_kernel_tss()->rsp[0] = current_thread->kern_esp;
		}
		
		//x64_write_cr3 (current_thread->cr3);
		mutex_unlock (scheduler_mutex);
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
	scheduler_initialized = true;
	x64_cli();
#ifdef USE_APIC
	setvect(0x40, scheduler_isr);
#endif
#ifdef USE_PIC
	interrupt_set(0,scheduler_isr,0);
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

void set_sched_debug (bool value) {
	//debug = value;
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


void sleep_thread (thread_t *t, uint64_t ms) {
	t->quanta = ms;
	//printf ("Sleeping thread -> %d\n", t->quanta);
	t->state = THREAD_STATE_SLEEP;
}

//! returns currently running thread
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

bool is_scheduler_initialized () {
	return scheduler_initialized;
}