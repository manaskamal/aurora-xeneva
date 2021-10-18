/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  ioquery.cpp -- IOQuery System call
 *
 *  /PROJECT - Aurora's Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ============================================
 */

#include <fs\vfs.h>
#include <stdint.h>
#include <stdio.h>
#include <hal.h>
#include <proc.h>


/**
 * IOQuery System call
 */
void ioquery (int device_id, int code, void* arg) {
	x64_cli();
	vfs_node_t *node = get_current_thread()->fd[device_id];
	vfs_ioquery(node, code, arg);
	return;
}