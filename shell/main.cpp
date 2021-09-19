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
#include <ssfn.h>

#define SSFN_CONSOLEBITMAP_TRUECOLOR

#define PI  3.14159265



void main (int argc, char*argv[]) {

	sys_print_text ("\n");
	sys_print_text ("Copyright (C) Manas Kamal Choudhury 2021\n");
	sys_print_text ("Operating System : Aurora's Xeneva v1.0\n");
	sys_print_text ("XNShell v1.0\n");
	sys_print_text ("Shell created thread\n");

	for (int i = 0; i < (52*1024)/ 4096; i++)
		valloc(0x0000070000000000 + i * 4096);
	FILE f;
	sys_open_file(&f,"a:Vera.sfn");
	unsigned char* binary_font_start = (unsigned char*)0x0000070000000000;

	sys_read_file(&f, binary_font_start, f.size);

	ssfn_src = (ssfn_font_t*)binary_font_start;
	ssfn_dst.ptr = (uint8_t*)0xFFFFF00000000000;
	ssfn_dst.p = 32;
	ssfn_dst.fg = 0xFFFFFFFF;
	ssfn_dst.bg = 0xFFFFFFFF;
	ssfn_dst.x = 500;
	ssfn_dst.y = 600;
	sys_print_text ("SSFN DST PTR -> %x\n", ssfn_dst.ptr);
	ssfn_putc('H');
	ssfn_putc('E');
	ssfn_putc('L');
	ssfn_putc('L');
	ssfn_putc('O');

	message_t msg;
	while(1) {
		message_receive(&msg);

		if(msg.type == 3) {
			sys_print_text ("Key pressed\n");
		}

		//sys_print_text ("Shell Loop\n");
		sys_wait();
	}
}