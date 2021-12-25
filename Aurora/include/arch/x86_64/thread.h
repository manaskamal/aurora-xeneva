/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  thread.h -- Manages multitasking of the entire system
 *  manages threads states, scheduling, creation and deletion
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *==============================================
 */

#ifndef __THREAD_H__
#define __THREAD_H__

#include <stdint.h>
#include <utils\list.h>
#include <ipc\signals.h>
#include <fs\vfs.h>
#include <stream.h>
#include <mm.h>


//! ====Thread States======================================================
//! THREAD_STATE_READY -- set a thread for next runnable
//! THREAD_STATE_BLOCKED -- this bit is set when the thread is blocked for 
//! some reason
//! THREAD_STATE_SLEEP -- this bit is set when the thread is in sleep mode

#define  THREAD_STATE_READY  1
#define  THREAD_STATE_BLOCKED 3
#define  THREAD_STATE_SLEEP 4

//! Thread levels =========================================================
//! THREAD_LEVEL_KERNEL -- This bit is set when the thread given is kernel mode
//! THREAD_LEVEL_USER -- This bit is set when the thread given is user mode
#define  THREAD_LEVEL_KERNEL 1
#define  THREAD_LEVEL_USER 2

#define  QUANTUM  4  //4 runs/ticks



//! THREAD STRUCTURE
typedef struct _thread_ {
	uint64_t ss;       //0x00
	uint64_t *rsp;      //0x08
	uint64_t rflags;   //0x10
	uint64_t cs;       //0x18
	uint64_t rip;      //0x20

	uint64_t rax;      //0x28
	uint64_t rbx;      //0x30
	uint64_t rcx;      //0x38
	uint64_t rdx;      //0x40
	uint64_t rsi;       //0x48
	uint64_t rdi;       //0x50
	uint64_t rbp;       //0x58
	uint64_t r8;        //0x60
	uint64_t r9;        //0x68
	uint64_t r10;        //0x70
	uint64_t r11;        //0x78
	uint64_t r12;        //0x80
	uint64_t r13;        //0x88
	uint64_t r14;        //0x90
	uint64_t r15;        //0x98
	uint64_t ds;         //0xA0
	uint64_t es;         //0xA8
	uint64_t fs;         //0xB0
	uint64_t gs;         //0xB8
	uint64_t cr3;        //0xC0     [0x08]
	uint64_t kern_esp;   //0xC8     [0x10]
	bool _is_user;       //0xD0
	char* name;
	uint8_t state;
	uint16_t id;
	uint8_t priviledge;
	uint16_t quanta;
	uint64_t ttype;
	uint64_t* msg_box;
	uint64_t* qu_box;
	uint8_t priority;
	vfs_node_t *fd[60];   //file descriptor
	int fd_current;
	uint8_t master_fd;
	uint8_t slave_fd;
	stream_t *stream;
	struct _thread_* next;
	struct _thread_* prev;
}thread_t;

typedef struct _uthread_ {
	void (*entry)(void*);
	struct _uthread_ *self_pointer;
}uthread;


//!****************************
//! FUNCTION PROTOTYPE
//!*****************************

//!initialize_scheduler -- initialize scheduler engine and creates all data structures
extern void initialize_scheduler ();

//!scheduler_start -- start the scheduler
extern void scheduler_start ();

//!create_user_thread -- creates a user thread entry
//!@param entry -- entry point address
//!@param stack -- stack address
//!@param cr3 -- top level paging structure for the thread
//!@param name -- name of the thread
//!@param priority -- (currently not used) sets the priority level of the thread
extern thread_t* create_user_thread (void (*entry) (void*),uint64_t stack,uint64_t cr3, char name[8], uint8_t priority);

//!create_kthread -- creates a kernel thread entry
//! @param entry -- entry point address
//! @param stack -- stack address of the kernel thread
//! @param cr3 -- top level paging structure for the thread
//! @param name -- name of the thread
//! @param priority -- (currently not used)priority of the thread 
extern thread_t* create_kthread (void (*entry) (void), uint64_t stack,uint64_t cr3, char name[8], uint8_t priority);

//! block_thread -- blocks a thread entry
//! @param thread -- thread address to block
extern void block_thread (thread_t *thread);

//! unblock_thread --unblocks a thread entry
//! @param thread -- thread address to unblock
extern void unblock_thread (thread_t *thread);

//! get_current_thread -- get current thread
//! @return -- returns the currently running thread to the caller
extern thread_t * get_current_thread ();

//!set_multi_task_enable -- enable or disable multi tasking
//! @param value -- enable/disable multitask bit
extern void set_multi_task_enable (bool value);

//!is_multi_task_enable -- check if multi tasking is enable
//!@return -- true if enabled else false if disabled
extern bool is_multi_task_enable ();

//!foce_sched -- force the scheduler to task switch
extern void force_sched();

//!thread_iterate_ready_list -- iterate through ready list and return a specific thread
//! @param id -- id of the thread to search 
//! @return -- found thread address
extern thread_t * thread_iterate_ready_list (uint16_t id);

//!thread_iterate_block_list -- iterate through block list and return a specific blocked 
//! thread
//! @param id -- id of the thread to search
//! @return -- thread address if found
extern thread_t* thread_iterate_block_list (int id);

//!thread_get_id_by_name --Get thread id by its name
//! @return -- thread id
extern uint16_t thread_get_id_by_name (char* name);

//!save_context -- save current processor register context
//! to threads context
//! @param t -- thread address to store to
//! @param tss -- tss address 
extern "C" int save_context (thread_t *t,void *tss);

//! execute_idle -- execute the current processor register from 
//! given thread context
//! @param thread -- thread address from where to load
//! @param tss -- tss address
extern "C" void execute_idle(thread_t* thread, void* tss);

//! set_current_thread -- sets the current thread address to specific thread address
//! @param thread -- thread address to set to current_thread 
extern void set_current_thread (thread_t *thread);

//! sleep_thread -- causes a specific thread to sleep for some times
//! @param t -- thread address 
//! @param ms -- time to sleep in milliseconds
extern void sleep_thread (thread_t *t, uint64_t ms);

//! task_delete -- delete a specific task from thread list
//! @param thread -- address of the thread to delete
extern void task_delete (thread_t* thread);

//! is_scheduler_initialized -- checks and return if scheduler initialized or not
//! @return --- initialized bit
extern bool is_scheduler_initialized ();

//! sched_get_tick -- get the system tick incremented
//! @return -- system ticks incremented in integer number 
extern uint32_t sched_get_tick();


#endif