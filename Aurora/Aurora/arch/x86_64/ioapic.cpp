/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  ioapic.h -- I/O APIC
 *
 *  /PROJECT - Aurora v1.0 {Xeneva v1.0}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *==================================================
 */

#include <arch\x86_64\ioapic.h>
#include <arch\x86_64\mmngr\paging.h>

extern void debug_print(const char *text, ...);

void* io_apic_base;

//! Read I/O Apic register
static uint32_t read_ioapic_register(void* apic_base, const uint8_t offset)
{
	volatile uint32_t* ioregsel = reinterpret_cast<volatile uint32_t*>(io_apic_base);
	volatile uint32_t* ioregwin = raw_offset<volatile uint32_t*>(io_apic_base, 0x10);
	*ioregsel = offset;
	return *ioregwin;
}

//! Write I/O Apic register
static void write_ioapic_register(void* apic_base, const uint8_t offset, const uint32_t val)
{
	volatile uint32_t* ioregsel = reinterpret_cast<volatile uint32_t*>(io_apic_base);
	volatile uint32_t* ioregwin = raw_offset<volatile uint32_t*>(io_apic_base, 0x10);
	*ioregsel = offset;
	*ioregwin = val;
}


/**
 *  Here's the special
 *  our I/O Apic interrupt router to IDT
 *  very very very very special function
 *
 *  @param vector -- vector number for IDT
 *  @param fn     -- handler function
 *  @param irq    -- IRQ number to remap to vector
 *
 */
void ioapic_register_irq(size_t vector, void (*fn)(size_t, void* p),uint8_t irq, bool level)
{
	uint32_t reg = IOAPIC_REG_RED_TBL_BASE + irq* 2;
	write_ioapic_register((void*)io_apic_base, reg + 1, read_apic_register(0x02) << 24);
	uint32_t low = read_ioapic_register ((void*)io_apic_base,reg);
	//!unmask the irq
	low &= ~(1<<16);
	//!set to physical delivery mode
	low |= (0<<15);
	if (level)
		low |= (1<<15);
	else
		low |= (0<<15);
	low |= (0<<13);
	low |= (0<<11);
	low |= vector + 32;
	write_ioapic_register(io_apic_base, reg, low);   //vector + 32
    setvect(vector + 32, fn);
}


void ioapic_redirect (uint8_t irq, uint32_t gsi, uint16_t flags, uint8_t apic) {
	uint32_t ioapic_base = 0xfec00000;
	uint64_t redirection = irq + 32;
	if (flags & 2) {
		redirection |= 1 << 13;
	}


	if (flags & 8) {
		redirection |= 1 << 15;
	}

	redirection |= ((uint64_t)apic) << 56;
	
	uint32_t ioredtbl = (gsi - 0) * 2 + 16;

	write_ioapic_register ((void*)ioapic_base,ioredtbl + 0, (uint32_t)(redirection));
	write_ioapic_register ((void*)ioapic_base,ioredtbl + 1, (uint32_t)(redirection >> 32));
}

void ioapic_mask_irq (uint8_t irq, bool value){
	uint32_t reg = IOAPIC_REG_RED_TBL_BASE + irq* 2;
	write_ioapic_register((void*)io_apic_base, reg + 1, read_apic_register(0x02) << 24);
	uint32_t low = read_ioapic_register ((void*)0xfec00000,reg);
	//!unmask the irq
	if (value)
		low |= (1<<16);  //mask
	else
		low &= ~(1<<16); //unmask

	write_ioapic_register((void*)io_apic_base, reg, low);   //vector + 32
}

//! I/O Apic Initialization
void ioapic_init(void* address)
{
	uint64_t ioapic_phys = (uint64_t)address;
	io_apic_base = (void*)AuMapMMIO(ioapic_phys,2);

	uint32_t ver = read_ioapic_register(io_apic_base, IOAPIC_REG_VER);
	uint32_t intr_num = (ver >> 16) & 0xFF;
	for(size_t n = 0; n <= intr_num; ++n)
	{
		uint32_t reg = IOAPIC_REG_RED_TBL_BASE + n * 2;
		uint32_t val = read_ioapic_register(address, reg);
		write_ioapic_register(io_apic_base, reg, val |(1<<16));
	}

}