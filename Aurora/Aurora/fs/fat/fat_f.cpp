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
 * @fat_file --FAT file system's file management
 *
 **/

#include <fs\fat\fat_f.h>
#include <fs\fat\fat_util.h>
#include <fs\fat\fat.h>
#include <arch\x86_64\mmngr\kheap.h>
#include <pmmngr.h>
#include <drivers\ahci.h>
#include <drivers\ahci_disk.h>
#include <string.h>
#include <serial.h>


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
 * fat32_make_file -- creates a fat32 file
 * @param parent_clust -- parent directory cluster
 * @param filename -- filename
 * @param size -- size of the file
 */
vfs_node_t* fat32_make_file (uint32_t parent_clust, char* filename, uint32_t size) {
	vfs_node_t *file = (vfs_node_t*)malloc(sizeof(vfs_node_t));
	memset(file, 0, sizeof(vfs_node_t));


	uint64_t* buff = (uint64_t*)pmmngr_alloc();
	memset(buff, 0, 4096);

	bool is_parent_root = false;

	_debug_print_ ("FAT32: Creating a file \r\n");

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

				dirent->attrib = ATTRIBUTE_ARCHIVE;
				dirent->first_cluster = cluster & 0x0000FFFF;
				dirent->first_cluster_hi_bytes = (cluster & 0x0FFF0000)>>16;
				dirent->date_created = fat32_format_date();
				dirent->time_created = fat32_format_time();
				dirent->last_wrt_date = dirent->date_created;
				dirent->last_wrt_time = dirent->time_created;
				dirent->date_last_accessed = 0;
				dirent->file_size = size;

			    ahci_disk_write (ahci_disk_get_port(),cluster_to_sector32(parent_clust) + j,1,buff);
			    pmmngr_free(buffer);

				strcpy (file->filename,fname);
				file->size = dirent->file_size;
				file->eof = 0;
				file->pos = 0;
				file->current = dirent->first_cluster;
				file->flags = FS_FLAG_GENERAL;
				file->status = FS_STATUS_FOUND;
				_debug_print_ ("FAT32: file created at entry-> %d \r\n",i);
			    return file;
			}
			dirent++;
		}
	}
	parent_clust = fat32_read_fat(parent_clust);
	if (parent_clust != FAT_EOC_MARK)
		goto search;
	else {
		free (file);
		return NULL;
	}
}


/**
 * fat32_write_content -- writes memory buffers to a file on disk
 * @param first_cluster -- first cluster of the file
 * @param buffer -- pointer to the memory buffer
 * @param length -- length of the file
 */
void fat32_write_content (uint32_t first_cluster, uint8_t *buffer, uint32_t length) {

	uint32_t one_cluster_sz = 512* fat32_get_sector_per_cluster();

	uint32_t required_cluster = 0;
	if (length > one_cluster_sz) {
		for (int i = 0; i < length / one_cluster_sz; i++)
			required_cluster++;
	}

	uint64_t* ahci_buff = (uint64_t*)pmmngr_alloc();
	memset(ahci_buff, 0, 4096);
	

	uint32_t cluster = first_cluster;
	
	for (int i = 0; i < required_cluster; i++) {
		if (cluster != FAT_EOC_MARK || cluster != FAT_BAD_CLUSTER) {
			memcpy (ahci_buff,buffer,4096);
			ahci_disk_write (ahci_disk_get_port(),cluster_to_sector32(cluster),fat32_get_sector_per_cluster(),ahci_buff);
			_debug_print_ ("[FAT32]: cluster -> %d flushed to disk \r\n", cluster);
		}
		cluster = fat32_read_fat(cluster);
		if (cluster == FAT_EOC_MARK || cluster == FAT_BAD_CLUSTER)
			break;
		buffer += 4096;
	}

	pmmngr_free(ahci_buff);
}
/**
 * fat32_write_file -- writes memory buffers to a file
 * @param file -- pointer to the file object
 * @param buffer -- pointer to the memory buffer
 * @param length -- length of the file
 */
void fat32_write_file (vfs_node_t *file, uint8_t* buffer, uint32_t length) {

	uint32_t one_cluster_sz = 512* fat32_get_sector_per_cluster();

	uint32_t required_cluster = 0;
	if (length > one_cluster_sz) {
		for (int i = 0; i < length / one_cluster_sz; i++)
			required_cluster++;
	}

	_debug_print_ ("[FAT32]: Writing to file, required clusters -> %d \r\n", required_cluster);

	uint32_t cluster = file->current;

	uint32_t cluster_next = 0;
	for (int i = 0; i < required_cluster-1; i++) {
		cluster_next = fat32_find_free_cluster();
		fat32_alloc_cluster(cluster,cluster_next);
		fat32_clear_cluster (cluster);
		cluster = cluster_next;
	}
	fat32_alloc_cluster (cluster,FAT_EOC_MARK);

	fat32_write_content (file->current,buffer, length);
}

