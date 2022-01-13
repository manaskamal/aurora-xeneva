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
	strcpy(node->filename, "dev");
	node->size = 0;
	node->eof = 0;
	node->pos = 0;
	node->current = 0;
	node->flags = FS_FLAG_DIRECTORY;
	node->status = 0;
	node->open = 0;
	node->read = 0;
	node->write = 0;
	node->read_blk = 0;
	node->ioquery = 0;
	vfs_mount ("/dev", node);
}
