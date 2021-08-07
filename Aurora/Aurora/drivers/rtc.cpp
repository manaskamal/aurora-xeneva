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

#include <drivers\rtc.h>
#include <stdio.h>

static bool bcd;
uint8_t century;
uint8_t year;
uint8_t month;
uint8_t day;
uint8_t hour;
uint8_t minute;
uint8_t second;
/*
 * Get the value of a specific rtc register
 * */
uint8_t get_rtc_register(int reg_num) {
    x64_outportb(CMOS_ADDR, reg_num);
    return x64_inportb(CMOS_DATA);
}

/*
 * Set the value of a specific rtc register
 * */
void set_rtc_register(uint16_t reg_num, uint8_t val) {
    x64_outportb(CMOS_ADDR, reg_num);
    x64_outportb(CMOS_DATA, val);
}


/*
 * Check if rtc is updating time currently
 * */
int is_updating_rtc() {
	x64_outportb(CMOS_ADDR, 0x0A);
    uint32_t status = x64_inportb(CMOS_DATA);
    return (status & 0x80);
}


/*
 * Read current date and time from rtc, store in global var current_datetime
 * */
void rtc_read_datetime() {
    // Wait until rtc is not updating
    while(is_updating_rtc());

    second = get_rtc_register(0x00);
    minute = get_rtc_register(0x02);
    hour = get_rtc_register(0x04);
    day = get_rtc_register(0x07);
    month = get_rtc_register(0x08);
    year = get_rtc_register(0x09);

    uint8_t registerB = get_rtc_register(0x0B);

    // Convert BCD to binary values if necessary
    if (!(registerB & 0x04)) {
        second = (second & 0x0F) + ((second / 16) * 10);
        minute = (minute & 0x0F) + ((minute / 16) * 10);
        hour = ( (hour & 0x0F) + (((hour & 0x70) / 16) * 10) ) | (hour & 0x80);
        day = (day & 0x0F) + ((day / 16) * 10);
        month = (month & 0x0F) + ((month / 16) * 10);
        year = (year & 0x0F) + ((year / 16) * 10);
    }
}

//! RTC clock interrupt handler
//! it updates current time from RTC clock
void rtc_clock_update(size_t s, void* p) {
	bool ready = get_rtc_register(0x0C) & 0x10;
	if (ready) {
		rtc_read_datetime();
	}
	//!send a EOI to apic
	apic_local_eoi();
}

void initialize_rtc () {

	unsigned char status = get_rtc_register (0x0B);
	status |= 0x02;
	status |= 0x10;
	status &= ~0x20;
	status &= ~0x40;
	bcd = !(status & 0x04);

	//! Write status to rtc
	x64_outportb (0x70, 0x0B);
	x64_outportb (0x71, status);

	//! Read status from RTC
	get_rtc_register (0x0C);

	//!register interrupt
	interrupt_set (8,rtc_clock_update, 8);
}


uint8_t rtc_get_year () {
	return year;
}