; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?map_shared_memory@@YAXG_K0@Z			; map_shared_memory
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	x64_cli:PROC
EXTRN	?pml4_index@@YA_K_K@Z:PROC			; pml4_index
EXTRN	?map_page@@YA_N_K0@Z:PROC			; map_page
EXTRN	?get_current_thread@@YAPEAU_thread_@@XZ:PROC	; get_current_thread
EXTRN	?thread_iterate_ready_list@@YAPEAU_thread_@@G@Z:PROC ; thread_iterate_ready_list
pdata	SEGMENT
$pdata$?map_shared_memory@@YAXG_K0@Z DD imagerel $LN9
	DD	imagerel $LN9+338
	DD	imagerel $unwind$?map_shared_memory@@YAXG_K0@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?map_shared_memory@@YAXG_K0@Z DD 011301H
	DD	0c213H
xdata	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\sysserv\sysmem.cpp
_TEXT	SEGMENT
i$1 = 32
i$2 = 36
t$ = 40
tv80 = 48
cr3$ = 56
tv65 = 64
current_cr3$ = 72
tv71 = 80
tv90 = 88
dest_id$ = 112
pos$ = 120
size$ = 128
?map_shared_memory@@YAXG_K0@Z PROC			; map_shared_memory

; 17   : void map_shared_memory (uint16_t dest_id,uint64_t pos, size_t size) {

$LN9:
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+16], rdx
	mov	WORD PTR [rsp+8], cx
	sub	rsp, 104				; 00000068H

; 18   : 	x64_cli ();

	call	x64_cli

; 19   : 
; 20   : 	for (int i = 0; i < size/4096; i++)

	mov	DWORD PTR i$2[rsp], 0
	jmp	SHORT $LN6@map_shared
$LN5@map_shared:
	mov	eax, DWORD PTR i$2[rsp]
	inc	eax
	mov	DWORD PTR i$2[rsp], eax
$LN6@map_shared:
	movsxd	rax, DWORD PTR i$2[rsp]
	mov	QWORD PTR tv65[rsp], rax
	xor	edx, edx
	mov	rax, QWORD PTR size$[rsp]
	mov	ecx, 4096				; 00001000H
	div	rcx
	mov	rcx, QWORD PTR tv65[rsp]
	cmp	rcx, rax
	jae	SHORT $LN4@map_shared

; 21   : 		map_page ((uint64_t)pmmngr_alloc(),pos + i * 4096);

	mov	eax, DWORD PTR i$2[rsp]
	imul	eax, 4096				; 00001000H
	cdqe
	mov	rcx, QWORD PTR pos$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	QWORD PTR tv71[rsp], rax
	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	rcx, QWORD PTR tv71[rsp]
	mov	rdx, rcx
	mov	rcx, rax
	call	?map_page@@YA_N_K0@Z			; map_page
	jmp	SHORT $LN5@map_shared
$LN4@map_shared:

; 22   : 
; 23   : 	thread_t* t = thread_iterate_ready_list (dest_id);

	movzx	ecx, WORD PTR dest_id$[rsp]
	call	?thread_iterate_ready_list@@YAPEAU_thread_@@G@Z ; thread_iterate_ready_list
	mov	QWORD PTR t$[rsp], rax

; 24   : 	uint64_t *cr3 = (uint64_t*)t->cr3;

	mov	rax, QWORD PTR t$[rsp]
	mov	rax, QWORD PTR [rax+192]
	mov	QWORD PTR cr3$[rsp], rax

; 25   : 	uint64_t *current_cr3 = (uint64_t*)get_current_thread()->cr3;

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	mov	rax, QWORD PTR [rax+192]
	mov	QWORD PTR current_cr3$[rsp], rax

; 26   : 	for (int i = 0; i < size / 4096; i++)

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@map_shared
$LN2@map_shared:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN3@map_shared:
	movsxd	rax, DWORD PTR i$1[rsp]
	mov	QWORD PTR tv80[rsp], rax
	xor	edx, edx
	mov	rax, QWORD PTR size$[rsp]
	mov	ecx, 4096				; 00001000H
	div	rcx
	mov	rcx, QWORD PTR tv80[rsp]
	cmp	rcx, rax
	jae	SHORT $LN1@map_shared

; 27   : 		cr3[pml4_index(pos + i * 4096)] = current_cr3[pml4_index(pos + i * 4096)];

	mov	eax, DWORD PTR i$1[rsp]
	imul	eax, 4096				; 00001000H
	cdqe
	mov	rcx, QWORD PTR pos$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	rcx, rax
	call	?pml4_index@@YA_K_K@Z			; pml4_index
	mov	QWORD PTR tv90[rsp], rax
	mov	ecx, DWORD PTR i$1[rsp]
	imul	ecx, 4096				; 00001000H
	movsxd	rcx, ecx
	mov	rdx, QWORD PTR pos$[rsp]
	add	rdx, rcx
	mov	rcx, rdx
	call	?pml4_index@@YA_K_K@Z			; pml4_index
	mov	rcx, QWORD PTR cr3$[rsp]
	mov	rdx, QWORD PTR current_cr3$[rsp]
	mov	r8, QWORD PTR tv90[rsp]
	mov	rdx, QWORD PTR [rdx+r8*8]
	mov	QWORD PTR [rcx+rax*8], rdx
	jmp	$LN2@map_shared
$LN1@map_shared:

; 28   : }

	add	rsp, 104				; 00000068H
	ret	0
?map_shared_memory@@YAXG_K0@Z ENDP			; map_shared_memory
_TEXT	ENDS
END
