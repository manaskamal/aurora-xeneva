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
EXTRN	?map_page_ex@@YA_NPEA_K_K1E@Z:PROC		; map_page_ex
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
p$2 = 48
cr3$ = 80
?allocate_kstack@@YA_KPEA_K@Z PROC			; allocate_kstack

; 16   : extern uint64_t allocate_kstack (uint64_t *cr3) {

$LN6:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 17   : 
; 18   : 	uint64_t location = KSTACK_START; //+ index;

	mov	rax, -5497558138880			; fffffb0000000000H
	mov	QWORD PTR location$[rsp], rax

; 19   : 	for (int i = 0; i < (2*1024*1024)/4096; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@allocate_k
$LN2@allocate_k:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN3@allocate_k:
	cmp	DWORD PTR i$1[rsp], 512			; 00000200H
	jge	SHORT $LN1@allocate_k

; 20   : 		void* p = pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR p$2[rsp], rax

; 21   : 		map_page_ex (cr3,(uint64_t)p,location + i * 4096, 0);

	mov	eax, DWORD PTR i$1[rsp]
	imul	eax, 4096				; 00001000H
	cdqe
	mov	rcx, QWORD PTR location$[rsp]
	add	rcx, rax
	mov	rax, rcx
	xor	r9d, r9d
	mov	r8, rax
	mov	rdx, QWORD PTR p$2[rsp]
	mov	rcx, QWORD PTR cr3$[rsp]
	call	?map_page_ex@@YA_NPEA_K_K1E@Z		; map_page_ex

; 22   : 	}

	jmp	SHORT $LN2@allocate_k
$LN1@allocate_k:

; 23   : 	//index += 2*1024*1024;
; 24   : 	return (KSTACK_START + 2*1024*1024);

	mov	rax, -5497556041728			; fffffb0000200000H

; 25   : }

	add	rsp, 72					; 00000048H
	ret	0
?allocate_kstack@@YA_KPEA_K@Z ENDP			; allocate_kstack
_TEXT	ENDS
END
