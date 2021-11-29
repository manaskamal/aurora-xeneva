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
$SG3605	DB	'aurora_init_driver', 00H
	ORG $+5
$SG3607	DB	'aurora_close_driver', 00H
	ORG $+4
$SG3609	DB	'aurora_write', 00H
	ORG $+3
$SG3617	DB	'sb16', 00H
CONST	ENDS
PUBLIC	?driver_mngr_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; driver_mngr_initialize
PUBLIC	?drv_mngr_write_driver@@YAXPEAE_K@Z		; drv_mngr_write_driver
PUBLIC	?request_driver_class_uid@@YAIXZ		; request_driver_class_uid
PUBLIC	?decreament_driver_class_uid@@YAXXZ		; decreament_driver_class_uid
PUBLIC	?create_driver_parameter@@YAPEAU_driver_param_@@XZ ; create_driver_parameter
EXTRN	?interrupt_end@@YAXI@Z:PROC			; interrupt_end
EXTRN	?interrupt_set@@YAX_KP6AX0PEAX@ZE@Z:PROC	; interrupt_set
EXTRN	?memset@@YAXPEAXEI@Z:PROC			; memset
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
EXTRN	?GetProcAddress@@YAPEAXPEAXPEBD@Z:PROC		; GetProcAddress
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	?get_physical_address@@YAPEA_K_K@Z:PROC		; get_physical_address
EXTRN	?alloc@@YAPEAX_K@Z:PROC				; alloc
pdata	SEGMENT
$pdata$?driver_mngr_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD imagerel $LN8
	DD	imagerel $LN8+425
	DD	imagerel $unwind$?driver_mngr_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z
$pdata$?drv_mngr_write_driver@@YAXPEAE_K@Z DD imagerel $LN7
	DD	imagerel $LN7+117
	DD	imagerel $unwind$?drv_mngr_write_driver@@YAXPEAE_K@Z
$pdata$?request_driver_class_uid@@YAIXZ DD imagerel $LN3
	DD	imagerel $LN3+35
	DD	imagerel $unwind$?request_driver_class_uid@@YAIXZ
$pdata$?create_driver_parameter@@YAPEAU_driver_param_@@XZ DD imagerel $LN3
	DD	imagerel $LN3+142
	DD	imagerel $unwind$?create_driver_parameter@@YAPEAU_driver_param_@@XZ
pdata	ENDS
xdata	SEGMENT
$unwind$?driver_mngr_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD 010901H
	DD	0e209H
$unwind$?drv_mngr_write_driver@@YAXPEAE_K@Z DD 010e01H
	DD	0620eH
$unwind$?request_driver_class_uid@@YAIXZ DD 010401H
	DD	02204H
$unwind$?create_driver_parameter@@YAPEAU_driver_param_@@XZ DD 010401H
	DD	06204H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drvmngr.cpp
_TEXT	SEGMENT
param$ = 32
?create_driver_parameter@@YAPEAU_driver_param_@@XZ PROC	; create_driver_parameter

; 38   : driver_param_t * create_driver_parameter () {

$LN3:
	sub	rsp, 56					; 00000038H

; 39   : 	driver_param_t* param = (driver_param_t*)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR param$[rsp], rax

; 40   : 	param->kdebug = printf;

	mov	rax, QWORD PTR param$[rsp]
	lea	rcx, OFFSET FLAT:?printf@@YAXPEBDZZ	; printf
	mov	QWORD PTR [rax], rcx

; 41   : 	param->interrupt_eoi = interrupt_end;

	mov	rax, QWORD PTR param$[rsp]
	lea	rcx, OFFSET FLAT:?interrupt_end@@YAXI@Z	; interrupt_end
	mov	QWORD PTR [rax+8], rcx

; 42   : 	param->interrupt_set = interrupt_set;

	mov	rax, QWORD PTR param$[rsp]
	lea	rcx, OFFSET FLAT:?interrupt_set@@YAX_KP6AX0PEAX@ZE@Z ; interrupt_set
	mov	QWORD PTR [rax+16], rcx

; 43   : 	param->pci_find_device = 0; //pci_find_device;

	mov	rax, QWORD PTR param$[rsp]
	mov	QWORD PTR [rax+24], 0

; 44   : 	param->pci_get_bar = 0; //pci_get_bar_addr;

	mov	rax, QWORD PTR param$[rsp]
	mov	QWORD PTR [rax+32], 0

; 45   : 	param->pci_set_mem_enable = 0; //pci_set_mem_enable;

	mov	rax, QWORD PTR param$[rsp]
	mov	QWORD PTR [rax+40], 0

; 46   : 	param->malloc = alloc;

	mov	rax, QWORD PTR param$[rsp]
	lea	rcx, OFFSET FLAT:?alloc@@YAPEAX_K@Z	; alloc
	mov	QWORD PTR [rax+48], rcx

; 47   : 	param->get_phys_address = get_physical_address;

	mov	rax, QWORD PTR param$[rsp]
	lea	rcx, OFFSET FLAT:?get_physical_address@@YAPEA_K_K@Z ; get_physical_address
	mov	QWORD PTR [rax+56], rcx

; 48   : 	return param;

	mov	rax, QWORD PTR param$[rsp]

; 49   : }

	add	rsp, 56					; 00000038H
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

; 83   : void drv_mngr_write_driver (unsigned char* buffer, size_t length) {

$LN7:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 84   : 	for (int i = 0; i < 256; i++) { 

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN4@drv_mngr_w
$LN3@drv_mngr_w:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN4@drv_mngr_w:
	cmp	DWORD PTR i$1[rsp], 256			; 00000100H
	jge	SHORT $LN2@drv_mngr_w

; 85   : 		if (drivers[i].present)

	movsxd	rax, DWORD PTR i$1[rsp]
	imul	rax, 48					; 00000030H
	lea	rcx, OFFSET FLAT:?drivers@@3PAU_aurora_driver_@@A ; drivers
	movzx	eax, BYTE PTR [rcx+rax+16]
	test	eax, eax
	je	SHORT $LN1@drv_mngr_w

; 86   : 			drivers[i].aurora_write(buffer, length);

	movsxd	rax, DWORD PTR i$1[rsp]
	imul	rax, 48					; 00000030H
	lea	rcx, OFFSET FLAT:?drivers@@3PAU_aurora_driver_@@A ; drivers
	mov	QWORD PTR tv79[rsp], rcx
	mov	rdx, QWORD PTR length$[rsp]
	mov	rcx, QWORD PTR buffer$[rsp]
	mov	r8, QWORD PTR tv79[rsp]
	call	QWORD PTR [r8+rax+40]
$LN1@drv_mngr_w:

; 87   : 	}

	jmp	SHORT $LN3@drv_mngr_w
$LN2@drv_mngr_w:

; 88   : }

	add	rsp, 56					; 00000038H
	ret	0
?drv_mngr_write_driver@@YAXPEAE_K@Z ENDP		; drv_mngr_write_driver
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drvmngr.cpp
_TEXT	SEGMENT
uid$1 = 32
i$2 = 36
write_address$3 = 40
c$4 = 48
close_address$5 = 56
w$6 = 64
i$7 = 72
param$ = 80
init_address$8 = 88
tv159 = 96
info$ = 128
?driver_mngr_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z PROC ; driver_mngr_initialize

; 51   : void driver_mngr_initialize (KERNEL_BOOT_INFO *info) {

$LN8:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 120				; 00000078H

; 52   : 
; 53   : 	
; 54   :    
; 55   : 	memset (drivers,0,sizeof(aurora_driver_t));

	mov	r8d, 48					; 00000030H
	xor	edx, edx
	lea	rcx, OFFSET FLAT:?drivers@@3PAU_aurora_driver_@@A ; drivers
	call	?memset@@YAXPEAXEI@Z			; memset

; 56   : 
; 57   : 	//!First of all register the pre-boot driver classes
; 58   : 	if (info->driver_entry1 != NULL) {  

	mov	rax, QWORD PTR info$[rsp]
	cmp	QWORD PTR [rax+122], 0
	je	$LN5@driver_mng

; 59   : 		void* init_address = GetProcAddress (info->driver_entry1,"aurora_init_driver");

	lea	rdx, OFFSET FLAT:$SG3605
	mov	rax, QWORD PTR info$[rsp]
	mov	rcx, QWORD PTR [rax+122]
	call	?GetProcAddress@@YAPEAXPEAXPEBD@Z	; GetProcAddress
	mov	QWORD PTR init_address$8[rsp], rax

; 60   : 		void* close_address = GetProcAddress (info->driver_entry1, "aurora_close_driver");

	lea	rdx, OFFSET FLAT:$SG3607
	mov	rax, QWORD PTR info$[rsp]
	mov	rcx, QWORD PTR [rax+122]
	call	?GetProcAddress@@YAPEAXPEAXPEBD@Z	; GetProcAddress
	mov	QWORD PTR close_address$5[rsp], rax

; 61   : 		void* write_address = GetProcAddress(info->driver_entry1 ,"aurora_write");

	lea	rdx, OFFSET FLAT:$SG3609
	mov	rax, QWORD PTR info$[rsp]
	mov	rcx, QWORD PTR [rax+122]
	call	?GetProcAddress@@YAPEAXPEAXPEBD@Z	; GetProcAddress
	mov	QWORD PTR write_address$3[rsp], rax

; 62   : 		init i = (init)init_address;

	mov	rax, QWORD PTR init_address$8[rsp]
	mov	QWORD PTR i$7[rsp], rax

; 63   : 		close c = (close)close_address;

	mov	rax, QWORD PTR close_address$5[rsp]
	mov	QWORD PTR c$4[rsp], rax

; 64   : 		write w = (write)write_address;

	mov	rax, QWORD PTR write_address$3[rsp]
	mov	QWORD PTR w$6[rsp], rax

; 65   : 	    uint32_t uid = request_driver_class_uid();

	call	?request_driver_class_uid@@YAIXZ	; request_driver_class_uid
	mov	DWORD PTR uid$1[rsp], eax

; 66   : 		drivers[uid].class_type = DRIVER_CLASS_AUDIO;

	mov	eax, DWORD PTR uid$1[rsp]
	imul	rax, 48					; 00000030H
	lea	rcx, OFFSET FLAT:?drivers@@3PAU_aurora_driver_@@A ; drivers
	mov	DWORD PTR [rcx+rax], 1

; 67   : 		drivers[uid].name = "sb16";

	mov	eax, DWORD PTR uid$1[rsp]
	imul	rax, 48					; 00000030H
	lea	rcx, OFFSET FLAT:?drivers@@3PAU_aurora_driver_@@A ; drivers
	lea	rdx, OFFSET FLAT:$SG3617
	mov	QWORD PTR [rcx+rax+8], rdx

; 68   : 		drivers[uid].present = true;

	mov	eax, DWORD PTR uid$1[rsp]
	imul	rax, 48					; 00000030H
	lea	rcx, OFFSET FLAT:?drivers@@3PAU_aurora_driver_@@A ; drivers
	mov	BYTE PTR [rcx+rax+16], 1

; 69   : 		drivers[uid].aurora_init_driver = i;

	mov	eax, DWORD PTR uid$1[rsp]
	imul	rax, 48					; 00000030H
	lea	rcx, OFFSET FLAT:?drivers@@3PAU_aurora_driver_@@A ; drivers
	mov	rdx, QWORD PTR i$7[rsp]
	mov	QWORD PTR [rcx+rax+24], rdx

; 70   : 		drivers[uid].aurora_close_driver = c;

	mov	eax, DWORD PTR uid$1[rsp]
	imul	rax, 48					; 00000030H
	lea	rcx, OFFSET FLAT:?drivers@@3PAU_aurora_driver_@@A ; drivers
	mov	rdx, QWORD PTR c$4[rsp]
	mov	QWORD PTR [rcx+rax+32], rdx

; 71   : 		drivers[uid].aurora_write = w;

	mov	eax, DWORD PTR uid$1[rsp]
	imul	rax, 48					; 00000030H
	lea	rcx, OFFSET FLAT:?drivers@@3PAU_aurora_driver_@@A ; drivers
	mov	rdx, QWORD PTR w$6[rsp]
	mov	QWORD PTR [rcx+rax+40], rdx
$LN5@driver_mng:

; 72   : 
; 73   : 	}
; 74   : 
; 75   :     driver_param_t *param = create_driver_parameter ();

	call	?create_driver_parameter@@YAPEAU_driver_param_@@XZ ; create_driver_parameter
	mov	QWORD PTR param$[rsp], rax

; 76   : 	for (int i = 0; i < 256; i++) { 

	mov	DWORD PTR i$2[rsp], 0
	jmp	SHORT $LN4@driver_mng
$LN3@driver_mng:
	mov	eax, DWORD PTR i$2[rsp]
	inc	eax
	mov	DWORD PTR i$2[rsp], eax
$LN4@driver_mng:
	cmp	DWORD PTR i$2[rsp], 256			; 00000100H
	jge	SHORT $LN2@driver_mng

; 77   : 		if (drivers[i].present)

	movsxd	rax, DWORD PTR i$2[rsp]
	imul	rax, 48					; 00000030H
	lea	rcx, OFFSET FLAT:?drivers@@3PAU_aurora_driver_@@A ; drivers
	movzx	eax, BYTE PTR [rcx+rax+16]
	test	eax, eax
	je	SHORT $LN1@driver_mng

; 78   : 			drivers[i].aurora_init_driver(param);

	movsxd	rax, DWORD PTR i$2[rsp]
	imul	rax, 48					; 00000030H
	lea	rcx, OFFSET FLAT:?drivers@@3PAU_aurora_driver_@@A ; drivers
	mov	QWORD PTR tv159[rsp], rcx
	mov	rcx, QWORD PTR param$[rsp]
	mov	rdx, QWORD PTR tv159[rsp]
	call	QWORD PTR [rdx+rax+24]
$LN1@driver_mng:

; 79   : 	}

	jmp	SHORT $LN3@driver_mng
$LN2@driver_mng:

; 80   : 
; 81   : }

	add	rsp, 120				; 00000078H
	ret	0
?driver_mngr_initialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ENDP ; driver_mngr_initialize
_TEXT	ENDS
END
