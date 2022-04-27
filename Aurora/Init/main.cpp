#include <sys/_term.h>
#include <sys/_process.h>
#include <sys/_wait.h>
#include <sys/shm.h>
#include <sys/mmap.h>
#include <sys/_file.h>
#include <stdlib.h>
#include <string.h>

#define KEY 0x1234
/*
 * main -- the main entry point of init
 */
int main (int argc, char* argv[]) {
	sys_print_text ("Init process started \n");
	UFILE f;
	int fd = sys_open_file("/audrv.cnf", &f);
	sys_print_text ("File opened size -> %d , filedesc -> %d\n", f.size, fd);

	sys_print_text ("[Init]: Memory Mapping audrv.cnf file\n");
	void* ptr = mmap(NULL, f.size, 1,2,fd,0);
	uint8_t *ptr6 = (uint8_t*)ptr;

	sys_print_text ("[Init]: mmap successfull \n");

	sys_print_text ("[Init]: file content :- \n");
	sys_print_text ("      ");
	for (uint8_t i = 0; i < 40; i++)
		sys_print_text ("%c", ptr6[i]);

	while(1) {
		sys_wait();
	}
}