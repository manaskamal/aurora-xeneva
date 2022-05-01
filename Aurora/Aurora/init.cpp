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
#include <drivers\usb\xhci.h>
#include <drivers\rtc.h>
#include <drivers\acpi\acpi.h>
#include <drivers\ahci.h>
#include <ipc\evntsh.h>
#include <ipc\message.h>
#include <ipc\dwm_ipc.h>
#include <fs\gpt.h>
#include <fs\vfs.h>
#include <screen.h>
#include <proc.h>
#include <pmmngr.h>
#include <audrv.h>
#include <serial.h>
#include <stream.h>
#include <sound.h>
#include <ipc\pri_loop.h>
#include <mmngr\shmem.h>

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


void (*debug) (const char* text, ...);

void debug_print (const char* text, ...) {
	debug(text);
}

extern "C" void x64_stack_test(uint8_t a, uint16_t b, int c, int d, int e, uint8 f);
/**========================================
 ** the main entry routine -- _kmain
 **/
void _AuMain (KERNEL_BOOT_INFO *info) {
	debug = info->printf_gui;
	//! Initialize the memory mappings
	AuPmmngrInit (info);
	AuPagingInit();
	AuHeapInitialize();
	

	AuInitializeShMem();
	AuHalInitialize();

	AuInitializeSerial();
	AuInitializeBasicAcpi (info->acpi_table_pointer);

	ahci_initialize();
	hda_initialize();
	AuVFSInit();
	
	AuInitializeScreen(info);
	AuConsoleInitialize(info);
	AuInitializeRTC(); 

	AuInitializeMouse();

	//Here we initialise all drivers stuffs
	/* Clear interrupts as scheduler will enable it */
	x64_cli();
	//AuDrvMngrInitialize(info);
	AuKeyboardInitialize();
	dwm_ipc_init();
	pri_loop_init();

	process_list_initialize();
	ttype_init();
	
	//================================================
	//! Initialize the scheduler here
	//!===============================================
	AuInitializeScheduler();
	
	/*Initialize other processor */
	AuInitializeCpu(AuGetNumCPU());

	/*Clear the lower half for user space */
	AuPagingClearLow();

#ifdef ARCH_X64
	
	printf ("Scheduler Initialized\n");

	int au_status = 0;

	/* start the sound service manager at id 1 */
	au_status = AuCreateProcess ("/init.exe","shell");

	/* start the compositing window manager at id 2 */
	au_status = AuCreateProcess ("/priwm.exe","priwm");

	//au_status = AuCreateProcess ("/dock.exe", "dock");
	//! Here start the scheduler (multitasking engine)
	AuSchedulerStart();
#endif

	//! Loop forever
	while(1) {
		//!looping looping
		x64_cli();
		x64_hlt();
	}
}