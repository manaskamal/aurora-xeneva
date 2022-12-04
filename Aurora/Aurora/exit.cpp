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

#include <exit.h>
#include <proc.h>
#include <arch\x86_64\thread.h>
#include <sound.h>
#include <timer.h>
#include <libmngr.h>
#include <ipc\pri_loop.h>
#include <arch\x86_64\kstack.h>
#include <serial.h>

/* AuUnmapProcess -- unmaps the process image and its stack
 * @param proc -- pointer to the process data structure
 * @param thread -- pointer to the thread data structure
 */
void AuUnmapProcess(process_t *proc, thread_t *thread) {

	uint64_t init_stack = proc->stack - 2*1024*1024;

	/* Unmap the process image */
	for (uint32_t i = 0; i < proc->image_size / 4096 + 1; i++) {
		void* phys = AuGetPhysicalAddress(thread->frame.cr3,proc->image_base + i * 4096);
		uint64_t physical_address = (uint64_t)v2p((uint64_t)phys);
		if (physical_address != 0){
			AuPmmngrFree((void*)physical_address);
		}
	}

	/* here we leave the user stack unmap steps */
	//!unmap the runtime stack
	for (int i = 0; i < (2*1024*1024) / 4096; i++) 
		AuUnmapPage(init_stack + i * 4096, true);
	

	/* finally unmap the user space heap of this process */
	for (int i = 0; i < proc->_heap_size_ / 4096; i++) {
		void* phys = AuGetPhysicalAddress(thread->frame.cr3,PROCESS_HEAP_BREAK + i * 4096);
		uint64_t physical_address = (uint64_t)v2p((uint64_t)phys);
		if (physical_address != 0){
			AuPmmngrFree((void*)physical_address);
		}
	}
}

/*
 * AuDestroyFiles -- Destroy all opened files of this process
 * @param proc -- pointer to process
 * @param thread -- pointer to thread data structure
 */
void AuDestroyFiles (process_t *proc, thread_t *thread) {
	for (int i = 0; i < thread->fd_current; i++) {
		vfs_node_t *file = thread->fd[i];
		if (file) {
			if (file->flags & FS_FLAG_DEVICE) {
				continue;
			}
			free(file);
		}
	}

}


void AuDestroyChildThreads (process_t* proc, thread_t* thread) {
	/* Here we need to free all child threads */
	for (int i = 1; i < proc->num_thread-1; i++) {
		thread_t *killable = proc->threads[i];

		if (killable == NULL)
			continue;


		/* free kernel stack */
		free_kstack_child((uint64_t*)killable->frame.cr3,killable->frame.kern_esp - 8192);

		/* free the SSE memory */
		free(killable->fx_state);

		/* free up the user stack location */
		uint64_t stack_location = 0;
		if (killable == proc->main_thread) {
			stack_location = proc->stack;
			stack_location -= 2*1024*1024;
		}else {
			stack_location = killable->user_stack;
			stack_location += 1*1024*1024;
			stack_location -= 2*1024*1024;
		}


		for (int i = 0; i < (2*1024*1024) / 4096; i++) {
			void* phys = AuGetPhysicalAddress(killable->frame.cr3,stack_location + i * 4096);
			uint64_t physical_address = (uint64_t)v2p((uint64_t)phys);
			if (physical_address != 0){
				AuPmmngrFree((void*)physical_address);
			}
		}
		/* Now, check if the thread is in block list,
		 * if yes, than move it to runtime queue and free
		 * up the block list */
		thread_t *t = thread_iterate_block_list(killable->id);
		if (t != NULL){
			unblock_thread(t);
		}

		/* Destroy all opened files */
		AuDestroyFiles(proc,killable);
		/* delete the task */
		task_delete(killable);

		/* free the killable thread */
		free(killable);
	}
}


/*
 * AuDestroyMemory -- destroys all allocated memories
 * by the process
 * @param proc -- pointer to the process
 * @param thread -- pointer to the thread
 */
void AuDestroyMemory (process_t *proc, thread_t *thread) {

	/* Unmap, process image, stack & heap */
	AuUnmapProcess(proc, thread);

	/* Free the message box */
	AuPmmngrFree((void*)v2p((size_t)thread->msg_box));

	/* clean all allocated memory data structure */
	AuCleanVMA(proc);

}
/* AuUnallocSysLibs -- unallocate three system library
 * @Aurora uses only three system library for now,
 * that is also in a static location within the
 * process address space, in future Aurora will have 
 * more system libraries in a dynamic location within the
 * process address space
 */

void AuUnallocSysLibs () {
	/*Close all open dlls */
	AuLibEntry_t *lib1 = AuGetSysLib("xewid.dll");
	for (int i = 0; i < lib1->phys_blocks_count; i++)
		AuUnmapPage(XNWID_BASE + i * 4096, true);

	AuLibEntry_t *lib2 = AuGetSysLib("xnclib.dll");
	for (int i = 0; i < lib2->phys_blocks_count; i++)
		AuUnmapPage(XNCLIB_BASE + i * 4096, true);

	AuLibEntry_t *lib3 = AuGetSysLib("xnacrl.dll");
	for (int i = 0; i < lib3->phys_blocks_count; i++)
		AuUnmapPage(XNACRL_BASE + i * 4096, true);
}


void AuDestroyMainThread (process_t* proc, thread_t* thr) {
	free(thr->fx_state);
	AuDestroyFiles(proc, thr);
	task_delete(thr);
}

/*
 * AuExitProcess -- Exits the current process
 */
void AuExitProcess (process_t *proc) {
	x64_cli ();

	AuSoundStop();

	thread_t* main_thr = proc->main_thread;
	uint16_t t_id = main_thr->id;

	uint64_t cr3 = main_thr->frame.cr3;

	/* Destroy the sound dsp entry */
	AuSoundDestroyDSP(t_id);

	/* Now find a timer entry for this thread */
	int timer = find_timer_id(t_id);

	if (timer != -1) 
		destroy_timer(timer);

	/* Destroy the opened pri_loop message box */
	pri_loop_destroy_by_id(t_id);


	/* unallocate system libraries */
	AuUnallocSysLibs();

	/* destroy allocated memory */
	AuDestroyMemory(proc, main_thr);
	
	
	/* destroy all threads allocated */
	AuDestroyChildThreads(proc, main_thr);

	AuDestroyFiles(proc, main_thr);
	
	/* remove the process from process 
	 * list
	 */
	
	free(main_thr->fx_state);
	task_delete (main_thr);
	free(main_thr);

	free(proc->process_file);
	remove_process (proc);

	free_kstack((uint64_t*)cr3);
	/* free the address space */
	AuPmmngrFree((void*)cr3);

	AuSoundStart();
}