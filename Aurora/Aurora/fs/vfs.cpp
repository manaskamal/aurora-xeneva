/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2022, Manas Kamal Choudhury
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
 *
 **/

#include <fs\vfs.h>
#include <stdio.h>
#include <arch\x86_64\mmngr\kheap.h>
#include <utils\gtree.h>
#include <fs\fat\fat.h>
#include <fs\devfs.h>
#include <serial.h>

vfs_entry *root_dir = NULL;   // for '/' directory

vfs_node_t* openfs (vfs_node_t *node, char* path) {
	if (node) {
		return node->open (node, path);
	}
}

size_t readfs (vfs_node_t *node, vfs_node_t* file, uint64_t* buffer, uint32_t length) {
	if (node) {
		return node->read (file, buffer, length);
	}
	return -1;
}


void writefs (vfs_node_t *node, vfs_node_t* file, uint64_t *buffer, uint32_t length) {
	if (node) {
		node->write (file, buffer, length);
	}
}

size_t readfs_block (vfs_node_t* node, vfs_node_t* file, uint64_t *buffer) {
	if (node) {
		return node->read_blk (file, buffer);
	}
	return -1;
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
 * vfs_unmount -- unmounts a file or directory from 
 * virtual file system 
 * @param path -- path of the directory/file
 */
vfs_node_t* vfs_unmount (char *path) {

	char* next = strchr(path, '/');
	if (next)
		next++;

	char* fs_path = next;

	vfs_entry* ent = root_dir;
	vfs_node_t* entry_found = 0;
	char pathname[16];
	int index = 0;
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
				if (file_->flags & FS_FLAG_DIRECTORY)
					ent = (vfs_entry*)file_->device;
				entry_found = file_;
				index = j;
			}
		}

		next = strchr(next + 1, '/');
		if (next)
			next++;
	}

	if (!entry_found) 
		entry_found = root_dir->node;

	vfs_node_t* ret = (vfs_node_t*)list_remove (ent->childs, index);
	return ret;
}

/*
 * vfs_remove_file -- removes a file/directory 
 * from the virtual file system layer
 * @param path -- file path
 */
vfs_node_t* vfs_remove_file (char* path) {
	return vfs_unmount (path);
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
			_debug_print_ ("[VFS]: Mounting filesystem to root failed, already in use\n");
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
			_debug_print_ ("Recursively calling for -> %s \r\n", path);
			vfs_mount(path,node,ent);
		}
		_debug_print_ ("[vfs]: already mounted -> %s \r\n", path);
		return;
	}

	if (!found) {
		_debug_print_ ("Not found entry -> %s \r\n", path);
		if (entry_found) {
			_debug_print_ ("Mounting path -> %s, creating entry \r\n", path);
			vfs_entry* entryn = vfs_mkentry();
			_debug_print_ ("Entry created -> %x \r\n", entryn);
			vfs_mkdir(path,node,entryn);
		}
		_debug_print_ ("Ent->child -> %x %x nodes-> %d \r\n", ent->childs, node, sizeof(vfs_node_t));
		list_add(ent->childs, node);
		_debug_print_ ("List added %x \r\n", ent->childs);
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
			if (f->flags & FS_FLAG_DIRECTORY)
				type = "Directory";
			else if (f->flags & FS_FLAG_GENERAL)
				type = "File";
			_debug_print_("%s -> %s \r\n",type, f->filename);
		}
		return;
	}
}


