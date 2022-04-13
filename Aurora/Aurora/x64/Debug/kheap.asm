; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?first_block@@3PEAU_meta_data_@@EA		; first_block
PUBLIC	?last_block@@3PEAU_meta_data_@@EA		; last_block
_BSS	SEGMENT
?first_block@@3PEAU_meta_data_@@EA DQ 01H DUP (?)	; first_block
?last_block@@3PEAU_meta_data_@@EA DQ 01H DUP (?)	; last_block
_BSS	ENDS
PUBLIC	?heap_initialize@@YAXXZ				; heap_initialize
PUBLIC	?au_request_page@@YAPEA_KH@Z			; au_request_page
PUBLIC	?au_free_page@@YAXPEAXH@Z			; au_free_page
PUBLIC	?malloc@@YAPEAX_K@Z				; malloc
PUBLIC	?free@@YAXPEAX@Z				; free
PUBLIC	?au_split_block@@YAXPEAU_meta_data_@@_K@Z	; au_split_block
PUBLIC	?au_expand_kmalloc@@YAX_K@Z			; au_expand_kmalloc
PUBLIC	?krealloc@@YAPEAXPEAX_K@Z			; krealloc
PUBLIC	?kcalloc@@YAPEAX_K0@Z				; kcalloc
EXTRN	?memset@@YAXPEAXEI@Z:PROC			; memset
EXTRN	memcpy:PROC
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	?map_page@@YA_N_K0E@Z:PROC			; map_page
EXTRN	?get_free_page@@YAPEA_K_K_N@Z:PROC		; get_free_page
EXTRN	?vmmngr_free_pages@@YAX_K_N0@Z:PROC		; vmmngr_free_pages
pdata	SEGMENT
$pdata$?heap_initialize@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+165
	DD	imagerel $unwind$?heap_initialize@@YAXXZ
$pdata$?au_request_page@@YAPEA_KH@Z DD imagerel $LN6
	DD	imagerel $LN6+132
	DD	imagerel $unwind$?au_request_page@@YAPEA_KH@Z
$pdata$?au_free_page@@YAXPEAXH@Z DD imagerel $LN3
	DD	imagerel $LN3+38
	DD	imagerel $unwind$?au_free_page@@YAXPEAXH@Z
$pdata$?malloc@@YAPEAX_K@Z DD imagerel $LN9
	DD	imagerel $LN9+197
	DD	imagerel $unwind$?malloc@@YAPEAX_K@Z
$pdata$?free@@YAXPEAX@Z DD imagerel $LN6
	DD	imagerel $LN6+229
	DD	imagerel $unwind$?free@@YAXPEAX@Z
$pdata$?au_split_block@@YAXPEAU_meta_data_@@_K@Z DD imagerel $LN4
	DD	imagerel $LN4+207
	DD	imagerel $unwind$?au_split_block@@YAXPEAU_meta_data_@@_K@Z
$pdata$?au_expand_kmalloc@@YAX_K@Z DD imagerel $LN5
	DD	imagerel $LN5+315
	DD	imagerel $unwind$?au_expand_kmalloc@@YAX_K@Z
$pdata$?krealloc@@YAPEAXPEAX_K@Z DD imagerel $LN4
	DD	imagerel $LN4+77
	DD	imagerel $unwind$?krealloc@@YAPEAXPEAX_K@Z
$pdata$?kcalloc@@YAPEAX_K0@Z DD imagerel $LN4
	DD	imagerel $LN4+80
	DD	imagerel $unwind$?kcalloc@@YAPEAX_K0@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?heap_initialize@@YAXXZ DD 010401H
	DD	08204H
$unwind$?au_request_page@@YAPEA_KH@Z DD 010801H
	DD	08208H
$unwind$?au_free_page@@YAXPEAXH@Z DD 010d01H
	DD	0420dH
$unwind$?malloc@@YAPEAX_K@Z DD 010901H
	DD	06209H
$unwind$?free@@YAXPEAX@Z DD 010901H
	DD	02209H
$unwind$?au_split_block@@YAXPEAU_meta_data_@@_K@Z DD 010e01H
	DD	0220eH
$unwind$?au_expand_kmalloc@@YAX_K@Z DD 010901H
	DD	08209H
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

; 188  : void* kcalloc(size_t n_item, size_t size) {

$LN4:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 189  : 	size_t total = n_item * size;

	mov	rax, QWORD PTR n_item$[rsp]
	imul	rax, QWORD PTR size$[rsp]
	mov	QWORD PTR total$[rsp], rax

; 190  : 
; 191  : 	void* ptr = malloc(total);

	mov	rcx, QWORD PTR total$[rsp]
	call	?malloc@@YAPEAX_K@Z			; malloc
	mov	QWORD PTR ptr$[rsp], rax

; 192  : 	if (ptr)

	cmp	QWORD PTR ptr$[rsp], 0
	je	SHORT $LN1@kcalloc

; 193  : 		memset(ptr, 0, total);

	mov	r8d, DWORD PTR total$[rsp]
	xor	edx, edx
	mov	rcx, QWORD PTR ptr$[rsp]
	call	?memset@@YAXPEAXEI@Z			; memset
$LN1@kcalloc:

; 194  : 	return ptr;

	mov	rax, QWORD PTR ptr$[rsp]

; 195  : }

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

; 170  : void* krealloc(void* ptr, size_t new_size) {

$LN4:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 171  : 	void* result = malloc(new_size);

	mov	rcx, QWORD PTR new_size$[rsp]
	call	?malloc@@YAPEAX_K@Z			; malloc
	mov	QWORD PTR result$[rsp], rax

; 172  : 	if (ptr) {

	cmp	QWORD PTR ptr$[rsp], 0
	je	SHORT $LN1@krealloc

; 173  : 		/* here we can check the size difference
; 174  : 		 * of new_size and old size from internal
; 175  : 		 * data structure of kmalloc */
; 176  : 		memcpy(result, ptr, new_size);

	mov	r8d, DWORD PTR new_size$[rsp]
	mov	rdx, QWORD PTR ptr$[rsp]
	mov	rcx, QWORD PTR result$[rsp]
	call	memcpy
$LN1@krealloc:

; 177  : 	}
; 178  : 
; 179  : 	free(ptr);

	mov	rcx, QWORD PTR ptr$[rsp]
	call	?free@@YAXPEAX@Z			; free

; 180  : 	return result;

	mov	rax, QWORD PTR result$[rsp]

; 181  : }

	add	rsp, 56					; 00000038H
	ret	0
?krealloc@@YAPEAXPEAX_K@Z ENDP				; krealloc
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\kheap.cpp
_TEXT	SEGMENT
meta$ = 32
req_pages$ = 40
desc_addr$ = 48
page$ = 56
req_size$ = 80
?au_expand_kmalloc@@YAX_K@Z PROC			; au_expand_kmalloc

; 77   : void au_expand_kmalloc(size_t req_size) {

$LN5:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 78   : 	size_t req_pages = 1;

	mov	QWORD PTR req_pages$[rsp], 1

; 79   : 	if (req_size >= 4096)

	cmp	QWORD PTR req_size$[rsp], 4096		; 00001000H
	jb	SHORT $LN2@au_expand_

; 80   : 		req_pages = (req_size + sizeof(meta_data_t)) / 4096 + 1;

	mov	rax, QWORD PTR req_size$[rsp]
	add	rax, 48					; 00000030H
	xor	edx, edx
	mov	ecx, 4096				; 00001000H
	div	rcx
	inc	rax
	mov	QWORD PTR req_pages$[rsp], rax
$LN2@au_expand_:

; 81   : 
; 82   : 	void* page = au_request_page(req_pages);

	mov	ecx, DWORD PTR req_pages$[rsp]
	call	?au_request_page@@YAPEA_KH@Z		; au_request_page
	mov	QWORD PTR page$[rsp], rax

; 83   : 	uint8_t* desc_addr = (uint8_t*)page;

	mov	rax, QWORD PTR page$[rsp]
	mov	QWORD PTR desc_addr$[rsp], rax

; 84   : 	/* setup the first meta data block */
; 85   : 	meta_data_t *meta = (meta_data_t*)desc_addr;

	mov	rax, QWORD PTR desc_addr$[rsp]
	mov	QWORD PTR meta$[rsp], rax

; 86   : 	meta->free = true;

	mov	rax, QWORD PTR meta$[rsp]
	mov	BYTE PTR [rax+16], 1

; 87   : 	meta->next = NULL;

	mov	rax, QWORD PTR meta$[rsp]
	mov	QWORD PTR [rax+32], 0

; 88   : 	meta->prev = NULL;

	mov	rax, QWORD PTR meta$[rsp]
	mov	QWORD PTR [rax+40], 0

; 89   : 	meta->magic = MAGIC_FREE;

	mov	rax, QWORD PTR meta$[rsp]
	mov	DWORD PTR [rax], 369500162		; 16062002H

; 90   : 	meta->eob_mark = (desc_addr + 4095);

	mov	rax, QWORD PTR desc_addr$[rsp]
	add	rax, 4095				; 00000fffH
	mov	rcx, QWORD PTR meta$[rsp]
	mov	QWORD PTR [rcx+24], rax

; 91   : 
; 92   : 	/* meta->size holds only the usable area size for user */
; 93   : 	meta->size = req_pages * 4096 - sizeof(meta_data_t);

	mov	rax, QWORD PTR req_pages$[rsp]
	imul	rax, 4096				; 00001000H
	sub	rax, 48					; 00000030H
	mov	rcx, QWORD PTR meta$[rsp]
	mov	QWORD PTR [rcx+8], rax

; 94   : 	last_block->next = meta;

	mov	rax, QWORD PTR ?last_block@@3PEAU_meta_data_@@EA ; last_block
	mov	rcx, QWORD PTR meta$[rsp]
	mov	QWORD PTR [rax+32], rcx

; 95   : 	meta->prev = last_block;

	mov	rax, QWORD PTR meta$[rsp]
	mov	rcx, QWORD PTR ?last_block@@3PEAU_meta_data_@@EA ; last_block
	mov	QWORD PTR [rax+40], rcx

; 96   : 	last_block = meta;

	mov	rax, QWORD PTR meta$[rsp]
	mov	QWORD PTR ?last_block@@3PEAU_meta_data_@@EA, rax ; last_block

; 97   : 
; 98   : 
; 99   : 	/* now check if we can merge the last block and this
; 100  : 	* into one
; 101  : 	*/
; 102  : 	if (meta->prev->free) {

	mov	rax, QWORD PTR meta$[rsp]
	mov	rax, QWORD PTR [rax+40]
	movzx	eax, BYTE PTR [rax+16]
	test	eax, eax
	je	SHORT $LN1@au_expand_

; 103  : 		meta->prev->size += meta->size;

	mov	rax, QWORD PTR meta$[rsp]
	mov	rax, QWORD PTR [rax+40]
	mov	rax, QWORD PTR [rax+8]
	mov	rcx, QWORD PTR meta$[rsp]
	add	rax, QWORD PTR [rcx+8]
	mov	rcx, QWORD PTR meta$[rsp]
	mov	rcx, QWORD PTR [rcx+40]
	mov	QWORD PTR [rcx+8], rax

; 104  : 		meta->prev->next = NULL;

	mov	rax, QWORD PTR meta$[rsp]
	mov	rax, QWORD PTR [rax+40]
	mov	QWORD PTR [rax+32], 0

; 105  : 		last_block = meta->prev;

	mov	rax, QWORD PTR meta$[rsp]
	mov	rax, QWORD PTR [rax+40]
	mov	QWORD PTR ?last_block@@3PEAU_meta_data_@@EA, rax ; last_block
$LN1@au_expand_:

; 106  : 	}
; 107  : 	
; 108  : }

	add	rsp, 72					; 00000048H
	ret	0
?au_expand_kmalloc@@YAX_K@Z ENDP			; au_expand_kmalloc
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\kheap.cpp
_TEXT	SEGMENT
new_block$ = 0
meta_block_a$ = 8
meta_block$ = 32
req_size$ = 40
?au_split_block@@YAXPEAU_meta_data_@@_K@Z PROC		; au_split_block

; 60   : void au_split_block(meta_data_t* meta_block, size_t req_size) {

$LN4:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 24

; 61   : 	uint8_t* meta_block_a = (uint8_t*)meta_block;	

	mov	rax, QWORD PTR meta_block$[rsp]
	mov	QWORD PTR meta_block_a$[rsp], rax

; 62   : 	meta_data_t* new_block = (meta_data_t*)(meta_block_a + sizeof(meta_data_t) + req_size);

	mov	rax, QWORD PTR meta_block_a$[rsp]
	mov	rcx, QWORD PTR req_size$[rsp]
	lea	rax, QWORD PTR [rax+rcx+48]
	mov	QWORD PTR new_block$[rsp], rax

; 63   : 	new_block->free = true;

	mov	rax, QWORD PTR new_block$[rsp]
	mov	BYTE PTR [rax+16], 1

; 64   : 	new_block->eob_mark = meta_block->eob_mark;

	mov	rax, QWORD PTR new_block$[rsp]
	mov	rcx, QWORD PTR meta_block$[rsp]
	mov	rcx, QWORD PTR [rcx+24]
	mov	QWORD PTR [rax+24], rcx

; 65   : 	new_block->magic = MAGIC_FREE;

	mov	rax, QWORD PTR new_block$[rsp]
	mov	DWORD PTR [rax], 369500162		; 16062002H

; 66   : 	new_block->prev = meta_block;

	mov	rax, QWORD PTR new_block$[rsp]
	mov	rcx, QWORD PTR meta_block$[rsp]
	mov	QWORD PTR [rax+40], rcx

; 67   : 	new_block->next = meta_block->next;

	mov	rax, QWORD PTR new_block$[rsp]
	mov	rcx, QWORD PTR meta_block$[rsp]
	mov	rcx, QWORD PTR [rcx+32]
	mov	QWORD PTR [rax+32], rcx

; 68   : 	new_block->size = meta_block->size - req_size - sizeof(meta_data_t);

	mov	rax, QWORD PTR meta_block$[rsp]
	mov	rcx, QWORD PTR req_size$[rsp]
	mov	rax, QWORD PTR [rax+8]
	sub	rax, rcx
	sub	rax, 48					; 00000030H
	mov	rcx, QWORD PTR new_block$[rsp]
	mov	QWORD PTR [rcx+8], rax

; 69   : 	if (new_block->size < 0)

	mov	rax, QWORD PTR new_block$[rsp]
	cmp	QWORD PTR [rax+8], 0
	jae	SHORT $LN1@au_split_b

; 70   : 		new_block->size = 0;

	mov	rax, QWORD PTR new_block$[rsp]
	mov	QWORD PTR [rax+8], 0
$LN1@au_split_b:

; 71   : 	meta_block->size = req_size + sizeof(meta_data_t);

	mov	rax, QWORD PTR req_size$[rsp]
	add	rax, 48					; 00000030H
	mov	rcx, QWORD PTR meta_block$[rsp]
	mov	QWORD PTR [rcx+8], rax

; 72   : 	meta_block->next = new_block;

	mov	rax, QWORD PTR meta_block$[rsp]
	mov	rcx, QWORD PTR new_block$[rsp]
	mov	QWORD PTR [rax+32], rcx

; 73   : 	last_block = new_block;

	mov	rax, QWORD PTR new_block$[rsp]
	mov	QWORD PTR ?last_block@@3PEAU_meta_data_@@EA, rax ; last_block

; 74   : }

	add	rsp, 24
	ret	0
?au_split_block@@YAXPEAU_meta_data_@@_K@Z ENDP		; au_split_block
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\kheap.cpp
_TEXT	SEGMENT
meta$ = 0
actual_addr$ = 8
ptr$ = 32
?free@@YAXPEAX@Z PROC					; free

; 143  : void free(void* ptr) {

$LN6:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 24

; 144  : 	uint8_t* actual_addr = (uint8_t*)ptr - sizeof(meta_data_t);

	mov	rax, QWORD PTR ptr$[rsp]
	sub	rax, 48					; 00000030H
	mov	QWORD PTR actual_addr$[rsp], rax

; 145  : 	meta_data_t *meta = (meta_data_t*)actual_addr;

	mov	rax, QWORD PTR actual_addr$[rsp]
	mov	QWORD PTR meta$[rsp], rax

; 146  : 	meta->free = true;

	mov	rax, QWORD PTR meta$[rsp]
	mov	BYTE PTR [rax+16], 1

; 147  : 
; 148  : 	/* merge it with 3 near blocks if they are free*/
; 149  : 
; 150  : 	if (meta->next && meta->next->free) {

	mov	rax, QWORD PTR meta$[rsp]
	cmp	QWORD PTR [rax+32], 0
	je	SHORT $LN3@free
	mov	rax, QWORD PTR meta$[rsp]
	mov	rax, QWORD PTR [rax+32]
	movzx	eax, BYTE PTR [rax+16]
	test	eax, eax
	je	SHORT $LN3@free

; 151  : 		meta->size += meta->next->size;

	mov	rax, QWORD PTR meta$[rsp]
	mov	rax, QWORD PTR [rax+32]
	mov	rcx, QWORD PTR meta$[rsp]
	mov	rcx, QWORD PTR [rcx+8]
	add	rcx, QWORD PTR [rax+8]
	mov	rax, rcx
	mov	rcx, QWORD PTR meta$[rsp]
	mov	QWORD PTR [rcx+8], rax
$LN3@free:

; 152  : 	}
; 153  : 
; 154  : 	if (meta->prev && meta->prev->free) {

	mov	rax, QWORD PTR meta$[rsp]
	cmp	QWORD PTR [rax+40], 0
	je	SHORT $LN2@free
	mov	rax, QWORD PTR meta$[rsp]
	mov	rax, QWORD PTR [rax+40]
	movzx	eax, BYTE PTR [rax+16]
	test	eax, eax
	je	SHORT $LN2@free

; 155  : 		meta->prev->size += meta->size;

	mov	rax, QWORD PTR meta$[rsp]
	mov	rax, QWORD PTR [rax+40]
	mov	rax, QWORD PTR [rax+8]
	mov	rcx, QWORD PTR meta$[rsp]
	add	rax, QWORD PTR [rcx+8]
	mov	rcx, QWORD PTR meta$[rsp]
	mov	rcx, QWORD PTR [rcx+40]
	mov	QWORD PTR [rcx+8], rax

; 156  : 		meta->prev->next = meta->next;

	mov	rax, QWORD PTR meta$[rsp]
	mov	rax, QWORD PTR [rax+40]
	mov	rcx, QWORD PTR meta$[rsp]
	mov	rcx, QWORD PTR [rcx+32]
	mov	QWORD PTR [rax+32], rcx
$LN2@free:

; 157  : 	}
; 158  : 
; 159  : 	if (meta->next && meta->next->free) {

	mov	rax, QWORD PTR meta$[rsp]
	cmp	QWORD PTR [rax+32], 0
	je	SHORT $LN1@free
	mov	rax, QWORD PTR meta$[rsp]
	mov	rax, QWORD PTR [rax+32]
	movzx	eax, BYTE PTR [rax+16]
	test	eax, eax
	je	SHORT $LN1@free

; 160  : 		meta->next->prev = meta->prev;

	mov	rax, QWORD PTR meta$[rsp]
	mov	rax, QWORD PTR [rax+32]
	mov	rcx, QWORD PTR meta$[rsp]
	mov	rcx, QWORD PTR [rcx+40]
	mov	QWORD PTR [rax+40], rcx
$LN1@free:

; 161  : 	}
; 162  : 
; 163  : }

	add	rsp, 24
	ret	0
?free@@YAXPEAX@Z ENDP					; free
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\kheap.cpp
_TEXT	SEGMENT
meta$1 = 32
size$ = 64
?malloc@@YAPEAX_K@Z PROC				; malloc

; 113  : void* malloc(size_t size) {

$LN9:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 114  : 	
; 115  : 	/* now search begins */
; 116  : 	for (meta_data_t *meta = first_block; meta != NULL; meta = meta->next) {

	mov	rax, QWORD PTR ?first_block@@3PEAU_meta_data_@@EA ; first_block
	mov	QWORD PTR meta$1[rsp], rax
	jmp	SHORT $LN6@malloc
$LN5@malloc:
	mov	rax, QWORD PTR meta$1[rsp]
	mov	rax, QWORD PTR [rax+32]
	mov	QWORD PTR meta$1[rsp], rax
$LN6@malloc:
	cmp	QWORD PTR meta$1[rsp], 0
	je	SHORT $LN4@malloc

; 117  : 		if (meta->free) {

	mov	rax, QWORD PTR meta$1[rsp]
	movzx	eax, BYTE PTR [rax+16]
	test	eax, eax
	je	SHORT $LN3@malloc

; 118  : 
; 119  : 			if (meta->size > size) {

	mov	rax, QWORD PTR meta$1[rsp]
	mov	rcx, QWORD PTR size$[rsp]
	cmp	QWORD PTR [rax+8], rcx
	jbe	SHORT $LN2@malloc

; 120  : 				au_split_block(meta, size);

	mov	rdx, QWORD PTR size$[rsp]
	mov	rcx, QWORD PTR meta$1[rsp]
	call	?au_split_block@@YAXPEAU_meta_data_@@_K@Z ; au_split_block

; 121  : 				meta->free = false;

	mov	rax, QWORD PTR meta$1[rsp]
	mov	BYTE PTR [rax+16], 0

; 122  : 				meta->magic = MAGIC_USED;

	mov	rax, QWORD PTR meta$1[rsp]
	mov	DWORD PTR [rax], 303112194		; 12112002H

; 123  : 				return ((uint8_t*)meta + sizeof(meta_data_t));

	mov	rax, QWORD PTR meta$1[rsp]
	add	rax, 48					; 00000030H
	jmp	SHORT $LN7@malloc
$LN2@malloc:

; 124  : 			}
; 125  : 
; 126  : 			if (meta->size == size) {

	mov	rax, QWORD PTR meta$1[rsp]
	mov	rcx, QWORD PTR size$[rsp]
	cmp	QWORD PTR [rax+8], rcx
	jne	SHORT $LN1@malloc

; 127  : 				meta->free = false;

	mov	rax, QWORD PTR meta$1[rsp]
	mov	BYTE PTR [rax+16], 0

; 128  : 				meta->magic = MAGIC_USED;

	mov	rax, QWORD PTR meta$1[rsp]
	mov	DWORD PTR [rax], 303112194		; 12112002H

; 129  : 				return ((uint8_t*)meta + sizeof(meta_data_t));

	mov	rax, QWORD PTR meta$1[rsp]
	add	rax, 48					; 00000030H
	jmp	SHORT $LN7@malloc
$LN1@malloc:
$LN3@malloc:

; 130  : 			}
; 131  : 		}
; 132  : 	}

	jmp	$LN5@malloc
$LN4@malloc:

; 133  : 
; 134  : 	au_expand_kmalloc(size);

	mov	rcx, QWORD PTR size$[rsp]
	call	?au_expand_kmalloc@@YAX_K@Z		; au_expand_kmalloc

; 135  : 	return malloc(size);

	mov	rcx, QWORD PTR size$[rsp]
	call	?malloc@@YAPEAX_K@Z			; malloc
$LN7@malloc:

; 136  : }

	add	rsp, 56					; 00000038H
	ret	0
?malloc@@YAPEAX_K@Z ENDP				; malloc
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\kheap.cpp
_TEXT	SEGMENT
ptr$ = 48
pages$ = 56
?au_free_page@@YAXPEAXH@Z PROC				; au_free_page

; 216  : void au_free_page(void* ptr, int pages) {

$LN3:
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 217  : 	vmmngr_free_pages((uint64_t)ptr,true,pages);

	movsxd	rax, DWORD PTR pages$[rsp]
	mov	r8, rax
	mov	dl, 1
	mov	rcx, QWORD PTR ptr$[rsp]
	call	?vmmngr_free_pages@@YAX_K_N0@Z		; vmmngr_free_pages

; 218  : }

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
tv73 = 56
pages$ = 80
?au_request_page@@YAPEA_KH@Z PROC			; au_request_page

; 200  : uint64_t* au_request_page(int pages) {

$LN6:
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 72					; 00000048H

; 201  : 	uint64_t* page = get_free_page(0,false);

	xor	edx, edx
	xor	ecx, ecx
	call	?get_free_page@@YAPEA_K_K_N@Z		; get_free_page
	mov	QWORD PTR page$[rsp], rax

; 202  : 	uint64_t page_ = (uint64_t)page;

	mov	rax, QWORD PTR page$[rsp]
	mov	QWORD PTR page_$[rsp], rax

; 203  : 	for (size_t i = 0; i < pages; i++) {

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

; 204  : 		map_page((uint64_t)pmmngr_alloc(), (uint64_t)(page_ + i * 4096), 0);

	mov	rax, QWORD PTR i$1[rsp]
	imul	rax, 4096				; 00001000H
	mov	rcx, QWORD PTR page_$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	QWORD PTR tv73[rsp], rax
	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	xor	r8d, r8d
	mov	rcx, QWORD PTR tv73[rsp]
	mov	rdx, rcx
	mov	rcx, rax
	call	?map_page@@YA_N_K0E@Z			; map_page

; 205  : 		
; 206  : 	}

	jmp	SHORT $LN2@au_request
$LN1@au_request:

; 207  : 	return (uint64_t*)page;

	mov	rax, QWORD PTR page$[rsp]

; 208  : }

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
?heap_initialize@@YAXXZ PROC				; heap_initialize

; 41   : void heap_initialize() {

$LN3:
	sub	rsp, 72					; 00000048H

; 42   : 	uint64_t* page = au_request_page(4);

	mov	ecx, 4
	call	?au_request_page@@YAPEA_KH@Z		; au_request_page
	mov	QWORD PTR page$[rsp], rax

; 43   : 	memset(page, 0, (4*4096));

	mov	r8d, 16384				; 00004000H
	xor	edx, edx
	mov	rcx, QWORD PTR page$[rsp]
	call	?memset@@YAXPEAXEI@Z			; memset

; 44   : 	/* setup the first meta data block */
; 45   : 	uint8_t* desc_addr = (uint8_t*)page;

	mov	rax, QWORD PTR page$[rsp]
	mov	QWORD PTR desc_addr$[rsp], rax

; 46   : 	meta_data_t *meta = (meta_data_t*)desc_addr;

	mov	rax, QWORD PTR desc_addr$[rsp]
	mov	QWORD PTR meta$[rsp], rax

; 47   : 	meta->free = true;

	mov	rax, QWORD PTR meta$[rsp]
	mov	BYTE PTR [rax+16], 1

; 48   : 	meta->next = NULL;

	mov	rax, QWORD PTR meta$[rsp]
	mov	QWORD PTR [rax+32], 0

; 49   : 	meta->prev = NULL;

	mov	rax, QWORD PTR meta$[rsp]
	mov	QWORD PTR [rax+40], 0

; 50   : 	meta->magic = MAGIC_FREE;

	mov	rax, QWORD PTR meta$[rsp]
	mov	DWORD PTR [rax], 369500162		; 16062002H

; 51   : 	meta->eob_mark = (desc_addr + 4095);

	mov	rax, QWORD PTR desc_addr$[rsp]
	add	rax, 4095				; 00000fffH
	mov	rcx, QWORD PTR meta$[rsp]
	mov	QWORD PTR [rcx+24], rax

; 52   : 	/* meta->size holds only the usable area size for user */
; 53   : 	meta->size = (4*4096) - sizeof(meta_data_t);

	mov	rax, QWORD PTR meta$[rsp]
	mov	QWORD PTR [rax+8], 16336		; 00003fd0H

; 54   : 	first_block = meta;

	mov	rax, QWORD PTR meta$[rsp]
	mov	QWORD PTR ?first_block@@3PEAU_meta_data_@@EA, rax ; first_block

; 55   : 	last_block = meta;

	mov	rax, QWORD PTR meta$[rsp]
	mov	QWORD PTR ?last_block@@3PEAU_meta_data_@@EA, rax ; last_block

; 56   : }

	add	rsp, 72					; 00000048H
	ret	0
?heap_initialize@@YAXXZ ENDP				; heap_initialize
_TEXT	ENDS
END
