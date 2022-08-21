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

	int event = sys_open_file("/dev/pri_loop",NULL);
	ioquery(event, PRI_LOOP_CREATE, NULL);

	int fd = sys_open_file("/dev/dsp", NULL);
	ioquery (fd, SOUND_REGISTER_MEDIAPLAYER, NULL);
	
	UFILE file;
	int fdfile = sys_open_file ("/Ss.wav", &file);
	file.size = 1;
	uint8_t* buffer = (uint8_t*)malloc(4096);
	sys_read_file(fdfile,buffer, &file);

	UFILE sound;
	sound.flags = 0;
	sys_write_file(fd, (uint64_t*)buffer, &sound);

	pri_event_t ev;
	while(1) {
		ioquery(event,PRI_LOOP_GET_EVENT, &ev);
		if (ev.type != 0) {
		if (ev.type == 10) {
			if (file.eof != 1){
				sys_read_file(fdfile,buffer, &file);
				sys_write_file(fd, (uint64_t*)buffer, &sound);
					//sys_print_text ("Buffer -> %x , pos -> %d  ", buffer, pos);
			}
				
			/*if (file.eof)
				ioquery(fd, SOUND_STOP_OUTPUT, NULL);*/

			memset(&ev, 0, sizeof(pri_event_t));
		}
		}
		sys_wait();
	}
	return 0;
}