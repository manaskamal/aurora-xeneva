/**
 *
 *   Copyright (C) Manas Kamal Choudhury 2021
 *
 *   FAT32 -- FILE ALLOCATION TABLE V32
 *
 *   /PROJECT - Xeneva v1.0
 *   /AUTHOR  - Manas Kamal Choudhury
 *
 *   Read-Only Mode Supported for now
 * =====================================================
 */

#include <fs/fat32.h>
#include <drivers\ata.h>
#include <pmmngr.h>
#include <ctype.h>
#include <mm.h>
#include <console.h>
#include <fs/vfs.h>


unsigned int part_lba;  //partition_begin_lba
unsigned long fat_begin_lba;
unsigned long cluster_begin_lba;
unsigned char sectors_per_cluster = 0;
unsigned long root_dir_first_cluster;
unsigned long root_sector;
unsigned int sectors_per_fat32;
int alloc_counter = 0;
unsigned int total_clusters;
unsigned char* root_dir_cache;

#define max(a, b) ((a) >= (b) ? (a) : (b))


//! converts clusters to LBA 
uint64_t  cluster_to_sector32 (uint64_t cluster)
{
	return cluster_begin_lba + (cluster - 2) * sectors_per_cluster ;
}



void to_dos_file_name32 (const char* filename, char* fname, unsigned int fname_length)
{
	unsigned int i=0;

	if (fname_length > 11)
		return;

	if (!fname || !filename)
		return;

	memset (fname, ' ', fname_length);

	for (i=0; i < strlen (filename)-1 && i < fname_length; i++)
	{
		if (filename[i] == '.' || i==8)
			break;

		fname[i] = toupper (filename[i]);
	}

	if (filename[i] =='.')
	{
		for (int k=0; k < 3; k++)
		{
			 ++i;
			 if (filename[i])
				 fname[8+k] = filename[i];
		}
	}

	for (i = 0; i < 3; i++)
		fname[8+i] = toupper (fname[8+i]);
}



static uint32_t read_32 (uint8_t* buff, size_t offset) {
	uint8_t* ubuff = buff + offset;
	return ((ubuff[3] << 24) & 0xFF000000) | 
		((ubuff[2] << 16) & 0x00FF0000) | 
		((ubuff[1] << 8) & 0x0000FF00) | 
		(ubuff[0] & 0x000000FF);
}



void initialize_fat32 () {

	unsigned char *buf = (unsigned char*)pmmngr_alloc();
	ata_read_28 (2048,1,buf); //partition_begin_lba = 2048

	BPB *fat32_data = (BPB*)buf;

	part_lba = 2048;

#if 0
	printf ("FAT32 BOOT PARAMETER BLOCK\n");
	printf ("Bytes/Sector -> %d\n", fat32_data->bytes_per_sector);
	printf ("Sectors/Cluster -> %d\n", fat32_data->sectors_per_cluster);
	printf ("Reserved Sectors -> %d\n", fat32_data->reserved_sectors);
	printf ("Number Of FATs -> %d\n", fat32_data->num_fats);
	printf ("Root Base Cluster -> %d\n", fat32_data->info.FAT32.root_dir_cluster);
	printf ("Sector/FAT32 -> %d\n", fat32_data->info.FAT32.sect_per_fat32);
#endif
	for (int i=0; i <12; i++) {
		putc(fat32_data->info.FAT32.vol_label[i]);
	}
	for (int i=0; i <9; i++) {
		putc(fat32_data->info.FAT32.sys_id[i]);
	}


	fat_begin_lba = part_lba + fat32_data->reserved_sectors;
	cluster_begin_lba = part_lba + fat32_data->reserved_sectors + (fat32_data->num_fats * fat32_data->info.FAT32.sect_per_fat32);
	sectors_per_cluster = fat32_data->sectors_per_cluster;
	root_dir_first_cluster = fat32_data->info.FAT32.root_dir_cluster;
	root_sector = cluster_to_sector32 (root_dir_first_cluster);
	sectors_per_fat32 = fat32_data->info.FAT32.sect_per_fat32;

	total_clusters = fat32_data->large_sector_count / sectors_per_cluster;
	//fat32_list_files();
	//for (int i = 0; i < sectors_per_cluster; i++) {
	//	ata_read_28 (root_sector + i, 1, root_dir_cache);
	//	root_dir_cache += 512;
	//}

}


uint32_t fat32_read_fat (uint32_t cluster_index) {
	auto fat_offset = cluster_index * 4;
	uint64_t fat_sector = fat_begin_lba + (fat_offset / 512);
	size_t ent_offset = fat_offset  % 512;
	unsigned char buf[512];
	ata_read_28 (fat_sector,1,buf);
	uint32_t value = *(uint32_t*) &buf[ent_offset];
	return value & 0x0FFFFFFF;
}



void fat32_read (vfs_node_t *file, unsigned char* buf) {

	auto lba = cluster_to_sector32 (file->current); 	

	for (int i = 0; i < sectors_per_cluster; i++) {
		ata_read_28 (lba+i,1,buf);
		buf += 512;
	}
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


void fat32_read_file (vfs_node_t *file, unsigned char* buf, uint32_t count) {
	for (int i=0; i < count; i+= 8) {
		fat32_read(file,buf);
		if(file->eof) {
			break;
		}
		buf += 4096;
	}
}

vfs_node_t fat32_locate_dir (const char* dir) {
	vfs_node_t file;
	unsigned char* buf;
	fat32_dir *dirent;

	char dos_file_name[11];
	to_dos_file_name32 (dir, dos_file_name, 11);
	//dos_file_name[11]=0;	
	buf = (unsigned char*)pmmngr_alloc ();
	for (unsigned int sector = 0; sector < sectors_per_cluster; sector++) {
	
		memset (buf, 0, 4096);
		ata_read_28 (root_sector + sector,1, buf);
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
				
				pmmngr_free(buf);
				return file;
			}
			dirent++;
		}
		pmmngr_free(buf);		
	}

	file.status = FS_FLAG_INVALID;
	file.size = 0;
	file.eof = 0;
	return file;
}


vfs_node_t fat32_locate_subdir (vfs_node_t kfile, const char* filename) {

	vfs_node_t file;

	char dos_file_name[11];
	to_dos_file_name32 (filename, dos_file_name, 11);
	//dos_file_name[11] = 0;
	unsigned char* buf = (unsigned char*)pmmngr_alloc();
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

					//!return file
					return file;
				}

				//! go to next entry
				pkDir++;
			}

			//pmmngr_free (buf);
		}
	}

	file.flags = FS_FLAG_INVALID;
	return file;
}


void convert_fat83_32(fat32_dir *root, char *filename)
{
	char *p;
	char *f = filename;
	int i;

	p = (char*)root->filename;
	i = 8;
	while ((*p != 0x20) && i)
	{
		*f++ = *p++;
		i--;
	}

	*f++ = '.';

	p = (char*)root->ext;
	i = 3;
	while ((*p != 0x20) && i)
	{
		*f++ = *p++;
		i--;
	}

	if (i == 3)
		f--;

	*f++ = '\0';
}

void fat32_list_files() {
	unsigned char buf[512];
	unsigned char buf2[512];
	char filename[32];
	ata_read_28(root_sector, 1, buf);
	ata_read_28(root_sector + 1, 1, buf2);
	fat32_dir *dir = (fat32_dir*)buf;
	for (int i=0; i < 16; i++) {
		convert_fat83_32(dir,filename);
		printf ("%s             %d bytes\n",filename, dir->file_size);
		dir++;
	}

	char filename2[32];
	fat32_dir *dir2 = (fat32_dir*)buf2;
	for (int i=0; i < 16; i++) {
		convert_fat83_32(dir2,filename2);
		printf ("%s             %d bytes\n",filename2, dir2->file_size);
		dir2++;
	}
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
		if (cur_dir.flags == FS_FLAG_GENERAL)
			return cur_dir;

		//! find next '\'
		p=strchr(p+1, '/');
		if (p)
			p++;
	}

	//! unable to find
	vfs_node_t ret;
	ret.flags = FS_FLAG_INVALID;
	return ret;
}


//! Write buffers to sectors {Physical Disk}
//! @param buffer -- Buffer Pointer
//! @param sector -- Starting lba
//! @param count  -- number of sectors to write
static void update_sector (uint8_t *buffer, uint32_t sector, uint32_t count) {
	for (int i =0; i < count; i++) {
		ata_write_one (buffer + (i * 512),sector + i);
	}
}

//! Update clusters 
//! @param buffer -- pointer to buffer to write
//! @param cluster_number -- cluster pointer
//! @.....
static void update_cluster (uint8_t* buffer, uint32_t cluster_number) {
	uint32_t sector = cluster_to_sector32 (cluster_number);
	uint32_t sector_count = sectors_per_cluster;
	update_sector (buffer, sector, sector_count);
}

//! Clear clusters
//! @param cluster -- cluster pointer
//! @...
static void clear_cluster (uint32_t cluster) {
	uint8_t *buffer = (uint8_t*)pmmngr_alloc();
	memset (buffer, 0, 4096);
	//update_cluster (buffer,cluster);
	uint32_t sector = cluster_to_sector32 (cluster);
	for (int i = 0; i < sectors_per_cluster; i++) {
		ata_write_one(buffer + (i*512),sector + i);
	}
	pmmngr_free (buffer);
}


//! Finds free clusters in FAT Table
uint32_t find_free_cluster () {
	//!iterate through every sectors in fat32 table
	for (int i = 2; i < total_clusters; i++) {
		auto fat_offset = i * 4;
		uint64_t fat_sector = fat_begin_lba + (fat_offset / 512);
		size_t ent_offset = fat_offset  % 512;
		unsigned char *buf = (unsigned char*)malloc(512);
		ata_read_28 (fat_sector,1,buf);
		uint32_t value = *(uint32_t*)&buf[ent_offset];
		
		//! Found a free cluster return the value
		if (value == 0x0) {
			return i;
		}
	}

	return 0;
}

//!Allocate a new cluster and add the entry in FAT table
uint32_t alloc_cluster (int position, uint32_t n_value) {
	auto fat_offset = position * 4;
	uint64_t fat_sector = fat_begin_lba + (fat_offset / 512);
	size_t ent_offset = fat_offset  % 512;
	unsigned char *buf = (unsigned char*)malloc(512);
	ata_read_28 (fat_sector,1,buf);
	uint32_t value = *(uint32_t*)&buf[ent_offset];
		
	*(uint32_t*)&buf[ent_offset] = n_value;// & 0x0FFFFFFF;
	ata_write_one (buf,fat_sector);
	uint32_t value2 = *(uint32_t*)&buf[ent_offset];
	return value2;
}


//!Allocate a new cluster and add the entry in FAT table
uint32_t find_cluster (uint32_t new_cluster) {
	auto fat_offset = new_cluster * 4;
	uint64_t fat_sector = fat_begin_lba + (fat_offset / 512);
	size_t ent_offset = fat_offset  % 512;
	unsigned char *buf = (unsigned char*)malloc(512);
	ata_read_28 (fat_sector,1,buf);
	uint32_t value = *(uint32_t*)&buf[ent_offset];		
	return value;
}

//! Get cluster value
uint32_t get_cluster (uint32_t cluster) {
	auto fat_offset = cluster * 4;
	uint64_t fat_sector = fat_begin_lba + (fat_offset / 512);
	size_t ent_offset = fat_offset  % 512;
	unsigned char *buf = (unsigned char*)malloc(512);
	ata_read_28 (fat_sector,1,buf);
	uint32_t value = *(uint32_t*)&buf[ent_offset];		
	return value;
}


void format_fat83_32(char *string_to_format, char ext[3],  char *filename)
{
	char *p;
	char *f = filename;
	int i;

	p = string_to_format;
	i = 8;
	while ((*p != 0x20) && i)
	{
		*f++ = *p++;
		i--;
	}

	*f++ = '.';

	p = (char*)ext;
	i = 3;
	while ((*p != 0x20) && i)
	{
		*f++ = *p++;
		i--;
	}

	if (i == 3)
		f--;

	*f++ = '\0';
}

void list_fat_entries () {

	printf ("Root Dir entries scanning\n");
	fat32_dir *dirent;
	char filename2[32];
	char format_name[11];

	unsigned char buf[512];
	for (int i = 0; i < sectors_per_cluster; i++) {
		ata_read_28 (root_sector + i, 1,buf);
		dirent = (fat32_dir*)buf;
		for (int j = 0; j < 16; j++) {
			convert_fat83_32(dirent,filename2);
			printf ("Other file size -> %s, dirent attrib -> %x, count ->%d\n", filename2, *(uint8_t*)&buf[j], i);
			dirent++;
		}
	}
}



/**
 * Write contents from RAM to disk 
 *
 * @param buffer - Pointer to the buffer {i.e data in RAM}
 * @param first_cluster - Address of the first cluster
 * @param length - Length of the file in bytes
 */
void fat32_write_content (uint8_t *buffer, uint32_t first_cluster, unsigned int length) {
	bool parse_fat = false;
	uint32_t num_cluster = 0;
	uint32_t sector_first = cluster_to_sector32 (first_cluster);
	for (int i = 0; i < sectors_per_cluster; i++) {
		ata_write_one (buffer + (i * 512), sector_first + i);
	}
	buffer += 4096;

	if (length > 4096) {
		parse_fat = true;
		num_cluster = length / 4096;
	}

	if (parse_fat) {
		for (int k = 0; k < num_cluster; k++) {
			uint32_t cluster_value = get_cluster (first_cluster);
			if (cluster_value >= 0x0FFFFFF8)
				return;
			uint32_t sector = cluster_to_sector32 (cluster_value);
			for (int i = 0; i < sectors_per_cluster; i++) {
				ata_write_one (buffer + (i * 512), sector + i);
			}
			buffer += 4096;
			first_cluster = cluster_value;
		}
	}
}


/** 
 * Create a file and write the contents to disk
 *
 * @param filename -- Name of the file
 * @param buffer -- Pointer to the data in RAM
 * @param length -- Length of the file
 *
 */
uint32_t fat32_create_file  (char* filename, uint8_t *buffer, unsigned int length) {

	/**
	 * First we scan the FAT table for free cluster which will
	 * be used as first cluster and store it in a temporary variable
	 */
	uint32_t first_cluster = 0;
	uint32_t cluster_first = find_free_cluster ();
	first_cluster = cluster_first;
	uint32_t status = alloc_cluster (cluster_first, 0x0FFFFFF8);

	//! Clear the cluster
	clear_cluster (cluster_first);

	//! Now calculate the number of clusters required 
	//! for the file
	uint32_t required_cluster = 0;
	if (length > 4096) {
		for (int i = 0; i < length / 4096; i++) {
			required_cluster++;
		}
	}

	//! Now allocate each clusters in the fat table
	//! [Knowledge]: In FAT table if the file requires more cluster
	//! than the file's first cluster points to next cluster
	//! kind of linked list data structure
    uint32_t cluster = 0;
	for (int i = 0; i < required_cluster; i++) {
		cluster = find_free_cluster ();
		uint32_t stat = alloc_cluster (cluster_first, cluster);
		clear_cluster (cluster);
		cluster_first = cluster;
	}

	//! the last cluster should be marked as EOC {0x0FFFFFF8}
	uint32_t status2 = alloc_cluster (cluster, 0x0FFFFFF8);

	//! Finally format the name 
	//! for now Aurora's Xeneva support only short name MSDOS 8.3
	char formated_name[11];
	to_dos_file_name32 (filename, formated_name, 11);

	//! now it's time to parse the root directory
	unsigned char buf[512];
	//! Root Directory Entries scanning goes here
	for (int sector = 0; sector < sectors_per_cluster; sector++) {
		ata_read_28 (root_sector + sector,1, buf);	
		fat32_dir *dirent = (fat32_dir*)buf;
		for (int i = 0; i < 16; i++) {
		
			//! scan for free directory entry
			if (dirent->filename[0] == 0x00 || dirent->filename[0] == 0xE5){
				
				memset(dirent, 0, sizeof(fat32_dir));
				memcpy (dirent->filename, formated_name, 11);
				dirent->attrib = ATTRIBUTE_ARCHIVE;
				dirent->time_created_ms = 2021;
				dirent->time_created = 2021;
				dirent->date_created = 2021;
				dirent->date_last_accessed = 2021;
				dirent->first_cluster_hi_bytes = (first_cluster >> 16) & 0xFFFF;
				dirent->last_mod_time = 2021;
				dirent->last_mod_date = 2021;
				dirent->first_cluster = first_cluster & 0xFFFF;
				dirent->file_size = length;
				//! write the dir entry and go for writing the contents of the file
				ata_write_one (buf, root_sector + sector);
				//! actuall file writing process begins here
				fat32_write_content (buffer, first_cluster,length);
				return 0;
			}
			dirent++;
		}
	
	}
	//!free every allocated memories
}


void create_dir (const char* filename) {
	/**
	 * First we scan the FAT table for free cluster which will
	 * be used as first cluster and store it in a temporary variable
	 */
	uint32_t first_cluster = 0;
	uint32_t cluster_first = find_free_cluster ();
	first_cluster = cluster_first;
	uint32_t status = alloc_cluster (cluster_first, 0x0FFFFFF8);

	//! Clear the cluster
	clear_cluster (cluster_first);

	char formated_name[11];
	to_dos_file_name32 (filename, formated_name, 11);
    unsigned char buf[512];
	//! now it's time to parse the root directory
	//! Root Directory Entries scanning goes here
	for (int sector = 0; sector < sectors_per_cluster; sector++) {
		
		ata_read_28 (root_sector + sector,1, buf);
		fat32_dir *dirent = (fat32_dir*)buf;
		for (int i = 0; i < 16; i++) {


			//! scan for free directory entry
			if (dirent->filename[0] == 0x00 || dirent->filename[0] == 0xE5){
				printf ("Empty entry found\n");
				memset(dirent, 0, sizeof(fat32_dir));
				memcpy (dirent->filename, formated_name, 11);
				dirent->attrib = ATTRIBUTE_DIRECTORY;
				dirent->time_created_ms = 2021;
				dirent->time_created = 2021;
				dirent->date_created = 2021;
				dirent->date_last_accessed = 2021;
				dirent->first_cluster_hi_bytes = (first_cluster >> 16) & 0xFFFF;
				dirent->last_mod_time = 2021;
				dirent->last_mod_date = 2021;
				dirent->first_cluster = first_cluster & 0xFFFF;
				dirent->file_size = 0;

				//! write the dir entry and go for writing the contents of the file
				ata_write_one (buf, root_sector + sector);

				unsigned char* dir_content = (unsigned char*)pmmngr_alloc();
				memset(dir_content, 0, 4096);
				uint32_t sector_d = cluster_to_sector32 (first_cluster);
				fat32_dir *dot_entry = (fat32_dir*)dir_content;
				dot_entry->attrib = ATTRIBUTE_DIRECTORY;
				dot_entry->time_created_ms = 2021;
				dot_entry->time_created = 2021;
				dot_entry->date_created = 2021;
				dot_entry->date_last_accessed = 2021;
				dot_entry->first_cluster_hi_bytes = (first_cluster >> 16) & 0xFFFF;
				dot_entry->last_mod_time = 2021;
				dot_entry->last_mod_date = 2021;
				dot_entry->first_cluster = first_cluster & 0xFFFF;
				dot_entry->file_size = 0;


				fat32_dir* dot_dot_entry = (fat32_dir*)(dir_content + 32);
				dot_dot_entry->attrib = ATTRIBUTE_DIRECTORY;
				dot_dot_entry->time_created_ms = 2021;
				dot_dot_entry->time_created = 2021;
				dot_dot_entry->date_created = 2021;
				dot_dot_entry->date_last_accessed = 2021;
				dot_dot_entry->first_cluster_hi_bytes = (root_dir_first_cluster >> 16) & 0xFFFF;
				dot_dot_entry->last_mod_time = 2021;
				dot_dot_entry->last_mod_date = 2021;
				dot_dot_entry->first_cluster = root_dir_first_cluster & 0xFFFF;
				dot_dot_entry->file_size = 0;

				for (int i = 0; i < 8; i++) {
					ata_write_one (dir_content + (i * 512),sector_d + i);
				}
				return;
			}
			dirent++;
		}
	}

}


void fat32_self_register () {
	vfs_node_t *fsys = (vfs_node_t*)malloc(sizeof(vfs_node_t));
	strcpy (fsys->filename, "/");
	fsys->size = 0;
	fsys->eof = 0;
	fsys->pos = 0;
	fsys->current = 0;
	fsys->flags = FS_FLAG_DIRECTORY;
	fsys->status = 0;
	fsys->open = fat32_open;
	fsys->read = fat32_read_file;
	fsys->write = 0;
	fsys->read_blk = fat32_read;
	fsys->ioquery = 0;
	vfs_mount ("/", fsys);
	printf ("File System registered\n");
}






