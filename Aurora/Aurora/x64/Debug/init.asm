; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?debug@@3P6AXPEBDZZEA				; debug
_BSS	SEGMENT
?debug@@3P6AXPEBDZZEA DQ 01H DUP (?)			; debug
_BSS	ENDS
CONST	SEGMENT
$SG5635	DB	'Scheduler Initialized', 0aH, 00H
	ORG $+1
$SG5637	DB	'shell', 00H
	ORG $+2
$SG5638	DB	'/sndsrv.exe', 00H
$SG5639	DB	'priwm', 00H
	ORG $+6
$SG5640	DB	'/priwm.exe', 00H
CONST	ENDS
PUBLIC	?debug_print@@YAXPEBDZZ				; debug_print
PUBLIC	?_AuMain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z		; _AuMain
EXTRN	x64_cli:PROC
EXTRN	x64_sti:PROC
EXTRN	x64_hlt:PROC
EXTRN	?AuHalInitialize@@YAXXZ:PROC			; AuHalInitialize
EXTRN	?AuPmmngrInit@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z:PROC ; AuPmmngrInit
EXTRN	?AuPagingInit@@YAXXZ:PROC			; AuPagingInit
EXTRN	?AuConsoleInitialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z:PROC ; AuConsoleInitialize
EXTRN	printf:PROC
EXTRN	?AuKeyboardInitialize@@YAXXZ:PROC		; AuKeyboardInitialize
EXTRN	?AuInitializeMouse@@YAXXZ:PROC			; AuInitializeMouse
EXTRN	?AuHeapInitialize@@YAXXZ:PROC			; AuHeapInitialize
EXTRN	?hda_initialize@@YAXXZ:PROC			; hda_initialize
EXTRN	?ahci_initialize@@YAXXZ:PROC			; ahci_initialize
EXTRN	?e1000_initialize@@YAXXZ:PROC			; e1000_initialize
EXTRN	?AuInitializeRTC@@YAXXZ:PROC			; AuInitializeRTC
EXTRN	?AuInitializeBasicAcpi@@YAXPEAX@Z:PROC		; AuInitializeBasicAcpi
EXTRN	?AuVFSInit@@YAXXZ:PROC				; AuVFSInit
EXTRN	?initialize_scheduler@@YAXXZ:PROC		; initialize_scheduler
EXTRN	?scheduler_start@@YAXXZ:PROC			; scheduler_start
EXTRN	?message_init@@YAXXZ:PROC			; message_init
EXTRN	?dwm_ipc_init@@YAXXZ:PROC			; dwm_ipc_init
EXTRN	?AuInitializeScreen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z:PROC ; AuInitializeScreen
EXTRN	?AuCreateProcess@@YAHPEBDPEAD@Z:PROC		; AuCreateProcess
EXTRN	?process_list_initialize@@YAXXZ:PROC		; process_list_initialize
EXTRN	?AuDrvMngrInitialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z:PROC ; AuDrvMngrInitialize
EXTRN	?AuInitializeSerial@@YAXXZ:PROC			; AuInitializeSerial
EXTRN	?pri_loop_init@@YAXXZ:PROC			; pri_loop_init
EXTRN	?ttype_init@@YAXXZ:PROC				; ttype_init
pdata	SEGMENT
$pdata$?debug_print@@YAXPEBDZZ DD imagerel $LN3
	DD	imagerel $LN3+40
	DD	imagerel $unwind$?debug_print@@YAXPEBDZZ
$pdata$?_AuMain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD imagerel $LN5
	DD	imagerel $LN5+269
	DD	imagerel $unwind$?_AuMain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?debug_print@@YAXPEBDZZ DD 011801H
	DD	04218H
$unwind$?_AuMain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD 010901H
	DD	06209H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
au_status$ = 32
info$ = 64
?_AuMain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z PROC		; _AuMain

; 98   : void _AuMain (KERNEL_BOOT_INFO *info) {

$LN5:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 99   : 	debug = info->printf_gui;

	mov	rax, QWORD PTR info$[rsp]
	mov	rax, QWORD PTR [rax+106]
	mov	QWORD PTR ?debug@@3P6AXPEBDZZEA, rax	; debug

; 100  : 	//! Initialize the memory mappings
; 101  : 	AuPmmngrInit (info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?AuPmmngrInit@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; AuPmmngrInit

; 102  : 	AuPagingInit();

	call	?AuPagingInit@@YAXXZ			; AuPagingInit

; 103  : 	AuHeapInitialize();

	call	?AuHeapInitialize@@YAXXZ		; AuHeapInitialize

; 104  : 	AuHalInitialize();

	call	?AuHalInitialize@@YAXXZ			; AuHalInitialize

; 105  : 
; 106  : 	AuInitializeSerial();

	call	?AuInitializeSerial@@YAXXZ		; AuInitializeSerial

; 107  : 	AuInitializeBasicAcpi (info->acpi_table_pointer);

	mov	rax, QWORD PTR info$[rsp]
	mov	rcx, QWORD PTR [rax+82]
	call	?AuInitializeBasicAcpi@@YAXPEAX@Z	; AuInitializeBasicAcpi

; 108  : 
; 109  : 	ahci_initialize();

	call	?ahci_initialize@@YAXXZ			; ahci_initialize

; 110  : 	hda_initialize();

	call	?hda_initialize@@YAXXZ			; hda_initialize

; 111  : 
; 112  : 	AuVFSInit();

	call	?AuVFSInit@@YAXXZ			; AuVFSInit

; 113  : 	
; 114  : 	AuInitializeScreen(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?AuInitializeScreen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; AuInitializeScreen

; 115  : 	AuConsoleInitialize(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?AuConsoleInitialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; AuConsoleInitialize

; 116  : 	AuInitializeRTC(); 

	call	?AuInitializeRTC@@YAXXZ			; AuInitializeRTC

; 117  : 
; 118  : 	AuInitializeMouse();

	call	?AuInitializeMouse@@YAXXZ		; AuInitializeMouse

; 119  : 
; 120  : 	//Here we initialise all drivers stuffs
; 121  : 	AuDrvMngrInitialize(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?AuDrvMngrInitialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; AuDrvMngrInitialize

; 122  : 	AuKeyboardInitialize();

	call	?AuKeyboardInitialize@@YAXXZ		; AuKeyboardInitialize

; 123  : 	message_init ();

	call	?message_init@@YAXXZ			; message_init

; 124  : 	dwm_ipc_init();

	call	?dwm_ipc_init@@YAXXZ			; dwm_ipc_init

; 125  : 	pri_loop_init();

	call	?pri_loop_init@@YAXXZ			; pri_loop_init

; 126  : 	
; 127  : 	e1000_initialize();   //<< receiver not working

	call	?e1000_initialize@@YAXXZ		; e1000_initialize

; 128  : 
; 129  : 	process_list_initialize();

	call	?process_list_initialize@@YAXXZ		; process_list_initialize

; 130  : 	ttype_init();

	call	?ttype_init@@YAXXZ			; ttype_init

; 131  : 	
; 132  : #ifdef ARCH_X64
; 133  : 	//================================================
; 134  : 	//! Initialize the scheduler here
; 135  : 	//!===============================================
; 136  : 	initialize_scheduler();

	call	?initialize_scheduler@@YAXXZ		; initialize_scheduler

; 137  : 
; 138  : 	printf ("Scheduler Initialized\n");

	lea	rcx, OFFSET FLAT:$SG5635
	call	printf

; 139  : 
; 140  : 	x64_cli();

	call	x64_cli

; 141  : 	int au_status = 0;

	mov	DWORD PTR au_status$[rsp], 0

; 142  : 
; 143  : 	/* start the sound service manager at id 1 */
; 144  : 	au_status = AuCreateProcess ("/sndsrv.exe","shell");

	lea	rdx, OFFSET FLAT:$SG5637
	lea	rcx, OFFSET FLAT:$SG5638
	call	?AuCreateProcess@@YAHPEBDPEAD@Z		; AuCreateProcess
	mov	DWORD PTR au_status$[rsp], eax

; 145  : 
; 146  : 	/* start the compositing window manager at id 2 */
; 147  : 	au_status = AuCreateProcess ("/priwm.exe","priwm");

	lea	rdx, OFFSET FLAT:$SG5639
	lea	rcx, OFFSET FLAT:$SG5640
	call	?AuCreateProcess@@YAHPEBDPEAD@Z		; AuCreateProcess
	mov	DWORD PTR au_status$[rsp], eax

; 148  : 
; 149  : 	//create_process ("/dock.exe", "dock");
; 150  : 	x64_sti();

	call	x64_sti

; 151  : 	//! Here start the scheduler (multitasking engine)
; 152  : 	scheduler_start();

	call	?scheduler_start@@YAXXZ			; scheduler_start
$LN2@AuMain:

; 153  : #endif
; 154  : 
; 155  : 	//! Loop forever
; 156  : 	while(1) {

	xor	eax, eax
	cmp	eax, 1
	je	SHORT $LN1@AuMain

; 157  : 		//!looping looping
; 158  : 		x64_cli();

	call	x64_cli

; 159  : 		x64_hlt();

	call	x64_hlt

; 160  : 	}

	jmp	SHORT $LN2@AuMain
$LN1@AuMain:

; 161  : }

	add	rsp, 56					; 00000038H
	ret	0
?_AuMain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ENDP		; _AuMain
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
text$ = 48
?debug_print@@YAXPEBDZZ PROC				; debug_print

; 90   : void debug_print (const char* text, ...) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+32], r9
	sub	rsp, 40					; 00000028H

; 91   : 	debug(text);

	mov	rcx, QWORD PTR text$[rsp]
	call	QWORD PTR ?debug@@3P6AXPEBDZZEA		; debug

; 92   : }

	add	rsp, 40					; 00000028H
	ret	0
?debug_print@@YAXPEBDZZ ENDP				; debug_print
_TEXT	ENDS
END
