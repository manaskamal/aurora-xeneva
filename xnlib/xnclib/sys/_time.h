///!
///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  _time.h -- System time events
///!
///!  //PROJECT - Aurora's Xeneva
///!  //AUTHOR  - Manas Kamal Choudhury
///!
///!=================================================

#ifndef __TIME_H__
#define __TIME_H__

#include <stdint.h>
#include <sys\_xeneva.h>

typedef struct _sys_time_ {
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hour;
	uint8_t day;
	uint8_t month;
	uint8_t year;
	uint8_t century;
}sys_time;

#ifdef __cplusplus
extern "C" {
#endif
//! System get current time
//! @param time - pointer to memory location where time will be written
XE_EXPORT void sys_get_current_time (sys_time *time);
XE_EXPORT uint32_t sys_get_system_tick();

#ifdef __cplusplus
}
#endif
#endif