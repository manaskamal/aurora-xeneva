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
#include <sys\_file.h>
#include <sys\_process.h>
#include <sys\ioquery.h>
#include <sys\mmap.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <canvas.h>
#include <setjmp.h>
#include <ttf\ttf.h>

#define SSFN_CONSOLEBITMAP_TRUECOLOR

#define PI  3.14159265

void main (int argc, char*argv[]) {
	sys_print_text ("\n");
	sys_print_text ("Copyright (C) Manas Kamal Choudhury 2021\n");
	sys_print_text ("Operating System : Aurora's Xeneva v1.0\n");
	sys_print_text ("XNShell v1.0\n");
	sys_print_text ("Shell created thread\n");

	message_t msg;
	while(1) {
		//sys_print_text ("Shell Loop\n");
		sys_wait();
	}
}

