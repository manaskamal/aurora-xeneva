/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  amd_am79c973.h -- AMD PCNet FAST III card driver
 *
 *  /PROJECT - Aurora Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ========================================================
 */

#ifndef __AMD_AM79C973_H__
#define __AMD_AM79C973_H__

#include <stdint.h>
#include <drivers\pci.h>
#include <hal.h>

#define APROM0   0x00
#define APROM2    0x02
#define APROM4    0x04
#define RDP       0x10
#define RAP       0x12
#define RESET     0x14
#define BDP       0x16

#pragma pack (push)
typedef struct _init_block_ {
	uint16_t mode;
	unsigned reserved1 : 4;
	unsigned receive_length : 4;
	unsigned reserved2 : 4;
	unsigned transfer_length : 4;
	uint8_t physical_address[6];
	uint16_t reserved3;
	uint64_t logical_address;
	uint32_t receive_descriptor;
	uint32_t transmit_descriptor;
}amd_init_block;
#pragma pack(pop)

#pragma pack(push)
typedef struct _desc_ {
	uint32_t address;
	uint32_t flags;
	uint32_t flags2;
	uint32_t avail;
}amd_descriptor;
#pragma pack(pop)

typedef struct _amd_net_ {
	amd_descriptor *trans_desc;
	amd_descriptor *recv_desc;
}amd_net;


extern void amd_pcnet_initialize ();
#endif