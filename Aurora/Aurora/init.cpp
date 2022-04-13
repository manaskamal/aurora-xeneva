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
#include <drivers\ahci_disk.h>
#include <drivers\vga.h>
#include <drivers\usb\xhci.h>
#include <drivers\net\e1000.h>
#include <drivers\net\amd_am79c973.h>
#include <drivers\rtc.h>
#include <drivers\acpi\acpi.h>
#include <drivers\vbox.h>
#include <drivers\ahci.h>
#include <ipc\evntsh.h>
#include <ipc\message.h>
#include <ipc\dwm_ipc.h>
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
#include <ipc\pri_loop.h>

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

#include "efi.h"
#include <fs\fat\fat_dir.h>
#include <fs\fat\fat.h>
#include <fs\fat\fat_f.h>

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
	free(p);
}

void (*debug) (const char* text, ...);

void debug_print (const char* text, ...) {
	debug(text);
}

void message() {
	printf ("Hello Message\n");
}

typedef int (*return_int)();

/**========================================
 ** the main entry routine -- _kmain
 **/
void _kmain (KERNEL_BOOT_INFO *info) {
	debug = info->printf_gui;
	//! Initialize the memory mappings
	pmmngr_init (info);
	vmmngr_x86_64_init(); 
	heap_initialize();
	hal_init();
	hal_x86_64_setup_int();	
	initialize_serial();

	initialize_acpi (info->acpi_table_pointer);

	/*IterateImportTable(info->driver_entry1, info->driver_entry3);
	void* address = GetProcAddress(info->driver_entry1, "return_int");
	return_int i = (return_int)address;
	i();
	for(;;);*/
	ahci_initialize();
	//hda_initialize();

	vfs_init();

    initialize_screen(info);
	screen_set_configuration(info->X_Resolution,info->Y_Resolution);
	console_initialize(info);
	
	initialize_rtc(); 

	initialize_mouse();
	kybrd_init();
	message_init ();
	dwm_ipc_init();
	pri_loop_init();
	
	e1000_initialize();   //<< receiver not working
	//svga_init();
	//sound_initialize();
	//driver_mngr_initialize(info);
	process_list_initialize();
	ttype_init();

#ifdef ARCH_X64
	//================================================
	//! Initialize the scheduler here
	//!===============================================
	initialize_scheduler();

	printf ("Scheduler Initialized\n");

	x64_cli();
	/* start the sound service manager at id 1 */
	create_process ("/sndsrv.exe","shell");

	/* start the compositing window manager at id 2 */
	//create_process ("/priwm.exe","priwm");

	//create_process ("/dock.exe", "dock");
	x64_sti();
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