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
#include <va_list.h>
#include <pmmngr.h>
#include <stdarg.h>

#define PORT  0x3f8
static bool _serial_initialized_ = false;

void SerialHandler (size_t v, void* p) {
	printf ("Serial Handler\n");
	AuInterruptEnd(4);
}

void AuInitializeSerial() {
	x64_outportb (p2v(PORT + 1), 0x00);
	x64_outportb (p2v(PORT + 3), 0x80);
	x64_outportb (p2v(PORT + 0), 0x03);
	x64_outportb (p2v(PORT + 1), 0x00);
	x64_outportb (p2v(PORT + 3), 0x03);
	x64_outportb (p2v(PORT + 2), 0xC7);
	x64_outportb (p2v(PORT + 4), 0x0B);
	

	//x64_outportb (PORT + 4, 0x0F);
	//interrupt_set (4,serial_handler, 4);
	_serial_initialized_ = true;
}

int is_transmit_empty () {
	return x64_inportb (p2v(PORT + 5)) & 0x20;
}

void write_serial (char a) {
	while (is_transmit_empty() == 0);
	x64_outportb (p2v(PORT), a);
}

void debug_serial (char* string) {
	for (int i = 0; i < strlen(string); i++)
		write_serial(string[i]);
}

void _debug_print_ (char* format, ...) {
	_va_list_ args;
	va_start(args, format);

	while (*format)
	{
		if (*format == '%')
		{
			++format;
			if (*format == 'd')
			{
				size_t width = 0;
				if (format[1] == '.')
				{
					for (size_t i = 2; format[i] >= '0' && format[i] <= '9'; ++i)
					{
						width *= 10;
						width += format[i] - '0';
					}
				}
				size_t i = va_arg(args, size_t);
				char buffer[sizeof(size_t) * 8 + 1];
			//	size_t len
				if (i < 0) {
					i = +i;
					sztoa (i,buffer,10);
				}else {
					sztoa(i, buffer, 10);
					size_t len = strlen(buffer);
				}
			/*	while (len++ < width)
					puts("0");*/
				debug_serial(buffer);
			}
			else if (*format == 'c')
			{
				char c = va_arg(args, char);
				//char buffer[sizeof(size_t) * 8 + 1];
				//sztoa(c, buffer, 10);
				//puts(buffer);
				write_serial(c);
			}
			else if (*format == 'x')
			{
				size_t x = va_arg(args, size_t);
				char buffer[sizeof(size_t) * 8 + 1];
				sztoa(x, buffer, 16);
				//puts("0x");
				debug_serial(buffer);
			}
			else if (*format == 's')
			{
				char* x = va_arg(args, char*);
				debug_serial(x);
			}
			else if (*format == 'f')
			{
				double x = va_arg(args, double);
				debug_serial(ftoa(x,2));
			}
			else if (*format == '%')
			{
				debug_serial(".");
			}
			else
			{
				char buf[3];
				buf[0] = '%'; buf[1] = *format; buf[2] = '\0';
				debug_serial(buf);
			}
		}
		else
		{
			char buf[2];
			buf[0] = *format; buf[1] = '\0';
			debug_serial(buf);
		}
		++format;
	}
	va_end(args);
}

bool is_serial_initialized() {
	return _serial_initialized_;
}