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

	mutex_lock (process_mutex);
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
	
	//!extract the informations
    load_pe_file(buf,file.size);
	ientry ent = get_entry_point();
	uint64_t _image_base_ = (uint64_t)get_image_base();
	
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

	//! Create and thread and start scheduling when scheduler starts */
	thread_t *t = create_user_thread(process->entry_point,stack,(uint64_t)cr3,procname,priority);
	//! add the process to process manager
	process->thread_data_pointer = t;
   // process_manager_add_process(process);
	mutex_unlock (process_mutex);

}

void kill_process () {

}