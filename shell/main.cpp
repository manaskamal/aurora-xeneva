/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  main.cpp -- The main shell program entry file
 *
 *  /PROJECT - Aurora Xeneva {XNShell}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ====================================================
 */

#include <sys\_term.h>
#include <sys\_wait.h>
#include <sys\_exit.h>
#include <sys\_ipc.h>
#include <sys\_file.h>
#include <sys\_sleep.h>
#include <sys\pe.h>
#include <sys\_process.h>
#include <sys\_xeneva.h>
#include <sys\ioquery.h>
#include <sys\mmap.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <setjmp.h>

#include "sndsrv.h"

int pri_event_fd = 0;

extern "C" void shl_test();

/**
 * snd_share_buffer -- shares the sound buffer to desired app
 * @param to_id -- requested application id
 */
void snd_share_buffer (int to_id) {
	sys_copy_mem(to_id,0x000000E000000000,8 * 1024 * 1024);

	pri_event_t e;
	memset(&e, 0, sizeof(pri_event_t));
	e.type = SND_SRV_BUFFER_READY;
	e.to_id = to_id;
	e.p_value = (uint32_t*)0x000000E000000000;
	e.dword = (8*1024*1024); //size
	e.from_id = get_current_pid();
	ioquery(pri_event_fd,PRI_LOOP_PUT_EVENT,&e);
}


/*
 * main -- main entry point
 * @param argc -- system argument
 * @param argv -- system argument 2
 */
void main (int argc, char*argv[]) {

	sys_print_text ("Sound Service v0.1 \r\n");
	sys_print_text ("Copyright (C) Manas Kamal Choudhury 2022 \r\n");

	uint64_t mem = sys_get_used_ram();
	sys_print_text ("PhysicaL MEMORY MB -> %d MB \r\n", mem / 1024 / 1024);

	void *p = malloc(4096 *2);
	memset(p, 0, 4096*2);

	/*int snd_fd = sys_open_file ("/dev/snd",NULL);
	pri_event_fd = sys_open_file ("/dev/pri_loop", NULL);
	ioquery (pri_event_fd, PRI_LOOP_CREATE, NULL);

	for (int i = 0; i < 8 * 1024 * 1024 / 4096; i++) {
		valloc(0x000000E000000000 + i * 4096);
		uint64_t* p = (uint64_t*)(0x000000E000000000 + i * 4096);
	}
	memset((void*)0x000000E000000000,0,8*1024*1024);
	UFILE file;
	file.flags = NULL;
	file.size = 0x100000;

	uint32_t *buffer_p = (uint32_t*)0x000000E000000000;
	uint32_t *buffer_p_current = (uint32_t*)buffer_p;
	pri_event_t e;*/
	//exit(0);
	while(1) {
		/*ioquery(pri_event_fd, PRI_LOOP_GET_EVENT,&e);
		if (e.type != 0) {

			if (e.type == SND_SRV_REQUEST_BUFFER) {
				snd_share_buffer(e.from_id);
				memset(&e, 0, sizeof(pri_event_t));
			}

			if (e.type == SND_SRV_ADD_PCM) {
				sys_print_text ("PCM Data Added\n");
				sys_write_file (snd_fd,(unsigned char*)buffer_p,&file);
				memset(&e, 0, sizeof(pri_event_t));
			}

			if (e.type == SND_SRV_REQUEST_NEXT) {
				sys_write_file (snd_fd,(unsigned char*)(buffer_p + 0x100000),&file);
				buffer_p += 0x100000;
				memset(&e, 0, sizeof(pri_event_t));
			}

			if (e.type == SND_SRV_PLAY_AUDIO) {
				ioquery (snd_fd,SOUND_PLAY,NULL);
				memset(&e, 0, sizeof(pri_event_t));
			}


		}
		*/
		sys_wait();
	}
}

