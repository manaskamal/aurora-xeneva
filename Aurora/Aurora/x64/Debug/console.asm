; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

_BSS	SEGMENT
scanline DW	01H DUP (?)
	ALIGN	4

screen_width DW	01H DUP (?)
	ALIGN	4

screen_height DW 01H DUP (?)
	ALIGN	8

fb	DQ	01H DUP (?)
console_x DD	01H DUP (?)
console_y DD	01H DUP (?)
psf_data DQ	01H DUP (?)
_console_initialized_ DB 01H DUP (?)
_BSS	ENDS
CONST	SEGMENT
$SG3378	DB	'/font.psf', 00H
CONST	ENDS
PUBLIC	?AuConsoleInitialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; AuConsoleInitialize
PUBLIC	?puts@@YAXPEAD@Z				; puts
PUBLIC	?putc@@YAXD@Z					; putc
PUBLIC	?AuIsConsoleInitialized@@YA_NXZ			; AuIsConsoleInitialized
PUBLIC	?fb_write@@YAXPEAU_vfs_node_@@PEAEI@Z		; fb_write
PUBLIC	?fb_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z	; fb_io_query
PUBLIC	?console_pixel@@YAXIII@Z			; console_pixel
EXTRN	AuPmmngrAllocBlocks:PROC
EXTRN	p2v:PROC
EXTRN	v2p:PROC
EXTRN	memset:PROC
EXTRN	memcpy:PROC
EXTRN	?fat32_open@@YA?AU_vfs_node_@@PEAU1@PEAD@Z:PROC	; fat32_open
EXTRN	?fat32_read_file@@YAXPEAU_vfs_node_@@PEA_KI@Z:PROC ; fat32_read_file
EXTRN	AuGetFramebuffer:PROC
pdata	SEGMENT
$pdata$?AuConsoleInitialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD imagerel $LN3
	DD	imagerel $LN3+270
	DD	imagerel $unwind$?AuConsoleInitialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z
$pdata$?puts@@YAXPEAD@Z DD imagerel $LN25
	DD	imagerel $LN25+739
	DD	imagerel $unwind$?puts@@YAXPEAD@Z
$pdata$?putc@@YAXD@Z DD imagerel $LN14
	DD	imagerel $LN14+516
	DD	imagerel $unwind$?putc@@YAXD@Z
$pdata$?fb_write@@YAXPEAU_vfs_node_@@PEAEI@Z DD imagerel $LN3
	DD	imagerel $LN3+46
	DD	imagerel $unwind$?fb_write@@YAXPEAU_vfs_node_@@PEAEI@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?AuConsoleInitialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD 040e01H
	DD	02f010eH
	DD	060067007H
$unwind$?puts@@YAXPEAD@Z DD 010901H
	DD	08209H
$unwind$?putc@@YAXD@Z DD 010801H
	DD	08208H
$unwind$?fb_write@@YAXPEAU_vfs_node_@@PEAEI@Z DD 011301H
	DD	04213H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\console.cpp
_TEXT	SEGMENT
col$ = 8
x$ = 16
y$ = 24
?console_pixel@@YAXIII@Z PROC				; console_pixel

; 87   : {

	mov	DWORD PTR [rsp+24], r8d
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx

; 88   : 	fb[x + y * screen_width] = col;

	movzx	eax, WORD PTR screen_width
	mov	ecx, DWORD PTR y$[rsp]
	imul	ecx, eax
	mov	eax, ecx
	mov	ecx, DWORD PTR x$[rsp]
	add	ecx, eax
	mov	eax, ecx
	mov	eax, eax
	mov	rcx, QWORD PTR fb
	mov	edx, DWORD PTR col$[rsp]
	mov	DWORD PTR [rcx+rax*4], edx

; 89   : }

	ret	0
?console_pixel@@YAXIII@Z ENDP				; console_pixel
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\console.cpp
_TEXT	SEGMENT
node$ = 8
code$ = 16
arg$ = 24
?fb_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z PROC		; fb_io_query

; 35   : int fb_io_query (vfs_node_t* node, int code, void* arg) {

	mov	QWORD PTR [rsp+24], r8
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx

; 36   : 
; 37   : 	return 1;

	mov	eax, 1

; 38   : }

	ret	0
?fb_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z ENDP		; fb_io_query
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\console.cpp
_TEXT	SEGMENT
file$ = 48
buffer$ = 56
length$ = 64
?fb_write@@YAXPEAU_vfs_node_@@PEAEI@Z PROC		; fb_write

; 31   : void fb_write (_vfs_node_ *file, uint8_t* buffer, uint32_t length){

$LN3:
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 32   : 	memcpy (fb,buffer,length);

	mov	r8d, DWORD PTR length$[rsp]
	mov	rdx, QWORD PTR buffer$[rsp]
	mov	rcx, QWORD PTR fb
	call	memcpy

; 33   : }

	add	rsp, 40					; 00000028H
	ret	0
?fb_write@@YAXPEAU_vfs_node_@@PEAEI@Z ENDP		; fb_write
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\console.cpp
_TEXT	SEGMENT
?AuIsConsoleInitialized@@YA_NXZ PROC			; AuIsConsoleInitialized

; 165  : 	return _console_initialized_;

	movzx	eax, BYTE PTR _console_initialized_

; 166  : }

	ret	0
?AuIsConsoleInitialized@@YA_NXZ ENDP			; AuIsConsoleInitialized
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\console.cpp
_TEXT	SEGMENT
line$ = 0
font$ = 8
x$ = 16
offs$ = 20
mask$ = 24
y$ = 28
tv77 = 32
tv136 = 36
bpl$ = 40
tv184 = 44
kx$ = 48
glyph$ = 56
c$ = 80
?putc@@YAXD@Z PROC					; putc

; 62   : void putc (char c) {

$LN14:
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 72					; 00000048H

; 63   : 	if (psf_data == NULL)

	cmp	QWORD PTR psf_data, 0
	jne	SHORT $LN7@putc

; 64   : 		return;

	jmp	$LN8@putc
$LN7@putc:

; 65   : 
; 66   : 	psf2_t *font = (psf2_t*)psf_data;

	mov	rax, QWORD PTR psf_data
	mov	QWORD PTR font$[rsp], rax

; 67   :     int x,y,kx=0,line,mask,offs;

	mov	DWORD PTR kx$[rsp], 0

; 68   :     int bpl=(font->width+7)/8;

	mov	rax, QWORD PTR font$[rsp]
	mov	eax, DWORD PTR [rax+28]
	add	eax, 7
	xor	edx, edx
	mov	ecx, 8
	div	ecx
	mov	DWORD PTR bpl$[rsp], eax

; 69   :   
; 70   : 	
; 71   : 	unsigned char *glyph = (unsigned char*)psf_data + font->headersize + 
; 72   : 				(c>0&&c<font->numglyph?c:0)*font->bytesperglyph;

	movsx	eax, BYTE PTR c$[rsp]
	test	eax, eax
	jle	SHORT $LN10@putc
	movsx	eax, BYTE PTR c$[rsp]
	mov	rcx, QWORD PTR font$[rsp]
	cmp	eax, DWORD PTR [rcx+16]
	jae	SHORT $LN10@putc
	movsx	eax, BYTE PTR c$[rsp]
	mov	DWORD PTR tv77[rsp], eax
	jmp	SHORT $LN11@putc
$LN10@putc:
	mov	DWORD PTR tv77[rsp], 0
$LN11@putc:
	mov	rax, QWORD PTR font$[rsp]
	mov	eax, DWORD PTR [rax+8]
	mov	rcx, QWORD PTR psf_data
	add	rcx, rax
	mov	rax, rcx
	mov	rcx, QWORD PTR font$[rsp]
	mov	edx, DWORD PTR tv77[rsp]
	imul	edx, DWORD PTR [rcx+20]
	mov	ecx, edx
	mov	ecx, ecx
	add	rax, rcx
	mov	QWORD PTR glyph$[rsp], rax

; 73   : 	offs = kx * (font->width + 1);// * 4);

	mov	rax, QWORD PTR font$[rsp]
	mov	eax, DWORD PTR [rax+28]
	inc	eax
	mov	ecx, DWORD PTR kx$[rsp]
	imul	ecx, eax
	mov	eax, ecx
	mov	DWORD PTR offs$[rsp], eax

; 74   : 	for(y=0;y<font->height;y++) {

	mov	DWORD PTR y$[rsp], 0
	jmp	SHORT $LN6@putc
$LN5@putc:
	mov	eax, DWORD PTR y$[rsp]
	inc	eax
	mov	DWORD PTR y$[rsp], eax
$LN6@putc:
	mov	rax, QWORD PTR font$[rsp]
	mov	eax, DWORD PTR [rax+24]
	cmp	DWORD PTR y$[rsp], eax
	jae	$LN4@putc

; 75   : 		line=offs; mask=1<<(font->width-1);

	mov	eax, DWORD PTR offs$[rsp]
	mov	DWORD PTR line$[rsp], eax
	mov	rax, QWORD PTR font$[rsp]
	mov	eax, DWORD PTR [rax+28]
	dec	eax
	mov	ecx, 1
	mov	DWORD PTR tv184[rsp], ecx
	movzx	ecx, al
	mov	eax, DWORD PTR tv184[rsp]
	shl	eax, cl
	mov	DWORD PTR mask$[rsp], eax

; 76   : 		for(x=0;x<font->width;x++) {

	mov	DWORD PTR x$[rsp], 0
	jmp	SHORT $LN3@putc
$LN2@putc:
	mov	eax, DWORD PTR x$[rsp]
	inc	eax
	mov	DWORD PTR x$[rsp], eax
$LN3@putc:
	mov	rax, QWORD PTR font$[rsp]
	mov	eax, DWORD PTR [rax+28]
	cmp	DWORD PTR x$[rsp], eax
	jae	SHORT $LN1@putc

; 77   : 			fb[line + console_x + console_y * screen_width ]=((int)*glyph) & (mask)?0xFFFFFF:0;

	mov	rax, QWORD PTR glyph$[rsp]
	movzx	eax, BYTE PTR [rax]
	and	eax, DWORD PTR mask$[rsp]
	test	eax, eax
	je	SHORT $LN12@putc
	mov	DWORD PTR tv136[rsp], 16777215		; 00ffffffH
	jmp	SHORT $LN13@putc
$LN12@putc:
	mov	DWORD PTR tv136[rsp], 0
$LN13@putc:
	mov	eax, DWORD PTR console_x
	mov	ecx, DWORD PTR line$[rsp]
	add	ecx, eax
	mov	eax, ecx
	movzx	ecx, WORD PTR screen_width
	mov	edx, DWORD PTR console_y
	imul	edx, ecx
	mov	ecx, edx
	add	eax, ecx
	cdqe
	mov	rcx, QWORD PTR fb
	mov	edx, DWORD PTR tv136[rsp]
	mov	DWORD PTR [rcx+rax*4], edx

; 78   : 			mask>>=1; line+=1;

	mov	eax, DWORD PTR mask$[rsp]
	sar	eax, 1
	mov	DWORD PTR mask$[rsp], eax
	mov	eax, DWORD PTR line$[rsp]
	inc	eax
	mov	DWORD PTR line$[rsp], eax

; 79   : 		}

	jmp	SHORT $LN2@putc
$LN1@putc:

; 80   : 		fb[line + console_x + console_y * screen_width]=0; glyph+=bpl; offs+=scanline;

	mov	eax, DWORD PTR console_x
	mov	ecx, DWORD PTR line$[rsp]
	add	ecx, eax
	mov	eax, ecx
	movzx	ecx, WORD PTR screen_width
	mov	edx, DWORD PTR console_y
	imul	edx, ecx
	mov	ecx, edx
	add	eax, ecx
	cdqe
	mov	rcx, QWORD PTR fb
	mov	DWORD PTR [rcx+rax*4], 0
	movsxd	rax, DWORD PTR bpl$[rsp]
	mov	rcx, QWORD PTR glyph$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	QWORD PTR glyph$[rsp], rax
	movzx	eax, WORD PTR scanline
	mov	ecx, DWORD PTR offs$[rsp]
	add	ecx, eax
	mov	eax, ecx
	mov	DWORD PTR offs$[rsp], eax

; 81   : 	}

	jmp	$LN5@putc
$LN4@putc:

; 82   : 	console_x += font->width + 1;

	mov	rax, QWORD PTR font$[rsp]
	mov	eax, DWORD PTR [rax+28]
	mov	ecx, DWORD PTR console_x
	lea	eax, DWORD PTR [rcx+rax+1]
	mov	DWORD PTR console_x, eax
$LN8@putc:

; 83   : }

	add	rsp, 72					; 00000048H
	ret	0
?putc@@YAXD@Z ENDP					; putc
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\console.cpp
_TEXT	SEGMENT
i$1 = 0
line$ = 4
font$ = 8
offs$ = 16
y$ = 20
x$ = 24
mask$ = 28
tv162 = 32
tv136 = 36
bpl$ = 40
tv224 = 44
glyph$2 = 48
s$ = 80
?puts@@YAXPEAD@Z PROC					; puts

; 93   : void puts(char *s){

$LN25:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 94   : 	if (psf_data == NULL)

	cmp	QWORD PTR psf_data, 0
	jne	SHORT $LN18@puts

; 95   : 		return;

	jmp	$LN19@puts
$LN18@puts:

; 96   : 
; 97   : 	psf2_t *font = (psf2_t*)psf_data;

	mov	rax, QWORD PTR psf_data
	mov	QWORD PTR font$[rsp], rax

; 98   :     int x,y,line,mask,offs;
; 99   :     int bpl=(font->width+7)/8;

	mov	rax, QWORD PTR font$[rsp]
	mov	eax, DWORD PTR [rax+28]
	add	eax, 7
	xor	edx, edx
	mov	ecx, 8
	div	ecx
	mov	DWORD PTR bpl$[rsp], eax
$LN17@puts:

; 100  :     while(*s) {

	mov	rax, QWORD PTR s$[rsp]
	movsx	eax, BYTE PTR [rax]
	test	eax, eax
	je	$LN16@puts

; 101  : 		if (*s == '\n') {

	mov	rax, QWORD PTR s$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 10
	jne	$LN15@puts

; 102  : 
; 103  :             console_y += 16;

	mov	eax, DWORD PTR console_y
	add	eax, 16
	mov	DWORD PTR console_y, eax

; 104  : 			console_x = 0;

	mov	DWORD PTR console_x, 0

; 105  : 			////!Scroll
; 106  : 			if (console_y + 1 > screen_height) {

	mov	eax, DWORD PTR console_y
	inc	eax
	movzx	ecx, WORD PTR screen_height
	cmp	eax, ecx
	jle	SHORT $LN14@puts

; 107  : 				for (int i = 16; i < screen_height * screen_width; i++) {

	mov	DWORD PTR i$1[rsp], 16
	jmp	SHORT $LN13@puts
$LN12@puts:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN13@puts:
	movzx	eax, WORD PTR screen_height
	movzx	ecx, WORD PTR screen_width
	imul	eax, ecx
	cmp	DWORD PTR i$1[rsp], eax
	jge	SHORT $LN11@puts

; 108  : 					fb[i] = fb[i + screen_width * 16];

	movzx	eax, WORD PTR screen_width
	imul	eax, 16
	mov	ecx, DWORD PTR i$1[rsp]
	add	ecx, eax
	mov	eax, ecx
	cdqe
	movsxd	rcx, DWORD PTR i$1[rsp]
	mov	rdx, QWORD PTR fb
	mov	r8, QWORD PTR fb
	mov	eax, DWORD PTR [r8+rax*4]
	mov	DWORD PTR [rdx+rcx*4], eax

; 109  : 				}

	jmp	SHORT $LN12@puts
$LN11@puts:

; 110  : 				console_y--;

	mov	eax, DWORD PTR console_y
	dec	eax
	mov	DWORD PTR console_y, eax
$LN14@puts:
	jmp	$LN10@puts
$LN15@puts:

; 111  : 			}
; 112  : 
; 113  : 		} else if (*s == '\b') {

	mov	rax, QWORD PTR s$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 8
	jne	SHORT $LN9@puts

; 114  : 			if (console_x > 0) {

	cmp	DWORD PTR console_x, 0
	jle	SHORT $LN8@puts

; 115  : 				console_x--;

	mov	eax, DWORD PTR console_x
	dec	eax
	mov	DWORD PTR console_x, eax
$LN8@puts:

; 116  : 			}
; 117  : 		}else {

	jmp	$LN7@puts
$LN9@puts:

; 118  : 			unsigned char *glyph = (unsigned char*)psf_data + font->headersize + 
; 119  : 				(*s>0&&*s<font->numglyph?*s:0)*font->bytesperglyph;

	mov	rax, QWORD PTR s$[rsp]
	movsx	eax, BYTE PTR [rax]
	test	eax, eax
	jle	SHORT $LN21@puts
	mov	rax, QWORD PTR s$[rsp]
	movsx	eax, BYTE PTR [rax]
	mov	rcx, QWORD PTR font$[rsp]
	cmp	eax, DWORD PTR [rcx+16]
	jae	SHORT $LN21@puts
	mov	rax, QWORD PTR s$[rsp]
	movsx	eax, BYTE PTR [rax]
	mov	DWORD PTR tv136[rsp], eax
	jmp	SHORT $LN22@puts
$LN21@puts:
	mov	DWORD PTR tv136[rsp], 0
$LN22@puts:
	mov	rax, QWORD PTR font$[rsp]
	mov	eax, DWORD PTR [rax+8]
	mov	rcx, QWORD PTR psf_data
	add	rcx, rax
	mov	rax, rcx
	mov	rcx, QWORD PTR font$[rsp]
	mov	edx, DWORD PTR tv136[rsp]
	imul	edx, DWORD PTR [rcx+20]
	mov	ecx, edx
	mov	ecx, ecx
	add	rax, rcx
	mov	QWORD PTR glyph$2[rsp], rax

; 120  : 			offs = console_x * (font->width + 1);// * 4);

	mov	rax, QWORD PTR font$[rsp]
	mov	eax, DWORD PTR [rax+28]
	inc	eax
	mov	ecx, DWORD PTR console_x
	imul	ecx, eax
	mov	eax, ecx
	mov	DWORD PTR offs$[rsp], eax

; 121  : 			for(y=0;y<font->height;y++) {

	mov	DWORD PTR y$[rsp], 0
	jmp	SHORT $LN6@puts
$LN5@puts:
	mov	eax, DWORD PTR y$[rsp]
	inc	eax
	mov	DWORD PTR y$[rsp], eax
$LN6@puts:
	mov	rax, QWORD PTR font$[rsp]
	mov	eax, DWORD PTR [rax+24]
	cmp	DWORD PTR y$[rsp], eax
	jae	$LN4@puts

; 122  : 				line=offs; mask=1<<(font->width-1);

	mov	eax, DWORD PTR offs$[rsp]
	mov	DWORD PTR line$[rsp], eax
	mov	rax, QWORD PTR font$[rsp]
	mov	eax, DWORD PTR [rax+28]
	dec	eax
	mov	ecx, 1
	mov	DWORD PTR tv224[rsp], ecx
	movzx	ecx, al
	mov	eax, DWORD PTR tv224[rsp]
	shl	eax, cl
	mov	DWORD PTR mask$[rsp], eax

; 123  : 				for(x=0;x<font->width;x++) {

	mov	DWORD PTR x$[rsp], 0
	jmp	SHORT $LN3@puts
$LN2@puts:
	mov	eax, DWORD PTR x$[rsp]
	inc	eax
	mov	DWORD PTR x$[rsp], eax
$LN3@puts:
	mov	rax, QWORD PTR font$[rsp]
	mov	eax, DWORD PTR [rax+28]
	cmp	DWORD PTR x$[rsp], eax
	jae	SHORT $LN1@puts

; 124  : 					fb[line  + console_y * screen_width ]=((int)*glyph) & (mask)?0xFFFFFF:0;

	mov	rax, QWORD PTR glyph$2[rsp]
	movzx	eax, BYTE PTR [rax]
	and	eax, DWORD PTR mask$[rsp]
	test	eax, eax
	je	SHORT $LN23@puts
	mov	DWORD PTR tv162[rsp], 16777215		; 00ffffffH
	jmp	SHORT $LN24@puts
$LN23@puts:
	mov	DWORD PTR tv162[rsp], 0
$LN24@puts:
	movzx	eax, WORD PTR screen_width
	mov	ecx, DWORD PTR console_y
	imul	ecx, eax
	mov	eax, ecx
	mov	ecx, DWORD PTR line$[rsp]
	add	ecx, eax
	mov	eax, ecx
	cdqe
	mov	rcx, QWORD PTR fb
	mov	edx, DWORD PTR tv162[rsp]
	mov	DWORD PTR [rcx+rax*4], edx

; 125  : 					mask>>=1; line+=1;

	mov	eax, DWORD PTR mask$[rsp]
	sar	eax, 1
	mov	DWORD PTR mask$[rsp], eax
	mov	eax, DWORD PTR line$[rsp]
	inc	eax
	mov	DWORD PTR line$[rsp], eax

; 126  : 				}

	jmp	SHORT $LN2@puts
$LN1@puts:

; 127  : 				fb[line  + console_y * screen_width]=0; glyph+=bpl; offs+=scanline;

	movzx	eax, WORD PTR screen_width
	mov	ecx, DWORD PTR console_y
	imul	ecx, eax
	mov	eax, ecx
	mov	ecx, DWORD PTR line$[rsp]
	add	ecx, eax
	mov	eax, ecx
	cdqe
	mov	rcx, QWORD PTR fb
	mov	DWORD PTR [rcx+rax*4], 0
	movsxd	rax, DWORD PTR bpl$[rsp]
	mov	rcx, QWORD PTR glyph$2[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	QWORD PTR glyph$2[rsp], rax
	movzx	eax, WORD PTR scanline
	mov	ecx, DWORD PTR offs$[rsp]
	add	ecx, eax
	mov	eax, ecx
	mov	DWORD PTR offs$[rsp], eax

; 128  : 			}

	jmp	$LN5@puts
$LN4@puts:

; 129  : 			console_x++;

	mov	eax, DWORD PTR console_x
	inc	eax
	mov	DWORD PTR console_x, eax
$LN7@puts:
$LN10@puts:

; 130  : 		}
; 131  : 		s++; 

	mov	rax, QWORD PTR s$[rsp]
	inc	rax
	mov	QWORD PTR s$[rsp], rax

; 132  :     }

	jmp	$LN17@puts
$LN16@puts:
$LN19@puts:

; 133  : 
; 134  : 	
; 135  : }

	add	rsp, 72					; 00000048H
	ret	0
?puts@@YAXPEAD@Z ENDP					; puts
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\console.cpp
_TEXT	SEGMENT
buffer$ = 32
file$ = 48
$T1 = 160
$T2 = 264
info$ = 400
?AuConsoleInitialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z PROC ; AuConsoleInitialize

; 44   : void AuConsoleInitialize (PKERNEL_BOOT_INFO info) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	push	rsi
	push	rdi
	sub	rsp, 376				; 00000178H

; 45   : 	console_x = 0;

	mov	DWORD PTR console_x, 0

; 46   : 	console_y = 0;

	mov	DWORD PTR console_y, 0

; 47   : 	scanline = info->pixels_per_line;

	mov	rax, QWORD PTR info$[rsp]
	movzx	eax, WORD PTR [rax+64]
	mov	WORD PTR scanline, ax

; 48   : 	screen_width = info->X_Resolution;

	mov	rax, QWORD PTR info$[rsp]
	movzx	eax, WORD PTR [rax+60]
	mov	WORD PTR screen_width, ax

; 49   : 	screen_height = info->Y_Resolution;

	mov	rax, QWORD PTR info$[rsp]
	movzx	eax, WORD PTR [rax+62]
	mov	WORD PTR screen_height, ax

; 50   : 	fb =  AuGetFramebuffer();//info->graphics_framebuffer;

	call	AuGetFramebuffer
	mov	QWORD PTR fb, rax

; 51   : 
; 52   : 
; 53   : 	uint64_t* buffer = (uint64_t*)p2v((size_t)AuPmmngrAllocBlocks(2));

	mov	ecx, 2
	call	AuPmmngrAllocBlocks
	mov	rcx, rax
	call	p2v
	mov	QWORD PTR buffer$[rsp], rax

; 54   : 	memset(buffer, 0, 8192);

	mov	r8d, 8192				; 00002000H
	xor	edx, edx
	mov	rcx, QWORD PTR buffer$[rsp]
	call	memset

; 55   : 	vfs_node_t file = fat32_open(NULL, "/font.psf");

	lea	r8, OFFSET FLAT:$SG3378
	xor	edx, edx
	lea	rcx, QWORD PTR $T2[rsp]
	call	?fat32_open@@YA?AU_vfs_node_@@PEAU1@PEAD@Z ; fat32_open
	lea	rcx, QWORD PTR $T1[rsp]
	mov	rdi, rcx
	mov	rsi, rax
	mov	ecx, 104				; 00000068H
	rep movsb
	lea	rax, QWORD PTR file$[rsp]
	lea	rcx, QWORD PTR $T1[rsp]
	mov	rdi, rax
	mov	rsi, rcx
	mov	ecx, 104				; 00000068H
	rep movsb

; 56   : 	fat32_read_file (&file,(uint64_t*)v2p((size_t)buffer),file.size);

	mov	rcx, QWORD PTR buffer$[rsp]
	call	v2p
	mov	r8d, DWORD PTR file$[rsp+32]
	mov	rdx, rax
	lea	rcx, QWORD PTR file$[rsp]
	call	?fat32_read_file@@YAXPEAU_vfs_node_@@PEA_KI@Z ; fat32_read_file

; 57   : 	psf_data = buffer;

	mov	rax, QWORD PTR buffer$[rsp]
	mov	QWORD PTR psf_data, rax

; 58   : 	_console_initialized_ = true;

	mov	BYTE PTR _console_initialized_, 1

; 59   : }

	add	rsp, 376				; 00000178H
	pop	rdi
	pop	rsi
	ret	0
?AuConsoleInitialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ENDP ; AuConsoleInitialize
_TEXT	ENDS
END
