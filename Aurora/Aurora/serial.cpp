/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  serial.h -- Serial Port 
 *
 *  /PROJECT - Aurora Xeneva
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * =============================================
 */


#include <serial.h>
#include <hal.h>
#include <string.h>
#include <stdio.h>

#define PORT  0x3f8

void serial_handler (size_t v, void* p) {
	//printf ("Serial Handler\n");
	interrupt_end(4);
}

void initialize_serial() {
	x64_outportb (PORT + 1, 0x00);
	x64_outportb (PORT + 3, 0x80);
	x64_outportb (PORT + 0, 0x03);
	x64_outportb (PORT + 1, 0x00);
	x64_outportb (PORT + 3, 0x03);
	x64_outportb (PORT + 2, 0xC7);
	x64_outportb (PORT + 4, 0x0B);
	x64_outportb (PORT + 4, 0x1E);
	x64_outportb (PORT + 0, 0xAE);

	if (x64_inportb (PORT + 0) != 0xAE) {
		return;
	}

	x64_outportb (PORT + 4, 0x0F);
	interrupt_set (4,serial_handler, 4);
}

int is_transmit_empty () {
	return x64_inportb (PORT + 5) & 0x20;
}

void write_serial (char a) {
	while (is_transmit_empty() == 0);
	x64_outportb (PORT, a);
}

void debug_serial (char* string) {
	for (int i = 0; i < strlen(string); i++)
		write_serial(string[i]);
}