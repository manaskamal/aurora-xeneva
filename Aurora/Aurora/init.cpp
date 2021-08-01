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

	driver_mngr_initialize(info);
	
#ifdef ARCH_X64
	initialize_scheduler();
	create_process ("dwm.exe","dwm",20);
	//! task list should be more than 4 or less than 4 not 
	create_process ("dwm2.exe", "dwm2", 1);
	create_process ("dwm3.exe", "dwm3", 1);
	scheduler_start();
#endif
	while(1) {
	}
}