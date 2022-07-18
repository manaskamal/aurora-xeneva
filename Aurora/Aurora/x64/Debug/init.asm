; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?debug@@3P6AXPEBDZZEA				; debug
_BSS	SEGMENT
?debug@@3P6AXPEBDZZEA DQ 01H DUP (?)			; debug
_BSS	ENDS
CONST	SEGMENT
$SG5541	DB	'Scheduler Initialized', 0aH, 00H
	ORG $+1
$SG5543	DB	'shell', 00H
	ORG $+2
$SG5544	DB	'/init.exe', 00H
	ORG $+2
$SG5545	DB	'priwm', 00H
	ORG $+6
$SG5546	DB	'/priwm.exe', 00H
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
EXTRN	?ahci_initialize@@YAXXZ:PROC			; ahci_initialize
EXTRN	?AuInitializeRTC@@YAXXZ:PROC			; AuInitializeRTC
EXTRN	?AuInitializeBasicAcpi@@YAXPEAX@Z:PROC		; AuInitializeBasicAcpi
EXTRN	?AuGetNumCPU@@YAEXZ:PROC			; AuGetNumCPU
EXTRN	?AuVFSInit@@YAXXZ:PROC				; AuVFSInit
EXTRN	?AuInitializeScheduler@@YAXXZ:PROC		; AuInitializeScheduler
EXTRN	?AuSchedulerStart@@YAXXZ:PROC			; AuSchedulerStart
EXTRN	?AuPointDevInitialize@@YAXXZ:PROC		; AuPointDevInitialize
EXTRN	?AuInitializeScreen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z:PROC ; AuInitializeScreen
EXTRN	?AuSysLibInitialize@@YAXXZ:PROC			; AuSysLibInitialize
EXTRN	?AuCreateProcess@@YAHPEBDPEAD@Z:PROC		; AuCreateProcess
EXTRN	?process_list_initialize@@YAXXZ:PROC		; process_list_initialize
EXTRN	?AuDrvMngrInitialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z:PROC ; AuDrvMngrInitialize
EXTRN	?AuInitializeSerial@@YAXXZ:PROC			; AuInitializeSerial
EXTRN	?AuSoundInitialize@@YAXXZ:PROC			; AuSoundInitialize
EXTRN	?AuSoundOutputStart@@YAXXZ:PROC			; AuSoundOutputStart
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
	DD	imagerel $LN5+297
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

; 99   : void _AuMain (KERNEL_BOOT_INFO *info) {

$LN5:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 100  : 	debug = info->printf_gui;

	mov	rax, QWORD PTR info$[rsp]
	mov	rax, QWORD PTR [rax+106]
	mov	QWORD PTR ?debug@@3P6AXPEBDZZEA, rax	; debug

; 101  : 	//! Initialize the memory mappings
; 102  : 	AuPmmngrInit (info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?AuPmmngrInit@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; AuPmmngrInit

; 103  : 	AuPagingInit();

	call	?AuPagingInit@@YAXXZ			; AuPagingInit

; 104  : 	AuHeapInitialize();

	call	?AuHeapInitialize@@YAXXZ		; AuHeapInitialize

; 105  : 
; 106  : 	AuInitializeShMem();

	call	?AuInitializeShMem@@YAXXZ		; AuInitializeShMem

; 107  : 	AuHalInitialize();

	call	?AuHalInitialize@@YAXXZ			; AuHalInitialize

; 108  : 
; 109  : 	AuInitializeSerial();

	call	?AuInitializeSerial@@YAXXZ		; AuInitializeSerial

; 110  : 	AuInitializeBasicAcpi (info->acpi_table_pointer);

	mov	rax, QWORD PTR info$[rsp]
	mov	rcx, QWORD PTR [rax+82]
	call	?AuInitializeBasicAcpi@@YAXPEAX@Z	; AuInitializeBasicAcpi

; 111  : 	AuSharedDeviceInit();

	call	?AuSharedDeviceInit@@YAXXZ		; AuSharedDeviceInit

; 112  : 	ahci_initialize();

	call	?ahci_initialize@@YAXXZ			; ahci_initialize

; 113  : 	AuVFSInit();

	call	?AuVFSInit@@YAXXZ			; AuVFSInit

; 114  : 	
; 115  : 	AuInitializeScreen(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?AuInitializeScreen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; AuInitializeScreen

; 116  : 	AuConsoleInitialize(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?AuConsoleInitialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; AuConsoleInitialize

; 117  : 	AuSoundInitialize();

	call	?AuSoundInitialize@@YAXXZ		; AuSoundInitialize

; 118  : 	AuInitializeRTC(); 

	call	?AuInitializeRTC@@YAXXZ			; AuInitializeRTC

; 119  : 
; 120  : 	AuInitializeMouse();

	call	?AuInitializeMouse@@YAXXZ		; AuInitializeMouse

; 121  : 	AuNetInitialize();

	call	?AuNetInitialize@@YAXXZ			; AuNetInitialize

; 122  : 	
; 123  : 	/***************************************************
; 124  : 	 * PHASE - 2
; 125  : 	 ***************************************************
; 126  : 	 */
; 127  : 
; 128  : 
; 129  : 	//================================================
; 130  : 	//! Initialize the scheduler here
; 131  : 	//!===============================================
; 132  : 	AuInitializeScheduler();

	call	?AuInitializeScheduler@@YAXXZ		; AuInitializeScheduler

; 133  : 
; 134  : 	//Here we initialise all drivers stuffs
; 135  : 	/* Clear interrupts as scheduler will enable it */
; 136  : 	x64_cli();

	call	x64_cli

; 137  : 	AuDrvMngrInitialize(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?AuDrvMngrInitialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; AuDrvMngrInitialize

; 138  : 	
; 139  : 	// Load system known libraries for usermode processes
; 140  : 	AuSysLibInitialize();

	call	?AuSysLibInitialize@@YAXXZ		; AuSysLibInitialize

; 141  : 
; 142  : 
; 143  : 	AuKeyboardInitialize();

	call	?AuKeyboardInitialize@@YAXXZ		; AuKeyboardInitialize

; 144  : 	AuPointDevInitialize();

	call	?AuPointDevInitialize@@YAXXZ		; AuPointDevInitialize

; 145  : 	
; 146  : 	// Initialize main ipc manager
; 147  : 	pri_loop_init();

	call	?pri_loop_init@@YAXXZ			; pri_loop_init

; 148  : 
; 149  : 	// Initialize the process list
; 150  : 	process_list_initialize();

	call	?process_list_initialize@@YAXXZ		; process_list_initialize

; 151  : 	ttype_init();

	call	?ttype_init@@YAXXZ			; ttype_init

; 152  : 
; 153  : 	/*Initialize other processor */
; 154  : 	AuInitializeCpu(AuGetNumCPU());	

	call	?AuGetNumCPU@@YAEXZ			; AuGetNumCPU
	movzx	ecx, al
	call	?AuInitializeCpu@@YAXE@Z		; AuInitializeCpu

; 155  : 
; 156  : 	/*Clear the lower half for user space */
; 157  : 	AuPagingClearLow();

	call	?AuPagingClearLow@@YAXXZ		; AuPagingClearLow

; 158  : 
; 159  : 	AuSoundOutputStart();

	call	?AuSoundOutputStart@@YAXXZ		; AuSoundOutputStart

; 160  : 	
; 161  : #ifdef ARCH_X64
; 162  : 
; 163  : 	printf ("Scheduler Initialized\n");

	lea	rcx, OFFSET FLAT:$SG5541
	call	printf

; 164  : 	int au_status = 0;

	mov	DWORD PTR au_status$[rsp], 0

; 165  : 
; 166  : 	/* start the init process here */
; 167  : 	au_status = AuCreateProcess ("/init.exe","shell");

	lea	rdx, OFFSET FLAT:$SG5543
	lea	rcx, OFFSET FLAT:$SG5544
	call	?AuCreateProcess@@YAHPEBDPEAD@Z		; AuCreateProcess
	mov	DWORD PTR au_status$[rsp], eax

; 168  : 
; 169  : 	/* start the compositing window manager at id 3 */
; 170  : 	au_status = AuCreateProcess ("/priwm.exe","priwm");

	lea	rdx, OFFSET FLAT:$SG5545
	lea	rcx, OFFSET FLAT:$SG5546
	call	?AuCreateProcess@@YAHPEBDPEAD@Z		; AuCreateProcess
	mov	DWORD PTR au_status$[rsp], eax

; 171  : 
; 172  : 	//! Here start the scheduler (multitasking engine)
; 173  : 	
; 174  : 	AuSchedulerStart();

	call	?AuSchedulerStart@@YAXXZ		; AuSchedulerStart
$LN2@AuMain:

; 175  : #endif
; 176  : 
; 177  : 	//! Loop forever
; 178  : 	while(1) {

	xor	eax, eax
	cmp	eax, 1
	je	SHORT $LN1@AuMain

; 179  : 		//!looping looping
; 180  : 		x64_cli();

	call	x64_cli

; 181  : 		x64_hlt();

	call	x64_hlt

; 182  : 	}

	jmp	SHORT $LN2@AuMain
$LN1@AuMain:

; 183  : }

	add	rsp, 56					; 00000038H
	ret	0
?_AuMain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ENDP		; _AuMain
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
text$ = 48
?debug_print@@YAXPEBDZZ PROC				; debug_print

; 91   : void debug_print (const char* text, ...) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+32], r9
	sub	rsp, 40					; 00000028H

; 92   : 	debug(text);

	mov	rcx, QWORD PTR text$[rsp]
	call	QWORD PTR ?debug@@3P6AXPEBDZZEA		; debug

; 93   : }

	add	rsp, 40					; 00000028H
	ret	0
?debug_print@@YAXPEBDZZ ENDP				; debug_print
_TEXT	ENDS
END
