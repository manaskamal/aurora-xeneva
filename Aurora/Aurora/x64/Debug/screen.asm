; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?display@@3U__display__@@A			; display
_BSS	SEGMENT
?display@@3U__display__@@A DB 020H DUP (?)		; display
_BSS	ENDS
CONST	SEGMENT
$SG3171	DB	'fb', 00H
	ORG $+5
$SG3172	DB	'VFS Node created', 0aH, 00H
	ORG $+6
$SG3173	DB	'/dev/fb', 00H
$SG3174	DB	'VFS DEV FB Registered', 0aH, 00H
CONST	ENDS
PUBLIC	?AuInitializeScreen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; AuInitializeScreen
PUBLIC	?AuScreenMap@@YAXII@Z				; AuScreenMap
PUBLIC	AuGetScreenWidth
PUBLIC	AuGetScreenHeight
PUBLIC	AuGetFramebuffer
PUBLIC	AuGetScreenBPP
PUBLIC	AuGetScreenScanline
PUBLIC	AuGetFramebufferSize
PUBLIC	AuDrawPixel
PUBLIC	?screen_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z	; screen_io_query
EXTRN	strcpy:PROC
EXTRN	printf:PROC
EXTRN	vfs_mount:PROC
EXTRN	AuPmmngrAlloc:PROC
EXTRN	AuMapPage:PROC
pdata	SEGMENT
$pdata$?AuInitializeScreen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD imagerel $LN9
	DD	imagerel $LN9+448
	DD	imagerel $unwind$?AuInitializeScreen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z
$pdata$?AuScreenMap@@YAXII@Z DD imagerel $LN6
	DD	imagerel $LN6+159
	DD	imagerel $unwind$?AuScreenMap@@YAXII@Z
$pdata$?screen_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z DD imagerel $LN9
	DD	imagerel $LN9+164
	DD	imagerel $unwind$?screen_io_query@@YAHPEAU_vfs_node_@@HPEAX@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?AuInitializeScreen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD 010901H
	DD	06209H
$unwind$?AuScreenMap@@YAXII@Z DD 010c01H
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

; 157  : int screen_io_query (vfs_node_t* node, int code, void* arg) {

$LN9:
	mov	QWORD PTR [rsp+24], r8
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 158  : 	int ret = 0;

	mov	DWORD PTR ret$[rsp], 0

; 159  : 	switch (code) {

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

; 160  : 	case SCREEN_GETWIDTH:{
; 161  : 		uint32_t width = display.width;

	mov	eax, DWORD PTR ?display@@3U__display__@@A
	mov	DWORD PTR width$2[rsp], eax

; 162  : 		ret = width;

	mov	eax, DWORD PTR width$2[rsp]
	mov	DWORD PTR ret$[rsp], eax

; 163  : 		break;

	jmp	SHORT $LN5@screen_io_
$LN3@screen_io_:

; 164  : 	}
; 165  : 	case SCREEN_GETHEIGHT:{
; 166  : 		uint32_t height = display.height;

	mov	eax, DWORD PTR ?display@@3U__display__@@A+4
	mov	DWORD PTR height$3[rsp], eax

; 167  : 		ret = height;

	mov	eax, DWORD PTR height$3[rsp]
	mov	DWORD PTR ret$[rsp], eax

; 168  : 		break;

	jmp	SHORT $LN5@screen_io_
$LN2@screen_io_:

; 169  : 	}
; 170  : 	case SCREEN_GETBPP:{
; 171  : 		uint32_t bpp = display.bpp;

	mov	eax, DWORD PTR ?display@@3U__display__@@A+16
	mov	DWORD PTR bpp$4[rsp], eax

; 172  : 		ret =  bpp;

	mov	eax, DWORD PTR bpp$4[rsp]
	mov	DWORD PTR ret$[rsp], eax

; 173  : 		break;

	jmp	SHORT $LN5@screen_io_
$LN1@screen_io_:

; 174  : 	 }
; 175  : 	case SCREEN_GET_SCANLINE: {
; 176  : 		uint16_t scanline = display.scanline;

	movzx	eax, WORD PTR ?display@@3U__display__@@A+20
	mov	WORD PTR scanline$1[rsp], ax

; 177  : 		ret =  scanline;

	movzx	eax, WORD PTR scanline$1[rsp]
	mov	DWORD PTR ret$[rsp], eax
$LN5@screen_io_:

; 178  : 		break;
; 179  : 	}
; 180  : 	}
; 181  : 
; 182  : 	return ret;

	mov	eax, DWORD PTR ret$[rsp]

; 183  : }

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
AuDrawPixel PROC

; 146  : void AuDrawPixel (unsigned x, unsigned y, uint32_t color ) {

	mov	DWORD PTR [rsp+24], r8d
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx

; 147  : 	display.buffer[x + y * display.width] = color;

	mov	eax, DWORD PTR y$[rsp]
	imul	eax, DWORD PTR ?display@@3U__display__@@A
	mov	ecx, DWORD PTR x$[rsp]
	add	ecx, eax
	mov	eax, ecx
	mov	eax, eax
	mov	rcx, QWORD PTR ?display@@3U__display__@@A+8
	mov	edx, DWORD PTR color$[rsp]
	mov	DWORD PTR [rcx+rax*4], edx

; 148  : }

	ret	0
AuDrawPixel ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
AuGetFramebufferSize PROC

; 137  : 	return display.size;

	mov	eax, DWORD PTR ?display@@3U__display__@@A+24

; 138  : }

	ret	0
AuGetFramebufferSize ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
AuGetScreenScanline PROC

; 129  : 	return display.scanline;

	movzx	eax, WORD PTR ?display@@3U__display__@@A+20

; 130  : }

	ret	0
AuGetScreenScanline ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
AuGetScreenBPP PROC

; 121  : 	return display.bpp;

	mov	eax, DWORD PTR ?display@@3U__display__@@A+16

; 122  : }

	ret	0
AuGetScreenBPP ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
AuGetFramebuffer PROC

; 113  : 	return display.buffer;

	mov	rax, QWORD PTR ?display@@3U__display__@@A+8

; 114  : }

	ret	0
AuGetFramebuffer ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
AuGetScreenHeight PROC

; 104  : 	return display.height;

	mov	eax, DWORD PTR ?display@@3U__display__@@A+4

; 105  : }

	ret	0
AuGetScreenHeight ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
AuGetScreenWidth PROC

; 96   : 	return display.width;

	mov	eax, DWORD PTR ?display@@3U__display__@@A

; 97   : }

	ret	0
AuGetScreenWidth ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
i$1 = 32
width$ = 64
height$ = 72
?AuScreenMap@@YAXII@Z PROC				; AuScreenMap

; 81   : void AuScreenMap (uint32_t width, uint32_t height) {

$LN6:
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 56					; 00000038H

; 82   : 	display.width = width;

	mov	eax, DWORD PTR width$[rsp]
	mov	DWORD PTR ?display@@3U__display__@@A, eax

; 83   : 	display.height = height;

	mov	eax, DWORD PTR height$[rsp]
	mov	DWORD PTR ?display@@3U__display__@@A+4, eax

; 84   : 	//! Map a shared region for other processes to output
; 85   : 	for (int i = 0; i < display.size / 4096 ; i++)

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN3@AuScreenMa
$LN2@AuScreenMa:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN3@AuScreenMa:
	xor	edx, edx
	mov	eax, DWORD PTR ?display@@3U__display__@@A+24
	mov	ecx, 4096				; 00001000H
	div	ecx
	cmp	DWORD PTR i$1[rsp], eax
	jae	SHORT $LN1@AuScreenMa

; 86   : 		AuMapPage((uint64_t)display.buffer + i * 4096, 0xFFFFD00000200000 + i * 4096, PAGING_USER);

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
	call	AuMapPage
	jmp	SHORT $LN2@AuScreenMa
$LN1@AuScreenMa:

; 87   : 
; 88   : 	display.buffer = (uint32_t*)0xFFFFD00000200000;

	mov	rax, -52776556036096			; ffffd00000200000H
	mov	QWORD PTR ?display@@3U__display__@@A+8, rax

; 89   : }

	add	rsp, 56					; 00000038H
	ret	0
?AuScreenMap@@YAXII@Z ENDP				; AuScreenMap
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\screen.cpp
_TEXT	SEGMENT
h$1 = 32
w$2 = 36
svga$ = 40
info$ = 64
?AuInitializeScreen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z PROC	; AuInitializeScreen

; 36   : void AuInitializeScreen (KERNEL_BOOT_INFO *info){

$LN9:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 37   : 	display.buffer = info->graphics_framebuffer;

	mov	rax, QWORD PTR info$[rsp]
	mov	rax, QWORD PTR [rax+44]
	mov	QWORD PTR ?display@@3U__display__@@A+8, rax

; 38   : 	display.width = info->X_Resolution;

	mov	rax, QWORD PTR info$[rsp]
	movzx	eax, WORD PTR [rax+60]
	mov	DWORD PTR ?display@@3U__display__@@A, eax

; 39   : 	display.height = info->Y_Resolution;

	mov	rax, QWORD PTR info$[rsp]
	movzx	eax, WORD PTR [rax+62]
	mov	DWORD PTR ?display@@3U__display__@@A+4, eax

; 40   : 	display.bpp = 32;

	mov	DWORD PTR ?display@@3U__display__@@A+16, 32 ; 00000020H

; 41   : 	display.scanline = info->pixels_per_line;

	mov	rax, QWORD PTR info$[rsp]
	movzx	eax, WORD PTR [rax+64]
	mov	WORD PTR ?display@@3U__display__@@A+20, ax

; 42   : 	display.size = info->fb_size;

	mov	rax, QWORD PTR info$[rsp]
	mov	eax, DWORD PTR [rax+52]
	mov	DWORD PTR ?display@@3U__display__@@A+24, eax

; 43   : 
; 44   : 	/**
; 45   : 	 * register the device node for screen interface
; 46   : 	 */
; 47   : 	vfs_node_t * svga = (vfs_node_t*)AuPmmngrAlloc(); 

	call	AuPmmngrAlloc
	mov	QWORD PTR svga$[rsp], rax

; 48   : 	strcpy (svga->filename, "fb");

	mov	rax, QWORD PTR svga$[rsp]
	lea	rdx, OFFSET FLAT:$SG3171
	mov	rcx, rax
	call	strcpy

; 49   : 	svga->size = 0;

	mov	rax, QWORD PTR svga$[rsp]
	mov	DWORD PTR [rax+32], 0

; 50   : 	svga->eof = 0;

	mov	rax, QWORD PTR svga$[rsp]
	mov	BYTE PTR [rax+36], 0

; 51   : 	svga->pos = 0;

	mov	rax, QWORD PTR svga$[rsp]
	mov	DWORD PTR [rax+40], 0

; 52   : 	svga->current = 0;

	mov	rax, QWORD PTR svga$[rsp]
	mov	DWORD PTR [rax+44], 0

; 53   : 	svga->flags = FS_FLAG_GENERAL;

	mov	rax, QWORD PTR svga$[rsp]
	mov	BYTE PTR [rax+48], 2

; 54   : 	svga->status = 0;

	mov	rax, QWORD PTR svga$[rsp]
	mov	BYTE PTR [rax+49], 0

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

	lea	rcx, OFFSET FLAT:$SG3172
	call	printf

; 61   : 	vfs_mount ("/dev/fb", svga, 0);

	xor	r8d, r8d
	mov	rdx, QWORD PTR svga$[rsp]
	lea	rcx, OFFSET FLAT:$SG3173
	call	vfs_mount

; 62   : 	printf ("VFS DEV FB Registered\n");

	lea	rcx, OFFSET FLAT:$SG3174
	call	printf

; 63   : 
; 64   : 	/* clear the screen */
; 65   : 	for (int w = 0; w < info->X_Resolution; w++) {

	mov	DWORD PTR w$2[rsp], 0
	jmp	SHORT $LN6@AuInitiali
$LN5@AuInitiali:
	mov	eax, DWORD PTR w$2[rsp]
	inc	eax
	mov	DWORD PTR w$2[rsp], eax
$LN6@AuInitiali:
	mov	rax, QWORD PTR info$[rsp]
	movzx	eax, WORD PTR [rax+60]
	cmp	DWORD PTR w$2[rsp], eax
	jge	SHORT $LN4@AuInitiali

; 66   : 		for (int h = 0; h < info->Y_Resolution; h++) {

	mov	DWORD PTR h$1[rsp], 0
	jmp	SHORT $LN3@AuInitiali
$LN2@AuInitiali:
	mov	eax, DWORD PTR h$1[rsp]
	inc	eax
	mov	DWORD PTR h$1[rsp], eax
$LN3@AuInitiali:
	mov	rax, QWORD PTR info$[rsp]
	movzx	eax, WORD PTR [rax+62]
	cmp	DWORD PTR h$1[rsp], eax
	jge	SHORT $LN1@AuInitiali

; 67   : 			info->graphics_framebuffer[w + h * info->X_Resolution] = 0x00000000;

	mov	rax, QWORD PTR info$[rsp]
	movzx	eax, WORD PTR [rax+60]
	mov	ecx, DWORD PTR h$1[rsp]
	imul	ecx, eax
	mov	eax, ecx
	mov	ecx, DWORD PTR w$2[rsp]
	add	ecx, eax
	mov	eax, ecx
	cdqe
	mov	rcx, QWORD PTR info$[rsp]
	mov	rcx, QWORD PTR [rcx+44]
	mov	DWORD PTR [rcx+rax*4], 0

; 68   : 		}

	jmp	SHORT $LN2@AuInitiali
$LN1@AuInitiali:

; 69   : 	}

	jmp	SHORT $LN5@AuInitiali
$LN4@AuInitiali:

; 70   : 
; 71   : 	AuScreenMap(info->X_Resolution, info->Y_Resolution);

	mov	rax, QWORD PTR info$[rsp]
	movzx	eax, WORD PTR [rax+62]
	mov	rcx, QWORD PTR info$[rsp]
	movzx	ecx, WORD PTR [rcx+60]
	mov	edx, eax
	call	?AuScreenMap@@YAXII@Z			; AuScreenMap

; 72   : }

	add	rsp, 56					; 00000038H
	ret	0
?AuInitializeScreen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ENDP	; AuInitializeScreen
_TEXT	ENDS
END
