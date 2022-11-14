; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

CONST	SEGMENT
$SG4196	DB	'xewid.dll', 00H
	ORG $+6
$SG4202	DB	'xnclib.dll', 00H
	ORG $+5
$SG4208	DB	'xnacrl.dll', 00H
CONST	ENDS
PUBLIC	?AuExitProcess@@YAXPEAU_process_@@@Z		; AuExitProcess
PUBLIC	?AuUnmapProcess@@YAXPEAU_process_@@PEAU_thread_@@@Z ; AuUnmapProcess
PUBLIC	?AuDestroyFiles@@YAXPEAU_process_@@PEAU_thread_@@@Z ; AuDestroyFiles
PUBLIC	?AuDestroyChildThreads@@YAXPEAU_process_@@PEAU_thread_@@@Z ; AuDestroyChildThreads
PUBLIC	?AuDestroyMemory@@YAXPEAU_process_@@PEAU_thread_@@@Z ; AuDestroyMemory
PUBLIC	?AuUnallocSysLibs@@YAXXZ			; AuUnallocSysLibs
PUBLIC	?AuDestroyMainThread@@YAXPEAU_process_@@PEAU_thread_@@@Z ; AuDestroyMainThread
EXTRN	AuPmmngrFree:PROC
EXTRN	v2p:PROC
EXTRN	x64_cli:PROC
EXTRN	AuUnmapPage:PROC
EXTRN	AuGetPhysicalAddress:PROC
EXTRN	free:PROC
EXTRN	unblock_thread:PROC
EXTRN	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z:PROC ; thread_iterate_block_list
EXTRN	?task_delete@@YAXPEAU_thread_@@@Z:PROC		; task_delete
EXTRN	?remove_process@@YAXPEAU_process_@@@Z:PROC	; remove_process
EXTRN	?AuCleanVMA@@YAXPEAU_process_@@@Z:PROC		; AuCleanVMA
EXTRN	?AuSoundDestroyDSP@@YAXG@Z:PROC			; AuSoundDestroyDSP
EXTRN	?destroy_timer@@YAXH@Z:PROC			; destroy_timer
EXTRN	?find_timer_id@@YAHG@Z:PROC			; find_timer_id
EXTRN	?AuGetSysLib@@YAPEAU_libentry_@@PEAD@Z:PROC	; AuGetSysLib
EXTRN	?pri_loop_destroy_by_id@@YAXG@Z:PROC		; pri_loop_destroy_by_id
EXTRN	?free_kstack@@YAXPEA_K@Z:PROC			; free_kstack
EXTRN	?free_kstack_child@@YAXPEA_K_K@Z:PROC		; free_kstack_child
pdata	SEGMENT
$pdata$?AuExitProcess@@YAXPEAU_process_@@@Z DD imagerel $LN4
	DD	imagerel $LN4+254
	DD	imagerel $unwind$?AuExitProcess@@YAXPEAU_process_@@@Z
$pdata$?AuUnmapProcess@@YAXPEAU_process_@@PEAU_thread_@@@Z DD imagerel $LN14
	DD	imagerel $LN14+426
	DD	imagerel $unwind$?AuUnmapProcess@@YAXPEAU_process_@@PEAU_thread_@@@Z
$pdata$?AuDestroyFiles@@YAXPEAU_process_@@PEAU_thread_@@@Z DD imagerel $LN8
	DD	imagerel $LN8+117
	DD	imagerel $unwind$?AuDestroyFiles@@YAXPEAU_process_@@PEAU_thread_@@@Z
$pdata$?AuDestroyChildThreads@@YAXPEAU_process_@@PEAU_thread_@@@Z DD imagerel $LN14
	DD	imagerel $LN14+455
	DD	imagerel $unwind$?AuDestroyChildThreads@@YAXPEAU_process_@@PEAU_thread_@@@Z
$pdata$?AuDestroyMemory@@YAXPEAU_process_@@PEAU_thread_@@@Z DD imagerel $LN3
	DD	imagerel $LN3+69
	DD	imagerel $unwind$?AuDestroyMemory@@YAXPEAU_process_@@PEAU_thread_@@@Z
$pdata$?AuUnallocSysLibs@@YAXXZ DD imagerel $LN12
	DD	imagerel $LN12+273
	DD	imagerel $unwind$?AuUnallocSysLibs@@YAXXZ
$pdata$?AuDestroyMainThread@@YAXPEAU_process_@@PEAU_thread_@@@Z DD imagerel $LN3
	DD	imagerel $LN3+61
	DD	imagerel $unwind$?AuDestroyMainThread@@YAXPEAU_process_@@PEAU_thread_@@@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?AuExitProcess@@YAXPEAU_process_@@@Z DD 010901H
	DD	08209H
$unwind$?AuUnmapProcess@@YAXPEAU_process_@@PEAU_thread_@@@Z DD 010e01H
	DD	0e20eH
$unwind$?AuDestroyFiles@@YAXPEAU_process_@@PEAU_thread_@@@Z DD 010e01H
	DD	0620eH
$unwind$?AuDestroyChildThreads@@YAXPEAU_process_@@PEAU_thread_@@@Z DD 010e01H
	DD	0a20eH
$unwind$?AuDestroyMemory@@YAXPEAU_process_@@PEAU_thread_@@@Z DD 010e01H
	DD	0420eH
$unwind$?AuUnallocSysLibs@@YAXXZ DD 010401H
	DD	0a204H
$unwind$?AuDestroyMainThread@@YAXPEAU_process_@@PEAU_thread_@@@Z DD 010e01H
	DD	0420eH
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\exit.cpp
_TEXT	SEGMENT
proc$ = 48
thr$ = 56
?AuDestroyMainThread@@YAXPEAU_process_@@PEAU_thread_@@@Z PROC ; AuDestroyMainThread

; 188  : void AuDestroyMainThread (process_t* proc, thread_t* thr) {

$LN3:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 189  : 	free(thr->fx_state);

	mov	rax, QWORD PTR thr$[rsp]
	mov	rcx, QWORD PTR [rax+216]
	call	free

; 190  : 	AuDestroyFiles(proc, thr);

	mov	rdx, QWORD PTR thr$[rsp]
	mov	rcx, QWORD PTR proc$[rsp]
	call	?AuDestroyFiles@@YAXPEAU_process_@@PEAU_thread_@@@Z ; AuDestroyFiles

; 191  : 	task_delete(thr);

	mov	rcx, QWORD PTR thr$[rsp]
	call	?task_delete@@YAXPEAU_thread_@@@Z	; task_delete

; 192  : }

	add	rsp, 40					; 00000028H
	ret	0
?AuDestroyMainThread@@YAXPEAU_process_@@PEAU_thread_@@@Z ENDP ; AuDestroyMainThread
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\exit.cpp
_TEXT	SEGMENT
i$1 = 32
i$2 = 36
i$3 = 40
lib1$ = 48
lib2$ = 56
lib3$ = 64
?AuUnallocSysLibs@@YAXXZ PROC				; AuUnallocSysLibs

; 172  : void AuUnallocSysLibs () {

$LN12:
	sub	rsp, 88					; 00000058H

; 173  : 	/*Close all open dlls */
; 174  : 	AuLibEntry_t *lib1 = AuGetSysLib("xewid.dll");

	lea	rcx, OFFSET FLAT:$SG4196
	call	?AuGetSysLib@@YAPEAU_libentry_@@PEAD@Z	; AuGetSysLib
	mov	QWORD PTR lib1$[rsp], rax

; 175  : 	for (int i = 0; i < lib1->phys_blocks_count; i++)

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN9@AuUnallocS
$LN8@AuUnallocS:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN9@AuUnallocS:
	mov	rax, QWORD PTR lib1$[rsp]
	mov	eax, DWORD PTR [rax+88]
	cmp	DWORD PTR i$1[rsp], eax
	jge	SHORT $LN7@AuUnallocS

; 176  : 		AuUnmapPage(XNWID_BASE + i * 4096, true);

	mov	eax, DWORD PTR i$1[rsp]
	imul	eax, 4096				; 00001000H
	cdqe
	mov	rcx, 4297064448				; 0000000100200000H
	add	rax, rcx
	mov	dl, 1
	mov	rcx, rax
	call	AuUnmapPage
	jmp	SHORT $LN8@AuUnallocS
$LN7@AuUnallocS:

; 177  : 
; 178  : 	AuLibEntry_t *lib2 = AuGetSysLib("xnclib.dll");

	lea	rcx, OFFSET FLAT:$SG4202
	call	?AuGetSysLib@@YAPEAU_libentry_@@PEAD@Z	; AuGetSysLib
	mov	QWORD PTR lib2$[rsp], rax

; 179  : 	for (int i = 0; i < lib2->phys_blocks_count; i++)

	mov	DWORD PTR i$2[rsp], 0
	jmp	SHORT $LN6@AuUnallocS
$LN5@AuUnallocS:
	mov	eax, DWORD PTR i$2[rsp]
	inc	eax
	mov	DWORD PTR i$2[rsp], eax
$LN6@AuUnallocS:
	mov	rax, QWORD PTR lib2$[rsp]
	mov	eax, DWORD PTR [rax+88]
	cmp	DWORD PTR i$2[rsp], eax
	jge	SHORT $LN4@AuUnallocS

; 180  : 		AuUnmapPage(XNCLIB_BASE + i * 4096, true);

	mov	eax, DWORD PTR i$2[rsp]
	imul	eax, 4096				; 00001000H
	cdqe
	mov	rcx, 4294967296				; 0000000100000000H
	add	rax, rcx
	mov	dl, 1
	mov	rcx, rax
	call	AuUnmapPage
	jmp	SHORT $LN5@AuUnallocS
$LN4@AuUnallocS:

; 181  : 
; 182  : 	AuLibEntry_t *lib3 = AuGetSysLib("xnacrl.dll");

	lea	rcx, OFFSET FLAT:$SG4208
	call	?AuGetSysLib@@YAPEAU_libentry_@@PEAD@Z	; AuGetSysLib
	mov	QWORD PTR lib3$[rsp], rax

; 183  : 	for (int i = 0; i < lib3->phys_blocks_count; i++)

	mov	DWORD PTR i$3[rsp], 0
	jmp	SHORT $LN3@AuUnallocS
$LN2@AuUnallocS:
	mov	eax, DWORD PTR i$3[rsp]
	inc	eax
	mov	DWORD PTR i$3[rsp], eax
$LN3@AuUnallocS:
	mov	rax, QWORD PTR lib3$[rsp]
	mov	eax, DWORD PTR [rax+88]
	cmp	DWORD PTR i$3[rsp], eax
	jge	SHORT $LN1@AuUnallocS

; 184  : 		AuUnmapPage(XNACRL_BASE + i * 4096, true);

	mov	eax, DWORD PTR i$3[rsp]
	imul	eax, 4096				; 00001000H
	cdqe
	mov	rcx, 4299161600				; 0000000100400000H
	add	rax, rcx
	mov	dl, 1
	mov	rcx, rax
	call	AuUnmapPage
	jmp	SHORT $LN2@AuUnallocS
$LN1@AuUnallocS:

; 185  : }

	add	rsp, 88					; 00000058H
	ret	0
?AuUnallocSysLibs@@YAXXZ ENDP				; AuUnallocSysLibs
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\exit.cpp
_TEXT	SEGMENT
proc$ = 48
thread$ = 56
?AuDestroyMemory@@YAXPEAU_process_@@PEAU_thread_@@@Z PROC ; AuDestroyMemory

; 152  : void AuDestroyMemory (process_t *proc, thread_t *thread) {

$LN3:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 153  : 
; 154  : 	/* Unmap, process image, stack & heap */
; 155  : 	AuUnmapProcess(proc, thread);

	mov	rdx, QWORD PTR thread$[rsp]
	mov	rcx, QWORD PTR proc$[rsp]
	call	?AuUnmapProcess@@YAXPEAU_process_@@PEAU_thread_@@@Z ; AuUnmapProcess

; 156  : 
; 157  : 	/* Free the message box */
; 158  : 	AuPmmngrFree((void*)v2p((size_t)thread->msg_box));

	mov	rax, QWORD PTR thread$[rsp]
	mov	rcx, QWORD PTR [rax+248]
	call	v2p
	mov	rcx, rax
	call	AuPmmngrFree

; 159  : 
; 160  : 	/* clean all allocated memory data structure */
; 161  : 	AuCleanVMA(proc);

	mov	rcx, QWORD PTR proc$[rsp]
	call	?AuCleanVMA@@YAXPEAU_process_@@@Z	; AuCleanVMA

; 162  : 
; 163  : }

	add	rsp, 40					; 00000028H
	ret	0
?AuDestroyMemory@@YAXPEAU_process_@@PEAU_thread_@@@Z ENDP ; AuDestroyMemory
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\exit.cpp
_TEXT	SEGMENT
i$1 = 32
i$2 = 36
killable$3 = 40
stack_location$4 = 48
physical_address$5 = 56
t$6 = 64
phys$7 = 72
proc$ = 96
thread$ = 104
?AuDestroyChildThreads@@YAXPEAU_process_@@PEAU_thread_@@@Z PROC ; AuDestroyChildThreads

; 93   : void AuDestroyChildThreads (process_t* proc, thread_t* thread) {

$LN14:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 88					; 00000058H

; 94   : 	/* Here we need to free all child threads */
; 95   : 	for (int i = 1; i < proc->num_thread-1; i++) {

	mov	DWORD PTR i$1[rsp], 1
	jmp	SHORT $LN11@AuDestroyC
$LN10@AuDestroyC:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN11@AuDestroyC:
	mov	rax, QWORD PTR proc$[rsp]
	movzx	eax, BYTE PTR [rax+2072]
	dec	eax
	cmp	DWORD PTR i$1[rsp], eax
	jge	$LN9@AuDestroyC

; 96   : 		thread_t *killable = proc->threads[i];

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR proc$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8+24]
	mov	QWORD PTR killable$3[rsp], rax

; 97   : 
; 98   : 		if (killable == NULL)

	cmp	QWORD PTR killable$3[rsp], 0
	jne	SHORT $LN8@AuDestroyC

; 99   : 			continue;

	jmp	SHORT $LN10@AuDestroyC
$LN8@AuDestroyC:

; 100  : 
; 101  : 
; 102  : 		/* free kernel stack */
; 103  : 		free_kstack_child((uint64_t*)killable->frame.cr3,killable->frame.kern_esp - 8192);

	mov	rax, QWORD PTR killable$3[rsp]
	mov	rax, QWORD PTR [rax+200]
	sub	rax, 8192				; 00002000H
	mov	rdx, rax
	mov	rax, QWORD PTR killable$3[rsp]
	mov	rcx, QWORD PTR [rax+192]
	call	?free_kstack_child@@YAXPEA_K_K@Z	; free_kstack_child

; 104  : 
; 105  : 		/* free the SSE memory */
; 106  : 		free(killable->fx_state);

	mov	rax, QWORD PTR killable$3[rsp]
	mov	rcx, QWORD PTR [rax+216]
	call	free

; 107  : 
; 108  : 		/* free up the user stack location */
; 109  : 		uint64_t stack_location = 0;

	mov	QWORD PTR stack_location$4[rsp], 0

; 110  : 		if (killable == proc->main_thread) {

	mov	rax, QWORD PTR proc$[rsp]
	mov	rax, QWORD PTR [rax+2064]
	cmp	QWORD PTR killable$3[rsp], rax
	jne	SHORT $LN7@AuDestroyC

; 111  : 			stack_location = proc->stack;

	mov	rax, QWORD PTR proc$[rsp]
	mov	rax, QWORD PTR [rax+2104]
	mov	QWORD PTR stack_location$4[rsp], rax

; 112  : 			stack_location -= 2*1024*1024;

	mov	rax, QWORD PTR stack_location$4[rsp]
	sub	rax, 2097152				; 00200000H
	mov	QWORD PTR stack_location$4[rsp], rax

; 113  : 		}else {

	jmp	SHORT $LN6@AuDestroyC
$LN7@AuDestroyC:

; 114  : 			stack_location = killable->user_stack;

	mov	rax, QWORD PTR killable$3[rsp]
	mov	rax, QWORD PTR [rax+208]
	mov	QWORD PTR stack_location$4[rsp], rax

; 115  : 			stack_location += 1*1024*1024;

	mov	rax, QWORD PTR stack_location$4[rsp]
	add	rax, 1048576				; 00100000H
	mov	QWORD PTR stack_location$4[rsp], rax

; 116  : 			stack_location -= 2*1024*1024;

	mov	rax, QWORD PTR stack_location$4[rsp]
	sub	rax, 2097152				; 00200000H
	mov	QWORD PTR stack_location$4[rsp], rax
$LN6@AuDestroyC:

; 117  : 		}
; 118  : 
; 119  : 
; 120  : 		for (int i = 0; i < (2*1024*1024) / 4096; i++) {

	mov	DWORD PTR i$2[rsp], 0
	jmp	SHORT $LN5@AuDestroyC
$LN4@AuDestroyC:
	mov	eax, DWORD PTR i$2[rsp]
	inc	eax
	mov	DWORD PTR i$2[rsp], eax
$LN5@AuDestroyC:
	cmp	DWORD PTR i$2[rsp], 512			; 00000200H
	jge	SHORT $LN3@AuDestroyC

; 121  : 			void* phys = AuGetPhysicalAddress(killable->frame.cr3,stack_location + i * 4096);

	mov	eax, DWORD PTR i$2[rsp]
	imul	eax, 4096				; 00001000H
	cdqe
	mov	rcx, QWORD PTR stack_location$4[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	rdx, rax
	mov	rax, QWORD PTR killable$3[rsp]
	mov	rcx, QWORD PTR [rax+192]
	call	AuGetPhysicalAddress
	mov	QWORD PTR phys$7[rsp], rax

; 122  : 			uint64_t physical_address = (uint64_t)v2p((uint64_t)phys);

	mov	rcx, QWORD PTR phys$7[rsp]
	call	v2p
	mov	QWORD PTR physical_address$5[rsp], rax

; 123  : 			if (physical_address != 0){

	cmp	QWORD PTR physical_address$5[rsp], 0
	je	SHORT $LN2@AuDestroyC

; 124  : 				AuPmmngrFree((void*)physical_address);

	mov	rcx, QWORD PTR physical_address$5[rsp]
	call	AuPmmngrFree
$LN2@AuDestroyC:

; 125  : 			}
; 126  : 		}

	jmp	SHORT $LN4@AuDestroyC
$LN3@AuDestroyC:

; 127  : 		/* Now, check if the thread is in block list,
; 128  : 		 * if yes, than move it to runtime queue and free
; 129  : 		 * up the block list */
; 130  : 		thread_t *t = thread_iterate_block_list(killable->id);

	mov	rax, QWORD PTR killable$3[rsp]
	movzx	eax, WORD PTR [rax+242]
	mov	ecx, eax
	call	?thread_iterate_block_list@@YAPEAU_thread_@@H@Z ; thread_iterate_block_list
	mov	QWORD PTR t$6[rsp], rax

; 131  : 		if (t != NULL){

	cmp	QWORD PTR t$6[rsp], 0
	je	SHORT $LN1@AuDestroyC

; 132  : 			unblock_thread(t);

	mov	rcx, QWORD PTR t$6[rsp]
	call	unblock_thread
$LN1@AuDestroyC:

; 133  : 		}
; 134  : 
; 135  : 		/* Destroy all opened files */
; 136  : 		AuDestroyFiles(proc,killable);

	mov	rdx, QWORD PTR killable$3[rsp]
	mov	rcx, QWORD PTR proc$[rsp]
	call	?AuDestroyFiles@@YAXPEAU_process_@@PEAU_thread_@@@Z ; AuDestroyFiles

; 137  : 		/* delete the task */
; 138  : 		task_delete(killable);

	mov	rcx, QWORD PTR killable$3[rsp]
	call	?task_delete@@YAXPEAU_thread_@@@Z	; task_delete

; 139  : 
; 140  : 		/* free the killable thread */
; 141  : 		free(killable);

	mov	rcx, QWORD PTR killable$3[rsp]
	call	free

; 142  : 	}

	jmp	$LN10@AuDestroyC
$LN9@AuDestroyC:

; 143  : }

	add	rsp, 88					; 00000058H
	ret	0
?AuDestroyChildThreads@@YAXPEAU_process_@@PEAU_thread_@@@Z ENDP ; AuDestroyChildThreads
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\exit.cpp
_TEXT	SEGMENT
i$1 = 32
file$2 = 40
proc$ = 64
thread$ = 72
?AuDestroyFiles@@YAXPEAU_process_@@PEAU_thread_@@@Z PROC ; AuDestroyFiles

; 79   : void AuDestroyFiles (process_t *proc, thread_t *thread) {

$LN8:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 80   : 	for (int i = 0; i < thread->fd_current; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN5@AuDestroyF
$LN4@AuDestroyF:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN5@AuDestroyF:
	mov	rax, QWORD PTR thread$[rsp]
	mov	eax, DWORD PTR [rax+744]
	cmp	DWORD PTR i$1[rsp], eax
	jge	SHORT $LN3@AuDestroyF

; 81   : 		vfs_node_t *file = thread->fd[i];

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR thread$[rsp]
	mov	rax, QWORD PTR [rcx+rax*8+264]
	mov	QWORD PTR file$2[rsp], rax

; 82   : 		if (file) {

	cmp	QWORD PTR file$2[rsp], 0
	je	SHORT $LN2@AuDestroyF

; 83   : 			if (file->flags & FS_FLAG_DEVICE) {

	mov	rax, QWORD PTR file$2[rsp]
	movzx	eax, BYTE PTR [rax+48]
	and	eax, 8
	test	eax, eax
	je	SHORT $LN1@AuDestroyF

; 84   : 				continue;

	jmp	SHORT $LN4@AuDestroyF
$LN1@AuDestroyF:

; 85   : 			}
; 86   : 			free(file);

	mov	rcx, QWORD PTR file$2[rsp]
	call	free
$LN2@AuDestroyF:

; 87   : 		}
; 88   : 	}

	jmp	SHORT $LN4@AuDestroyF
$LN3@AuDestroyF:

; 89   : 
; 90   : }

	add	rsp, 56					; 00000038H
	ret	0
?AuDestroyFiles@@YAXPEAU_process_@@PEAU_thread_@@@Z ENDP ; AuDestroyFiles
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\exit.cpp
_TEXT	SEGMENT
i$1 = 32
i$2 = 36
i$3 = 40
physical_address$4 = 48
physical_address$5 = 56
phys$6 = 64
init_stack$ = 72
tv93 = 80
tv67 = 88
phys$7 = 96
proc$ = 128
thread$ = 136
?AuUnmapProcess@@YAXPEAU_process_@@PEAU_thread_@@@Z PROC ; AuUnmapProcess

; 45   : void AuUnmapProcess(process_t *proc, thread_t *thread) {

$LN14:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 120				; 00000078H

; 46   : 
; 47   : 	uint64_t init_stack = proc->stack - 2*1024*1024;

	mov	rax, QWORD PTR proc$[rsp]
	mov	rax, QWORD PTR [rax+2104]
	sub	rax, 2097152				; 00200000H
	mov	QWORD PTR init_stack$[rsp], rax

; 48   : 
; 49   : 	/* Unmap the process image */
; 50   : 	for (uint32_t i = 0; i < proc->image_size / 4096 + 1; i++) {

	mov	DWORD PTR i$2[rsp], 0
	jmp	SHORT $LN11@AuUnmapPro
$LN10@AuUnmapPro:
	mov	eax, DWORD PTR i$2[rsp]
	inc	eax
	mov	DWORD PTR i$2[rsp], eax
$LN11@AuUnmapPro:
	mov	eax, DWORD PTR i$2[rsp]
	mov	QWORD PTR tv67[rsp], rax
	xor	edx, edx
	mov	rcx, QWORD PTR proc$[rsp]
	mov	rax, QWORD PTR [rcx+2080]
	mov	ecx, 4096				; 00001000H
	div	rcx
	inc	rax
	mov	rcx, QWORD PTR tv67[rsp]
	cmp	rcx, rax
	jae	SHORT $LN9@AuUnmapPro

; 51   : 		void* phys = AuGetPhysicalAddress(thread->frame.cr3,proc->image_base + i * 4096);

	mov	eax, DWORD PTR i$2[rsp]
	imul	eax, 4096				; 00001000H
	mov	eax, eax
	mov	rcx, QWORD PTR proc$[rsp]
	add	rax, QWORD PTR [rcx+2096]
	mov	rdx, rax
	mov	rax, QWORD PTR thread$[rsp]
	mov	rcx, QWORD PTR [rax+192]
	call	AuGetPhysicalAddress
	mov	QWORD PTR phys$6[rsp], rax

; 52   : 		uint64_t physical_address = (uint64_t)v2p((uint64_t)phys);

	mov	rcx, QWORD PTR phys$6[rsp]
	call	v2p
	mov	QWORD PTR physical_address$5[rsp], rax

; 53   : 		if (physical_address != 0){

	cmp	QWORD PTR physical_address$5[rsp], 0
	je	SHORT $LN8@AuUnmapPro

; 54   : 			AuPmmngrFree((void*)physical_address);

	mov	rcx, QWORD PTR physical_address$5[rsp]
	call	AuPmmngrFree
$LN8@AuUnmapPro:

; 55   : 		}
; 56   : 	}

	jmp	$LN10@AuUnmapPro
$LN9@AuUnmapPro:

; 57   : 
; 58   : 	/* here we leave the user stack unmap steps */
; 59   : 	//!unmap the runtime stack
; 60   : 	for (int i = 0; i < (2*1024*1024) / 4096; i++) 

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN7@AuUnmapPro
$LN6@AuUnmapPro:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN7@AuUnmapPro:
	cmp	DWORD PTR i$1[rsp], 512			; 00000200H
	jge	SHORT $LN5@AuUnmapPro

; 61   : 		AuUnmapPage(init_stack + i * 4096, true);

	mov	eax, DWORD PTR i$1[rsp]
	imul	eax, 4096				; 00001000H
	cdqe
	mov	rcx, QWORD PTR init_stack$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	dl, 1
	mov	rcx, rax
	call	AuUnmapPage
	jmp	SHORT $LN6@AuUnmapPro
$LN5@AuUnmapPro:

; 62   : 	
; 63   : 
; 64   : 	/* finally unmap the user space heap of this process */
; 65   : 	for (int i = 0; i < proc->_heap_size_ / 4096; i++) {

	mov	DWORD PTR i$3[rsp], 0
	jmp	SHORT $LN4@AuUnmapPro
$LN3@AuUnmapPro:
	mov	eax, DWORD PTR i$3[rsp]
	inc	eax
	mov	DWORD PTR i$3[rsp], eax
$LN4@AuUnmapPro:
	movsxd	rax, DWORD PTR i$3[rsp]
	mov	QWORD PTR tv93[rsp], rax
	xor	edx, edx
	mov	rcx, QWORD PTR proc$[rsp]
	mov	rax, QWORD PTR [rcx+2120]
	mov	ecx, 4096				; 00001000H
	div	rcx
	mov	rcx, QWORD PTR tv93[rsp]
	cmp	rcx, rax
	jae	SHORT $LN2@AuUnmapPro

; 66   : 		void* phys = AuGetPhysicalAddress(thread->frame.cr3,PROCESS_HEAP_BREAK + i * 4096);

	mov	eax, DWORD PTR i$3[rsp]
	imul	eax, 4096				; 00001000H
	cdqe
	mov	rcx, 15032385536			; 0000000380000000H
	add	rax, rcx
	mov	rdx, rax
	mov	rax, QWORD PTR thread$[rsp]
	mov	rcx, QWORD PTR [rax+192]
	call	AuGetPhysicalAddress
	mov	QWORD PTR phys$7[rsp], rax

; 67   : 		uint64_t physical_address = (uint64_t)v2p((uint64_t)phys);

	mov	rcx, QWORD PTR phys$7[rsp]
	call	v2p
	mov	QWORD PTR physical_address$4[rsp], rax

; 68   : 		if (physical_address != 0){

	cmp	QWORD PTR physical_address$4[rsp], 0
	je	SHORT $LN1@AuUnmapPro

; 69   : 			AuPmmngrFree((void*)physical_address);

	mov	rcx, QWORD PTR physical_address$4[rsp]
	call	AuPmmngrFree
$LN1@AuUnmapPro:

; 70   : 		}
; 71   : 	}

	jmp	$LN3@AuUnmapPro
$LN2@AuUnmapPro:

; 72   : }

	add	rsp, 120				; 00000078H
	ret	0
?AuUnmapProcess@@YAXPEAU_process_@@PEAU_thread_@@@Z ENDP ; AuUnmapProcess
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\exit.cpp
_TEXT	SEGMENT
t_id$ = 32
timer$ = 36
main_thr$ = 40
cr3$ = 48
proc$ = 80
?AuExitProcess@@YAXPEAU_process_@@@Z PROC		; AuExitProcess

; 197  : void AuExitProcess (process_t *proc) {

$LN4:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 198  : 	x64_cli ();

	call	x64_cli

; 199  : 
; 200  : 	thread_t* main_thr = proc->main_thread;

	mov	rax, QWORD PTR proc$[rsp]
	mov	rax, QWORD PTR [rax+2064]
	mov	QWORD PTR main_thr$[rsp], rax

; 201  : 	uint16_t t_id = main_thr->id;

	mov	rax, QWORD PTR main_thr$[rsp]
	movzx	eax, WORD PTR [rax+242]
	mov	WORD PTR t_id$[rsp], ax

; 202  : 
; 203  : 	uint64_t cr3 = main_thr->frame.cr3;

	mov	rax, QWORD PTR main_thr$[rsp]
	mov	rax, QWORD PTR [rax+192]
	mov	QWORD PTR cr3$[rsp], rax

; 204  : 
; 205  : 	/* Destroy the sound dsp entry */
; 206  : 	AuSoundDestroyDSP(t_id);

	movzx	ecx, WORD PTR t_id$[rsp]
	call	?AuSoundDestroyDSP@@YAXG@Z		; AuSoundDestroyDSP

; 207  : 
; 208  : 	/* Now find a timer entry for this thread */
; 209  : 	int timer = find_timer_id(t_id);

	movzx	ecx, WORD PTR t_id$[rsp]
	call	?find_timer_id@@YAHG@Z			; find_timer_id
	mov	DWORD PTR timer$[rsp], eax

; 210  : 
; 211  : 	if (timer != -1) 

	cmp	DWORD PTR timer$[rsp], -1
	je	SHORT $LN1@AuExitProc

; 212  : 		destroy_timer(timer);

	mov	ecx, DWORD PTR timer$[rsp]
	call	?destroy_timer@@YAXH@Z			; destroy_timer
$LN1@AuExitProc:

; 213  : 
; 214  : 	/* Destroy the opened pri_loop message box */
; 215  : 	pri_loop_destroy_by_id(t_id);

	movzx	ecx, WORD PTR t_id$[rsp]
	call	?pri_loop_destroy_by_id@@YAXG@Z		; pri_loop_destroy_by_id

; 216  : 
; 217  : 
; 218  : 	/* unallocate system libraries */
; 219  : 	AuUnallocSysLibs();

	call	?AuUnallocSysLibs@@YAXXZ		; AuUnallocSysLibs

; 220  : 
; 221  : 	/* destroy allocated memory */
; 222  : 	AuDestroyMemory(proc, main_thr);

	mov	rdx, QWORD PTR main_thr$[rsp]
	mov	rcx, QWORD PTR proc$[rsp]
	call	?AuDestroyMemory@@YAXPEAU_process_@@PEAU_thread_@@@Z ; AuDestroyMemory

; 223  : 	
; 224  : 	
; 225  : 	/* destroy all threads allocated */
; 226  : 	AuDestroyChildThreads(proc, main_thr);

	mov	rdx, QWORD PTR main_thr$[rsp]
	mov	rcx, QWORD PTR proc$[rsp]
	call	?AuDestroyChildThreads@@YAXPEAU_process_@@PEAU_thread_@@@Z ; AuDestroyChildThreads

; 227  : 
; 228  : 	AuDestroyFiles(proc, main_thr);

	mov	rdx, QWORD PTR main_thr$[rsp]
	mov	rcx, QWORD PTR proc$[rsp]
	call	?AuDestroyFiles@@YAXPEAU_process_@@PEAU_thread_@@@Z ; AuDestroyFiles

; 229  : 	
; 230  : 	/* remove the process from process 
; 231  : 	 * list
; 232  : 	 */
; 233  : 	
; 234  : 	free(main_thr->fx_state);

	mov	rax, QWORD PTR main_thr$[rsp]
	mov	rcx, QWORD PTR [rax+216]
	call	free

; 235  : 	task_delete (main_thr);

	mov	rcx, QWORD PTR main_thr$[rsp]
	call	?task_delete@@YAXPEAU_thread_@@@Z	; task_delete

; 236  : 	free(main_thr);

	mov	rcx, QWORD PTR main_thr$[rsp]
	call	free

; 237  : 
; 238  : 	free(proc->process_file);

	mov	rax, QWORD PTR proc$[rsp]
	mov	rcx, QWORD PTR [rax+2144]
	call	free

; 239  : 	remove_process (proc);

	mov	rcx, QWORD PTR proc$[rsp]
	call	?remove_process@@YAXPEAU_process_@@@Z	; remove_process

; 240  : 
; 241  : 	free_kstack((uint64_t*)cr3);

	mov	rcx, QWORD PTR cr3$[rsp]
	call	?free_kstack@@YAXPEA_K@Z		; free_kstack

; 242  : 	/* free the address space */
; 243  : 	AuPmmngrFree((void*)cr3);

	mov	rcx, QWORD PTR cr3$[rsp]
	call	AuPmmngrFree

; 244  : }

	add	rsp, 72					; 00000048H
	ret	0
?AuExitProcess@@YAXPEAU_process_@@@Z ENDP		; AuExitProcess
_TEXT	ENDS
END