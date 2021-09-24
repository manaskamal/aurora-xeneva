///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   vbox.h -- Virtual Box Driver
///! 
///!   //PROJECT - Aurora's Xeneva
///!   //AUTHOR  - Manas Kamal Choudhury
///!
///!===================================================

#include <drivers\vbox.h>
#include <stdio.h>
#include <pmmngr.h>

static int vbox_port;
static uint32_t* vbox_vmmdev;
static uint32_t vbox_mouse_phys;
vbox_mouse_absolute * vbox_mouse;
static uint32_t vbox_ack_phys;
static vbox_ack_events *ack;

void vbox_handler (size_t v, void* p) {
   if (!vbox_vmmdev[2])goto end;

	//printf ("VBox Interrupt fired\n");
	ack->event = vbox_vmmdev[2];
	outportd (vbox_port, vbox_ack_phys);
	outportd (vbox_port, (uint32_t)vbox_mouse_phys);

	unsigned int x = ((unsigned int)vbox_mouse->x * 1024) / 0xFFFF;
	unsigned int y = ((unsigned int)vbox_mouse->y * 720) / 0xFFFF;

end:
	interrupt_end(11);
}
void initialize_guest_vbox () {
	pci_device_info addr;
	if (!pci_find_device_id(0xCAFE, 0x80EE,&addr)) {
		printf ("Virtual Box Guest Driver not found\n");
		return;
	}

	interrupt_set (10, vbox_handler, 10);
	printf ("Initialize Virtual Box Driver\n");
	vbox_port = addr.device.nonBridge.baseAddress[0] & 0xFFFFFFFC;
	
	vbox_vmmdev = (uint32_t*)(addr.device.nonBridge.baseAddress[1] & 0xFFFFFFF0);
	
	uint32_t vbox_guest_phys;
	vbox_guest_info *guest_info = (vbox_guest_info*)pmmngr_alloc();
	guest_info->header.size = sizeof(vbox_guest_info);
	guest_info->header.version = VBOX_REQUEST_HEADER_VERSION;
	guest_info->header.request_type = VBOX_REQUEST_GUEST_INFO;
	guest_info->header.rc = 0;
	guest_info->header.reserved1 = 0;
	guest_info->header.reserved2 = 0;
	guest_info->version = VBOX_VMMDEV_VERSION;
	guest_info->ostype = 0;

	vbox_guest_phys = (uint32_t)guest_info;
	outportd (vbox_port, vbox_guest_phys);

	ack = (vbox_ack_events*)pmmngr_alloc();
	ack->header.size = sizeof(vbox_ack_events);
	ack->header.version = VBOX_REQUEST_HEADER_VERSION;
	ack->header.request_type = VBOX_REQUEST_ACK_EVENTS;
	ack->header.rc = 0;
	ack->header.reserved1 = 0;
	ack->header.reserved2 = 0;
	ack->event = 0;
	vbox_ack_phys = (uint32_t)ack;


	vbox_mouse = (vbox_mouse_absolute*)pmmngr_alloc();
	vbox_mouse->header.size = sizeof(vbox_mouse_absolute);
	vbox_mouse->header.version = VBOX_REQUEST_HEADER_VERSION;
	vbox_mouse->header.request_type = VBOX_REQUEST_SET_MOUSE;
	vbox_mouse->header.rc = 0;
	vbox_mouse->header.reserved1 = 0;
	vbox_mouse->header.reserved2 = 0;
	vbox_mouse->features = (1<<0) | (1<<4);
	vbox_mouse->x = 0;
	vbox_mouse->y = 0;
	vbox_mouse_phys = (uint32_t)vbox_mouse;
	outportd (vbox_port,vbox_mouse_phys);

	vbox_mouse->header.request_type = VBOX_REQUEST_GET_MOUSE;

	printf ("Virtual Box Driver initialized -> %d\n", guest_info->header.rc);
	vbox_vmmdev[3] =  0xFFFFFFFF;
}