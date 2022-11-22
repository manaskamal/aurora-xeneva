///! 
///!   Copyright (C) Manas Kamal Choudhury 2021
///!
///!   devfs -- Device File system
///!
///!   /PROJECT - Aurora's Xeneva
///!   /AUTHOR  - Manas Kamal Choudhury 
///!
///!=================================================

#include <fs\devfs.h>
#include <fs\vfs.h>
#include <arch\x86_64\mmngr\kheap.h>


void devfs_mount () {
	vfs_node_t *node = (vfs_node_t*)malloc(sizeof(vfs_node_t));
	memset(node, 0, sizeof(vfs_node_t));
	strcpy(node->filename, "dev");
	node->flags |= FS_FLAG_DIRECTORY;

	vfs_entry *ent = vfs_mkentry();
	vfs_mkdir("/dev", node, ent);
}
