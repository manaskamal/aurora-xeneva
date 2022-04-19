///!
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   vfs.cpp -- Virtual File System object
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury
///!
///!===================================================

#include <fs\vfs.h>
#include <stdio.h>
#include <arch\x86_64\mmngr\kheap.h>
#include <utils\gtree.h>
#include <fs\fat\fat.h>
#include <fs\devfs.h>

vfs_entry *root_dir = NULL;   // for '/' directory

vfs_node_t openfs (vfs_node_t *node, char* path) {
	if (node) {
		return node->open (node, path);
	}
}

void readfs (vfs_node_t *node, vfs_node_t* file, uint64_t* buffer, uint32_t length) {
	if (node) {
		node->read (file, buffer, length);
	}
}


void writefs (vfs_node_t *node, vfs_node_t* file, uint8_t *buffer, uint32_t length) {
	if (node) {
		node->write (file, buffer, length);
	}
}

void readfs_block (vfs_node_t* node, vfs_node_t* file, uint64_t *buffer) {
	if (node) {
		node->read_blk (file, buffer);
	}
}

int vfs_ioquery (vfs_node_t *node, int code, void* arg) {
	if (node) {
		return node->ioquery (node, code, arg);
	}
}


void AuVFSInit () {
	vfs_entry *root = (vfs_entry*)malloc(sizeof(vfs_entry));
	root->node = 0;
	root->childs = initialize_list();
	root_dir = root;


	//! Initialize the root file system
	initialize_fat32();
	fat32_self_register();

	//! Initialize the device file system
	devfs_mount();


}

vfs_node_t* vfs_finddir (char *path) {
	if (path[0] == '/' && strlen(path) == 2) {
		vfs_entry *entry_ = root_dir;
		return entry_->node;
	}


	char* next = strchr(path, '/');
	if (next)
		next++;

	char* fs_path = next;

	vfs_entry* ent = root_dir;
	vfs_node_t* entry_found = 0;
	char pathname[16];

	while(next) {
		int i = 0;
		for (i = 0; i < 16; i++) {
			if (next[i] == '/' || next[i] == '\0')
				break;
			pathname[i] = next[i];
		}
		pathname[i] = 0;

		if (ent == NULL)
			ent = root_dir;

		for (int j = 0; j < ent->childs->pointer; j++) {
			vfs_node_t *file_ = (vfs_node_t*)list_get_at(ent->childs, j);
			if (strcmp(file_->filename, pathname) == 0) {
				if (file_->flags == FS_FLAG_DIRECTORY)
					ent = (vfs_entry*)file_->device;
				entry_found = file_;
			}
		}

		next = strchr(next + 1, '/');
		if (next)
			next++;
	}

	if (!entry_found) 
		entry_found = root_dir->node;

	return entry_found;
}

/*
 * vfs_mkdir -- creates a virtual directory
 * @param path -- path to use
 * @param dir -- directory file
 * @param dir_node -- dir node
 */
void vfs_mkdir (char* path, vfs_node_t* dir, vfs_entry* dir_node) {
	dir->device = dir_node;
	bool found = false;
	char* next = strchr(path, '/');
	if (next)
		next++;

	vfs_entry* ent = root_dir;
	vfs_node_t* entry_found = 0;
	char pathname[16];
	
	while(next) {
		int i = 0;

		for (i = 0; i < 16; i++) {
			if (next[i] == '/' || next[i] == '\0')
				break;
			pathname[i] = next[i];
		}
		pathname[i] = 0;

		if (ent == NULL)
			ent = root_dir;

		for (int j = 0; j < ent->childs->pointer; j++) {
			vfs_node_t* file_ = (vfs_node_t*)list_get_at(ent->childs, j);
			if (strcmp(file_->filename, pathname) == 0) {
				if (file_->flags == FS_FLAG_DIRECTORY)
					ent = (vfs_entry *)file_->device;
				found = true;
				entry_found = file_;
			}
		}

		next = strchr(next + 1, '/');
		if (next)
			next++;
	}

	strcpy(dir->filename, pathname);
	if (found) {
		/* if this entry is a directory, recursively
		* call the node and check it */
		list_add(ent->childs, dir);
		return;
	}
	if (!found) {
		list_add(ent->childs, dir);
		return;
	}		
}

vfs_entry * vfs_mkentry() {
	vfs_entry* ent = (vfs_entry*)malloc(sizeof(vfs_entry));
	ent->node = 0;
	ent->childs = initialize_list();
	return ent;
}

/*
 * vfs_mount -- mounts a new filesystem to a vfs directory
 * @param path -- path to use
 * @param node -- file node
 * @param dirnode -- directory node
 */
void vfs_mount (char *path, vfs_node_t *node, vfs_entry *dirnode) {
	if (path[0] == '/' && strlen(path) == 2) {
		vfs_entry *entry_ = root_dir;
		if (entry_->node) {
			printf ("[VFS]: Mounting filesystem to root failed, already in use\n");
			return;   //Already a root filesystem is present
		}
		entry_->node = node; //else mount
		return;
	}


	//! seeking else? other mount points
	//! /home/manas
	char* next = strchr(path,'/');
	if (next)
		next++;
	
	vfs_entry *ent = dirnode;
	bool found = false;
	vfs_node_t *entry_found = 0;
	while (next) {
		int i = 0;
		char pathname[16];
		for (i = 0; i < 16; i++) {
			if ( next[i] == '/'  || next[i] == '\0')
				break;
			pathname[i] = next[i];
		}
		pathname[i] = 0;

		if (ent == NULL)
			ent = root_dir;

		for (int j = 0; j < ent->childs->pointer; j++) {
			vfs_node_t *file_ = (vfs_node_t*)list_get_at(ent->childs, j);
		
			if (strcmp(file_->filename, pathname)==0) {
				entry_found = file_;
				found = true;
			}
		}

		next = strchr (next + 1, '/'); 
		if (next)
			next++;
	}

	if (found) {
		if (entry_found->flags == FS_FLAG_DIRECTORY) {
			ent = (vfs_entry*)entry_found->device;
			vfs_mount(path,node,ent);
		}
		printf ("[vfs]: already mounted -> %s\n", path);
		return;
	}

	if (!found) {
		if (entry_found) {
			vfs_entry* entryn = vfs_mkentry();
			vfs_mkdir(path,node,entryn);
		}
		list_add(ent->childs, node);
	}
	
}

void vfs_lsdir (char* path) {
	char* next = strchr(path, '/');
	if (next)
		next++;

	bool found = false;
	vfs_entry *ent = root_dir;
	vfs_node_t *entry_found = 0;

	if (path[0] == '/' && strlen(path) == 2)
		found = true;


	while (next) {
		int i = 0;
	    char pathname[16];
		for (i = 0; i < 16; i++) {
			if (next[i] == '/' || next[i] == '\0')
				break;
			pathname[i] = next[i];
		}
		pathname[i] = 0;

		for (int j = 0; j < ent->childs->pointer; j++) {
			vfs_node_t *file_ = (vfs_node_t*)list_get_at(ent->childs, j);
			entry_found = file_;
			if (strcmp(file_->filename, pathname) == 0) {
				if (file_->flags == FS_FLAG_DIRECTORY)
					ent = (vfs_entry *)file_->device;
			}
		}

		next = strchr(next + 1, '/');
		if (next)
			next++;
	}

	if (ent) {
		/* if this entry is a directory, recursively
		* call the node and check it */
		for (int i = 0; i < ent->childs->pointer; i++) {
			vfs_node_t *f = (vfs_node_t*)list_get_at(ent->childs, i);
			char* type = 0;
			if (f->flags == FS_FLAG_DIRECTORY)
				type = "Directory";
			else if (f->flags == FS_FLAG_GENERAL)
				type = "File";
			printf("%s -> %s \n",type, f->filename);
		}
		return;
	}
}


