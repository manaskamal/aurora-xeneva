/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2021, Manas Kamal Choudhury
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 **/

#include <drivers\rtc.h>
#include <stdio.h>
#include <ipc\message.h>
#include <arch\x86_64\thread.h>
#include <ipc\pri_loop.h>

//! send this message to task 4
#define CLOCK_MESSAGE     10 

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
uint8_t AuGetRTCRegister(int reg_num) {
    x64_outportb(CMOS_ADDR, reg_num);
    return x64_inportb(CMOS_DATA);
}

/*
 * Set the value of a specific rtc register
 * */
void AuSetRTCRegister(uint16_t reg_num, uint8_t val) {
    x64_outportb(CMOS_ADDR, reg_num);
    x64_outportb(CMOS_DATA, val);
}


/*
 * Check if rtc is updating time currently
 * */
int AuIsUpdatingRTC() {
	x64_outportb(CMOS_ADDR, 0x0A);
    uint32_t status = x64_inportb(CMOS_DATA);
    return (status & 0x80);
}


/*
 * Read current date and time from rtc, store in global var current_datetime
 * */
void AuRTCReadDateTime() {
    // Wait until rtc is not updating
	while(AuIsUpdatingRTC());

	second = AuGetRTCRegister(0x00);
    minute = AuGetRTCRegister(0x02);
    hour = AuGetRTCRegister(0x04);
    day = AuGetRTCRegister(0x07);
    month = AuGetRTCRegister(0x08);
    year = AuGetRTCRegister(0x09);

    uint8_t registerB = AuGetRTCRegister(0x0B);

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
void AuRTCClockUpdate(size_t s, void* p) {
	x64_cli ();

	bool ready = AuGetRTCRegister(0x0C) & 0x10;
	if (ready) {
		AuRTCReadDateTime();
	}

	
	//pri_event_t msg;
	//msg.type = CLOCK_MESSAGE;
	//msg.dword = second;
	//msg.dword2 = minute;
	//msg.dword3 = hour;
	//msg.dword5 = day;
	//msg.dword6 = month;
	//msg.dword7 = year;
	//msg.to_id = 3; //the dock bar

	//pri_put_message(&msg);
	//!send a EOI to apic
	AuInterruptEnd(8);
	x64_sti();
}

/*
 * AuInitializeRTC -- Initialize Real time clock
 */
void AuInitializeRTC () {

	century = year = month = day = 0;
    hour = minute = second = 0;

	unsigned char status = AuGetRTCRegister(0x0B);
	status |= 0x02;
	status |= 0x10;
	status &= ~0x20;
	status &= ~0x40;
	bcd = !(status & 0x04);

	//! Write status to rtc
	x64_outportb (0x70, 0x0B);
	x64_outportb (0x71, status);

	//! Read status from RTC
	AuGetRTCRegister(0x0C);

	AuRTCReadDateTime();

	//!register interrupt
	AuInterruptSet(8,AuRTCClockUpdate, 8, false);

#ifdef USE_PIC
	AuIrqMask(8,false);
#endif
}


uint8_t AuGetYear () {
	return year;
}

uint8_t AuGetCentury() {
	return century;
}

uint8_t AuGetMinutes() {
	return minute;
}

uint8_t AuGetSecond() {
	return second;
}

uint8_t AuGetDay() {
	return day;
}

uint8_t AuGetHour () {
	return hour;
}

uint8_t AuGetMonth() {
	return month;
}

