///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   gpt.h -- Partitioning Table for UEFI systems
///!
///!   //PROJECT - Aurora's Xeneva
///!   //AUTHOR  - Manas Kamal Choudhury
///!
///!=====================================================


#include <fs\gpt.h>
#include <stdio.h>
#include <string.h>
#include <pmmngr.h>
#include <drivers\ata.h>

//! EFI System partition
#define EFI_SYSTEM_GUID   0xC12A7328F81F11D2BA4B00A0C93EC93B

void initialize_gpt () {
	printf ("[GPT]: Initializing gpt partition tables....\n");
	uint8_t buffer[512];
	memset(buffer,0,512);

	ata_read_28 (1,1,buffer);

	gpt_header_t *gpt_h = (gpt_header_t*)buffer;

	printf ("[GPT]: Signature %s\n", gpt_h->signature);
	printf ("[GPT]: Revision %x\n", gpt_h->reserved);
	printf ("[GPT]: Total partition entries %d\n", gpt_h->num_partition_entries);
	printf ("[GPT]: Partition table lba -> %d\n", gpt_h->partition_table_lba);
	printf ("[GPT]: SizeOf(GPTPartitionTable) -> %d\n", sizeof(gpt_partition_t));
	uint8_t buf[512];
	//memset (buf, 0, 4096);
	auto raw_byte_index = gpt_h->partition_table_lba;

	for (int i = 0; i < 128; i++) {
		ata_read_28(raw_byte_index, 1, buf);
		gpt_partition_t *part = (gpt_partition_t*)buf;
		raw_byte_index++;
	}

	pmmngr_free(buf);
}