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
#include <drivers\net\rtl8139.h>
#include <drivers\rtc.h>
#include <drivers\acpi\acpi.h>
#include <drivers\vbox.h>
#include <ipc\evntsh.h>
#include <ipc\message.h>
#include <ipc\dwm_ipc.h>
#include <vfs.h>
#include <fs\fat32.h>
#include <fs\gpt.h>
#include <screen.h>
#include <proc.h>
#include <pmmngr.h>
#include <drvmngr.h>
#include <procmngr.h>
#include <serial.h>
#include <gui\splash.h>

#include <net\arp.h>
#include <net\ethernet.h>
#include <net\nethw.h>

#ifdef ARCH_X64
#include <arch\x86_64\thread.h>
#include <arch\x86_64\mmngr\map.h>
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


void timer_callback (size_t v, void* p) {
	printf ("Timer fired\n");
	interrupt_end(2);
}

struct test_bit {
	unsigned char value_a;
	unsigned char value_b;
};
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

void dummy_thread_2 () {
	while(1) {
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
void _kmain (KERNEL_BOOT_INFO *info) {
	hal_init ();
	pmmngr_init (info);
	mm_init(); 
	initialize_serial();
	console_initialize(info);
	//!Initialize kernel runtime drivers	
	kybrd_init();
	initialize_acpi (info->acpi_table_pointer);
	initialize_rtc();  
	hda_initialize();
	e1000_initialize();  //<< receiver not working


    ata_initialize();
	initialize_gpt();
	initialize_vfs();
	initialize_screen(info);
	svga_init (); 
	initialize_mouse();

	message_init ();
	dwm_ipc_init();

	driver_mngr_initialize(info);
#ifdef ARCH_X64

	//================================================
	//! Initialize the scheduler here
	//!===============================================
	initialize_scheduler();
	create_process ("a:xshell.exe","shell",0, NULL);

	//! Quince -- The Compositing window manager for Aurora kernel
	//! always put quince in thread id -- > 2
	create_process ("a:quince.exe","quince",0, NULL);

	/**=====================================================
	 ** Kernel threads handle some specific callbacks like
	 ** procmngr handles process creation and termination
	 **=====================================================
	 */
	create_kthread (procmngr_start,(uint64_t)pmmngr_alloc(),x64_read_cr3(),"procmngr",0);

	//! Misc programs goes here
	create_process ("a:dwm2.exe", "dwm3", 0, NULL);
//	create_process ("a:dwm2.exe", "dwm4", 0, NULL);

	//! Here start the scheduler (multitasking engine)
	scheduler_start();
#endif

	//! Loop forever
	while(1) {
		//!looping looping
	}
}