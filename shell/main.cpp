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
#include <sys\_process.h>
#include <sys\ioquery.h>
#include <sys\mmap.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <canvas.h>
#include <setjmp.h>

#define SSFN_CONSOLEBITMAP_TRUECOLOR

#define PI  3.14159265

typedef struct _data_ {
	uint8_t i;
	uint8_t j;
	uint8_t k;
	uint32_t data4;
	uint8_t *p;
	uint8_t ch[32];
}data_t;

void main (int argc, char*argv[]) {
	sys_print_text ("Starting Xeneva.....\n");
	sys_print_text ("Starting Window Manager...\n");
	//int fd = sys_open_file ("/dev/fb",NULL);
	//UFILE f;
	//f.flags = 0;
	//f.size = 100*100*32;
	//uint8_t* buffer = (uint8_t*)0xFFFFD00000200000;  //malloc(100*100*32);
	//for (int i = 0; i < 100; i++)
	//	for (int j = 0; j < 100; j++)
	//		buffer[0+i * 1280 + 0 + j] = 0xFFFFFFFF;

	//sys_write_file (fd,buffer,&f);
	/*int fd;

	unsigned char *data = (unsigned char*)malloc(sizeof(data_t));
	data_t *d = (data_t*)data;
	d->i = 10;
	d->j = 11;
	d->data4 = 1280;
	d->k = 12;
	d->p = (uint8_t*)0x0000D00000000000;
	memset(d->ch, 0, 32);
	strcpy ((char*)d->ch,"Hello");
	sys_pipe(&fd,NULL);
	UFILE file;
	file.size = 32;
	file.flags = 0;
	sys_write_file (fd,data,&file);*/
	///message_t msg;
	while(1) {
		//sys_wait();
	}
}

