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
#include <fs\fat32.h>
#include <fs\devfs.h>

vfs_entry *root_entry = NULL;   // for '/' directory
vfs_entry *dev_entry = NULL;    //! for '/dev' directory

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


void vfs_init () {
	vfs_entry *entry = (vfs_entry*)malloc(sizeof(vfs_entry));
	entry->next = NULL;
	entry->node = 0;
	entry->prev = NULL;
	root_entry = entry;

	vfs_entry *dev = (vfs_entry*)malloc(sizeof(vfs_entry));
	dev->next = NULL;
	dev->node = 0;
	dev->prev = NULL;
	dev_entry = dev;

	//! Initialize the root file system
	initialize_fat32();
	fat32_self_register();

	//! Initialize the device file system
	devfs_mount();


}


vfs_node_t * devfs_get_node (char* path) {
	int i;
	char *p = strchr(path, '/');
	p++;
	
	char pathname[16];

	for (i = 0; i < 16; i++) {
		if ( p[i] == '/'  || p[i] == '\0')
			break;
		pathname[i] = p[i];
	}


	if (strcmp(pathname, "dev") && strlen(path) == 5) {
		return dev_entry->node;
	}

	char *next = strchr(path, '/');
	if (next)
		next++;

	vfs_entry *ent;
	bool found;
	while (next) {
		int i = 0;
		char pathname[16];
		for (i = 0; i < 16; i++) {
			if ( next[i] == '/'  || next[i] == '\0')
				break;
			pathname[i] = next[i];
		}
		pathname[i] = 0;

		ent = dev_entry;
		while(ent->next != 0) {
			ent = ent->next;
			if (!(strcmp(pathname, "dev")==0)){
				if (strcmp(ent->node->filename, pathname)==0) {
					found = true;
					break;
				}
			}
			
		}
		

		next = strchr (next + 1, '/'); 
		if (next)
			next++;
	}

	if (found) {
		if (ent->node) {
			return ent->node;
		}
		return NULL;
	}

	return NULL;
}


vfs_node_t* vfs_finddir (char *path) {
	int i;
	char *p = strchr(path, '/');
	p++;
	
	char pathname[16];

	for (i = 0; i < 16; i++) {
		if ( p[i] == '/'  || p[i] == '\0')
			break;
		pathname[i] = p[i];
	}

	pathname[i] = 0;

	if (strcmp (pathname,"dev") == 0) {
		//pass the path to devfs 
		return devfs_get_node (path);
	}

	/* Any directory or file except ('dev', 'tmp', ..etc) belongs to the
	   root file system, I just pass the path to root file system (FAT32) for now */
	vfs_node_t *node = root_entry->node;
	return node;
}


void vfs_add_devfs (char *path, vfs_node_t *node) {
	int i;
	char *p = strchr(path, '/');
	p++;
	
	if (strcmp(p, "dev") && strlen(path) == 5) {
		vfs_entry *entry_ = (vfs_entry*)dev_entry;
		if (entry_->node) {
			printf ("[VFS]: /dev directory is already present");
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
	
	vfs_entry *ent ;
	bool found = false;
	int count = 0;
	while (next) {
		int i = 0;
		char pathname[16];
		for (i = 0; i < 16; i++) {
			if ( next[i] == '/'  || next[i] == '\0')
				break;
			pathname[i] = next[i];
		}
		pathname[i] = 0;

		ent = dev_entry;
		while(ent->next != 0) {
			ent = ent->next;
			//!is this last value in the path && pathname is not "dev"?
			if (!(strcmp (pathname, "dev") == 0)){
				if (strcmp (ent->node->filename, pathname) == 0) {
					found = true;
					break;
				}
			}
		}

		next = strchr (next + 1, '/'); 
		if (next)
			next++;
	}

	if (found) {
		if (ent->node) {
			printf ("[VFS]: %s is already mounted in /dev directory\n", ent->node->filename);
			return;
		}else {
			ent->node = node;
		}
	}


	if (!found) {
		ent = dev_entry;
		while(ent->next != 0)
			ent = ent->next;
		vfs_entry *entry = (vfs_entry*)malloc(sizeof(vfs_entry));
		entry->prev = ent;
		entry->node = node;
		entry->next = NULL;
		ent->next = entry;
	}
}


void vfs_mount (char *path, vfs_node_t *node) {
	if (path[0] == '/' && strlen(path) == 2) {
		vfs_entry *entry_ = (vfs_entry*)root_entry;
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
	
	vfs_entry *ent ;
	bool found = false;
	int count = 0;
	while (next) {
		int i = 0;
		char pathname[16];
		for (i = 0; i < 16; i++) {
			if ( next[i] == '/'  || next[i] == '\0')
				break;
			pathname[i] = next[i];
		}
		pathname[i] = 0;

		if (strcmp(pathname, "dev") == 0) {
			//!pass the path to devfs
			vfs_add_devfs (path,node);
			break;
		}

		ent = root_entry;
		while(ent->next != 0) {
			ent = ent->next;
			if (strcmp(ent->node->filename, pathname)==0) {
				found = true;
				break;
			}
			count++;
		}

		next = strchr (next + 1, '/'); 
		if (next)
			next++;
	}

	if (found) {
		if (ent->node) {
			printf ("Already mounted, with name %s\n", ent->node->filename);
			return;
		}else 
			ent->node = node;
	}

	if (!found) {
		ent = root_entry;
		while(ent->next != 0)
			ent = ent->next;
		vfs_entry *entry = (vfs_entry*)malloc(sizeof(vfs_entry));
		entry->prev = ent;
		entry->node = node;
		entry->next = NULL;
		ent->next = entry;
	}
	
}


