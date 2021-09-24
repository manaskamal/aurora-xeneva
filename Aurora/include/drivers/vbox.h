///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   vbox.h -- Virtual Box Driver
///! 
///!   //PROJECT - Aurora's Xeneva
///!   //AUTHOR  - Manas Kamal Choudhury
///!
///!===================================================

#ifndef __VBOX_H__
#define __VBOX_H__

#include <drivers\pci.h>
#include <stdint.h>

#define VBOX_VMMDEV_VERSION 0x00010003
#define VBOX_REQUEST_HEADER_VERSION  0x10001
#define VBOX_REQUEST_GUEST_INFO   50
#define VBOX_REQUEST_GET_MOUSE 1
#define VBOX_REQUEST_SET_MOUSE 2
#define VBOX_REQUEST_ACK_EVENTS 41


typedef struct _vbox_ {
	uint32_t size;
	uint32_t version;
	uint32_t request_type;
	int32_t  rc;
	uint32_t reserved1;
	uint32_t reserved2;
}vbox_header;

typedef struct _vbox_g_caps_ {
	vbox_header header;
	uint32_t caps;
}vbox_guest_caps;

typedef struct _vbox_ack_events_ {
	vbox_header header;
	uint32_t event;
}vbox_ack_events;

typedef struct _vbox_display_change_ {
	vbox_header header;
	uint32_t xres;
	uint32_t yres;
	uint32_t bpp;
	uint32_t eventack;
}vbox_display_change;


typedef struct _vbox_mouse_absolute_ {
	vbox_header header;
	uint32_t features;
	int32_t x;
	int32_t y;
}vbox_mouse_absolute;


typedef struct _vbox_guest_info_ {
	vbox_header header;
	uint32_t version;
	uint32_t ostype;
}vbox_guest_info;


extern void initialize_guest_vbox();


#endif