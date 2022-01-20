/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  main.cpp -- The main entry for Dock 
 *
 *  /PROJECT - Aurora's Xeneva v1.0
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *===============================================
 */

#include <stdint.h>
#include <sys\_wait.h>
#include <sys\_ipc.h>
#include <sys\ioquery.h>
#include <sys\_file.h>
#include <sys\pe.h>
#include <QuWindow.h>
#include <QuBase.h>
#include <sys\postbox.h>
#include <acrylic.h>
#include <font.h>
#include <color.h>
#include <string.h>
#include <sys\_sleep.h>
#include <stdio.h>
#include <sys\_process.h>
#include <sys\_term.h>
#include <daisy.h>
#include <daisy_window.h>

typedef int (*test_num) ();

int main (int argc, char*argv[]) {
	/*printf ("Copyright (C) Manas Kamal Choudhury 2020-2022\n");
	printf ("Dock v1.0 -- Console testing app\n");

	UFILE uf;
	int fd = sys_open_file ("/sb16.dll",&uf);
	unsigned char* buffer = (unsigned char*)malloc(uf.size);
	sys_read_file (fd, buffer, &uf);

	test_num tn = (test_num)GetProcAddress(buffer,"test_num");
	int n = tn();
	printf ("DLL Returned -> %d\n", n);*/
	/*while(1) {
		sys_wait();
	}*/
	daisy_application();
	daisy_window_t *win = daisy_window_create (10,10,500,300,NULL);
	daisy_win_info_t *info = daisy_get_window_info(win);
	daisy_window_set_title(win, "dock");
	daisy_window_show(win);
	while(1) {
		pri_event_t *e = daisy_get_gifts();
		daisy_window_service_event(win,e);
	}
}