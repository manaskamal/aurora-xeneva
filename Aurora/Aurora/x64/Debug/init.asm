; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	_fltused
CONST	SEGMENT
$SG7574	DB	'Multitasking started', 0aH, 00H
	ORG $+2
$SG7588	DB	'/', 00H
	ORG $+6
$SG7591	DB	'/start.wav', 00H
	ORG $+1
$SG7594	DB	'shell', 00H
	ORG $+6
$SG7595	DB	'/xshell.exe', 00H
$SG7596	DB	'quince', 00H
	ORG $+5
$SG7597	DB	'/quince.exe', 00H
	ORG $+4
$SG7599	DB	'procmngr', 00H
	ORG $+3
$SG7600	DB	'dwm4', 00H
	ORG $+7
$SG7601	DB	'/dwm2.exe', 00H
	ORG $+2
$SG7602	DB	'cnsl', 00H
	ORG $+7
$SG7603	DB	'/cnsl.exe', 00H
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
EXTRN	?hal_x86_64_setup_int@@YAXXZ:PROC		; hal_x86_64_setup_int
EXTRN	?hal_init@@YAXXZ:PROC				; hal_init
EXTRN	?pmmngr_init@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z:PROC ; pmmngr_init
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	?vmmngr_x86_64_init@@YAXXZ:PROC			; vmmngr_x86_64_init
EXTRN	?map_page@@YA_N_K0E@Z:PROC			; map_page
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
EXTRN	?vfs_finddir@@YAPEAU_vfs_node_@@PEAD@Z:PROC	; vfs_finddir
EXTRN	?openfs@@YA?AU_vfs_node_@@PEAU1@PEAD@Z:PROC	; openfs
EXTRN	?readfs@@YAXPEAU_vfs_node_@@0PEAEI@Z:PROC	; readfs
EXTRN	?stream_init@@YAXXZ:PROC			; stream_init
EXTRN	?initialize_scheduler@@YAXXZ:PROC		; initialize_scheduler
EXTRN	?scheduler_start@@YAXXZ:PROC			; scheduler_start
EXTRN	?create_kthread@@YAPEAU_thread_@@P6AXXZ_K1QEADE@Z:PROC ; create_kthread
EXTRN	?message_init@@YAXXZ:PROC			; message_init
EXTRN	?dwm_ipc_init@@YAXXZ:PROC			; dwm_ipc_init
EXTRN	?initialize_screen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z:PROC ; initialize_screen
EXTRN	?screen_set_configuration@@YAXII@Z:PROC		; screen_set_configuration
EXTRN	?create_process@@YAXPEBDPEAD@Z:PROC		; create_process
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
$pdata$?test_thread2@@YAXXZ DD imagerel $LN5
	DD	imagerel $LN5+30
	DD	imagerel $unwind$?test_thread2@@YAXXZ
$pdata$?_kmain@@YAXXZ DD imagerel $LN8
	DD	imagerel $LN8+573
	DD	imagerel $unwind$?_kmain@@YAXXZ
pdata	ENDS
xdata	SEGMENT
$unwind$??2@YAPEAX_K@Z DD 010901H
	DD	04209H
$unwind$??3@YAXPEAX@Z DD 010901H
	DD	04209H
$unwind$??_U@YAPEAX_K@Z DD 010901H
	DD	04209H
$unwind$?test_thread2@@YAXXZ DD 010401H
	DD	04204H
$unwind$?_kmain@@YAXXZ DD 040a01H
	DD	035010aH
	DD	060027003H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
i$1 = 48
info$ = 56
node$ = 64
buffer2$ = 72
tv82 = 80
tv136 = 88
file$ = 96
$T2 = 208
$T3 = 312
?_kmain@@YAXXZ PROC					; _kmain

; 127  : void _kmain () {

$LN8:
	push	rsi
	push	rdi
	sub	rsp, 424				; 000001a8H

; 128  : 	KERNEL_BOOT_INFO *info = (KERNEL_BOOT_INFO*)0xFFFFE00000000000;

	mov	rax, -35184372088832			; ffffe00000000000H
	mov	QWORD PTR info$[rsp], rax

; 129  : 
; 130  : 	
; 131  : 	//! Initialize the memory mappings
; 132  : 	pmmngr_init (info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?pmmngr_init@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; pmmngr_init

; 133  : 	vmmngr_x86_64_init(); 

	call	?vmmngr_x86_64_init@@YAXXZ		; vmmngr_x86_64_init

; 134  : 	hal_init();

	call	?hal_init@@YAXXZ			; hal_init

; 135  : 	hal_x86_64_setup_int();	

	call	?hal_x86_64_setup_int@@YAXXZ		; hal_x86_64_setup_int

; 136  : 
; 137  :     mm_init(info); 

	mov	rcx, QWORD PTR info$[rsp]
	call	?mm_init@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z	; mm_init

; 138  : 	initialize_serial();

	call	?initialize_serial@@YAXXZ		; initialize_serial

; 139  : 
; 140  : 	ata_initialize();

	call	?ata_initialize@@YAXXZ			; ata_initialize

; 141  : 	vfs_init();

	call	?vfs_init@@YAXXZ			; vfs_init

; 142  : 	initialize_screen(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?initialize_screen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; initialize_screen

; 143  : 	console_initialize(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?console_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; console_initialize

; 144  : 	
; 145  : 	screen_set_configuration(info->X_Resolution,info->Y_Resolution);

	mov	rax, QWORD PTR info$[rsp]
	movzx	eax, WORD PTR [rax+70]
	mov	rcx, QWORD PTR info$[rsp]
	movzx	ecx, WORD PTR [rcx+68]
	mov	edx, eax
	call	?screen_set_configuration@@YAXII@Z	; screen_set_configuration

; 146  : 	initialize_rtc(); 

	call	?initialize_rtc@@YAXXZ			; initialize_rtc

; 147  : 
; 148  : 	initialize_acpi (info->acpi_table_pointer);

	mov	rax, QWORD PTR info$[rsp]
	mov	rcx, QWORD PTR [rax+90]
	call	?initialize_acpi@@YAXPEAX@Z		; initialize_acpi

; 149  : 	
; 150  : 	//!Initialize kernel runtime drivers	
; 151  : 	kybrd_init();

	call	?kybrd_init@@YAXXZ			; kybrd_init

; 152  : 	initialize_mouse();

	call	?initialize_mouse@@YAXXZ		; initialize_mouse

; 153  : 	
; 154  : 	for (int i = 0; i < 2*1024*1024/4096; i++)

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN5@kmain
$LN4@kmain:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN5@kmain:
	cmp	DWORD PTR i$1[rsp], 512			; 00000200H
	jge	SHORT $LN3@kmain

; 155  : 		map_page((uint64_t)pmmngr_alloc(),0xFFFFF00000000000 + i * 4096, 0);

	mov	eax, DWORD PTR i$1[rsp]
	imul	eax, 4096				; 00001000H
	cdqe
	mov	rcx, 17592186044416			; 0000100000000000H
	sub	rax, rcx
	mov	QWORD PTR tv82[rsp], rax
	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	xor	r8d, r8d
	mov	rcx, QWORD PTR tv82[rsp]
	mov	rdx, rcx
	mov	rcx, rax
	call	?map_page@@YA_N_K0E@Z			; map_page
	jmp	SHORT $LN4@kmain
$LN3@kmain:

; 156  : 
; 157  : 	vfs_node_t *node = vfs_finddir("/");

	lea	rcx, OFFSET FLAT:$SG7588
	call	?vfs_finddir@@YAPEAU_vfs_node_@@PEAD@Z	; vfs_finddir
	mov	QWORD PTR node$[rsp], rax

; 158  : 	vfs_node_t file = openfs (node, "/start.wav");

	lea	r8, OFFSET FLAT:$SG7591
	mov	rdx, QWORD PTR node$[rsp]
	lea	rcx, QWORD PTR $T3[rsp]
	call	?openfs@@YA?AU_vfs_node_@@PEAU1@PEAD@Z	; openfs
	lea	rcx, QWORD PTR $T2[rsp]
	mov	rdi, rcx
	mov	rsi, rax
	mov	ecx, 104				; 00000068H
	rep movsb
	lea	rax, QWORD PTR file$[rsp]
	lea	rcx, QWORD PTR $T2[rsp]
	mov	rdi, rax
	mov	rsi, rcx
	mov	ecx, 104				; 00000068H
	rep movsb

; 159  : 	unsigned char* buffer2 = (unsigned char*)0xFFFFF00000000000;

	mov	rax, -17592186044416			; fffff00000000000H
	mov	QWORD PTR buffer2$[rsp], rax

; 160  : 
; 161  : 	readfs (node,&file,buffer2,file.size);

	mov	r9d, DWORD PTR file$[rsp+32]
	mov	r8, QWORD PTR buffer2$[rsp]
	lea	rdx, QWORD PTR file$[rsp]
	mov	rcx, QWORD PTR node$[rsp]
	call	?readfs@@YAXPEAU_vfs_node_@@0PEAEI@Z	; readfs

; 162  : 
; 163  : 
; 164  : 	message_init ();

	call	?message_init@@YAXXZ			; message_init

; 165  : 	dwm_ipc_init();

	call	?dwm_ipc_init@@YAXXZ			; dwm_ipc_init

; 166  : 	stream_init ();

	call	?stream_init@@YAXXZ			; stream_init

; 167  : 	driver_mngr_initialize(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?driver_mngr_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; driver_mngr_initialize

; 168  : 	hda_initialize(); 

	call	?hda_initialize@@YAXXZ			; hda_initialize

; 169  : 
; 170  : 	e1000_initialize();   //<< receiver not working

	call	?e1000_initialize@@YAXXZ		; e1000_initialize

; 171  : 	//svga_init();
; 172  : #ifdef ARCH_X64
; 173  : 	//================================================
; 174  : 	//! Initialize the scheduler here
; 175  : 	//!===============================================
; 176  : 	initialize_scheduler();

	call	?initialize_scheduler@@YAXXZ		; initialize_scheduler

; 177  : 	create_process ("/xshell.exe","shell");

	lea	rdx, OFFSET FLAT:$SG7594
	lea	rcx, OFFSET FLAT:$SG7595
	call	?create_process@@YAXPEBDPEAD@Z		; create_process

; 178  : 
; 179  : 	//! Quince -- The Compositing window manager for Aurora kernel
; 180  : 	//! always put quince in thread id -- > 2
; 181  : 	create_process ("/quince.exe","quince");

	lea	rdx, OFFSET FLAT:$SG7596
	lea	rcx, OFFSET FLAT:$SG7597
	call	?create_process@@YAXPEBDPEAD@Z		; create_process

; 182  : 
; 183  : 	/**=====================================================
; 184  : 	 ** Kernel threads handle some specific callbacks like
; 185  : 	 ** procmngr handles process creation and termination
; 186  : 	 **=====================================================
; 187  : 	 */
; 188  : 	create_kthread (procmngr_start,(uint64_t)pmmngr_alloc() + 4096,x64_read_cr3(),"procmngr",0);

	call	x64_read_cr3
	mov	QWORD PTR tv136[rsp], rax
	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	add	rax, 4096				; 00001000H
	mov	BYTE PTR [rsp+32], 0
	lea	r9, OFFSET FLAT:$SG7599
	mov	rcx, QWORD PTR tv136[rsp]
	mov	r8, rcx
	mov	rdx, rax
	lea	rcx, OFFSET FLAT:?procmngr_start@@YAXXZ	; procmngr_start
	call	?create_kthread@@YAPEAU_thread_@@P6AXXZ_K1QEADE@Z ; create_kthread

; 189  : 	//! Misc programs goes here
; 190  : 	create_process ("/dwm2.exe", "dwm4");

	lea	rdx, OFFSET FLAT:$SG7600
	lea	rcx, OFFSET FLAT:$SG7601
	call	?create_process@@YAXPEBDPEAD@Z		; create_process

; 191  : 	create_process ("/cnsl.exe", "cnsl");

	lea	rdx, OFFSET FLAT:$SG7602
	lea	rcx, OFFSET FLAT:$SG7603
	call	?create_process@@YAXPEBDPEAD@Z		; create_process

; 192  : 	//! Here start the scheduler (multitasking engine)
; 193  : 	scheduler_start();

	call	?scheduler_start@@YAXXZ			; scheduler_start
$LN2@kmain:

; 194  : #endif
; 195  : 
; 196  : 	//! Loop forever
; 197  : 	while(1) {

	xor	eax, eax
	cmp	eax, 1
	je	SHORT $LN1@kmain

; 198  : 		//!looping looping
; 199  : 		x64_cli();

	call	x64_cli

; 200  : 		x64_hlt();

	call	x64_hlt

; 201  : 	}

	jmp	SHORT $LN2@kmain
$LN1@kmain:

; 202  : }

	add	rsp, 424				; 000001a8H
	pop	rdi
	pop	rsi
	ret	0
?_kmain@@YAXXZ ENDP					; _kmain
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
?test_thread2@@YAXXZ PROC				; test_thread2

; 111  : void test_thread2 () {

$LN5:
	sub	rsp, 40					; 00000028H

; 112  : 	printf ("Multitasking started\n");

	lea	rcx, OFFSET FLAT:$SG7574
	call	?printf@@YAXPEBDZZ			; printf
$LN2@test_threa:

; 113  : 	while(1) {

	xor	eax, eax
	cmp	eax, 1
	je	SHORT $LN1@test_threa

; 114  : 		//printf ("Multitasking\n");
; 115  : 	}

	jmp	SHORT $LN2@test_threa
$LN1@test_threa:

; 116  : }

	add	rsp, 40					; 00000028H
	ret	0
?test_thread2@@YAXXZ ENDP				; test_thread2
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
size$ = 48
??_U@YAPEAX_K@Z PROC					; operator new[]

; 101  : void* __cdecl operator new[] (size_t size) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 102  : 	return malloc(size);

	mov	ecx, DWORD PTR size$[rsp]
	call	?malloc@@YAPEAXI@Z			; malloc

; 103  : }

	add	rsp, 40					; 00000028H
	ret	0
??_U@YAPEAX_K@Z ENDP					; operator new[]
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
p$ = 48
??3@YAXPEAX@Z PROC					; operator delete

; 105  : void __cdecl operator delete (void* p) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 106  : 	mfree(p);

	mov	rcx, QWORD PTR p$[rsp]
	call	?mfree@@YAXPEAX@Z			; mfree

; 107  : }

	add	rsp, 40					; 00000028H
	ret	0
??3@YAXPEAX@Z ENDP					; operator delete
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
size$ = 48
??2@YAPEAX_K@Z PROC					; operator new

; 97   : void* __cdecl ::operator new(size_t size) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 98   : 	return malloc(size);

	mov	ecx, DWORD PTR size$[rsp]
	call	?malloc@@YAPEAXI@Z			; malloc

; 99   : }

	add	rsp, 40					; 00000028H
	ret	0
??2@YAPEAX_K@Z ENDP					; operator new
_TEXT	ENDS
END
