/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  ethernet.h -- Ethernet Protocol 
 *
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ================================================
 */

#ifndef __ETHERNET_H__
#define __ETHERNET_H__

#include <stdint.h>
#include <arch\x86_64\mmngr\kheap.h>

#define ETHERNET_TYPE_ARP  0x0806
#define ETHERNET_TYPE_IP   0x0800

#define HARDWARE_TYPE_ETHERNET  0x01

#pragma pack (push,1)

typedef struct _ethernet_frame_ {
	uint8_t dst_mac_addr[6];
	uint8_t src_mac_addr[6];
	uint16_t type;
	uint8_t data[];
} ethernet_frame_t;

#pragma pack(pop)

extern int ethernet_send_packet (uint8_t *dst_mac_addr, uint8_t* data, int len, uint16_t protocol);
extern void ethernet_handle_packet (ethernet_frame_t* packet, int len);

#endif