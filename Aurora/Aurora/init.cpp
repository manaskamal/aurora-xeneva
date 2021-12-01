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
#include <drivers\svga\gmr.h>
#include <drivers\ac97\ac97.h>
#include <drivers\hdaudio\hda.h>
#include <drivers\vga.h>
#include <drivers\usb\xhci.h>
#include <drivers\net\e1000.h>
#include <drivers\net\amd_am79c973.h>
#include <drivers\rtc.h>
#include <drivers\acpi\acpi.h>
#include <drivers\vbox.h>
#include <ipc\evntsh.h>
#include <ipc\message.h>
#include <ipc\dwm_ipc.h>
#include <fs\fat32.h>
#include <fs\gpt.h>
#include <fs\vfs.h>
#include <screen.h>
#include <proc.h>
#include <pmmngr.h>
#include <drvmngr.h>
#include <procmngr.h>
#include <serial.h>
#include <stream.h>
#include <fs\ttype.h>

#include <net\arp.h>
#include <net\ethernet.h>
#include <net\nethw.h>
#include <utils\circ_buf.h>

#ifdef ARCH_X64
#include <arch\x86_64\thread.h>
#include <arch\x86_64\mmngr\map.h>
#include <arch\x86_64\cpu.h>
#include <arch\x86_64\pic.h>
#endif

typedef struct _wav_riff_ {
	char chunk_id[4];
	uint32_t chunk_size;
	char format[4];
}riff_t;

typedef struct _wav_fmt_ {
	char sub_chunk_1_id[4];
	uint32_t subchunk1_size;
	uint16_t audio_format;
	uint16_t num_channel;
	uint32_t sample_rate;
	uint32_t byte_rate;
	uint16_t block_align;
	uint16_t bits_per_sample;
}fmt_t;

typedef struct _wav_data_ {
	char sub_chunk2id[4];
	uint32_t subchunk2size;
}data_t;

typedef struct _wav_format_ {
	riff_t riff;
	fmt_t fmt;
	data_t data;
}wav;


//! the main entry point of the kernel
//! @param info -- The boot information passed by
//!                XNLDR 

extern "C" int _fltused = 1;

void* __cdecl ::operator new(size_t size) {
	return malloc(size);
}

void* __cdecl operator new[] (size_t size) {
	return malloc(size);
}

void __cdecl operator delete (void* p) {
	mfree(p);
}

extern "C" void test_sys (char* text);

void test_thread2 () {
	while(1) {
		//printf ("Multitasking\n");
	}
}
 
/**========================================
 ** the main entry routine -- _kmain
 **
 ** @param info -- Boot time information 
 **                passed to kernel by
 **                Xnldr
 **========================================
 */
void _kmain () {
	KERNEL_BOOT_INFO *info = (KERNEL_BOOT_INFO*)0xFFFFE00000000000;

	hal_init();
	//! Initialize the memory mappings
	pmmngr_init (info);
	vmmngr_x86_64_init();  
	hal_x86_64_setup_int();	

    mm_init(info); 
	initialize_serial();

	ata_initialize();
	vfs_init();
	initialize_screen(info);
	console_initialize(info);
	initialize_rtc(); 

	initialize_acpi (info->acpi_table_pointer);
	
	//!Initialize kernel runtime drivers	
	kybrd_init();
	initialize_mouse();

	message_init ();
	dwm_ipc_init();
    
	stream_init ();
	driver_mngr_initialize(info);

	hda_initialize(); 
	e1000_initialize();   //<< receiver not working
	//svga_init (); 
	
	printf ("CR3 -> %x\n", x64_read_cr3());
	printf ("Total Used RAM -> %d MB / Total RAM -> %d MB\n", pmmngr_get_used_ram() / 1024 / 1024, pmmngr_get_total_ram() / 1024 / 1024);


	uint64_t *new_cr3 = (uint64_t*)create_user_address_space();
	x64_write_cr3((size_t)new_cr3);

	printf ("Hello New CR3 switched\n");


	/**
	 * The Kernel's Virtual Memory is re-written
	 * so the scheduler is not ready yet, it needs
	 * to be updated!! and many more new designs are 
	 * coming soon...
	 */
	for(;;);

	//! DON'T REACH HERE!!!!
#ifdef ARCH_X64
	//================================================
	//! Initialize the scheduler here
	//!===============================================
	initialize_scheduler();
	uint64_t st = 0xFFFFA00000800000;
	map_page ((uint64_t)pmmngr_alloc(),st,0);
	create_kthread(test_thread2,st + 0x1000,(size_t)x64_read_cr3, "Hello", 1);
	//create_process ("/xshell.exe","shell");
	//create_process ("/xshell.exe","shell");
	//create_user_thread (add,(uint64_t)stack,(uint64_t)cr3,"Test",1);

	//! Quince -- The Compositing window manager for Aurora kernel
	//! always put quince in thread id -- > 2
	//create_process ("/quince.exe","quince",0, NULL);

	/**=====================================================
	 ** Kernel threads handle some specific callbacks like
	 ** procmngr handles process creation and termination
	 **=====================================================
	 */
	//create_kthread (procmngr_start,(uint64_t)pmmngr_alloc(),x64_read_cr3(),"procmngr",0);
	//! Misc programs goes here
	//create_process ("/dwm2.exe", "dwm4", 0, NULL);
	//! Here start the scheduler (multitasking engine)
	scheduler_start();
#endif

	//! Loop forever
	while(1) {
		//!looping looping
		x64_cli();
		x64_hlt();
	}
}