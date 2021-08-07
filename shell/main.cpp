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

void main () {
	print_text ("\n");
	print_text ("Copyright (C) Manas Kamal Choudhury 2021\n");
	print_text ("Operating System : Aurora's Xeneva v1.0\n");
	print_text ("XNShell v1.0\n");

	message_t msg;
	while(1) {
		message_receive (&msg);

		if (msg.type == 3) {
			print_text ("XNShell Key Pressed\n");
			memset(&msg,0,sizeof (message_t));
		}

		sched_wait();
	}
}