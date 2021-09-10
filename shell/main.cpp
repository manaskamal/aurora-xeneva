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
#include <sys\ioquery.h>
#include <stdlib.h>

void main (int argc, char*argv[]) {
	sys_print_text ("\n");
	sys_print_text ("Copyright (C) Manas Kamal Choudhury 2021\n");
	sys_print_text ("Operating System : Aurora's Xeneva v1.0\n");
	sys_print_text ("XNShell v1.0\n");
	sys_print_text ("Shell created thread\n");
	ioquery(IO_QUERY_SVGA, 0x201, 0);

	while(1) {
		sys_print_text ("Shell Loop\n");
		sys_wait();
	}
}