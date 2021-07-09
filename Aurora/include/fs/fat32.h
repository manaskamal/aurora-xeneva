/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  fat32.h -- File Allocation Table 28 bit 
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * =============================================
 */

#ifndef __FAT32_H__
#define __FAT32_H__

#include <stdint.h>
#include <vfs.h>

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

#pragma pack (push, 1)

typedef struct _fat32_dir_ 
{
    uint8_t  filename[8];
	uint8_t  ext[3];
	uint8_t  attrib;
	uint8_t  reserved;
	uint8_t  time_created_ms;
	uint16_t time_created;
	uint16_t date_created;
	uint16_t date_last_accessed;
	uint16_t first_cluster_hi_bytes;
	uint16_t last_mod_time;
	uint16_t last_mod_date;
	uint16_t first_cluster;
	uint32_t file_size;
}fat32_dir;

#pragma pack(pop)

extern void initialize_fat32 ();
extern FILE fat32_open (const char* filename);
extern void fat32_read_file (FILE *file, unsigned char* buf, int count);
extern void fat32_read (FILE *file, unsigned char* buf);
extern FILE fat32_locate_dir (const char* dir);
#endif