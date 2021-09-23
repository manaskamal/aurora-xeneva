///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  systime.cpp -- Timer system call
///!
///!  /PROJECT - Aurora's Xeneva
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!================================================

#include <drivers\rtc.h>
#include <string.h>
#include <arch\x86_64\apic.h>
#include <arch\x86_64\thread.h>




void sys_get_current_time (sys_time *time) {
	x64_cli();
	memset (time, 0, sizeof(sys_time));
	time->seconds = rtc_get_second();
	time->minutes = rtc_get_minutes();
	time->hour = rtc_get_hour();
	time->day = rtc_get_day();
	time->month = rtc_get_month();
	time->year = rtc_get_year();
	time->century = rtc_get_century();
}

uint32_t sys_get_system_tick () {
	x64_cli();
	return sched_get_tick();
}
