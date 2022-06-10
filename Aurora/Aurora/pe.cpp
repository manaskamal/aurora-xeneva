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

#include <arch\x86_64\mmngr\paging.h>
#include <pe.h>
#include <stdio.h>
#include <serial.h>
#include <libmngr.h>

ientry ent;
uint64_t image_base;
//! Loads a pe file and extracts its
//! informations
void load_pe_file (uint64_t* buffer, int size) {

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


void* AuGetProcAddress(void *image, const char* procname){
	
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

/*
 * LinkLibrary -- Links a dll library to its executable
 * @param image -- dll image
 * @param exporter -- executable image
 */
void AuPeLinkLibrary (void* image) {
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
			void* procaddr = AuGetProcAddress((void*)0xFFFFC00000000000, fname);
			*iat = (uint64_t)procaddr;
			++iat;
		}
	}
}




/*
 * LinkLibrary -- Links a dll library to its executable
 * @param image -- executable
 * @param exporter -- dll images
 * @param exporter -- executable image
 */
void AuPeLinkLibraryEx (void* image, void* exporter) {
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
		
		if(func == 0)
			return;
		
		/* Here Check the required dll name, for the base address */
		if (strcmp(func,"xnclib.dll") == 0){
			exporter = (void*)XNCLIB_BASE;
		}else if (strcmp(func,"xnacrl.dll") == 0){
			exporter = (void*)XNACRL_BASE;
		}else if (strcmp(func,"xewid.dll") == 0){
			exporter = (void*)XNWID_BASE;
		}else if (strcmp(func, "ftype.dll") == 0){
			_debug_print_ ("Exporter found -> %s \r\n", func);
			//exporter = (void*)FTYPE_BASE;
		}

		
		PIMAGE_IMPORT_LOOKUP_TABLE_PE32P iat = raw_offset<PIMAGE_IMPORT_LOOKUP_TABLE_PE32P>(image, importdir[n].ThunkTableRva);
	
		while (*iat) {
			PIMAGE_IMPORT_HINT_TABLE hint = raw_offset<PIMAGE_IMPORT_HINT_TABLE>(image, *iat);
			const char* fname = hint->name;
			
			void* procaddr = AuGetProcAddress(exporter, fname);
	
			if (procaddr != 0) {
				uint64_t addr = *iat;
				uint64_t paddr = (uint64_t)procaddr;
				if (addr == paddr) {
					return;
				}

				*iat = (uint64_t)procaddr;
			}
			++iat;
		}
	}
}





