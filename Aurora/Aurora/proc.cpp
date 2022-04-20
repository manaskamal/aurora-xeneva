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
#include <timer.h>
#include <fs\fat\fat.h>
#include <_null.h>
#include <serial.h>
#include <ipc\pri_loop.h>


process_t *process_head = NULL;
process_t *process_last = NULL;
static int pid = 0;

/**
 * add_process -- Adds a process to the process list
 * @param proc -- process address
 */
void add_process (process_t *proc) {
	//mutex_lock (add_mutex);
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
	//mutex_unlock (add_mutex);
}

/**
 * remove_process -- removes a process from the process list
 * @param proc -- process address
 */
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
	AuPmmngrFree(proc);
}


/**
 * find_process_by_thread -- Finds a process by its thread address
 * @param thread -- thread address
 */
process_t *find_process_by_thread (thread_t *thread) {
	for (process_t *proc = process_head; proc != NULL; proc = proc->next) {
		if (proc->thread_data_pointer == thread) {
			return proc;
		}
	}
}

/**
 * find_process_by_id -- Finds a process by its pid
 * @param pid -- process id
 */
process_t *find_process_by_id (uint32_t pid) {
	for (process_t *proc = process_head; proc != NULL; proc = proc->next) {
		if (proc->pid_t == pid) {
			return proc;
		}
	}
	return NULL;
}

/**
 * create_user_stack -- Create stack for User process 
 * @param cr3 -- top level paging structure address
 */
uint64_t *create_user_stack (uint64_t* cr3) {
#define USER_STACK  0x0000700000000000 
	
	uint64_t location = USER_STACK;
	
	/* 2 mb stack / process */
	for (int i=0; i < (2*1024*1024)/4096; i++) {
		uint64_t *block = (uint64_t*)AuPmmngrAlloc();
		memset (block, 0, 4096);
		AuMapPageEx(cr3, (uint64_t)block,location + i * 4096, PAGING_USER);
	}

	return (uint64_t*)(USER_STACK + (2*1024*1024));
}

/*
 * Create incremental stack : Creates stack in same address space
 */
uint64_t* create_inc_stack (uint64_t* cr3) {
#define INC_STACK 0x0000010000000000 
	uint64_t location = INC_STACK ; //+ user_stack_index;

	for (int i = 0; i < (2*1024*1024) / 4096; i++) {
		void* p = AuPmmngrAlloc();
		memset(p, 0, 4096);
		AuMapPageEx(cr3,(uint64_t)p, location + i * 4096, PAGING_USER);
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

/**
 * create_process -- creates a thread with executable image entry point
 * address
 * @param filename -- executable file path
 * @param procname -- processname
 * @return -- created thread id
 */
int AuCreateProcess(const char* filename, char* procname) {
	//!allocate a data-structure for process 
	process_t *process = (process_t*)malloc(sizeof(process_t)); //pmmngr_alloc();
	memset(process, 0,sizeof(process_t));
	process->pid_t = pid;
	process->mmap_sz = 0;


	//!open the process file-binary
	char *fname = (char*)filename;
   
	//vfs_node_t file = openfs (n,fname);
	vfs_node_t file = fat32_open(NULL, fname);

	if (file.status == FS_FLAG_INVALID) {
		printf("Executable image not found\n");
		return -1;
	}
	//!open the binary file and read it
	uint64_t* buf = (uint64_t*)AuPmmngrAlloc();   
	//readfs_block(n,&file,buf);
	fat32_read (&file,buf);
	

	IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)buf;
	PIMAGE_NT_HEADERS nt = raw_offset<PIMAGE_NT_HEADERS>(dos, dos->e_lfanew);

	//!extract the informations
   // load_pe_file(buf,file.size);
	uint64_t _image_base_ = nt->OptionalHeader.ImageBase;
	ientry ent = (ientry)(nt->OptionalHeader.AddressOfEntryPoint + nt->OptionalHeader.ImageBase); //buffer

	//! create the user stack and address space
	uint64_t *cr3 = AuCreateAddressSpace();	

	uint64_t stack = (uint64_t)create_user_stack(cr3);

	AuMapPageEx(cr3,(uint64_t)buf,_image_base_, PAGING_USER);
	////! read rest of the image
	int position = 1;  //we already read 4096 bytes at first


	while (file.eof != 1){
		uint64_t* block = (uint64_t*)AuPmmngrAlloc();
		//read_blk(&file,block,file.id);
		//readfs_block (n, &file, block);
		fat32_read (&file,block);
		AuMapPageEx(cr3,(uint64_t)block,_image_base_ + position * 4096, PAGING_USER);
		position++;
	}


	//!allocate current process
	//strcpy (process->name,procname);
	process->name = procname;
	process->entry_point = ent;

	process->cr3 = cr3;
	process->image_base = _image_base_;
	process->stack = stack;
	process->image_size = nt->OptionalHeader.SizeOfImage;
	_debug_print_ ("PROCESS CREATION IMAGE SIZE -> %d bytes \r\n", process->image_size);
	process->parent = NULL;
	//! Create and thread and start scheduling when scheduler starts */
	thread_t *t = create_user_thread(ent,stack,(uint64_t)cr3,procname,0);
	//allocate_fd(t);
	//! add the process to process manager
	process->thread_data_pointer = t;
    add_process(process);

	return t->id;
}

/**
 * kill_process -- kills the running process
 */
void kill_process () {
	x64_cli();
	thread_t * remove_thread = get_current_thread();
	uint16_t t_id = remove_thread->id;
	process_t *proc = find_process_by_thread (remove_thread);
	uint64_t  init_stack = proc->stack - 0x100000;
	uint64_t image_base = proc->image_base;
	uint64_t *cr3 = (uint64_t*)remove_thread->cr3;
	
	int timer = find_timer_id (remove_thread->id);

	/** destroy the timer */
	if (timer != -1) {
		destroy_timer (timer);
	}


	/*uint64_t virt = USER_BASE_ADDRESS;
	for (int i = 0; i < proc->mmap_sz + 1; i++) {
		unmap_page (virt);
		virt = virt + i * 4096;
	}*/
		

	remove_process (proc);
	task_delete (remove_thread);
	AuPmmngrFree(remove_thread);
	AuPmmngrFree(remove_thread->msg_box);
	pri_loop_destroy_by_id (t_id);

	//!unmap the binary image
	for (uint32_t i = 0; i < proc->image_size / 4096; i++) {
	//	uint64_t virtual_addr = proc->image_base + (i * 4096);
		AuUnmapPage(image_base + i * 4096);
	}
	
	//!unmap the runtime stack
	for (int i = 0; i < 0x100000 / 4096; i++) {
		AuUnmapPage(init_stack + i * 4096);
	}


	_debug_print_ ("Used Pmmngr -> %d MB / Total -> %d MB \r\n", pmmngr_get_used_ram () / 1024 / 1024, pmmngr_get_total_ram() / 1024 / 1024);

	AuPmmngrFree(cr3);
}

/**
 * kill_process_by_id -- kills a process by its id
 * @param id -- id of the thread to be killed
 */
void kill_process_by_id (uint16_t id) {
	x64_cli();
	bool was_blocked = false;
	thread_t * remove_thread = thread_iterate_ready_list(id);
	if (remove_thread == NULL) {
		remove_thread = (thread_t*)thread_iterate_block_list(id);
		was_blocked = true;
	}
	process_t *proc = find_process_by_thread (remove_thread);

	uint64_t  init_stack = proc->stack - 0x100000;
	uint64_t image_base = proc->image_base;
	size_t image_size = proc->image_size;
	//uint64_t heap_base = (uint64_t)proc->user_heap_start;
	uint64_t *cr3 = (uint64_t*)remove_thread->cr3;

	if (was_blocked)
		unblock_thread(remove_thread);
	remove_thread->state = THREAD_STATE_BLOCKED;
	task_delete (remove_thread);
	AuPmmngrFree(remove_thread);
	remove_process (proc);

	
	//!unmap the runtime stack
	for (int i = 0; i < 0x100000 / 4096; i++) {
		AuUnmapPageEx(cr3,init_stack + i * 4096, true);
	}

	//!unmap the binary image
	for (int i = 0; i < image_size / 4096; i++) {
		uint64_t virtual_addr = image_base + (i * 4096);
		AuUnmapPageEx(cr3, virtual_addr, true);
	}

	//!unmap user heap
	/*for (int i = 0; i < 0xB01000 / 4096; i++) {
		unmap_page_ex(cr3,heap_base + i * 4096, true);
	}*/

	AuPmmngrFree(cr3);
}


uint32_t fork () {
	process_t *child_process = (process_t*)AuPmmngrAlloc();
	
	thread_t * p_thread = get_current_thread();
	process_t *parent = find_process_by_thread (p_thread);

	uint64_t *child_cr3 = (uint64_t*)AuPmmngrAlloc(); //create_user_address_space();
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
	unsigned char* buffer = (unsigned char*)AuPmmngrAlloc();
/*	read_blk (&f, buffer, f.id);
*/
	//! Create new mappings for exec
	uint64_t* new_cr3 = AuCreateAddressSpace();
	//! copy the new mappings to child_cr3
	memcpy ((void*)c_cr3, new_cr3, 4096);
	//! deallocate the new mappings
	memset((void*)new_cr3, 0, 4096);
	AuPmmngrFree(new_cr3);


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

	AuMapPage((uint64_t)buffer,_image_base_, PAGING_USER);
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


process_t * get_current_process () {
	thread_t * p_thread = get_current_thread();
	process_t *c_proc = find_process_by_thread (p_thread);
	return c_proc;
}

void process_list_initialize () {
	pid = 0;
	process_head = NULL;
	process_last = NULL;
}
