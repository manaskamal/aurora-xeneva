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
extern "C" void shl_test ();
void func_call () {
}
void thread_1 (void* p) {
	func_call();
	shl_test ();
	for(;;);
}
void main () {
	print_text ("\n");
	print_text ("Copyright (C) Manas Kamal Choudhury 2021\n");
	print_text ("Operating System : Aurora's Xeneva v1.0\n");
	print_text ("XNShell v1.0\n");
	print_text ("Shell created thread\n");
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