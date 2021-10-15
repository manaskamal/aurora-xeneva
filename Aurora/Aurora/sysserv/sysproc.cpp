#include <proc.h>
#include <procmngr.h>


void create__sys_process (const char* name, char* procnm) {
	procmngr_queue *queue = (procmngr_queue*)pmmngr_alloc();
	strcpy(queue->name, procnm);
	strcpy(queue->path,name);
	procmngr_add_process (queue);
	procmngr_wakeup();
	//create_process (name, procnm, 1, NULL);
}

//!Exit System call
void sys_exit () {
	x64_cli();	
	kill_process ();
	force_sched();
}

//! Send a signal to a process or process group
void sys_kill (int pid, int signo) {
	//x64_cli();
	/*thread_t * t = (thread_t*)thread_iterate_ready_list(pid);
	if (t == NULL) {
		t = (thread_t*)thread_iterate_block_list(pid);
	}

	if (t == NULL)
		return;

	t->signal_interrupt = true;*/

	kill_process_by_id(pid);
	force_sched();
	//! For now, no signals are supported, just kill the process
}

void sys_set_signal (int signo, sig_handler handler) {
	x64_cli();
	get_current_thread()->signals[signo] = handler;
}