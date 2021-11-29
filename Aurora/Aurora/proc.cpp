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
#include <_null.h>


static int user_stack_index = 0;
static int user_stack_index_2 = 0;
static mutex_t *process_mutex = create_mutex();
static mutex_t *kill_mutex = create_mutex();
static mutex_t *add_mutex = create_mutex();
process_t *process_head = NULL;
process_t *process_last = NULL;
static int pid = 0;

//! Adds a process to the process list
void add_process (process_t *proc) {
	mutex_lock (add_mutex);
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
	pid++;
	mutex_unlock (add_mutex);
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
	pid--;
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

//! Finds a process by its pid
process_t *find_process_by_id (uint32_t pid) {
	for (process_t *proc = process_head; proc != NULL; proc = proc->next) {
		if (proc->pid_t == pid) {
			return proc;
		}
	}
	return NULL;
}
/* Create stack for User process */
uint64_t *create_user_stack (uint64_t* cr3) {
#define USER_STACK  0x0000700000000000 
	
	/*uint64_t* old_cr3 = (uint64_t*)x64_read_cr3();
	x64_write_cr3 ((size_t)cr3);*/
	uint64_t location = USER_STACK;
	
	/* 1 mb stack / process */
	for (int i=0; i < (2*1024*1024)/4096; i++) {
		uint64_t *block = (uint64_t*)pmmngr_alloc();
		memset (block, 0, 4096);
		map_page_ex(cr3, (uint64_t)block,location + i * 4096, PAGING_USER);
	}
 
	//x64_write_cr3((size_t)old_cr3);
	
	return (uint64_t*)(USER_STACK + (2*1024*1024));
}

/*
 * Create incremental stack : Creates stack in same address space
 */
uint64_t* create_inc_stack (uint64_t* cr3) {
#define INC_STACK 0x0000700000000000 
	uint64_t location = INC_STACK ; //+ user_stack_index;

	for (int i = 0; i < (2*1024*1024) / 4096; i++) {
		void* p = pmmngr_alloc();
		memset(p, 0, 4096);
		map_page_ex(cr3,(uint64_t)p, location + i * 4096, PAGING_USER);
	}

	//user_stack_index += 0x100000;
	return (uint64_t*)(INC_STACK + (2*1024*1024));
}

void allocate_fd (thread_t *t) {
	vfs_node_t * stdin = vfs_finddir("/dev/stdin");
	t->fd[t->fd_current] = stdin;
	t->fd_current++;
	vfs_node_t* stdout = vfs_finddir("/dev/stdout");
	t->fd[t->fd_current] = stdout;
	t->fd_current++;
	vfs_node_t* stderr = vfs_finddir("/dev/stderr");
	t->fd[t->fd_current] = stderr;
	t->fd_current++;

}

void create_process(const char* filename, char* procname) {
	
	//printf ("Creating processs -> %s\n", filename);
	//mutex_lock (process_mutex);
	//!allocate a data-structure for process 
	process_t *process = (process_t*)pmmngr_alloc();
	process->pid_t = pid;


	//!open the process file-binary
	char *fname = (char*)filename;
    vfs_node_t *n = vfs_finddir (fname);
	vfs_node_t file = openfs(n, fname);

	if (file.status == FS_FLAG_INVALID) {
		printf("Executable image not found\n");
		return;
	}
	//!open the binary file and read it
	unsigned char* buf = (unsigned char*)pmmngr_alloc();   //18*1024
	readfs_block(n,&file,buf);

	IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)buf;
	PIMAGE_NT_HEADERS nt = raw_offset<PIMAGE_NT_HEADERS>(dos, dos->e_lfanew);

	//!extract the informations
    load_pe_file(buf,file.size);
	uint64_t _image_base_ = nt->OptionalHeader.ImageBase;
	ientry ent = (ientry)(nt->OptionalHeader.AddressOfEntryPoint + nt->OptionalHeader.ImageBase); //buffer
	
	//! create the user stack and address space
    uint64_t *cr3 = create_user_address_space();	
	uint64_t stack = (uint64_t)create_user_stack(cr3);

	map_page_ex(cr3,(uint64_t)buf,_image_base_, PAGING_USER);
	////! read rest of the image
	int position = 1;  //we already read 4096 bytes at first

	while (file.eof != 1){
		unsigned char* block = (unsigned char*)pmmngr_alloc();
		//read_blk(&file,block,file.id);
		readfs_block (n, &file, block);
		//fat32_read (&file,block);
		map_page_ex(cr3,(uint64_t)block,_image_base_ + position * 4096, PAGING_USER);
		position++;
	}

	uint64_t pos = 0x0000080000000000;   //0x0000080000000000;
	for (int i = 0; i < 0xB01000 / 4096; i++) {
		void* p = pmmngr_alloc();
		memset (p, 0, 4096);
		map_page_ex(cr3,(uint64_t)p, pos + i * 4096, PAGING_USER);
	}
	//!allocate current process
	process->name = procname;
	process->entry_point = ent;

	process->cr3 = cr3;
	process->image_base = _image_base_;
	process->stack = stack;
	process->image_size = nt->OptionalHeader.SizeOfImage;
	process->parent = NULL;
	process->user_heap_start = (void*)0x0000080000000000;
	process->heap_size = 0xB00000;
	//! Create and thread and start scheduling when scheduler starts */
	thread_t *t = create_user_thread(process->entry_point,stack,(uint64_t)cr3,procname,0);
	printf ("stack -> %x\n",stack);
	//allocate_fd(t);
	//! add the process to process manager
	process->thread_data_pointer = t;
    add_process(process);
	//mutex_unlock (process_mutex);
}

//! Kill Process
void kill_process () {
	x64_cli();
	mutex_lock (kill_mutex);
	thread_t * remove_thread = get_current_thread();
	process_t *proc = find_process_by_thread (remove_thread);
	uint64_t  init_stack = proc->stack - 0x100000;

	//!unmap the runtime stack
	for (int i = 0; i < 0x100000 / 4096; i++) {
		unmap_page (init_stack + i * 4096);
	}

	//!unmap the binary image
	for (int i = 0; i < proc->image_size / 4096; i++) {
		uint64_t virtual_addr = proc->image_base + (i * 4096);
		unmap_page (virtual_addr);
	}

	remove_process (proc);
	task_delete (remove_thread);
	mutex_unlock (kill_mutex);
}

//! Kill Process
void kill_process_by_id (uint16_t id) {
	x64_cli();
	mutex_lock (kill_mutex);
	bool was_blocked = false;
	thread_t * remove_thread = thread_iterate_ready_list(id);
	if (remove_thread == NULL) {
		remove_thread = (thread_t*)thread_iterate_block_list(id);
		was_blocked = true;
	}
	process_t *proc = find_process_by_thread (remove_thread);
	
	uint64_t  init_stack = proc->stack - 0x100000;

	//!unmap the runtime stack
	for (int i = 0; i < 0x100000 / 4096; i++) {
		unmap_page_ex ((uint64_t*)remove_thread->cr3,init_stack + i * 4096, true);
	}

	//!unmap the binary image
	for (int i = 0; i < proc->image_size / 4096; i++) {
		uint64_t virtual_addr = proc->image_base + (i * 4096);
		unmap_page_ex ((uint64_t*)remove_thread->cr3, virtual_addr, true);
	}

	task_delete (remove_thread);
	remove_process (proc);
	mutex_unlock (kill_mutex);
}


uint32_t fork () {
	process_t *child_process = (process_t*)pmmngr_alloc();
	
	thread_t * p_thread = get_current_thread();
	process_t *parent = find_process_by_thread (p_thread);

	uint64_t *child_cr3 = (uint64_t*)pmmngr_alloc(); //create_user_address_space();
	uint64_t *parent_cr3 = parent->cr3;

	for (int i = 0; i < 512; i++)
		child_cr3[i] = parent_cr3[i];

	memcpy (child_process, parent,sizeof(process_t));
	child_process->pid_t = pid;
	child_process->cr3 = child_cr3; //parent->cr3;
	child_process->parent = parent;
	add_process (child_process);
	return child_process->pid_t;
}


void exec (const char* filename, uint32_t pid) {
	process_t *child_proc = find_process_by_id (pid);
	uint64_t p_cr3 = x64_read_cr3();

	//!Clear up the child address space
	uint64_t c_cr3 = (uint64_t)child_proc->cr3;
	memset((void*)c_cr3, 0, 4096);
	/*FILE f = open (filename);
	if (f.status == FILE_FLAG_INVALID)
		return;*/
	unsigned char* buffer = (unsigned char*)pmmngr_alloc();
/*	read_blk (&f, buffer, f.id);
*/
	//! Create new mappings for exec
	uint64_t* new_cr3 = create_user_address_space();
	//! copy the new mappings to child_cr3
	memcpy ((void*)c_cr3, new_cr3, 4096);
	//! deallocate the new mappings
	memset((void*)new_cr3, 0, 4096);
	pmmngr_free(new_cr3);


	//!After reading we can change cr3
    x64_write_cr3((size_t)c_cr3);

	//!create the stack
	uint64_t stack = (uint64_t)create_user_stack(child_proc->cr3);
	child_proc->stack = stack;

	IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)buffer;
	PIMAGE_NT_HEADERS nt = raw_offset<PIMAGE_NT_HEADERS>(dos, dos->e_lfanew);
	
	//!extract the informations
    //load_pe_file(buffer,f.size);
	uint64_t _image_base_ = nt->OptionalHeader.ImageBase;
	ientry ent = (ientry)(nt->OptionalHeader.AddressOfEntryPoint + nt->OptionalHeader.ImageBase); //buffer

	map_page((uint64_t)buffer,_image_base_, PAGING_USER);
	int position = 1;  //we already read 4096 bytes at first
	//while(f.eof != 1){
	//	unsigned char* block = (unsigned char*)pmmngr_alloc();
	//	//read_blk(&f,block, f.id);
	//	map_page((uint64_t)block,_image_base_ + position * 4096);
	//	position++;
	//}

	child_proc->entry_point = ent;
	x64_write_cr3(p_cr3);


	thread_t *t = create_user_thread(child_proc->entry_point,child_proc->stack,(uint64_t)child_proc->cr3,"child",1);
}



uint32_t get_num_process () {
	uint32_t num_process = 0;
	for (process_t * current_proc = process_head; current_proc != NULL; current_proc = current_proc->next) {
		num_process++;
	}
	return num_process;
}

void process_map_addresses (uint64_t addr, uint64_t length, uint64_t *current_address_space, process_t *c_proc) {
	uint64_t *c_cr3 = 0;
	for (process_t * current_proc = process_head; current_proc != NULL; current_proc = current_proc->next) {
		if (current_proc == c_proc) 
			continue;
		c_cr3 = (uint64_t*)current_proc->thread_data_pointer->cr3;
		c_cr3[pml4_index(addr)] = current_address_space[pml4_index(addr)];
	}
}

process_t * get_current_process () {
	thread_t * p_thread = get_current_thread();
	process_t *c_proc = find_process_by_thread (p_thread);
	return c_proc;
}