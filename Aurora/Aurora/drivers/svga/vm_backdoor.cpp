/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  vm_backdoor.cpp -- VMware Backdoor
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *================================================
 */

#include <drivers\svga\backdoor_def.h>
#include <drivers\svga\vmsvga.h>
#include <drivers\svga\vmmouse_defs.h>
#include <drivers\vmmouse.h>
#include <stdio.h>

#ifdef HW_SVGA

extern "C" uint32_t vm_backdoor_in (uint32_t rcx, uint32_t rdx);
extern "C" uint32_t vm_backdoor_get_ecx(void);
extern "C" uint32_t vm_backdoor_get_edx();
extern "C" uint32_t vm_backdoor_get_ebx();
static bool vmware_aware = false;

void vm_backdoor_mouse_init (bool absolute) {
	uint32_t eax;
	eax = vm_backdoor_in (0,BDOOR_CMD_GETVERSION);
	uint32_t ecx = vm_backdoor_get_ecx();
	if (ecx <= 0x4) {
		vmware_aware = true;
	} 

	if (vmware_aware){
	eax = vm_backdoor_in (VMMOUSE_CMD_READ_ID,BDOOR_CMD_ABSPOINTER_COMMAND);
	eax = vm_backdoor_in (0, BDOOR_CMD_ABSPOINTER_STATUS);
	eax = vm_backdoor_in(1, BDOOR_CMD_ABSPOINTER_DATA);
	eax = vm_backdoor_in (absolute ? VMMOUSE_CMD_REQUEST_ABSOLUTE : VMMOUSE_CMD_REQUEST_RELATIVE,
		BDOOR_CMD_ABSPOINTER_COMMAND);
	}
}


bool vmbackdoor_mouse_get_packet (vm_mouse_packet  *packet) {
	uint32_t eax;
	eax = vm_backdoor_in (0,BDOOR_CMD_GETVERSION);
	uint32_t ecx = vm_backdoor_get_ecx();
	if (ecx <= 0x4) {

	const uint32_t words_to_read = 4;
   
	eax = vm_backdoor_in (0,BDOOR_CMD_ABSPOINTER_STATUS);

	if ((eax & 0x0000ffff) < words_to_read) {
		//printf ("No Mouse packet available\n");
		return false;
	}

	eax = vm_backdoor_in (words_to_read, BDOOR_CMD_ABSPOINTER_DATA);

	packet->x = vm_backdoor_get_ebx();
	packet->y = vm_backdoor_get_ecx();
	packet->z = vm_backdoor_get_edx();
	packet->flags = eax >> 16;
	packet->buttons = eax & 0xFFFF;

	return true;
	}
	else
		return false;
}


bool vmbackdoor_mouse_aware () {
	return vmware_aware;
}

#endif
