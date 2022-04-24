#include <sys/_term.h>
#include <sys/_process.h>
#include <sys/_wait.h>

/*
 * main -- the main entry point of init
 */
int main (int argc, char* argv[]) {
	sys_print_text ("Init process started \n");
	while(1) {
		sys_wait();
	}
}