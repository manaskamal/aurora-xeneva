/**
 *
 *   Copyright (C) Manas Kamal Choudhury 2021
 *
 *   FAT32 -- FILE ALLOCATION TABLE V32
 *
 *   /PROJECT - Xeneva v1.0
 *   /AUTHOR  - Manas Kamal Choudhury
 *
 * =====================================================
 */

#include <fs/fat32.h>
#include <drivers\ata.h>
#include <pmmngr.h>
#include <ctype.h>


unsigned int part_lba;  //partition_begin_lba
unsigned long fat_begin_lba;
unsigned long cluster_begin_lba;
unsigned char sectors_per_cluster;
unsigned long root_dir_first_cluster;
unsigned long root_sector;

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
	for (int i=0; i <12; i++) {
		putc(fat32_data->info.FAT32.vol_label[i]);
	}
	for (int i=0; i <9; i++) {
		putc(fat32_data->info.FAT32.sys_id[i]);
	}
#endif

	fat_begin_lba = part_lba + fat32_data->reserved_sectors;
	cluster_begin_lba = part_lba + fat32_data->reserved_sectors + (fat32_data->num_fats * fat32_data->info.FAT32.sect_per_fat32);
	sectors_per_cluster = fat32_data->sectors_per_cluster;
	root_dir_first_cluster = fat32_data->info.FAT32.root_dir_cluster;
	root_sector = cluster_to_sector32 (root_dir_first_cluster);
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

void fat32_read (FILE *file, unsigned char* buf) {

	auto lba = cluster_to_sector32 (file->start_cluster); 
	/*ata_read_28 (lba, 1, buf);
	ata_read_28 (lba + 1, 1, buf + 512);
	ata_read_28 (lba + 2, 1, buf + 512 + 512);
	ata_read_28 (lba + 3, 1, buf + 512 + 512 + 512);
	ata_read_28 (lba + 4, 1, buf + 512 + 512 + 512 + 512);
	ata_read_28 (lba + 5, 1, buf + 512 + 512 + 512 + 512 + 512);
	ata_read_28 (lba + 6, 1, buf + 512 + 512 + 512 + 512 + 512 + 512);
	ata_read_28 (lba + 7, 1, buf + 512 + 512 + 512 + 512 + 512 + 512 + 512);*/
	for (int i = 0; i < 8; i++) {
		ata_read_28 (lba+i,1,buf);
		buf += 512;
	}

	//kprintf("Current cluster -> %x\n",file->start_cluster);
    uint32_t value = fat32_read_fat (file->start_cluster);
	if (value  >= 0x0FFFFFF8) {
	    file->eof = 1;
	}

	if (value  == 0x0FFFFFF7) {
	    file->eof = 1;
	}


	file->start_cluster = value;
}


void fat32_read_file (FILE *file, unsigned char* buf, int count) {
	for (int i=0; i < count; i+= 8) {
		fat32_read(file,buf);
		if(file->eof) {
			break;
		}
		buf += 4096;
	}
}

FILE fat32_locate_dir (const char* dir) {
    
	FILE file;
	unsigned char* buf;
	fat32_dir *dirent;

	char dos_file_name[11];
	to_dos_file_name32 (dir, dos_file_name, 11);
	//dos_file_name[11]=0;

	for (unsigned int sector = 0; sector < 14; sector++) {
		buf = (unsigned char*)pmmngr_alloc ();
		ata_read_28 (root_sector + sector,1, buf);
		dirent = (fat32_dir*)buf;
		for (int i=0; i < 16; i++) {
			
			char name[11];
			memcpy (name, dirent->filename, 11);
			//name[11] = 0;

			if (strcmp (dos_file_name, name) == 0) {
				//kprintf ("File found\n");
				strcpy (file.filename, dir);
				file.id = 0;
				file.start_cluster = dirent->first_cluster;
				file.size = dirent->file_size;
				file.eof = 0;
				file.status = FILE_STATUS_FOUND;

				if (dirent->attrib == 0x10)
					file.flags = FILE_FLAG_DIRECTORY;
				else
					file.flags = FILE_FLAG_GENERAL;
				
				pmmngr_free(buf);
				return file;
			}
			dirent++;
		}
		pmmngr_free(buf);		
	}

	file.status = FILE_FLAG_INVALID;
	file.id = 0;
	file.size = 0;
	file.eof = 0;
	return file;
}


FILE fat32_locate_subdir (FILE kfile, const char* filename) {

	FILE file;

	char dos_file_name[11];
	to_dos_file_name32 (filename, dos_file_name, 11);
	//dos_file_name[11] = 0;

	if (kfile.flags != FILE_FLAG_INVALID) {
		
		//! read the directory
		while (!kfile.eof) {

			//! read 
			unsigned char* buf = (unsigned char*)pmmngr_alloc();
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
					file.id = 0;
					file.start_cluster = pkDir->first_cluster;
					file.size = pkDir->file_size;
					file.eof = 0;
					file.status = FILE_STATUS_FOUND;
					//! set file type
					if (pkDir->attrib == 0x10)
						file.flags = FILE_FLAG_DIRECTORY;
					else
						file.flags = FILE_FLAG_GENERAL;

					//!return file
					return file;
				}

				//! go to next entry
				pkDir++;
			}

			//pmmngr_free (buf);
		}
	}

	file.flags = FILE_FLAG_INVALID;
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
FILE fat32_open (const char* filename) {

	FILE cur_dir;
	char* p = 0;
	bool  root_dir = true;
	char* path = (char*) filename;

	//! any '\'s in path ?
	p = strchr (path, '\\');
	if (!p) {

		//! nope, must be in root directory, search it
		cur_dir = fat32_locate_dir (path);

		//! found file ?
		if (cur_dir.flags == FILE_FLAG_GENERAL)
			return cur_dir;

		//! unable to find
		FILE ret;
		ret.flags = FILE_FLAG_INVALID;
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
			if (p[i] == '\\' || p[i]=='\0')
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
		if (cur_dir.flags == FILE_FLAG_INVALID)
			break;

		//! found file?
		if (cur_dir.flags == FILE_FLAG_GENERAL)
			return cur_dir;

		//! find next '\'
		p=strchr(p+1, '\\');
		if (p)
			p++;
	}

	//! unable to find
	FILE ret;
	ret.flags = FILE_FLAG_INVALID;
	return ret;
}
