/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  _xeneva.h -- Aurora's Kernel Core system calls
 *
 *  /PROJECT - Aurora's Xeneva v1.0
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *=====================================================
 */

#ifndef __XENEVA_H__
#define __XENEVA_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

	///**
	//  sys_get_used_ram -- returns the amount of used ram in bytes
	//  */
	uint32_t sys_get_used_ram ();

	/**
	  sys_get_free_ram -- returns the amount of free ram in bytes
	  */
	uint32_t sys_get_free_ram ();


    int sys_create_timer (uint32_t interval, uint16_t id);
	
	void sys_destroy_timer (int utimer_id);

	void sys_start_timer (int utimer_id);

	void sys_pause_timer (int utimer_id);


#ifdef __cplusplus
}
#endif
#endif