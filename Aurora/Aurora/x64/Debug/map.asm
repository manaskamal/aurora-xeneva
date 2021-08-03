; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

CONST	SEGMENT
$SG3001	DB	'MM1.txt', 00H
CONST	ENDS
PUBLIC	?map_memory@@YAPEAX_KIEE@Z			; map_memory
PUBLIC	?unmap_memory@@YAXPEAXI@Z			; unmap_memory
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	?map_page@@YA_N_K0@Z:PROC			; map_page
EXTRN	?get_free_page@@YAPEA_K_K@Z:PROC		; get_free_page
EXTRN	?fat32_create_file@@YAIPEADPEAEI@Z:PROC		; fat32_create_file
pdata	SEGMENT
$pdata$?map_memory@@YAPEAX_KIEE@Z DD imagerel $LN8
	DD	imagerel $LN8+186
	DD	imagerel $unwind$?map_memory@@YAPEAX_KIEE@Z
$pdata$?unmap_memory@@YAXPEAXI@Z DD imagerel $LN3
	DD	imagerel $LN3+50
	DD	imagerel $unwind$?unmap_memory@@YAXPEAXI@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?map_memory@@YAPEAX_KIEE@Z DD 011701H
	DD	06217H
$unwind$?unmap_memory@@YAXPEAXI@Z DD 010d01H
	DD	0620dH
xdata	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\map.cpp
_TEXT	SEGMENT
buffer$ = 32
addr$ = 64
length$ = 72
?unmap_memory@@YAXPEAXI@Z PROC				; unmap_memory

; 30   : void unmap_memory (void* addr, uint32_t length) {

$LN3:
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 31   : 	unsigned char* buffer = (unsigned char*)addr;

	mov	rax, QWORD PTR addr$[rsp]
	mov	QWORD PTR buffer$[rsp], rax

; 32   : 	fat32_create_file ("MM1.txt",buffer, length);

	mov	r8d, DWORD PTR length$[rsp]
	mov	rdx, QWORD PTR buffer$[rsp]
	lea	rcx, OFFSET FLAT:$SG3001
	call	?fat32_create_file@@YAIPEADPEAEI@Z	; fat32_create_file

; 33   : 
; 34   : 	/*if (length == 4096) 
; 35   : 		unmap_page ((uint64_t)addr);
; 36   : 	else if (length > 4096) {
; 37   : 		for (int i = 0; i < length / 4096; i++) {
; 38   : 			unmap_page ((uint64_t)addr + i * 4096);
; 39   : 		}
; 40   : 	}*/
; 41   : }

	add	rsp, 56					; 00000038H
	ret	0
?unmap_memory@@YAXPEAXI@Z ENDP				; unmap_memory
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\map.cpp
_TEXT	SEGMENT
i$1 = 32
tv78 = 40
addr$ = 64
length$ = 72
map_type$ = 80
attribute$ = 88
?map_memory@@YAPEAX_KIEE@Z PROC				; map_memory

; 16   : void *map_memory (uint64_t addr, uint32_t length, uint8_t map_type, uint8_t attribute) {

$LN8:
	mov	BYTE PTR [rsp+32], r9b
	mov	BYTE PTR [rsp+24], r8b
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 17   : 	if (addr == NULL) {

	cmp	QWORD PTR addr$[rsp], 0
	jne	$LN5@map_memory

; 18   : 		addr = (uint64_t)get_free_page (length);

	mov	eax, DWORD PTR length$[rsp]
	mov	ecx, eax
	call	?get_free_page@@YAPEA_K_K@Z		; get_free_page
	mov	QWORD PTR addr$[rsp], rax

; 19   : 		if (length == 4096) {

	cmp	DWORD PTR length$[rsp], 4096		; 00001000H
	jne	SHORT $LN4@map_memory

; 20   : 			map_page ((uint64_t)pmmngr_alloc(), addr);

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	rdx, QWORD PTR addr$[rsp]
	mov	rcx, rax
	call	?map_page@@YA_N_K0@Z			; map_page

; 21   : 			return (void*)addr;

	mov	rax, QWORD PTR addr$[rsp]
	jmp	SHORT $LN6@map_memory
$LN4@map_memory:

; 22   : 		}
; 23   : 
; 24   : 		for (int i = 0; i < length / 4096; i++)

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@map_memory
$LN2@map_memory:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN3@map_memory:
	xor	edx, edx
	mov	eax, DWORD PTR length$[rsp]
	mov	ecx, 4096				; 00001000H
	div	ecx
	cmp	DWORD PTR i$1[rsp], eax
	jae	SHORT $LN1@map_memory

; 25   : 				map_page ((uint64_t)pmmngr_alloc(),addr + i * 4096);

	mov	eax, DWORD PTR i$1[rsp]
	imul	eax, 4096				; 00001000H
	cdqe
	mov	rcx, QWORD PTR addr$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	QWORD PTR tv78[rsp], rax
	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	rcx, QWORD PTR tv78[rsp]
	mov	rdx, rcx
	mov	rcx, rax
	call	?map_page@@YA_N_K0@Z			; map_page
	jmp	SHORT $LN2@map_memory
$LN1@map_memory:
$LN5@map_memory:

; 26   : 	}
; 27   : 	return (void*)addr;

	mov	rax, QWORD PTR addr$[rsp]
$LN6@map_memory:

; 28   : }

	add	rsp, 56					; 00000038H
	ret	0
?map_memory@@YAPEAX_KIEE@Z ENDP				; map_memory
_TEXT	ENDS
END
