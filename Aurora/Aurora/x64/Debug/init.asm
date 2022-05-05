; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?debug@@3P6AXPEBDZZEA				; debug
_BSS	SEGMENT
?debug@@3P6AXPEBDZZEA DQ 01H DUP (?)			; debug
_BSS	ENDS
CONST	SEGMENT
$SG5650	DB	'Scheduler Initialized', 0aH, 00H
	ORG $+1
$SG5652	DB	'shell', 00H
	ORG $+2
$SG5653	DB	'/init.exe', 00H
	ORG $+2
$SG5654	DB	'priwm', 00H
	ORG $+6
$SG5655	DB	'/priwm.exe', 00H
CONST	ENDS
PUBLIC	?debug_print@@YAXPEBDZZ				; debug_print
PUBLIC	?_AuMain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z		; _AuMain
EXTRN	x64_cli:PROC
EXTRN	x64_hlt:PROC
EXTRN	?AuInitializeCpu@@YAXE@Z:PROC			; AuInitializeCpu
EXTRN	?AuHalInitialize@@YAXXZ:PROC			; AuHalInitialize
EXTRN	?AuPmmngrInit@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z:PROC ; AuPmmngrInit
EXTRN	?AuPagingInit@@YAXXZ:PROC			; AuPagingInit
EXTRN	?AuPagingClearLow@@YAXXZ:PROC			; AuPagingClearLow
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
EXTRN	?AuInitializeShMem@@YAXXZ:PROC			; AuInitializeShMem
EXTRN	?AuSharedDeviceInit@@YAXXZ:PROC			; AuSharedDeviceInit
EXTRN	?ttype_init@@YAXXZ:PROC				; ttype_init
EXTRN	?AuNetInitialize@@YAXXZ:PROC			; AuNetInitialize
pdata	SEGMENT
$pdata$?debug_print@@YAXPEBDZZ DD imagerel $LN3
	DD	imagerel $LN3+40
	DD	imagerel $unwind$?debug_print@@YAXPEBDZZ
$pdata$?_AuMain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD imagerel $LN5
	DD	imagerel $LN5+287
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

; 102  : 	
; 103  : 
; 104  : 	AuInitializeShMem();

	call	?AuInitializeShMem@@YAXXZ		; AuInitializeShMem

; 105  : 	AuHalInitialize();

	call	?AuHalInitialize@@YAXXZ			; AuHalInitialize

; 106  : 
; 107  : 	AuInitializeSerial();

	call	?AuInitializeSerial@@YAXXZ		; AuInitializeSerial

; 108  : 	AuInitializeBasicAcpi (info->acpi_table_pointer);

	mov	rax, QWORD PTR info$[rsp]
	mov	rcx, QWORD PTR [rax+82]
	call	?AuInitializeBasicAcpi@@YAXPEAX@Z	; AuInitializeBasicAcpi

; 109  : 
; 110  : 	ahci_initialize();

	call	?ahci_initialize@@YAXXZ			; ahci_initialize

; 111  : 	hda_initialize();

	call	?hda_initialize@@YAXXZ			; hda_initialize

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
; 120  : 	AuNetInitialize();

	call	?AuNetInitialize@@YAXXZ			; AuNetInitialize

; 121  : 	AuSharedDeviceInit();

	call	?AuSharedDeviceInit@@YAXXZ		; AuSharedDeviceInit

; 122  : 
; 123  : 	//Here we initialise all drivers stuffs
; 124  : 	/* Clear interrupts as scheduler will enable it */
; 125  : 	x64_cli();

	call	x64_cli

; 126  : 	AuDrvMngrInitialize(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?AuDrvMngrInitialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; AuDrvMngrInitialize

; 127  : 	AuKeyboardInitialize();

	call	?AuKeyboardInitialize@@YAXXZ		; AuKeyboardInitialize

; 128  : 	dwm_ipc_init();

	call	?dwm_ipc_init@@YAXXZ			; dwm_ipc_init

; 129  : 	pri_loop_init();

	call	?pri_loop_init@@YAXXZ			; pri_loop_init

; 130  : 
; 131  : 	process_list_initialize();

	call	?process_list_initialize@@YAXXZ		; process_list_initialize

; 132  : 	ttype_init();

	call	?ttype_init@@YAXXZ			; ttype_init

; 133  : 	
; 134  : 	//================================================
; 135  : 	//! Initialize the scheduler here
; 136  : 	//!===============================================
; 137  : 	AuInitializeScheduler();

	call	?AuInitializeScheduler@@YAXXZ		; AuInitializeScheduler

; 138  : 	
; 139  : 	/*Initialize other processor */
; 140  : 	AuInitializeCpu(AuGetNumCPU());

	call	?AuGetNumCPU@@YAEXZ			; AuGetNumCPU
	movzx	ecx, al
	call	?AuInitializeCpu@@YAXE@Z		; AuInitializeCpu

; 141  : 
; 142  : 	/*Clear the lower half for user space */
; 143  : 	AuPagingClearLow();

	call	?AuPagingClearLow@@YAXXZ		; AuPagingClearLow

; 144  : 
; 145  : 
; 146  : #ifdef ARCH_X64
; 147  : 	
; 148  : 	printf ("Scheduler Initialized\n");

	lea	rcx, OFFSET FLAT:$SG5650
	call	printf

; 149  : 
; 150  : 	int au_status = 0;

	mov	DWORD PTR au_status$[rsp], 0

; 151  : 
; 152  : 	/* start the sound service manager at id 1 */
; 153  : 	au_status = AuCreateProcess ("/init.exe","shell");

	lea	rdx, OFFSET FLAT:$SG5652
	lea	rcx, OFFSET FLAT:$SG5653
	call	?AuCreateProcess@@YAHPEBDPEAD@Z		; AuCreateProcess
	mov	DWORD PTR au_status$[rsp], eax

; 154  : 
; 155  : 	/* start the compositing window manager at id 2 */
; 156  : 	au_status = AuCreateProcess ("/priwm.exe","priwm");

	lea	rdx, OFFSET FLAT:$SG5654
	lea	rcx, OFFSET FLAT:$SG5655
	call	?AuCreateProcess@@YAHPEBDPEAD@Z		; AuCreateProcess
	mov	DWORD PTR au_status$[rsp], eax

; 157  : 
; 158  : 	//au_status = AuCreateProcess ("/dock.exe", "dock");
; 159  : 	//! Here start the scheduler (multitasking engine)
; 160  : 	AuSchedulerStart();

	call	?AuSchedulerStart@@YAXXZ		; AuSchedulerStart
$LN2@AuMain:

; 161  : #endif
; 162  : 
; 163  : 	//! Loop forever
; 164  : 	while(1) {

	xor	eax, eax
	cmp	eax, 1
	je	SHORT $LN1@AuMain

; 165  : 		//!looping looping
; 166  : 		x64_cli();

	call	x64_cli

; 167  : 		x64_hlt();

	call	x64_hlt

; 168  : 	}

	jmp	SHORT $LN2@AuMain
$LN1@AuMain:

; 169  : }

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
