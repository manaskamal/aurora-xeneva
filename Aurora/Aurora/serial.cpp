/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2022, Manas Kamal Choudhury
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * /PROJECT - Aurora's Xeneva v1.0
 * @init.cpp -- Main kernel entry 
 *
 **/


#include <serial.h>
#include <hal.h>
#include <string.h>
#include <stdio.h>
#include <va_list.h>
#include <pmmngr.h>
#include <stdarg.h>
#include <atomic\mutex.h>

#define PORT  0x3f8
static bool _serial_initialized_ = false;

void SerialHandler (size_t v, void* p) {
	printf ("Serial Handler\n");
	AuInterruptEnd(4);
}

void AuInitializeSerial() {
	x64_outportb (PORT + 1, 0x00);
	x64_outportb ((PORT + 3), 0x80);
	x64_outportb ((PORT + 0), 0x03);
	x64_outportb ((PORT + 1), 0x00);
	x64_outportb ((PORT + 3), 0x03);
	x64_outportb ((PORT + 2), 0xC7);
	x64_outportb ((PORT + 4), 0x0B);

	//x64_outportb (PORT + 4, 0x0F);
	//interrupt_set (4,serial_handler, 4);
	_serial_initialized_ = true;
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

/* AuSerialWrite -- Writes characters to serial device
 * @param file -- Pointer to serial file
 * @param buffer -- Pointer to character buffer
 * @param length -- Length of data
 */
void AuSerialWrite (vfs_node_t *file, uint64_t* buffer, uint32_t length) {
	char* format = (char*)buffer;
	_debug_print_ (format);
}

/* AuSerialRead -- Read characters from serial device
 * @param file -- Pointer to serial file
 * @param buffer -- Pointer to character buffer
 * @param length -- Length of data to be read
 */
size_t AuSerialRead (vfs_node_t *file, uint64_t* buffer,uint32_t length){
	return 0;
}

/* AuSerialIoQuery -- I/O Query to serial file */
int AuSerialIoQuery (vfs_node_t* devid, int code, void* arg) {
	return 1;
}


/* AuInitializeSerialFile -- Mounts the serial file
 * to virtual file system
 */
void AuInitializeSerialFile() {
	vfs_node_t *node = (vfs_node_t*)malloc(sizeof(vfs_node_t));
	strcpy (node->filename, "serial");
	node->size = 0;
	node->eof = 0;
	node->pos = 0;
	node->current = 0;
	node->flags = FS_FLAG_GENERAL | FS_FLAG_DEVICE;
	node->status = 0;
	node->open = 0;
	node->read = AuSerialRead;
	node->write = AuSerialWrite;
	node->read_blk = 0;
	node->ioquery = AuSerialIoQuery;
	vfs_mount ("/dev/serial", node, 0);
}

bool is_serial_initialized() {
	return _serial_initialized_;
}