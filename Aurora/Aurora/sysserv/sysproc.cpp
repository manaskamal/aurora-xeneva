#include <proc.h>
#include <procmngr.h>

void create__sys_process (const char* name) {
	x64_cli();
	/*procmngr_queue *queue = (procmngr_queue*)pmmngr_alloc();
	strcpy(queue->name, "uproc");
	strcpy(queue->path,name);
	procmngr_add_process (queue);
	procmngr_wakeup();*/
	create_process (name, "uproc", 1);
}

//!Exit System call
void sys_exit () {
	x64_cli();
	kill_process ();
	force_sched();
}