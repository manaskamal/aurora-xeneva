/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  procmngr.cpp -- Process Manager
 *
 *  /PROJECT - Aurora Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ================================================
 */

#include <procmngr.h>
#include <arch\x86_64\thread.h>
#include <ipc\message.h>
#include <proc.h>
#include <_null.h>

static procmngr_queue *top = NULL;
static int process_count = 0;
#define PROCESS_CREATE 10
bool waked = false;

void procmngr_add_process (procmngr_queue *queue) {
	procmngr_queue * temp = queue;

	temp->link = top;
	top = temp;
	process_count++;
}

procmngr_queue* procmngr_get_process () {
	procmngr_queue *temp = NULL;
	if (top != NULL) {
		temp = top;
		top = top->link;
		temp->link = NULL;
		pmmngr_free(temp);
		process_count--;
		return temp;
	}
	return NULL;
}

void procmngr_create_process (procmngr_queue *queue) {
	x64_cli();
	create_process (queue->path,queue->name,1, "0");
	x64_sti();
}


void procmngr_wakeup () {
	thread_t *proc_thr = (thread_t*)thread_iterate_block_list (3);
	if (proc_thr != NULL) {
		if (!waked) {
			waked = true;
			unblock_thread (proc_thr);
		}
	}
}


void procmngr_start () {
	procmngr_queue *queue;
	while (1) {
		if (process_count > 0) {
			for (int i = 0; i < process_count; i++) {
				queue = procmngr_get_process ();
				procmngr_create_process (queue);
			}
		}

		waked = false;
		block_thread(get_current_thread());
		force_sched();
		//sleep_thread(get_current_thread(),1000);
	}
}