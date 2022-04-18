/*
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  hal.cpp -- Hardware Abstract Layer
 *
 *  /PROJECT - Aurora v1.0 {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 * ==============================================*/

#include <hal.h>
#include <arch\x86_64\pic.h>

#ifdef ARCH_X64
#include <arch\x86_64\ioapic.h>
#endif

void AuHalSetVect (size_t vector, void (*function)(size_t vector, void* param)) {
#ifdef ARCH_X64
	//! initialize x86_64 hal initializer
	setvect (vector,function);
#elif  ARCH_ARM
	//! initialize arm32 hal initializer
	arm_set_vect(vector,function);
#elif  ARCH_ARM64
	//! initialize arm64 hal initializer
	arm64_set_vect(vector,function);
#endif
}


//! Architecture specific hal initializer
void AuHalInitialize () {

	//! Check processor type
#ifdef ARCH_X64
	//! initialize x86_64 hal initializer
	x86_64_gdt_init ();
	x86_64_init_cpu();
#elif  ARCH_ARM
	//! initialize arm32 hal initializer
	hal_arm_init ();
#elif  ARCH_ARM64
	//! initialize arm64 hal initializer
	hal_arm64_init ();
#endif

}


//! Port Functions
//! Architecture specific
uint8_t inportb (uint16_t port) {
#ifdef ARCH_X64
	return x64_inportb (port);
#elif ARCH_ARM
	//return arm32_inportb (port);
#elif ARCH_ARM64
	//return arm64_inportb (port);
#endif
}

//! Architecture specific
uint16_t inportw (uint16_t port) {
#ifdef ARCH_X64
	return x64_inportw (port);
#elif ARCH_ARM
	//return arm32_inportw (port);
#elif ARCH_ARM64
	//return arm64_inportw (port);
#endif

}

//! Architecture specific
uint32_t  inportd (uint16_t port) {
#ifdef ARCH_X64
	return x64_inportd (port);
#elif ARCH_ARM
	//! return arm32_inportd (port);
#elif ARCH_ARM64
	//! return arm64_inportd (port);
#endif

}


//! Architecture specific
void  outportb (uint16_t port, uint8_t data ) {
#ifdef ARCH_X64
	x64_outportb (port,data);
#elif ARCH_ARM
	//!arm32_outportb (port, data);
#elif ARCH_ARM64
	//!arm64_outportb (port, data);
#endif
}


//! Architecture specific
void outportw (uint16_t port, uint16_t data) {
#ifdef ARCH_X64
	x64_outportw (port, data);
#elif  ARCH_ARM
	//! arm32_outportw (port, data);
#elif ARCH_ARM64
	//! arm64_outportw (port, data);
#endif
}


//! Architecture specific
void  outportd (uint16_t port, uint32_t data) {
#ifdef ARCH_X64
	x64_outportd (port, data);
#elif ARCH_ARM
	//! arm32_outportd (port, data);
#elif ARCH_ARM64
	//! arm64_outportw (port, data);
#endif
}

//! Architecture specific
void AuInterruptEnd (uint32_t irq) { 
#ifdef ARCH_X64
#ifdef USE_PIC
	pic_interrupt_eoi(irq);
#endif
#ifdef USE_APIC
	apic_local_eoi ();
#endif
#elif ARCH_ARM
	//! update comming soon..
#elif ARCH_ARM64
	//! update comming soon..
#endif
}

void AuInterruptSet (size_t vector, void (*fn)(size_t, void* p),uint8_t irq){
#ifdef ARCH_X64
#ifdef USE_PIC
	setvect(32 + vector, fn);
	irq_mask(irq,false);
#endif
#ifdef USE_APIC
	ioapic_register_irq(vector,fn,irq);
#endif
#elif  ARCH_ARM
	//! update comming soon..
#elif ARCH_ARM64
	//! update comming soon...
#endif
}
	

void AuIrqMask (uint8_t irq, bool value) {
#ifdef USE_APIC
	ioapic_mask_irq(irq, value);
#elif USE_PIC
	if(value)
		pic_set_mask(irq);
	else
		pic_clear_mask(irq);
#endif
}


