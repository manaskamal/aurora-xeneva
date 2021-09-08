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

#include <xnsys.h>

char *manas = 0;
extern "C" void shl_print(const char* txt);
void func_call () {
}
void thread_1 () {
	manas = "Manas";
	print_text ("User inner thread spawned %s\n",manas);
	print_text ("Hello Multi-threading world\n");
	while(1) {
	}
}

void thread_2 () {
	manas = "Kamal";
	print_text ("User inner thread 2\n");
	print_text ("Multi threading World from thread 2  %s\n", manas);
	while(1) {
	}
}
void main () {
	print_text ("\n");
	print_text ("Copyright (C) Manas Kamal Choudhury 2021\n");
	print_text ("Operating System : Aurora's Xeneva v1.0\n");
	print_text ("XNShell v1.0\n");
	print_text ("Shell created thread\n");
	create_uthread (thread_1);
	create_uthread (thread_2);

	/*uint32_t status = fork();
	if (status)
		print_text ("Current process forked\n");
	exec ("dwm3.exe", status);*/
	message_t msg;
	while(1) {
		message_receive (&msg);

		if (msg.type == 3) {
			print_text ("Hello\n");
			memset(&msg,0,sizeof (message_t));
		}

		sched_wait();
	}
}