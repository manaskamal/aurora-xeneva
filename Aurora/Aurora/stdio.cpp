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
#include <va_list.h>

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
				sztoa(i, buffer, 10);
				size_t len = strlen(buffer);
				while (len++ < width)
					puts("0");
				puts(buffer);
			}
			else if (*format == 'c')
			{
				int c = va_arg(args, int);
				char buffer[sizeof(size_t) * 8 + 1];
				sztoa(c, buffer, 10);
				puts(buffer);
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
			/*else if (*format == 'f')
			{
				double x = va_arg(args, double);
				xput_char(ftoa(x,2));
			}*/
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