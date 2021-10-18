; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	_fltused
_DATA	SEGMENT
_fltused DD	01H
_DATA	ENDS
CONST	SEGMENT
$SG8108	DB	'Timer fired', 0aH, 00H
	ORG $+3
$SG8136	DB	'shell', 00H
	ORG $+2
$SG8137	DB	'/xshell.exe', 00H
$SG8138	DB	'quince', 00H
	ORG $+1
$SG8142	DB	'tsk', 00H
$SG8139	DB	'/quince.exe', 00H
	ORG $+4
$SG8141	DB	'procmngr', 00H
	ORG $+7
$SG8143	DB	'/autask.exe', 00H
$SG8144	DB	'cnsl', 00H
	ORG $+7
$SG8145	DB	'/cnsl.exe', 00H
	ORG $+2
$SG8146	DB	'dwm4', 00H
	ORG $+7
$SG8147	DB	'/dwm2.exe', 00H
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
EXTRN	?vfs_init@@YAXXZ:PROC				; vfs_init
EXTRN	?initialize_scheduler@@YAXXZ:PROC		; initialize_scheduler
EXTRN	?scheduler_start@@YAXXZ:PROC			; scheduler_start
EXTRN	?create_kthread@@YAPEAU_thread_@@P6AXXZ_K1QEADE@Z:PROC ; create_kthread
EXTRN	?message_init@@YAXXZ:PROC			; message_init
EXTRN	?dwm_ipc_init@@YAXXZ:PROC			; dwm_ipc_init
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
	DD	imagerel $LN5+332
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

; 128  : void _kmain (KERNEL_BOOT_INFO *info) {

$LN5:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 129  : 	hal_init ();

	call	?hal_init@@YAXXZ			; hal_init

; 130  : 	pmmngr_init (info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?pmmngr_init@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; pmmngr_init

; 131  : 	mm_init(); 

	call	?mm_init@@YAXXZ				; mm_init

; 132  : 	initialize_serial();

	call	?initialize_serial@@YAXXZ		; initialize_serial

; 133  : 	console_initialize(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?console_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; console_initialize

; 134  : 	//!Initialize kernel runtime drivers	
; 135  : 	kybrd_init();

	call	?kybrd_init@@YAXXZ			; kybrd_init

; 136  : 	initialize_acpi (info->acpi_table_pointer);

	mov	rax, QWORD PTR info$[rsp]
	mov	rcx, QWORD PTR [rax+66]
	call	?initialize_acpi@@YAXPEAX@Z		; initialize_acpi

; 137  : 	initialize_rtc();  

	call	?initialize_rtc@@YAXXZ			; initialize_rtc

; 138  : 	hda_initialize();

	call	?hda_initialize@@YAXXZ			; hda_initialize

; 139  : 	e1000_initialize();  //<< receiver not working

	call	?e1000_initialize@@YAXXZ		; e1000_initialize

; 140  : 
; 141  : 	
; 142  :     ata_initialize();

	call	?ata_initialize@@YAXXZ			; ata_initialize

; 143  : 	initialize_gpt();

	call	?initialize_gpt@@YAXXZ			; initialize_gpt

; 144  : 	//initialize_vfs();
; 145  : 	vfs_init();

	call	?vfs_init@@YAXXZ			; vfs_init

; 146  : 
; 147  : 	initialize_screen(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?initialize_screen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; initialize_screen

; 148  : 	svga_init (); 

	call	?svga_init@@YAXXZ			; svga_init

; 149  : 	initialize_mouse();

	call	?initialize_mouse@@YAXXZ		; initialize_mouse

; 150  :     
; 151  : 	message_init ();

	call	?message_init@@YAXXZ			; message_init

; 152  : 	dwm_ipc_init();

	call	?dwm_ipc_init@@YAXXZ			; dwm_ipc_init

; 153  : 
; 154  : 	driver_mngr_initialize(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?driver_mngr_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; driver_mngr_initialize

; 155  : 
; 156  : #ifdef ARCH_X64
; 157  : 
; 158  : 	//================================================
; 159  : 	//! Initialize the scheduler here
; 160  : 	//!===============================================
; 161  : 	initialize_scheduler();

	call	?initialize_scheduler@@YAXXZ		; initialize_scheduler

; 162  : 	create_process ("/xshell.exe","shell",0, NULL);

	xor	r9d, r9d
	xor	r8d, r8d
	lea	rdx, OFFSET FLAT:$SG8136
	lea	rcx, OFFSET FLAT:$SG8137
	call	?create_process@@YAXPEBDPEADE1@Z	; create_process

; 163  : 	//! Quince -- The Compositing window manager for Aurora kernel
; 164  : 	//! always put quince in thread id -- > 2
; 165  : 	create_process ("/quince.exe","quince",0, NULL);

	xor	r9d, r9d
	xor	r8d, r8d
	lea	rdx, OFFSET FLAT:$SG8138
	lea	rcx, OFFSET FLAT:$SG8139
	call	?create_process@@YAXPEBDPEADE1@Z	; create_process

; 166  : 
; 167  : 	/**=====================================================
; 168  : 	 ** Kernel threads handle some specific callbacks like
; 169  : 	 ** procmngr handles process creation and termination
; 170  : 	 **=====================================================
; 171  : 	 */
; 172  : 	create_kthread (procmngr_start,(uint64_t)pmmngr_alloc(),x64_read_cr3(),"procmngr",0);

	call	x64_read_cr3
	mov	QWORD PTR tv81[rsp], rax
	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	BYTE PTR [rsp+32], 0
	lea	r9, OFFSET FLAT:$SG8141
	mov	rcx, QWORD PTR tv81[rsp]
	mov	r8, rcx
	mov	rdx, rax
	lea	rcx, OFFSET FLAT:?procmngr_start@@YAXXZ	; procmngr_start
	call	?create_kthread@@YAPEAU_thread_@@P6AXXZ_K1QEADE@Z ; create_kthread

; 173  : 
; 174  : 	create_process ("/autask.exe", "tsk", 0, NULL);

	xor	r9d, r9d
	xor	r8d, r8d
	lea	rdx, OFFSET FLAT:$SG8142
	lea	rcx, OFFSET FLAT:$SG8143
	call	?create_process@@YAXPEBDPEADE1@Z	; create_process

; 175  : 	//! Misc programs goes here
; 176  : 	create_process ("/cnsl.exe", "cnsl", 0, NULL);

	xor	r9d, r9d
	xor	r8d, r8d
	lea	rdx, OFFSET FLAT:$SG8144
	lea	rcx, OFFSET FLAT:$SG8145
	call	?create_process@@YAXPEBDPEADE1@Z	; create_process

; 177  : 	create_process ("/dwm2.exe", "dwm4", 0, NULL);

	xor	r9d, r9d
	xor	r8d, r8d
	lea	rdx, OFFSET FLAT:$SG8146
	lea	rcx, OFFSET FLAT:$SG8147
	call	?create_process@@YAXPEBDPEADE1@Z	; create_process

; 178  : 
; 179  : 	//! Here start the scheduler (multitasking engine)
; 180  : 	scheduler_start();

	call	?scheduler_start@@YAXXZ			; scheduler_start
$LN2@kmain:

; 181  : #endif
; 182  : 
; 183  : 	//! Loop forever
; 184  : 	while(1) {

	xor	eax, eax
	cmp	eax, 1
	je	SHORT $LN1@kmain

; 185  : 		//!looping looping
; 186  : 	}

	jmp	SHORT $LN2@kmain
$LN1@kmain:

; 187  : }

	add	rsp, 72					; 00000048H
	ret	0
?_kmain@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ENDP		; _kmain
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
?dummy_thread_2@@YAXXZ PROC				; dummy_thread_2

; 115  : void dummy_thread_2 () {

	npad	2
$LN2@dummy_thre:

; 116  : 	while(1) {

	xor	eax, eax
	cmp	eax, 1
	je	SHORT $LN1@dummy_thre

; 117  : 	}

	jmp	SHORT $LN2@dummy_thre
$LN1@dummy_thre:

; 118  : }

	fatret	0
?dummy_thread_2@@YAXXZ ENDP				; dummy_thread_2
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
size$ = 48
??_U@YAPEAX_K@Z PROC					; operator new[]

; 107  : void* __cdecl operator new[] (size_t size) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 108  : 	return malloc(size);

	mov	ecx, DWORD PTR size$[rsp]
	call	?malloc@@YAPEAXI@Z			; malloc

; 109  : }

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

; 88   : void timer_callback (size_t v, void* p) {

$LN3:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 89   : 	printf ("Timer fired\n");

	lea	rcx, OFFSET FLAT:$SG8108
	call	?printf@@YAXPEBDZZ			; printf

; 90   : 	interrupt_end(2);

	mov	ecx, 2
	call	?interrupt_end@@YAXI@Z			; interrupt_end

; 91   : }

	add	rsp, 40					; 00000028H
	ret	0
?timer_callback@@YAX_KPEAX@Z ENDP			; timer_callback
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
p$ = 48
??3@YAXPEAX@Z PROC					; operator delete

; 111  : void __cdecl operator delete (void* p) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 112  : 	mfree(p);

	mov	rcx, QWORD PTR p$[rsp]
	call	?mfree@@YAXPEAX@Z			; mfree

; 113  : }

	add	rsp, 40					; 00000028H
	ret	0
??3@YAXPEAX@Z ENDP					; operator delete
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
size$ = 48
??2@YAPEAX_K@Z PROC					; operator new

; 103  : void* __cdecl ::operator new(size_t size) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 104  : 	return malloc(size);

	mov	ecx, DWORD PTR size$[rsp]
	call	?malloc@@YAPEAXI@Z			; malloc

; 105  : }

	add	rsp, 40					; 00000028H
	ret	0
??2@YAPEAX_K@Z ENDP					; operator new
_TEXT	ENDS
END
