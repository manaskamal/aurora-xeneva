/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2021, Manas Kamal Choudhury
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * /PROJECT - Aurora's Xeneva v1.0
 * @fat --FAT file system
 *
 **/

#ifndef __FAT_H__
#define __FAT_H__

#include <stdint.h>
#include <fs/vfs.h>

//! Attributes for directory entry
#define ATTRIBUTE_MASK        0x3F
#define ATTRIBUTE_READ_ONLY   0x01
#define ATTRIBUTE_HIDDEN      0x02
#define ATTRIBUTE_SYSTEM      0x04
#define ATTRIBUTE_VOLUME      0x08
#define ATTRIBUTE_DIRECTORY   0x10
#define ATTRIBUTE_ARCHIVE     0x20
#define ATTRIBUTE_LONG_NAME   0x0F
 
#define FAT_EOC_MARK     0xFFFFFFF8
#define FAT_BAD_CLUSTER  0xFFFFFFF7

/** FAT32 BPB */
#pragma pack (push,1)
typedef struct _fat32_ {
	uint8_t jmp[3];
	char    oemid[8];
	uint16_t bytes_per_sector;
	uint8_t  sectors_per_cluster;
	uint16_t reserved_sectors;
	uint8_t  num_fats;
	uint16_t num_dir_entries;
	uint16_t total_sectors_short;
	uint8_t  media_type;
	uint16_t sectors_per_fat;
	uint16_t sectors_per_track;
	uint16_t heads;
	uint32_t hidden_sectors;
	uint32_t large_sector_count;
	union {
		struct {
			uint8_t  drive_num;
			uint8_t  WinNtFlags;
			uint8_t  signature;
			uint32_t vol_serial_num;
			char     vol_label[11];
			char     sys_id[8];
		}FAT16;

		struct {
			uint32_t sect_per_fat32;
			uint16_t falgs;
			uint16_t fat_version;
			uint32_t root_dir_cluster;
			uint16_t fs_info_sect;
			uint16_t backup_boot_sect;
			uint8_t  reserved[12];
			uint8_t  drive_number;
			uint8_t  flagsWinNT;
			uint8_t  signature;
			uint32_t vol_serial_num;
			char     vol_label[11];
			char     sys_id[8];
		}FAT32;
	}info;

}BPB;

#pragma pack (pop)

/** _fat32_dir_ -- 32 byte fat directory structure */
#pragma pack (push, 1)
typedef struct _fat32_dir_ 
{
    uint8_t  filename[11];
	uint8_t  attrib;
	uint8_t  reserved;
	uint8_t  time_created_ms;
	uint16_t time_created;
	uint16_t date_created;
	uint16_t date_last_accessed;
	uint16_t first_cluster_hi_bytes;
	uint16_t last_wrt_time;
	uint16_t last_wrt_date;
	uint16_t first_cluster;
	uint32_t file_size;
}fat32_dir;
#pragma pack(pop)


/**
 * initialize_fat32 -- initialize the fat file system
 */
extern void initialize_fat32 ();

/** fat32_open -- Opens a file 
 * @param node -- pointer to the file struct
 * @param filename -- name of the file
 * @example -- \\EFI\\BOOT\\BOOTx64.efi
 */
extern vfs_node_t fat32_open (vfs_node_t *node,char* filename);

/**
 * fat32_read_file -- reads entire file to a buffer (unused)
 * @param file -- file structure
 * @param buffer -- buffer to store to
 * @param count -- size of the file
 */
extern void fat32_read_file (vfs_node_t *file, uint64_t* buf, uint32_t count);

/**
 * fat32_read -- read just 4kb portion of a file
 * @param file -- file structure pointer
 * @param buf -- pointer to buffer to store the content
 */
extern void fat32_read (vfs_node_t *file, uint64_t* buf);

/**
 * fat32_locate_dir -- locates a file in current directory
 * @param dir -- actually filename to search
 */
extern vfs_node_t fat32_locate_dir (const char* dir);

/**
 * fat32_self_register -- registers the file system as vfs object
 */
extern void fat32_self_register ();

/**
 * fat32_find_free_cluster -- finds a free cluster within the FAT32 table
 */
extern uint32_t fat32_find_free_cluster ();

/**
 * fat32_alloc_cluster -- allocates a new cluster with a value
 * @param position -- cluster position within the fat table
 * @param n_value -- cluster value to allocate
 */
extern void fat32_alloc_cluster (int position, uint32_t n_value);

/**
 * fat32_get_root_sector -- returns the root sector
 */
extern uint64_t fat32_get_root_sector ();

/**
 * fat32_get_root_cluster -- returns the root cluster
 */
extern uint32_t fat32_get_root_cluster ();

/**
 * fat32_get_sector_per_cluster -- return sectors/ cluster value
 */
extern uint64_t fat32_get_sector_per_cluster ();

#endif