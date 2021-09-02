/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  ARP (Address Resolution Protocol) for aurora-xeneva
 *
 *  /PROJECT - Aurora Xeneva v1.0
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * =====================================================
 */

#ifndef __ARP_H__
#define __ARP_H__

#include <stdint.h>

//! ARP Mode
#define ARP_REQUEST     1
#define ARP_REPLY       2


//! ARP Packet structure
#pragma pack(push,1)
typedef struct _arp_packet_ {
	uint16_t  hw_type;
	uint16_t  protocol;
	uint8_t   hw_addr_len;
	uint8_t   protocol_addr_len;
	uint16_t  opcode;
	uint8_t   src_hw_addr[6];
	uint8_t   src_protocol_addr[4];
	uint8_t   dst_hw_addr[6];
	uint8_t   dst_protocol_addr[4];
}arp_packet_t;
#pragma pack(pop)

//!ARP Table
typedef struct _arp_table_ {
	uint32_t ip_addr;
	uint64_t mac_addr;
}arp_table_entry_t;

extern void arp_initialize ();
extern void arp_send_packet (uint8_t *dst_hardware_addr, uint8_t* dst_protocol_addr);
extern void arp_broadcast();
#endif