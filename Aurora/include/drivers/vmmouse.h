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

#ifndef __VM_MOUSE_H__
#define __VM_MOUSE_H__

#include <drivers\svga\backdoor_def.h>
#include <drivers\svga\vmsvga.h>
#include <drivers\svga\vmmouse_defs.h>
#include <stdint.h>


typedef struct _mouse_packet_ {
	uint32_t flags;
	uint32_t buttons;
	int x, y, z;
}vm_mouse_packet;

extern void vm_backdoor_mouse_init (bool absolute);
extern bool vmbackdoor_mouse_get_packet (vm_mouse_packet  *packet);
extern bool vmbackdoor_mouse_aware ();
#endif
