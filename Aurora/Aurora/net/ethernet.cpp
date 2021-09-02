/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  ethernet.cpp -- Ethernet Protocol
 *
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * =================================================
 */

#include <net\ethernet.h>
#include <net\nethw.h>
#include <string.h>
#include <drivers\net\e1000.h>
#include <stdio.h>

//! Send a packet
int ethernet_send_packet (uint8_t* dst_mac_addr, uint8_t *data, int len, uint16_t protocol) {

	uint8_t src_mac_addr[6];
	ethernet_frame_t *frame = (ethernet_frame_t*)malloc (sizeof(ethernet_frame_t) + len);
	void *frame_data = (void*)(frame + sizeof(ethernet_frame_t));

	//! get the src mac address
	nethw_get_mac (src_mac_addr);

	//! fill in source and destination mac address
	memcpy (frame->src_mac_addr, src_mac_addr, 6);
	memcpy (frame->dst_mac_addr, dst_mac_addr, 6);

	//!fill in data
	memcpy (frame_data,data, len);

	//!fill in type
	frame->type = htons(protocol);

	//!Send packet
	e1000_send_packet (frame, sizeof(ethernet_frame_t) + len);
	mfree (frame);
	return len;
}

//! Handle a packet
void ethernet_handle_packet (ethernet_frame_t * packet, int len) {
	void* data = (void*)(packet + sizeof(ethernet_frame_t));
	int data_len = len - sizeof(ethernet_frame_t);
	if(ntohs(packet->type) == ETHERNET_TYPE_ARP) {
		printf ("Ethernet Protocol Received ->> ARP type\n");
		//arp_handle_packet
	}

	//!IP packets (TCP, UDP, or others)
	if (ntohs(packet->type) == ETHERNET_TYPE_IP) {
		printf ("Ethernet Protocol Received packet ->> IP Packet\n");
	}
}
