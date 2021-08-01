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

//! Read I/O Apic register
static uint32_t read_ioapic_register(void* apic_base, const uint8_t offset)
{
	volatile uint32_t* ioregsel = reinterpret_cast<volatile uint32_t*>(apic_base);
	volatile uint32_t* ioregwin = raw_offset<volatile uint32_t*>(apic_base, 0x10);

	*ioregsel = offset;
	return *ioregwin;
}

//! Write I/O Apic register
static void write_ioapic_register(void* apic_base, const uint8_t offset, const uint32_t val)
{
	volatile uint32_t* ioregsel = reinterpret_cast<volatile uint32_t*>(apic_base);
	volatile uint32_t* ioregwin = raw_offset<volatile uint32_t*>(apic_base, 0x10);
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
void ioapic_register_irq(size_t vector, void (*fn)(size_t, void* p),uint8_t irq)
{
	uint32_t reg = IOAPIC_REG_RED_TBL_BASE + irq* 2;
	write_ioapic_register((void*)0xfec00000, reg + 1, read_apic_register(0x02) << 24);
	uint32_t low = read_ioapic_register ((void*)0xfec00000,reg);
	//!unmask the irq
	low &= ~(1<<16);
	//!set to physical delivery mode
	low &= ~(1<<11);
	low &= ~0x700;

	low &= ~0xff;
	low |= vector + 32;
	
	write_ioapic_register((void*)0xfec00000, reg, low);   //vector + 32
    setvect(vector + 32, fn);
}


void ioapic_mask_irq (uint8_t irq, bool value){
	uint32_t reg = IOAPIC_REG_RED_TBL_BASE + irq* 2;
	write_ioapic_register((void*)0xfec00000, reg + 1, read_apic_register(0x02) << 24);
	uint32_t low = read_ioapic_register ((void*)0xfec00000,reg);
	//!unmask the irq
	if (value)
		low |= (1<<16);  //mask
	else
		low &= ~(1<<16); //unmask

	write_ioapic_register((void*)0xfec00000, reg, low);   //vector + 32
}

//! I/O Apic Initialization
void ioapic_init(void* address)
{
	uint32_t ver = read_ioapic_register(address, IOAPIC_REG_VER);
	uint32_t intr_num = (ver >> 16) & 0xFF;
	for(size_t n = 0; n <= 255; ++n)
	{
		uint32_t reg = IOAPIC_REG_RED_TBL_BASE + n * 2;
		write_ioapic_register(address, reg, read_ioapic_register(address, reg) |(1<<16));
	}
}