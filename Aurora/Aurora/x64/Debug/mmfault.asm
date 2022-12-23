; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?AuHandlePageNotPresent@@YAX_K_NPEAX@Z		; AuHandlePageNotPresent
EXTRN	AuPmmngrAlloc:PROC
EXTRN	x64_cli:PROC
EXTRN	x64_read_cr2:PROC
EXTRN	AuMapPage:PROC
EXTRN	block_thread:PROC
EXTRN	get_current_thread:PROC
EXTRN	force_sched:PROC
EXTRN	?AuFindVMA@@YAPEAU_vma_area_@@_K@Z:PROC		; AuFindVMA
EXTRN	?fat32_read@@YA_KPEAU_vfs_node_@@PEA_K@Z:PROC	; fat32_read
pdata	SEGMENT
$pdata$?AuHandlePageNotPresent@@YAX_K_NPEAX@Z DD imagerel $LN10
	DD	imagerel $LN10+251
	DD	imagerel $unwind$?AuHandlePageNotPresent@@YAX_K_NPEAX@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?AuHandlePageNotPresent@@YAX_K_NPEAX@Z DD 011201H
	DD	0a212H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\mmngr\mmfault.cpp
_TEXT	SEGMENT
i$1 = 32
vm$ = 40
phys_addr$2 = 48
virtual_address$ = 56
frame$ = 64
vaddr$ = 96
user$ = 104
param$ = 112
?AuHandlePageNotPresent@@YAX_K_NPEAX@Z PROC		; AuHandlePageNotPresent

; 40   : void AuHandlePageNotPresent (uint64_t vaddr, bool user, void* param) {

$LN10:
	mov	QWORD PTR [rsp+24], r8
	mov	BYTE PTR [rsp+16], dl
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 88					; 00000058H

; 41   : 	x64_cli();

	call	x64_cli

; 42   : 	interrupt_stack_frame *frame = (interrupt_stack_frame*)param;

	mov	rax, QWORD PTR param$[rsp]
	mov	QWORD PTR frame$[rsp], rax

; 43   : 	void* virtual_address = (void*)x64_read_cr2();

	call	x64_read_cr2
	mov	QWORD PTR virtual_address$[rsp], rax

; 44   : 	if (!user) {

	movzx	eax, BYTE PTR user$[rsp]
	test	eax, eax
	jne	SHORT $LN7@AuHandlePa

; 45   : 		x64_cli();

	call	x64_cli

; 46   : 		//printf ("Kernel Panic!! Page fault \n");
; 47   : 		//printf ("Virtual address -> %x \n", virtual_address);
; 48   : 		//printf ("RIP ->%x \n", frame->rip);
; 49   : 		//printf ("Current thread -> %s \n", get_current_thread()->name);
; 50   : 		if (virtual_address == NULL)

	cmp	QWORD PTR virtual_address$[rsp], 0
	jne	SHORT $LN6@AuHandlePa

; 51   : 			block_thread (get_current_thread());

	call	get_current_thread
	mov	rcx, rax
	call	block_thread
$LN6@AuHandlePa:

; 52   : 		force_sched();

	call	force_sched
$LN7@AuHandlePa:

; 53   : 	}
; 54   : 	au_vm_area_t *vm = AuFindVMA(vaddr);

	mov	rcx, QWORD PTR vaddr$[rsp]
	call	?AuFindVMA@@YAPEAU_vma_area_@@_K@Z	; AuFindVMA
	mov	QWORD PTR vm$[rsp], rax

; 55   : 	if (vm == NULL){

	cmp	QWORD PTR vm$[rsp], 0
	jne	SHORT $LN5@AuHandlePa

; 56   : 		x64_cli();

	call	x64_cli

; 57   : 		//printf ("Page Fault -> 0x%x \n", vaddr);
; 58   : 		//printf ("RIP -> %x \n", frame->rip);
; 59   : 		//printf ("Current thread -> %s,id -> %d \n", get_current_thread()->name, get_current_thread()->id);
; 60   : 		block_thread (get_current_thread());

	call	get_current_thread
	mov	rcx, rax
	call	block_thread

; 61   : 		force_sched();

	call	force_sched

; 62   : 		return;

	jmp	SHORT $LN8@AuHandlePa
$LN5@AuHandlePa:

; 63   : 	}
; 64   : 
; 65   : 	for (int i = 0; i < vm->length; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN4@AuHandlePa
$LN3@AuHandlePa:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN4@AuHandlePa:
	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR vm$[rsp]
	cmp	rax, QWORD PTR [rcx+40]
	jae	SHORT $LN2@AuHandlePa

; 66   : 		void* phys_addr = AuPmmngrAlloc();

	call	AuPmmngrAlloc
	mov	QWORD PTR phys_addr$2[rsp], rax

; 67   : 		if (vm->file && vm->file->eof != 1) {

	mov	rax, QWORD PTR vm$[rsp]
	cmp	QWORD PTR [rax+24], 0
	je	SHORT $LN1@AuHandlePa
	mov	rax, QWORD PTR vm$[rsp]
	mov	rax, QWORD PTR [rax+24]
	movzx	eax, BYTE PTR [rax+36]
	cmp	eax, 1
	je	SHORT $LN1@AuHandlePa

; 68   : 			fat32_read(vm->file, (uint64_t*)phys_addr);

	mov	rdx, QWORD PTR phys_addr$2[rsp]
	mov	rax, QWORD PTR vm$[rsp]
	mov	rcx, QWORD PTR [rax+24]
	call	?fat32_read@@YA_KPEAU_vfs_node_@@PEA_K@Z ; fat32_read
$LN1@AuHandlePa:

; 69   : 		}
; 70   : 		AuMapPage((uint64_t)phys_addr, vaddr, PAGING_USER);

	mov	r8b, 4
	mov	rdx, QWORD PTR vaddr$[rsp]
	mov	rcx, QWORD PTR phys_addr$2[rsp]
	call	AuMapPage

; 71   : 	}

	jmp	SHORT $LN3@AuHandlePa
$LN2@AuHandlePa:
$LN8@AuHandlePa:

; 72   : }

	add	rsp, 88					; 00000058H
	ret	0
?AuHandlePageNotPresent@@YAX_K_NPEAX@Z ENDP		; AuHandlePageNotPresent
_TEXT	ENDS
END
