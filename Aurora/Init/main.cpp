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
	int master,  slave = 0;
	sys_ttype_create(&master, &slave);
	sys_print_text ("Master fd -> %d, slave fd -> %d \r\n", master, slave);
	uint8_t *out_buffer = (uint8_t*)malloc(512);
	uint8_t *in_buffer = (uint8_t*)malloc(512);

	memset(out_buffer, 'M', 512);
	memset(in_buffer,0, 512);

	UFILE f;
	f.flags = 0;
	f.size = 512;
	sys_write_file(slave,(uint64_t*)out_buffer, &f);

	while(1) {
		sys_read_file(slave, in_buffer,NULL);
		for (int i = 0; i < 512; i++)
			sys_print_text ("%c", in_buffer[i]);
		sys_wait();
	}
	return 0;
}