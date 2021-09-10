/**
 *
 *   Copyright (C) Manas Kamal Choudhury 2021
 *
 *   image.cpp -- Image Loader basically it loads Microsofts PE Executables
 *
 *   /PROJECT - Xeneva v1.0
 *   /AUTHOR  - Manas Kamal Choudhury 2021
 *
 *=============================================================================
 */

#include <arch\x86_64\mmngr\vmmngr.h>
#include <pe.h>
#include <stdio.h>


ientry ent;
uint64_t image_base;
//! Loads a pe file and extracts its
//! informations
void load_pe_file (unsigned char* buffer, int size) {

	IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)buffer;
	PIMAGE_NT_HEADERS nt = raw_offset<PIMAGE_NT_HEADERS>(dos, dos->e_lfanew);

    image_base = nt->OptionalHeader.ImageBase;
	ent = (ientry)(nt->OptionalHeader.AddressOfEntryPoint + nt->OptionalHeader.ImageBase); //buffer
	//! For now Xeneva only loads binary that are aligned in 512, 1024 & 4096 byte
	//! aligned. Simply we call its entry address that are expected to be aligned in
	//! 512, 1024 and 4096 bytes

	//! copy the image to its desired virtual address
	//memcpy ((void*)nt->OptionalHeader.ImageBase,buffer, size);

	//! set the entry point
	//set_entry_point (nt);
}

ientry get_entry_point () {
	return ent;
}


uint64_t get_image_base() {
	return image_base;
}


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





