#include <stdint.h>
#include <arch\x86_64\cpu.h>
#include <stdio.h>
#include <sysserv.h>

extern "C" uint64_t *funct = NULL;


//! System Call Handler Functions
//! @param a -- arg1 passed in r12 register
//! @param b -- arg2 passed in r13 register
//! @param c -- arg3 passed in r14 register
//! @param d -- arg4 passed in r15 register
extern "C" void x64_syscall_handler (int a) {

	//! get the index number
	int idx = a;

	//! check for index limit
	if (idx > 256) {
		printf ("System Call Fault!! Halting System\n");
		for(;;);  //Loop forever for now
	}

	switch (idx) {
	case 0:
		funct = (uint64_t*)printf;
		break;
	case 1:
		funct = (uint64_t*)wait;
		break;
	case 2:
		funct = (uint64_t*)create__sys_process;
		break;
	case 3:
		funct = (uint64_t*)copy_memory;
		break;
	case 4:
		funct = (uint64_t*)0;
		break;
	case 5:
		funct = (uint64_t*)valloc;
		break;
	case 6:
		funct = (uint64_t*)message_send;
		break;
	case 7:
		funct = (uint64_t*)message_receive;
		break;
	case 8:
		funct = (uint64_t*)map_shared_memory;
		break;
	case 9:
		funct = (uint64_t*)get_thread_id;
		break;
	case 10:
		funct = (uint64_t*)create_timer;
		break;
	case 11:
		funct = (uint64_t*)destroy_timer;
		break;
	case 12:
		funct = (uint64_t*)0;
		break;
	case 13:
		funct = (uint64_t*)ttype_create;
		break;
	case 14:
		funct = (uint64_t*)start_timer;
		break;
	case 15:
		funct = (uint64_t*)pause_timer;
		break;
	case 16:
		funct = (uint64_t*)allocate_pipe;
		break;
	case 17:
		funct = (uint64_t*)sys_unblock_id;
		break;
	case 18:
		funct = (uint64_t*)create_uthread;
		break;
	case 19:
		funct = (uint64_t*)sys_open_file;
		break;
	case 20:
		funct = (uint64_t*)sys_read_file;
		break;
	case 21:
		funct = (uint64_t*)ttype_dup_master;
		break;
	case 22:
		funct = (uint64_t*)sys_get_used_ram;
		break;
	case 23:
		funct = (uint64_t*)sys_get_free_ram;
		break;
	case 24:
		funct = (uint64_t*)sys_sleep;
		break;
	case 25:
		funct = (uint64_t*)sys_exit;
		break;
	case 26:
		funct = (uint64_t*)sys_attach_ttype;
		break;
	case 27:
		funct = (uint64_t*)fork;
		break;
	case 28:
		funct = (uint64_t*)exec;
		break;
	case 29:
		funct = (uint64_t*)map_memory;
		break;
	case 30:
		funct = (uint64_t*)unmap_memory;
		break;
	case 31:
		funct = (uint64_t*)ioquery;
		break;
	case 32:
		funct = (uint64_t*)sys_get_current_time;
		break;
	case 33:
		funct = (uint64_t*)sys_get_system_tick;
		break;
	case 34:
		funct = (uint64_t*)sys_kill;
		break;
	case 35:
		funct = (uint64_t*)sys_set_signal;
		break;
	case 36:
		funct = (uint64_t*)unmap_shared_memory;
		break;
	case 37:
		funct = (uint64_t*)sys_write_file;
		break;
	case 38:
		funct = (uint64_t*)vfree;
		break;
	}

	
	//! update the function pointer to syscall table index
	//funct = (uint64_t*)_syscalls[idx];

	//return to the caller
}