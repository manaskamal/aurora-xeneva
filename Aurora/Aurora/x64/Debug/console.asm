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
PUBLIC	?console_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; console_initialize
PUBLIC	?puts@@YAXPEAD@Z				; puts
PUBLIC	?putc@@YAXD@Z					; putc
PUBLIC	?console_pixel@@YAXIII@Z			; console_pixel
pdata	SEGMENT
$pdata$?puts@@YAXPEAD@Z DD imagerel $LN24
	DD	imagerel $LN24+724
	DD	imagerel $unwind$?puts@@YAXPEAD@Z
$pdata$?putc@@YAXD@Z DD imagerel $LN13
	DD	imagerel $LN13+501
	DD	imagerel $unwind$?putc@@YAXD@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?puts@@YAXPEAD@Z DD 010901H
	DD	08209H
$unwind$?putc@@YAXD@Z DD 010801H
	DD	08208H
xdata	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\console.cpp
_TEXT	SEGMENT
col$ = 8
x$ = 16
y$ = 24
?console_pixel@@YAXIII@Z PROC				; console_pixel

; 58   : {

	mov	DWORD PTR [rsp+24], r8d
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx

; 59   : 	fb[x + y * screen_width] = col;

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

; 60   : }

	ret	0
?console_pixel@@YAXIII@Z ENDP				; console_pixel
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\console.cpp
_TEXT	SEGMENT
line$ = 0
font$ = 8
x$ = 16
offs$ = 20
mask$ = 24
y$ = 28
tv76 = 32
tv135 = 36
bpl$ = 40
tv183 = 44
kx$ = 48
glyph$ = 56
c$ = 80
?putc@@YAXD@Z PROC					; putc

; 36   : void putc (char c) {

$LN13:
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 72					; 00000048H

; 37   : 	psf2_t *font = (psf2_t*)psf_data;

	mov	rax, QWORD PTR psf_data
	mov	QWORD PTR font$[rsp], rax

; 38   :     int x,y,kx=0,line,mask,offs;

	mov	DWORD PTR kx$[rsp], 0

; 39   :     int bpl=(font->width+7)/8;

	mov	rax, QWORD PTR font$[rsp]
	mov	eax, DWORD PTR [rax+28]
	add	eax, 7
	xor	edx, edx
	mov	ecx, 8
	div	ecx
	mov	DWORD PTR bpl$[rsp], eax

; 40   :   
; 41   : 	
; 42   : 	unsigned char *glyph = (unsigned char*)psf_data + font->headersize + 
; 43   : 				(c>0&&c<font->numglyph?c:0)*font->bytesperglyph;

	movsx	eax, BYTE PTR c$[rsp]
	test	eax, eax
	jle	SHORT $LN9@putc
	movsx	eax, BYTE PTR c$[rsp]
	mov	rcx, QWORD PTR font$[rsp]
	cmp	eax, DWORD PTR [rcx+16]
	jae	SHORT $LN9@putc
	movsx	eax, BYTE PTR c$[rsp]
	mov	DWORD PTR tv76[rsp], eax
	jmp	SHORT $LN10@putc
$LN9@putc:
	mov	DWORD PTR tv76[rsp], 0
$LN10@putc:
	mov	rax, QWORD PTR font$[rsp]
	mov	eax, DWORD PTR [rax+8]
	mov	rcx, QWORD PTR psf_data
	add	rcx, rax
	mov	rax, rcx
	mov	rcx, QWORD PTR font$[rsp]
	mov	edx, DWORD PTR tv76[rsp]
	imul	edx, DWORD PTR [rcx+20]
	mov	ecx, edx
	mov	ecx, ecx
	add	rax, rcx
	mov	QWORD PTR glyph$[rsp], rax

; 44   : 	offs = kx * (font->width + 1);// * 4);

	mov	rax, QWORD PTR font$[rsp]
	mov	eax, DWORD PTR [rax+28]
	inc	eax
	mov	ecx, DWORD PTR kx$[rsp]
	imul	ecx, eax
	mov	eax, ecx
	mov	DWORD PTR offs$[rsp], eax

; 45   : 	for(y=0;y<font->height;y++) {

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

; 46   : 		line=offs; mask=1<<(font->width-1);

	mov	eax, DWORD PTR offs$[rsp]
	mov	DWORD PTR line$[rsp], eax
	mov	rax, QWORD PTR font$[rsp]
	mov	eax, DWORD PTR [rax+28]
	dec	eax
	mov	ecx, 1
	mov	DWORD PTR tv183[rsp], ecx
	movzx	ecx, al
	mov	eax, DWORD PTR tv183[rsp]
	shl	eax, cl
	mov	DWORD PTR mask$[rsp], eax

; 47   : 		for(x=0;x<font->width;x++) {

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

; 48   : 			fb[line + console_x + console_y * screen_width ]=((int)*glyph) & (mask)?0xFFFFFF:0;

	mov	rax, QWORD PTR glyph$[rsp]
	movzx	eax, BYTE PTR [rax]
	and	eax, DWORD PTR mask$[rsp]
	test	eax, eax
	je	SHORT $LN11@putc
	mov	DWORD PTR tv135[rsp], 16777215		; 00ffffffH
	jmp	SHORT $LN12@putc
$LN11@putc:
	mov	DWORD PTR tv135[rsp], 0
$LN12@putc:
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
	mov	edx, DWORD PTR tv135[rsp]
	mov	DWORD PTR [rcx+rax*4], edx

; 49   : 			mask>>=1; line+=1;

	mov	eax, DWORD PTR mask$[rsp]
	sar	eax, 1
	mov	DWORD PTR mask$[rsp], eax
	mov	eax, DWORD PTR line$[rsp]
	inc	eax
	mov	DWORD PTR line$[rsp], eax

; 50   : 		}

	jmp	SHORT $LN2@putc
$LN1@putc:

; 51   : 		fb[line + console_x + console_y * screen_width]=0; glyph+=bpl; offs+=scanline;

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

; 52   : 	}

	jmp	$LN5@putc
$LN4@putc:

; 53   : 	console_x += font->width + 1;

	mov	rax, QWORD PTR font$[rsp]
	mov	eax, DWORD PTR [rax+28]
	mov	ecx, DWORD PTR console_x
	lea	eax, DWORD PTR [rcx+rax+1]
	mov	DWORD PTR console_x, eax

; 54   : }

	add	rsp, 72					; 00000048H
	ret	0
?putc@@YAXD@Z ENDP					; putc
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\console.cpp
_TEXT	SEGMENT
i$1 = 0
line$ = 4
font$ = 8
offs$ = 16
y$ = 20
x$ = 24
mask$ = 28
tv161 = 32
tv135 = 36
bpl$ = 40
tv223 = 44
glyph$2 = 48
s$ = 80
?puts@@YAXPEAD@Z PROC					; puts

; 64   : void puts(char *s){

$LN24:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 65   : 	
; 66   : 	psf2_t *font = (psf2_t*)psf_data;

	mov	rax, QWORD PTR psf_data
	mov	QWORD PTR font$[rsp], rax

; 67   :     int x,y,line,mask,offs;
; 68   :     int bpl=(font->width+7)/8;

	mov	rax, QWORD PTR font$[rsp]
	mov	eax, DWORD PTR [rax+28]
	add	eax, 7
	xor	edx, edx
	mov	ecx, 8
	div	ecx
	mov	DWORD PTR bpl$[rsp], eax
$LN17@puts:

; 69   :     while(*s) {

	mov	rax, QWORD PTR s$[rsp]
	movsx	eax, BYTE PTR [rax]
	test	eax, eax
	je	$LN16@puts

; 70   : 		if (*s == '\n') {

	mov	rax, QWORD PTR s$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 10
	jne	$LN15@puts

; 71   : 
; 72   : 			//!Scroll
; 73   : 			if (console_y + 1 > screen_height) {

	mov	eax, DWORD PTR console_y
	inc	eax
	movzx	ecx, WORD PTR screen_height
	cmp	eax, ecx
	jle	SHORT $LN14@puts

; 74   : 				for (int i = 16; i < screen_height * screen_width; i++) {

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

; 75   : 					fb[i] = fb[i + screen_width * 16];

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

; 76   : 				}

	jmp	SHORT $LN12@puts
$LN11@puts:

; 77   : 				console_y--;

	mov	eax, DWORD PTR console_y
	dec	eax
	mov	DWORD PTR console_y, eax
$LN14@puts:

; 78   : 			}
; 79   : 
; 80   : 			console_y += 16;

	mov	eax, DWORD PTR console_y
	add	eax, 16
	mov	DWORD PTR console_y, eax

; 81   : 			console_x = 0;

	mov	DWORD PTR console_x, 0
	jmp	$LN10@puts
$LN15@puts:

; 82   : 			//!Scroll is needed
; 83   : 			
; 84   : 		} else if (*s == '\b') {

	mov	rax, QWORD PTR s$[rsp]
	movsx	eax, BYTE PTR [rax]
	cmp	eax, 8
	jne	SHORT $LN9@puts

; 85   : 			if (console_x > 0) {

	cmp	DWORD PTR console_x, 0
	jle	SHORT $LN8@puts

; 86   : 				console_x--;

	mov	eax, DWORD PTR console_x
	dec	eax
	mov	DWORD PTR console_x, eax
$LN8@puts:

; 87   : 			}
; 88   : 		}else {

	jmp	$LN7@puts
$LN9@puts:

; 89   : 			unsigned char *glyph = (unsigned char*)psf_data + font->headersize + 
; 90   : 				(*s>0&&*s<font->numglyph?*s:0)*font->bytesperglyph;

	mov	rax, QWORD PTR s$[rsp]
	movsx	eax, BYTE PTR [rax]
	test	eax, eax
	jle	SHORT $LN20@puts
	mov	rax, QWORD PTR s$[rsp]
	movsx	eax, BYTE PTR [rax]
	mov	rcx, QWORD PTR font$[rsp]
	cmp	eax, DWORD PTR [rcx+16]
	jae	SHORT $LN20@puts
	mov	rax, QWORD PTR s$[rsp]
	movsx	eax, BYTE PTR [rax]
	mov	DWORD PTR tv135[rsp], eax
	jmp	SHORT $LN21@puts
$LN20@puts:
	mov	DWORD PTR tv135[rsp], 0
$LN21@puts:
	mov	rax, QWORD PTR font$[rsp]
	mov	eax, DWORD PTR [rax+8]
	mov	rcx, QWORD PTR psf_data
	add	rcx, rax
	mov	rax, rcx
	mov	rcx, QWORD PTR font$[rsp]
	mov	edx, DWORD PTR tv135[rsp]
	imul	edx, DWORD PTR [rcx+20]
	mov	ecx, edx
	mov	ecx, ecx
	add	rax, rcx
	mov	QWORD PTR glyph$2[rsp], rax

; 91   : 			offs = console_x * (font->width + 1);// * 4);

	mov	rax, QWORD PTR font$[rsp]
	mov	eax, DWORD PTR [rax+28]
	inc	eax
	mov	ecx, DWORD PTR console_x
	imul	ecx, eax
	mov	eax, ecx
	mov	DWORD PTR offs$[rsp], eax

; 92   : 			for(y=0;y<font->height;y++) {

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

; 93   : 				line=offs; mask=1<<(font->width-1);

	mov	eax, DWORD PTR offs$[rsp]
	mov	DWORD PTR line$[rsp], eax
	mov	rax, QWORD PTR font$[rsp]
	mov	eax, DWORD PTR [rax+28]
	dec	eax
	mov	ecx, 1
	mov	DWORD PTR tv223[rsp], ecx
	movzx	ecx, al
	mov	eax, DWORD PTR tv223[rsp]
	shl	eax, cl
	mov	DWORD PTR mask$[rsp], eax

; 94   : 				for(x=0;x<font->width;x++) {

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

; 95   : 					fb[line  + console_y * screen_width ]=((int)*glyph) & (mask)?0xFFFFFF:0;

	mov	rax, QWORD PTR glyph$2[rsp]
	movzx	eax, BYTE PTR [rax]
	and	eax, DWORD PTR mask$[rsp]
	test	eax, eax
	je	SHORT $LN22@puts
	mov	DWORD PTR tv161[rsp], 16777215		; 00ffffffH
	jmp	SHORT $LN23@puts
$LN22@puts:
	mov	DWORD PTR tv161[rsp], 0
$LN23@puts:
	movzx	eax, WORD PTR screen_width
	mov	ecx, DWORD PTR console_y
	imul	ecx, eax
	mov	eax, ecx
	mov	ecx, DWORD PTR line$[rsp]
	add	ecx, eax
	mov	eax, ecx
	cdqe
	mov	rcx, QWORD PTR fb
	mov	edx, DWORD PTR tv161[rsp]
	mov	DWORD PTR [rcx+rax*4], edx

; 96   : 					mask>>=1; line+=1;

	mov	eax, DWORD PTR mask$[rsp]
	sar	eax, 1
	mov	DWORD PTR mask$[rsp], eax
	mov	eax, DWORD PTR line$[rsp]
	inc	eax
	mov	DWORD PTR line$[rsp], eax

; 97   : 				}

	jmp	SHORT $LN2@puts
$LN1@puts:

; 98   : 				fb[line  + console_y * screen_width]=0; glyph+=bpl; offs+=scanline;

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

; 99   : 			}

	jmp	$LN5@puts
$LN4@puts:

; 100  : 			console_x++;

	mov	eax, DWORD PTR console_x
	inc	eax
	mov	DWORD PTR console_x, eax
$LN7@puts:
$LN10@puts:

; 101  : 		}
; 102  : 		s++; 

	mov	rax, QWORD PTR s$[rsp]
	inc	rax
	mov	QWORD PTR s$[rsp], rax

; 103  :     }

	jmp	$LN17@puts
$LN16@puts:

; 104  : 
; 105  : 	
; 106  : }

	add	rsp, 72					; 00000048H
	ret	0
?puts@@YAXPEAD@Z ENDP					; puts
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\console.cpp
_TEXT	SEGMENT
info$ = 8
?console_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z PROC	; console_initialize

; 25   : void console_initialize (PKERNEL_BOOT_INFO info) {

	mov	QWORD PTR [rsp+8], rcx

; 26   : 	console_x = 0;

	mov	DWORD PTR console_x, 0

; 27   : 	console_y = 0;

	mov	DWORD PTR console_y, 0

; 28   : 	scanline = info->pixels_per_line;

	mov	rax, QWORD PTR info$[rsp]
	movzx	eax, WORD PTR [rax+48]
	mov	WORD PTR scanline, ax

; 29   : 	screen_width = info->X_Resolution;

	mov	rax, QWORD PTR info$[rsp]
	movzx	eax, WORD PTR [rax+44]
	mov	WORD PTR screen_width, ax

; 30   : 	screen_height = info->Y_Resolution;

	mov	rax, QWORD PTR info$[rsp]
	movzx	eax, WORD PTR [rax+46]
	mov	WORD PTR screen_height, ax

; 31   : 	fb = info->graphics_framebuffer;

	mov	rax, QWORD PTR info$[rsp]
	mov	rax, QWORD PTR [rax+28]
	mov	QWORD PTR fb, rax

; 32   : 	psf_data = info->psf_font_data;

	mov	rax, QWORD PTR info$[rsp]
	mov	rax, QWORD PTR [rax+82]
	mov	QWORD PTR psf_data, rax

; 33   : }

	ret	0
?console_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ENDP	; console_initialize
_TEXT	ENDS
END
