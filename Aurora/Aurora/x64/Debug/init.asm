; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	_fltused
CONST	SEGMENT
$SG7539	DB	'CR3 -> %x', 0aH, 00H
	ORG $+5
$SG7540	DB	'Total Used RAM -> %d MB / Total RAM -> %d MB', 0aH, 00H
	ORG $+2
$SG7544	DB	'Hello New CR3 switched', 0aH, 00H
$SG7551	DB	'Hello', 00H
CONST	ENDS
_DATA	SEGMENT
_fltused DD	01H
_DATA	ENDS
PUBLIC	??2@YAPEAX_K@Z					; operator new
PUBLIC	??3@YAXPEAX@Z					; operator delete
PUBLIC	??_U@YAPEAX_K@Z					; operator new[]
PUBLIC	?test_thread2@@YAXXZ				; test_thread2
PUBLIC	?_kmain@@YAXXZ					; _kmain
EXTRN	x64_cli:PROC
EXTRN	x64_hlt:PROC
EXTRN	x64_read_cr3:PROC
EXTRN	x64_write_cr3:PROC
EXTRN	?hal_x86_64_setup_int@@YAXXZ:PROC		; hal_x86_64_setup_int
EXTRN	?hal_init@@YAXXZ:PROC				; hal_init
EXTRN	?pmmngr_init@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z:PROC ; pmmngr_init
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	?pmmngr_get_used_ram@@YA_KXZ:PROC		; pmmngr_get_used_ram
EXTRN	?pmmngr_get_total_ram@@YA_KXZ:PROC		; pmmngr_get_total_ram
EXTRN	?vmmngr_x86_64_init@@YAXXZ:PROC			; vmmngr_x86_64_init
EXTRN	?map_page@@YA_N_K0E@Z:PROC			; map_page
EXTRN	?create_user_address_space@@YAPEA_KXZ:PROC	; create_user_address_space
EXTRN	?mm_init@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z:PROC	; mm_init
EXTRN	?malloc@@YAPEAXI@Z:PROC				; malloc
EXTRN	?mfree@@YAXPEAX@Z:PROC				; mfree
EXTRN	?console_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z:PROC ; console_initialize
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
EXTRN	?kybrd_init@@YAXXZ:PROC				; kybrd_init
EXTRN	?initialize_mouse@@YAXXZ:PROC			; initialize_mouse
EXTRN	?ata_initialize@@YAXXZ:PROC			; ata_initialize
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
EXTRN	?driver_mngr_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z:PROC ; driver_mngr_initialize
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
$pdata$?_kmain@@YAXXZ DD imagerel $LN7
	DD	imagerel $LN7+400
	DD	imagerel $unwind$?_kmain@@YAXXZ
pdata	ENDS
xdata	SEGMENT
$unwind$??2@YAPEAX_K@Z DD 010901H
	DD	04209H
$unwind$??3@YAXPEAX@Z DD 010901H
	DD	04209H
$unwind$??_U@YAPEAX_K@Z DD 010901H
	DD	04209H
$unwind$?_kmain@@YAXXZ DD 010401H
	DD	0a204H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
info$ = 48
st$ = 56
tv76 = 64
new_cr3$ = 72
?_kmain@@YAXXZ PROC					; _kmain

; 124  : void _kmain () {

$LN7:
	sub	rsp, 88					; 00000058H

; 125  : 	KERNEL_BOOT_INFO *info = (KERNEL_BOOT_INFO*)0xFFFFE00000000000;

	mov	rax, -35184372088832			; ffffe00000000000H
	mov	QWORD PTR info$[rsp], rax

; 126  : 
; 127  : 	hal_init();

	call	?hal_init@@YAXXZ			; hal_init

; 128  : 	//! Initialize the memory mappings
; 129  : 	pmmngr_init (info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?pmmngr_init@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; pmmngr_init

; 130  : 	vmmngr_x86_64_init();  

	call	?vmmngr_x86_64_init@@YAXXZ		; vmmngr_x86_64_init

; 131  : 	hal_x86_64_setup_int();	

	call	?hal_x86_64_setup_int@@YAXXZ		; hal_x86_64_setup_int

; 132  : 
; 133  :     mm_init(info); 

	mov	rcx, QWORD PTR info$[rsp]
	call	?mm_init@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z	; mm_init

; 134  : 	initialize_serial();

	call	?initialize_serial@@YAXXZ		; initialize_serial

; 135  : 
; 136  : 	ata_initialize();

	call	?ata_initialize@@YAXXZ			; ata_initialize

; 137  : 	vfs_init();

	call	?vfs_init@@YAXXZ			; vfs_init

; 138  : 	initialize_screen(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?initialize_screen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; initialize_screen

; 139  : 	console_initialize(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?console_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; console_initialize

; 140  : 	initialize_rtc(); 

	call	?initialize_rtc@@YAXXZ			; initialize_rtc

; 141  : 
; 142  : 	initialize_acpi (info->acpi_table_pointer);

	mov	rax, QWORD PTR info$[rsp]
	mov	rcx, QWORD PTR [rax+90]
	call	?initialize_acpi@@YAXPEAX@Z		; initialize_acpi

; 143  : 	
; 144  : 	//!Initialize kernel runtime drivers	
; 145  : 	kybrd_init();

	call	?kybrd_init@@YAXXZ			; kybrd_init

; 146  : 	initialize_mouse();

	call	?initialize_mouse@@YAXXZ		; initialize_mouse

; 147  : 
; 148  : 	message_init ();

	call	?message_init@@YAXXZ			; message_init

; 149  : 	dwm_ipc_init();

	call	?dwm_ipc_init@@YAXXZ			; dwm_ipc_init

; 150  :     
; 151  : 	stream_init ();

	call	?stream_init@@YAXXZ			; stream_init

; 152  : 	driver_mngr_initialize(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?driver_mngr_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; driver_mngr_initialize

; 153  : 
; 154  : 	hda_initialize(); 

	call	?hda_initialize@@YAXXZ			; hda_initialize

; 155  : 	e1000_initialize();   //<< receiver not working

	call	?e1000_initialize@@YAXXZ		; e1000_initialize

; 156  : 	//svga_init (); 
; 157  : 	
; 158  : 	printf ("CR3 -> %x\n", x64_read_cr3());

	call	x64_read_cr3
	mov	rdx, rax
	lea	rcx, OFFSET FLAT:$SG7539
	call	?printf@@YAXPEBDZZ			; printf

; 159  : 	printf ("Total Used RAM -> %d MB / Total RAM -> %d MB\n", pmmngr_get_used_ram() / 1024 / 1024, pmmngr_get_total_ram() / 1024 / 1024);

	call	?pmmngr_get_total_ram@@YA_KXZ		; pmmngr_get_total_ram
	xor	edx, edx
	mov	ecx, 1024				; 00000400H
	div	rcx
	xor	edx, edx
	mov	ecx, 1024				; 00000400H
	div	rcx
	mov	QWORD PTR tv76[rsp], rax
	call	?pmmngr_get_used_ram@@YA_KXZ		; pmmngr_get_used_ram
	xor	edx, edx
	mov	ecx, 1024				; 00000400H
	div	rcx
	xor	edx, edx
	mov	ecx, 1024				; 00000400H
	div	rcx
	mov	rcx, QWORD PTR tv76[rsp]
	mov	r8, rcx
	mov	rdx, rax
	lea	rcx, OFFSET FLAT:$SG7540
	call	?printf@@YAXPEBDZZ			; printf

; 160  : 
; 161  : 
; 162  : 	uint64_t *new_cr3 = (uint64_t*)create_user_address_space();

	call	?create_user_address_space@@YAPEA_KXZ	; create_user_address_space
	mov	QWORD PTR new_cr3$[rsp], rax

; 163  : 	x64_write_cr3((size_t)new_cr3);

	mov	rcx, QWORD PTR new_cr3$[rsp]
	call	x64_write_cr3

; 164  : 
; 165  : 	printf ("Hello New CR3 switched\n");

	lea	rcx, OFFSET FLAT:$SG7544
	call	?printf@@YAXPEBDZZ			; printf
$LN4@kmain:

; 166  : 
; 167  : 
; 168  : 	/**
; 169  : 	 * The Kernel's Virtual Memory is re-written
; 170  : 	 * so the scheduler is not ready yet, it needs
; 171  : 	 * to be updated!! and many more new designs are 
; 172  : 	 * coming soon...
; 173  : 	 */
; 174  : 	for(;;);

	jmp	SHORT $LN4@kmain

; 175  : 
; 176  : 	//! DON'T REACH HERE!!!!
; 177  : #ifdef ARCH_X64
; 178  : 	//================================================
; 179  : 	//! Initialize the scheduler here
; 180  : 	//!===============================================
; 181  : 	initialize_scheduler();

	call	?initialize_scheduler@@YAXXZ		; initialize_scheduler

; 182  : 	uint64_t st = 0xFFFFA00000800000;

	mov	rax, -105553107877888			; ffffa00000800000H
	mov	QWORD PTR st$[rsp], rax

; 183  : 	map_page ((uint64_t)pmmngr_alloc(),st,0);

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	xor	r8d, r8d
	mov	rdx, QWORD PTR st$[rsp]
	mov	rcx, rax
	call	?map_page@@YA_N_K0E@Z			; map_page

; 184  : 	create_kthread(test_thread2,st + 0x1000,(size_t)x64_read_cr3, "Hello", 1);

	mov	rax, QWORD PTR st$[rsp]
	add	rax, 4096				; 00001000H
	mov	BYTE PTR [rsp+32], 1
	lea	r9, OFFSET FLAT:$SG7551
	lea	r8, OFFSET FLAT:x64_read_cr3
	mov	rdx, rax
	lea	rcx, OFFSET FLAT:?test_thread2@@YAXXZ	; test_thread2
	call	?create_kthread@@YAPEAU_thread_@@P6AXXZ_K1QEADE@Z ; create_kthread

; 185  : 	//create_process ("/xshell.exe","shell");
; 186  : 	//create_process ("/xshell.exe","shell");
; 187  : 	//create_user_thread (add,(uint64_t)stack,(uint64_t)cr3,"Test",1);
; 188  : 
; 189  : 	//! Quince -- The Compositing window manager for Aurora kernel
; 190  : 	//! always put quince in thread id -- > 2
; 191  : 	//create_process ("/quince.exe","quince",0, NULL);
; 192  : 
; 193  : 	/**=====================================================
; 194  : 	 ** Kernel threads handle some specific callbacks like
; 195  : 	 ** procmngr handles process creation and termination
; 196  : 	 **=====================================================
; 197  : 	 */
; 198  : 	//create_kthread (procmngr_start,(uint64_t)pmmngr_alloc(),x64_read_cr3(),"procmngr",0);
; 199  : 	//! Misc programs goes here
; 200  : 	//create_process ("/dwm2.exe", "dwm4", 0, NULL);
; 201  : 	//! Here start the scheduler (multitasking engine)
; 202  : 	scheduler_start();

	call	?scheduler_start@@YAXXZ			; scheduler_start
$LN2@kmain:

; 203  : #endif
; 204  : 
; 205  : 	//! Loop forever
; 206  : 	while(1) {

	xor	eax, eax
	cmp	eax, 1
	je	SHORT $LN1@kmain

; 207  : 		//!looping looping
; 208  : 		x64_cli();

	call	x64_cli

; 209  : 		x64_hlt();

	call	x64_hlt

; 210  : 	}

	jmp	SHORT $LN2@kmain
$LN1@kmain:

; 211  : }

	add	rsp, 88					; 00000058H
	ret	0
?_kmain@@YAXXZ ENDP					; _kmain
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
?test_thread2@@YAXXZ PROC				; test_thread2

; 110  : void test_thread2 () {

	npad	2
$LN2@test_threa:

; 111  : 	while(1) {

	xor	eax, eax
	cmp	eax, 1
	je	SHORT $LN1@test_threa

; 112  : 		//printf ("Multitasking\n");
; 113  : 	}

	jmp	SHORT $LN2@test_threa
$LN1@test_threa:

; 114  : }

	fatret	0
?test_thread2@@YAXXZ ENDP				; test_thread2
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
size$ = 48
??_U@YAPEAX_K@Z PROC					; operator new[]

; 100  : void* __cdecl operator new[] (size_t size) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 101  : 	return malloc(size);

	mov	ecx, DWORD PTR size$[rsp]
	call	?malloc@@YAPEAXI@Z			; malloc

; 102  : }

	add	rsp, 40					; 00000028H
	ret	0
??_U@YAPEAX_K@Z ENDP					; operator new[]
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
p$ = 48
??3@YAXPEAX@Z PROC					; operator delete

; 104  : void __cdecl operator delete (void* p) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 105  : 	mfree(p);

	mov	rcx, QWORD PTR p$[rsp]
	call	?mfree@@YAXPEAX@Z			; mfree

; 106  : }

	add	rsp, 40					; 00000028H
	ret	0
??3@YAXPEAX@Z ENDP					; operator delete
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
size$ = 48
??2@YAPEAX_K@Z PROC					; operator new

; 96   : void* __cdecl ::operator new(size_t size) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 97   : 	return malloc(size);

	mov	ecx, DWORD PTR size$[rsp]
	call	?malloc@@YAPEAXI@Z			; malloc

; 98   : }

	add	rsp, 40					; 00000028H
	ret	0
??2@YAPEAX_K@Z ENDP					; operator new
_TEXT	ENDS
END
