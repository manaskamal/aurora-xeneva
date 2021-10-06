///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   gpt.h -- Partitioning Table for UEFI systems
///!
///!   //PROJECT - Aurora's Xeneva
///!   //AUTHOR  - Manas Kamal Choudhury
///!
///!=====================================================

#ifndef __GPT_H__
#define __GPT_H__

#include <string.h>
#include <stdint.h>

#pragma pack(push, 1)
typedef struct _gpt_header_ {
	char signature[8];
	uint32_t revision;
	uint32_t header_size;
	uint32_t crc32;
	uint32_t reserved;
	uint64_t current_lba;
	uint64_t backup_lba;
	uint64_t first_usable_lba;
	uint64_t last_usable_lba;
	uint64_t disk_guid[2];
	uint64_t partition_table_lba;
	uint32_t num_partition_entries;
	uint32_t size_of_partition;
	uint32_t crc32_of_partition_entries;
}gpt_header_t;


//! Partition structure
typedef struct _gpt_partition_ {
	uint32_t partition_guid[4];
	uint32_t partition_unique_guid[4];
	uint32_t first_lba[2];
	uint32_t last_lba[2];
	uint64_t attributes;
	char     partition_name[72];
}gpt_partition_t;
#pragma pack (pop)

extern void initialize_gpt ();
#endif