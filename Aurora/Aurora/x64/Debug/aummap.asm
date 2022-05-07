; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?au_mmap@@YAPEAXPEAX_KHHH1@Z			; au_mmap
EXTRN	AuPmmngrAlloc:PROC
EXTRN	x64_cli:PROC
EXTRN	AuMapPage:PROC
EXTRN	AuGetFreePage:PROC
EXTRN	malloc:PROC
EXTRN	get_current_thread:PROC
EXTRN	?AuInsertVMArea@@YAXPEAU_process_@@PEAU_vma_area_@@@Z:PROC ; AuInsertVMArea
EXTRN	?get_current_process@@YAPEAU_process_@@XZ:PROC	; get_current_process
pdata	SEGMENT
$pdata$?au_mmap@@YAPEAXPEAX_KHHH1@Z DD imagerel $LN11
	DD	imagerel $LN11+425
	DD	imagerel $unwind$?au_mmap@@YAPEAXPEAX_KHHH1@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?au_mmap@@YAPEAXPEAX_KHHH1@Z DD 011801H
	DD	0c218H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\mmngr\aummap.cpp
_TEXT	SEGMENT
i$1 = 32
vma$ = 40
size$ = 48
vaddr_start$ = 56
file$ = 64
proc$ = 72
tv134 = 80
address$ = 112
length$ = 120
protect$ = 128
flags$ = 136
filedesc$ = 144
offset$ = 152
?au_mmap@@YAPEAXPEAX_KHHH1@Z PROC			; au_mmap

; 47   : void* au_mmap (void* address, size_t length, int protect, int flags, int filedesc, uint64_t offset) {

$LN11:
	mov	DWORD PTR [rsp+32], r9d
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 104				; 00000068H

; 48   : 	/* this is a system call, so make sure it is atomic */
; 49   : 	x64_cli();

	call	x64_cli

; 50   : 
; 51   : 	process_t *proc = get_current_process();

	call	?get_current_process@@YAPEAU_process_@@XZ ; get_current_process
	mov	QWORD PTR proc$[rsp], rax

; 52   : 	uint64_t vaddr_start = 0;

	mov	QWORD PTR vaddr_start$[rsp], 0

; 53   : 
; 54   : 	/* Get the starting address */
; 55   : 	if (address == NULL) {

	cmp	QWORD PTR address$[rsp], 0
	jne	SHORT $LN8@au_mmap

; 56   : 		address = AuGetFreePage(0,true, 0);

	xor	r8d, r8d
	mov	dl, 1
	xor	ecx, ecx
	call	AuGetFreePage
	mov	QWORD PTR address$[rsp], rax

; 57   : 		vaddr_start = (uint64_t)address;

	mov	rax, QWORD PTR address$[rsp]
	mov	QWORD PTR vaddr_start$[rsp], rax

; 58   : 	}else 

	jmp	SHORT $LN7@au_mmap
$LN8@au_mmap:

; 59   : 		vaddr_start = (uint64_t)address;

	mov	rax, QWORD PTR address$[rsp]
	mov	QWORD PTR vaddr_start$[rsp], rax
$LN7@au_mmap:

; 60   : 
; 61   : 	vfs_node_t *file = NULL;

	mov	QWORD PTR file$[rsp], 0

; 62   : 	if (filedesc) {

	cmp	DWORD PTR filedesc$[rsp], 0
	je	SHORT $LN6@au_mmap

; 63   : 		file = get_current_thread()->fd[filedesc];

	call	get_current_thread
	movsxd	rcx, DWORD PTR filedesc$[rsp]
	mov	rax, QWORD PTR [rax+rcx*8+776]
	mov	QWORD PTR file$[rsp], rax
$LN6@au_mmap:

; 64   : 	}
; 65   : 
; 66   : 	uint64_t size = length / 4096;

	xor	edx, edx
	mov	rax, QWORD PTR length$[rsp]
	mov	ecx, 4096				; 00001000H
	div	rcx
	mov	QWORD PTR size$[rsp], rax

; 67   : 	
; 68   : 	if (size == 0)

	cmp	QWORD PTR size$[rsp], 0
	jne	SHORT $LN5@au_mmap

; 69   : 		size = 1;

	mov	QWORD PTR size$[rsp], 1
$LN5@au_mmap:

; 70   : 	
; 71   : 	au_vm_area_t *vma = (au_vm_area_t*)malloc(sizeof(au_vm_area_t));

	mov	ecx, 72					; 00000048H
	call	malloc
	mov	QWORD PTR vma$[rsp], rax

; 72   : 	vma->start = vaddr_start;

	mov	rax, QWORD PTR vma$[rsp]
	mov	rcx, QWORD PTR vaddr_start$[rsp]
	mov	QWORD PTR [rax], rcx

; 73   : 	vma->end = vma->start + (size * 0x1000);

	mov	rax, QWORD PTR size$[rsp]
	imul	rax, 4096				; 00001000H
	mov	rcx, QWORD PTR vma$[rsp]
	add	rax, QWORD PTR [rcx]
	mov	rcx, QWORD PTR vma$[rsp]
	mov	QWORD PTR [rcx+8], rax

; 74   : 	vma->file = file;

	mov	rax, QWORD PTR vma$[rsp]
	mov	rcx, QWORD PTR file$[rsp]
	mov	QWORD PTR [rax+24], rcx

; 75   : 	vma->offset = offset;

	mov	rax, QWORD PTR vma$[rsp]
	mov	rcx, QWORD PTR offset$[rsp]
	mov	QWORD PTR [rax+32], rcx

; 76   : 	vma->prot_flags = protect;

	mov	rax, QWORD PTR vma$[rsp]
	movzx	ecx, WORD PTR protect$[rsp]
	mov	WORD PTR [rax+16], cx

; 77   : 	vma->type = VM_TYPE_RESOURCE;

	mov	rax, QWORD PTR vma$[rsp]
	mov	BYTE PTR [rax+48], 5

; 78   : 	vma->length = size;

	mov	rax, QWORD PTR vma$[rsp]
	mov	rcx, QWORD PTR size$[rsp]
	mov	QWORD PTR [rax+40], rcx

; 79   : 	AuInsertVMArea(proc, vma);

	mov	rdx, QWORD PTR vma$[rsp]
	mov	rcx, QWORD PTR proc$[rsp]
	call	?AuInsertVMArea@@YAXPEAU_process_@@PEAU_vma_area_@@@Z ; AuInsertVMArea

; 80   : 
; 81   : 	/* Map it quicky */
; 82   : 	if (vma->file == NULL)

	mov	rax, QWORD PTR vma$[rsp]
	cmp	QWORD PTR [rax+24], 0
	jne	SHORT $LN4@au_mmap

; 83   : 		for (int i = 0; i < size; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@au_mmap
$LN2@au_mmap:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN3@au_mmap:
	movsxd	rax, DWORD PTR i$1[rsp]
	cmp	rax, QWORD PTR size$[rsp]
	jae	SHORT $LN1@au_mmap

; 84   : 			AuMapPage((uint64_t)AuPmmngrAlloc(), vma->start + i * 4096, PAGING_USER);

	mov	eax, DWORD PTR i$1[rsp]
	imul	eax, 4096				; 00001000H
	cdqe
	mov	rcx, QWORD PTR vma$[rsp]
	add	rax, QWORD PTR [rcx]
	mov	QWORD PTR tv134[rsp], rax
	call	AuPmmngrAlloc
	mov	r8b, 4
	mov	rcx, QWORD PTR tv134[rsp]
	mov	rdx, rcx
	mov	rcx, rax
	call	AuMapPage

; 85   : 		}

	jmp	SHORT $LN2@au_mmap
$LN1@au_mmap:
$LN4@au_mmap:

; 86   : 	return address;

	mov	rax, QWORD PTR address$[rsp]

; 87   : }

	add	rsp, 104				; 00000068H
	ret	0
?au_mmap@@YAPEAXPEAX_KHHH1@Z ENDP			; au_mmap
_TEXT	ENDS
END
