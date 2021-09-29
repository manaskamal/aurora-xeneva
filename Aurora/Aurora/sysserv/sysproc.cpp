#include <proc.h>
#include <procmngr.h>

void create__sys_process (const char* name, char* procnm) {
	//x64_cli();
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