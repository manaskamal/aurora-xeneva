/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  proc.cpp -- Process
 *
 *  /PROJECT - Aurora {Xeneva}
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * ===============================================
 */

#include <proc.h>
#include <atomic\mutex.h>
#include <fs\fat32.h>


static int user_stack_index = 0;
static mutex_t *process_mutex = create_mutex();
process_t *process_head = NULL;
process_t *process_last = NULL;

//! Adds a process to the process list
void add_process (process_t *proc) {

	proc->next = NULL;
	proc->prev = NULL;

	if (process_head == NULL) {
		process_head = proc;
		process_last = proc;
	} else {
		process_last->next = proc;
		proc->prev = process_last;
		process_last = proc;
	}
}

//! removes a process from the process list
void remove_process (process_t *proc) {
	
	if (process_head == NULL)
		return;

	if (proc == process_head) {
		process_head = process_head->next;
	} else {
		proc->prev->next = proc->next;
	}

	if (proc == process_last) {
		process_last = proc->prev;
	} else {
		proc->next->prev = proc->prev;
	}

	pmmngr_free (proc);
}


//! Finds a process by its thread address
process_t *find_process_by_thread (thread_t *thread) {
	for (process_t *proc = process_head; proc != NULL; proc = proc->next) {
		if (proc->thread_data_pointer == thread) {
			return proc;
		}
	}
}

/* Create stack for User process */
uint64_t *create_user_stack (uint64_t* cr3) {

#define USER_STACK 0x0000700000000000
	uint64_t location = USER_STACK + user_stack_index;
	
	/* 1 mb stack / process */
	for (int i=0; i < 0x100000/4096; i++) {
		map_page_ex(cr3,(uint64_t)pmmngr_alloc(),location + i * 4096);
	}

	user_stack_index += 0x100000;
	return (uint64_t*)(USER_STACK +  user_stack_index);
}



void create_process(const char* filename, char* procname, uint8_t priority) {

	//mutex_lock (process_mutex);
	//!allocate a data-structure for process 
	process_t *process = (process_t*)pmmngr_alloc();

	//!open the process file-binary
	FILE file = open(filename);
	if (file.status == FILE_FLAG_INVALID) {
		printf("Executable image not found\n");
		return;
	}
	//!open the binary file and read it
	unsigned char* buf = (unsigned char*)pmmngr_alloc();   //18*1024
	read_blk(&file,buf);
	
	IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)buf;
	PIMAGE_NT_HEADERS nt = raw_offset<PIMAGE_NT_HEADERS>(dos, dos->e_lfanew);
	//!extract the informations
    load_pe_file(buf,file.size);
	uint64_t _image_base_ = nt->OptionalHeader.ImageBase;
	ientry ent = (ientry)(nt->OptionalHeader.AddressOfEntryPoint + nt->OptionalHeader.ImageBase); //buffer
	//ientry ent = get_entry_point();
	//printf ("size pf address for process -> %s is -> %x\n", procname, dos->e_magic);
	//uint64_t _image_base_ = (uint64_t)get_image_base();
	
	//! create the user stack and address space
	
    uint64_t *cr3 = create_user_address_space();
	uint64_t stack = (uint64_t)create_user_stack(cr3);
	map_page_ex(cr3,(uint64_t)buf,_image_base_);

	//! read rest of the image
	int position = 1;  //we already read 4096 bytes at first
	while(file.eof != 1){
		unsigned char* block = (unsigned char*)pmmngr_alloc();
		read_blk(&file,block);
		map_page_ex(cr3,(uint64_t)block,_image_base_ + position * 4096);
		position++;
	}

	//!allocate current process
	process->name = procname;
	process->entry_point = ent;

	process->cr3 = cr3;
	process->image_base = _image_base_;
	process->stack = stack;
	process->image_size = nt->OptionalHeader.SizeOfImage;
	//! Create and thread and start scheduling when scheduler starts */
	thread_t *t = create_user_thread(process->entry_point,stack,(uint64_t)cr3,procname,priority);
	//! add the process to process manager
	process->thread_data_pointer = t;
    add_process(process);
	//mutex_unlock (process_mutex);

}

//! Kill Process
void kill_process () {
	x64_cli();
	thread_t * remove_thread = get_current_thread();
	process_t *proc = find_process_by_thread (remove_thread);
	uint64_t  init_stack = proc->stack - 0x100000;
	for (int i = 0; i < 0x100000 / 256; i++) {
		unmap_page (init_stack + i * 4096);
	}

	for (int i = 0; i < proc->image_size / 4096; i++) {
		uint64_t virtual_addr = proc->image_base + (i * 4096);
		unmap_page (virtual_addr);
	}

	remove_process (proc);
	task_delete (remove_thread);
}