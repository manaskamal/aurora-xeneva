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
#include <sound.h>

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



void test_thread2 () {
	printf ("Multitasking started\n");
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
	info->printf_gui ("We are inside Aurora Kernel\n");
	//! Initialize the memory mappings
	pmmngr_init (info);
	info->printf_gui ("Initialized Physical Memory Manager\n");
	vmmngr_x86_64_init(); 
	info->printf_gui ("Virtual Memory Initialized\n");
	hal_init();
	info->printf_gui ("Hal Initialized\n");
	hal_x86_64_setup_int();	
	info->printf_gui ("Interrupt APIC initialized\n");
    mm_init(info); 
	info->printf_gui ("MM initialized\n");
	initialize_serial();

	ata_initialize();
	vfs_init();
	initialize_screen(info);
	console_initialize(info);
	
	screen_set_configuration(info->X_Resolution,info->Y_Resolution);
	initialize_rtc(); 

	initialize_acpi (info->acpi_table_pointer);
	
	//!Initialize kernel runtime drivers	
	kybrd_init();
	initialize_mouse();
	
	for (int i = 0; i < 2*1024*1024/4096; i++)
		map_page((uint64_t)pmmngr_alloc(),0xFFFFF00000000000 + i * 4096, 0);

	vfs_node_t *node = vfs_finddir("/");
	vfs_node_t file = openfs (node, "/start.wav");
	unsigned char* buffer = (unsigned char*)0xFFFFF00000000000;
	unsigned char* buffer2 = (unsigned char*)(buffer + 44);
	readfs (node,&file,buffer2,file.size);

	message_init ();
	dwm_ipc_init();
	stream_init ();
	driver_mngr_initialize(info);
	hda_initialize(); 
    hda_audio_add_pcm(buffer2, file.size);

	e1000_initialize();   //<< receiver not working
	
	//svga_init();
	sound_initialize();

#ifdef ARCH_X64
	//================================================
	//! Initialize the scheduler here
	//!===============================================
	initialize_scheduler();

	create_process ("/xshell.exe","shell");
	//! Quince -- The Compositing window manager for Aurora kernel
	//! always put quince in thread id -- > 2
	create_process ("/quince.exe","quince");

	/**=====================================================
	 ** Kernel threads handle some specific callbacks like
	 ** procmngr handles process creation and termination
	 **=====================================================
	 */
	//! Misc programs goes here
	//create_process ("/dwm2.exe", "dwm4");
	create_process ("/cnsl.exe", "cnsl");
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