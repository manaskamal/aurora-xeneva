; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?debug@@3P6AXPEBDZZEA				; debug
_BSS	SEGMENT
?debug@@3P6AXPEBDZZEA DQ 01H DUP (?)			; debug
_BSS	ENDS
CONST	SEGMENT
$SG5583	DB	'Scheduler Initialized', 0aH, 00H
	ORG $+1
$SG5585	DB	'shell', 00H
	ORG $+2
$SG5586	DB	'/sndsrv.exe', 00H
$SG5587	DB	'priwm', 00H
	ORG $+6
$SG5588	DB	'/priwm.exe', 00H
CONST	ENDS
PUBLIC	?debug_print@@YAXPEBDZZ				; debug_print
PUBLIC	?_AuMain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z		; _AuMain
EXTRN	x64_cli:PROC
EXTRN	x64_hlt:PROC
EXTRN	?AuInitializeCpu@@YAXE@Z:PROC			; AuInitializeCpu
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
EXTRN	?AuInitializeRTC@@YAXXZ:PROC			; AuInitializeRTC
EXTRN	?AuInitializeBasicAcpi@@YAXPEAX@Z:PROC		; AuInitializeBasicAcpi
EXTRN	?AuGetNumCPU@@YAEXZ:PROC			; AuGetNumCPU
EXTRN	?AuVFSInit@@YAXXZ:PROC				; AuVFSInit
EXTRN	?AuInitializeScheduler@@YAXXZ:PROC		; AuInitializeScheduler
EXTRN	?AuSchedulerStart@@YAXXZ:PROC			; AuSchedulerStart
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
	DD	imagerel $LN5+267
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

; 96   : void _AuMain (KERNEL_BOOT_INFO *info) {

$LN5:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 97   : 	debug = info->printf_gui;

	mov	rax, QWORD PTR info$[rsp]
	mov	rax, QWORD PTR [rax+106]
	mov	QWORD PTR ?debug@@3P6AXPEBDZZEA, rax	; debug

; 98   : 	//! Initialize the memory mappings
; 99   : 	AuPmmngrInit (info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?AuPmmngrInit@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; AuPmmngrInit

; 100  : 	AuPagingInit();

	call	?AuPagingInit@@YAXXZ			; AuPagingInit

; 101  : 	AuHeapInitialize();

	call	?AuHeapInitialize@@YAXXZ		; AuHeapInitialize

; 102  : 	AuHalInitialize();

	call	?AuHalInitialize@@YAXXZ			; AuHalInitialize

; 103  : 
; 104  : 	AuInitializeSerial();

	call	?AuInitializeSerial@@YAXXZ		; AuInitializeSerial

; 105  : 	AuInitializeBasicAcpi (info->acpi_table_pointer);

	mov	rax, QWORD PTR info$[rsp]
	mov	rcx, QWORD PTR [rax+82]
	call	?AuInitializeBasicAcpi@@YAXPEAX@Z	; AuInitializeBasicAcpi

; 106  : 
; 107  : 	ahci_initialize();

	call	?ahci_initialize@@YAXXZ			; ahci_initialize

; 108  : 	hda_initialize();

	call	?hda_initialize@@YAXXZ			; hda_initialize

; 109  : 
; 110  : 	AuVFSInit();

	call	?AuVFSInit@@YAXXZ			; AuVFSInit

; 111  : 	
; 112  : 	AuInitializeScreen(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?AuInitializeScreen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; AuInitializeScreen

; 113  : 	AuConsoleInitialize(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?AuConsoleInitialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; AuConsoleInitialize

; 114  : 	AuInitializeRTC(); 

	call	?AuInitializeRTC@@YAXXZ			; AuInitializeRTC

; 115  : 
; 116  : 	AuInitializeMouse();

	call	?AuInitializeMouse@@YAXXZ		; AuInitializeMouse

; 117  : 
; 118  : 	//Here we initialise all drivers stuffs
; 119  : 	/* Clear interrupts as scheduler will enable it */
; 120  : 	x64_cli();

	call	x64_cli

; 121  : 	AuDrvMngrInitialize(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?AuDrvMngrInitialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; AuDrvMngrInitialize

; 122  : 	AuKeyboardInitialize();

	call	?AuKeyboardInitialize@@YAXXZ		; AuKeyboardInitialize

; 123  : 	dwm_ipc_init();

	call	?dwm_ipc_init@@YAXXZ			; dwm_ipc_init

; 124  : 	pri_loop_init();

	call	?pri_loop_init@@YAXXZ			; pri_loop_init

; 125  : 
; 126  : 	process_list_initialize();

	call	?process_list_initialize@@YAXXZ		; process_list_initialize

; 127  : 	ttype_init();

	call	?ttype_init@@YAXXZ			; ttype_init

; 128  : 	
; 129  : 	/*Initialize other processor */
; 130  : 	AuInitializeCpu(AuGetNumCPU());

	call	?AuGetNumCPU@@YAEXZ			; AuGetNumCPU
	movzx	ecx, al
	call	?AuInitializeCpu@@YAXE@Z		; AuInitializeCpu

; 131  : 	
; 132  : #ifdef ARCH_X64
; 133  : 	//================================================
; 134  : 	//! Initialize the scheduler here
; 135  : 	//!===============================================
; 136  : 	AuInitializeScheduler();

	call	?AuInitializeScheduler@@YAXXZ		; AuInitializeScheduler

; 137  : 
; 138  : 	printf ("Scheduler Initialized\n");

	lea	rcx, OFFSET FLAT:$SG5583
	call	printf

; 139  : 
; 140  : 	int au_status = 0;

	mov	DWORD PTR au_status$[rsp], 0

; 141  : 
; 142  : 	/* start the sound service manager at id 1 */
; 143  : 	au_status = AuCreateProcess ("/sndsrv.exe","shell");

	lea	rdx, OFFSET FLAT:$SG5585
	lea	rcx, OFFSET FLAT:$SG5586
	call	?AuCreateProcess@@YAHPEBDPEAD@Z		; AuCreateProcess
	mov	DWORD PTR au_status$[rsp], eax

; 144  : 
; 145  : 	/* start the compositing window manager at id 2 */
; 146  : 	au_status = AuCreateProcess ("/priwm.exe","priwm");

	lea	rdx, OFFSET FLAT:$SG5587
	lea	rcx, OFFSET FLAT:$SG5588
	call	?AuCreateProcess@@YAHPEBDPEAD@Z		; AuCreateProcess
	mov	DWORD PTR au_status$[rsp], eax

; 147  : 
; 148  : 	//au_status = AuCreateProcess ("/dock.exe", "dock");
; 149  : 	//! Here start the scheduler (multitasking engine)
; 150  : 	AuSchedulerStart();

	call	?AuSchedulerStart@@YAXXZ		; AuSchedulerStart
$LN2@AuMain:

; 151  : #endif
; 152  : 
; 153  : 	//! Loop forever
; 154  : 	while(1) {

	xor	eax, eax
	cmp	eax, 1
	je	SHORT $LN1@AuMain

; 155  : 		//!looping looping
; 156  : 		x64_cli();

	call	x64_cli

; 157  : 		x64_hlt();

	call	x64_hlt

; 158  : 	}

	jmp	SHORT $LN2@AuMain
$LN1@AuMain:

; 159  : }

	add	rsp, 56					; 00000038H
	ret	0
?_AuMain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ENDP		; _AuMain
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
text$ = 48
?debug_print@@YAXPEBDZZ PROC				; debug_print

; 88   : void debug_print (const char* text, ...) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+32], r9
	sub	rsp, 40					; 00000028H

; 89   : 	debug(text);

	mov	rcx, QWORD PTR text$[rsp]
	call	QWORD PTR ?debug@@3P6AXPEBDZZEA		; debug

; 90   : }

	add	rsp, 40					; 00000028H
	ret	0
?debug_print@@YAXPEBDZZ ENDP				; debug_print
_TEXT	ENDS
END
