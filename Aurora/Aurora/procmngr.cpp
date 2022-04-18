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
bool waked = false;

void procmngr_add_process (procmngr_queue *queue) {
	procmngr_queue * temp = queue;

	temp->link = top;
	top = temp;
	process_count++;
}

void procmngr_remove_process (uint16_t id) {
	kill_process_by_id (id);
}

procmngr_queue* procmngr_get_process () {
	procmngr_queue *temp = NULL;
	if (top != NULL) {
		temp = top;
		top = top->link;
		temp->link = NULL;
		return temp;
	}
	return NULL;
}

void procmngr_create_process (procmngr_queue *queue) {
	x64_cli();
	create_process (queue->path,queue->name);
	AuPmmngrFree(queue);
	x64_sti();
}


void procmngr_wakeup () {
	x64_cli();
	thread_t *proc_thr = thread_iterate_block_list (3);
	if (proc_thr != NULL) {
		unblock_thread (proc_thr);
	}else {
		proc_thr = thread_iterate_ready_list(3);
		printf ("Proc mngr is already awake-> %x\n", proc_thr);
		block_thread(proc_thr);
		force_sched();
	}
	x64_sti();
}


void procmngr_start () {
	procmngr_queue *queue;
	while (1) {
		for (int i = 0; i < process_count; i++) {
			queue = procmngr_get_process ();
			if (queue->type == PROCESS_CREATE) {
				procmngr_create_process (queue);
				break;
			}

			if (queue->type == PROCESS_DESTROY) {
				procmngr_remove_process(queue->id);
				AuPmmngrFree(queue);
				break;
			}
		}

		process_count = 0;

	    block_thread(get_current_thread());
	    force_sched();
	}
	
}