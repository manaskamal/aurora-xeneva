/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  _xeneva.cpp -- System Functions
 *
 *  /PROJECT - Aurora's Xeneva v1.0
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 */

#include <sys\_xeneva.h>
#include <sys\pe.h>
#include <string.h>


void* GetProcAddress(void *image, const char* procname){
	
	PIMAGE_DOS_HEADER dos_header  = (PIMAGE_DOS_HEADER)image;
	PIMAGE_NT_HEADERS ntHeaders = raw_offset<PIMAGE_NT_HEADERS>(dos_header, dos_header->e_lfanew); 
	if (IMAGE_DATA_DIRECTORY_EXPORT + 1 > ntHeaders->OptionalHeader.NumberOfRvaAndSizes)
		return NULL;
	IMAGE_DATA_DIRECTORY& datadir = ntHeaders->OptionalHeader.DataDirectory[IMAGE_DATA_DIRECTORY_EXPORT];
	if (datadir.VirtualAddress == 0 || datadir.Size == 0)
		return NULL;
	PIMAGE_EXPORT_DIRECTORY exportdir = raw_offset<PIMAGE_EXPORT_DIRECTORY>(image, datadir.VirtualAddress);
	uint32_t* FuntionNameAddressArray = raw_offset<uint32_t*>(image,exportdir->AddressOfNames);
	uint16_t* FunctionOrdinalAddressArray = raw_offset<uint16_t*>(image,exportdir->AddressOfNameOrdinal);
	uint32_t* FunctionAddressArray = raw_offset<uint32_t*>(image,exportdir->AddressOfFunctions);

	for (int i = 0; i < exportdir->NumberOfNames; i++ ) {

	    char* function_name = raw_offset<char*>(image,FuntionNameAddressArray [i]);
		if (strcmp (function_name, procname) == 0) {
			uint16_t ordinal = FunctionOrdinalAddressArray[i];
			uint32_t FunctionAddress = FunctionAddressArray [ordinal];
			return raw_offset<void*>(image,FunctionAddress);
		}
	}

	return nullptr;
}