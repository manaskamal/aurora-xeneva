; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?drivers@@3PAU_aurora_driver_@@A		; drivers
_BSS	SEGMENT
?drivers@@3PAU_aurora_driver_@@A DB 03000H DUP (?)	; drivers
driver_class_unique_id DD 01H DUP (?)
_BSS	ENDS
CONST	SEGMENT
$SG3973	DB	'aurora_init_driver', 00H
	ORG $+5
$SG3975	DB	'aurora_close_driver', 00H
$SG4000	DB	'usb', 00H
$SG3977	DB	'aurora_write', 00H
	ORG $+3
$SG3985	DB	'sb16', 00H
	ORG $+3
$SG3988	DB	'aurora_init_driver', 00H
	ORG $+5
$SG3990	DB	'aurora_close_driver', 00H
	ORG $+4
$SG3992	DB	'aurora_write', 00H
CONST	ENDS
PUBLIC	?driver_mngr_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; driver_mngr_initialize
PUBLIC	?drv_mngr_write_driver@@YAXPEAE_K@Z		; drv_mngr_write_driver
PUBLIC	?request_driver_class_uid@@YAIXZ		; request_driver_class_uid
PUBLIC	?decreament_driver_class_uid@@YAXXZ		; decreament_driver_class_uid
PUBLIC	?create_driver_parameter@@YAPEAU_driver_param_@@XZ ; create_driver_parameter
EXTRN	x64_inportb:PROC
EXTRN	x64_inportw:PROC
EXTRN	x64_inportd:PROC
EXTRN	x64_outportb:PROC
EXTRN	x64_outportw:PROC
EXTRN	x64_outportd:PROC
EXTRN	?memset@@YAXPEAXEI@Z:PROC			; memset
EXTRN	printf:PROC
EXTRN	?read_config_16@@YAXGHHHHPEAG@Z:PROC		; read_config_16
EXTRN	?write_config_16@@YAXGHHHHG@Z:PROC		; write_config_16
EXTRN	?read_config_32@@YAXGHHHHI@Z:PROC		; read_config_32
EXTRN	?read_config_8@@YAXGHHHHPEAE@Z:PROC		; read_config_8
EXTRN	?write_config_8@@YAXGHHHHE@Z:PROC		; write_config_8
EXTRN	?read_config_32_ext@@YAXGHHHHPEAI@Z:PROC	; read_config_32_ext
EXTRN	?write_config_32@@YAXHHHHI@Z:PROC		; write_config_32
EXTRN	?pci_find_device_class@@YA_NEEPEATpci_device_info@@PEAH11@Z:PROC ; pci_find_device_class
EXTRN	?pci_find_device_id@@YA_NGGPEATpci_device_info@@@Z:PROC ; pci_find_device_id
EXTRN	?pci_enable_bus_master@@YAXHHH@Z:PROC		; pci_enable_bus_master
EXTRN	?pci_enable_interrupt@@YAXHHH@Z:PROC		; pci_enable_interrupt
EXTRN	?GetProcAddress@@YAPEAXPEAXPEBD@Z:PROC		; GetProcAddress
EXTRN	?AuPmmngrAlloc@@YAPEAXXZ:PROC			; AuPmmngrAlloc
pdata	SEGMENT
$pdata$?driver_mngr_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD imagerel $LN9
	DD	imagerel $LN9+744
	DD	imagerel $unwind$?driver_mngr_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z
$pdata$?drv_mngr_write_driver@@YAXPEAE_K@Z DD imagerel $LN7
	DD	imagerel $LN7+117
	DD	imagerel $unwind$?drv_mngr_write_driver@@YAXPEAE_K@Z
$pdata$?request_driver_class_uid@@YAIXZ DD imagerel $LN3
	DD	imagerel $LN3+35
	DD	imagerel $unwind$?request_driver_class_uid@@YAIXZ
$pdata$?create_driver_parameter@@YAPEAU_driver_param_@@XZ DD imagerel $LN3
	DD	imagerel $LN3+431
	DD	imagerel $unwind$?create_driver_parameter@@YAPEAU_driver_param_@@XZ
pdata	ENDS
xdata	SEGMENT
$unwind$?driver_mngr_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD 020c01H
	DD	015010cH
$unwind$?drv_mngr_write_driver@@YAXPEAE_K@Z DD 010e01H
	DD	0620eH
$unwind$?request_driver_class_uid@@YAIXZ DD 010401H
	DD	02204H
$unwind$?create_driver_parameter@@YAPEAU_driver_param_@@XZ DD 010401H
	DD	0a204H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drvmngr.cpp
_TEXT	SEGMENT
pci$ = 32
cpu$ = 40
param$ = 48
m$ = 56
fs$ = 64
?create_driver_parameter@@YAPEAU_driver_param_@@XZ PROC	; create_driver_parameter

; 38   : driver_param_t * create_driver_parameter () {

$LN3:
	sub	rsp, 88					; 00000058H

; 39   : 	cpu_t *cpu = (cpu_t*)AuPmmngrAlloc();

	call	?AuPmmngrAlloc@@YAPEAXXZ		; AuPmmngrAlloc
	mov	QWORD PTR cpu$[rsp], rax

; 40   : 	cpu->interrupt_set_p = 0; //interrupt_set;

	mov	rax, QWORD PTR cpu$[rsp]
	mov	QWORD PTR [rax+8], 0

; 41   : 	cpu->interrupt_eoi_p = 0; //interrupt_end;

	mov	rax, QWORD PTR cpu$[rsp]
	mov	QWORD PTR [rax], 0

; 42   : 	cpu->inportb_p = x64_inportb;

	mov	rax, QWORD PTR cpu$[rsp]
	lea	rcx, OFFSET FLAT:x64_inportb
	mov	QWORD PTR [rax+16], rcx

; 43   : 	cpu->inportd_p = x64_inportd;

	mov	rax, QWORD PTR cpu$[rsp]
	lea	rcx, OFFSET FLAT:x64_inportd
	mov	QWORD PTR [rax+32], rcx

; 44   : 	cpu->inportw_p = x64_inportw;

	mov	rax, QWORD PTR cpu$[rsp]
	lea	rcx, OFFSET FLAT:x64_inportw
	mov	QWORD PTR [rax+24], rcx

; 45   : 	cpu->outportb_p = x64_outportb;

	mov	rax, QWORD PTR cpu$[rsp]
	lea	rcx, OFFSET FLAT:x64_outportb
	mov	QWORD PTR [rax+40], rcx

; 46   : 	cpu->outportd_p = x64_outportd;

	mov	rax, QWORD PTR cpu$[rsp]
	lea	rcx, OFFSET FLAT:x64_outportd
	mov	QWORD PTR [rax+56], rcx

; 47   : 	cpu->outportw_p = x64_outportw;

	mov	rax, QWORD PTR cpu$[rsp]
	lea	rcx, OFFSET FLAT:x64_outportw
	mov	QWORD PTR [rax+48], rcx

; 48   : 
; 49   : 	pci_p_t *pci = (pci_p_t*)AuPmmngrAlloc();

	call	?AuPmmngrAlloc@@YAPEAXXZ		; AuPmmngrAlloc
	mov	QWORD PTR pci$[rsp], rax

; 50   : 	pci->pci_enable_bus_master_p = pci_enable_bus_master;

	mov	rax, QWORD PTR pci$[rsp]
	lea	rcx, OFFSET FLAT:?pci_enable_bus_master@@YAXHHH@Z ; pci_enable_bus_master
	mov	QWORD PTR [rax+16], rcx

; 51   : 	pci->pci_enable_interrupt_p = pci_enable_interrupt;

	mov	rax, QWORD PTR pci$[rsp]
	lea	rcx, OFFSET FLAT:?pci_enable_interrupt@@YAXHHH@Z ; pci_enable_interrupt
	mov	QWORD PTR [rax+24], rcx

; 52   : 	pci->pci_find_device_class_p = pci_find_device_class;

	mov	rax, QWORD PTR pci$[rsp]
	lea	rcx, OFFSET FLAT:?pci_find_device_class@@YA_NEEPEATpci_device_info@@PEAH11@Z ; pci_find_device_class
	mov	QWORD PTR [rax], rcx

; 53   : 	pci->pci_find_device_id_p = pci_find_device_id;

	mov	rax, QWORD PTR pci$[rsp]
	lea	rcx, OFFSET FLAT:?pci_find_device_id@@YA_NGGPEATpci_device_info@@@Z ; pci_find_device_id
	mov	QWORD PTR [rax+8], rcx

; 54   : 	pci->read_config_16_p = read_config_16;

	mov	rax, QWORD PTR pci$[rsp]
	lea	rcx, OFFSET FLAT:?read_config_16@@YAXGHHHHPEAG@Z ; read_config_16
	mov	QWORD PTR [rax+32], rcx

; 55   : 	pci->read_config_8_p = read_config_8;

	mov	rax, QWORD PTR pci$[rsp]
	lea	rcx, OFFSET FLAT:?read_config_8@@YAXGHHHHPEAE@Z ; read_config_8
	mov	QWORD PTR [rax+56], rcx

; 56   : 	pci->read_config_32_p = read_config_32;

	mov	rax, QWORD PTR pci$[rsp]
	lea	rcx, OFFSET FLAT:?read_config_32@@YAXGHHHHI@Z ; read_config_32
	mov	QWORD PTR [rax+48], rcx

; 57   : 	pci->read_config_32_ext_p = read_config_32_ext;

	mov	rax, QWORD PTR pci$[rsp]
	lea	rcx, OFFSET FLAT:?read_config_32_ext@@YAXGHHHHPEAI@Z ; read_config_32_ext
	mov	QWORD PTR [rax+72], rcx

; 58   : 	pci->write_config_16_p = write_config_16;

	mov	rax, QWORD PTR pci$[rsp]
	lea	rcx, OFFSET FLAT:?write_config_16@@YAXGHHHHG@Z ; write_config_16
	mov	QWORD PTR [rax+40], rcx

; 59   : 	pci->write_config_32_p = write_config_32;

	mov	rax, QWORD PTR pci$[rsp]
	lea	rcx, OFFSET FLAT:?write_config_32@@YAXHHHHI@Z ; write_config_32
	mov	QWORD PTR [rax+80], rcx

; 60   : 	pci->write_config_8_p = write_config_8;

	mov	rax, QWORD PTR pci$[rsp]
	lea	rcx, OFFSET FLAT:?write_config_8@@YAXGHHHHE@Z ; write_config_8
	mov	QWORD PTR [rax+64], rcx

; 61   : 
; 62   : 	mem_t *m = (mem_t*)AuPmmngrAlloc();

	call	?AuPmmngrAlloc@@YAPEAXXZ		; AuPmmngrAlloc
	mov	QWORD PTR m$[rsp], rax

; 63   : 	/*m->get_free_page_p = get_free_page;
; 64   : 	m->get_phys_address_p = get_physical_address;
; 65   : 	m->malloc_p = malloc;
; 66   : 	m->map_page_p = map_page;
; 67   : 	m->mfree_p = free;
; 68   : 	m->pmmngr_alloc_blocks_p = pmmngr_alloc_blocks;
; 69   : 	m->pmmngr_alloc_p = pmmngr_alloc;
; 70   : 	m->pmmngr_free_p = pmmngr_free;
; 71   : 	m->unmap_page_p = unmap_page;*/
; 72   : 
; 73   : 	fs_t *fs = (fs_t*)AuPmmngrAlloc();

	call	?AuPmmngrAlloc@@YAPEAXXZ		; AuPmmngrAlloc
	mov	QWORD PTR fs$[rsp], rax

; 74   : 	//fs->vfs_mount_p = vfs_mount;
; 75   : 
; 76   : 	driver_param_t* param = (driver_param_t*)AuPmmngrAlloc();

	call	?AuPmmngrAlloc@@YAPEAXXZ		; AuPmmngrAlloc
	mov	QWORD PTR param$[rsp], rax

; 77   : 	param->mem = m;

	mov	rax, QWORD PTR param$[rsp]
	mov	rcx, QWORD PTR m$[rsp]
	mov	QWORD PTR [rax+8], rcx

; 78   : 	param->cpu = cpu;

	mov	rax, QWORD PTR param$[rsp]
	mov	rcx, QWORD PTR cpu$[rsp]
	mov	QWORD PTR [rax+16], rcx

; 79   : 	param->pci = pci;

	mov	rax, QWORD PTR param$[rsp]
	mov	rcx, QWORD PTR pci$[rsp]
	mov	QWORD PTR [rax+24], rcx

; 80   : 	param->kdebug = printf;

	mov	rax, QWORD PTR param$[rsp]
	lea	rcx, OFFSET FLAT:printf
	mov	QWORD PTR [rax], rcx

; 81   : 	param->fs = fs;

	mov	rax, QWORD PTR param$[rsp]
	mov	rcx, QWORD PTR fs$[rsp]
	mov	QWORD PTR [rax+32], rcx

; 82   : 	return param;

	mov	rax, QWORD PTR param$[rsp]

; 83   : }

	add	rsp, 88					; 00000058H
	ret	0
?create_driver_parameter@@YAPEAU_driver_param_@@XZ ENDP	; create_driver_parameter
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drvmngr.cpp
_TEXT	SEGMENT
?decreament_driver_class_uid@@YAXXZ PROC		; decreament_driver_class_uid

; 35   : 	driver_class_unique_id--;

	mov	eax, DWORD PTR driver_class_unique_id
	dec	eax
	mov	DWORD PTR driver_class_unique_id, eax

; 36   : }

	ret	0
?decreament_driver_class_uid@@YAXXZ ENDP		; decreament_driver_class_uid
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drvmngr.cpp
_TEXT	SEGMENT
uid$ = 0
?request_driver_class_uid@@YAIXZ PROC			; request_driver_class_uid

; 27   : uint32_t request_driver_class_uid () {

$LN3:
	sub	rsp, 24

; 28   : 	uint32_t uid = driver_class_unique_id;

	mov	eax, DWORD PTR driver_class_unique_id
	mov	DWORD PTR uid$[rsp], eax

; 29   : 	driver_class_unique_id++;

	mov	eax, DWORD PTR driver_class_unique_id
	inc	eax
	mov	DWORD PTR driver_class_unique_id, eax

; 30   : 	return uid;

	mov	eax, DWORD PTR uid$[rsp]

; 31   : }

	add	rsp, 24
	ret	0
?request_driver_class_uid@@YAIXZ ENDP			; request_driver_class_uid
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drvmngr.cpp
_TEXT	SEGMENT
i$1 = 32
tv79 = 40
buffer$ = 64
length$ = 72
?drv_mngr_write_driver@@YAXPEAE_K@Z PROC		; drv_mngr_write_driver

; 131  : void drv_mngr_write_driver (unsigned char* buffer, size_t length) {

$LN7:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 132  : 	for (int i = 0; i < 256; i++) { 

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN4@drv_mngr_w
$LN3@drv_mngr_w:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN4@drv_mngr_w:
	cmp	DWORD PTR i$1[rsp], 256			; 00000100H
	jge	SHORT $LN2@drv_mngr_w

; 133  : 		if (drivers[i].present)

	movsxd	rax, DWORD PTR i$1[rsp]
	imul	rax, 48					; 00000030H
	lea	rcx, OFFSET FLAT:?drivers@@3PAU_aurora_driver_@@A ; drivers
	movzx	eax, BYTE PTR [rcx+rax+16]
	test	eax, eax
	je	SHORT $LN1@drv_mngr_w

; 134  : 			drivers[i].aurora_write(buffer, length);

	movsxd	rax, DWORD PTR i$1[rsp]
	imul	rax, 48					; 00000030H
	lea	rcx, OFFSET FLAT:?drivers@@3PAU_aurora_driver_@@A ; drivers
	mov	QWORD PTR tv79[rsp], rcx
	mov	rdx, QWORD PTR length$[rsp]
	mov	rcx, QWORD PTR buffer$[rsp]
	mov	r8, QWORD PTR tv79[rsp]
	call	QWORD PTR [r8+rax+40]
$LN1@drv_mngr_w:

; 135  : 	}

	jmp	SHORT $LN3@drv_mngr_w
$LN2@drv_mngr_w:

; 136  : }

	add	rsp, 56					; 00000038H
	ret	0
?drv_mngr_write_driver@@YAXPEAE_K@Z ENDP		; drv_mngr_write_driver
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drvmngr.cpp
_TEXT	SEGMENT
uid$1 = 32
uid$2 = 36
i$3 = 40
w$4 = 48
close_address$5 = 56
close_address$6 = 64
write_address$7 = 72
i$8 = 80
i$9 = 88
init_address$10 = 96
c$11 = 104
write_address$12 = 112
w$13 = 120
init_address$14 = 128
param$ = 136
c$15 = 144
tv204 = 152
info$ = 176
?driver_mngr_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z PROC ; driver_mngr_initialize

; 85   : void driver_mngr_initialize (KERNEL_BOOT_INFO *info) {

$LN9:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 168				; 000000a8H

; 86   : 	memset (drivers,0,sizeof(aurora_driver_t));

	mov	r8d, 48					; 00000030H
	xor	edx, edx
	lea	rcx, OFFSET FLAT:?drivers@@3PAU_aurora_driver_@@A ; drivers
	call	?memset@@YAXPEAXEI@Z			; memset

; 87   : 	driver_param_t *param = create_driver_parameter ();

	call	?create_driver_parameter@@YAPEAU_driver_param_@@XZ ; create_driver_parameter
	mov	QWORD PTR param$[rsp], rax

; 88   : 
; 89   : 	//!First of all register the pre-boot driver classes
; 90   : 	if (info->driver_entry1 != NULL) {  

	mov	rax, QWORD PTR info$[rsp]
	cmp	QWORD PTR [rax+114], 0
	je	$LN6@driver_mng

; 91   : 		void* init_address = GetProcAddress (info->driver_entry1,"aurora_init_driver");

	lea	rdx, OFFSET FLAT:$SG3973
	mov	rax, QWORD PTR info$[rsp]
	mov	rcx, QWORD PTR [rax+114]
	call	?GetProcAddress@@YAPEAXPEAXPEBD@Z	; GetProcAddress
	mov	QWORD PTR init_address$10[rsp], rax

; 92   : 		void* close_address = GetProcAddress (info->driver_entry1, "aurora_close_driver");

	lea	rdx, OFFSET FLAT:$SG3975
	mov	rax, QWORD PTR info$[rsp]
	mov	rcx, QWORD PTR [rax+114]
	call	?GetProcAddress@@YAPEAXPEAXPEBD@Z	; GetProcAddress
	mov	QWORD PTR close_address$6[rsp], rax

; 93   : 		void* write_address = GetProcAddress(info->driver_entry1 ,"aurora_write");

	lea	rdx, OFFSET FLAT:$SG3977
	mov	rax, QWORD PTR info$[rsp]
	mov	rcx, QWORD PTR [rax+114]
	call	?GetProcAddress@@YAPEAXPEAXPEBD@Z	; GetProcAddress
	mov	QWORD PTR write_address$12[rsp], rax

; 94   : 		init i = (init)init_address;

	mov	rax, QWORD PTR init_address$10[rsp]
	mov	QWORD PTR i$8[rsp], rax

; 95   : 		close c = (close)close_address;

	mov	rax, QWORD PTR close_address$6[rsp]
	mov	QWORD PTR c$15[rsp], rax

; 96   : 		write w = (write)write_address;

	mov	rax, QWORD PTR write_address$12[rsp]
	mov	QWORD PTR w$4[rsp], rax

; 97   : 	    uint32_t uid = request_driver_class_uid();

	call	?request_driver_class_uid@@YAIXZ	; request_driver_class_uid
	mov	DWORD PTR uid$2[rsp], eax

; 98   : 		drivers[uid].class_type = DRIVER_CLASS_AUDIO;

	mov	eax, DWORD PTR uid$2[rsp]
	imul	rax, 48					; 00000030H
	lea	rcx, OFFSET FLAT:?drivers@@3PAU_aurora_driver_@@A ; drivers
	mov	DWORD PTR [rcx+rax], 1

; 99   : 		drivers[uid].name = "sb16";

	mov	eax, DWORD PTR uid$2[rsp]
	imul	rax, 48					; 00000030H
	lea	rcx, OFFSET FLAT:?drivers@@3PAU_aurora_driver_@@A ; drivers
	lea	rdx, OFFSET FLAT:$SG3985
	mov	QWORD PTR [rcx+rax+8], rdx

; 100  : 		drivers[uid].present = true;

	mov	eax, DWORD PTR uid$2[rsp]
	imul	rax, 48					; 00000030H
	lea	rcx, OFFSET FLAT:?drivers@@3PAU_aurora_driver_@@A ; drivers
	mov	BYTE PTR [rcx+rax+16], 1

; 101  : 		drivers[uid].aurora_init_driver = i;

	mov	eax, DWORD PTR uid$2[rsp]
	imul	rax, 48					; 00000030H
	lea	rcx, OFFSET FLAT:?drivers@@3PAU_aurora_driver_@@A ; drivers
	mov	rdx, QWORD PTR i$8[rsp]
	mov	QWORD PTR [rcx+rax+24], rdx

; 102  : 		drivers[uid].aurora_close_driver = c;

	mov	eax, DWORD PTR uid$2[rsp]
	imul	rax, 48					; 00000030H
	lea	rcx, OFFSET FLAT:?drivers@@3PAU_aurora_driver_@@A ; drivers
	mov	rdx, QWORD PTR c$15[rsp]
	mov	QWORD PTR [rcx+rax+32], rdx

; 103  : 		drivers[uid].aurora_write = w;

	mov	eax, DWORD PTR uid$2[rsp]
	imul	rax, 48					; 00000030H
	lea	rcx, OFFSET FLAT:?drivers@@3PAU_aurora_driver_@@A ; drivers
	mov	rdx, QWORD PTR w$4[rsp]
	mov	QWORD PTR [rcx+rax+40], rdx
$LN6@driver_mng:

; 104  : 	}
; 105  : 
; 106  : 	//!First of all register the pre-boot driver classes
; 107  : 	if (info->driver_entry2 != NULL) {  

	mov	rax, QWORD PTR info$[rsp]
	cmp	QWORD PTR [rax+122], 0
	je	$LN5@driver_mng

; 108  : 		void* init_address = GetProcAddress (info->driver_entry2,"aurora_init_driver");

	lea	rdx, OFFSET FLAT:$SG3988
	mov	rax, QWORD PTR info$[rsp]
	mov	rcx, QWORD PTR [rax+122]
	call	?GetProcAddress@@YAPEAXPEAXPEBD@Z	; GetProcAddress
	mov	QWORD PTR init_address$14[rsp], rax

; 109  : 		void* close_address = GetProcAddress (info->driver_entry2, "aurora_close_driver");

	lea	rdx, OFFSET FLAT:$SG3990
	mov	rax, QWORD PTR info$[rsp]
	mov	rcx, QWORD PTR [rax+122]
	call	?GetProcAddress@@YAPEAXPEAXPEBD@Z	; GetProcAddress
	mov	QWORD PTR close_address$5[rsp], rax

; 110  : 		void* write_address = GetProcAddress(info->driver_entry2 ,"aurora_write");

	lea	rdx, OFFSET FLAT:$SG3992
	mov	rax, QWORD PTR info$[rsp]
	mov	rcx, QWORD PTR [rax+122]
	call	?GetProcAddress@@YAPEAXPEAXPEBD@Z	; GetProcAddress
	mov	QWORD PTR write_address$7[rsp], rax

; 111  : 		init i = (init)init_address;

	mov	rax, QWORD PTR init_address$14[rsp]
	mov	QWORD PTR i$9[rsp], rax

; 112  : 		close c = (close)close_address;

	mov	rax, QWORD PTR close_address$5[rsp]
	mov	QWORD PTR c$11[rsp], rax

; 113  : 		write w = (write)write_address;

	mov	rax, QWORD PTR write_address$7[rsp]
	mov	QWORD PTR w$13[rsp], rax

; 114  : 	    uint32_t uid = request_driver_class_uid();

	call	?request_driver_class_uid@@YAIXZ	; request_driver_class_uid
	mov	DWORD PTR uid$1[rsp], eax

; 115  : 		drivers[uid].class_type = DRIVER_CLASS_AUDIO;

	mov	eax, DWORD PTR uid$1[rsp]
	imul	rax, 48					; 00000030H
	lea	rcx, OFFSET FLAT:?drivers@@3PAU_aurora_driver_@@A ; drivers
	mov	DWORD PTR [rcx+rax], 1

; 116  : 		drivers[uid].name = "usb";

	mov	eax, DWORD PTR uid$1[rsp]
	imul	rax, 48					; 00000030H
	lea	rcx, OFFSET FLAT:?drivers@@3PAU_aurora_driver_@@A ; drivers
	lea	rdx, OFFSET FLAT:$SG4000
	mov	QWORD PTR [rcx+rax+8], rdx

; 117  : 		drivers[uid].present = true;

	mov	eax, DWORD PTR uid$1[rsp]
	imul	rax, 48					; 00000030H
	lea	rcx, OFFSET FLAT:?drivers@@3PAU_aurora_driver_@@A ; drivers
	mov	BYTE PTR [rcx+rax+16], 1

; 118  : 		drivers[uid].aurora_init_driver = i;

	mov	eax, DWORD PTR uid$1[rsp]
	imul	rax, 48					; 00000030H
	lea	rcx, OFFSET FLAT:?drivers@@3PAU_aurora_driver_@@A ; drivers
	mov	rdx, QWORD PTR i$9[rsp]
	mov	QWORD PTR [rcx+rax+24], rdx

; 119  : 		drivers[uid].aurora_close_driver = c;

	mov	eax, DWORD PTR uid$1[rsp]
	imul	rax, 48					; 00000030H
	lea	rcx, OFFSET FLAT:?drivers@@3PAU_aurora_driver_@@A ; drivers
	mov	rdx, QWORD PTR c$11[rsp]
	mov	QWORD PTR [rcx+rax+32], rdx

; 120  : 		drivers[uid].aurora_write = w;

	mov	eax, DWORD PTR uid$1[rsp]
	imul	rax, 48					; 00000030H
	lea	rcx, OFFSET FLAT:?drivers@@3PAU_aurora_driver_@@A ; drivers
	mov	rdx, QWORD PTR w$13[rsp]
	mov	QWORD PTR [rcx+rax+40], rdx
$LN5@driver_mng:

; 121  : 	}
; 122  : 
; 123  : 
; 124  : 	for (int i = 0; i < 256; i++) { 

	mov	DWORD PTR i$3[rsp], 0
	jmp	SHORT $LN4@driver_mng
$LN3@driver_mng:
	mov	eax, DWORD PTR i$3[rsp]
	inc	eax
	mov	DWORD PTR i$3[rsp], eax
$LN4@driver_mng:
	cmp	DWORD PTR i$3[rsp], 256			; 00000100H
	jge	SHORT $LN2@driver_mng

; 125  : 		if (drivers[i].present)

	movsxd	rax, DWORD PTR i$3[rsp]
	imul	rax, 48					; 00000030H
	lea	rcx, OFFSET FLAT:?drivers@@3PAU_aurora_driver_@@A ; drivers
	movzx	eax, BYTE PTR [rcx+rax+16]
	test	eax, eax
	je	SHORT $LN1@driver_mng

; 126  : 			drivers[i].aurora_init_driver(param);

	movsxd	rax, DWORD PTR i$3[rsp]
	imul	rax, 48					; 00000030H
	lea	rcx, OFFSET FLAT:?drivers@@3PAU_aurora_driver_@@A ; drivers
	mov	QWORD PTR tv204[rsp], rcx
	mov	rcx, QWORD PTR param$[rsp]
	mov	rdx, QWORD PTR tv204[rsp]
	call	QWORD PTR [rdx+rax+24]
$LN1@driver_mng:

; 127  : 	}

	jmp	SHORT $LN3@driver_mng
$LN2@driver_mng:

; 128  : 
; 129  : }

	add	rsp, 168				; 000000a8H
	ret	0
?driver_mngr_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ENDP ; driver_mngr_initialize
_TEXT	ENDS
END
