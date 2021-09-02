/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  udp.h -- User Datagram Protocol
 *
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR - Manas Kamal Choudhury
 *
 * ===========================================
 */

#ifndef __UDP_H__
#define __UDP_H__

#include <stdint.h>

#pragma pack (push,1)
typedef struct _udp_packet_ {
	uint16_t src_port;
	uint16_t dst_port;
	uint16_t length;
	uint16_t checksum;
	uint8_t  data[];
} udp_packet_t;
#pragma pack(pop)

extern void udp_send_packet (uint8_t * dst_ip, uint16_t src_port, uint16_t dst_port, void* data, int len);

#endif