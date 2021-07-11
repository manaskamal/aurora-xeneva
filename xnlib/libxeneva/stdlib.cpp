
#include <stdlib.h>


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