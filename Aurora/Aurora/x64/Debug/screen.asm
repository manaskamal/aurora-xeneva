; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?display@@3U__display__@@A			; display
_BSS	SEGMENT
?display@@3U__display__@@A DB 020H DUP (?)		; display
_BSS	ENDS
CONST	SEGMENT
$SG3025	DB	'fb', 00H
	ORG $+5
$SG3026	DB	'/dev/fb', 00H
CONST	ENDS
PUBLIC	?initialize_screen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; initialize_screen
PUBLIC	?screen_set_configuration@@YAXII@Z		; screen_set_configuration
PUBLIC	?get_screen_width@@YAIXZ			; get_screen_width
PUBLIC	?get_screen_height@@YAIXZ			; get_screen_height
PUBLIC	?get_framebuffer_addr@@YAPEAIXZ			; get_framebuffer_addr
PUBLIC	?get_bpp@@YAIXZ					; get_bpp
PUBLIC	?get_screen_scanline@@YAGXZ			; get_screen_scanline
PUBLIC	?get_fb_size@@YAIXZ				; get_fb_size
PUBLIC	?draw_pixel@@YAXIII@Z				; draw_pixel
PUBLIC	?screen_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z	; screen_io_query
EXTRN	?strcpy@@YAPEADPEADPEBD@Z:PROC			; strcpy
EXTRN	?vfs_mount@@YAXPEADPEAU_vfs_node_@@@Z:PROC	; vfs_mount
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	?map_page@@YA_N_K0E@Z:PROC			; map_page
pdata	SEGMENT
$pdata$?initialize_screen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD imagerel $LN3
	DD	imagerel $LN3+287
	DD	imagerel $unwind$?initialize_screen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z
$pdata$?screen_set_configuration@@YAXII@Z DD imagerel $LN6
	DD	imagerel $LN6+142
	DD	imagerel $unwind$?screen_set_configuration@@YAXII@Z
$pdata$?screen_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z DD imagerel $LN9
	DD	imagerel $LN9+142
	DD	imagerel $unwind$?screen_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?initialize_screen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD 010901H
	DD	06209H
$unwind$?screen_set_configuration@@YAXII@Z DD 010c01H
	DD	0620cH
$unwind$?screen_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z DD 011201H
	DD	04212H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
scanline$1 = 0
tv64 = 4
width$2 = 8
height$3 = 12
bpp$4 = 16
node$ = 48
code$ = 56
arg$ = 64
?screen_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z PROC	; screen_io_query

; 145  : int screen_io_query (vfs_node_t* node, int code, void* arg) {

$LN9:
	mov	QWORD PTR [rsp+24], r8
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 146  : 	switch (code) {

	mov	eax, DWORD PTR code$[rsp]
	mov	DWORD PTR tv64[rsp], eax
	cmp	DWORD PTR tv64[rsp], 257		; 00000101H
	je	SHORT $LN4@screen_io_
	cmp	DWORD PTR tv64[rsp], 258		; 00000102H
	je	SHORT $LN3@screen_io_
	cmp	DWORD PTR tv64[rsp], 259		; 00000103H
	je	SHORT $LN2@screen_io_
	cmp	DWORD PTR tv64[rsp], 263		; 00000107H
	je	SHORT $LN1@screen_io_
	jmp	SHORT $LN5@screen_io_
$LN4@screen_io_:

; 147  : 	case SCREEN_GETWIDTH:{
; 148  : 		uint32_t width = display.width;

	mov	eax, DWORD PTR ?display@@3U__display__@@A
	mov	DWORD PTR width$2[rsp], eax

; 149  : 		return width;

	mov	eax, DWORD PTR width$2[rsp]
	jmp	SHORT $LN7@screen_io_

; 150  : 		break;

	jmp	SHORT $LN5@screen_io_
$LN3@screen_io_:

; 151  : 	}
; 152  : 	case SCREEN_GETHEIGHT:{
; 153  : 		uint32_t height = display.height;

	mov	eax, DWORD PTR ?display@@3U__display__@@A+4
	mov	DWORD PTR height$3[rsp], eax

; 154  : 		return height;

	mov	eax, DWORD PTR height$3[rsp]
	jmp	SHORT $LN7@screen_io_

; 155  : 		break;

	jmp	SHORT $LN5@screen_io_
$LN2@screen_io_:

; 156  : 	}
; 157  : 	case SCREEN_GETBPP:{
; 158  : 		uint32_t bpp = display.bpp;

	mov	eax, DWORD PTR ?display@@3U__display__@@A+16
	mov	DWORD PTR bpp$4[rsp], eax

; 159  : 		return bpp;

	mov	eax, DWORD PTR bpp$4[rsp]
	jmp	SHORT $LN7@screen_io_

; 160  : 		break;

	jmp	SHORT $LN5@screen_io_
$LN1@screen_io_:

; 161  : 	 }
; 162  : 	case SCREEN_GET_SCANLINE: {
; 163  : 		uint16_t scanline = display.scanline;

	movzx	eax, WORD PTR ?display@@3U__display__@@A+20
	mov	WORD PTR scanline$1[rsp], ax

; 164  : 		return scanline;

	movzx	eax, WORD PTR scanline$1[rsp]
$LN5@screen_io_:
$LN7@screen_io_:

; 165  : 		break;
; 166  : 	}
; 167  : 	}
; 168  : }

	add	rsp, 40					; 00000028H
	ret	0
?screen_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z ENDP	; screen_io_query
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
x$ = 8
y$ = 16
color$ = 24
?draw_pixel@@YAXIII@Z PROC				; draw_pixel

; 134  : void draw_pixel (unsigned x, unsigned y, uint32_t color ) {

	mov	DWORD PTR [rsp+24], r8d
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx

; 135  : 	display.buffer[x + y * display.width] = color;

	mov	eax, DWORD PTR y$[rsp]
	imul	eax, DWORD PTR ?display@@3U__display__@@A
	mov	ecx, DWORD PTR x$[rsp]
	add	ecx, eax
	mov	eax, ecx
	mov	eax, eax
	mov	rcx, QWORD PTR ?display@@3U__display__@@A+8
	mov	edx, DWORD PTR color$[rsp]
	mov	DWORD PTR [rcx+rax*4], edx

; 136  : }

	ret	0
?draw_pixel@@YAXIII@Z ENDP				; draw_pixel
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
?get_fb_size@@YAIXZ PROC				; get_fb_size

; 125  : 	return display.size;

	mov	eax, DWORD PTR ?display@@3U__display__@@A+24

; 126  : }

	ret	0
?get_fb_size@@YAIXZ ENDP				; get_fb_size
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
?get_screen_scanline@@YAGXZ PROC			; get_screen_scanline

; 117  : 	return display.scanline;

	movzx	eax, WORD PTR ?display@@3U__display__@@A+20

; 118  : }

	ret	0
?get_screen_scanline@@YAGXZ ENDP			; get_screen_scanline
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
?get_bpp@@YAIXZ PROC					; get_bpp

; 109  : 	return display.bpp;

	mov	eax, DWORD PTR ?display@@3U__display__@@A+16

; 110  : }

	ret	0
?get_bpp@@YAIXZ ENDP					; get_bpp
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
?get_framebuffer_addr@@YAPEAIXZ PROC			; get_framebuffer_addr

; 101  : 	return display.buffer;

	mov	rax, QWORD PTR ?display@@3U__display__@@A+8

; 102  : }

	ret	0
?get_framebuffer_addr@@YAPEAIXZ ENDP			; get_framebuffer_addr
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
?get_screen_height@@YAIXZ PROC				; get_screen_height

; 92   : 	return display.height;

	mov	eax, DWORD PTR ?display@@3U__display__@@A+4

; 93   : }

	ret	0
?get_screen_height@@YAIXZ ENDP				; get_screen_height
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
?get_screen_width@@YAIXZ PROC				; get_screen_width

; 84   : 	return display.width;

	mov	eax, DWORD PTR ?display@@3U__display__@@A

; 85   : }

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

; 70   : void screen_set_configuration (uint32_t width, uint32_t height) {

$LN6:
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 56					; 00000038H

; 71   : 	display.width = width;

	mov	eax, DWORD PTR width$[rsp]
	mov	DWORD PTR ?display@@3U__display__@@A, eax

; 72   : 	display.height = height;

	mov	eax, DWORD PTR height$[rsp]
	mov	DWORD PTR ?display@@3U__display__@@A+4, eax

; 73   : 	//! Map a shared region for other processes to output
; 74   : 	for (int i = 0; i < display.size / 4096 ; i++)

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@screen_set
$LN2@screen_set:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN3@screen_set:
	xor	edx, edx
	mov	eax, DWORD PTR ?display@@3U__display__@@A+24
	mov	ecx, 4096				; 00001000H
	div	ecx
	cmp	DWORD PTR i$1[rsp], eax
	jae	SHORT $LN1@screen_set

; 75   : 		map_page ((uint64_t)display.buffer + i * 4096, 0xFFFFD00000200000 + i * 4096, PAGING_USER);

	mov	eax, DWORD PTR i$1[rsp]
	imul	eax, 4096				; 00001000H
	cdqe
	mov	rcx, 52776556036096			; 00002fffffe00000H
	sub	rax, rcx
	mov	ecx, DWORD PTR i$1[rsp]
	imul	ecx, 4096				; 00001000H
	movsxd	rcx, ecx
	mov	rdx, QWORD PTR ?display@@3U__display__@@A+8
	add	rdx, rcx
	mov	rcx, rdx
	mov	r8b, 4
	mov	rdx, rax
	call	?map_page@@YA_N_K0E@Z			; map_page
	jmp	SHORT $LN2@screen_set
$LN1@screen_set:

; 76   : 
; 77   : }

	add	rsp, 56					; 00000038H
	ret	0
?screen_set_configuration@@YAXII@Z ENDP			; screen_set_configuration
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
svga$ = 32
info$ = 64
?initialize_screen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z PROC	; initialize_screen

; 36   : void initialize_screen (KERNEL_BOOT_INFO *info){

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 37   : 	display.buffer = info->graphics_framebuffer;

	mov	rax, QWORD PTR info$[rsp]
	mov	rax, QWORD PTR [rax+52]
	mov	QWORD PTR ?display@@3U__display__@@A+8, rax

; 38   : 	display.width = info->X_Resolution;

	mov	rax, QWORD PTR info$[rsp]
	movzx	eax, WORD PTR [rax+68]
	mov	DWORD PTR ?display@@3U__display__@@A, eax

; 39   : 	display.height = info->Y_Resolution;

	mov	rax, QWORD PTR info$[rsp]
	movzx	eax, WORD PTR [rax+70]
	mov	DWORD PTR ?display@@3U__display__@@A+4, eax

; 40   : 	display.bpp = 32;

	mov	DWORD PTR ?display@@3U__display__@@A+16, 32 ; 00000020H

; 41   : 	display.scanline = info->pixels_per_line;

	mov	rax, QWORD PTR info$[rsp]
	movzx	eax, WORD PTR [rax+72]
	mov	WORD PTR ?display@@3U__display__@@A+20, ax

; 42   : 	display.size = info->fb_size;

	mov	rax, QWORD PTR info$[rsp]
	mov	eax, DWORD PTR [rax+60]
	mov	DWORD PTR ?display@@3U__display__@@A+24, eax

; 43   : 
; 44   : 	/**
; 45   : 	 * register the device node for screen interface
; 46   : 	 */
; 47   : 	vfs_node_t * svga = (vfs_node_t*)pmmngr_alloc(); 

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR svga$[rsp], rax

; 48   : 	strcpy (svga->filename, "fb");

	mov	rax, QWORD PTR svga$[rsp]
	lea	rdx, OFFSET FLAT:$SG3025
	mov	rcx, rax
	call	?strcpy@@YAPEADPEADPEBD@Z		; strcpy

; 49   : 	svga->size = 0;

	mov	rax, QWORD PTR svga$[rsp]
	mov	DWORD PTR [rax+32], 0

; 50   : 	svga->eof = 0;

	mov	rax, QWORD PTR svga$[rsp]
	mov	DWORD PTR [rax+36], 0

; 51   : 	svga->pos = 0;

	mov	rax, QWORD PTR svga$[rsp]
	mov	DWORD PTR [rax+40], 0

; 52   : 	svga->current = 0;

	mov	rax, QWORD PTR svga$[rsp]
	mov	DWORD PTR [rax+44], 0

; 53   : 	svga->flags = FS_FLAG_GENERAL;

	mov	rax, QWORD PTR svga$[rsp]
	mov	DWORD PTR [rax+48], 2

; 54   : 	svga->status = 0;

	mov	rax, QWORD PTR svga$[rsp]
	mov	DWORD PTR [rax+52], 0

; 55   : 	svga->open = 0;

	mov	rax, QWORD PTR svga$[rsp]
	mov	QWORD PTR [rax+64], 0

; 56   : 	svga->read = 0;

	mov	rax, QWORD PTR svga$[rsp]
	mov	QWORD PTR [rax+72], 0

; 57   : 	svga->write = 0;

	mov	rax, QWORD PTR svga$[rsp]
	mov	QWORD PTR [rax+80], 0

; 58   : 	svga->read_blk = 0;

	mov	rax, QWORD PTR svga$[rsp]
	mov	QWORD PTR [rax+88], 0

; 59   : 	svga->ioquery = screen_io_query;

	mov	rax, QWORD PTR svga$[rsp]
	lea	rcx, OFFSET FLAT:?screen_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z ; screen_io_query
	mov	QWORD PTR [rax+96], rcx

; 60   : 	vfs_mount ("/dev/fb", svga);

	mov	rdx, QWORD PTR svga$[rsp]
	lea	rcx, OFFSET FLAT:$SG3026
	call	?vfs_mount@@YAXPEADPEAU_vfs_node_@@@Z	; vfs_mount

; 61   : }

	add	rsp, 56					; 00000038H
	ret	0
?initialize_screen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ENDP	; initialize_screen
_TEXT	ENDS
END
