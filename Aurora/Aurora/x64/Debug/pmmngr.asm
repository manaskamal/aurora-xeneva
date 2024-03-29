; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?free_memory@@3_KA				; free_memory
PUBLIC	?reserved_memory@@3_KA				; reserved_memory
PUBLIC	?used_memory@@3_KA				; used_memory
PUBLIC	?ram_bitmap_index@@3_KA				; ram_bitmap_index
PUBLIC	?total_ram@@3_KA				; total_ram
PUBLIC	?bitmap_size@@3_KA				; bitmap_size
PUBLIC	?higher_half@@3_NA				; higher_half
PUBLIC	?ram_bitmap@@3VBitmap@@A			; ram_bitmap
_BSS	SEGMENT
?free_memory@@3_KA DQ 01H DUP (?)			; free_memory
?reserved_memory@@3_KA DQ 01H DUP (?)			; reserved_memory
?used_memory@@3_KA DQ 01H DUP (?)			; used_memory
?ram_bitmap_index@@3_KA DQ 01H DUP (?)			; ram_bitmap_index
?total_ram@@3_KA DQ 01H DUP (?)				; total_ram
?bitmap_size@@3_KA DQ 01H DUP (?)			; bitmap_size
?higher_half@@3_NA DB 01H DUP (?)			; higher_half
	ALIGN	4

?ram_bitmap@@3VBitmap@@A DB 010H DUP (?)		; ram_bitmap
_BSS	ENDS
CONST	SEGMENT
$SG3241	DB	'B', 00H
	ORG $+2
$SG3243	DB	'KB', 00H
	ORG $+1
$SG3245	DB	'MB', 00H
	ORG $+5
$SG3246	DB	'[aurora]: usable memory -> %x length -> %d %s', 0aH, 00H
	ORG $+1
$SG3247	DB	'[aurora]: total memory -> %d GB ', 0aH, 00H
	ORG $+6
$SG3249	DB	'[aurora]: bitmap initialized %d bytes', 0aH, 00H
	ORG $+1
$SG3272	DB	'[aurora]:pmmngr initialized', 0aH, 00H
	ORG $+3
$SG3300	DB	'Used RAM -> %d MB, Free RAM -> %d MB', 0aH, 00H
	ORG $+2
$SG3301	DB	'No more available pages', 0aH, 00H
CONST	ENDS
PUBLIC	?AuPmmngrInit@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z	; AuPmmngrInit
PUBLIC	AuPmmngrAlloc
PUBLIC	AuPmmngrAllocBlocks
PUBLIC	?AuPmmngrLockPages@@YAXPEAX_K@Z			; AuPmmngrLockPages
PUBLIC	?AuPmmngrLockPage@@YAXPEAX@Z			; AuPmmngrLockPage
PUBLIC	AuPmmngrFree
PUBLIC	AuPmmngrFreeBlocks
PUBLIC	?pmmngr_get_free_ram@@YA_KXZ			; pmmngr_get_free_ram
PUBLIC	?pmmngr_get_used_ram@@YA_KXZ			; pmmngr_get_used_ram
PUBLIC	?pmmngr_get_total_ram@@YA_KXZ			; pmmngr_get_total_ram
PUBLIC	?AuPmmngrMoveHigher@@YAXXZ			; AuPmmngrMoveHigher
PUBLIC	?AuPmmngrSetHighHalf@@YAX_N@Z			; AuPmmngrSetHighHalf
PUBLIC	?pmmngr_get_ram_bitmap_size@@YA_KXZ		; pmmngr_get_ram_bitmap_size
PUBLIC	p2v
PUBLIC	v2p
PUBLIC	?is_higher_half@@YA_NXZ				; is_higher_half
PUBLIC	??ABitmap@@QEAA_N_K@Z				; Bitmap::operator[]
PUBLIC	?Set@Bitmap@@QEAA_N_K_N@Z			; Bitmap::Set
PUBLIC	?AuPmmngrInitBitmap@@YAX_KPEAX@Z		; AuPmmngrInitBitmap
PUBLIC	?AuPmmngrUnreservePage@@YAXPEAX@Z		; AuPmmngrUnreservePage
EXTRN	memset:PROC
EXTRN	memcpy:PROC
EXTRN	printf:PROC
EXTRN	x64_cli:PROC
EXTRN	x64_hlt:PROC
pdata	SEGMENT
$pdata$?AuPmmngrInit@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD imagerel $LN16
	DD	imagerel $LN16+958
	DD	imagerel $unwind$?AuPmmngrInit@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z
$pdata$AuPmmngrAlloc DD imagerel $LN9
	DD	imagerel $LN9+245
	DD	imagerel $unwind$AuPmmngrAlloc
$pdata$AuPmmngrAllocBlocks DD imagerel $LN6
	DD	imagerel $LN6+77
	DD	imagerel $unwind$AuPmmngrAllocBlocks
$pdata$?AuPmmngrLockPages@@YAXPEAX_K@Z DD imagerel $LN6
	DD	imagerel $LN6+84
	DD	imagerel $unwind$?AuPmmngrLockPages@@YAXPEAX_K@Z
$pdata$?AuPmmngrLockPage@@YAXPEAX@Z DD imagerel $LN5
	DD	imagerel $LN5+128
	DD	imagerel $unwind$?AuPmmngrLockPage@@YAXPEAX@Z
$pdata$AuPmmngrFree DD imagerel $LN6
	DD	imagerel $LN6+153
	DD	imagerel $unwind$AuPmmngrFree
$pdata$AuPmmngrFreeBlocks DD imagerel $LN6
	DD	imagerel $LN6+86
	DD	imagerel $unwind$AuPmmngrFreeBlocks
$pdata$?AuPmmngrMoveHigher@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+35
	DD	imagerel $unwind$?AuPmmngrMoveHigher@@YAXXZ
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
$pdata$?AuPmmngrInitBitmap@@YAX_KPEAX@Z DD imagerel $LN6
	DD	imagerel $LN6+88
	DD	imagerel $unwind$?AuPmmngrInitBitmap@@YAX_KPEAX@Z
$pdata$?AuPmmngrUnreservePage@@YAXPEAX@Z DD imagerel $LN6
	DD	imagerel $LN6+153
	DD	imagerel $unwind$?AuPmmngrUnreservePage@@YAXPEAX@Z
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
$unwind$?AuPmmngrInit@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD 020c01H
	DD	013010cH
$unwind$AuPmmngrAlloc DD 010401H
	DD	06204H
$unwind$AuPmmngrAllocBlocks DD 010801H
	DD	06208H
$unwind$?AuPmmngrLockPages@@YAXPEAX_K@Z DD 010e01H
	DD	0620eH
$unwind$?AuPmmngrLockPage@@YAXPEAX@Z DD 010901H
	DD	06209H
$unwind$AuPmmngrFree DD 010901H
	DD	06209H
$unwind$AuPmmngrFreeBlocks DD 010d01H
	DD	0620dH
$unwind$?AuPmmngrMoveHigher@@YAXXZ DD 010401H
	DD	04204H
$unwind$?AuPmmngrInitBitmap@@YAX_KPEAX@Z DD 010e01H
	DD	0220eH
$unwind$?AuPmmngrUnreservePage@@YAXPEAX@Z DD 010901H
	DD	06209H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\pmmngr.cpp
_TEXT	SEGMENT
index$ = 32
addr$ = 64
?AuPmmngrUnreservePage@@YAXPEAX@Z PROC			; AuPmmngrUnreservePage

; 98   : void AuPmmngrUnreservePage (void* addr) {

$LN6:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 99   : 
; 100  : 	uint64_t index = (uint64_t)addr / 4096;

	xor	edx, edx
	mov	rax, QWORD PTR addr$[rsp]
	mov	ecx, 4096				; 00001000H
	div	rcx
	mov	QWORD PTR index$[rsp], rax

; 101  : 	if (ram_bitmap[index] == false) return;

	mov	rdx, QWORD PTR index$[rsp]
	lea	rcx, OFFSET FLAT:?ram_bitmap@@3VBitmap@@A ; ram_bitmap
	call	??ABitmap@@QEAA_N_K@Z			; Bitmap::operator[]
	movzx	eax, al
	test	eax, eax
	jne	SHORT $LN3@AuPmmngrUn
	jmp	SHORT $LN4@AuPmmngrUn
$LN3@AuPmmngrUn:

; 102  : 	if (ram_bitmap.Set(index, false)) {

	xor	r8d, r8d
	mov	rdx, QWORD PTR index$[rsp]
	lea	rcx, OFFSET FLAT:?ram_bitmap@@3VBitmap@@A ; ram_bitmap
	call	?Set@Bitmap@@QEAA_N_K_N@Z		; Bitmap::Set
	movzx	eax, al
	test	eax, eax
	je	SHORT $LN2@AuPmmngrUn

; 103  : 		free_memory += 4096;

	mov	rax, QWORD PTR ?free_memory@@3_KA	; free_memory
	add	rax, 4096				; 00001000H
	mov	QWORD PTR ?free_memory@@3_KA, rax	; free_memory

; 104  : 		reserved_memory -= 4096;

	mov	rax, QWORD PTR ?reserved_memory@@3_KA	; reserved_memory
	sub	rax, 4096				; 00001000H
	mov	QWORD PTR ?reserved_memory@@3_KA, rax	; reserved_memory

; 105  : 		if (ram_bitmap_index > index) ram_bitmap_index = index;

	mov	rax, QWORD PTR index$[rsp]
	cmp	QWORD PTR ?ram_bitmap_index@@3_KA, rax	; ram_bitmap_index
	jbe	SHORT $LN1@AuPmmngrUn
	mov	rax, QWORD PTR index$[rsp]
	mov	QWORD PTR ?ram_bitmap_index@@3_KA, rax	; ram_bitmap_index
$LN1@AuPmmngrUn:
$LN2@AuPmmngrUn:
$LN4@AuPmmngrUn:

; 106  : 	}
; 107  : }

	add	rsp, 56					; 00000038H
	ret	0
?AuPmmngrUnreservePage@@YAXPEAX@Z ENDP			; AuPmmngrUnreservePage
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\pmmngr.cpp
_TEXT	SEGMENT
i$1 = 0
bitmap_size$ = 32
buffer$ = 40
?AuPmmngrInitBitmap@@YAX_KPEAX@Z PROC			; AuPmmngrInitBitmap

; 70   : void AuPmmngrInitBitmap (size_t bitmap_size, void* buffer) {

$LN6:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 24

; 71   : 
; 72   : 	ram_bitmap.Size = bitmap_size;

	mov	rax, QWORD PTR bitmap_size$[rsp]
	mov	QWORD PTR ?ram_bitmap@@3VBitmap@@A, rax

; 73   : 	ram_bitmap.Buffer = (uint8_t*)buffer;

	mov	rax, QWORD PTR buffer$[rsp]
	mov	QWORD PTR ?ram_bitmap@@3VBitmap@@A+8, rax

; 74   : 
; 75   : 	for (int i = 0; i < bitmap_size ; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@AuPmmngrIn
$LN2@AuPmmngrIn:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN3@AuPmmngrIn:
	movsxd	rax, DWORD PTR i$1[rsp]
	cmp	rax, QWORD PTR bitmap_size$[rsp]
	jae	SHORT $LN1@AuPmmngrIn

; 76   : 		*(uint8_t*)(ram_bitmap.Buffer + i) = 0;

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR ?ram_bitmap@@3VBitmap@@A+8
	mov	BYTE PTR [rcx+rax], 0

; 77   : 	}

	jmp	SHORT $LN2@AuPmmngrIn
$LN1@AuPmmngrIn:

; 78   : }

	add	rsp, 24
	ret	0
?AuPmmngrInitBitmap@@YAX_KPEAX@Z ENDP			; AuPmmngrInitBitmap
_TEXT	ENDS
; Function compile flags: /Odtpy
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

; 50   : 	bool Set(uint64_t index, bool value) {

$LN5:
	mov	BYTE PTR [rsp+24], r8b
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 24

; 51   : 		
; 52   : 		if (index > Size * 8) return false;

	mov	rax, QWORD PTR this$[rsp]
	mov	rax, QWORD PTR [rax]
	shl	rax, 3
	cmp	QWORD PTR index$[rsp], rax
	jbe	SHORT $LN2@Set
	xor	al, al
	jmp	$LN3@Set
$LN2@Set:

; 53   : 
; 54   : 		uint64_t byteIndex = index / 8;

	xor	edx, edx
	mov	rax, QWORD PTR index$[rsp]
	mov	ecx, 8
	div	rcx
	mov	QWORD PTR byteIndex$[rsp], rax

; 55   : 		uint8_t  bitIndex = index % 8;

	xor	edx, edx
	mov	rax, QWORD PTR index$[rsp]
	mov	ecx, 8
	div	rcx
	mov	rax, rdx
	mov	BYTE PTR bitIndex$[rsp], al

; 56   : 		uint8_t  bitIndexer = 0x80 >> bitIndex;

	movzx	eax, BYTE PTR bitIndex$[rsp]
	mov	ecx, 128				; 00000080H
	mov	DWORD PTR tv145[rsp], ecx
	movzx	ecx, al
	mov	eax, DWORD PTR tv145[rsp]
	sar	eax, cl
	mov	BYTE PTR bitIndexer$[rsp], al

; 57   : 	
; 58   : 		Buffer[byteIndex] &= ~bitIndexer;

	mov	rax, QWORD PTR this$[rsp]
	mov	rax, QWORD PTR [rax+8]
	movzx	ecx, BYTE PTR bitIndexer$[rsp]
	not	ecx
	mov	rdx, QWORD PTR byteIndex$[rsp]
	movzx	eax, BYTE PTR [rax+rdx]
	and	eax, ecx
	mov	rcx, QWORD PTR this$[rsp]
	mov	rcx, QWORD PTR [rcx+8]
	mov	rdx, QWORD PTR byteIndex$[rsp]
	mov	BYTE PTR [rcx+rdx], al

; 59   : 		if (value) {

	movzx	eax, BYTE PTR value$[rsp]
	test	eax, eax
	je	SHORT $LN1@Set

; 60   : 			Buffer[byteIndex] |= bitIndexer;	

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

; 61   : 		}
; 62   : 
; 63   : 		return true;

	mov	al, 1
$LN3@Set:

; 64   : 	}

	add	rsp, 24
	ret	0
?Set@Bitmap@@QEAA_N_K_N@Z ENDP				; Bitmap::Set
_TEXT	ENDS
; Function compile flags: /Odtpy
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

; 36   : 	bool operator[](uint64_t index) {

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 24

; 37   : 		
; 38   : 		if (index > Size * 8) return false;

	mov	rax, QWORD PTR this$[rsp]
	mov	rax, QWORD PTR [rax]
	shl	rax, 3
	cmp	QWORD PTR index$[rsp], rax
	jbe	SHORT $LN2@operator
	xor	al, al
	jmp	SHORT $LN3@operator
$LN2@operator:

; 39   : 		uint64_t byteIndex = index / 8;

	xor	edx, edx
	mov	rax, QWORD PTR index$[rsp]
	mov	ecx, 8
	div	rcx
	mov	QWORD PTR byteIndex$[rsp], rax

; 40   : 		uint8_t  bitIndex = index % 8;

	xor	edx, edx
	mov	rax, QWORD PTR index$[rsp]
	mov	ecx, 8
	div	rcx
	mov	rax, rdx
	mov	BYTE PTR bitIndex$[rsp], al

; 41   : 		uint8_t  bitIndexer = 0x80 >> bitIndex;

	movzx	eax, BYTE PTR bitIndex$[rsp]
	mov	ecx, 128				; 00000080H
	mov	DWORD PTR tv94[rsp], ecx
	movzx	ecx, al
	mov	eax, DWORD PTR tv94[rsp]
	sar	eax, cl
	mov	BYTE PTR bitIndexer$[rsp], al

; 42   : 
; 43   : 		if ((Buffer[byteIndex] & bitIndexer) > 0) {

	mov	rax, QWORD PTR this$[rsp]
	mov	rax, QWORD PTR [rax+8]
	mov	rcx, QWORD PTR byteIndex$[rsp]
	movzx	eax, BYTE PTR [rax+rcx]
	movzx	ecx, BYTE PTR bitIndexer$[rsp]
	and	eax, ecx
	test	eax, eax
	jle	SHORT $LN1@operator

; 44   : 			return true;

	mov	al, 1
	jmp	SHORT $LN3@operator
$LN1@operator:

; 45   : 		}
; 46   : 		return false;

	xor	al, al
$LN3@operator:

; 47   : 	}

	add	rsp, 24
	ret	0
??ABitmap@@QEAA_N_K@Z ENDP				; Bitmap::operator[]
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\pmmngr.cpp
_TEXT	SEGMENT
?is_higher_half@@YA_NXZ PROC				; is_higher_half

; 215  : 	return higher_half;

	movzx	eax, BYTE PTR ?higher_half@@3_NA	; higher_half

; 216  : }

	ret	0
?is_higher_half@@YA_NXZ ENDP				; is_higher_half
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\pmmngr.cpp
_TEXT	SEGMENT
vaddr$ = 8
v2p	PROC

; 207  : uint64_t v2p (uint64_t vaddr) {

	mov	QWORD PTR [rsp+8], rcx

; 208  : 	if (higher_half)

	movzx	eax, BYTE PTR ?higher_half@@3_NA	; higher_half
	test	eax, eax
	je	SHORT $LN2@v2p

; 209  : 		return (vaddr - PHYSICAL_MEMORY_BASE);

	mov	rax, 140737488355328			; 0000800000000000H
	mov	rcx, QWORD PTR vaddr$[rsp]
	add	rcx, rax
	mov	rax, rcx
	jmp	SHORT $LN3@v2p

; 210  : 	else 

	jmp	SHORT $LN1@v2p
$LN2@v2p:

; 211  : 		return vaddr;

	mov	rax, QWORD PTR vaddr$[rsp]
$LN1@v2p:
$LN3@v2p:

; 212  : }

	fatret	0
v2p	ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\pmmngr.cpp
_TEXT	SEGMENT
addr$ = 8
p2v	PROC

; 200  : uint64_t p2v (uint64_t addr) {

	mov	QWORD PTR [rsp+8], rcx

; 201  : 	if (higher_half)

	movzx	eax, BYTE PTR ?higher_half@@3_NA	; higher_half
	test	eax, eax
	je	SHORT $LN2@p2v

; 202  : 		return (PHYSICAL_MEMORY_BASE + addr);

	mov	rax, 140737488355328			; 0000800000000000H
	mov	rcx, QWORD PTR addr$[rsp]
	sub	rcx, rax
	mov	rax, rcx
	jmp	SHORT $LN3@p2v

; 203  : 	else

	jmp	SHORT $LN1@p2v
$LN2@p2v:

; 204  : 		return addr;

	mov	rax, QWORD PTR addr$[rsp]
$LN1@p2v:
$LN3@p2v:

; 205  : }

	fatret	0
p2v	ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\pmmngr.cpp
_TEXT	SEGMENT
?pmmngr_get_ram_bitmap_size@@YA_KXZ PROC		; pmmngr_get_ram_bitmap_size

; 297  : 	return bitmap_size;

	mov	rax, QWORD PTR ?bitmap_size@@3_KA	; bitmap_size

; 298  : }

	ret	0
?pmmngr_get_ram_bitmap_size@@YA_KXZ ENDP		; pmmngr_get_ram_bitmap_size
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\pmmngr.cpp
_TEXT	SEGMENT
value$ = 8
?AuPmmngrSetHighHalf@@YAX_N@Z PROC			; AuPmmngrSetHighHalf

; 196  : void AuPmmngrSetHighHalf(bool value) {

	mov	BYTE PTR [rsp+8], cl

; 197  : 	higher_half = value;

	movzx	eax, BYTE PTR value$[rsp]
	mov	BYTE PTR ?higher_half@@3_NA, al		; higher_half

; 198  : }

	ret	0
?AuPmmngrSetHighHalf@@YAX_N@Z ENDP			; AuPmmngrSetHighHalf
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\pmmngr.cpp
_TEXT	SEGMENT
?AuPmmngrMoveHigher@@YAXXZ PROC				; AuPmmngrMoveHigher

; 191  : void AuPmmngrMoveHigher () {

$LN3:
	sub	rsp, 40					; 00000028H

; 192  : 	higher_half = true;

	mov	BYTE PTR ?higher_half@@3_NA, 1		; higher_half

; 193  : 	ram_bitmap.Buffer = (uint8_t*)p2v((uint64_t)ram_bitmap.Buffer);

	mov	rcx, QWORD PTR ?ram_bitmap@@3VBitmap@@A+8
	call	p2v
	mov	QWORD PTR ?ram_bitmap@@3VBitmap@@A+8, rax

; 194  : }

	add	rsp, 40					; 00000028H
	ret	0
?AuPmmngrMoveHigher@@YAXXZ ENDP				; AuPmmngrMoveHigher
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\pmmngr.cpp
_TEXT	SEGMENT
?pmmngr_get_total_ram@@YA_KXZ PROC			; pmmngr_get_total_ram

; 292  : 	return total_ram;

	mov	rax, QWORD PTR ?total_ram@@3_KA		; total_ram

; 293  : }

	ret	0
?pmmngr_get_total_ram@@YA_KXZ ENDP			; pmmngr_get_total_ram
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\pmmngr.cpp
_TEXT	SEGMENT
?pmmngr_get_used_ram@@YA_KXZ PROC			; pmmngr_get_used_ram

; 287  : 	return used_memory;

	mov	rax, QWORD PTR ?used_memory@@3_KA	; used_memory

; 288  : }

	ret	0
?pmmngr_get_used_ram@@YA_KXZ ENDP			; pmmngr_get_used_ram
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\pmmngr.cpp
_TEXT	SEGMENT
?pmmngr_get_free_ram@@YA_KXZ PROC			; pmmngr_get_free_ram

; 282  : 	return free_memory;

	mov	rax, QWORD PTR ?free_memory@@3_KA	; free_memory

; 283  : }

	ret	0
?pmmngr_get_free_ram@@YA_KXZ ENDP			; pmmngr_get_free_ram
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\pmmngr.cpp
_TEXT	SEGMENT
i$1 = 32
address$ = 40
addr$ = 64
count$ = 72
AuPmmngrFreeBlocks PROC

; 272  : void AuPmmngrFreeBlocks(void* addr, int count) {

$LN6:
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 273  : 	uint64_t * address = (uint64_t*)addr;

	mov	rax, QWORD PTR addr$[rsp]
	mov	QWORD PTR address$[rsp], rax

; 274  : 	for (uint32_t i = 0; i < count; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@AuPmmngrFr
$LN2@AuPmmngrFr:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN3@AuPmmngrFr:
	mov	eax, DWORD PTR count$[rsp]
	cmp	DWORD PTR i$1[rsp], eax
	jae	SHORT $LN1@AuPmmngrFr

; 275  : 		AuPmmngrFree(address);

	mov	rcx, QWORD PTR address$[rsp]
	call	AuPmmngrFree

; 276  : 		address += 0x1000;

	mov	rax, QWORD PTR address$[rsp]
	add	rax, 32768				; 00008000H
	mov	QWORD PTR address$[rsp], rax

; 277  : 	}

	jmp	SHORT $LN2@AuPmmngrFr
$LN1@AuPmmngrFr:

; 278  : }

	add	rsp, 56					; 00000038H
	ret	0
AuPmmngrFreeBlocks ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\pmmngr.cpp
_TEXT	SEGMENT
index$ = 32
addr$ = 64
AuPmmngrFree PROC

; 257  : {

$LN6:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 258  : 	uint64_t index = (uint64_t)addr / 4096;

	xor	edx, edx
	mov	rax, QWORD PTR addr$[rsp]
	mov	ecx, 4096				; 00001000H
	div	rcx
	mov	QWORD PTR index$[rsp], rax

; 259  : 	if (ram_bitmap[index] == false) return;

	mov	rdx, QWORD PTR index$[rsp]
	lea	rcx, OFFSET FLAT:?ram_bitmap@@3VBitmap@@A ; ram_bitmap
	call	??ABitmap@@QEAA_N_K@Z			; Bitmap::operator[]
	movzx	eax, al
	test	eax, eax
	jne	SHORT $LN3@AuPmmngrFr
	jmp	SHORT $LN4@AuPmmngrFr
$LN3@AuPmmngrFr:

; 260  : 	if (ram_bitmap.Set (index, false)) {

	xor	r8d, r8d
	mov	rdx, QWORD PTR index$[rsp]
	lea	rcx, OFFSET FLAT:?ram_bitmap@@3VBitmap@@A ; ram_bitmap
	call	?Set@Bitmap@@QEAA_N_K_N@Z		; Bitmap::Set
	movzx	eax, al
	test	eax, eax
	je	SHORT $LN2@AuPmmngrFr

; 261  : 		free_memory += 4096;

	mov	rax, QWORD PTR ?free_memory@@3_KA	; free_memory
	add	rax, 4096				; 00001000H
	mov	QWORD PTR ?free_memory@@3_KA, rax	; free_memory

; 262  : 		used_memory -= 4096 * 1;	

	mov	rax, QWORD PTR ?used_memory@@3_KA	; used_memory
	sub	rax, 4096				; 00001000H
	mov	QWORD PTR ?used_memory@@3_KA, rax	; used_memory

; 263  : 		if (ram_bitmap_index > index) {

	mov	rax, QWORD PTR index$[rsp]
	cmp	QWORD PTR ?ram_bitmap_index@@3_KA, rax	; ram_bitmap_index
	jbe	SHORT $LN1@AuPmmngrFr

; 264  : 			ram_bitmap_index = index;

	mov	rax, QWORD PTR index$[rsp]
	mov	QWORD PTR ?ram_bitmap_index@@3_KA, rax	; ram_bitmap_index
$LN1@AuPmmngrFr:
$LN2@AuPmmngrFr:
$LN4@AuPmmngrFr:

; 265  : 		}
; 266  : 	}
; 267  : }

	add	rsp, 56					; 00000038H
	ret	0
AuPmmngrFree ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\pmmngr.cpp
_TEXT	SEGMENT
index$ = 32
addr$ = 64
?AuPmmngrLockPage@@YAXPEAX@Z PROC			; AuPmmngrLockPage

; 81   : void AuPmmngrLockPage ( void* addr) {

$LN5:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 82   : 
; 83   : 	uint64_t index = (uint64_t)addr / 4096;

	xor	edx, edx
	mov	rax, QWORD PTR addr$[rsp]
	mov	ecx, 4096				; 00001000H
	div	rcx
	mov	QWORD PTR index$[rsp], rax

; 84   : 	if (ram_bitmap[index] == true) return;

	mov	rdx, QWORD PTR index$[rsp]
	lea	rcx, OFFSET FLAT:?ram_bitmap@@3VBitmap@@A ; ram_bitmap
	call	??ABitmap@@QEAA_N_K@Z			; Bitmap::operator[]
	movzx	eax, al
	cmp	eax, 1
	jne	SHORT $LN2@AuPmmngrLo
	jmp	SHORT $LN3@AuPmmngrLo
$LN2@AuPmmngrLo:

; 85   : 	if (ram_bitmap.Set (index, true)) {

	mov	r8b, 1
	mov	rdx, QWORD PTR index$[rsp]
	lea	rcx, OFFSET FLAT:?ram_bitmap@@3VBitmap@@A ; ram_bitmap
	call	?Set@Bitmap@@QEAA_N_K_N@Z		; Bitmap::Set
	movzx	eax, al
	test	eax, eax
	je	SHORT $LN1@AuPmmngrLo

; 86   : 		free_memory -= 4096;

	mov	rax, QWORD PTR ?free_memory@@3_KA	; free_memory
	sub	rax, 4096				; 00001000H
	mov	QWORD PTR ?free_memory@@3_KA, rax	; free_memory

; 87   : 		reserved_memory += 4096;

	mov	rax, QWORD PTR ?reserved_memory@@3_KA	; reserved_memory
	add	rax, 4096				; 00001000H
	mov	QWORD PTR ?reserved_memory@@3_KA, rax	; reserved_memory
$LN1@AuPmmngrLo:
$LN3@AuPmmngrLo:

; 88   : 	}
; 89   : }

	add	rsp, 56					; 00000038H
	ret	0
?AuPmmngrLockPage@@YAXPEAX@Z ENDP			; AuPmmngrLockPage
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\pmmngr.cpp
_TEXT	SEGMENT
i$1 = 32
addr$ = 64
size$ = 72
?AuPmmngrLockPages@@YAXPEAX_K@Z PROC			; AuPmmngrLockPages

; 92   : void AuPmmngrLockPages (void *addr, size_t size) {

$LN6:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 93   : 	for (int i = 0; i < size; i++) 

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@AuPmmngrLo
$LN2@AuPmmngrLo:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN3@AuPmmngrLo:
	movsxd	rax, DWORD PTR i$1[rsp]
	cmp	rax, QWORD PTR size$[rsp]
	jae	SHORT $LN1@AuPmmngrLo

; 94   : 		AuPmmngrLockPage ((void*)((size_t)addr + i * 4096));

	mov	eax, DWORD PTR i$1[rsp]
	imul	eax, 4096				; 00001000H
	cdqe
	mov	rcx, QWORD PTR addr$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	rcx, rax
	call	?AuPmmngrLockPage@@YAXPEAX@Z		; AuPmmngrLockPage
	jmp	SHORT $LN2@AuPmmngrLo
$LN1@AuPmmngrLo:

; 95   : }

	add	rsp, 56					; 00000038H
	ret	0
?AuPmmngrLockPages@@YAXPEAX_K@Z ENDP			; AuPmmngrLockPages
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\pmmngr.cpp
_TEXT	SEGMENT
i$1 = 32
first$ = 40
size$ = 64
AuPmmngrAllocBlocks PROC

; 243  : void* AuPmmngrAllocBlocks(int size) {

$LN6:
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 56					; 00000038H

; 244  : 	void *first = AuPmmngrAlloc();

	call	AuPmmngrAlloc
	mov	QWORD PTR first$[rsp], rax

; 245  : 	for (int i = 0; i < size / 4096; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@AuPmmngrAl
$LN2@AuPmmngrAl:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN3@AuPmmngrAl:
	mov	eax, DWORD PTR size$[rsp]
	cdq
	and	edx, 4095				; 00000fffH
	add	eax, edx
	sar	eax, 12
	cmp	DWORD PTR i$1[rsp], eax
	jge	SHORT $LN1@AuPmmngrAl

; 246  : 		AuPmmngrAlloc();

	call	AuPmmngrAlloc

; 247  : 	}

	jmp	SHORT $LN2@AuPmmngrAl
$LN1@AuPmmngrAl:

; 248  : 
; 249  : 	return first; //here we need to swap page to file

	mov	rax, QWORD PTR first$[rsp]

; 250  : }

	add	rsp, 56					; 00000038H
	ret	0
AuPmmngrAllocBlocks ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\pmmngr.cpp
_TEXT	SEGMENT
tv77 = 32
AuPmmngrAlloc PROC

; 225  : {

$LN9:
	sub	rsp, 56					; 00000038H

; 226  : 	
; 227  : 	for (; ram_bitmap_index < ram_bitmap.Size * 8; ram_bitmap_index++) {

	jmp	SHORT $LN6@AuPmmngrAl
$LN5@AuPmmngrAl:
	mov	rax, QWORD PTR ?ram_bitmap_index@@3_KA	; ram_bitmap_index
	inc	rax
	mov	QWORD PTR ?ram_bitmap_index@@3_KA, rax	; ram_bitmap_index
$LN6@AuPmmngrAl:
	mov	rax, QWORD PTR ?ram_bitmap@@3VBitmap@@A
	shl	rax, 3
	cmp	QWORD PTR ?ram_bitmap_index@@3_KA, rax	; ram_bitmap_index
	jae	SHORT $LN4@AuPmmngrAl

; 228  : 		if (ram_bitmap[ram_bitmap_index] == true) continue;

	mov	rdx, QWORD PTR ?ram_bitmap_index@@3_KA	; ram_bitmap_index
	lea	rcx, OFFSET FLAT:?ram_bitmap@@3VBitmap@@A ; ram_bitmap
	call	??ABitmap@@QEAA_N_K@Z			; Bitmap::operator[]
	movzx	eax, al
	cmp	eax, 1
	jne	SHORT $LN3@AuPmmngrAl
	jmp	SHORT $LN5@AuPmmngrAl
$LN3@AuPmmngrAl:

; 229  : 		AuPmmngrLockPage((void*)(ram_bitmap_index * 4096));

	mov	rax, QWORD PTR ?ram_bitmap_index@@3_KA	; ram_bitmap_index
	imul	rax, 4096				; 00001000H
	mov	rcx, rax
	call	?AuPmmngrLockPage@@YAXPEAX@Z		; AuPmmngrLockPage

; 230  : 		used_memory += 4096 * 1;

	mov	rax, QWORD PTR ?used_memory@@3_KA	; used_memory
	add	rax, 4096				; 00001000H
	mov	QWORD PTR ?used_memory@@3_KA, rax	; used_memory

; 231  : 		return (void*)(ram_bitmap_index * 4096);

	mov	rax, QWORD PTR ?ram_bitmap_index@@3_KA	; ram_bitmap_index
	imul	rax, 4096				; 00001000H
	jmp	SHORT $LN7@AuPmmngrAl

; 232  : 	}

	jmp	SHORT $LN5@AuPmmngrAl
$LN4@AuPmmngrAl:

; 233  : 
; 234  : 	x64_cli();

	call	x64_cli

; 235  : 	printf ("Used RAM -> %d MB, Free RAM -> %d MB\n", used_memory /1024 / 1024, free_memory / 1024 / 1024);

	xor	edx, edx
	mov	rax, QWORD PTR ?free_memory@@3_KA	; free_memory
	mov	ecx, 1024				; 00000400H
	div	rcx
	xor	edx, edx
	mov	ecx, 1024				; 00000400H
	div	rcx
	mov	QWORD PTR tv77[rsp], rax
	xor	edx, edx
	mov	rax, QWORD PTR ?used_memory@@3_KA	; used_memory
	mov	ecx, 1024				; 00000400H
	div	rcx
	xor	edx, edx
	mov	ecx, 1024				; 00000400H
	div	rcx
	mov	rcx, QWORD PTR tv77[rsp]
	mov	r8, rcx
	mov	rdx, rax
	lea	rcx, OFFSET FLAT:$SG3300
	call	printf

; 236  : 	printf ("No more available pages\n");

	lea	rcx, OFFSET FLAT:$SG3301
	call	printf

; 237  : 	x64_hlt();

	call	x64_hlt
$LN2@AuPmmngrAl:

; 238  : 	for(;;);

	jmp	SHORT $LN2@AuPmmngrAl

; 239  : 	return NULL; //here we need to swap page to file

	xor	eax, eax
$LN7@AuPmmngrAl:

; 240  : }

	add	rsp, 56					; 00000038H
	ret	0
AuPmmngrAlloc ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\pmmngr.cpp
_TEXT	SEGMENT
efi_mem$1 = 32
allocated_count$ = 40
i$2 = 48
i$3 = 56
bitmap_area$ = 64
efi_mem$4 = 72
unit$5 = 80
allocated_stack$ = 88
bitmap_size$ = 96
size_in_mb_kb$6 = 104
memmap_entries$ = 112
address$ = 120
address$7 = 128
info$ = 160
?AuPmmngrInit@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z PROC	; AuPmmngrInit

; 117  : {

$LN16:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 152				; 00000098H

; 118  : 	free_memory = 0;

	mov	QWORD PTR ?free_memory@@3_KA, 0		; free_memory

; 119  : 	bitmap_size = 0;

	mov	QWORD PTR ?bitmap_size@@3_KA, 0		; bitmap_size

; 120  : 	total_ram = 0;

	mov	QWORD PTR ?total_ram@@3_KA, 0		; total_ram

; 121  : 	ram_bitmap_index = 0;

	mov	QWORD PTR ?ram_bitmap_index@@3_KA, 0	; ram_bitmap_index

; 122  : 
; 123  : 	uint64_t memmap_entries = info->mem_map_size / info->descriptor_size;

	xor	edx, edx
	mov	rax, QWORD PTR info$[rsp]
	mov	rax, QWORD PTR [rax+36]
	mov	rcx, QWORD PTR info$[rsp]
	div	QWORD PTR [rcx+28]
	mov	QWORD PTR memmap_entries$[rsp], rax

; 124  : 	void* bitmap_area = 0;

	mov	QWORD PTR bitmap_area$[rsp], 0

; 125  : 
; 126  : 	/* Scan a suitable area for the bitmap */
; 127  : 	for (size_t i = 0; i < memmap_entries; i++) {

	mov	QWORD PTR i$2[rsp], 0
	jmp	SHORT $LN13@AuPmmngrIn
$LN12@AuPmmngrIn:
	mov	rax, QWORD PTR i$2[rsp]
	inc	rax
	mov	QWORD PTR i$2[rsp], rax
$LN13@AuPmmngrIn:
	mov	rax, QWORD PTR memmap_entries$[rsp]
	cmp	QWORD PTR i$2[rsp], rax
	jae	$LN11@AuPmmngrIn

; 128  : 		EFI_MEMORY_DESCRIPTOR *efi_mem = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)info->map + i * info->descriptor_size);

	mov	rax, QWORD PTR info$[rsp]
	mov	rcx, QWORD PTR i$2[rsp]
	imul	rcx, QWORD PTR [rax+28]
	mov	rax, rcx
	mov	rcx, QWORD PTR info$[rsp]
	add	rax, QWORD PTR [rcx+20]
	mov	QWORD PTR efi_mem$1[rsp], rax

; 129  : 		total_ram += efi_mem->num_pages * 4096;

	mov	rax, QWORD PTR efi_mem$1[rsp]
	mov	rax, QWORD PTR [rax+24]
	imul	rax, 4096				; 00001000H
	mov	rcx, QWORD PTR ?total_ram@@3_KA		; total_ram
	add	rcx, rax
	mov	rax, rcx
	mov	QWORD PTR ?total_ram@@3_KA, rax		; total_ram

; 130  : 		if (efi_mem->type == 7) {

	mov	rax, QWORD PTR efi_mem$1[rsp]
	cmp	DWORD PTR [rax], 7
	jne	$LN10@AuPmmngrIn

; 131  : 			if (((efi_mem->num_pages * 4096) > 0x100000) && bitmap_area == 0) {

	mov	rax, QWORD PTR efi_mem$1[rsp]
	mov	rax, QWORD PTR [rax+24]
	imul	rax, 4096				; 00001000H
	cmp	rax, 1048576				; 00100000H
	jbe	SHORT $LN9@AuPmmngrIn
	cmp	QWORD PTR bitmap_area$[rsp], 0
	jne	SHORT $LN9@AuPmmngrIn

; 132  : 				bitmap_area = (void*)efi_mem->phys_start;

	mov	rax, QWORD PTR efi_mem$1[rsp]
	mov	rax, QWORD PTR [rax+8]
	mov	QWORD PTR bitmap_area$[rsp], rax
$LN9@AuPmmngrIn:

; 133  : 			}
; 134  : 			uint64_t size_in_mb_kb = 0;

	mov	QWORD PTR size_in_mb_kb$6[rsp], 0

; 135  : 			char* unit = "B";

	lea	rax, OFFSET FLAT:$SG3241
	mov	QWORD PTR unit$5[rsp], rax

; 136  : 			if ((efi_mem->num_pages * 4096 / 1024 / 1024) == 0) {

	mov	rax, QWORD PTR efi_mem$1[rsp]
	mov	rax, QWORD PTR [rax+24]
	imul	rax, 4096				; 00001000H
	xor	edx, edx
	mov	ecx, 1024				; 00000400H
	div	rcx
	xor	edx, edx
	mov	ecx, 1024				; 00000400H
	div	rcx
	test	rax, rax
	jne	SHORT $LN8@AuPmmngrIn

; 137  : 				size_in_mb_kb = efi_mem->num_pages * 4096 / 1024;

	mov	rax, QWORD PTR efi_mem$1[rsp]
	mov	rax, QWORD PTR [rax+24]
	imul	rax, 4096				; 00001000H
	xor	edx, edx
	mov	ecx, 1024				; 00000400H
	div	rcx
	mov	QWORD PTR size_in_mb_kb$6[rsp], rax

; 138  : 				unit = "KB";

	lea	rax, OFFSET FLAT:$SG3243
	mov	QWORD PTR unit$5[rsp], rax

; 139  : 			}
; 140  : 			else {

	jmp	SHORT $LN7@AuPmmngrIn
$LN8@AuPmmngrIn:

; 141  : 				size_in_mb_kb = (efi_mem->num_pages * 4096 / 1024 / 1024);

	mov	rax, QWORD PTR efi_mem$1[rsp]
	mov	rax, QWORD PTR [rax+24]
	imul	rax, 4096				; 00001000H
	xor	edx, edx
	mov	ecx, 1024				; 00000400H
	div	rcx
	xor	edx, edx
	mov	ecx, 1024				; 00000400H
	div	rcx
	mov	QWORD PTR size_in_mb_kb$6[rsp], rax

; 142  : 				unit = "MB";

	lea	rax, OFFSET FLAT:$SG3245
	mov	QWORD PTR unit$5[rsp], rax
$LN7@AuPmmngrIn:

; 143  : 			}
; 144  : 			info->printf_gui("[aurora]: usable memory -> %x length -> %d %s\n", efi_mem->phys_start, size_in_mb_kb, unit);

	mov	r9, QWORD PTR unit$5[rsp]
	mov	r8, QWORD PTR size_in_mb_kb$6[rsp]
	mov	rax, QWORD PTR efi_mem$1[rsp]
	mov	rdx, QWORD PTR [rax+8]
	lea	rcx, OFFSET FLAT:$SG3246
	mov	rax, QWORD PTR info$[rsp]
	call	QWORD PTR [rax+106]
$LN10@AuPmmngrIn:

; 145  : 		}
; 146  : 	}

	jmp	$LN12@AuPmmngrIn
$LN11@AuPmmngrIn:

; 147  : 
; 148  : 	info->printf_gui("[aurora]: total memory -> %d GB \n", (total_ram/ 1024 / 1024 / 1024));

	xor	edx, edx
	mov	rax, QWORD PTR ?total_ram@@3_KA		; total_ram
	mov	ecx, 1024				; 00000400H
	div	rcx
	xor	edx, edx
	mov	ecx, 1024				; 00000400H
	div	rcx
	xor	edx, edx
	mov	ecx, 1024				; 00000400H
	div	rcx
	mov	rdx, rax
	lea	rcx, OFFSET FLAT:$SG3247
	mov	rax, QWORD PTR info$[rsp]
	call	QWORD PTR [rax+106]

; 149  : 	uint64_t bitmap_size = total_ram / 4096 / 8 + 1;

	xor	edx, edx
	mov	rax, QWORD PTR ?total_ram@@3_KA		; total_ram
	mov	ecx, 4096				; 00001000H
	div	rcx
	xor	edx, edx
	mov	ecx, 8
	div	rcx
	inc	rax
	mov	QWORD PTR bitmap_size$[rsp], rax

; 150  : 
; 151  : 	AuPmmngrInitBitmap(bitmap_size, bitmap_area);

	mov	rdx, QWORD PTR bitmap_area$[rsp]
	mov	rcx, QWORD PTR bitmap_size$[rsp]
	call	?AuPmmngrInitBitmap@@YAX_KPEAX@Z	; AuPmmngrInitBitmap

; 152  : 
; 153  : 	info->printf_gui("[aurora]: bitmap initialized %d bytes\n", bitmap_size);

	mov	rdx, QWORD PTR bitmap_size$[rsp]
	lea	rcx, OFFSET FLAT:$SG3249
	mov	rax, QWORD PTR info$[rsp]
	call	QWORD PTR [rax+106]

; 154  : 	AuPmmngrLockPages((void*)bitmap_area, bitmap_size);

	mov	rdx, QWORD PTR bitmap_size$[rsp]
	mov	rcx, QWORD PTR bitmap_area$[rsp]
	call	?AuPmmngrLockPages@@YAXPEAX_K@Z		; AuPmmngrLockPages

; 155  : 
; 156  : 	/* No lock all pages, that are not for use */
; 157  : 	for (size_t i = 0; i < memmap_entries; i++) {

	mov	QWORD PTR i$3[rsp], 0
	jmp	SHORT $LN6@AuPmmngrIn
$LN5@AuPmmngrIn:
	mov	rax, QWORD PTR i$3[rsp]
	inc	rax
	mov	QWORD PTR i$3[rsp], rax
$LN6@AuPmmngrIn:
	mov	rax, QWORD PTR memmap_entries$[rsp]
	cmp	QWORD PTR i$3[rsp], rax
	jae	SHORT $LN4@AuPmmngrIn

; 158  : 		EFI_MEMORY_DESCRIPTOR *efi_mem = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)info->map + i * info->descriptor_size);

	mov	rax, QWORD PTR info$[rsp]
	mov	rcx, QWORD PTR i$3[rsp]
	imul	rcx, QWORD PTR [rax+28]
	mov	rax, rcx
	mov	rcx, QWORD PTR info$[rsp]
	add	rax, QWORD PTR [rcx+20]
	mov	QWORD PTR efi_mem$4[rsp], rax

; 159  : 		total_ram += efi_mem->num_pages;

	mov	rax, QWORD PTR efi_mem$4[rsp]
	mov	rax, QWORD PTR [rax+24]
	mov	rcx, QWORD PTR ?total_ram@@3_KA		; total_ram
	add	rcx, rax
	mov	rax, rcx
	mov	QWORD PTR ?total_ram@@3_KA, rax		; total_ram

; 160  : 		if (efi_mem->type != 7) {

	mov	rax, QWORD PTR efi_mem$4[rsp]
	cmp	DWORD PTR [rax], 7
	je	SHORT $LN3@AuPmmngrIn

; 161  : 			AuPmmngrLockPages((void*)efi_mem->phys_start, efi_mem->num_pages);

	mov	rax, QWORD PTR efi_mem$4[rsp]
	mov	rdx, QWORD PTR [rax+24]
	mov	rax, QWORD PTR efi_mem$4[rsp]
	mov	rcx, QWORD PTR [rax+8]
	call	?AuPmmngrLockPages@@YAXPEAX_K@Z		; AuPmmngrLockPages
$LN3@AuPmmngrIn:

; 162  : 		}
; 163  : 	}

	jmp	SHORT $LN5@AuPmmngrIn
$LN4@AuPmmngrIn:

; 164  : 
; 165  : 	AuPmmngrLockPage((void*)0x0);

	xor	ecx, ecx
	call	?AuPmmngrLockPage@@YAXPEAX@Z		; AuPmmngrLockPage

; 166  : 
; 167  : 	/* also lock the early used physical blocks for 
; 168  : 	 * kernel and kernel stack */
; 169  : 	uint32_t allocated_count = info->reserved_mem_count;

	mov	rax, QWORD PTR info$[rsp]
	mov	eax, DWORD PTR [rax+12]
	mov	DWORD PTR allocated_count$[rsp], eax

; 170  : 	uint64_t* allocated_stack = (uint64_t*)info->allocated_stack;

	mov	rax, QWORD PTR info$[rsp]
	mov	rax, QWORD PTR [rax+4]
	mov	QWORD PTR allocated_stack$[rsp], rax
$LN2@AuPmmngrIn:

; 171  : 	while (allocated_count) {

	cmp	DWORD PTR allocated_count$[rsp], 0
	je	SHORT $LN1@AuPmmngrIn

; 172  : 		uint64_t address = *allocated_stack--;

	mov	rax, QWORD PTR allocated_stack$[rsp]
	mov	rax, QWORD PTR [rax]
	mov	QWORD PTR address$7[rsp], rax
	mov	rax, QWORD PTR allocated_stack$[rsp]
	sub	rax, 8
	mov	QWORD PTR allocated_stack$[rsp], rax

; 173  : 		AuPmmngrLockPage((void*)address);

	mov	rcx, QWORD PTR address$7[rsp]
	call	?AuPmmngrLockPage@@YAXPEAX@Z		; AuPmmngrLockPage

; 174  : 		allocated_count--;

	mov	eax, DWORD PTR allocated_count$[rsp]
	dec	eax
	mov	DWORD PTR allocated_count$[rsp], eax

; 175  : 	}

	jmp	SHORT $LN2@AuPmmngrIn
$LN1@AuPmmngrIn:

; 176  : 
; 177  : 	/* Will be used for SMP AP initialisation code */
; 178  : 	uint64_t *address = (uint64_t*)0xA000;

	mov	QWORD PTR address$[rsp], 40960		; 0000a000H

; 179  : 	AuPmmngrLockPage((void*)0xA000);

	mov	ecx, 40960				; 0000a000H
	call	?AuPmmngrLockPage@@YAXPEAX@Z		; AuPmmngrLockPage

; 180  : 	memset(address, 0, 4096);

	mov	r8d, 4096				; 00001000H
	xor	edx, edx
	mov	rcx, QWORD PTR address$[rsp]
	call	memset

; 181  : 	memcpy(address, info->apcode, 4096);

	mov	r8d, 4096				; 00001000H
	mov	rax, QWORD PTR info$[rsp]
	mov	rdx, QWORD PTR [rax+162]
	mov	rcx, QWORD PTR address$[rsp]
	call	memcpy

; 182  : 
; 183  : 	higher_half = false;

	mov	BYTE PTR ?higher_half@@3_NA, 0		; higher_half

; 184  : 	info->printf_gui("[aurora]:pmmngr initialized\n");

	lea	rcx, OFFSET FLAT:$SG3272
	mov	rax, QWORD PTR info$[rsp]
	call	QWORD PTR [rax+106]

; 185  : }

	add	rsp, 152				; 00000098H
	ret	0
?AuPmmngrInit@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ENDP	; AuPmmngrInit
_TEXT	ENDS
END
