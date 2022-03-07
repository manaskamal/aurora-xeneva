/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2021, Manas Kamal Choudhury
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
 * @fat --FAT file system
 *
 **/

#include <stdint.h>
#include <fs\fat\fat_util.h>
#include <ctype.h>
#include <string.h>


/**
 * fat32_to_dos_file_name -- converts a given filename to MSDOS file name
 * format
 * @param filename -- filename for conversion
 * @param fname -- pointer to the buffer to store the conversion
 * @param fname_length -- manly 11 buffer[0-8] -- filename, buffer[9-11] -- file extension
 */
void fat32_to_dos_file_name (const char* filename, char* fname, unsigned int fname_length)
{
	unsigned int i=0;

	if (fname_length > 11)
		return;

	if (!fname || !filename)
		return;

	memset (fname, ' ', fname_length);

	for (i=0; i < strlen (filename)-1 && i < fname_length; i++)
	{
		if (filename[i] == '.' || i==8)
			break;

		fname[i] = toupper (filename[i]);
	}

	if (filename[i] =='.')
	{
		for (int k=0; k < 3; k++)
		{
			 ++i;
			 if (filename[i])
				 fname[8+k] = filename[i];
		}
	}

	for (i = 0; i < 3; i++)
		fname[8+i] = toupper (fname[8+i]);
}
