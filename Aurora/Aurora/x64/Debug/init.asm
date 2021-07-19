; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

CONST	SEGMENT
$SG6105	DB	'dwm', 00H
	ORG $+4
$SG6106	DB	'dwm.exe', 00H
$SG6107	DB	'dwm2', 00H
	ORG $+3
$SG6108	DB	'dwm2.exe', 00H
	ORG $+3
$SG6109	DB	'dwm3', 00H
	ORG $+7
$SG6110	DB	'dwm3.exe', 00H
CONST	ENDS
PUBLIC	?_kmain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z		; _kmain
EXTRN	?hal_init@@YAXXZ:PROC				; hal_init
EXTRN	?pmmngr_init@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z:PROC ; pmmngr_init
EXTRN	?mm_init@@YAXXZ:PROC				; mm_init
EXTRN	?console_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z:PROC ; console_initialize
EXTRN	?kybrd_init@@YAXXZ:PROC				; kybrd_init
EXTRN	?initialize_mouse@@YAXXZ:PROC			; initialize_mouse
EXTRN	?ata_initialize@@YAXXZ:PROC			; ata_initialize
EXTRN	?svga_init@@YAXXZ:PROC				; svga_init
EXTRN	?initialize_scheduler@@YAXXZ:PROC		; initialize_scheduler
EXTRN	?scheduler_start@@YAXXZ:PROC			; scheduler_start
EXTRN	?message_init@@YAXXZ:PROC			; message_init
EXTRN	?dwm_ipc_init@@YAXXZ:PROC			; dwm_ipc_init
EXTRN	?initialize_vfs@@YAXXZ:PROC			; initialize_vfs
EXTRN	?initialize_screen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z:PROC ; initialize_screen
EXTRN	?create_process@@YAXPEBDPEADE@Z:PROC		; create_process
EXTRN	?driver_mngr_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z:PROC ; driver_mngr_initialize
pdata	SEGMENT
$pdata$?_kmain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD imagerel $LN5
	DD	imagerel $LN5+184
	DD	imagerel $unwind$?_kmain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?_kmain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD 010901H
	DD	04209H
xdata	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
info$ = 48
?_kmain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z PROC		; _kmain

; 45   : void _kmain (KERNEL_BOOT_INFO *info) {

$LN5:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 46   : 	hal_init ();

	call	?hal_init@@YAXXZ			; hal_init

; 47   : 	pmmngr_init (info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?pmmngr_init@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; pmmngr_init

; 48   : 	mm_init(); 

	call	?mm_init@@YAXXZ				; mm_init

; 49   : 	console_initialize(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?console_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; console_initialize

; 50   : 	kybrd_init();

	call	?kybrd_init@@YAXXZ			; kybrd_init

; 51   : 	
; 52   : 	//!initialize runtime drivers
; 53   : 	ata_initialize();

	call	?ata_initialize@@YAXXZ			; ata_initialize

; 54   : 	initialize_vfs();

	call	?initialize_vfs@@YAXXZ			; initialize_vfs

; 55   : 	initialize_screen(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?initialize_screen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; initialize_screen

; 56   : 
; 57   : 	svga_init ();

	call	?svga_init@@YAXXZ			; svga_init

; 58   : 	initialize_mouse();

	call	?initialize_mouse@@YAXXZ		; initialize_mouse

; 59   : 	message_init ();

	call	?message_init@@YAXXZ			; message_init

; 60   : 	dwm_ipc_init();

	call	?dwm_ipc_init@@YAXXZ			; dwm_ipc_init

; 61   : 
; 62   : 	//!initialize every drivers
; 63   : 	driver_mngr_initialize(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?driver_mngr_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; driver_mngr_initialize

; 64   : 
; 65   : #ifdef ARCH_X64
; 66   : 	initialize_scheduler();

	call	?initialize_scheduler@@YAXXZ		; initialize_scheduler

; 67   : 	create_process ("dwm.exe","dwm",20);

	mov	r8b, 20
	lea	rdx, OFFSET FLAT:$SG6105
	lea	rcx, OFFSET FLAT:$SG6106
	call	?create_process@@YAXPEBDPEADE@Z		; create_process

; 68   : 	//! task list should be more than 4 or less than 4 not 
; 69   : 	create_process ("dwm2.exe", "dwm2", 1);

	mov	r8b, 1
	lea	rdx, OFFSET FLAT:$SG6107
	lea	rcx, OFFSET FLAT:$SG6108
	call	?create_process@@YAXPEBDPEADE@Z		; create_process

; 70   : 	create_process ("dwm3.exe", "dwm3", 1);

	mov	r8b, 1
	lea	rdx, OFFSET FLAT:$SG6109
	lea	rcx, OFFSET FLAT:$SG6110
	call	?create_process@@YAXPEBDPEADE@Z		; create_process

; 71   : 	//create_process ("dwm3.exe", "dwm3", 1);
; 72   : 	//create_process ("dwm3.exe", "dwm3", 1);
; 73   : 	scheduler_start();

	call	?scheduler_start@@YAXXZ			; scheduler_start
$LN2@kmain:

; 74   : #endif
; 75   : 	while(1) {

	xor	eax, eax
	cmp	eax, 1
	je	SHORT $LN1@kmain

; 76   : 	}

	jmp	SHORT $LN2@kmain
$LN1@kmain:

; 77   : }

	add	rsp, 40					; 00000028H
	ret	0
?_kmain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ENDP		; _kmain
_TEXT	ENDS
END
