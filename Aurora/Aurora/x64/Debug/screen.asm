; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?display@@3U__display__@@A			; display
_BSS	SEGMENT
?display@@3U__display__@@A DB 020H DUP (?)		; display
_BSS	ENDS
CONST	SEGMENT
$SG3048	DB	'fb', 00H
	ORG $+5
$SG3049	DB	'VFS Node created', 0aH, 00H
	ORG $+6
$SG3050	DB	'/dev/fb', 00H
$SG3051	DB	'VFS DEV FB Registered', 0aH, 00H
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
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
EXTRN	?vfs_mount@@YAXPEADPEAU_vfs_node_@@@Z:PROC	; vfs_mount
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	?map_page@@YA_N_K0E@Z:PROC			; map_page
pdata	SEGMENT
$pdata$?initialize_screen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD imagerel $LN9
	DD	imagerel $LN9+429
	DD	imagerel $unwind$?initialize_screen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z
$pdata$?screen_set_configuration@@YAXII@Z DD imagerel $LN6
	DD	imagerel $LN6+142
	DD	imagerel $unwind$?screen_set_configuration@@YAXII@Z
$pdata$?screen_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z DD imagerel $LN9
	DD	imagerel $LN9+164
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
ret$ = 4
tv64 = 8
width$2 = 12
height$3 = 16
bpp$4 = 20
node$ = 48
code$ = 56
arg$ = 64
?screen_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z PROC	; screen_io_query

; 154  : int screen_io_query (vfs_node_t* node, int code, void* arg) {

$LN9:
	mov	QWORD PTR [rsp+24], r8
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 155  : 	int ret = 0;

	mov	DWORD PTR ret$[rsp], 0

; 156  : 	switch (code) {

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

; 157  : 	case SCREEN_GETWIDTH:{
; 158  : 		uint32_t width = display.width;

	mov	eax, DWORD PTR ?display@@3U__display__@@A
	mov	DWORD PTR width$2[rsp], eax

; 159  : 		ret = width;

	mov	eax, DWORD PTR width$2[rsp]
	mov	DWORD PTR ret$[rsp], eax

; 160  : 		break;

	jmp	SHORT $LN5@screen_io_
$LN3@screen_io_:

; 161  : 	}
; 162  : 	case SCREEN_GETHEIGHT:{
; 163  : 		uint32_t height = display.height;

	mov	eax, DWORD PTR ?display@@3U__display__@@A+4
	mov	DWORD PTR height$3[rsp], eax

; 164  : 		ret = height;

	mov	eax, DWORD PTR height$3[rsp]
	mov	DWORD PTR ret$[rsp], eax

; 165  : 		break;

	jmp	SHORT $LN5@screen_io_
$LN2@screen_io_:

; 166  : 	}
; 167  : 	case SCREEN_GETBPP:{
; 168  : 		uint32_t bpp = display.bpp;

	mov	eax, DWORD PTR ?display@@3U__display__@@A+16
	mov	DWORD PTR bpp$4[rsp], eax

; 169  : 		ret =  bpp;

	mov	eax, DWORD PTR bpp$4[rsp]
	mov	DWORD PTR ret$[rsp], eax

; 170  : 		break;

	jmp	SHORT $LN5@screen_io_
$LN1@screen_io_:

; 171  : 	 }
; 172  : 	case SCREEN_GET_SCANLINE: {
; 173  : 		uint16_t scanline = display.scanline;

	movzx	eax, WORD PTR ?display@@3U__display__@@A+20
	mov	WORD PTR scanline$1[rsp], ax

; 174  : 		ret =  scanline;

	movzx	eax, WORD PTR scanline$1[rsp]
	mov	DWORD PTR ret$[rsp], eax
$LN5@screen_io_:

; 175  : 		break;
; 176  : 	}
; 177  : 	}
; 178  : 
; 179  : 	return ret;

	mov	eax, DWORD PTR ret$[rsp]

; 180  : }

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

; 143  : void draw_pixel (unsigned x, unsigned y, uint32_t color ) {

	mov	DWORD PTR [rsp+24], r8d
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx

; 144  : 	display.buffer[x + y * display.width] = color;

	mov	eax, DWORD PTR y$[rsp]
	imul	eax, DWORD PTR ?display@@3U__display__@@A
	mov	ecx, DWORD PTR x$[rsp]
	add	ecx, eax
	mov	eax, ecx
	mov	eax, eax
	mov	rcx, QWORD PTR ?display@@3U__display__@@A+8
	mov	edx, DWORD PTR color$[rsp]
	mov	DWORD PTR [rcx+rax*4], edx

; 145  : }

	ret	0
?draw_pixel@@YAXIII@Z ENDP				; draw_pixel
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
?get_fb_size@@YAIXZ PROC				; get_fb_size

; 134  : 	return display.size;

	mov	eax, DWORD PTR ?display@@3U__display__@@A+24

; 135  : }

	ret	0
?get_fb_size@@YAIXZ ENDP				; get_fb_size
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
?get_screen_scanline@@YAGXZ PROC			; get_screen_scanline

; 126  : 	return display.scanline;

	movzx	eax, WORD PTR ?display@@3U__display__@@A+20

; 127  : }

	ret	0
?get_screen_scanline@@YAGXZ ENDP			; get_screen_scanline
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
?get_bpp@@YAIXZ PROC					; get_bpp

; 118  : 	return display.bpp;

	mov	eax, DWORD PTR ?display@@3U__display__@@A+16

; 119  : }

	ret	0
?get_bpp@@YAIXZ ENDP					; get_bpp
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
?get_framebuffer_addr@@YAPEAIXZ PROC			; get_framebuffer_addr

; 110  : 	return display.buffer;

	mov	rax, QWORD PTR ?display@@3U__display__@@A+8

; 111  : }

	ret	0
?get_framebuffer_addr@@YAPEAIXZ ENDP			; get_framebuffer_addr
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
?get_screen_height@@YAIXZ PROC				; get_screen_height

; 101  : 	return display.height;

	mov	eax, DWORD PTR ?display@@3U__display__@@A+4

; 102  : }

	ret	0
?get_screen_height@@YAIXZ ENDP				; get_screen_height
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
?get_screen_width@@YAIXZ PROC				; get_screen_width

; 93   : 	return display.width;

	mov	eax, DWORD PTR ?display@@3U__display__@@A

; 94   : }

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

; 79   : void screen_set_configuration (uint32_t width, uint32_t height) {

$LN6:
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 56					; 00000038H

; 80   : 	display.width = width;

	mov	eax, DWORD PTR width$[rsp]
	mov	DWORD PTR ?display@@3U__display__@@A, eax

; 81   : 	display.height = height;

	mov	eax, DWORD PTR height$[rsp]
	mov	DWORD PTR ?display@@3U__display__@@A+4, eax

; 82   : 	//! Map a shared region for other processes to output
; 83   : 	for (int i = 0; i < display.size / 4096 ; i++)

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

; 84   : 		map_page ((uint64_t)display.buffer + i * 4096, 0xFFFFD00000200000 + i * 4096, PAGING_USER);

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

; 85   : 
; 86   : }

	add	rsp, 56					; 00000038H
	ret	0
?screen_set_configuration@@YAXII@Z ENDP			; screen_set_configuration
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
h$1 = 32
w$2 = 36
svga$ = 40
info$ = 64
?initialize_screen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z PROC	; initialize_screen

; 36   : void initialize_screen (KERNEL_BOOT_INFO *info){

$LN9:
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
	lea	rdx, OFFSET FLAT:$SG3048
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

; 60   : 	printf ("VFS Node created\n");

	lea	rcx, OFFSET FLAT:$SG3049
	call	?printf@@YAXPEBDZZ			; printf

; 61   : 	vfs_mount ("/dev/fb", svga);

	mov	rdx, QWORD PTR svga$[rsp]
	lea	rcx, OFFSET FLAT:$SG3050
	call	?vfs_mount@@YAXPEADPEAU_vfs_node_@@@Z	; vfs_mount

; 62   : 	printf ("VFS DEV FB Registered\n");

	lea	rcx, OFFSET FLAT:$SG3051
	call	?printf@@YAXPEBDZZ			; printf

; 63   : 
; 64   : 	/* clear the screen */
; 65   : 	for (int w = 0; w < info->X_Resolution; w++) {

	mov	DWORD PTR w$2[rsp], 0
	jmp	SHORT $LN6@initialize
$LN5@initialize:
	mov	eax, DWORD PTR w$2[rsp]
	inc	eax
	mov	DWORD PTR w$2[rsp], eax
$LN6@initialize:
	mov	rax, QWORD PTR info$[rsp]
	movzx	eax, WORD PTR [rax+68]
	cmp	DWORD PTR w$2[rsp], eax
	jge	SHORT $LN4@initialize

; 66   : 		for (int h = 0; h < info->Y_Resolution; h++) {

	mov	DWORD PTR h$1[rsp], 0
	jmp	SHORT $LN3@initialize
$LN2@initialize:
	mov	eax, DWORD PTR h$1[rsp]
	inc	eax
	mov	DWORD PTR h$1[rsp], eax
$LN3@initialize:
	mov	rax, QWORD PTR info$[rsp]
	movzx	eax, WORD PTR [rax+70]
	cmp	DWORD PTR h$1[rsp], eax
	jge	SHORT $LN1@initialize

; 67   : 			info->graphics_framebuffer[w + h * info->X_Resolution] = 0x00000000;

	mov	rax, QWORD PTR info$[rsp]
	movzx	eax, WORD PTR [rax+68]
	mov	ecx, DWORD PTR h$1[rsp]
	imul	ecx, eax
	mov	eax, ecx
	mov	ecx, DWORD PTR w$2[rsp]
	add	ecx, eax
	mov	eax, ecx
	cdqe
	mov	rcx, QWORD PTR info$[rsp]
	mov	rcx, QWORD PTR [rcx+52]
	mov	DWORD PTR [rcx+rax*4], 0

; 68   : 		}

	jmp	SHORT $LN2@initialize
$LN1@initialize:

; 69   : 	}

	jmp	SHORT $LN5@initialize
$LN4@initialize:

; 70   : }

	add	rsp, 56					; 00000038H
	ret	0
?initialize_screen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ENDP	; initialize_screen
_TEXT	ENDS
END
