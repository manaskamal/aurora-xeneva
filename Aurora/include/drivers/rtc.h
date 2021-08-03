/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  rtc.h -- Real Time Clock driver
 *
 *  /PROJECT - Aurora Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury 
 *
 * ================================================
 */

#ifndef __RTC_H__
#define __RTC_H__

#include <stdint.h>
#include <hal.h>

#define CMOS_ADDR 0x70
#define CMOS_DATA 0x71

extern void initialize_rtc ();
extern uint8_t rtc_get_year ();
#endif