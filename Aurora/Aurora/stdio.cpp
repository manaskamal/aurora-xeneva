/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  stdio.h -- standard input output 
 *
 *  /PROJECT - Aurora v1.0 {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 *====================================================
 */

#include <stdio.h>
#include <console.h>
#include <stdint.h>
#include <serial.h>
#include <va_list.h>
#include <string.h>

static char* chars = "0123456789ABCDEF";

char* sztoa(size_t value, char* str, int base)
{
	if (base < 2 || base > 16)
		return nullptr;
	unsigned int i = 0;
	do 
	{
		str[++i] = chars[value%base];
		value /= base;
	} while (value != 0);
	str[0] = '\0';
	for (unsigned int z = 0; z < i; ++z, --i)
	{
		char tmp = str[z];
		str[z] = str[i];
		str[i] = tmp;
	}
	return str;
}

void atow(char* buf, const char* source)
{
	while(*source != 0)*buf++ = *source++;
	*buf = '\0';
}

char integer_buffer[32];
const char* int_to_str (int value) {
	uint8_t size = 0;
	uint64_t size_tester = (uint64_t)value;
	while (size_tester / 10 > 0) {
		size_tester /= 10;
		size++;
	}

	uint8_t index = 0;
	uint64_t new_value = (uint64_t)value;
	while (new_value / 10 > 0) {
		uint8_t remainder = new_value % 10;
		new_value /= 10;
		integer_buffer[size - index] = remainder + 48;
		index++;
	}

	uint8_t remainder = new_value % 10;
	integer_buffer[size - index] = remainder + 48;
	integer_buffer[size + 1] = 0;
	return integer_buffer;
}

char float_to_string_output[32];
char* ftoa(float value, uint8_t decimal_places) {
	char* int_ptr = (char*)int_to_str((int)value);
	char* float_ptr = float_to_string_output;

	if (value < 0) {
		value *= -1;
	}


	while (*int_ptr != 0) {
		*float_ptr = *int_ptr;
		int_ptr++;
		float_ptr++;
	}

	*float_ptr = '.';
	float_ptr++;

	float new_value = value - (int)value;

	for (uint8_t i = 0; i < decimal_places; i++) {
		new_value *= 10;
		*float_ptr = (int)new_value + 48;
		new_value -= (int)new_value;
		float_ptr++;
	}

	*float_ptr = 0;

	return float_to_string_output;
}

void printf(const char* format, ...)
{
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
				puts(buffer);
			}
			else if (*format == 'c')
			{
				char c = va_arg(args, char);
				//char buffer[sizeof(size_t) * 8 + 1];
				//sztoa(c, buffer, 10);
				//puts(buffer);
				puts((char*)c);
			}
			else if (*format == 'x')
			{
				size_t x = va_arg(args, size_t);
				char buffer[sizeof(size_t) * 8 + 1];
				sztoa(x, buffer, 16);
				//puts("0x");
				puts(buffer);
			}
			else if (*format == 's')
			{
				char* x = va_arg(args, char*);
				puts(x);
			}
			else if (*format == 'f')
			{
				double x = va_arg(args, double);
				puts(ftoa(x,2));
			}
			else if (*format == '%')
			{
				puts(".");
			}
			else
			{
				char buf[3];
				buf[0] = '%'; buf[1] = *format; buf[2] = '\0';
				puts(buf);
			}
		}
		else
		{
			char buf[2];
			buf[0] = *format; buf[1] = '\0';
			puts(buf);
		}
		++format;
	}
	va_end(args);
}