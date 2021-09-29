; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?index@@3IA					; index
_BSS	SEGMENT
?index@@3IA DD	01H DUP (?)				; index
_BSS	ENDS
PUBLIC	?allocate_kstack@@YA_KPEA_K@Z			; allocate_kstack
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	?map_page_ex@@YA_NPEA_K_K1@Z:PROC		; map_page_ex
pdata	SEGMENT
$pdata$?allocate_kstack@@YA_KPEA_K@Z DD imagerel $LN6
	DD	imagerel $LN6+125
	DD	imagerel $unwind$?allocate_kstack@@YA_KPEA_K@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?allocate_kstack@@YA_KPEA_K@Z DD 010901H
	DD	08209H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\kstack.cpp
_TEXT	SEGMENT
i$1 = 32
location$ = 40
tv69 = 48
cr3$ = 80
?allocate_kstack@@YA_KPEA_K@Z PROC			; allocate_kstack

; 15   : extern uint64_t allocate_kstack (uint64_t *cr3) {

$LN6:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 16   : 
; 17   : 	uint64_t location = KSTACK_START ; //+ index;

	mov	rax, -5497558138880			; fffffb0000000000H
	mov	QWORD PTR location$[rsp], rax

; 18   : 	for (int i = 0; i < (2*1024*1024)/4096; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@allocate_k
$LN2@allocate_k:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN3@allocate_k:
	cmp	DWORD PTR i$1[rsp], 512			; 00000200H
	jge	SHORT $LN1@allocate_k

; 19   : 		map_page_ex (cr3,(uint64_t)pmmngr_alloc(),location + i * 4096);

	mov	eax, DWORD PTR i$1[rsp]
	imul	eax, 4096				; 00001000H
	cdqe
	mov	rcx, QWORD PTR location$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	QWORD PTR tv69[rsp], rax
	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	rcx, QWORD PTR tv69[rsp]
	mov	r8, rcx
	mov	rdx, rax
	mov	rcx, QWORD PTR cr3$[rsp]
	call	?map_page_ex@@YA_NPEA_K_K1@Z		; map_page_ex

; 20   : 	}

	jmp	SHORT $LN2@allocate_k
$LN1@allocate_k:

; 21   : 
; 22   : 	//index += 8192;
; 23   : 	return (KSTACK_START + 2*1024*1024);

	mov	rax, -5497556041728			; fffffb0000200000H

; 24   : }

	add	rsp, 72					; 00000048H
	ret	0
?allocate_kstack@@YA_KPEA_K@Z ENDP			; allocate_kstack
_TEXT	ENDS
END
