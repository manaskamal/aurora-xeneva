; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	_fltused
_DATA	SEGMENT
_fltused DD	01H
_DATA	ENDS
CONST	SEGMENT
$SG8129	DB	'Timer fired', 0aH, 00H
	ORG $+3
$SG8157	DB	'shell', 00H
	ORG $+2
$SG8158	DB	'a:xshell.exe', 00H
	ORG $+3
$SG8159	DB	'quince', 00H
	ORG $+1
$SG8160	DB	'a:quince.exe', 00H
	ORG $+3
$SG8162	DB	'procmngr', 00H
	ORG $+3
$SG8163	DB	'dwm3', 00H
	ORG $+7
$SG8164	DB	'a:dwm2.exe', 00H
CONST	ENDS
PUBLIC	??2@YAPEAX_K@Z					; operator new
PUBLIC	??3@YAXPEAX@Z					; operator delete
PUBLIC	?timer_callback@@YAX_KPEAX@Z			; timer_callback
PUBLIC	??_U@YAPEAX_K@Z					; operator new[]
PUBLIC	?dummy_thread_2@@YAXXZ				; dummy_thread_2
PUBLIC	?_kmain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z		; _kmain
EXTRN	x64_read_cr3:PROC
EXTRN	?hal_init@@YAXXZ:PROC				; hal_init
EXTRN	?interrupt_end@@YAXI@Z:PROC			; interrupt_end
EXTRN	?pmmngr_init@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z:PROC ; pmmngr_init
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	?mm_init@@YAXXZ:PROC				; mm_init
EXTRN	?malloc@@YAPEAXI@Z:PROC				; malloc
EXTRN	?mfree@@YAXPEAX@Z:PROC				; mfree
EXTRN	?console_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z:PROC ; console_initialize
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
EXTRN	?kybrd_init@@YAXXZ:PROC				; kybrd_init
EXTRN	?initialize_mouse@@YAXXZ:PROC			; initialize_mouse
EXTRN	?ata_initialize@@YAXXZ:PROC			; ata_initialize
EXTRN	?svga_init@@YAXXZ:PROC				; svga_init
EXTRN	?hda_initialize@@YAXXZ:PROC			; hda_initialize
EXTRN	?e1000_initialize@@YAXXZ:PROC			; e1000_initialize
EXTRN	?initialize_rtc@@YAXXZ:PROC			; initialize_rtc
EXTRN	?initialize_acpi@@YAXPEAX@Z:PROC		; initialize_acpi
EXTRN	?initialize_scheduler@@YAXXZ:PROC		; initialize_scheduler
EXTRN	?scheduler_start@@YAXXZ:PROC			; scheduler_start
EXTRN	?create_kthread@@YAPEAU_thread_@@P6AXXZ_K1QEADE@Z:PROC ; create_kthread
EXTRN	?message_init@@YAXXZ:PROC			; message_init
EXTRN	?dwm_ipc_init@@YAXXZ:PROC			; dwm_ipc_init
EXTRN	?initialize_vfs@@YAXXZ:PROC			; initialize_vfs
EXTRN	?initialize_gpt@@YAXXZ:PROC			; initialize_gpt
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
$pdata$?timer_callback@@YAX_KPEAX@Z DD imagerel $LN3
	DD	imagerel $LN3+41
	DD	imagerel $unwind$?timer_callback@@YAX_KPEAX@Z
$pdata$??_U@YAPEAX_K@Z DD imagerel $LN3
	DD	imagerel $LN3+23
	DD	imagerel $unwind$??_U@YAPEAX_K@Z
$pdata$?_kmain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD imagerel $LN5
	DD	imagerel $LN5+282
	DD	imagerel $unwind$?_kmain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z
pdata	ENDS
xdata	SEGMENT
$unwind$??2@YAPEAX_K@Z DD 010901H
	DD	04209H
$unwind$??3@YAXPEAX@Z DD 010901H
	DD	04209H
$unwind$?timer_callback@@YAX_KPEAX@Z DD 010e01H
	DD	0420eH
$unwind$??_U@YAPEAX_K@Z DD 010901H
	DD	04209H
$unwind$?_kmain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD 010901H
	DD	08209H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
tv81 = 48
info$ = 80
?_kmain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z PROC		; _kmain

; 127  : void _kmain (KERNEL_BOOT_INFO *info) {

$LN5:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 128  : 	hal_init ();

	call	?hal_init@@YAXXZ			; hal_init

; 129  : 	pmmngr_init (info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?pmmngr_init@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; pmmngr_init

; 130  : 	mm_init(); 

	call	?mm_init@@YAXXZ				; mm_init

; 131  : 	initialize_serial();

	call	?initialize_serial@@YAXXZ		; initialize_serial

; 132  : 	console_initialize(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?console_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; console_initialize

; 133  : 	//!Initialize kernel runtime drivers	
; 134  : 	kybrd_init();

	call	?kybrd_init@@YAXXZ			; kybrd_init

; 135  : 	initialize_acpi (info->acpi_table_pointer);

	mov	rax, QWORD PTR info$[rsp]
	mov	rcx, QWORD PTR [rax+66]
	call	?initialize_acpi@@YAXPEAX@Z		; initialize_acpi

; 136  : 	initialize_rtc();  

	call	?initialize_rtc@@YAXXZ			; initialize_rtc

; 137  : 	hda_initialize();

	call	?hda_initialize@@YAXXZ			; hda_initialize

; 138  : 	e1000_initialize();  //<< receiver not working

	call	?e1000_initialize@@YAXXZ		; e1000_initialize

; 139  : 
; 140  : 
; 141  :     ata_initialize();

	call	?ata_initialize@@YAXXZ			; ata_initialize

; 142  : 	initialize_gpt();

	call	?initialize_gpt@@YAXXZ			; initialize_gpt

; 143  : 	initialize_vfs();

	call	?initialize_vfs@@YAXXZ			; initialize_vfs

; 144  : 	initialize_screen(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?initialize_screen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; initialize_screen

; 145  : 	svga_init (); 

	call	?svga_init@@YAXXZ			; svga_init

; 146  : 	initialize_mouse();

	call	?initialize_mouse@@YAXXZ		; initialize_mouse

; 147  : 
; 148  : 	message_init ();

	call	?message_init@@YAXXZ			; message_init

; 149  : 	dwm_ipc_init();

	call	?dwm_ipc_init@@YAXXZ			; dwm_ipc_init

; 150  : 
; 151  : 	driver_mngr_initialize(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?driver_mngr_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; driver_mngr_initialize

; 152  : #ifdef ARCH_X64
; 153  : 
; 154  : 	//================================================
; 155  : 	//! Initialize the scheduler here
; 156  : 	//!===============================================
; 157  : 	initialize_scheduler();

	call	?initialize_scheduler@@YAXXZ		; initialize_scheduler

; 158  : 	create_process ("a:xshell.exe","shell",0, NULL);

	xor	r9d, r9d
	xor	r8d, r8d
	lea	rdx, OFFSET FLAT:$SG8157
	lea	rcx, OFFSET FLAT:$SG8158
	call	?create_process@@YAXPEBDPEADE1@Z	; create_process

; 159  : 
; 160  : 	//! Quince -- The Compositing window manager for Aurora kernel
; 161  : 	//! always put quince in thread id -- > 2
; 162  : 	create_process ("a:quince.exe","quince",0, NULL);

	xor	r9d, r9d
	xor	r8d, r8d
	lea	rdx, OFFSET FLAT:$SG8159
	lea	rcx, OFFSET FLAT:$SG8160
	call	?create_process@@YAXPEBDPEADE1@Z	; create_process

; 163  : 
; 164  : 	/**=====================================================
; 165  : 	 ** Kernel threads handle some specific callbacks like
; 166  : 	 ** procmngr handles process creation and termination
; 167  : 	 **=====================================================
; 168  : 	 */
; 169  : 	create_kthread (procmngr_start,(uint64_t)pmmngr_alloc(),x64_read_cr3(),"procmngr",0);

	call	x64_read_cr3
	mov	QWORD PTR tv81[rsp], rax
	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	BYTE PTR [rsp+32], 0
	lea	r9, OFFSET FLAT:$SG8162
	mov	rcx, QWORD PTR tv81[rsp]
	mov	r8, rcx
	mov	rdx, rax
	lea	rcx, OFFSET FLAT:?procmngr_start@@YAXXZ	; procmngr_start
	call	?create_kthread@@YAPEAU_thread_@@P6AXXZ_K1QEADE@Z ; create_kthread

; 170  : 
; 171  : 	//! Misc programs goes here
; 172  : 	create_process ("a:dwm2.exe", "dwm3", 0, NULL);

	xor	r9d, r9d
	xor	r8d, r8d
	lea	rdx, OFFSET FLAT:$SG8163
	lea	rcx, OFFSET FLAT:$SG8164
	call	?create_process@@YAXPEBDPEADE1@Z	; create_process

; 173  : //	create_process ("a:dwm2.exe", "dwm4", 0, NULL);
; 174  : 
; 175  : 	//! Here start the scheduler (multitasking engine)
; 176  : 	scheduler_start();

	call	?scheduler_start@@YAXXZ			; scheduler_start
$LN2@kmain:

; 177  : #endif
; 178  : 
; 179  : 	//! Loop forever
; 180  : 	while(1) {

	xor	eax, eax
	cmp	eax, 1
	je	SHORT $LN1@kmain

; 181  : 		//!looping looping
; 182  : 	}

	jmp	SHORT $LN2@kmain
$LN1@kmain:

; 183  : }

	add	rsp, 72					; 00000048H
	ret	0
?_kmain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ENDP		; _kmain
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
?dummy_thread_2@@YAXXZ PROC				; dummy_thread_2

; 114  : void dummy_thread_2 () {

	npad	2
$LN2@dummy_thre:

; 115  : 	while(1) {

	xor	eax, eax
	cmp	eax, 1
	je	SHORT $LN1@dummy_thre

; 116  : 	}

	jmp	SHORT $LN2@dummy_thre
$LN1@dummy_thre:

; 117  : }

	fatret	0
?dummy_thread_2@@YAXXZ ENDP				; dummy_thread_2
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
size$ = 48
??_U@YAPEAX_K@Z PROC					; operator new[]

; 106  : void* __cdecl operator new[] (size_t size) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 107  : 	return malloc(size);

	mov	ecx, DWORD PTR size$[rsp]
	call	?malloc@@YAPEAXI@Z			; malloc

; 108  : }

	add	rsp, 40					; 00000028H
	ret	0
??_U@YAPEAX_K@Z ENDP					; operator new[]
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
v$ = 48
p$ = 56
?timer_callback@@YAX_KPEAX@Z PROC			; timer_callback

; 87   : void timer_callback (size_t v, void* p) {

$LN3:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 88   : 	printf ("Timer fired\n");

	lea	rcx, OFFSET FLAT:$SG8129
	call	?printf@@YAXPEBDZZ			; printf

; 89   : 	interrupt_end(2);

	mov	ecx, 2
	call	?interrupt_end@@YAXI@Z			; interrupt_end

; 90   : }

	add	rsp, 40					; 00000028H
	ret	0
?timer_callback@@YAX_KPEAX@Z ENDP			; timer_callback
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
p$ = 48
??3@YAXPEAX@Z PROC					; operator delete

; 110  : void __cdecl operator delete (void* p) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 111  : 	mfree(p);

	mov	rcx, QWORD PTR p$[rsp]
	call	?mfree@@YAXPEAX@Z			; mfree

; 112  : }

	add	rsp, 40					; 00000028H
	ret	0
??3@YAXPEAX@Z ENDP					; operator delete
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
size$ = 48
??2@YAPEAX_K@Z PROC					; operator new

; 102  : void* __cdecl ::operator new(size_t size) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 103  : 	return malloc(size);

	mov	ecx, DWORD PTR size$[rsp]
	call	?malloc@@YAPEAXI@Z			; malloc

; 104  : }

	add	rsp, 40					; 00000028H
	ret	0
??2@YAPEAX_K@Z ENDP					; operator new
_TEXT	ENDS
END
