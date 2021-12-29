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
_BSS	ENDS
CONST	SEGMENT
$SG3031	DB	'/font.psf', 00H
	ORG $+6
$SG3034	DB	'/font.psf', 00H
CONST	ENDS
PUBLIC	?console_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; console_initialize
PUBLIC	?puts@@YAXPEAD@Z				; puts
PUBLIC	?putc@@YAXD@Z					; putc
PUBLIC	?fb_write@@YAXPEAU_vfs_node_@@PEAEI@Z		; fb_write
PUBLIC	?fb_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z	; fb_io_query
PUBLIC	?console_pixel@@YAXIII@Z			; console_pixel
EXTRN	memcpy:PROC
EXTRN	?malloc@@YAPEAXI@Z:PROC				; malloc
EXTRN	?vfs_finddir@@YAPEAU_vfs_node_@@PEAD@Z:PROC	; vfs_finddir
EXTRN	?openfs@@YA?AU_vfs_node_@@PEAU1@PEAD@Z:PROC	; openfs
EXTRN	?readfs@@YAXPEAU_vfs_node_@@0PEAEI@Z:PROC	; readfs
pdata	SEGMENT
$pdata$?console_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD imagerel $LN3
	DD	imagerel $LN3+260
	DD	imagerel $unwind$?console_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z
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
$unwind$?console_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD 040e01H
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

; 86   : {

	mov	DWORD PTR [rsp+24], r8d
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx

; 87   : 	fb[x + y * screen_width] = col;

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

; 88   : }

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

; 32   : int fb_io_query (vfs_node_t* node, int code, void* arg) {

	mov	QWORD PTR [rsp+24], r8
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx

; 33   : 
; 34   : 	return 1;

	mov	eax, 1

; 35   : }

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

; 28   : void fb_write (_vfs_node_ *file, uint8_t* buffer, uint32_t length){

$LN3:
	mov	DWORD PTR [rsp+24], r8d
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 29   : 	memcpy (fb,buffer,length);

	mov	r8d, DWORD PTR length$[rsp]
	mov	rdx, QWORD PTR buffer$[rsp]
	mov	rcx, QWORD PTR fb
	call	memcpy

; 30   : }

	add	rsp, 40					; 00000028H
	ret	0
?fb_write@@YAXPEAU_vfs_node_@@PEAEI@Z ENDP		; fb_write
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

; 61   : void putc (char c) {

$LN14:
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 72					; 00000048H

; 62   : 	if (psf_data == NULL)

	cmp	QWORD PTR psf_data, 0
	jne	SHORT $LN7@putc

; 63   : 		return;

	jmp	$LN8@putc
$LN7@putc:

; 64   : 
; 65   : 	psf2_t *font = (psf2_t*)psf_data;

	mov	rax, QWORD PTR psf_data
	mov	QWORD PTR font$[rsp], rax

; 66   :     int x,y,kx=0,line,mask,offs;

	mov	DWORD PTR kx$[rsp], 0

; 67   :     int bpl=(font->width+7)/8;

	mov	rax, QWORD PTR font$[rsp]
	mov	eax, DWORD PTR [rax+28]
	add	eax, 7
	xor	edx, edx
	mov	ecx, 8
	div	ecx
	mov	DWORD PTR bpl$[rsp], eax

; 68   :   
; 69   : 	
; 70   : 	unsigned char *glyph = (unsigned char*)psf_data + font->headersize + 
; 71   : 				(c>0&&c<font->numglyph?c:0)*font->bytesperglyph;

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

; 72   : 	offs = kx * (font->width + 1);// * 4);

	mov	rax, QWORD PTR font$[rsp]
	mov	eax, DWORD PTR [rax+28]
	inc	eax
	mov	ecx, DWORD PTR kx$[rsp]
	imul	ecx, eax
	mov	eax, ecx
	mov	DWORD PTR offs$[rsp], eax

; 73   : 	for(y=0;y<font->height;y++) {

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

; 74   : 		line=offs; mask=1<<(font->width-1);

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

; 75   : 		for(x=0;x<font->width;x++) {

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

; 76   : 			fb[line + console_x + console_y * screen_width ]=((int)*glyph) & (mask)?0xFFFFFF:0;

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

; 77   : 			mask>>=1; line+=1;

	mov	eax, DWORD PTR mask$[rsp]
	sar	eax, 1
	mov	DWORD PTR mask$[rsp], eax
	mov	eax, DWORD PTR line$[rsp]
	inc	eax
	mov	DWORD PTR line$[rsp], eax

; 78   : 		}

	jmp	SHORT $LN2@putc
$LN1@putc:

; 79   : 		fb[line + console_x + console_y * screen_width]=0; glyph+=bpl; offs+=scanline;

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

; 80   : 	}

	jmp	$LN5@putc
$LN4@putc:

; 81   : 	console_x += font->width + 1;

	mov	rax, QWORD PTR font$[rsp]
	mov	eax, DWORD PTR [rax+28]
	mov	ecx, DWORD PTR console_x
	lea	eax, DWORD PTR [rcx+rax+1]
	mov	DWORD PTR console_x, eax
$LN8@putc:

; 82   : }

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

; 92   : void puts(char *s){

$LN25:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 93   : 	if (psf_data == NULL)

	cmp	QWORD PTR psf_data, 0
	jne	SHORT $LN18@puts

; 94   : 		return;

	jmp	$LN19@puts
$LN18@puts:

; 95   : 
; 96   : 	psf2_t *font = (psf2_t*)psf_data;

	mov	rax, QWORD PTR psf_data
	mov	QWORD PTR font$[rsp], rax

; 97   :     int x,y,line,mask,offs;
; 98   :     int bpl=(font->width+7)/8;

	mov	rax, QWORD PTR font$[rsp]
	mov	eax, DWORD PTR [rax+28]
	add	eax, 7
	xor	edx, edx
	mov	ecx, 8
	div	ecx
	mov	DWORD PTR bpl$[rsp], eax
$LN17@puts:

; 99   :     while(*s) {

	mov	rax, QWORD PTR s$[rsp]
	movsx	eax, BYTE PTR [rax]
	test	eax, eax
	je	$LN16@puts

; 100  : 		if (*s == '\n') {

	mov	rax, QWORD PTR s$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 10
	jne	$LN15@puts

; 101  : 
; 102  :             console_y += 16;

	mov	eax, DWORD PTR console_y
	add	eax, 16
	mov	DWORD PTR console_y, eax

; 103  : 			console_x = 0;

	mov	DWORD PTR console_x, 0

; 104  : 			////!Scroll
; 105  : 			if (console_y + 1 > screen_height) {

	mov	eax, DWORD PTR console_y
	inc	eax
	movzx	ecx, WORD PTR screen_height
	cmp	eax, ecx
	jle	SHORT $LN14@puts

; 106  : 				for (int i = 16; i < screen_height * screen_width; i++) {

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

; 107  : 					fb[i] = fb[i + screen_width * 16];

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

; 108  : 				}

	jmp	SHORT $LN12@puts
$LN11@puts:

; 109  : 				console_y--;

	mov	eax, DWORD PTR console_y
	dec	eax
	mov	DWORD PTR console_y, eax
$LN14@puts:
	jmp	$LN10@puts
$LN15@puts:

; 110  : 			}
; 111  : 
; 112  : 		} else if (*s == '\b') {

	mov	rax, QWORD PTR s$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 8
	jne	SHORT $LN9@puts

; 113  : 			if (console_x > 0) {

	cmp	DWORD PTR console_x, 0
	jle	SHORT $LN8@puts

; 114  : 				console_x--;

	mov	eax, DWORD PTR console_x
	dec	eax
	mov	DWORD PTR console_x, eax
$LN8@puts:

; 115  : 			}
; 116  : 		}else {

	jmp	$LN7@puts
$LN9@puts:

; 117  : 			unsigned char *glyph = (unsigned char*)psf_data + font->headersize + 
; 118  : 				(*s>0&&*s<font->numglyph?*s:0)*font->bytesperglyph;

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

; 119  : 			offs = console_x * (font->width + 1);// * 4);

	mov	rax, QWORD PTR font$[rsp]
	mov	eax, DWORD PTR [rax+28]
	inc	eax
	mov	ecx, DWORD PTR console_x
	imul	ecx, eax
	mov	eax, ecx
	mov	DWORD PTR offs$[rsp], eax

; 120  : 			for(y=0;y<font->height;y++) {

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

; 121  : 				line=offs; mask=1<<(font->width-1);

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

; 122  : 				for(x=0;x<font->width;x++) {

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

; 123  : 					fb[line  + console_y * screen_width ]=((int)*glyph) & (mask)?0xFFFFFF:0;

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

; 124  : 					mask>>=1; line+=1;

	mov	eax, DWORD PTR mask$[rsp]
	sar	eax, 1
	mov	DWORD PTR mask$[rsp], eax
	mov	eax, DWORD PTR line$[rsp]
	inc	eax
	mov	DWORD PTR line$[rsp], eax

; 125  : 				}

	jmp	SHORT $LN2@puts
$LN1@puts:

; 126  : 				fb[line  + console_y * screen_width]=0; glyph+=bpl; offs+=scanline;

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

; 127  : 			}

	jmp	$LN5@puts
$LN4@puts:

; 128  : 			console_x++;

	mov	eax, DWORD PTR console_x
	inc	eax
	mov	DWORD PTR console_x, eax
$LN7@puts:
$LN10@puts:

; 129  : 		}
; 130  : 		s++; 

	mov	rax, QWORD PTR s$[rsp]
	inc	rax
	mov	QWORD PTR s$[rsp], rax

; 131  :     }

	jmp	$LN17@puts
$LN16@puts:
$LN19@puts:

; 132  : 
; 133  : 	
; 134  : }

	add	rsp, 72					; 00000048H
	ret	0
?puts@@YAXPEAD@Z ENDP					; puts
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\console.cpp
_TEXT	SEGMENT
node$ = 32
buffer$ = 40
file$ = 48
$T1 = 160
$T2 = 264
info$ = 400
?console_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z PROC	; console_initialize

; 41   : void console_initialize (PKERNEL_BOOT_INFO info) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	push	rsi
	push	rdi
	sub	rsp, 376				; 00000178H

; 42   : 	console_x = 0;

	mov	DWORD PTR console_x, 0

; 43   : 	console_y = 0;

	mov	DWORD PTR console_y, 0

; 44   : 	scanline = info->pixels_per_line;

	mov	rax, QWORD PTR info$[rsp]
	movzx	eax, WORD PTR [rax+72]
	mov	WORD PTR scanline, ax

; 45   : 	screen_width = info->X_Resolution;

	mov	rax, QWORD PTR info$[rsp]
	movzx	eax, WORD PTR [rax+68]
	mov	WORD PTR screen_width, ax

; 46   : 	screen_height = info->Y_Resolution;

	mov	rax, QWORD PTR info$[rsp]
	movzx	eax, WORD PTR [rax+70]
	mov	WORD PTR screen_height, ax

; 47   : 	fb = info->graphics_framebuffer;

	mov	rax, QWORD PTR info$[rsp]
	mov	rax, QWORD PTR [rax+52]
	mov	QWORD PTR fb, rax

; 48   : 
; 49   : 	//psf_data = info->psf_font_data;
; 50   : 
; 51   : 	vfs_node_t *node = vfs_finddir ("/font.psf");

	lea	rcx, OFFSET FLAT:$SG3031
	call	?vfs_finddir@@YAPEAU_vfs_node_@@PEAD@Z	; vfs_finddir
	mov	QWORD PTR node$[rsp], rax

; 52   : 
; 53   : 	vfs_node_t file = openfs (node, "/font.psf");

	lea	r8, OFFSET FLAT:$SG3034
	mov	rdx, QWORD PTR node$[rsp]
	lea	rcx, QWORD PTR $T2[rsp]
	call	?openfs@@YA?AU_vfs_node_@@PEAU1@PEAD@Z	; openfs
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

; 54   : 	uint8_t *buffer = (uint8_t*)malloc(file.size);

	mov	ecx, DWORD PTR file$[rsp+32]
	call	?malloc@@YAPEAXI@Z			; malloc
	mov	QWORD PTR buffer$[rsp], rax

; 55   : 	readfs(node, &file,buffer,file.size);

	mov	r9d, DWORD PTR file$[rsp+32]
	mov	r8, QWORD PTR buffer$[rsp]
	lea	rdx, QWORD PTR file$[rsp]
	mov	rcx, QWORD PTR node$[rsp]
	call	?readfs@@YAXPEAU_vfs_node_@@0PEAEI@Z	; readfs

; 56   : 	
; 57   : 	psf_data = buffer;

	mov	rax, QWORD PTR buffer$[rsp]
	mov	QWORD PTR psf_data, rax

; 58   : }

	add	rsp, 376				; 00000178H
	pop	rdi
	pop	rsi
	ret	0
?console_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ENDP	; console_initialize
_TEXT	ENDS
END
