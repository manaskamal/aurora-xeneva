/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  arp -- Address Resolution Protocol
 *
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * =============================================
 */

#include <net\arp.h>
#include <net\ethernet.h>
#include <net\nethw.h>
#include <string.h>
#include <mm.h>
#include <stdio.h>

arp_table_entry_t *arp_table;
int arp_table_size;
int arp_table_curr;

uint8_t broadcast_mac_address[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

void arp_send_packet (uint8_t *dst_hardware_addr, uint8_t* dst_protocol_addr) {
	arp_packet_t *arp_packet = (arp_packet_t*)malloc(sizeof(arp_packet_t));

	nethw_get_mac (arp_packet->src_hw_addr);
	arp_packet->src_protocol_addr[0] = 10;
	arp_packet->src_protocol_addr[1] = 0;
	arp_packet->src_protocol_addr[2] = 2;
	arp_packet->src_protocol_addr[3] = 14;

	memcpy (arp_packet->dst_hw_addr, dst_hardware_addr, 6);
	memcpy (arp_packet->dst_protocol_addr, dst_protocol_addr, 4);

	arp_packet->opcode = htons(ARP_REQUEST);

	arp_packet->hw_addr_len = 6;
	arp_packet->protocol_addr_len = 4;

	arp_packet->hw_type = htons(HARDWARE_TYPE_ETHERNET);

	//! Set protocol ipv4
	arp_packet->protocol = htons(ETHERNET_TYPE_IP);

	ethernet_send_packet (broadcast_mac_address, (uint8_t*)arp_packet, sizeof(arp_packet_t), ETHERNET_TYPE_ARP);
}

void arp_lookup_add (uint8_t *ret_hardware_addr, uint8_t* ip_addr) {
	memcpy (&arp_table[arp_table_curr].ip_addr, ip_addr, 4);
	memcpy (&arp_table[arp_table_curr].mac_addr, ret_hardware_addr, 6);
	if (arp_table_size < 512)
		arp_table_size++;
	if (arp_table_curr >= 512)
		arp_table_curr = 0;
}

void arp_initialize () {
	arp_table = (arp_table_entry_t*)malloc(512);
	uint8_t broadcast_ip[4];
	uint8_t broadcast_mac[6];

	memset(broadcast_ip, 0xff, 4);
	memset(broadcast_mac, 0xff, 6);
	arp_lookup_add (broadcast_mac, broadcast_ip);
	printf ("Address Resolution Protocol Initialized\n");
}


void arp_broadcast() {
	arp_packet_t *pack = (arp_packet_t*)malloc(sizeof(arp_packet_t));
	pack->hw_type = 0x0100;
	pack->protocol = 0x0008; //ipv4
	pack->hw_addr_len = 6;
	pack->protocol_addr_len = 4;
	pack->opcode = 0x0200; //"response"
	

	nethw_get_mac(pack->src_hw_addr);
	pack->src_protocol_addr[0] = 10;
	pack->src_protocol_addr[1] = 0;
	pack->src_protocol_addr[2] = 2;
	pack->src_protocol_addr[3] = 14;

	pack->dst_hw_addr[0] = 0xFF;
	pack->dst_hw_addr[1] = 0xFF;
	pack->dst_hw_addr[2] = 0xFF;
	pack->dst_hw_addr[3] = 0xFF;
	pack->dst_hw_addr[4] = 0xFF;
	pack->dst_hw_addr[5] = 0xFF;
	
	memset(pack->dst_protocol_addr, 0xff, 4); 

	ethernet_send_packet (pack->dst_hw_addr, (uint8_t*)pack, sizeof(arp_packet_t),ETHERNET_TYPE_ARP);
}