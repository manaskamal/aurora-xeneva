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



int main (int argc, char*argv[]) {
	printf ("Copyright (C) Manas Kamal Choudhury\n");
	printf ("Dock v1.0\n");
	while(1) {
		sys_wait();
		//sys_sleep(100);
	}
}