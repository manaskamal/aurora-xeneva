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


#include <fs\fat\fat.h>
#include <fs\fat\fat_util.h>
#include <drivers\ata.h>
#include <pmmngr.h>
#include <ctype.h>
#include <arch\x86_64\mmngr\kheap.h>
#include <console.h>
#include <fs/vfs.h>
#include <drivers\ahci.h>
#include <drivers\ahci_disk.h>
#include <serial.h>
#include <drivers\rtc.h>

/** FAT variables */
unsigned int part_lba;  //partition_begin_lba
unsigned long fat_begin_lba;
unsigned long cluster_begin_lba;
unsigned char sectors_per_cluster = 0;
unsigned int root_dir_first_cluster;
unsigned long root_sector;
unsigned int sectors_per_fat32;
int alloc_counter = 0;
unsigned int total_clusters;
unsigned char* root_dir_cache;



//! converts clusters to LBA 
uint64_t  cluster_to_sector32 (uint64_t cluster){
	return cluster_begin_lba + (cluster - 2) * sectors_per_cluster ;
}


/**
 * initialize_fat32 -- initialize the fat file system
 */
void initialize_fat32 () {

	uint64_t *buf = (uint64_t*)AuPmmngrAlloc();
	//ata_read_28 (2048,1,buf); //partition_begin_lba = 2048
	ahci_disk_read (ahci_disk_get_port(),2048,1,buf);


	BPB *fat32_data = (BPB*)buf;

	part_lba = 2048;

#ifdef _DEBUG_ON_
	_debug_print_ ("FAT32 BOOT PARAMETER BLOCK \r\n");
	_debug_print_ ("Bytes/Sector -> %d \r\n", fat32_data->bytes_per_sector);
	_debug_print_ ("Sectors/Cluster -> %d \r\n", fat32_data->sectors_per_cluster);
	_debug_print_ ("Reserved Sectors -> %d \r\n", fat32_data->reserved_sectors);
	_debug_print_ ("Number Of FATs -> %d \r\n", fat32_data->num_fats);
	_debug_print_ ("Root Base Cluster -> %d \r\n", fat32_data->info.FAT32.root_dir_cluster);
	_debug_print_ ("Sector/FAT32 -> %d \r\n", fat32_data->info.FAT32.sect_per_fat32);


	for (int i=0; i <12; i++) {
		_debug_print_("%c",fat32_data->info.FAT32.vol_label[i]);
	}

	_debug_print_ ("\r\n");

	for (int i=0; i <9; i++) {
		_debug_print_("%c",fat32_data->info.FAT32.sys_id[i]);
	}

	_debug_print_ ("\r\n");
#endif
	fat_begin_lba = part_lba + fat32_data->reserved_sectors;
	cluster_begin_lba = part_lba + fat32_data->reserved_sectors + (fat32_data->num_fats * fat32_data->info.FAT32.sect_per_fat32);
	sectors_per_cluster = fat32_data->sectors_per_cluster;
	root_dir_first_cluster = fat32_data->info.FAT32.root_dir_cluster;
	root_sector = cluster_to_sector32 (root_dir_first_cluster);
	sectors_per_fat32 = fat32_data->info.FAT32.sect_per_fat32;

	total_clusters = fat32_data->large_sector_count / sectors_per_cluster;
	_debug_print_ ("FAT32 Total clusters -> %d \r\n", total_clusters);


}

/**
 * fat32_read_fat -- reads FAT table contents
 * @param cluster_index -- index of the cluster
 */
uint32_t fat32_read_fat (uint32_t cluster_index) {
	auto fat_offset = cluster_index * 4;
	uint64_t fat_sector = fat_begin_lba + (fat_offset / 512);
	size_t ent_offset = fat_offset  % 512;
	uint64_t *buf_area = (uint64_t*)AuPmmngrAlloc();
	memset(buf_area,0,4096);
	//ata_read_28 (fat_sector,1,buf);
	ahci_disk_read (ahci_disk_get_port(),fat_sector,1,buf_area);
	unsigned char *buf = (unsigned char*)buf_area;
	uint32_t value = *(uint32_t*)&buf[ent_offset];
	AuPmmngrFree(buf_area);
	return value & 0x0FFFFFFF;
}


/**
 * fat32_find_free_cluster -- finds a free cluster within the FAT32 table
 * [TODO] : use the fat_bpb:nxt_free to make search faster
 */
uint32_t fat32_find_free_cluster () {
	//!iterate through every sectors in fat32 table
	for (int i = 2; i < total_clusters; i++) {
		auto fat_offset = i * 4;
		uint64_t fat_sector = fat_begin_lba + (fat_offset / 512);
		size_t ent_offset = fat_offset  % 512;
		uint64_t *buffer = (uint64_t*)AuPmmngrAlloc();
		memset(buffer,0,4096);
		ahci_disk_read(ahci_disk_get_port(),fat_sector,1,buffer);
		uint8_t* buf = (uint8_t*)buffer;
		uint32_t value = *(uint32_t*)&buf[ent_offset];

		AuPmmngrFree(buffer);
		//! Found a free cluster return the value
		if (value == 0x00) {
			return i;
		}
	}
	return 0;
}

/**
 * fat32_alloc_cluster -- allocates a new cluster with a value
 * @param position -- cluster position within the fat table
 * @param n_value -- cluster value to allocate
 */
void fat32_alloc_cluster (int position, uint32_t n_value) {
	auto fat_offset = position * 4;
	uint64_t fat_sector = fat_begin_lba + (fat_offset / 512);
	size_t ent_offset = fat_offset  % 512;
	uint64_t *buffer = (uint64_t*)AuPmmngrAlloc();
	memset(buffer,0,4096);
	ahci_disk_read(ahci_disk_get_port(),fat_sector,1,buffer);

	uint8_t* buf = (uint8_t*)buffer;
	uint32_t value = *(uint32_t*)&buf[ent_offset];
	*(uint32_t*)&buf[ent_offset] = n_value & 0x0FFFFFFF;

	uint32_t value2 = *(uint32_t*)&buf[ent_offset];
	ahci_disk_write(ahci_disk_get_port(),fat_sector,1,buffer);
	AuPmmngrFree(buffer);
}

/**
 * fat32_clear_cluster -- clears a cluster to 0
 * @param cluster -- cluster to clear
 */
void fat32_clear_cluster (uint32_t cluster) {
	uint64_t *buffer = (uint64_t*)AuPmmngrAlloc();
	memset (buffer, 0, 4096);
	//update_cluster (buffer,cluster);
	uint32_t sector = cluster_to_sector32 (cluster);
	ahci_disk_write (ahci_disk_get_port(),sector,sectors_per_cluster,buffer);
	AuPmmngrFree(buffer);
}

/**
 * fat32_read -- read just 4kb portion of a file
 * @param file -- file structure pointer
 * @param buf -- pointer to buffer to store the content
 */
void fat32_read (vfs_node_t *file, uint64_t* buf) {

	auto lba = cluster_to_sector32 (file->current); 

	ahci_disk_read(ahci_disk_get_port(), lba, 8,buf);

	uint32_t value = fat32_read_fat (file->current);

	if (value  >= 0x0FFFFFF8) {
	    file->eof = 1;
		return;
	}

	if (value  == 0x0FFFFFF7) {
	    file->eof = 1;
		return;
	}
	
	file->current = value;
}



/**
 * fat32_read_file -- reads entire file to a buffer (unused)
 * @param file -- file structure
 * @param buffer -- buffer to store to
 * @param count -- size of the file
 */
void fat32_read_file (vfs_node_t *file, uint64_t* buffer, uint32_t count) {
	/*while(file->eof != 1) {
		fat32_read (file,buffer);
		buffer += 4096;
	}*/
	for (int i=0; i < count; i+= 8) {
		fat32_read (file, buffer);
		if (file->eof) 
			break;
		buffer += 4096;
	}
}

/**
 * fat32_locate_dir -- locates a file in current directory
 * @param dir -- actually filename to search
 */
vfs_node_t fat32_locate_dir (const char* dir) {
	vfs_node_t file;
	uint64_t* buf;
	fat32_dir *dirent;
	char dos_file_name[11];
	fat32_to_dos_file_name (dir, dos_file_name, 11);	
	buf = (uint64_t*)AuPmmngrAlloc();
	for (unsigned int sector = 0; sector < sectors_per_cluster; sector++) {
	
		memset (buf, 0, 4096);
		//ata_read_28 (root_sector + sector,1, buf);
		ahci_disk_read(ahci_disk_get_port(),root_sector + sector,1,buf);
		dirent = (fat32_dir*)buf;
		for (int i=0; i < 16; i++) {
			
			char name[11];
			memcpy (name, dirent->filename, 11);

			name[11] = 0;
			if (strcmp (dos_file_name, name) == 0) {
				strcpy (file.filename, dir);
				file.current = dirent->first_cluster;
				file.size = dirent->file_size;
				file.eof = 0;
				file.status = FS_STATUS_FOUND;

				if (dirent->attrib == 0x10)
					file.flags = FS_FLAG_DIRECTORY;
				else
					file.flags = FS_FLAG_GENERAL;
				
				AuPmmngrFree(buf);
				return file;
			}
			dirent++;
		}
	}

	file.status = FS_FLAG_INVALID;
	file.size = 0;
	file.eof = 0;
	return file;
}


/**
 * fat32_locate_subdir -- locates a subdirectory for a file
 * @param kfile -- parent vfs file object
 * @param filename -- file name to search
 */
vfs_node_t fat32_locate_subdir (vfs_node_t kfile, const char* filename) {

	vfs_node_t file;

	char dos_file_name[11];
	fat32_to_dos_file_name (filename, dos_file_name, 11);
	//dos_file_name[11] = 0;
	uint64_t* buf = (uint64_t*)AuPmmngrAlloc();
	if (kfile.flags != FS_FLAG_INVALID) {
		
		//! read the directory
		while (!kfile.eof) {

			//! read 
		
			fat32_read (&kfile, buf);
			//! set directory
			fat32_dir* pkDir = (fat32_dir*)buf;

			//! 16 entries
			for (unsigned int i = 0; i < 16; i++) {

				//! get current filename;
				char name[11];
				memcpy (name, pkDir->filename, 11);
				//name[11] = 0;

				if (strcmp (name, dos_file_name) == 0) {

					//! found file
					strcpy (file.filename, filename);
					file.current = pkDir->first_cluster;
					file.size = pkDir->file_size;
					file.eof = 0;
					file.status = FS_STATUS_FOUND;
					//! set file type
					if (pkDir->attrib == 0x10)
						file.flags = FS_FLAG_DIRECTORY;
					else
						file.flags = FS_FLAG_GENERAL;

					AuPmmngrFree(buf);
					//!return file
					return file;
				}

				//! go to next entry
				pkDir++;
			}

			//pmmngr_free (buf);
		}
	}

	AuPmmngrFree(buf);
	file.flags = FS_FLAG_INVALID;
	return file;
}



//! Opens a file 
//! @param filename -- name of the file
//! @example -- \\EFI\\BOOT\\BOOTx64.efi
vfs_node_t fat32_open (vfs_node_t * node, char* filename) {
	vfs_node_t cur_dir;
	char* p = 0;
	bool  root_dir = true;
	char* path = (char*) filename;

	//! any '\'s in path ?
	p = strchr (path, '/');
	if (!p) {
		//! nope, must be in root directory, search it
		cur_dir = fat32_locate_dir (path);

		//! found file ?
		if (cur_dir.flags == FS_FLAG_GENERAL) {
			return cur_dir;
		}

		//! unable to find
		vfs_node_t ret;
		ret.flags = FS_FLAG_INVALID;
		ret.size = 0;
		return ret;
	}

	//! go to next character after first '\'
	p++;

	while (p) {

		//! get pathname
		char pathname[16];
		int i=0;
		for (i=0; i < 16; i++) {

			//! if another '\' or end of line is reached, we are done
			if (p[i] == '/' || p[i]=='\0')
				break;

			//! copy character
			pathname[i]=p[i];
		}
		pathname[i]=0; //null terminate

		//! open subdirectory or file
		if (root_dir) {
			//! search root dir -- open pathname
			cur_dir = fat32_locate_dir (pathname);
			root_dir = false;
		}
		else {
			//! search a sub directory instead for pathname
			cur_dir = fat32_locate_subdir (cur_dir, pathname);
		}

		//! found directory or file?
		if (cur_dir.flags == FS_FLAG_INVALID)
			break;

		//! found file?
		if (cur_dir.flags == FS_FLAG_GENERAL){
			return cur_dir;
		}

		//! find next '\'
		p=strchr(p+1, '/');
		if (p)
			p++;
	}

	//! unable to find
	vfs_node_t ret;
	ret.flags = FS_FLAG_INVALID;
	ret.size = 0;
	return ret;
}


/**
 * fat32_get_root_sector -- returns the root sector
 */
uint64_t fat32_get_root_sector () {
	return root_sector;
}

/**
 * fat32_get_root_cluster -- returns the root cluster
 */
uint32_t fat32_get_root_cluster () {
	return root_dir_first_cluster;
}

/**
 * fat32_get_sector_per_cluster -- return sectors/ cluster value
 */
uint64_t fat32_get_sector_per_cluster () {
	return sectors_per_cluster;
}

/**
 * fat32_format_date -- returns fat32 formated date
 */
uint16_t fat32_format_date () {
	return (uint16_t)(2000 + rtc_get_year()-1980)<<9 | (uint16_t)rtc_get_month() << 5 | (uint16_t)rtc_get_day();
	//return (uint16_t)(2022-1980) <<9 | (uint16_t)3 << 5 | (uint16_t)6;
}

/**
 * fat32_format_time -- returns fat32 formated time
 */
uint16_t fat32_format_time () {
	return (uint16_t)rtc_get_hour() << 11 | (uint16_t)rtc_get_minutes() << 5 | (uint16_t)rtc_get_second()/2;
}

/**
 * fat32_self_register -- registers the file system as vfs object
 */
void fat32_self_register () {
	vfs_node_t *fsys = (vfs_node_t*)malloc(sizeof(vfs_node_t));
	strcpy (fsys->filename, "/");
	fsys->size = 0;
	fsys->eof = 0;
	fsys->pos = 0;
	fsys->current = 0;
	fsys->flags = FS_FLAG_GENERAL;
	fsys->status = 0;
	fsys->open = fat32_open;
	fsys->read = fat32_read_file;
	fsys->write = 0;
	fsys->read_blk = fat32_read;
	fsys->ioquery = 0;
	vfs_mount ("/", fsys, 0);
	printf ("File System registered\n");
}






