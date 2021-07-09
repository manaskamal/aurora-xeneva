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



//! Initialize our APIC
void initialize_apic () {

	//! Clear interrupts
	x64_cli ();


	size_t apic_base;
	apic_base = (size_t)0xFEE00000;

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

	//! timer initialized
	size_t timer_vector = 0x40;
	setvect (timer_vector, apic_timer_interrupt);

	size_t timer_reg = (1 << 17) | timer_vector;
	write_apic_register (LAPIC_REGISTER_LVT_TIMER, timer_reg);
	io_wait ();
	write_apic_register (LAPIC_REGISTER_TMRINITCNT, 0x1000);


	//! Finally Intialize I/O APIC
	size_t ioapic_base = (size_t)0xFEC00000;

	ioapic_init (&ioapic_base);

	x64_sti();
}
