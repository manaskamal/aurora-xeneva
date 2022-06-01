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
#include <xebase.h>
#include <sys\_xeneva.h>
#include <sys\_sleep.h>




//#define KEY 0x1234
/*
 * main -- the main entry point of init
 */
XE_EXTERN XE_EXPORT int XeMain (int argc, char* argv[]) {
	
	sys_print_text ("Init process started %d %d %d %d \r\n", 10, 20, 30, 40);
	void* ptr = mmap (0,8192,0,0,0,64);
	sys_print_text ("Ptr returned -> %x \r\n", ptr);
	void* p = malloc(16);
	sys_print_text ("P -> %x \n", p);
	while(1) {
		sys_sleep(1000);
	}
	return 0;
}