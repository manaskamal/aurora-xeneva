#include <proc.h>


void create__sys_process (const char* name) {
	x64_cli();
	create_process(name, "child",1);
}

//!Exit System call
void sys_exit () {
	x64_cli();
	kill_process ();
	force_sched();
}