; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?display@@3U__display__@@A			; display
_BSS	SEGMENT
?display@@3U__display__@@A DB 018H DUP (?)		; display
_BSS	ENDS
PUBLIC	?initialize_screen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; initialize_screen
PUBLIC	?screen_set_configuration@@YAXII@Z		; screen_set_configuration
PUBLIC	?get_screen_width@@YAIXZ			; get_screen_width
PUBLIC	?get_screen_height@@YAIXZ			; get_screen_height
PUBLIC	?get_framebuffer_addr@@YAPEAIXZ			; get_framebuffer_addr
PUBLIC	?get_bpp@@YAIXZ					; get_bpp
PUBLIC	?get_screen_scanline@@YAGXZ			; get_screen_scanline
PUBLIC	?draw_pixel@@YAXIII@Z				; draw_pixel
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	?map_page@@YA_N_K0@Z:PROC			; map_page
pdata	SEGMENT
$pdata$?initialize_screen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD imagerel $LN3
	DD	imagerel $LN3+109
	DD	imagerel $unwind$?initialize_screen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z
$pdata$?screen_set_configuration@@YAXII@Z DD imagerel $LN6
	DD	imagerel $LN6+149
	DD	imagerel $unwind$?screen_set_configuration@@YAXII@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?initialize_screen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD 010901H
	DD	04209H
$unwind$?screen_set_configuration@@YAXII@Z DD 010c01H
	DD	0620cH
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
x$ = 8
y$ = 16
color$ = 24
?draw_pixel@@YAXIII@Z PROC				; draw_pixel

; 68   : void draw_pixel (unsigned x, unsigned y, uint32_t color ) {

	mov	DWORD PTR [rsp+24], r8d
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx

; 69   : 	display.buffer[x + y * display.width] = color;

	mov	eax, DWORD PTR y$[rsp]
	imul	eax, DWORD PTR ?display@@3U__display__@@A
	mov	ecx, DWORD PTR x$[rsp]
	add	ecx, eax
	mov	eax, ecx
	mov	eax, eax
	mov	rcx, QWORD PTR ?display@@3U__display__@@A+8
	mov	edx, DWORD PTR color$[rsp]
	mov	DWORD PTR [rcx+rax*4], edx

; 70   : }

	ret	0
?draw_pixel@@YAXIII@Z ENDP				; draw_pixel
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
?get_screen_scanline@@YAGXZ PROC			; get_screen_scanline

; 64   : 	return display.scanline;

	movzx	eax, WORD PTR ?display@@3U__display__@@A+20

; 65   : }

	ret	0
?get_screen_scanline@@YAGXZ ENDP			; get_screen_scanline
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
?get_bpp@@YAIXZ PROC					; get_bpp

; 60   : 	return display.bpp;

	mov	eax, DWORD PTR ?display@@3U__display__@@A+16

; 61   : }

	ret	0
?get_bpp@@YAIXZ ENDP					; get_bpp
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
?get_framebuffer_addr@@YAPEAIXZ PROC			; get_framebuffer_addr

; 56   : 	return display.buffer;

	mov	rax, QWORD PTR ?display@@3U__display__@@A+8

; 57   : }

	ret	0
?get_framebuffer_addr@@YAPEAIXZ ENDP			; get_framebuffer_addr
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
?get_screen_height@@YAIXZ PROC				; get_screen_height

; 52   : 	return display.height;

	mov	eax, DWORD PTR ?display@@3U__display__@@A+4

; 53   : }

	ret	0
?get_screen_height@@YAIXZ ENDP				; get_screen_height
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
?get_screen_width@@YAIXZ PROC				; get_screen_width

; 48   : 	return display.width;

	mov	eax, DWORD PTR ?display@@3U__display__@@A

; 49   : }

	ret	0
?get_screen_width@@YAIXZ ENDP				; get_screen_width
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
i$1 = 32
width$ = 64
height$ = 72
?screen_set_configuration@@YAXII@Z PROC			; screen_set_configuration

; 38   : void screen_set_configuration (uint32_t width, uint32_t height) {

$LN6:
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 56					; 00000038H

; 39   : 	display.width = width;

	mov	eax, DWORD PTR width$[rsp]
	mov	DWORD PTR ?display@@3U__display__@@A, eax

; 40   : 	display.height = height;

	mov	eax, DWORD PTR height$[rsp]
	mov	DWORD PTR ?display@@3U__display__@@A+4, eax

; 41   : 
; 42   : 	//! Map a shared region for other processes to output
; 43   : 	for (int i = 0; i < display.width * display.height * 32 / 4096; i++)

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@screen_set
$LN2@screen_set:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN3@screen_set:
	mov	eax, DWORD PTR ?display@@3U__display__@@A
	imul	eax, DWORD PTR ?display@@3U__display__@@A+4
	imul	eax, 32					; 00000020H
	xor	edx, edx
	mov	ecx, 4096				; 00001000H
	div	ecx
	cmp	DWORD PTR i$1[rsp], eax
	jae	SHORT $LN1@screen_set

; 44   : 		map_page ((uint64_t)display.buffer + i * 4096,0xFFFFF00000000000 + i * 4096);

	mov	eax, DWORD PTR i$1[rsp]
	imul	eax, 4096				; 00001000H
	cdqe
	mov	rcx, 17592186044416			; 0000100000000000H
	sub	rax, rcx
	mov	ecx, DWORD PTR i$1[rsp]
	imul	ecx, 4096				; 00001000H
	movsxd	rcx, ecx
	mov	rdx, QWORD PTR ?display@@3U__display__@@A+8
	add	rdx, rcx
	mov	rcx, rdx
	mov	rdx, rax
	call	?map_page@@YA_N_K0@Z			; map_page
	jmp	SHORT $LN2@screen_set
$LN1@screen_set:

; 45   : }

	add	rsp, 56					; 00000038H
	ret	0
?screen_set_configuration@@YAXII@Z ENDP			; screen_set_configuration
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
info$ = 48
?initialize_screen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z PROC	; initialize_screen

; 22   : void initialize_screen (KERNEL_BOOT_INFO *info){

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 23   : 	display.buffer = info->graphics_framebuffer;

	mov	rax, QWORD PTR info$[rsp]
	mov	rax, QWORD PTR [rax+28]
	mov	QWORD PTR ?display@@3U__display__@@A+8, rax

; 24   : 	display.width = info->X_Resolution;

	mov	rax, QWORD PTR info$[rsp]
	movzx	eax, WORD PTR [rax+44]
	mov	DWORD PTR ?display@@3U__display__@@A, eax

; 25   : 	display.height = info->Y_Resolution;

	mov	rax, QWORD PTR info$[rsp]
	movzx	eax, WORD PTR [rax+46]
	mov	DWORD PTR ?display@@3U__display__@@A+4, eax

; 26   : 	display.bpp = 32;

	mov	DWORD PTR ?display@@3U__display__@@A+16, 32 ; 00000020H

; 27   : 	display.scanline = info->pixels_per_line;

	mov	rax, QWORD PTR info$[rsp]
	movzx	eax, WORD PTR [rax+48]
	mov	WORD PTR ?display@@3U__display__@@A+20, ax

; 28   : #ifdef ARCH_X64
; 29   : 	
; 30   : 
; 31   : 	//!map a shared page for fast IPC
; 32   : 	map_page ((uint64_t)pmmngr_alloc(),0xFFFFD00000000000);

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	rdx, -52776558133248			; ffffd00000000000H
	mov	rcx, rax
	call	?map_page@@YA_N_K0@Z			; map_page

; 33   : #endif
; 34   : 
; 35   : 
; 36   : }

	add	rsp, 40					; 00000028H
	ret	0
?initialize_screen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ENDP	; initialize_screen
_TEXT	ENDS
END
