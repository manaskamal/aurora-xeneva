#include <sys/_term.h>
#include <sys/_process.h>
#include <sys/_wait.h>
#include <sys/shm.h>
#include <sys/mmap.h>
#include <sys/_file.h>
#include <stdlib.h>
#include <string.h>
#include <canvas.h>
#include <sys/ioquery.h>
#include <image.h>


#define KEY 0x1234
/*
 * main -- the main entry point of init
 */
int main (int argc, char* argv[]) {
	//sys_print_text ("Init process started %d %d %d %d\n", 10, 20, 30, 40);
	void* ptr = mmap (0,8192,0,0,0,64);
	while(1) {
		sys_wait();
	}
}