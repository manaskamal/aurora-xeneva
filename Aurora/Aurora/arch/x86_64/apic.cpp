/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  apic.h -- Advanced programmable interrupt controller
 *
 *  /PROJECT - Aurora v1.0
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *============================================================
 */

#include <arch\x86_64\apic.h>
#include <arch\x86_64\ioapic.h>
#include <arch\x86_64\mmngr\vmmngr.h>
#include <string.h>
#include <fs\vfs.h>
#include <hal.h>
#include <stdio.h>

#define IA32_APIC_BASE_MSR  0x1B
#define IA32_APIC_BASE_MSR_BSP  0x100
#define IA32_APIC_BASE_MSR_X2APIC 0x400
#define IA32_APIC_BASE_MSR_ENABLE 0x800

#define IA32_X2APIC_REGISTER_BASE_MSR  0x800
#define IA32_APIC_SVR_ENABLE  0x100

#define IA32_APIC_LVT_MASK 0x10000


static bool x2apic = false;
static void* apic = nullptr;

//! Reads APIC register
uint64_t read_apic_register(uint16_t reg){

	if (x2apic){
		size_t msr = IA32_X2APIC_REGISTER_BASE_MSR + reg;
		return x64_read_msr(msr);
	} else{

		if (reg == LAPIC_REGISTER_ICR){
			volatile uint32_t* reg_addr = raw_offset<volatile uint32_t*>(apic, reg << 4);
			volatile uint32_t* reg_next_addr = raw_offset<volatile uint32_t*>(apic, (reg+1) << 4);
			return *reg_addr | ((uint64_t)*reg_next_addr << 32);
		}
		volatile uint32_t* reg_addr = raw_offset<volatile uint32_t*>(apic, reg << 4);
		return *reg_addr;
	}
}


//! Writs APIC Register
void write_apic_register(uint16_t reg, uint64_t value){

	if (x2apic){

		size_t msr = IA32_X2APIC_REGISTER_BASE_MSR + reg;
		x64_write_msr(msr, value);
	} else {

		if (reg == LAPIC_REGISTER_ICR){

			volatile uint32_t* reg_addr = raw_offset<volatile uint32_t*>(apic, reg << 4);
			volatile uint32_t* reg_next_addr = raw_offset<volatile uint32_t*>(apic, (reg + 1) << 4);
			uint32_t low_part = value & UINT32_MAX;
			uint32_t high_part = (value >> 32);
			*reg_next_addr = high_part;
			x64_mfence();
			*reg_addr = low_part;
		}
		volatile uint32_t* reg_addr = raw_offset<volatile uint32_t*>(apic, reg << 4);
		*reg_addr = value;
	}
}


//! Sends EOI to APIC
extern void apic_local_eoi(){

	write_apic_register(LAPIC_REGISTER_EOI, 0);
}


//! Checks if X2APIC is supported or not!!
bool x2apic_supported(){

	size_t a, b, c, d;
	x64_cpuid(0x1, &a, &b, &c, &d);
	return (c & (1 << 21)) != 0;
}

static void io_wait(){
	volatile size_t counter = 0;
	for(; counter < 1000; ++counter);
}


//! Interrupt Vector Functions for APIC
void  apic_timer_interrupt (size_t p, void* param) {
	apic_local_eoi();
}


void apic_spurious_interrupt (size_t p, void* param) {
}



#define PIC1  0x20
#define PIC2  0xA0
#define PIC1_COMMAND   PIC1
#define PIC1_DATA      (PIC1+1)
#define PIC2_COMMAND   PIC2
#define PIC2_DATA      (PIC2+1)

#define ICW1_ICW4   0x01
#define ICW1_SINGLE  0x02
#define ICW1_INTERVAL4 0x04
#define ICW1_LEVEL     0x08
#define ICW1_INIT      0x10

#define ICW4_8086  0x01
#define ICW4_AUTO  0x02
#define ICW4_BUF_SLAVE  0x08
#define ICW4_BUF_MASTER 0x0C
#define ICW4_SFNM  0x10
static void disable_pic()
{
	static const int offset1 = 0x20;
	static const int offset2 = 0x28;
	
	x64_outportb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	x64_outportb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	x64_outportb(PIC1_DATA, offset1);
	io_wait();
	x64_outportb(PIC2_DATA, offset2);
	io_wait();
	x64_outportb(PIC1_DATA, 4);
	io_wait();
	x64_outportb(PIC2_DATA, 2);
	io_wait();

	x64_outportb(PIC1_DATA, ICW4_8086);
	io_wait();
	x64_outportb(PIC2_DATA, ICW4_8086);
	io_wait();

	x64_outportb(PIC1_DATA, 0xFF);
	io_wait();
	x64_outportb(PIC2_DATA, 0xFF);
	//! handle spurious interrupt
	setvect(offset1 + 7, apic_spurious_interrupt);
	setvect(offset2 + 7, apic_spurious_interrupt);
}

//! Initialize our APIC
void initialize_apic () {

	//! Clear interrupts
	disable_pic();

	size_t apic_base;
	apic_base = (size_t)0xFEE00000;

	//map_page (0xFEE00000, 0xFEE00000,0);

	apic = (void*)apic_base;

	if (x2apic_supported() ) {
		x2apic = true;
		apic_base |= IA32_APIC_BASE_MSR_X2APIC;
	}

	apic_base |= IA32_APIC_BASE_MSR_ENABLE;
	x64_write_msr (IA32_APIC_BASE_MSR, apic_base);
	setvect (0xFF, &apic_spurious_interrupt);
	write_apic_register (LAPIC_REGISTER_SVR, read_apic_register (LAPIC_REGISTER_SVR) | 
		                                     IA32_APIC_SVR_ENABLE | 0xFF);

	for (unsigned n = 0; n < LAPIC_REGISTER_LVT_ERROR - LAPIC_REGISTER_LVT_TIMER; ++n) {
		write_apic_register (LAPIC_REGISTER_LVT_TIMER + n, read_apic_register (LAPIC_REGISTER_LVT_TIMER + n) | IA32_APIC_LVT_MASK);
	}

	//!Register the time speed
	write_apic_register (LAPIC_REGISTER_TMRDIV, 0xa);

	/*! timer initialized*/
	size_t timer_vector = 0x40;
	setvect (timer_vector, apic_timer_interrupt);

	size_t timer_reg = (1 << 17) | timer_vector;
	write_apic_register (LAPIC_REGISTER_LVT_TIMER, timer_reg);
	io_wait ();
	write_apic_register (LAPIC_REGISTER_TMRINITCNT, 0x1000);


	//! Finally Intialize I/O APIC
	size_t ioapic_base = (size_t)0xFEC00000;
	//map_page (ioapic_base,ioapic_base,0);
	ioapic_init (&ioapic_base);

}


uint64_t icr_dest (uint32_t processor ) {
	if (x2apic)
		return ((uint64_t)processor << 32);
	else
		return ((uint64_t)processor << 56);
}

bool icr_busy () {
	return (read_apic_register (LAPIC_REGISTER_ICR) & (1 << 12)) != 0;
}



void initialize_cpu (uint32_t processor) {

	uint64_t* address = (uint64_t*)pmmngr_alloc();
	void* ap_data = get_ap_address();
	memcpy (address, ap_data, 70);

	write_apic_register (LAPIC_REGISTER_ICR, icr_dest(processor) | 0x4500);
	while (icr_busy());

	//!startup ipi
	size_t startup_ipi = icr_dest (processor) | 0x4600 | ((size_t)address >> 12);
	write_apic_register (LAPIC_REGISTER_ICR, startup_ipi);
	while (icr_busy());
	for (int i = 0; i < 100; i++)
		;

}
