; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?first_block@@3PEAU_meta_data_@@EA		; first_block
PUBLIC	?last_block@@3PEAU_meta_data_@@EA		; last_block
PUBLIC	?last_mark@@3PEAEEA				; last_mark
_BSS	SEGMENT
?first_block@@3PEAU_meta_data_@@EA DQ 01H DUP (?)	; first_block
?last_block@@3PEAU_meta_data_@@EA DQ 01H DUP (?)	; last_block
?last_mark@@3PEAEEA DQ 01H DUP (?)			; last_mark
_BSS	ENDS
CONST	SEGMENT
$SG3134	DB	'Returning address -> %x ', 0dH, 0aH, 00H
	ORG $+5
$SG3176	DB	'*****Requesting page -> %x ', 0dH, 0aH, 00H
CONST	ENDS
PUBLIC	?AuHeapInitialize@@YAXXZ			; AuHeapInitialize
PUBLIC	?au_request_page@@YAPEA_KH@Z			; au_request_page
PUBLIC	?au_free_page@@YAXPEAXH@Z			; au_free_page
PUBLIC	malloc
PUBLIC	free
PUBLIC	?au_split_block@@YAHPEAU_meta_data_@@_K@Z	; au_split_block
PUBLIC	?au_expand_kmalloc@@YAX_K@Z			; au_expand_kmalloc
PUBLIC	?merge_forward@@YAXPEAU_meta_data_@@@Z		; merge_forward
PUBLIC	?merge_backward@@YAXPEAU_meta_data_@@@Z		; merge_backward
PUBLIC	?krealloc@@YAPEAXPEAX_K@Z			; krealloc
PUBLIC	?kcalloc@@YAPEAX_K0@Z				; kcalloc
EXTRN	memset:PROC
EXTRN	memcpy:PROC
EXTRN	AuPmmngrAlloc:PROC
EXTRN	AuMapPage:PROC
EXTRN	AuGetFreePage:PROC
EXTRN	AuFreePages:PROC
EXTRN	?_debug_print_@@YAXPEADZZ:PROC			; _debug_print_
pdata	SEGMENT
$pdata$?AuHeapInitialize@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+173
	DD	imagerel $unwind$?AuHeapInitialize@@YAXXZ
$pdata$?au_request_page@@YAPEA_KH@Z DD imagerel $LN6
	DD	imagerel $LN6+152
	DD	imagerel $unwind$?au_request_page@@YAPEA_KH@Z
$pdata$?au_free_page@@YAXPEAXH@Z DD imagerel $LN3
	DD	imagerel $LN3+38
	DD	imagerel $unwind$?au_free_page@@YAXPEAXH@Z
$pdata$malloc DD imagerel $LN11
	DD	imagerel $LN11+256
	DD	imagerel $unwind$malloc
$pdata$free DD	imagerel $LN3
	DD	imagerel $LN3+67
	DD	imagerel $unwind$free
$pdata$?au_split_block@@YAHPEAU_meta_data_@@_K@Z DD imagerel $LN7
	DD	imagerel $LN7+289
	DD	imagerel $unwind$?au_split_block@@YAHPEAU_meta_data_@@_K@Z
$pdata$?au_expand_kmalloc@@YAX_K@Z DD imagerel $LN5
	DD	imagerel $LN5+335
	DD	imagerel $unwind$?au_expand_kmalloc@@YAX_K@Z
$pdata$?merge_backward@@YAXPEAU_meta_data_@@@Z DD imagerel $LN4
	DD	imagerel $LN4+57
	DD	imagerel $unwind$?merge_backward@@YAXPEAU_meta_data_@@@Z
$pdata$?krealloc@@YAPEAXPEAX_K@Z DD imagerel $LN4
	DD	imagerel $LN4+77
	DD	imagerel $unwind$?krealloc@@YAPEAXPEAX_K@Z
$pdata$?kcalloc@@YAPEAX_K0@Z DD imagerel $LN4
	DD	imagerel $LN4+80
	DD	imagerel $unwind$?kcalloc@@YAPEAX_K0@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?AuHeapInitialize@@YAXXZ DD 010401H
	DD	08204H
$unwind$?au_request_page@@YAPEA_KH@Z DD 010801H
	DD	08208H
$unwind$?au_free_page@@YAXPEAXH@Z DD 010d01H
	DD	0420dH
$unwind$malloc DD 010901H
	DD	06209H
$unwind$free DD	010901H
	DD	06209H
$unwind$?au_split_block@@YAHPEAU_meta_data_@@_K@Z DD 010e01H
	DD	0420eH
$unwind$?au_expand_kmalloc@@YAX_K@Z DD 010901H
	DD	0a209H
$unwind$?merge_backward@@YAXPEAU_meta_data_@@@Z DD 010901H
	DD	04209H
$unwind$?krealloc@@YAPEAXPEAX_K@Z DD 010e01H
	DD	0620eH
$unwind$?kcalloc@@YAPEAX_K0@Z DD 010e01H
	DD	0620eH
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\kheap.cpp
_TEXT	SEGMENT
ptr$ = 32
total$ = 40
n_item$ = 64
size$ = 72
?kcalloc@@YAPEAX_K0@Z PROC				; kcalloc

; 242  : void* kcalloc(size_t n_item, size_t size) {

$LN4:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 243  : 	size_t total = n_item * size;

	mov	rax, QWORD PTR n_item$[rsp]
	imul	rax, QWORD PTR size$[rsp]
	mov	QWORD PTR total$[rsp], rax

; 244  : 
; 245  : 	void* ptr = malloc(total);

	mov	rcx, QWORD PTR total$[rsp]
	call	malloc
	mov	QWORD PTR ptr$[rsp], rax

; 246  : 	if (ptr)

	cmp	QWORD PTR ptr$[rsp], 0
	je	SHORT $LN1@kcalloc

; 247  : 		memset(ptr, 0, total);

	mov	r8d, DWORD PTR total$[rsp]
	xor	edx, edx
	mov	rcx, QWORD PTR ptr$[rsp]
	call	memset
$LN1@kcalloc:

; 248  : 	return ptr;

	mov	rax, QWORD PTR ptr$[rsp]

; 249  : }

	add	rsp, 56					; 00000038H
	ret	0
?kcalloc@@YAPEAX_K0@Z ENDP				; kcalloc
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\kheap.cpp
_TEXT	SEGMENT
result$ = 32
ptr$ = 64
new_size$ = 72
?krealloc@@YAPEAXPEAX_K@Z PROC				; krealloc

; 224  : void* krealloc(void* ptr, size_t new_size) {

$LN4:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 225  : 	void* result = malloc(new_size);

	mov	rcx, QWORD PTR new_size$[rsp]
	call	malloc
	mov	QWORD PTR result$[rsp], rax

; 226  : 	if (ptr) {

	cmp	QWORD PTR ptr$[rsp], 0
	je	SHORT $LN1@krealloc

; 227  : 		/* here we can check the size difference
; 228  : 		 * of new_size and old size from internal
; 229  : 		 * data structure of kmalloc */
; 230  : 		memcpy(result, ptr, new_size);

	mov	r8d, DWORD PTR new_size$[rsp]
	mov	rdx, QWORD PTR ptr$[rsp]
	mov	rcx, QWORD PTR result$[rsp]
	call	memcpy
$LN1@krealloc:

; 231  : 	}
; 232  : 
; 233  : 	free(ptr);

	mov	rcx, QWORD PTR ptr$[rsp]
	call	free

; 234  : 	return result;

	mov	rax, QWORD PTR result$[rsp]

; 235  : }

	add	rsp, 56					; 00000038H
	ret	0
?krealloc@@YAPEAXPEAX_K@Z ENDP				; krealloc
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\kheap.cpp
_TEXT	SEGMENT
meta$ = 48
?merge_backward@@YAXPEAU_meta_data_@@@Z PROC		; merge_backward

; 201  : void merge_backward (meta_data_t* meta) {

$LN4:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 202  : 	if (meta->prev != NULL && meta->prev->free)

	mov	rax, QWORD PTR meta$[rsp]
	cmp	QWORD PTR [rax+32], 0
	je	SHORT $LN1@merge_back
	mov	rax, QWORD PTR meta$[rsp]
	mov	rax, QWORD PTR [rax+32]
	movzx	eax, BYTE PTR [rax+16]
	test	eax, eax
	je	SHORT $LN1@merge_back

; 203  : 		merge_forward(meta->prev);

	mov	rax, QWORD PTR meta$[rsp]
	mov	rcx, QWORD PTR [rax+32]
	call	?merge_forward@@YAXPEAU_meta_data_@@@Z	; merge_forward
$LN1@merge_back:

; 204  : }

	add	rsp, 40					; 00000028H
	ret	0
?merge_backward@@YAXPEAU_meta_data_@@@Z ENDP		; merge_backward
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\kheap.cpp
_TEXT	SEGMENT
meta$ = 8
?merge_forward@@YAXPEAU_meta_data_@@@Z PROC		; merge_forward

; 175  : void merge_forward(meta_data_t *meta) {

	mov	QWORD PTR [rsp+8], rcx

; 176  : 	if (meta->next == NULL) 

	mov	rax, QWORD PTR meta$[rsp]
	cmp	QWORD PTR [rax+24], 0
	jne	SHORT $LN5@merge_forw

; 177  : 		return;

	jmp	$LN6@merge_forw
$LN5@merge_forw:

; 178  : 	if (!meta->next->free)

	mov	rax, QWORD PTR meta$[rsp]
	mov	rax, QWORD PTR [rax+24]
	movzx	eax, BYTE PTR [rax+16]
	test	eax, eax
	jne	SHORT $LN4@merge_forw

; 179  : 		return;

	jmp	$LN6@merge_forw
$LN4@merge_forw:

; 180  : 
; 181  : 	/* Corrupted meta block */
; 182  : 	if (meta->next->size <= sizeof(meta_data_t))

	mov	rax, QWORD PTR meta$[rsp]
	mov	rax, QWORD PTR [rax+24]
	cmp	QWORD PTR [rax+8], 40			; 00000028H
	ja	SHORT $LN3@merge_forw

; 183  : 		return;

	jmp	$LN6@merge_forw
$LN3@merge_forw:

; 184  : 
; 185  : 	if (last_block == meta->next)

	mov	rax, QWORD PTR meta$[rsp]
	mov	rax, QWORD PTR [rax+24]
	cmp	QWORD PTR ?last_block@@3PEAU_meta_data_@@EA, rax ; last_block
	jne	SHORT $LN2@merge_forw

; 186  : 		last_block = meta;

	mov	rax, QWORD PTR meta$[rsp]
	mov	QWORD PTR ?last_block@@3PEAU_meta_data_@@EA, rax ; last_block
$LN2@merge_forw:

; 187  : 
; 188  : 	meta->size += meta->size + meta->next->size;

	mov	rax, QWORD PTR meta$[rsp]
	mov	rax, QWORD PTR [rax+24]
	mov	rcx, QWORD PTR meta$[rsp]
	mov	rcx, QWORD PTR [rcx+8]
	add	rcx, QWORD PTR [rax+8]
	mov	rax, rcx
	mov	rcx, QWORD PTR meta$[rsp]
	add	rax, QWORD PTR [rcx+8]
	mov	rcx, QWORD PTR meta$[rsp]
	mov	QWORD PTR [rcx+8], rax

; 189  : 	
; 190  : 	if (meta->next->next != NULL)

	mov	rax, QWORD PTR meta$[rsp]
	mov	rax, QWORD PTR [rax+24]
	cmp	QWORD PTR [rax+24], 0
	je	SHORT $LN1@merge_forw

; 191  : 		meta->next->next->prev = meta;

	mov	rax, QWORD PTR meta$[rsp]
	mov	rax, QWORD PTR [rax+24]
	mov	rax, QWORD PTR [rax+24]
	mov	rcx, QWORD PTR meta$[rsp]
	mov	QWORD PTR [rax+32], rcx
$LN1@merge_forw:

; 192  : 
; 193  : 	meta->next = meta->next->next;

	mov	rax, QWORD PTR meta$[rsp]
	mov	rax, QWORD PTR [rax+24]
	mov	rcx, QWORD PTR meta$[rsp]
	mov	rax, QWORD PTR [rax+24]
	mov	QWORD PTR [rcx+24], rax
$LN6@merge_forw:

; 194  : }

	fatret	0
?merge_forward@@YAXPEAU_meta_data_@@@Z ENDP		; merge_forward
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\kheap.cpp
_TEXT	SEGMENT
meta$ = 32
req_pages$ = 40
page$ = 48
desc_addr$ = 56
lm$ = 64
req_size$ = 96
?au_expand_kmalloc@@YAX_K@Z PROC			; au_expand_kmalloc

; 94   : void au_expand_kmalloc(size_t req_size) {

$LN5:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 88					; 00000058H

; 95   : 	size_t req_pages = 1;

	mov	QWORD PTR req_pages$[rsp], 1

; 96   : 	if (req_size >= 4096)

	cmp	QWORD PTR req_size$[rsp], 4096		; 00001000H
	jb	SHORT $LN2@au_expand_

; 97   : 		req_pages = (req_size + sizeof(meta_data_t)) / 4096 + 1;

	mov	rax, QWORD PTR req_size$[rsp]
	add	rax, 40					; 00000028H
	xor	edx, edx
	mov	ecx, 4096				; 00001000H
	div	rcx
	inc	rax
	mov	QWORD PTR req_pages$[rsp], rax
$LN2@au_expand_:

; 98   : 
; 99   : 	void* page = au_request_page(req_pages);

	mov	ecx, DWORD PTR req_pages$[rsp]
	call	?au_request_page@@YAPEA_KH@Z		; au_request_page
	mov	QWORD PTR page$[rsp], rax

; 100  : 	uint8_t* desc_addr = (uint8_t*)page;

	mov	rax, QWORD PTR page$[rsp]
	mov	QWORD PTR desc_addr$[rsp], rax

; 101  : 	/* setup the first meta data block */
; 102  : 	meta_data_t *meta = (meta_data_t*)desc_addr;

	mov	rax, QWORD PTR desc_addr$[rsp]
	mov	QWORD PTR meta$[rsp], rax

; 103  : 	meta->free = true;

	mov	rax, QWORD PTR meta$[rsp]
	mov	BYTE PTR [rax+16], 1

; 104  : 	meta->next = NULL;

	mov	rax, QWORD PTR meta$[rsp]
	mov	QWORD PTR [rax+24], 0

; 105  : 	meta->prev = NULL;

	mov	rax, QWORD PTR meta$[rsp]
	mov	QWORD PTR [rax+32], 0

; 106  : 	meta->magic = MAGIC_FREE;

	mov	rax, QWORD PTR meta$[rsp]
	mov	DWORD PTR [rax], 369500162		; 16062002H

; 107  : 
; 108  : 	/* meta->size holds only the usable area size for user */
; 109  : 	meta->size = req_pages * 4096 - sizeof(meta_data_t);

	mov	rax, QWORD PTR req_pages$[rsp]
	imul	rax, 4096				; 00001000H
	sub	rax, 40					; 00000028H
	mov	rcx, QWORD PTR meta$[rsp]
	mov	QWORD PTR [rcx+8], rax

; 110  : 	last_block->next = meta;

	mov	rax, QWORD PTR ?last_block@@3PEAU_meta_data_@@EA ; last_block
	mov	rcx, QWORD PTR meta$[rsp]
	mov	QWORD PTR [rax+24], rcx

; 111  : 	meta->prev = last_block;

	mov	rax, QWORD PTR meta$[rsp]
	mov	rcx, QWORD PTR ?last_block@@3PEAU_meta_data_@@EA ; last_block
	mov	QWORD PTR [rax+32], rcx

; 112  : 	last_block = meta;

	mov	rax, QWORD PTR meta$[rsp]
	mov	QWORD PTR ?last_block@@3PEAU_meta_data_@@EA, rax ; last_block

; 113  : 
; 114  : 
; 115  : 	/* now check if we can merge the last block and this
; 116  : 	* into one
; 117  : 	*/
; 118  : 	if (meta->prev->free) {

	mov	rax, QWORD PTR meta$[rsp]
	mov	rax, QWORD PTR [rax+32]
	movzx	eax, BYTE PTR [rax+16]
	test	eax, eax
	je	SHORT $LN1@au_expand_

; 119  : 		meta->prev->size += meta->size;

	mov	rax, QWORD PTR meta$[rsp]
	mov	rax, QWORD PTR [rax+32]
	mov	rax, QWORD PTR [rax+8]
	mov	rcx, QWORD PTR meta$[rsp]
	add	rax, QWORD PTR [rcx+8]
	mov	rcx, QWORD PTR meta$[rsp]
	mov	rcx, QWORD PTR [rcx+32]
	mov	QWORD PTR [rcx+8], rax

; 120  : 		meta->prev->next = NULL;

	mov	rax, QWORD PTR meta$[rsp]
	mov	rax, QWORD PTR [rax+32]
	mov	QWORD PTR [rax+24], 0

; 121  : 		last_block = meta->prev;

	mov	rax, QWORD PTR meta$[rsp]
	mov	rax, QWORD PTR [rax+32]
	mov	QWORD PTR ?last_block@@3PEAU_meta_data_@@EA, rax ; last_block
$LN1@au_expand_:

; 122  : 	}
; 123  : 
; 124  : 	uint64_t lm = (uint64_t)page;

	mov	rax, QWORD PTR page$[rsp]
	mov	QWORD PTR lm$[rsp], rax

; 125  : 	last_mark = (uint8_t*)(lm + (req_pages * 4096));

	mov	rax, QWORD PTR req_pages$[rsp]
	imul	rax, 4096				; 00001000H
	mov	rcx, QWORD PTR lm$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	QWORD PTR ?last_mark@@3PEAEEA, rax	; last_mark

; 126  : 	
; 127  : }

	add	rsp, 88					; 00000058H
	ret	0
?au_expand_kmalloc@@YAX_K@Z ENDP			; au_expand_kmalloc
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\kheap.cpp
_TEXT	SEGMENT
new_block$ = 0
meta_block_a$ = 8
size$ = 16
meta_block$ = 48
req_size$ = 56
?au_split_block@@YAHPEAU_meta_data_@@_K@Z PROC		; au_split_block

; 62   : int au_split_block(meta_data_t* meta_block, size_t req_size) {

$LN7:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 63   : 	uint8_t* meta_block_a = (uint8_t*)meta_block;	

	mov	rax, QWORD PTR meta_block$[rsp]
	mov	QWORD PTR meta_block_a$[rsp], rax

; 64   : 	
; 65   : 	if (meta_block->size <= sizeof(meta_data_t))

	mov	rax, QWORD PTR meta_block$[rsp]
	cmp	QWORD PTR [rax+8], 40			; 00000028H
	ja	SHORT $LN4@au_split_b

; 66   : 		return 0;

	xor	eax, eax
	jmp	$LN5@au_split_b
$LN4@au_split_b:

; 67   : 
; 68   : 	meta_data_t* new_block = (meta_data_t*)(meta_block_a + sizeof(meta_data_t) + req_size);

	mov	rax, QWORD PTR meta_block_a$[rsp]
	mov	rcx, QWORD PTR req_size$[rsp]
	lea	rax, QWORD PTR [rax+rcx+40]
	mov	QWORD PTR new_block$[rsp], rax

; 69   : 	size_t size =  meta_block->size - req_size - sizeof(meta_data_t);

	mov	rax, QWORD PTR meta_block$[rsp]
	mov	rcx, QWORD PTR req_size$[rsp]
	mov	rax, QWORD PTR [rax+8]
	sub	rax, rcx
	sub	rax, 40					; 00000028H
	mov	QWORD PTR size$[rsp], rax

; 70   : 	if ((((uint8_t*)new_block + sizeof(meta_data_t)) > last_mark)) {

	mov	rax, QWORD PTR new_block$[rsp]
	add	rax, 40					; 00000028H
	cmp	rax, QWORD PTR ?last_mark@@3PEAEEA	; last_mark
	jbe	SHORT $LN3@au_split_b

; 71   : 		return 0;

	xor	eax, eax
	jmp	$LN5@au_split_b
$LN3@au_split_b:

; 72   : 	}
; 73   : 
; 74   : 	new_block->free = true;

	mov	rax, QWORD PTR new_block$[rsp]
	mov	BYTE PTR [rax+16], 1

; 75   : 	new_block->magic = MAGIC_FREE;

	mov	rax, QWORD PTR new_block$[rsp]
	mov	DWORD PTR [rax], 369500162		; 16062002H

; 76   : 	new_block->prev = meta_block;

	mov	rax, QWORD PTR new_block$[rsp]
	mov	rcx, QWORD PTR meta_block$[rsp]
	mov	QWORD PTR [rax+32], rcx

; 77   : 	new_block->next = meta_block->next;

	mov	rax, QWORD PTR new_block$[rsp]
	mov	rcx, QWORD PTR meta_block$[rsp]
	mov	rcx, QWORD PTR [rcx+24]
	mov	QWORD PTR [rax+24], rcx

; 78   : 	if (meta_block->next != NULL)

	mov	rax, QWORD PTR meta_block$[rsp]
	cmp	QWORD PTR [rax+24], 0
	je	SHORT $LN2@au_split_b

; 79   : 		meta_block->next->prev = new_block;

	mov	rax, QWORD PTR meta_block$[rsp]
	mov	rax, QWORD PTR [rax+24]
	mov	rcx, QWORD PTR new_block$[rsp]
	mov	QWORD PTR [rax+32], rcx
$LN2@au_split_b:

; 80   : 
; 81   : 	new_block->size = meta_block->size - req_size - sizeof(meta_data_t);

	mov	rax, QWORD PTR meta_block$[rsp]
	mov	rcx, QWORD PTR req_size$[rsp]
	mov	rax, QWORD PTR [rax+8]
	sub	rax, rcx
	sub	rax, 40					; 00000028H
	mov	rcx, QWORD PTR new_block$[rsp]
	mov	QWORD PTR [rcx+8], rax

; 82   : 	if (new_block->size <= sizeof(meta_data_t)) {

	mov	rax, QWORD PTR new_block$[rsp]
	cmp	QWORD PTR [rax+8], 40			; 00000028H
	ja	SHORT $LN1@au_split_b

; 83   : 		new_block->free = false;

	mov	rax, QWORD PTR new_block$[rsp]
	mov	BYTE PTR [rax+16], 0
$LN1@au_split_b:

; 84   : 	}
; 85   : 	
; 86   : 	meta_block->size = req_size + sizeof(meta_data_t);

	mov	rax, QWORD PTR req_size$[rsp]
	add	rax, 40					; 00000028H
	mov	rcx, QWORD PTR meta_block$[rsp]
	mov	QWORD PTR [rcx+8], rax

; 87   : 	meta_block->next = new_block;

	mov	rax, QWORD PTR meta_block$[rsp]
	mov	rcx, QWORD PTR new_block$[rsp]
	mov	QWORD PTR [rax+24], rcx

; 88   : 	last_block = new_block;

	mov	rax, QWORD PTR new_block$[rsp]
	mov	QWORD PTR ?last_block@@3PEAU_meta_data_@@EA, rax ; last_block

; 89   : 
; 90   : 	return 1;

	mov	eax, 1
$LN5@au_split_b:

; 91   : }

	add	rsp, 40					; 00000028H
	ret	0
?au_split_block@@YAHPEAU_meta_data_@@_K@Z ENDP		; au_split_block
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\kheap.cpp
_TEXT	SEGMENT
meta$ = 32
actual_addr$ = 40
ptr$ = 64
free	PROC

; 210  : void free(void* ptr) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 211  : 	uint8_t* actual_addr = (uint8_t*)ptr;

	mov	rax, QWORD PTR ptr$[rsp]
	mov	QWORD PTR actual_addr$[rsp], rax

; 212  : 	meta_data_t *meta = (meta_data_t*)(actual_addr - sizeof(meta_data_t));

	mov	rax, QWORD PTR actual_addr$[rsp]
	sub	rax, 40					; 00000028H
	mov	QWORD PTR meta$[rsp], rax

; 213  : 	meta->free = true;

	mov	rax, QWORD PTR meta$[rsp]
	mov	BYTE PTR [rax+16], 1

; 214  : 	/* merge it with 3 near blocks if they are free*/
; 215  : 	merge_forward(meta);

	mov	rcx, QWORD PTR meta$[rsp]
	call	?merge_forward@@YAXPEAU_meta_data_@@@Z	; merge_forward

; 216  : 	merge_backward(meta);

	mov	rcx, QWORD PTR meta$[rsp]
	call	?merge_backward@@YAXPEAU_meta_data_@@@Z	; merge_backward

; 217  : }

	add	rsp, 56					; 00000038H
	ret	0
free	ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\kheap.cpp
_TEXT	SEGMENT
meta$ = 32
ret$ = 40
size$ = 64
malloc	PROC

; 133  : void* malloc(size_t size) {

$LN11:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 134  : 	
; 135  : 	meta_data_t *meta = first_block;

	mov	rax, QWORD PTR ?first_block@@3PEAU_meta_data_@@EA ; first_block
	mov	QWORD PTR meta$[rsp], rax

; 136  : 	uint8_t* ret = 0;

	mov	QWORD PTR ret$[rsp], 0
$LN8@malloc:

; 137  : 	/* now search begins */
; 138  : 	while(meta){

	cmp	QWORD PTR meta$[rsp], 0
	je	$LN7@malloc

; 139  : 		if (meta->free) {

	mov	rax, QWORD PTR meta$[rsp]
	movzx	eax, BYTE PTR [rax+16]
	test	eax, eax
	je	SHORT $LN6@malloc

; 140  : 			if (meta->size > size) {

	mov	rax, QWORD PTR meta$[rsp]
	mov	rcx, QWORD PTR size$[rsp]
	cmp	QWORD PTR [rax+8], rcx
	jbe	SHORT $LN5@malloc

; 141  : 				if (au_split_block(meta, size)){

	mov	rdx, QWORD PTR size$[rsp]
	mov	rcx, QWORD PTR meta$[rsp]
	call	?au_split_block@@YAHPEAU_meta_data_@@_K@Z ; au_split_block
	test	eax, eax
	je	SHORT $LN4@malloc

; 142  : 					meta->free = false;

	mov	rax, QWORD PTR meta$[rsp]
	mov	BYTE PTR [rax+16], 0

; 143  : 					meta->magic = MAGIC_USED;

	mov	rax, QWORD PTR meta$[rsp]
	mov	DWORD PTR [rax], 303112194		; 12112002H

; 144  : 					ret = ((uint8_t*)meta + sizeof(meta_data_t));

	mov	rax, QWORD PTR meta$[rsp]
	add	rax, 40					; 00000028H
	mov	QWORD PTR ret$[rsp], rax
$LN4@malloc:

; 145  : 				}
; 146  : 				break;

	jmp	SHORT $LN7@malloc
$LN5@malloc:

; 147  : 			}
; 148  : 
; 149  : 			if (meta->size == size) {

	mov	rax, QWORD PTR meta$[rsp]
	mov	rcx, QWORD PTR size$[rsp]
	cmp	QWORD PTR [rax+8], rcx
	jne	SHORT $LN3@malloc

; 150  : 				meta->free = false;

	mov	rax, QWORD PTR meta$[rsp]
	mov	BYTE PTR [rax+16], 0

; 151  : 				meta->magic = MAGIC_USED;

	mov	rax, QWORD PTR meta$[rsp]
	mov	DWORD PTR [rax], 303112194		; 12112002H

; 152  : 				ret =  ((uint8_t*)meta + sizeof(meta_data_t));

	mov	rax, QWORD PTR meta$[rsp]
	add	rax, 40					; 00000028H
	mov	QWORD PTR ret$[rsp], rax

; 153  : 				break;

	jmp	SHORT $LN7@malloc
$LN3@malloc:
$LN6@malloc:

; 154  : 			}
; 155  : 
; 156  : 		}
; 157  : 		meta = meta->next;

	mov	rax, QWORD PTR meta$[rsp]
	mov	rax, QWORD PTR [rax+24]
	mov	QWORD PTR meta$[rsp], rax

; 158  : 	}

	jmp	$LN8@malloc
$LN7@malloc:

; 159  : 
; 160  : 	if (ret) {

	cmp	QWORD PTR ret$[rsp], 0
	je	SHORT $LN2@malloc

; 161  : 		_debug_print_ ("Returning address -> %x \r\n", ret);

	mov	rdx, QWORD PTR ret$[rsp]
	lea	rcx, OFFSET FLAT:$SG3134
	call	?_debug_print_@@YAXPEADZZ		; _debug_print_

; 162  : 		return ret;

	mov	rax, QWORD PTR ret$[rsp]
	jmp	SHORT $LN9@malloc

; 163  : 	} else{

	jmp	SHORT $LN1@malloc
$LN2@malloc:

; 164  : 		au_expand_kmalloc(size);

	mov	rcx, QWORD PTR size$[rsp]
	call	?au_expand_kmalloc@@YAX_K@Z		; au_expand_kmalloc
$LN1@malloc:

; 165  : 		
; 166  : 	}
; 167  : 	return malloc(size);

	mov	rcx, QWORD PTR size$[rsp]
	call	malloc
$LN9@malloc:

; 168  : }

	add	rsp, 56					; 00000038H
	ret	0
malloc	ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\kheap.cpp
_TEXT	SEGMENT
ptr$ = 48
pages$ = 56
?au_free_page@@YAXPEAXH@Z PROC				; au_free_page

; 272  : void au_free_page(void* ptr, int pages) {

$LN3:
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 273  : 	AuFreePages((uint64_t)ptr,true,pages);

	movsxd	rax, DWORD PTR pages$[rsp]
	mov	r8, rax
	mov	dl, 1
	mov	rcx, QWORD PTR ptr$[rsp]
	call	AuFreePages

; 274  : }

	add	rsp, 40					; 00000028H
	ret	0
?au_free_page@@YAXPEAXH@Z ENDP				; au_free_page
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\kheap.cpp
_TEXT	SEGMENT
i$1 = 32
page$ = 40
page_$ = 48
tv76 = 56
pages$ = 80
?au_request_page@@YAPEA_KH@Z PROC			; au_request_page

; 254  : uint64_t* au_request_page(int pages) {

$LN6:
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 72					; 00000048H

; 255  : 	uint64_t* page = AuGetFreePage(0,false, 0);

	xor	r8d, r8d
	xor	edx, edx
	xor	ecx, ecx
	call	AuGetFreePage
	mov	QWORD PTR page$[rsp], rax

; 256  : 	uint64_t page_ = (uint64_t)page;

	mov	rax, QWORD PTR page$[rsp]
	mov	QWORD PTR page_$[rsp], rax

; 257  : 
; 258  : 	_debug_print_ ("*****Requesting page -> %x \r\n", page);

	mov	rdx, QWORD PTR page$[rsp]
	lea	rcx, OFFSET FLAT:$SG3176
	call	?_debug_print_@@YAXPEADZZ		; _debug_print_

; 259  : 	for (size_t i = 0; i < pages; i++) {

	mov	QWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@au_request
$LN2@au_request:
	mov	rax, QWORD PTR i$1[rsp]
	inc	rax
	mov	QWORD PTR i$1[rsp], rax
$LN3@au_request:
	movsxd	rax, DWORD PTR pages$[rsp]
	cmp	QWORD PTR i$1[rsp], rax
	jae	SHORT $LN1@au_request

; 260  : 		AuMapPage((uint64_t)AuPmmngrAlloc(), page_ + i * 4096, 0);

	mov	rax, QWORD PTR i$1[rsp]
	imul	rax, 4096				; 00001000H
	mov	rcx, QWORD PTR page_$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	QWORD PTR tv76[rsp], rax
	call	AuPmmngrAlloc
	xor	r8d, r8d
	mov	rcx, QWORD PTR tv76[rsp]
	mov	rdx, rcx
	mov	rcx, rax
	call	AuMapPage

; 261  : 		
; 262  : 	}

	jmp	SHORT $LN2@au_request
$LN1@au_request:

; 263  : 	return (uint64_t*)page;

	mov	rax, QWORD PTR page$[rsp]

; 264  : }

	add	rsp, 72					; 00000048H
	ret	0
?au_request_page@@YAPEA_KH@Z ENDP			; au_request_page
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\kheap.cpp
_TEXT	SEGMENT
meta$ = 32
page$ = 40
desc_addr$ = 48
lm$ = 56
?AuHeapInitialize@@YAXXZ PROC				; AuHeapInitialize

; 42   : void AuHeapInitialize() {

$LN3:
	sub	rsp, 72					; 00000048H

; 43   : 	uint64_t* page = au_request_page(1);

	mov	ecx, 1
	call	?au_request_page@@YAPEA_KH@Z		; au_request_page
	mov	QWORD PTR page$[rsp], rax

; 44   : 	memset(page, 0, (1*4096));

	mov	r8d, 4096				; 00001000H
	xor	edx, edx
	mov	rcx, QWORD PTR page$[rsp]
	call	memset

; 45   : 	/* setup the first meta data block */
; 46   : 	uint8_t* desc_addr = (uint8_t*)page;

	mov	rax, QWORD PTR page$[rsp]
	mov	QWORD PTR desc_addr$[rsp], rax

; 47   : 	meta_data_t *meta = (meta_data_t*)desc_addr;

	mov	rax, QWORD PTR desc_addr$[rsp]
	mov	QWORD PTR meta$[rsp], rax

; 48   : 	meta->free = true;

	mov	rax, QWORD PTR meta$[rsp]
	mov	BYTE PTR [rax+16], 1

; 49   : 	meta->next = NULL;

	mov	rax, QWORD PTR meta$[rsp]
	mov	QWORD PTR [rax+24], 0

; 50   : 	meta->prev = NULL;

	mov	rax, QWORD PTR meta$[rsp]
	mov	QWORD PTR [rax+32], 0

; 51   : 	meta->magic = MAGIC_FREE;

	mov	rax, QWORD PTR meta$[rsp]
	mov	DWORD PTR [rax], 369500162		; 16062002H

; 52   : 	/* meta->size holds only the usable area size for user */
; 53   : 	meta->size = (1*4096) - sizeof(meta_data_t);

	mov	rax, QWORD PTR meta$[rsp]
	mov	QWORD PTR [rax+8], 4056			; 00000fd8H

; 54   : 	first_block = meta;

	mov	rax, QWORD PTR meta$[rsp]
	mov	QWORD PTR ?first_block@@3PEAU_meta_data_@@EA, rax ; first_block

; 55   : 	last_block = meta;

	mov	rax, QWORD PTR meta$[rsp]
	mov	QWORD PTR ?last_block@@3PEAU_meta_data_@@EA, rax ; last_block

; 56   : 	uint64_t lm = (uint64_t)page;

	mov	rax, QWORD PTR page$[rsp]
	mov	QWORD PTR lm$[rsp], rax

; 57   : 	last_mark = (uint8_t*)(lm + (1*4096));

	mov	rax, QWORD PTR lm$[rsp]
	add	rax, 4096				; 00001000H
	mov	QWORD PTR ?last_mark@@3PEAEEA, rax	; last_mark

; 58   : }

	add	rsp, 72					; 00000048H
	ret	0
?AuHeapInitialize@@YAXXZ ENDP				; AuHeapInitialize
_TEXT	ENDS
END
