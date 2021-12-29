/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2021, Manas Kamal Choudhury
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * /PROJECT - Aurora's Xeneva v1.0
 * @init.cpp -- Main kernel entry 
 *
 **/

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


/**
 * Runtime setup
 */
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


void *ap_address = 0;

void* get_ap_address () {
	return ap_address;
}
/**========================================
 ** the main entry routine -- _kmain
 **/
void _kmain () {
	KERNEL_BOOT_INFO *info = (KERNEL_BOOT_INFO*)0xFFFFE00000000000;
	//! Initialize the memory mappings
	pmmngr_init (info);
	vmmngr_x86_64_init(); 
	hal_init();
	hal_x86_64_setup_int();	
    mm_init(info); 
	
	initialize_serial();

	ata_initialize();
	vfs_init();
	initialize_screen(info);
	console_initialize(info);
	
	screen_set_configuration(info->X_Resolution,info->Y_Resolution);
	initialize_rtc(); 

	vfs_node_t *node = vfs_finddir("/");
	unsigned char* ap = (unsigned char*)pmmngr_alloc();
	vfs_node_t apfile = openfs(node, "/apstart.bin");
	readfs (node,&apfile,ap,70);
	ap_address = ap;
	printf ("AP_Adress setup -> %x\n", ap_address);
	

	initialize_acpi (info->acpi_table_pointer);
	hal_x86_64_feature_check();

	//!Initialize kernel runtime drivers	
	kybrd_init();
	initialize_mouse();


	
	for (int i = 0; i < 2*1024*1024/4096; i++)
		map_page((uint64_t)pmmngr_alloc(),0xFFFFF00000000000 + i * 4096, 0);

	
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