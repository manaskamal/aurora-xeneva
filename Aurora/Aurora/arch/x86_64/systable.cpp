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
extern "C" void x64_syscall_handler (void* a) {

	//! get the index number
	int idx = (int)a;

	//! check for index limit
	if (idx > 256) {
		printf ("System Call Fault!! Halting System\n");
		for(;;);  //Loop forever for now
	}
	
	//! update the function pointer to syscall table index
	funct = (uint64_t*)_syscalls[idx];

	//return to the caller
}