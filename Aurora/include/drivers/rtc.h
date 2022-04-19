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
#include <aurora.h>

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


extern void AuInitializeRTC ();
AU_EXTERN AU_EXPORT uint8_t AuGetYear();
AU_EXTERN AU_EXPORT uint8_t AuGetSecond ();
AU_EXTERN AU_EXPORT uint8_t AuGetDay();
AU_EXTERN AU_EXPORT uint8_t AuGetHour();
AU_EXTERN AU_EXPORT uint8_t AuGetMinutes();
AU_EXTERN AU_EXPORT uint8_t AuGetCentury();
AU_EXTERN AU_EXPORT uint8_t AuGetMonth();
#endif