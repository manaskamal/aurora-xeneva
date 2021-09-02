/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  nethw.h -- Hardware Layer for networking stack
 *
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury 
 *
 * ====================================================
 */

#ifndef __NETHW_H__
#define __NETHW_H__

#include <stdint.h>

//! Net Hardware Structure
typedef struct _net_hw_ {
	uint8_t mac[6];
}net_hw_t;


//! Net Hardware set mac address code
extern void nethw_set_mac (uint8_t* mac);

//! Copies the mac address code from NIC to protocol
extern void nethw_get_mac (uint8_t* mac);

//! Initialize the nethw layer
extern void nethw_initialize ();

//! network utils
extern uint16_t flip_short (uint16_t short_int);
extern uint32_t flip_long (uint32_t long_int);
extern uint8_t flip_byte (uint8_t byte, int num_bits);
extern uint8_t htonb (uint8_t byte, int num_bits);
extern uint8_t ntohb (uint8_t byte, int num_bits);
extern uint16_t htons (uint16_t hostshort);
extern uint32_t htonl (uint32_t hostlong);
extern uint16_t ntohs (uint16_t netshort);
extern uint32_t ntohl (uint32_t netlong);

#endif