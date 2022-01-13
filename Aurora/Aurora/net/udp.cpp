/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  udp.cpp -- User Datagram Protocol 
 *
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ===============================================
 */

#include <net\udp.h>
#include <arch\x86_64\mmngr\kheap.h>
#include <net\ethernet.h>
#include <net\nethw.h>
#include <string.h>
#include <stdio.h>

void udp_send_packet (uint8_t* dst_ip, uint16_t src_port, uint16_t dst_port, void* data, int len) {
	int length = sizeof(udp_packet_t) + len;
	udp_packet_t *packet = (udp_packet_t*)malloc(length);
	memset(packet, 0, sizeof(udp_packet_t));
	packet->src_port = htons (src_port);
	packet->dst_port = htons (dst_port);
	packet->length = htons (length);
	packet->checksum = 0;

	memcpy ((void*)(packet + sizeof(udp_packet_t)), data, len);
	printf ("UDP Packet sent\n");
	//not completed
}