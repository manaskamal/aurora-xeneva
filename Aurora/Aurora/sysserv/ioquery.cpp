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

#include <vfs.h>
#include <stdint.h>
#include <stdio.h>
#include <hal.h>


/**
 * IOQuery System call
 */
void ioquery (int device_id, int code, void* arg) {
	x64_cli();

	if (device_id < 0)
		return;

	file_system_t *sys_ = vfs_get_file_system(device_id);
	sys_->ioquery (code, arg);
}