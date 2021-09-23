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

typedef struct _sys_time_ {
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hour;
	uint8_t day;
	uint8_t month;
	uint8_t year;
	uint8_t century;
}sys_time;


extern void initialize_rtc ();
extern uint8_t rtc_get_year ();
extern uint8_t rtc_get_second ();
extern uint8_t rtc_get_day();
extern uint8_t rtc_get_hour();
extern uint8_t rtc_get_minutes ();
extern uint8_t rtc_get_century();
extern uint8_t rtc_get_month ();
#endif