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
 *
 **/

#include <proc.h>
#include <atomic\mutex.h>
#include <timer.h>
#include <fs\fat\fat.h>
#include <_null.h>
#include <libmngr.h>
#include <serial.h>
#include <ipc\pri_loop.h>
#include <arch\x86_64\kstack.h>
#include <sound.h>

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
	free(proc);
}


/**
 * find_process_by_thread -- Finds a process by its thread address
 * @param thread -- thread address
 */
process_t *find_process_by_thread (thread_t *thread) {
	for (process_t *proc = process_head; proc != NULL; proc = proc->next) {
		if (proc->main_thread == thread) {
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
uint64_t *create_user_stack (process_t *proc, uint64_t* cr3) {
#define USER_STACK  0x0000700000000000 
	uint64_t location = USER_STACK;
	
	/* 2 mb stack / process */
	for (int i=0; i < (2*1024*1024)/4096; i++) {
		uint64_t *block = (uint64_t*)p2v((size_t)AuPmmngrAlloc());
		AuMapPageEx(cr3,v2p((size_t)block),location + i * 4096, PAGING_USER);
	}

	au_vm_area_t *vma = (au_vm_area_t*)malloc(sizeof(au_vm_area_t));
	vma->start = location;
	vma->end = (location + 2*1024*1024);
	vma->file = NULL;
	vma->offset = 0;
	vma->prot_flags = VM_READ | VM_EXEC;
	vma->type = VM_TYPE_STACK;
	vma->length = 2*1024*1024;
	AuInsertVMArea(proc, vma);
	return (uint64_t*)(USER_STACK + (2*1024*1024));
}

/*
 * Create incremental stack : Creates stack in same address space
 */
uint64_t* create_inc_stack (uint64_t* cr3) {
#define INC_STACK 0x00000000C0000000
	uint64_t location = (uint64_t)AuGetFreePage(0,true,(void*)INC_STACK);
	for (int i = 0; i < (2*1024*1024) / 4096; i++) {
		AuMapPageEx(cr3,(uint64_t)AuPmmngrAlloc(), location + i * 4096, PAGING_USER);
	}

	return (uint64_t*)(location + (1*1024*1024));
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
	
	process_t *process = (process_t*)malloc(sizeof(process_t));
	memset(process, 0,sizeof(process_t));
	process->pid_t = pid;


	//!open the process file-binary
	char *fname = (char*)filename;

	//vfs_node_t file = openfs (n,fname);
	vfs_node_t *file = fat32_open(NULL, fname);
	if (file->status == FS_FLAG_INVALID) {
		_debug_print_ ("Executable invalid \r\n");
		printf("Executable image not found\n");
		return -1;
	}

	//!open the binary file and read it
	uint64_t* buf = (uint64_t*)p2v((size_t)AuPmmngrAlloc());   
	//readfs_block(n,&file,buf);
	
	fat32_read (file,(uint64_t*)v2p((size_t)buf));
	

	IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)buf;
	PIMAGE_NT_HEADERS nt = raw_offset<PIMAGE_NT_HEADERS>(dos, dos->e_lfanew);

	
	//!extract the informations
 
	uint64_t _image_base_ = nt->OptionalHeader.ImageBase;
	ientry ent = (ientry)(nt->OptionalHeader.AddressOfEntryPoint + nt->OptionalHeader.ImageBase); //buffer

	//! create the user stack and address space
	uint64_t *cr3 = AuCreateAddressSpace();	
	_debug_print_ ("PROCESS CR3 -> %x \r\n", cr3);


	AuMapPageEx(cr3,v2p((size_t)buf),_image_base_, PAGING_USER);
	////! read rest of the image
	int position = 1;  //we already read 4096 bytes at first

	uint64_t text_section_start = _image_base_;


	while (file->eof != 1){
		uint64_t* block = (uint64_t*)p2v((size_t)AuPmmngrAlloc());
		
		fat32_read (file,(uint64_t*)v2p((size_t)block));
		AuMapPageEx(cr3,v2p((size_t)block),_image_base_ + position * 4096, PAGING_USER);
		position++;
	}

	/*
	 * Hacky way, for now we just have two system known shared library
	 * the graphics library and the widget library
	 */

	AuLibEntry_t *lib = AuGetSysLib("xnclib.dll");
	if (lib != NULL)
		for (int i = 0; i < lib->phys_blocks_count; i++) {
			void* phys = (void*)p2v((size_t)AuPmmngrAlloc());
			memcpy (phys, (void*)p2v(lib->phys_start + i * 4096), 4096);
			AuMapPageEx(cr3, v2p((size_t)phys),0x100000000 + i * 4096, PAGING_USER); 
		}

	AuLibEntry_t *lib3 = AuGetSysLib("xnacrl.dll");
	if (lib != NULL) {
		for (int i = 0; i < lib3->phys_blocks_count; i++) {
			void* phys = (void*)p2v((size_t)AuPmmngrAlloc());
			memcpy (phys, (void*)p2v(lib3->phys_start + i * 4096), 4096);
			AuMapPageEx(cr3, v2p((size_t)phys), 0x100400000 + i * 4096, PAGING_USER);
		}
	}

	AuLibEntry_t *lib2 = AuGetSysLib("xewid.dll");
	if (lib2 != NULL){
		for (int i = 0; i < lib2->phys_blocks_count; i++) {
			void* phys = (void*)p2v((size_t)AuPmmngrAlloc());
			memcpy (phys, (void*)p2v(lib2->phys_start + i * 4096), 4096);
			AuMapPageEx(cr3, v2p((size_t)phys),0x100200000 + i * 4096, PAGING_USER); 
		}
	}
	


	uint64_t text_section_end = _image_base_ + position * 4096;
	
	au_vm_area_t *vma = (au_vm_area_t*)malloc(sizeof(au_vm_area_t));
	vma->start = text_section_start;
	vma->end = text_section_end;
	vma->file = NULL;
	vma->offset = 0;
	vma->prot_flags = VM_READ | VM_EXEC;
	vma->type = VM_TYPE_TEXT;
	vma->length = file->size;
	AuInsertVMArea(process, vma);

	uint64_t stack = (uint64_t)create_user_stack(process,cr3);

	//!allocate current process
	process->name = procname;
	process->entry_point = ent;
	process->num_thread = 0;
	process->cr3 = cr3;
	process->image_base = _image_base_;
	process->stack = stack;
	process->image_size = nt->OptionalHeader.SizeOfImage;
	process->parent = NULL;
	process->_image_heap_break_ = PROCESS_HEAP_BREAK;
	process->_heap_size_ = 0;
	process->process_file = file;
	process->shared_mem_list = initialize_list();
	//! Create and thread and start scheduling when scheduler starts */
	thread_t *t = create_user_thread(ent,stack,(uint64_t)cr3,procname,0);
	//! add the process to process manager
	process->threads[process->num_thread] = t;
	process->num_thread++;
	process->main_thread = t; 
    add_process(process);

	_debug_print_ ("***Process created \r\n");

	return t->id;
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
	uint64_t stack = (uint64_t)create_user_stack(child_proc,child_proc->cr3);
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

void AuProcessListInit () {
	pid = 0;
	process_head = NULL;
	process_last = NULL;
}


/*
 * process_heap_break -- increments the heap size
 * @param 
 */
void* process_heap_break (uint64_t pages) {
	x64_cli();
	process_t *proc = get_current_process();
	int i = 0;
	uint64_t first_page = 0;
	for (i = 0; i < pages; i++) {
		uint64_t page = (uint64_t)AuGetFreePage(0,true,(void*)proc->_image_heap_break_);
		if (first_page == 0)
			first_page = page;
		uint64_t p = (uint64_t)AuPmmngrAlloc();
		AuMapPage((uint64_t)p, page, PAGING_USER);
	}
	proc->_heap_size_ += pages * 4096;
	return (void*)first_page;
}

/*
 * Link all libraries
 */
void process_link_libraries () {
	x64_cli();

	process_t *proc = get_current_process();
	
	AuPeLinkLibraryEx((void*)0x0000000100400000,(void*)0x0000000100000000);
    AuPeLinkLibraryEx((void*)0x0000000100200000,(void*)0x0000000100000000);
	//AuPeLinkLibraryEx((void*)0x0000000100500000,(void*)0x0000000100000000);
	//

	AuPeLinkLibraryEx((void*)0x0000000000600000,(void*)0x0000000100000000);  //
	AuPeLinkLibraryEx((void*)0x0000000100000000,(void*)0x0000000000600000); //
	
	//AuPeLinkLibraryEx((void*)0x0000000000600000,(void*)0x0000000100400000);
	///* Link the CLIB to every DLL */
	

	
    //AuPeLinkLibraryEx((void*)0x0000000000600000,(void*)0x0000000100200000);
}