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
#include <arch\x86_64\mmngr\paging.h>
#include <string.h>
#include <fs\vfs.h>
#include <hal.h>
#include <stdio.h>
#include <arch\x86_64\pic.h>
#include <arch\x86_64\apinit.h>
#include <serial.h>
#include <arch\x86_64\cpu.h>

#define IA32_APIC_BASE_MSR  0x1B
#define IA32_APIC_BASE_MSR_BSP  0x100
#define IA32_APIC_BASE_MSR_X2APIC 0x400
#define IA32_APIC_BASE_MSR_ENABLE 0x800

#define IA32_X2APIC_REGISTER_BASE_MSR  0x800
#define IA32_APIC_SVR_ENABLE  0x100

#define IA32_APIC_LVT_MASK 0x10000


static bool x2apic = false;
static void* apic = nullptr;
bool debug_mode = false;
extern void debug_print(const char *text, ...);

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
	write_apic_register(LAPIC_REGISTER_EOI, 1);
}


//! Checks if X2APIC is supported or not!!
bool x2apic_supported(){

	size_t a, b, c, d;
	x64_cpuid(0x1, &a, &b, &c, &d);
	return false; //(c & (1 << 21)) != 0;
}

static void io_wait(){
	volatile size_t counter = 0;
	for(; counter < 1000; ++counter);
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

static int apic_timer_count = 0;
//! Interrupt Vector Functions for APIC
void  apic_timer_interrupt (size_t p, void* param) {
	x64_cli();
	apic_timer_count++;
	apic_local_eoi();
	x64_sti();
}



//! Initialize our APIC
void initialize_apic (bool bsp) {

	size_t apic_base;
	if (bsp) {
		apic_base = (size_t)0xFEE00000;

		apic_timer_count = 0;


		if (x2apic_supported() ) {
			x2apic = true;
			apic_base |= IA32_APIC_BASE_MSR_X2APIC;
		}else {
			apic = (void*)AuMapMMIO(apic_base,2);
		}

		apic_base |= IA32_APIC_BASE_MSR_ENABLE;
		x64_write_msr (IA32_APIC_BASE_MSR, apic_base);
	} else {
		x64_write_msr(IA32_APIC_BASE_MSR, x64_read_msr(IA32_APIC_BASE_MSR) | IA32_APIC_BASE_MSR_ENABLE | (x2apic ? IA32_APIC_BASE_MSR_X2APIC : 0));
	}

	
	setvect (0xFF, apic_spurious_interrupt);
	write_apic_register (LAPIC_REGISTER_SVR, read_apic_register (LAPIC_REGISTER_SVR) | 
		                                     IA32_APIC_SVR_ENABLE | 0xFF);


	//!Register the time speed
	write_apic_register (LAPIC_REGISTER_TMRDIV,0x3);  // //0x3    //->correct->   0x2

	/*! timer initialized*/
	size_t timer_vector = 0x40;
	setvect (timer_vector, apic_timer_interrupt);

	size_t timer_reg = (1 << 17) | timer_vector;
	write_apic_register (LAPIC_REGISTER_LVT_TIMER, timer_reg);
	io_wait ();
	write_apic_register (LAPIC_REGISTER_TMRINITCNT,500);  //100 , 500, 1000 <- correct
	

	x64_outportb(PIC1_DATA, 0xFF);
	io_wait();
	x64_outportb(PIC2_DATA, 0xFF);

	//! Finally Intialize I/O APIC
	//map_page (ioapic_base,ioapic_base,0);
	if (bsp)
		ioapic_init ((void*)0xfec00000);

}

void AuAPICMoveToHigher() {
	apic = (void*)p2v((size_t)apic);
	printf ("New APIC -> %x\n", apic);
}

void timer_sleep(uint32_t ms) {
	uint32_t tick = ms + apic_timer_count;
	while (tick > apic_timer_count)
		;
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


bool ap_started = false;


/*
 * Initialize other Application Processors
 * @param num_cpu -- total number of cpu
 */
void AuInitializeCpu(uint8_t num_cpu) {
	if (num_cpu == 0)
		return;

	//! fixed address
	uint64_t *apdata = (uint64_t*)0xA000;
	uint64_t ap_init_address = (uint64_t)AuApInit;
	uint64_t ap_aligned_address = (uint64_t)apdata;

	uint64_t *pml4 = (uint64_t*)AuGetRootPageTable();

	

	for (int i = 1; i <= num_cpu; i++) {
		if (i == 8)
			break;
		ap_started = false;

		void *stack_address = AuPmmngrAlloc();
		*(uint64_t*)(ap_aligned_address + 8) = (uint64_t)pml4;
		*(uint64_t*)(ap_aligned_address + 16) = (uint64_t)stack_address;
		*(uint64_t*)(ap_aligned_address + 24) = ap_init_address;
		*(uint64_t*)(ap_aligned_address + 32) = (uint64_t)p2v((size_t)AuPmmngrAlloc());
		void* cpu_struc = (void*)p2v((uint64_t)AuPmmngrAlloc());
		cpu_t *cpu = (cpu_t*)cpu_struc;
		cpu->cpu_id = i;
		cpu->au_current_thread = 0;
		cpu->kernel_tss = 0;
		*(uint64_t*)(ap_aligned_address + 40) = (uint64_t)cpu_struc;
		
		

		write_apic_register(LAPIC_REGISTER_ICR, icr_dest(i) | 0x4500);
		while (icr_busy());


		size_t startup_ipi = icr_dest(i) | 0x4600 | ((size_t)apdata >> 12);
		write_apic_register(LAPIC_REGISTER_ICR, startup_ipi);
		while (icr_busy());
		for (int i = 0; i < 10000000; i++)
			;
		write_apic_register(LAPIC_REGISTER_ICR, startup_ipi);
		while (icr_busy());
		
		for (int i = 0; i < 10000000; i++)
			;
	
		do {
			x64_pause();
		} while (!ap_started);
	}

}

/* AuAPStarted -- inform the BSP that ap has fully
 * initialized
 */
void AuAPStarted () {
	ap_started = true;
}

void APICDebug (bool debug){
	debug_mode = debug;
}
