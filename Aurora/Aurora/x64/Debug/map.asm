; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

CONST	SEGMENT
$SG3645	DB	'munmap called -> %x, length -> %d', 0aH, 00H
CONST	ENDS
PUBLIC	?map_memory@@YAPEAX_KIE@Z			; map_memory
PUBLIC	?unmap_memory@@YAXPEAXI@Z			; unmap_memory
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	x64_cli:PROC
EXTRN	?map_page@@YA_N_K0@Z:PROC			; map_page
EXTRN	?unmap_page@@YAX_K@Z:PROC			; unmap_page
EXTRN	?get_free_page@@YAPEA_K_K_N@Z:PROC		; get_free_page
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
EXTRN	?get_current_process@@YAPEAU_process_@@XZ:PROC	; get_current_process
pdata	SEGMENT
$pdata$?map_memory@@YAPEAX_KIE@Z DD imagerel $LN14
	DD	imagerel $LN14+353
	DD	imagerel $unwind$?map_memory@@YAPEAX_KIE@Z
$pdata$?unmap_memory@@YAXPEAXI@Z DD imagerel $LN8
	DD	imagerel $LN8+157
	DD	imagerel $unwind$?unmap_memory@@YAXPEAXI@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?map_memory@@YAPEAX_KIE@Z DD 011201H
	DD	0a212H
$unwind$?unmap_memory@@YAXPEAXI@Z DD 010d01H
	DD	0620dH
xdata	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\map.cpp
_TEXT	SEGMENT
i$1 = 32
address$ = 40
addr$ = 64
length$ = 72
?unmap_memory@@YAXPEAXI@Z PROC				; unmap_memory

; 74   : void unmap_memory (void* addr, uint32_t length) {

$LN8:
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 75   : 	x64_cli();

	call	x64_cli

; 76   : 	printf ("munmap called -> %x, length -> %d\n", addr, length);

	mov	r8d, DWORD PTR length$[rsp]
	mov	rdx, QWORD PTR addr$[rsp]
	lea	rcx, OFFSET FLAT:$SG3645
	call	?printf@@YAXPEBDZZ			; printf

; 77   : 	/*
; 78   : 	 * Before unmapping the object, we should get the object
; 79   : 	 * and write it to a file if object is not null
; 80   : 	 * but for now object manager is not implemented,
; 81   : 	 * kept for future use
; 82   : 	 */
; 83   : 
; 84   : 	uint64_t address = (uint64_t)addr;

	mov	rax, QWORD PTR addr$[rsp]
	mov	QWORD PTR address$[rsp], rax

; 85   : 
; 86   : 	if (length == 4096) 

	cmp	DWORD PTR length$[rsp], 4096		; 00001000H
	jne	SHORT $LN5@unmap_memo

; 87   : 		unmap_page (address);

	mov	rcx, QWORD PTR address$[rsp]
	call	?unmap_page@@YAX_K@Z			; unmap_page
$LN5@unmap_memo:

; 88   : 
; 89   : 	if (length > 4096) {

	cmp	DWORD PTR length$[rsp], 4096		; 00001000H
	jbe	SHORT $LN4@unmap_memo

; 90   : 		for (int i = 0; i < length / 4096; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@unmap_memo
$LN2@unmap_memo:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN3@unmap_memo:
	xor	edx, edx
	mov	eax, DWORD PTR length$[rsp]
	mov	ecx, 4096				; 00001000H
	div	ecx
	cmp	DWORD PTR i$1[rsp], eax
	jae	SHORT $LN1@unmap_memo

; 91   : 			unmap_page (address + i * 4096);

	mov	eax, DWORD PTR i$1[rsp]
	imul	eax, 4096				; 00001000H
	cdqe
	mov	rcx, QWORD PTR address$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	rcx, rax
	call	?unmap_page@@YAX_K@Z			; unmap_page

; 92   : 		}

	jmp	SHORT $LN2@unmap_memo
$LN1@unmap_memo:
$LN4@unmap_memo:

; 93   : 	}
; 94   : }

	add	rsp, 56					; 00000038H
	ret	0
?unmap_memory@@YAXPEAXI@Z ENDP				; unmap_memory
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\map.cpp
_TEXT	SEGMENT
user$ = 32
i$1 = 36
i$2 = 40
tv83 = 48
tv128 = 56
c_proc$ = 64
addr$ = 96
length$ = 104
attribute$ = 112
?map_memory@@YAPEAX_KIE@Z PROC				; map_memory

; 21   : void *map_memory (uint64_t addr, uint32_t length,uint8_t attribute) {

$LN14:
	mov	BYTE PTR [rsp+24], r8b
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 88					; 00000058H

; 22   : 	x64_cli();

	call	x64_cli

; 23   : 	process_t * c_proc = get_current_process();

	call	?get_current_process@@YAPEAU_process_@@XZ ; get_current_process
	mov	QWORD PTR c_proc$[rsp], rax

; 24   : 
; 25   : 	//!Attribute check
; 26   : 	bool user = false;

	mov	BYTE PTR user$[rsp], 0

; 27   : 	if (attribute & ATTRIBUTE_USER)

	movzx	eax, BYTE PTR attribute$[rsp]
	and	eax, 5
	test	eax, eax
	je	SHORT $LN11@map_memory

; 28   : 		user = true;

	mov	BYTE PTR user$[rsp], 1
$LN11@map_memory:

; 29   : 
; 30   : 	//! For more convenient, give a null to address parameter 
; 31   : 	//! cause, null parameter will cause map_memory to look for free
; 32   : 	//! memory in process's address space
; 33   : 	if (addr == NULL) {

	cmp	QWORD PTR addr$[rsp], 0
	jne	$LN10@map_memory

; 34   : 		addr = (uint64_t)get_free_page (length, user);

	mov	eax, DWORD PTR length$[rsp]
	movzx	edx, BYTE PTR user$[rsp]
	mov	ecx, eax
	call	?get_free_page@@YAPEA_K_K_N@Z		; get_free_page
	mov	QWORD PTR addr$[rsp], rax

; 35   : 		if (length == 4096) {

	cmp	DWORD PTR length$[rsp], 4096		; 00001000H
	jne	SHORT $LN9@map_memory

; 36   : 			map_page ((uint64_t)pmmngr_alloc(), addr);

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	rdx, QWORD PTR addr$[rsp]
	mov	rcx, rax
	call	?map_page@@YA_N_K0@Z			; map_page

; 37   : 			return (void*)addr;

	mov	rax, QWORD PTR addr$[rsp]
	jmp	$LN12@map_memory
$LN9@map_memory:

; 38   : 		}
; 39   : 
; 40   : 		for (int i = 0; i < length / 4096; i++)

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN8@map_memory
$LN7@map_memory:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN8@map_memory:
	xor	edx, edx
	mov	eax, DWORD PTR length$[rsp]
	mov	ecx, 4096				; 00001000H
	div	ecx
	cmp	DWORD PTR i$1[rsp], eax
	jae	SHORT $LN6@map_memory

; 41   : 				map_page ((uint64_t)pmmngr_alloc(),addr + i * 4096);

	mov	eax, DWORD PTR i$1[rsp]
	imul	eax, 4096				; 00001000H
	cdqe
	mov	rcx, QWORD PTR addr$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	QWORD PTR tv83[rsp], rax
	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	rcx, QWORD PTR tv83[rsp]
	mov	rdx, rcx
	mov	rcx, rax
	call	?map_page@@YA_N_K0@Z			; map_page
	jmp	SHORT $LN7@map_memory
$LN6@map_memory:

; 42   : 
; 43   : 
; 44   : 	} 
; 45   : 	//! use the given address to map a region
; 46   : 	//! TODO: Check if there's already a mapped region, and relocate the mapping
; 47   : 	else {

	jmp	SHORT $LN5@map_memory
$LN10@map_memory:

; 48   : 		if (length == 4096) {

	cmp	DWORD PTR length$[rsp], 4096		; 00001000H
	jne	SHORT $LN4@map_memory

; 49   : 			map_page ((uint64_t)pmmngr_alloc(), addr);

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	rdx, QWORD PTR addr$[rsp]
	mov	rcx, rax
	call	?map_page@@YA_N_K0@Z			; map_page

; 50   : 			return (void*)addr;

	mov	rax, QWORD PTR addr$[rsp]
	jmp	SHORT $LN12@map_memory
$LN4@map_memory:

; 51   : 		}
; 52   : 
; 53   : 		for (int i = 0; i < length / 4096; i++)

	mov	DWORD PTR i$2[rsp], 0
	jmp	SHORT $LN3@map_memory
$LN2@map_memory:
	mov	eax, DWORD PTR i$2[rsp]
	inc	eax
	mov	DWORD PTR i$2[rsp], eax
$LN3@map_memory:
	xor	edx, edx
	mov	eax, DWORD PTR length$[rsp]
	mov	ecx, 4096				; 00001000H
	div	ecx
	cmp	DWORD PTR i$2[rsp], eax
	jae	SHORT $LN1@map_memory

; 54   : 				map_page ((uint64_t)pmmngr_alloc(),addr + i * 4096);

	mov	eax, DWORD PTR i$2[rsp]
	imul	eax, 4096				; 00001000H
	cdqe
	mov	rcx, QWORD PTR addr$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	QWORD PTR tv128[rsp], rax
	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	rcx, QWORD PTR tv128[rsp]
	mov	rdx, rcx
	mov	rcx, rax
	call	?map_page@@YA_N_K0@Z			; map_page
	jmp	SHORT $LN2@map_memory
$LN1@map_memory:
$LN5@map_memory:

; 55   : 	}
; 56   : 
; 57   : 	//! MAP_GLOBAL flag will cause the map_memory to map the address
; 58   : 	//! in its child process, for now its not implemented
; 59   : 
; 60   : 	//if (attribute & MAP_GLOBAL) {
; 61   : 	//	process_map_addresses (addr,length,(uint64_t*)c_proc->thread_data_pointer->cr3,c_proc);
; 62   : 	//}
; 63   : 	
; 64   : 	//! return the mapped address
; 65   : 	return (void*)addr;

	mov	rax, QWORD PTR addr$[rsp]
$LN12@map_memory:

; 66   : }

	add	rsp, 88					; 00000058H
	ret	0
?map_memory@@YAPEAX_KIE@Z ENDP				; map_memory
_TEXT	ENDS
END
