; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	_fltused
PUBLIC	?ap_address@@3PEAXEA				; ap_address
_BSS	SEGMENT
?ap_address@@3PEAXEA DQ 01H DUP (?)			; ap_address
_BSS	ENDS
CONST	SEGMENT
$SG7674	DB	'/', 00H
	ORG $+6
$SG7679	DB	'/apstart.bin', 00H
	ORG $+3
$SG7680	DB	'AP_Adress setup -> %x', 0aH, 00H
	ORG $+1
$SG7681	DB	'shell', 00H
	ORG $+2
$SG7682	DB	'/xshell.exe', 00H
$SG7683	DB	'priwm', 00H
	ORG $+6
$SG7684	DB	'/priwm.exe', 00H
	ORG $+1
$SG7685	DB	'snake', 00H
	ORG $+6
$SG7686	DB	'/snake.exe', 00H
	ORG $+1
$SG7687	DB	'cnsl', 00H
	ORG $+7
$SG7688	DB	'/dock.exe', 00H
CONST	ENDS
_DATA	SEGMENT
_fltused DD	01H
_DATA	ENDS
PUBLIC	??2@YAPEAX_K@Z					; operator new
PUBLIC	??3@YAXPEAX@Z					; operator delete
PUBLIC	?get_ap_address@@YAPEAXXZ			; get_ap_address
PUBLIC	??_U@YAPEAX_K@Z					; operator new[]
PUBLIC	?_kmain@@YAXXZ					; _kmain
EXTRN	x64_cli:PROC
EXTRN	x64_hlt:PROC
EXTRN	?hal_x86_64_setup_int@@YAXXZ:PROC		; hal_x86_64_setup_int
EXTRN	?hal_x86_64_feature_check@@YAXXZ:PROC		; hal_x86_64_feature_check
EXTRN	?hal_init@@YAXXZ:PROC				; hal_init
EXTRN	?pmmngr_init@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z:PROC ; pmmngr_init
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	?vmmngr_x86_64_init@@YAXXZ:PROC			; vmmngr_x86_64_init
EXTRN	?console_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z:PROC ; console_initialize
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
EXTRN	?kybrd_init@@YAXXZ:PROC				; kybrd_init
EXTRN	?initialize_mouse@@YAXXZ:PROC			; initialize_mouse
EXTRN	?ata_initialize@@YAXXZ:PROC			; ata_initialize
EXTRN	?initialize_kmemory@@YAX_K@Z:PROC		; initialize_kmemory
EXTRN	?malloc@@YAPEAX_K@Z:PROC			; malloc
EXTRN	?free@@YAXPEAX@Z:PROC				; free
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
EXTRN	?message_init@@YAXXZ:PROC			; message_init
EXTRN	?dwm_ipc_init@@YAXXZ:PROC			; dwm_ipc_init
EXTRN	?initialize_screen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z:PROC ; initialize_screen
EXTRN	?screen_set_configuration@@YAXII@Z:PROC		; screen_set_configuration
EXTRN	?create_process@@YAHPEBDPEAD@Z:PROC		; create_process
EXTRN	?driver_mngr_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z:PROC ; driver_mngr_initialize
EXTRN	?initialize_serial@@YAXXZ:PROC			; initialize_serial
EXTRN	?sound_initialize@@YAXXZ:PROC			; sound_initialize
EXTRN	?pri_loop_init@@YAXXZ:PROC			; pri_loop_init
EXTRN	?arp_initialize@@YAXXZ:PROC			; arp_initialize
EXTRN	?arp_broadcast@@YAXXZ:PROC			; arp_broadcast
pdata	SEGMENT
$pdata$??2@YAPEAX_K@Z DD imagerel $LN3
	DD	imagerel $LN3+24
	DD	imagerel $unwind$??2@YAPEAX_K@Z
$pdata$??3@YAXPEAX@Z DD imagerel $LN3
	DD	imagerel $LN3+24
	DD	imagerel $unwind$??3@YAXPEAX@Z
$pdata$??_U@YAPEAX_K@Z DD imagerel $LN3
	DD	imagerel $LN3+24
	DD	imagerel $unwind$??_U@YAPEAX_K@Z
$pdata$?_kmain@@YAXXZ DD imagerel $LN5
	DD	imagerel $LN5+479
	DD	imagerel $unwind$?_kmain@@YAXXZ
pdata	ENDS
xdata	SEGMENT
$unwind$??2@YAPEAX_K@Z DD 010901H
	DD	04209H
$unwind$??3@YAXPEAX@Z DD 010901H
	DD	04209H
$unwind$??_U@YAPEAX_K@Z DD 010901H
	DD	04209H
$unwind$?_kmain@@YAXXZ DD 040a01H
	DD	031010aH
	DD	060027003H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
info$ = 32
ap$ = 40
node$ = 48
apfile$ = 64
$T1 = 176
$T2 = 280
?_kmain@@YAXXZ PROC					; _kmain

; 111  : void _kmain () {

$LN5:
	push	rsi
	push	rdi
	sub	rsp, 392				; 00000188H

; 112  : 	KERNEL_BOOT_INFO *info = (KERNEL_BOOT_INFO*)0xFFFFE00000000000;

	mov	rax, -35184372088832			; ffffe00000000000H
	mov	QWORD PTR info$[rsp], rax

; 113  : 	//! Initialize the memory mappings
; 114  : 	pmmngr_init (info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?pmmngr_init@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; pmmngr_init

; 115  : 	vmmngr_x86_64_init(); 

	call	?vmmngr_x86_64_init@@YAXXZ		; vmmngr_x86_64_init

; 116  : 	hal_init();

	call	?hal_init@@YAXXZ			; hal_init

; 117  : 	hal_x86_64_setup_int();	

	call	?hal_x86_64_setup_int@@YAXXZ		; hal_x86_64_setup_int

; 118  : 	initialize_kmemory(16);

	mov	ecx, 16
	call	?initialize_kmemory@@YAX_K@Z		; initialize_kmemory

; 119  : 
; 120  : 	initialize_serial();

	call	?initialize_serial@@YAXXZ		; initialize_serial

; 121  : 
; 122  : 	ata_initialize();

	call	?ata_initialize@@YAXXZ			; ata_initialize

; 123  : 	vfs_init();

	call	?vfs_init@@YAXXZ			; vfs_init

; 124  : 	initialize_screen(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?initialize_screen@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; initialize_screen

; 125  : 	console_initialize(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?console_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; console_initialize

; 126  : 	
; 127  : 	screen_set_configuration(info->X_Resolution,info->Y_Resolution);

	mov	rax, QWORD PTR info$[rsp]
	movzx	eax, WORD PTR [rax+70]
	mov	rcx, QWORD PTR info$[rsp]
	movzx	ecx, WORD PTR [rcx+68]
	mov	edx, eax
	call	?screen_set_configuration@@YAXII@Z	; screen_set_configuration

; 128  : 	initialize_rtc(); 

	call	?initialize_rtc@@YAXXZ			; initialize_rtc

; 129  : 
; 130  : 	vfs_node_t *node = vfs_finddir("/");

	lea	rcx, OFFSET FLAT:$SG7674
	call	?vfs_finddir@@YAPEAU_vfs_node_@@PEAD@Z	; vfs_finddir
	mov	QWORD PTR node$[rsp], rax

; 131  : 	unsigned char* ap = (unsigned char*)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR ap$[rsp], rax

; 132  : 	vfs_node_t apfile = openfs(node, "/apstart.bin");

	lea	r8, OFFSET FLAT:$SG7679
	mov	rdx, QWORD PTR node$[rsp]
	lea	rcx, QWORD PTR $T2[rsp]
	call	?openfs@@YA?AU_vfs_node_@@PEAU1@PEAD@Z	; openfs
	lea	rcx, QWORD PTR $T1[rsp]
	mov	rdi, rcx
	mov	rsi, rax
	mov	ecx, 104				; 00000068H
	rep movsb
	lea	rax, QWORD PTR apfile$[rsp]
	lea	rcx, QWORD PTR $T1[rsp]
	mov	rdi, rax
	mov	rsi, rcx
	mov	ecx, 104				; 00000068H
	rep movsb

; 133  : 	readfs (node,&apfile,ap,apfile.size);

	mov	r9d, DWORD PTR apfile$[rsp+32]
	mov	r8, QWORD PTR ap$[rsp]
	lea	rdx, QWORD PTR apfile$[rsp]
	mov	rcx, QWORD PTR node$[rsp]
	call	?readfs@@YAXPEAU_vfs_node_@@0PEAEI@Z	; readfs

; 134  : 	ap_address = ap;

	mov	rax, QWORD PTR ap$[rsp]
	mov	QWORD PTR ?ap_address@@3PEAXEA, rax	; ap_address

; 135  : 	printf ("AP_Adress setup -> %x\n", ap_address);

	mov	rdx, QWORD PTR ?ap_address@@3PEAXEA	; ap_address
	lea	rcx, OFFSET FLAT:$SG7680
	call	?printf@@YAXPEBDZZ			; printf

; 136  : 	
; 137  : 
; 138  : 	initialize_acpi (info->acpi_table_pointer);

	mov	rax, QWORD PTR info$[rsp]
	mov	rcx, QWORD PTR [rax+90]
	call	?initialize_acpi@@YAXPEAX@Z		; initialize_acpi

; 139  : 	hal_x86_64_feature_check();

	call	?hal_x86_64_feature_check@@YAXXZ	; hal_x86_64_feature_check

; 140  : 
; 141  : 	//!Initialize kernel runtime drivers	
; 142  : 	kybrd_init();

	call	?kybrd_init@@YAXXZ			; kybrd_init

; 143  : 	initialize_mouse();

	call	?initialize_mouse@@YAXXZ		; initialize_mouse

; 144  : 	
; 145  : 	/*vfs_node_t file = openfs (node, "/start.wav");
; 146  : 
; 147  : 	for (int i = 0; i < file.size/4096; i++) {
; 148  : 		void *p = pmmngr_alloc();
; 149  : 		memset(p, 0, 4096);
; 150  : 		map_page((uint64_t)p,0xFFFFF00000000000 + i * 4096, 0);
; 151  : 	}
; 152  : 	unsigned char* buffer = (unsigned char*)0xFFFFF00000000000;
; 153  : 	unsigned char* buffer2 = (unsigned char*)(buffer + 44);
; 154  : 	readfs (node,&file,buffer2,file.size);*/
; 155  : 
; 156  : 	message_init ();

	call	?message_init@@YAXXZ			; message_init

; 157  : 	dwm_ipc_init();

	call	?dwm_ipc_init@@YAXXZ			; dwm_ipc_init

; 158  : 	stream_init ();

	call	?stream_init@@YAXXZ			; stream_init

; 159  : 	pri_loop_init();

	call	?pri_loop_init@@YAXXZ			; pri_loop_init

; 160  : 	driver_mngr_initialize(info);

	mov	rcx, QWORD PTR info$[rsp]
	call	?driver_mngr_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; driver_mngr_initialize

; 161  : 	hda_initialize(); 

	call	?hda_initialize@@YAXXZ			; hda_initialize

; 162  : 	//hda_audio_add_pcm(buffer2, file.size);
; 163  : 
; 164  : 	e1000_initialize();   //<< receiver not working

	call	?e1000_initialize@@YAXXZ		; e1000_initialize

; 165  : 	arp_initialize();

	call	?arp_initialize@@YAXXZ			; arp_initialize

; 166  : 	arp_broadcast();

	call	?arp_broadcast@@YAXXZ			; arp_broadcast

; 167  : 	//svga_init();
; 168  : 	sound_initialize();

	call	?sound_initialize@@YAXXZ		; sound_initialize

; 169  : 
; 170  : #ifdef ARCH_X64
; 171  : 	//================================================
; 172  : 	//! Initialize the scheduler here
; 173  : 	//!===============================================
; 174  : 	initialize_scheduler();

	call	?initialize_scheduler@@YAXXZ		; initialize_scheduler

; 175  : 
; 176  : 	create_process ("/xshell.exe","shell");

	lea	rdx, OFFSET FLAT:$SG7681
	lea	rcx, OFFSET FLAT:$SG7682
	call	?create_process@@YAHPEBDPEAD@Z		; create_process

; 177  : 	//! Quince -- The Compositing window manager for Aurora kernel
; 178  : 	//! always put quince in thread id -- > 2
; 179  : 	create_process ("/priwm.exe","priwm");

	lea	rdx, OFFSET FLAT:$SG7683
	lea	rcx, OFFSET FLAT:$SG7684
	call	?create_process@@YAHPEBDPEAD@Z		; create_process

; 180  : 
; 181  : 	/**=====================================================
; 182  : 	 ** Kernel threads handle some specific callbacks like
; 183  : 	 ** procmngr handles process creation and termination
; 184  : 	 **=====================================================
; 185  : 	 */
; 186  : 	//! Misc programs goes here
; 187  : 	//create_process ("/dwm2.exe", "dwm4");
; 188  : 	create_process ("/snake.exe", "snake");

	lea	rdx, OFFSET FLAT:$SG7685
	lea	rcx, OFFSET FLAT:$SG7686
	call	?create_process@@YAHPEBDPEAD@Z		; create_process

; 189  : 	create_process ("/dock.exe", "cnsl");

	lea	rdx, OFFSET FLAT:$SG7687
	lea	rcx, OFFSET FLAT:$SG7688
	call	?create_process@@YAHPEBDPEAD@Z		; create_process

; 190  : 	//! Here start the scheduler (multitasking engine)
; 191  : 	
; 192  : 	scheduler_start();

	call	?scheduler_start@@YAXXZ			; scheduler_start
$LN2@kmain:

; 193  : #endif
; 194  : 
; 195  : 	//! Loop forever
; 196  : 	while(1) {

	xor	eax, eax
	cmp	eax, 1
	je	SHORT $LN1@kmain

; 197  : 		//!looping looping
; 198  : 		x64_cli();

	call	x64_cli

; 199  : 		x64_hlt();

	call	x64_hlt

; 200  : 	}

	jmp	SHORT $LN2@kmain
$LN1@kmain:

; 201  : }

	add	rsp, 392				; 00000188H
	pop	rdi
	pop	rsi
	ret	0
?_kmain@@YAXXZ ENDP					; _kmain
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
size$ = 48
??_U@YAPEAX_K@Z PROC					; operator new[]

; 94   : void* __cdecl operator new[] (size_t size) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 95   : 	return malloc(size);

	mov	rcx, QWORD PTR size$[rsp]
	call	?malloc@@YAPEAX_K@Z			; malloc

; 96   : }

	add	rsp, 40					; 00000028H
	ret	0
??_U@YAPEAX_K@Z ENDP					; operator new[]
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
?get_ap_address@@YAPEAXXZ PROC				; get_ap_address

; 106  : 	return ap_address;

	mov	rax, QWORD PTR ?ap_address@@3PEAXEA	; ap_address

; 107  : }

	ret	0
?get_ap_address@@YAPEAXXZ ENDP				; get_ap_address
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
p$ = 48
??3@YAXPEAX@Z PROC					; operator delete

; 98   : void __cdecl operator delete (void* p) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 99   : 	free(p);

	mov	rcx, QWORD PTR p$[rsp]
	call	?free@@YAXPEAX@Z			; free

; 100  : }

	add	rsp, 40					; 00000028H
	ret	0
??3@YAXPEAX@Z ENDP					; operator delete
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\init.cpp
_TEXT	SEGMENT
size$ = 48
??2@YAPEAX_K@Z PROC					; operator new

; 90   : void* __cdecl ::operator new(size_t size) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 91   : 	return malloc(size);

	mov	rcx, QWORD PTR size$[rsp]
	call	?malloc@@YAPEAX_K@Z			; malloc

; 92   : }

	add	rsp, 40					; 00000028H
	ret	0
??2@YAPEAX_K@Z ENDP					; operator new
_TEXT	ENDS
END
