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
 *
 **/

#include <libmngr.h>
#include <fs\vfs.h>
#include <fs\fat\fat.h>
#include <stdio.h>
#include <pe.h>

AuLibEntry_t *libentry_first = NULL;
AuLibEntry_t *libentry_last = NULL;

void AuLibInsert (AuLibEntry_t* new_entry) {
	new_entry->next = NULL;
	new_entry->prev = NULL;

	if (libentry_first == NULL) {
		libentry_last = new_entry;
		libentry_first = new_entry;
	} else {
		libentry_last->next = new_entry;
		new_entry->prev = libentry_last;
	}
	libentry_last = new_entry;
}


void AuLibRemove(AuLibEntry_t* libentry) {

	if (libentry_first == NULL)
		return;

	if (libentry == libentry_first) {
		libentry_first = libentry_first->next;
	} else {
		libentry->prev->next = libentry->next;
	}

	if (libentry == libentry_last) {
		libentry_last = libentry->prev;
	} else {
		libentry->next->prev = libentry->prev;
	}

	free(libentry);
}

AuLibEntry_t *AuGetSysLib (char* path) {
	for (AuLibEntry_t *first = libentry_first; first != NULL; first = first->next) {
		if (strcmp(first->path, path) == 0) 
			return first;
	}

	return NULL;
}


void AuSysLoadLib(char* fname) {
	int blocks_read = 0;
	vfs_node_t *file = fat32_open(NULL, fname);
	if (file == NULL){
		printf ("Failed to load -> %s \n", fname);
		return;
	}

	uint64_t* phys_start = (uint64_t*)AuPmmngrAlloc();
	fat32_read(file, phys_start);
	blocks_read = 1;

	while(file->eof != 1){
		uint64_t *phys = (uint64_t*)AuPmmngrAlloc();
		fat32_read(file, phys);
		blocks_read++;
	}

	AuLibEntry_t *entry = (AuLibEntry_t*)malloc(sizeof(AuLibEntry_t));
	strcpy(entry->path, fname);
	entry->loaded = true;
	entry->phys_start = (uint64_t)phys_start;
	entry->phys_end = (entry->phys_start + blocks_read * 4096);
	entry->phys_blocks_count = blocks_read;
	entry->linked = false;
	AuLibInsert(entry);
}


/*
 * AuSysLibInitialize -- Initialize the Library Manager
 * and loads all system known libraries
 */
void AuSysLibInitialize () {
	libentry_first = NULL;
	libentry_last = NULL;

	AuSysLoadLib("xnacrl.dll");
	AuSysLoadLib("xewid.dll");
	AuSysLoadLib("xnclib.dll");

}

