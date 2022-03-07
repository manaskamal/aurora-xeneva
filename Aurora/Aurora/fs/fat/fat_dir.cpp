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
 * @fat_dir --FAT file system's directory management
 *
 **/

#include <fs\fat\fat_dir.h>
#include <fs\fat\fat_util.h>
#include <fs\vfs.h>
#include <stdint.h>
#include <serial.h>
#include <fs\fat\fat.h>
#include <pmmngr.h>
#include <arch\x86_64\mmngr\kheap.h>
#include <drivers\ahci_disk.h>
#include <drivers\rtc.h>
#include <stdio.h>

/**
 * extern functions 
 */
extern uint32_t fat32_read_fat (uint32_t cluster_index);
extern uint32_t fat32_find_free_cluster ();
extern void fat32_alloc_cluster (int position, uint32_t n_value);
extern void fat32_clear_cluster (uint32_t cluster);
extern uint64_t  cluster_to_sector32 (uint64_t cluster);
extern uint16_t fat32_format_date ();
extern uint16_t fat32_format_time ();


/**
 * fat32_find_free_dir_entry -- finds free directory entry in root dir
 */
void fat32_find_free_dir_entry (uint32_t cluster) {
	uint64_t* buffer = (uint64_t*)pmmngr_alloc();
	memset(buffer, 0, 4096);

	ahci_disk_read (ahci_disk_get_port(),cluster_to_sector32(cluster),fat32_get_sector_per_cluster(),buffer);
	
	fat32_dir *dir = 0;
	fat32_dir *dirent = (fat32_dir*)buffer;

	printf ("Listing Files\n");
	for (int i = 0; i < 16; i++) {
		if (dirent->attrib != 0)
			printf ("%s         %d KB \n", dirent->filename, dirent->file_size / 1024);
		dirent++;
	}

}



/**
 * fat32_make_dir -- creates a fat32 directory
 * @param parent_clust -- parent directory cluster
 * @param filename -- directory name
 */
vfs_node_t *fat32_make_dir (uint32_t parent_clust, char* filename) {
	vfs_node_t *file = (vfs_node_t*)malloc(sizeof(vfs_node_t));
	memset(file, 0, sizeof(vfs_node_t));


	uint64_t* buff = (uint64_t*)pmmngr_alloc();
	memset(buff, 0, 4096);

	bool is_parent_root = false;

	_debug_print_ ("Creating directory \r\n");

	char fname[11];
	memset(fname,0,11);
	fat32_to_dos_file_name (filename, fname, 11);

	if (parent_clust == fat32_get_root_cluster ())
		is_parent_root = true;

search:
	for (int j = 0; j < fat32_get_sector_per_cluster(); j++) {
		memset(buff,0,4096);
		ahci_disk_read (ahci_disk_get_port(), cluster_to_sector32(parent_clust) + j, 1,buff);

		unsigned char* buffer = (unsigned char*)buff;
		fat32_dir *dirent = (fat32_dir*)buff;
		for (int i = 0; i < 16; i++) {
			if (dirent->filename[0] == 0x00 || dirent->filename[0] == 0xE5) {
				memcpy (dirent->filename, fname,11);

				uint32_t cluster = fat32_find_free_cluster();
				fat32_alloc_cluster (cluster,FAT_EOC_MARK);
				fat32_clear_cluster(cluster);

				dirent->attrib = ATTRIBUTE_DIRECTORY;
				dirent->first_cluster = cluster & 0x0000FFFF;
				dirent->first_cluster_hi_bytes = (cluster & 0x0FFF0000)>>16;
				dirent->date_created = fat32_format_date();
				dirent->time_created = fat32_format_time();
				dirent->last_wrt_date = dirent->date_created;
				dirent->last_wrt_time = dirent->time_created;
				dirent->date_last_accessed = 0;
				dirent->file_size = 0;

				uint64_t* entrybuf = (uint64_t*)pmmngr_alloc();
				memset(entrybuf, 0, 4096);
				uint8_t* entry = (uint8_t*)entrybuf;

				fat32_dir *dot_entry = (fat32_dir*)entrybuf;
				memset(dot_entry, 0, sizeof(fat32_dir));
				dot_entry->filename[0] = '.';
				memset(dot_entry->filename+1,0x20,10);
				dot_entry->attrib = ATTRIBUTE_DIRECTORY;
				dot_entry->date_created = dirent->date_created;
				dot_entry->time_created = dirent->time_created;
				dot_entry->date_last_accessed = dirent->date_last_accessed;
			    dot_entry->file_size = 0;
			    dot_entry->first_cluster = dirent->first_cluster;
			    dot_entry->first_cluster_hi_bytes = dirent->first_cluster_hi_bytes;
			    dot_entry->last_wrt_date = dirent->last_wrt_date;
			    dot_entry->last_wrt_time = dirent->last_wrt_time;
		
			    fat32_dir *dot_dot = (fat32_dir*)(entrybuf + sizeof(fat32_dir));
			    memset(dot_dot, 0, sizeof(fat32_dir));
				dot_dot->filename[0] = '.';
				dot_dot->filename[1] = '.';
			    dot_dot->attrib = ATTRIBUTE_DIRECTORY;
			    dot_dot->date_created = dirent->date_created;
				dot_dot->time_created = dirent->time_created;
			    dot_dot->date_last_accessed = dirent->date_last_accessed;
			    dot_dot->file_size = 0;

				if (is_parent_root) {
					dot_dot->first_cluster = 0 & 0x0000FFFF;
					dot_dot->first_cluster_hi_bytes = (0 & 0x0FFF0000)>>16;
				}else {
					dot_dot->first_cluster = parent_clust & 0x0000FFFF;
					dot_dot->first_cluster_hi_bytes = (0 & 0x0FFF0000)>>16;
				}

			    dot_dot->last_wrt_date = dirent->last_wrt_date;
			    dot_dot->last_wrt_time = dirent->last_wrt_time;

				ahci_disk_write (ahci_disk_get_port(),cluster_to_sector32(cluster),fat32_get_sector_per_cluster(),entrybuf);
			    ahci_disk_write (ahci_disk_get_port(),cluster_to_sector32(parent_clust) + j,1,buff);
			    pmmngr_free(entry);
			    pmmngr_free(buffer);

				strcpy (file->filename,fname);
				file->size = dirent->file_size;
				file->eof = 0;
				file->pos = 0;
				file->current = dirent->first_cluster;
				file->flags = FS_FLAG_DIRECTORY;
				file->status = FS_STATUS_FOUND;

				_debug_print_ ("FAT32: Directory created at entry-> %d \r\n",i);
			    return file;
			}
			dirent++;
		}
	}
	parent_clust = fat32_read_fat(parent_clust);
	if (parent_clust != 0x0FFFFFF7)
		goto search;
	else {
		free(file);
		return NULL;
	}
}


/**
 * fat32_open_dir -- opens a fat32 directory
 * @param parent_clust -- parent directory cluster
 * @param filename -- directory name
 */
vfs_node_t *fat32_open_dir (uint32_t parent_clust, char* filename) {
	vfs_node_t *file = (vfs_node_t*)malloc(sizeof(vfs_node_t));
	memset(file, 0, sizeof(vfs_node_t));


	uint64_t* buff = (uint64_t*)pmmngr_alloc();
	memset(buff, 0, 4096);

	bool is_parent_root = false;

	_debug_print_ ("Creating directory \r\n");

	char fname[11];
	memset(fname,0,11);
	fat32_to_dos_file_name (filename, fname, 11);

	if (parent_clust == fat32_get_root_cluster ())
		is_parent_root = true;

search:
	for (int j = 0; j < fat32_get_sector_per_cluster(); j++) {
		memset(buff,0,4096);
		ahci_disk_read (ahci_disk_get_port(), cluster_to_sector32(parent_clust) + j, 1,buff);

		unsigned char* buffer = (unsigned char*)buff;
		fat32_dir *dirent = (fat32_dir*)buff;
		for (int i = 0; i < 16; i++) {

			char cmpname[11];
			memcpy (cmpname,dirent->filename, 11);

			if (strcmp(cmpname,fname) == 0) {
				strcpy (file->filename,fname);
				file->size = dirent->file_size;
				file->eof = 0;
				file->pos = 0;
				file->current = dirent->first_cluster;
				file->flags = FS_FLAG_DIRECTORY;
				file->status = FS_STATUS_FOUND;
				pmmngr_free(buff);
				_debug_print_ ("FAT32: Directory opened at entry-> %d \r\n",i);
			    return file;
			}
			dirent++;
		}
	}
	parent_clust = fat32_read_fat(parent_clust);
	if (parent_clust != FAT_EOC_MARK)
		goto search;
	else {
		free(file);
		return NULL;
	}
}

