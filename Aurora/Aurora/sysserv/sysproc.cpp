#include <proc.h>


void create__sys_process (const char* name) {
	x64_cli();
	create_process(name, "child",1);
}