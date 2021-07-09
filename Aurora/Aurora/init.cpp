/** 
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  init.cpp -- Initialization of the kernel Aurora
 *
 *  /PROJECT - Aurora v1.0
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *======================================================
 */

#include <_xnboot.h>
#include <hal.h>
#include <pmmngr.h>
#include <mm.h>
#include <console.h>
#include <stdio.h>
#include <drivers\kybrd.h>
#include <drivers\mouse.h>
#include <drivers\ata.h>
#include <drivers\pci.h>
#include <drivers\svga\vmsvga.h>
#include <drivers\svga\svga_screen.h>
#include <drivers\vga.h>
#include <ipc\evntsh.h>
#include <ipc\message.h>
#include <ipc\dwm_ipc.h>
#include <vfs.h>
#include <fs\fat32.h>
#include <screen.h>
#include <proc.h>
#include <pmmngr.h>
#include <drvmngr.h>


#ifdef ARCH_X64
#include <arch\x86_64\thread.h>
#endif


//! the main entry point of the kernel
//! @param info -- The boot information passed by
//!                XNLDR 

void _kmain (KERNEL_BOOT_INFO *info) {
	hal_init ();
	pmmngr_init (info);
	mm_init(); 
	console_initialize(info);
	kybrd_init();
	
	//!initialize runtime drivers
	ata_initialize();
	initialize_vfs();
	initialize_screen(info);

	svga_init ();
	initialize_mouse();
	message_init ();
	dwm_ipc_init();
	
	//!initialize every drivers
	driver_mngr_initialize(info);

#ifdef ARCH_X64
	initialize_scheduler();
	create_process ("dwm.exe","dwm",20);
	//! task list should be more than 4 or less than 4 not 
	create_process ("dwm2.exe", "dwm2", 1);
	//create_process ("dwm3.exe", "dwm3", 1);
	scheduler_start();
#endif
	while(1) {
	}
}