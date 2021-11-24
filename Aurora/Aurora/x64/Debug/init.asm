; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	_fltused
CONST	SEGMENT
$SG7503	DB	'shell', 00H
	ORG $+2
$SG7504	DB	'/xshell.exe', 00H
$SG7505	DB	'quince', 00H
	ORG $+5
$SG7506	DB	'/quince.exe', 00H
	ORG $+4
$SG7508	DB	'procmngr', 00H
	ORG $+3
$SG7509	DB	'dwm4', 00H
	ORG $+7
$SG7510	DB	'/dwm2.exe', 00H
CONST	ENDS
_DATA	SEGMENT
_fltused DD	01H
_DATA	ENDS
PUBLIC	??2@YAPEAX_K@Z					; operator new
PUBLIC	??3@YAXPEAX@Z					; operator delete
PUBLIC	??_U@YAPEAX_K@Z					; operator new[]
PUBLIC	?_kmain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z		; _kmain
EXTRN	x64_cli:PROC
EXTRN	x64_hlt:PROC
EXTRN	x64_read_cr3:PROC
EXTRN	?hal_init@@YAXXZ:PROC				; hal_init
EXTRN	?pmmngr_init@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z:PROC ; pmmngr_init
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	?mm_init@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z:PROC	; mm_init
EXTRN	?malloc@@YAPEAXI@Z:PROC				; malloc
EXTRN	?mfree@@YAXPEAX@Z:PROC				; mfree
EXTRN	?console_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z:PROC ; console_initialize
EXTRN	?kybrd_init@@YAXXZ:PROC				; kybrd_init
EXTRN	?initialize_mouse@@YAXXZ:PROC			; initialize_mouse
EXTRN	?ata_initialize@@YAXXZ:PROC			; ata_initialize
EXTRN	?svga_init@@YAXXZ:PROC				; svga_init
EXTRN	?hda_initialize@@YAXXZ:PROC			; hda_initialize
EXTRN	?e1000_initialize@@YAXXZ:PROC			; e1000_initialize
EXTRN	?initialize_rtc@@YAXXZ:PROC			; initialize_rtc
EXTRN	?initialize_acpi@@YAXPEAX@Z:PROC		; initialize_acpi
EXTRN	?vfs_init@@YAXXZ:PROC				; vfs_init
EXTRN	?stream_init@@YAXXZ:PROC			; stream_init
EXTRN	?initialize_scheduler@@YAXXZ:PROC		; initialize_scheduler
EXTRN	?scheduler_start@@YAXXZ:PROC			; scheduler_start
EXTRN	?create_kthread@@YAPEAU_thread_@@P6AXXZ_K1QEADE@Z:PROC ; create_kthread
EXTRN	?message_init@@YAXXZ:PROC			; message_init
EXTRN	?dwm_ipc_init@@YAXXZ:PROC			; dwm_ipc_init
EXTRN	?initialize_screen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z:PROC ; initialize_screen
EXTRN	?create_process@@YAXPEBDPEADE1@Z:PROC		; create_process
EXTRN	?driver_mngr_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z:PROC ; driver_mngr_initialize
EXTRN	?procmngr_start@@YAXXZ:PROC			; procmngr_start
EXTRN	?initialize_serial@@YAXXZ:PROC			; initialize_serial
pdata	SEGMENT
$pdata$??2@YAPEAX_K@Z DD imagerel $LN3
	DD	imagerel $LN3+23
	DD	imagerel $unwind$??2@YAPEAX_K@Z
$pdata$??3@YAXPEAX@Z DD imagerel $LN3
	DD	imagerel $LN3+24
	DD	imagerel $unwind$??3@YAXPEAX@Z
$pdata$??_U@YAPEAX_K@Z DD imagerel $LN3
	DD	imagerel $LN3+23
	DD	imagerel $unwind$??_U@YAPEAX_K@Z
$pdata$?_kmain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD imagerel $LN5
	DD	imagerel $LN5+297
	DD	imagerel $unwind$?_kmain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z
pdata	ENDS
xdata	SEGMENT
$unwind$??2@YAPEAX_K@Z DD 010901H
	DD	04209H
$unwind$??3@YAXPEAX@Z DD 010901H
	DD	04209H
$unwind$??_U@YAPEAX_K@Z DD 010901H
	DD	04209H
$unwind$?_kmain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD 010901H
	DD	08209H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
tv82 = 48
info$ = 80
?_kmain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z PROC		; _kmain

; 116  : void _kmain (KERNEL_BOOT_INFO *info) {

$LN5:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 117  : 	hal_init ();

	call	?hal_init@@YAXXZ			; hal_init

; 118  : 	pmmngr_init (info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?pmmngr_init@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; pmmngr_init

; 119  : 	mm_init(info); 

	mov	rcx, QWORD PTR info$[rsp]
	call	?mm_init@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z	; mm_init

; 120  : 	
; 121  : 	initialize_serial();

	call	?initialize_serial@@YAXXZ		; initialize_serial

; 122  : 	console_initialize(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?console_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; console_initialize

; 123  : 	//!Initialize kernel runtime drivers	
; 124  : 	kybrd_init();

	call	?kybrd_init@@YAXXZ			; kybrd_init

; 125  : 	initialize_acpi (info->acpi_table_pointer);

	mov	rax, QWORD PTR info$[rsp]
	mov	rcx, QWORD PTR [rax+66]
	call	?initialize_acpi@@YAXPEAX@Z		; initialize_acpi

; 126  :     ata_initialize();

	call	?ata_initialize@@YAXXZ			; ata_initialize

; 127  : 	//initialize_gpt();
; 128  : 	vfs_init();

	call	?vfs_init@@YAXXZ			; vfs_init

; 129  : 
; 130  : 	initialize_screen(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?initialize_screen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; initialize_screen

; 131  : 	
; 132  : 	initialize_mouse();

	call	?initialize_mouse@@YAXXZ		; initialize_mouse

; 133  : 
; 134  : 	message_init ();

	call	?message_init@@YAXXZ			; message_init

; 135  : 	dwm_ipc_init();

	call	?dwm_ipc_init@@YAXXZ			; dwm_ipc_init

; 136  : 
; 137  : 	stream_init ();

	call	?stream_init@@YAXXZ			; stream_init

; 138  : 	driver_mngr_initialize(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?driver_mngr_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; driver_mngr_initialize

; 139  : 	initialize_rtc();  

	call	?initialize_rtc@@YAXXZ			; initialize_rtc

; 140  : 	hda_initialize();  

	call	?hda_initialize@@YAXXZ			; hda_initialize

; 141  : 	e1000_initialize();   //<< receiver not working

	call	?e1000_initialize@@YAXXZ		; e1000_initialize

; 142  : 	svga_init (); 

	call	?svga_init@@YAXXZ			; svga_init

; 143  : #ifdef ARCH_X64
; 144  : 
; 145  : 	//================================================
; 146  : 	//! Initialize the scheduler here
; 147  : 	//!===============================================
; 148  : 	initialize_scheduler();

	call	?initialize_scheduler@@YAXXZ		; initialize_scheduler

; 149  : 	create_process ("/xshell.exe","shell",0, NULL);

	xor	r9d, r9d
	xor	r8d, r8d
	lea	rdx, OFFSET FLAT:$SG7503
	lea	rcx, OFFSET FLAT:$SG7504
	call	?create_process@@YAXPEBDPEADE1@Z	; create_process

; 150  : 	//! Quince -- The Compositing window manager for Aurora kernel
; 151  : 	//! always put quince in thread id -- > 2
; 152  : 	create_process ("/quince.exe","quince",0, NULL);

	xor	r9d, r9d
	xor	r8d, r8d
	lea	rdx, OFFSET FLAT:$SG7505
	lea	rcx, OFFSET FLAT:$SG7506
	call	?create_process@@YAXPEBDPEADE1@Z	; create_process

; 153  : 
; 154  : 	/**=====================================================
; 155  : 	 ** Kernel threads handle some specific callbacks like
; 156  : 	 ** procmngr handles process creation and termination
; 157  : 	 **=====================================================
; 158  : 	 */
; 159  : 	create_kthread (procmngr_start,(uint64_t)pmmngr_alloc(),x64_read_cr3(),"procmngr",0);

	call	x64_read_cr3
	mov	QWORD PTR tv82[rsp], rax
	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	BYTE PTR [rsp+32], 0
	lea	r9, OFFSET FLAT:$SG7508
	mov	rcx, QWORD PTR tv82[rsp]
	mov	r8, rcx
	mov	rdx, rax
	lea	rcx, OFFSET FLAT:?procmngr_start@@YAXXZ	; procmngr_start
	call	?create_kthread@@YAPEAU_thread_@@P6AXXZ_K1QEADE@Z ; create_kthread

; 160  : 
; 161  : 	//! Misc programs goes here
; 162  : 	create_process ("/dwm2.exe", "dwm4", 0, NULL);

	xor	r9d, r9d
	xor	r8d, r8d
	lea	rdx, OFFSET FLAT:$SG7509
	lea	rcx, OFFSET FLAT:$SG7510
	call	?create_process@@YAXPEBDPEADE1@Z	; create_process

; 163  : 	
; 164  : 	//! Here start the scheduler (multitasking engine)
; 165  : 	scheduler_start();

	call	?scheduler_start@@YAXXZ			; scheduler_start
$LN2@kmain:

; 166  : #endif
; 167  : 
; 168  : 	//! Loop forever
; 169  : 	while(1) {

	xor	eax, eax
	cmp	eax, 1
	je	SHORT $LN1@kmain

; 170  : 		//!looping looping
; 171  : 		x64_cli();

	call	x64_cli

; 172  : 		x64_hlt();

	call	x64_hlt

; 173  : 	}

	jmp	SHORT $LN2@kmain
$LN1@kmain:

; 174  : }

	add	rsp, 72					; 00000048H
	ret	0
?_kmain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ENDP		; _kmain
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
size$ = 48
??_U@YAPEAX_K@Z PROC					; operator new[]

; 98   : void* __cdecl operator new[] (size_t size) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 99   : 	return malloc(size);

	mov	ecx, DWORD PTR size$[rsp]
	call	?malloc@@YAPEAXI@Z			; malloc

; 100  : }

	add	rsp, 40					; 00000028H
	ret	0
??_U@YAPEAX_K@Z ENDP					; operator new[]
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
p$ = 48
??3@YAXPEAX@Z PROC					; operator delete

; 102  : void __cdecl operator delete (void* p) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 103  : 	mfree(p);

	mov	rcx, QWORD PTR p$[rsp]
	call	?mfree@@YAXPEAX@Z			; mfree

; 104  : }

	add	rsp, 40					; 00000028H
	ret	0
??3@YAXPEAX@Z ENDP					; operator delete
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
size$ = 48
??2@YAPEAX_K@Z PROC					; operator new

; 94   : void* __cdecl ::operator new(size_t size) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 95   : 	return malloc(size);

	mov	ecx, DWORD PTR size$[rsp]
	call	?malloc@@YAPEAXI@Z			; malloc

; 96   : }

	add	rsp, 40					; 00000028H
	ret	0
??2@YAPEAX_K@Z ENDP					; operator new
_TEXT	ENDS
END
