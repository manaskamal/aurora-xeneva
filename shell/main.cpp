/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  main.cpp -- The main shell program entry file
 *
 *  /PROJECT - Aurora Xeneva {XNShell}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ====================================================
 */

#include <sys\_term.h>
#include <sys\_wait.h>
#include <sys\_exit.h>
#include <sys\_ipc.h>
#include <sys\_process.h>
#include <sys\ioquery.h>
#include <string.h>
#include <stdlib.h>


extern "C" void *syscall_data = NULL;

#pragma pack (push,1)
typedef struct _regs_ {
	uint64_t rcx;
	uint64_t rdx;
	uint64_t r8;
	uint64_t r9;
}regs_t;
#pragma pack(pop)


void call_this (int a, char* m) {
	int b = a + 2;
	char *p = m;
}

void main (int argc, char*argv[]) {
	sys_print_text ("\n");
	sys_print_text ("Copyright (C) Manas Kamal Choudhury 2021\n");
	sys_print_text ("Operating System : Aurora's Xeneva v1.0\n");
	sys_print_text ("XNShell v1.0\n");
	sys_print_text ("Shell created thread\n");

	call_this (100,"Manas");
	message_t msg;
	while(1) {
		message_receive(&msg);

		if(msg.type == 3) {
			sys_print_text ("Key pressed\n");
		}

		//sys_print_text ("Shell Loop\n");
		sys_wait();
	}
}