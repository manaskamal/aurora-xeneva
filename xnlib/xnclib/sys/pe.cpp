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
**/

#include <sys\pe.h>
#include <string.h>
#include <sys\_term.h>
#include <sys\_xeneva.h>


/*
 * LinkLibrary -- Links a dll library to its executable
 * @param image -- dll image
 * @param exporter -- executable image
 */
void PeLinkLibrary (void* image, void* exporter) {
	PIMAGE_DOS_HEADER dos_header = (PIMAGE_DOS_HEADER)image;
	PIMAGE_NT_HEADERS nt_headers = raw_offset<PIMAGE_NT_HEADERS>(dos_header, dos_header->e_lfanew);
	if (IMAGE_DATA_DIRECTORY_IMPORT + 1 > nt_headers->OptionalHeader.NumberOfRvaAndSizes)
		return;
	IMAGE_DATA_DIRECTORY& datadir = nt_headers->OptionalHeader.DataDirectory[IMAGE_DATA_DIRECTORY_IMPORT];
	if (datadir.VirtualAddress == 0 || datadir.Size == 0) {
		return;
	}
	PIMAGE_IMPORT_DIRECTORY importdir = raw_offset<PIMAGE_IMPORT_DIRECTORY>(image, datadir.VirtualAddress);
	for (size_t n = 0; importdir[n].ThunkTableRva; ++n) {
		const char* func = raw_offset<const char*>(image, importdir[n].NameRva);
		PIMAGE_IMPORT_LOOKUP_TABLE_PE32P iat = raw_offset<PIMAGE_IMPORT_LOOKUP_TABLE_PE32P>(image, importdir[n].ThunkTableRva);
		while (*iat) {
			PIMAGE_IMPORT_HINT_TABLE hint = raw_offset<PIMAGE_IMPORT_HINT_TABLE>(image, *iat);
			const char* fname = hint->name;
			void* procaddr = GetProcAddress((void*)exporter, fname);
			if (procaddr != NULL)
				*iat = (uint64_t)procaddr;
			++iat;
		}
	}
}


void LinkSharedLibrary () {
	PeLinkLibrary((void*)0x0000000000600000, (void*)0x0000000100000000);
	PeLinkLibrary((void*)0x0000000000600000, (void*)0x0000000100200000);
}