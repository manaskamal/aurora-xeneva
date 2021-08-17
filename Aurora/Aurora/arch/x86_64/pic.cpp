/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  pic.h -- Programmable Interrupt Controller
 *
 *  /PROJECT - Aurora Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury 2021
 *
 * ==============================================
 */

#include <arch\x86_64\pic.h>



void pic_interrupt_eoi (unsigned int intno) {

	if (intno > 16)
		return;

	if (intno >= 8)
		x64_outportb (PIC2_COMMAND, PIC_EOI);

	x64_outportb (PIC1_COMMAND, PIC_EOI);
}




void initialize_pic ( uint8_t base0, uint8_t base1) {

	unsigned char a1, a2;
	a1 = x64_inportb(PIC1_DATA);
	a2 = x64_inportb(PIC2_DATA);

	x64_outportb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
	for (int i = 0; i < 100; i++)
		;
	x64_outportb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	for (int i = 0; i < 100; i++)
		;
	x64_outportb(PIC1_DATA, base0);
	for (int i = 0; i < 100; i++)
		;
	x64_outportb(PIC2_DATA, base1);
	for (int i = 0; i < 100; i++)
		;
	x64_outportb(PIC1_DATA, 4);
	for (int i = 0; i < 100; i++)
		;
	x64_outportb(PIC2_DATA, 2);

	for (int i = 0; i < 100; i++)
		;
	
	x64_outportb (PIC1_DATA, ICW4_8086);
	for (int i = 0; i < 100; i++)
		;
	x64_outportb (PIC2_DATA, ICW4_8086);
	for (int i = 0; i < 100; i++)
		;

	x64_outportb (PIC1_DATA, a1);
	x64_outportb (PIC2_DATA, a2);

	unsigned int divisor =  1193181 / 100;
	x64_outportb(0x43, 0x00 | 0x06 | 0x30 | 0x00);
	x64_outportb(0x40, divisor);
	x64_outportb(0x40, divisor >> 8);

}


void pic_set_mask (uint8_t irq) {
	uint16_t port;
	uint8_t value;

	if (irq < 8) {
		port = PIC1_DATA;
	}else {
		port = PIC2_DATA;
		irq -= 8;
	}

	value = x64_inportb(port) | (1 <<irq);

	x64_outportb(port, value);
}

void pic_clear_mask (unsigned char irq) {
	uint16_t port;
	uint8_t value;

	if (irq < 8) {
		port = PIC1_DATA;
	}else {
		port = PIC2_DATA;
		irq -= 8;
	}

	value = x64_inportb(port) & ~(1 << irq);
	x64_outportb(port, value);
}