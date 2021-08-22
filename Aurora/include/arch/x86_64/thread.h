/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  thread.h -- Multi tasking
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *==============================================
 */

#ifndef __THREAD_H__
#define __THREAD_H__

#include <stdint.h>
#include <string.h>
#include <utils\list.h>
#include <mm.h>

#define  THREAD_STATE_READY  1
#define  THREAD_STATE_BLOCKED 3
#define  THREAD_STATE_SLEEP 4

#define  THREAD_LEVEL_KERNEL 1
#define  THREAD_LEVEL_USER 2

#define  QUANTUM  4  //4 runs/ticks

#pragma pack (push)
typedef struct _trap_frame_ {
	uint64_t gs;
	uint64_t fs;
	uint64_t es;
	uint64_t ds;

	uint64_t rax;
	uint64_t rbx;
	uint64_t rcx;
	uint64_t rdx;
	uint64_t rsi;
	uint64_t rdi;
	uint64_t rsp;
	uint64_t rbp;
	uint64_t r8;        //0x60
	uint64_t r9;        //0x68
	uint64_t r10;        //0x70
	uint64_t r11;        //0x78
	uint64_t r12;        //0x80
	uint64_t r13;        //0x88
	uint64_t r14;        //0x90
	uint64_t r15;        //0x98
	uint64_t rip;
	uint64_t cs;
	uint64_t flags;
}trap_frame;

#pragma pack (pop)

//! THREAD STRUCTURE
typedef struct _thread_ {
	//uint64_t stack;   //0x00
	uint64_t ss;       //0x00
	uint64_t rsp;      //0x08
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
	uint64_t blocked_stack_resv;
	uint64_t* mouse_box;
	uint8_t priority;
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

//!initialize scheduler engine and creates all data structures
extern void initialize_scheduler ();

//! start the scheduler
extern void scheduler_start ();

//! creates a user thread entry
extern thread_t* create_user_thread (void (*entry) (void*),uint64_t stack,uint64_t cr3, char name[8], uint8_t priority);

//! creates a kernel thread entry
extern thread_t* create_kthread (void (*entry) (void), uint64_t stack,uint64_t cr3, char name[8], uint8_t priority);

//! blocks a thread entry
extern void block_thread (thread_t *thread);

//! unblocks a thread entry
extern void unblock_thread (thread_t *thread);

//! get current thread
extern thread_t * get_current_thread ();

//! enable or disable multi tasking
extern void set_multi_task_enable (bool value);

//! check if multi tasking is enable
extern bool is_multi_task_enable ();

//! force the scheduler to task switch
extern void force_sched();

//! iterate through ready list and return a specific thread
extern thread_t * thread_iterate_ready_list (uint16_t id);

extern thread_t* thread_iterate_block_list (int id);

extern "C" int save_context (thread_t *t,void *tss);

extern "C" void execute_idle(thread_t* stack, void* tss);

extern void set_sched_debug (bool value);

extern void set_current_thread (thread_t *thread);

extern void sleep_thread (thread_t *t, uint64_t ms);

extern void task_delete (thread_t* thread);

extern bool is_scheduler_initialized ();
#endif