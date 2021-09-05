/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  nethw - Hardware Layer for Networking Stack
 *
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ===================================================
 */

#include <net\nethw.h>
#include <mm.h>
#include <string.h>
#include <stdio.h>

net_hw_t *hw;


//! Set the MAC address
void nethw_set_mac (uint8_t* mac) {
	memcpy (hw->mac, mac, 6);
	printf ("MAC:");
	for (int i = 0; i < 6; i++)
		printf (":%x", mac[i]);
	printf ("\n");
}

//! Returns the MAC address
void nethw_get_mac (uint8_t* dst_mac) {
	memcpy (dst_mac, hw->mac, 6);
}

//! Initialize the Network manager
void nethw_initialize () {
	hw = (net_hw_t*)malloc (sizeof(net_hw_t));
}

/* ==============================================
 * Netowrk Utilities
 * ==============================================
 */
uint16_t flip_short (uint16_t short_int) {
	uint32_t first_byte = *((uint8_t*)(&short_int));
	uint32_t second_byte = *((uint8_t*)(&short_int) + 1);
	return (first_byte << 8) | (second_byte);
}

uint32_t flip_long (uint32_t long_int) {
	uint32_t first_byte = *((uint8_t*)(&long_int));
	uint32_t second_byte = *((uint8_t*)(&long_int) + 1);
	uint32_t third_byte = *((uint8_t*)(&long_int) + 2);
	uint32_t fourth_byte = *((uint8_t*)(&long_int) + 3);
	return (first_byte << 24) | (second_byte << 16) | (third_byte << 8) | (fourth_byte);
}

uint8_t flip_byte (uint8_t byte, int num_bits) {
	uint8_t t = byte << (8 - num_bits);
	return t | (byte >> num_bits);
}

uint8_t htonb (uint8_t byte, int num_bits) {
	return flip_byte (byte, num_bits);
}

uint8_t ntohb (uint8_t byte, int num_bits) {
	return flip_byte (byte, 8 - num_bits);
}


uint16_t htons (uint16_t hostshort) {
	return flip_short (hostshort);
}

uint32_t htonl (uint32_t hostlong) {
	return flip_long (hostlong);
}

uint16_t ntohs (uint16_t netshort) {
	return flip_short (netshort);
}

uint32_t ntohl (uint32_t netlong) {
	return flip_long (netlong);
}