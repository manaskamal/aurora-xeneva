; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?free_memory@@3_KA				; free_memory
PUBLIC	?reserved_memory@@3_KA				; reserved_memory
PUBLIC	?used_memory@@3_KA				; used_memory
PUBLIC	?ram_bitmap_index@@3_KA				; ram_bitmap_index
PUBLIC	?ram_bitmap@@3VBitmap@@A			; ram_bitmap
_BSS	SEGMENT
?free_memory@@3_KA DQ 01H DUP (?)			; free_memory
?reserved_memory@@3_KA DQ 01H DUP (?)			; reserved_memory
?used_memory@@3_KA DQ 01H DUP (?)			; used_memory
?ram_bitmap_index@@3_KA DQ 01H DUP (?)			; ram_bitmap_index
?ram_bitmap@@3VBitmap@@A DB 010H DUP (?)		; ram_bitmap
_BSS	ENDS
PUBLIC	?pmmngr_init@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z	; pmmngr_init
PUBLIC	?pmmngr_alloc@@YAPEAXXZ				; pmmngr_alloc
PUBLIC	?pmmngr_free@@YAXPEAX@Z				; pmmngr_free
PUBLIC	?pmmngr_get_free_ram@@YA_KXZ			; pmmngr_get_free_ram
PUBLIC	?pmmngr_get_used_ram@@YA_KXZ			; pmmngr_get_used_ram
PUBLIC	??ABitmap@@QEAA_N_K@Z				; Bitmap::operator[]
PUBLIC	?Set@Bitmap@@QEAA_N_K_N@Z			; Bitmap::Set
PUBLIC	?pmmngr_init_bitmap@@YAX_KPEAX@Z		; pmmngr_init_bitmap
PUBLIC	?pmmngr_lock_page@@YAXPEAX@Z			; pmmngr_lock_page
PUBLIC	?pmmngr_unreserve_page@@YAXPEAX@Z		; pmmngr_unreserve_page
pdata	SEGMENT
$pdata$?pmmngr_init@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD imagerel $LN3
	DD	imagerel $LN3+113
	DD	imagerel $unwind$?pmmngr_init@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z
$pdata$?pmmngr_alloc@@YAPEAXXZ DD imagerel $LN7
	DD	imagerel $LN7+159
	DD	imagerel $unwind$?pmmngr_alloc@@YAPEAXXZ
$pdata$?pmmngr_free@@YAXPEAX@Z DD imagerel $LN6
	DD	imagerel $LN6+153
	DD	imagerel $unwind$?pmmngr_free@@YAXPEAX@Z
pdata	ENDS
;	COMDAT pdata
pdata	SEGMENT
$pdata$??ABitmap@@QEAA_N_K@Z DD imagerel $LN5
	DD	imagerel $LN5+144
	DD	imagerel $unwind$??ABitmap@@QEAA_N_K@Z
pdata	ENDS
;	COMDAT pdata
pdata	SEGMENT
$pdata$?Set@Bitmap@@QEAA_N_K_N@Z DD imagerel $LN5
	DD	imagerel $LN5+213
	DD	imagerel $unwind$?Set@Bitmap@@QEAA_N_K_N@Z
pdata	ENDS
pdata	SEGMENT
$pdata$?pmmngr_init_bitmap@@YAX_KPEAX@Z DD imagerel $LN6
	DD	imagerel $LN6+88
	DD	imagerel $unwind$?pmmngr_init_bitmap@@YAX_KPEAX@Z
$pdata$?pmmngr_lock_page@@YAXPEAX@Z DD imagerel $LN5
	DD	imagerel $LN5+128
	DD	imagerel $unwind$?pmmngr_lock_page@@YAXPEAX@Z
$pdata$?pmmngr_unreserve_page@@YAXPEAX@Z DD imagerel $LN6
	DD	imagerel $LN6+153
	DD	imagerel $unwind$?pmmngr_unreserve_page@@YAXPEAX@Z
pdata	ENDS
;	COMDAT xdata
xdata	SEGMENT
$unwind$?Set@Bitmap@@QEAA_N_K_N@Z DD 011301H
	DD	02213H
xdata	ENDS
;	COMDAT xdata
xdata	SEGMENT
$unwind$??ABitmap@@QEAA_N_K@Z DD 010e01H
	DD	0220eH
xdata	ENDS
xdata	SEGMENT
$unwind$?pmmngr_init@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD 010901H
	DD	08209H
$unwind$?pmmngr_alloc@@YAPEAXXZ DD 010401H
	DD	04204H
$unwind$?pmmngr_free@@YAXPEAX@Z DD 010901H
	DD	06209H
$unwind$?pmmngr_init_bitmap@@YAX_KPEAX@Z DD 010e01H
	DD	0220eH
$unwind$?pmmngr_lock_page@@YAXPEAX@Z DD 010901H
	DD	06209H
$unwind$?pmmngr_unreserve_page@@YAXPEAX@Z DD 010901H
	DD	06209H
xdata	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\pmmngr.cpp
_TEXT	SEGMENT
index$ = 32
addr$ = 64
?pmmngr_unreserve_page@@YAXPEAX@Z PROC			; pmmngr_unreserve_page

; 81   : void pmmngr_unreserve_page (void* addr) {

$LN6:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 82   : 
; 83   : 	uint64_t index = (uint64_t)addr / 4096;

	xor	edx, edx
	mov	rax, QWORD PTR addr$[rsp]
	mov	ecx, 4096				; 00001000H
	div	rcx
	mov	QWORD PTR index$[rsp], rax

; 84   : 	if (ram_bitmap[index] == false) return;

	mov	rdx, QWORD PTR index$[rsp]
	lea	rcx, OFFSET FLAT:?ram_bitmap@@3VBitmap@@A ; ram_bitmap
	call	??ABitmap@@QEAA_N_K@Z			; Bitmap::operator[]
	movzx	eax, al
	test	eax, eax
	jne	SHORT $LN3@pmmngr_unr
	jmp	SHORT $LN4@pmmngr_unr
$LN3@pmmngr_unr:

; 85   : 	if (ram_bitmap.Set(index, false)) {

	xor	r8d, r8d
	mov	rdx, QWORD PTR index$[rsp]
	lea	rcx, OFFSET FLAT:?ram_bitmap@@3VBitmap@@A ; ram_bitmap
	call	?Set@Bitmap@@QEAA_N_K_N@Z		; Bitmap::Set
	movzx	eax, al
	test	eax, eax
	je	SHORT $LN2@pmmngr_unr

; 86   : 		free_memory += 4096;

	mov	rax, QWORD PTR ?free_memory@@3_KA	; free_memory
	add	rax, 4096				; 00001000H
	mov	QWORD PTR ?free_memory@@3_KA, rax	; free_memory

; 87   : 		reserved_memory -= 4096;

	mov	rax, QWORD PTR ?reserved_memory@@3_KA	; reserved_memory
	sub	rax, 4096				; 00001000H
	mov	QWORD PTR ?reserved_memory@@3_KA, rax	; reserved_memory

; 88   : 		if (ram_bitmap_index > index) ram_bitmap_index = index;

	mov	rax, QWORD PTR index$[rsp]
	cmp	QWORD PTR ?ram_bitmap_index@@3_KA, rax	; ram_bitmap_index
	jbe	SHORT $LN1@pmmngr_unr
	mov	rax, QWORD PTR index$[rsp]
	mov	QWORD PTR ?ram_bitmap_index@@3_KA, rax	; ram_bitmap_index
$LN1@pmmngr_unr:
$LN2@pmmngr_unr:
$LN4@pmmngr_unr:

; 89   : 	}
; 90   : }

	add	rsp, 56					; 00000038H
	ret	0
?pmmngr_unreserve_page@@YAXPEAX@Z ENDP			; pmmngr_unreserve_page
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\pmmngr.cpp
_TEXT	SEGMENT
index$ = 32
addr$ = 64
?pmmngr_lock_page@@YAXPEAX@Z PROC			; pmmngr_lock_page

; 71   : void pmmngr_lock_page ( void* addr) {

$LN5:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 72   : 
; 73   : 	uint64_t index = (uint64_t)addr / 4096;

	xor	edx, edx
	mov	rax, QWORD PTR addr$[rsp]
	mov	ecx, 4096				; 00001000H
	div	rcx
	mov	QWORD PTR index$[rsp], rax

; 74   : 	if (ram_bitmap[index] == true) return;

	mov	rdx, QWORD PTR index$[rsp]
	lea	rcx, OFFSET FLAT:?ram_bitmap@@3VBitmap@@A ; ram_bitmap
	call	??ABitmap@@QEAA_N_K@Z			; Bitmap::operator[]
	movzx	eax, al
	cmp	eax, 1
	jne	SHORT $LN2@pmmngr_loc
	jmp	SHORT $LN3@pmmngr_loc
$LN2@pmmngr_loc:

; 75   : 	if (ram_bitmap.Set (index, true)) {

	mov	r8b, 1
	mov	rdx, QWORD PTR index$[rsp]
	lea	rcx, OFFSET FLAT:?ram_bitmap@@3VBitmap@@A ; ram_bitmap
	call	?Set@Bitmap@@QEAA_N_K_N@Z		; Bitmap::Set
	movzx	eax, al
	test	eax, eax
	je	SHORT $LN1@pmmngr_loc

; 76   : 		free_memory -= 4096;

	mov	rax, QWORD PTR ?free_memory@@3_KA	; free_memory
	sub	rax, 4096				; 00001000H
	mov	QWORD PTR ?free_memory@@3_KA, rax	; free_memory

; 77   : 		used_memory += 4096;

	mov	rax, QWORD PTR ?used_memory@@3_KA	; used_memory
	add	rax, 4096				; 00001000H
	mov	QWORD PTR ?used_memory@@3_KA, rax	; used_memory
$LN1@pmmngr_loc:
$LN3@pmmngr_loc:

; 78   : 	}
; 79   : }

	add	rsp, 56					; 00000038H
	ret	0
?pmmngr_lock_page@@YAXPEAX@Z ENDP			; pmmngr_lock_page
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\pmmngr.cpp
_TEXT	SEGMENT
i$1 = 0
bitmap_size$ = 32
buffer$ = 40
?pmmngr_init_bitmap@@YAX_KPEAX@Z PROC			; pmmngr_init_bitmap

; 61   : void pmmngr_init_bitmap (size_t bitmap_size, void* buffer) {

$LN6:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 24

; 62   : 
; 63   : 	ram_bitmap.Size = bitmap_size;

	mov	rax, QWORD PTR bitmap_size$[rsp]
	mov	QWORD PTR ?ram_bitmap@@3VBitmap@@A, rax

; 64   : 	ram_bitmap.Buffer = (uint8_t*)buffer;

	mov	rax, QWORD PTR buffer$[rsp]
	mov	QWORD PTR ?ram_bitmap@@3VBitmap@@A+8, rax

; 65   : 
; 66   : 	for (int i = 0; i < bitmap_size ; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@pmmngr_ini
$LN2@pmmngr_ini:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN3@pmmngr_ini:
	movsxd	rax, DWORD PTR i$1[rsp]
	cmp	rax, QWORD PTR bitmap_size$[rsp]
	jae	SHORT $LN1@pmmngr_ini

; 67   : 		*(uint8_t*)(ram_bitmap.Buffer + i) = 0;

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR ?ram_bitmap@@3VBitmap@@A+8
	mov	BYTE PTR [rcx+rax], 0

; 68   : 	}

	jmp	SHORT $LN2@pmmngr_ini
$LN1@pmmngr_ini:

; 69   : }

	add	rsp, 24
	ret	0
?pmmngr_init_bitmap@@YAX_KPEAX@Z ENDP			; pmmngr_init_bitmap
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\pmmngr.cpp
;	COMDAT ?Set@Bitmap@@QEAA_N_K_N@Z
_TEXT	SEGMENT
bitIndexer$ = 0
bitIndex$ = 1
tv145 = 4
byteIndex$ = 8
this$ = 32
index$ = 40
value$ = 48
?Set@Bitmap@@QEAA_N_K_N@Z PROC				; Bitmap::Set, COMDAT

; 41   : 	bool Set(uint64_t index, bool value) {

$LN5:
	mov	BYTE PTR [rsp+24], r8b
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 24

; 42   : 		
; 43   : 		if (index > Size * 8) return false;

	mov	rax, QWORD PTR this$[rsp]
	mov	rax, QWORD PTR [rax]
	shl	rax, 3
	cmp	QWORD PTR index$[rsp], rax
	jbe	SHORT $LN2@Set
	xor	al, al
	jmp	$LN3@Set
$LN2@Set:

; 44   : 
; 45   : 		uint64_t byteIndex = index / 8;

	xor	edx, edx
	mov	rax, QWORD PTR index$[rsp]
	mov	ecx, 8
	div	rcx
	mov	QWORD PTR byteIndex$[rsp], rax

; 46   : 		uint8_t  bitIndex = index % 8;

	xor	edx, edx
	mov	rax, QWORD PTR index$[rsp]
	mov	ecx, 8
	div	rcx
	mov	rax, rdx
	mov	BYTE PTR bitIndex$[rsp], al

; 47   : 		uint8_t  bitIndexer = 0x80 >> bitIndex;

	movzx	eax, BYTE PTR bitIndex$[rsp]
	mov	ecx, 128				; 00000080H
	mov	DWORD PTR tv145[rsp], ecx
	movzx	ecx, al
	mov	eax, DWORD PTR tv145[rsp]
	sar	eax, cl
	mov	BYTE PTR bitIndexer$[rsp], al

; 48   : 
; 49   : 		Buffer[byteIndex] &= -bitIndexer;

	mov	rax, QWORD PTR this$[rsp]
	mov	rax, QWORD PTR [rax+8]
	movzx	ecx, BYTE PTR bitIndexer$[rsp]
	neg	ecx
	mov	rdx, QWORD PTR byteIndex$[rsp]
	movzx	eax, BYTE PTR [rax+rdx]
	and	eax, ecx
	mov	rcx, QWORD PTR this$[rsp]
	mov	rcx, QWORD PTR [rcx+8]
	mov	rdx, QWORD PTR byteIndex$[rsp]
	mov	BYTE PTR [rcx+rdx], al

; 50   : 		if (value) {

	movzx	eax, BYTE PTR value$[rsp]
	test	eax, eax
	je	SHORT $LN1@Set

; 51   : 			Buffer[byteIndex] |= bitIndexer;

	mov	rax, QWORD PTR this$[rsp]
	mov	rax, QWORD PTR [rax+8]
	movzx	ecx, BYTE PTR bitIndexer$[rsp]
	mov	rdx, QWORD PTR byteIndex$[rsp]
	movzx	eax, BYTE PTR [rax+rdx]
	or	eax, ecx
	mov	rcx, QWORD PTR this$[rsp]
	mov	rcx, QWORD PTR [rcx+8]
	mov	rdx, QWORD PTR byteIndex$[rsp]
	mov	BYTE PTR [rcx+rdx], al
$LN1@Set:

; 52   : 		}
; 53   : 
; 54   : 		return false;

	xor	al, al
$LN3@Set:

; 55   : 	}

	add	rsp, 24
	ret	0
?Set@Bitmap@@QEAA_N_K_N@Z ENDP				; Bitmap::Set
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\pmmngr.cpp
;	COMDAT ??ABitmap@@QEAA_N_K@Z
_TEXT	SEGMENT
bitIndex$ = 0
bitIndexer$ = 1
tv94 = 4
byteIndex$ = 8
this$ = 32
index$ = 40
??ABitmap@@QEAA_N_K@Z PROC				; Bitmap::operator[], COMDAT

; 27   : 	bool operator[](uint64_t index) {

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 24

; 28   : 		
; 29   : 		if (index > Size * 8) return false;

	mov	rax, QWORD PTR this$[rsp]
	mov	rax, QWORD PTR [rax]
	shl	rax, 3
	cmp	QWORD PTR index$[rsp], rax
	jbe	SHORT $LN2@operator
	xor	al, al
	jmp	SHORT $LN3@operator
$LN2@operator:

; 30   : 		uint64_t byteIndex = index / 8;

	xor	edx, edx
	mov	rax, QWORD PTR index$[rsp]
	mov	ecx, 8
	div	rcx
	mov	QWORD PTR byteIndex$[rsp], rax

; 31   : 		uint8_t  bitIndex = index % 8;

	xor	edx, edx
	mov	rax, QWORD PTR index$[rsp]
	mov	ecx, 8
	div	rcx
	mov	rax, rdx
	mov	BYTE PTR bitIndex$[rsp], al

; 32   : 		uint8_t  bitIndexer = 0x80 >> bitIndex;

	movzx	eax, BYTE PTR bitIndex$[rsp]
	mov	ecx, 128				; 00000080H
	mov	DWORD PTR tv94[rsp], ecx
	movzx	ecx, al
	mov	eax, DWORD PTR tv94[rsp]
	sar	eax, cl
	mov	BYTE PTR bitIndexer$[rsp], al

; 33   : 
; 34   : 		if ((Buffer[byteIndex] & bitIndexer) > 0) {

	mov	rax, QWORD PTR this$[rsp]
	mov	rax, QWORD PTR [rax+8]
	mov	rcx, QWORD PTR byteIndex$[rsp]
	movzx	eax, BYTE PTR [rax+rcx]
	movzx	ecx, BYTE PTR bitIndexer$[rsp]
	and	eax, ecx
	test	eax, eax
	jle	SHORT $LN1@operator

; 35   : 			return true;

	mov	al, 1
	jmp	SHORT $LN3@operator
$LN1@operator:

; 36   : 		}
; 37   : 		return false;

	xor	al, al
$LN3@operator:

; 38   : 	}

	add	rsp, 24
	ret	0
??ABitmap@@QEAA_N_K@Z ENDP				; Bitmap::operator[]
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\pmmngr.cpp
_TEXT	SEGMENT
?pmmngr_get_used_ram@@YA_KXZ PROC			; pmmngr_get_used_ram

; 156  : 	return used_memory;

	mov	rax, QWORD PTR ?used_memory@@3_KA	; used_memory

; 157  : }

	ret	0
?pmmngr_get_used_ram@@YA_KXZ ENDP			; pmmngr_get_used_ram
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\pmmngr.cpp
_TEXT	SEGMENT
?pmmngr_get_free_ram@@YA_KXZ PROC			; pmmngr_get_free_ram

; 152  : 	return free_memory;

	mov	rax, QWORD PTR ?free_memory@@3_KA	; free_memory

; 153  : }

	ret	0
?pmmngr_get_free_ram@@YA_KXZ ENDP			; pmmngr_get_free_ram
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\pmmngr.cpp
_TEXT	SEGMENT
index$ = 32
addr$ = 64
?pmmngr_free@@YAXPEAX@Z PROC				; pmmngr_free

; 140  : {

$LN6:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 141  : 	uint64_t index = (uint64_t)addr / 4096;

	xor	edx, edx
	mov	rax, QWORD PTR addr$[rsp]
	mov	ecx, 4096				; 00001000H
	div	rcx
	mov	QWORD PTR index$[rsp], rax

; 142  : 	if (ram_bitmap[index] == false) return;

	mov	rdx, QWORD PTR index$[rsp]
	lea	rcx, OFFSET FLAT:?ram_bitmap@@3VBitmap@@A ; ram_bitmap
	call	??ABitmap@@QEAA_N_K@Z			; Bitmap::operator[]
	movzx	eax, al
	test	eax, eax
	jne	SHORT $LN3@pmmngr_fre
	jmp	SHORT $LN4@pmmngr_fre
$LN3@pmmngr_fre:

; 143  : 	if (ram_bitmap.Set (index, false)) {

	xor	r8d, r8d
	mov	rdx, QWORD PTR index$[rsp]
	lea	rcx, OFFSET FLAT:?ram_bitmap@@3VBitmap@@A ; ram_bitmap
	call	?Set@Bitmap@@QEAA_N_K_N@Z		; Bitmap::Set
	movzx	eax, al
	test	eax, eax
	je	SHORT $LN2@pmmngr_fre

; 144  : 		free_memory += 4096;

	mov	rax, QWORD PTR ?free_memory@@3_KA	; free_memory
	add	rax, 4096				; 00001000H
	mov	QWORD PTR ?free_memory@@3_KA, rax	; free_memory

; 145  : 		used_memory -= 4096;

	mov	rax, QWORD PTR ?used_memory@@3_KA	; used_memory
	sub	rax, 4096				; 00001000H
	mov	QWORD PTR ?used_memory@@3_KA, rax	; used_memory

; 146  : 		if (ram_bitmap_index > index) ram_bitmap_index = index;

	mov	rax, QWORD PTR index$[rsp]
	cmp	QWORD PTR ?ram_bitmap_index@@3_KA, rax	; ram_bitmap_index
	jbe	SHORT $LN1@pmmngr_fre
	mov	rax, QWORD PTR index$[rsp]
	mov	QWORD PTR ?ram_bitmap_index@@3_KA, rax	; ram_bitmap_index
$LN1@pmmngr_fre:
$LN2@pmmngr_fre:
$LN4@pmmngr_fre:

; 147  : 	}
; 148  : }

	add	rsp, 56					; 00000038H
	ret	0
?pmmngr_free@@YAXPEAX@Z ENDP				; pmmngr_free
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\pmmngr.cpp
_TEXT	SEGMENT
?pmmngr_alloc@@YAPEAXXZ PROC				; pmmngr_alloc

; 122  : {

$LN7:
	sub	rsp, 40					; 00000028H

; 123  : 	free_memory -= 4096 * 1;

	mov	rax, QWORD PTR ?free_memory@@3_KA	; free_memory
	sub	rax, 4096				; 00001000H
	mov	QWORD PTR ?free_memory@@3_KA, rax	; free_memory

; 124  : 	used_memory += 4096 * 1;

	mov	rax, QWORD PTR ?used_memory@@3_KA	; used_memory
	add	rax, 4096				; 00001000H
	mov	QWORD PTR ?used_memory@@3_KA, rax	; used_memory

; 125  : 	for (; ram_bitmap_index < ram_bitmap.Size * 8; ram_bitmap_index++) {

	jmp	SHORT $LN4@pmmngr_all
$LN3@pmmngr_all:
	mov	rax, QWORD PTR ?ram_bitmap_index@@3_KA	; ram_bitmap_index
	inc	rax
	mov	QWORD PTR ?ram_bitmap_index@@3_KA, rax	; ram_bitmap_index
$LN4@pmmngr_all:
	mov	rax, QWORD PTR ?ram_bitmap@@3VBitmap@@A
	shl	rax, 3
	cmp	QWORD PTR ?ram_bitmap_index@@3_KA, rax	; ram_bitmap_index
	jae	SHORT $LN2@pmmngr_all

; 126  : 		if (ram_bitmap[ram_bitmap_index] == true) continue;

	mov	rdx, QWORD PTR ?ram_bitmap_index@@3_KA	; ram_bitmap_index
	lea	rcx, OFFSET FLAT:?ram_bitmap@@3VBitmap@@A ; ram_bitmap
	call	??ABitmap@@QEAA_N_K@Z			; Bitmap::operator[]
	movzx	eax, al
	cmp	eax, 1
	jne	SHORT $LN1@pmmngr_all
	jmp	SHORT $LN3@pmmngr_all
$LN1@pmmngr_all:

; 127  : 		pmmngr_lock_page ((void*)(ram_bitmap_index * 4096));

	mov	rax, QWORD PTR ?ram_bitmap_index@@3_KA	; ram_bitmap_index
	imul	rax, 4096				; 00001000H
	mov	rcx, rax
	call	?pmmngr_lock_page@@YAXPEAX@Z		; pmmngr_lock_page

; 128  : 		return (void*)(ram_bitmap_index * 4096);

	mov	rax, QWORD PTR ?ram_bitmap_index@@3_KA	; ram_bitmap_index
	imul	rax, 4096				; 00001000H
	jmp	SHORT $LN5@pmmngr_all

; 129  : 	}

	jmp	SHORT $LN3@pmmngr_all
$LN2@pmmngr_all:

; 130  : 
; 131  : 	return NULL; //here we need to swap page to file

	xor	eax, eax
$LN5@pmmngr_all:

; 132  : }

	add	rsp, 40					; 00000028H
	ret	0
?pmmngr_alloc@@YAPEAXXZ ENDP				; pmmngr_alloc
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\pmmngr.cpp
_TEXT	SEGMENT
memory_size$ = 32
bitmap_size$ = 40
p$ = 48
_info$ = 80
?pmmngr_init@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z PROC	; pmmngr_init

; 101  : {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 102  : 	//! scan for memory above 1MB and set up the current pointer
; 103  : 
; 104  : 	uint64_t memory_size = _info->ram_size;

	mov	rax, QWORD PTR _info$[rsp]
	mov	rax, QWORD PTR [rax+20]
	mov	QWORD PTR memory_size$[rsp], rax

; 105  : 	free_memory = memory_size;

	mov	rax, QWORD PTR memory_size$[rsp]
	mov	QWORD PTR ?free_memory@@3_KA, rax	; free_memory

; 106  : 	uint64_t bitmap_size = memory_size / 4096 / 8 + 1;

	xor	edx, edx
	mov	rax, QWORD PTR memory_size$[rsp]
	mov	ecx, 4096				; 00001000H
	div	rcx
	xor	edx, edx
	mov	ecx, 8
	div	rcx
	inc	rax
	mov	QWORD PTR bitmap_size$[rsp], rax

; 107  : 	ram_bitmap_index = 0;

	mov	QWORD PTR ?ram_bitmap_index@@3_KA, 0	; ram_bitmap_index

; 108  : 
; 109  : 
; 110  : 	pmmngr_init_bitmap (bitmap_size, (void*)_info->phys_start);

	mov	rax, QWORD PTR _info$[rsp]
	mov	rdx, QWORD PTR [rax+4]
	mov	rcx, QWORD PTR bitmap_size$[rsp]
	call	?pmmngr_init_bitmap@@YAX_KPEAX@Z	; pmmngr_init_bitmap

; 111  : 	void * p = (void*)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR p$[rsp], rax

; 112  : }

	add	rsp, 72					; 00000048H
	ret	0
?pmmngr_init@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ENDP	; pmmngr_init
_TEXT	ENDS
END
