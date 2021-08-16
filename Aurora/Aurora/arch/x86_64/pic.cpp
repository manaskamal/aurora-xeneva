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


void pic_send_command (uint8_t cmd, uint8_t pic_num) {
	
	if (pic_num > 1)
		return;

	uint8_t reg = (pic_num == 1) ? I86_PIC2_REG_COMMAND : I86_PIC1_REG_COMMAND;
	x64_outportb (reg, cmd);
}

void pic_send_data (uint8_t data, uint8_t pic_num) {

	if (pic_num > 1)
		return;

	uint8_t reg = (pic_num == 1) ? I86_PIC2_REG_DATA : I86_PIC1_REG_DATA;
	x64_outportb (reg, data);
}

uint8_t pic_read_data (uint8_t pic_num) {

	if (pic_num > 1)
		return 0;

	uint8_t reg = (pic_num == 1) ? I86_PIC2_REG_DATA : I86_PIC1_REG_DATA;
	return x64_inportb (reg);
}

void pic_interrupt_eoi (unsigned int intno) {

	if (intno > 16)
		return;

	if (intno >= 8)
		pic_send_command(I86_PIC_OCW2_MASK_EOI, 1);

	pic_send_command (I86_PIC_OCW2_MASK_EOI, 0);
}



void initialize_pic ( uint8_t base0, uint8_t base1) {

	uint8_t icw = 0;

	x64_cli ();

	icw = (icw & ~I86_PIC_ICW1_MASK_INIT) | I86_PIC_ICW1_INIT_YES;
	icw = (icw & ~I86_PIC_ICW1_MASK_IC4) | I86_PIC_ICW1_IC4_EXPECT;

	pic_send_command (icw, 0);
	pic_send_command (icw, 1);

	//! send init control word 2
	pic_send_data (base0, 0);
	pic_send_data (base1, 1);

	pic_send_data (0x04, 0);
	pic_send_data (0x02, 1);

	icw = (icw & ~I86_PIC_ICW4_MASK_UPM) | I86_PIC_ICW4_UPM_86MODE;

	pic_send_data (icw, 0);
	pic_send_data (icw, 1);
}