; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?drivers@@3PAU_aurora_driver_@@A		; drivers
_BSS	SEGMENT
?drivers@@3PAU_aurora_driver_@@A DB 02800H DUP (?)	; drivers
driver_class_unique_id DD 01H DUP (?)
_BSS	ENDS
CONST	SEGMENT
$SG3948	DB	'Drivername -> %s', 0aH, 00H
	ORG $+6
$SG3956	DB	'/audrv.cnf', 00H
	ORG $+5
$SG3974	DB	'Search over ', 0aH, 00H
CONST	ENDS
PUBLIC	?AuDrvMngrInitialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; AuDrvMngrInitialize
PUBLIC	?AuRequestDriverId@@YAIXZ			; AuRequestDriverId
PUBLIC	?AuDecreaseDriverId@@YAXXZ			; AuDecreaseDriverId
PUBLIC	?AuGetConfEntry@@YAPEADIIPEAEH@Z		; AuGetConfEntry
PUBLIC	?AuGetDriverName@@YAXIIPEAEH@Z			; AuGetDriverName
EXTRN	?strchr@@YAPEADPEADH@Z:PROC			; strchr
EXTRN	?memset@@YAXPEAXEI@Z:PROC			; memset
EXTRN	?atoi@@YAHPEBD@Z:PROC				; atoi
EXTRN	printf:PROC
EXTRN	?read_config_header@@YAXHHHPEATpci_device_info@@@Z:PROC ; read_config_header
EXTRN	?read_config_32@@YAXGHHHHI@Z:PROC		; read_config_32
EXTRN	?AuPmmngrAlloc@@YAPEAXXZ:PROC			; AuPmmngrAlloc
EXTRN	?fat32_open@@YA?AU_vfs_node_@@PEAU1@PEAD@Z:PROC	; fat32_open
EXTRN	?fat32_read_file@@YAXPEAU_vfs_node_@@PEA_KI@Z:PROC ; fat32_read_file
pdata	SEGMENT
$pdata$?AuDrvMngrInitialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD imagerel $LN14
	DD	imagerel $LN14+425
	DD	imagerel $unwind$?AuDrvMngrInitialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z
$pdata$?AuRequestDriverId@@YAIXZ DD imagerel $LN3
	DD	imagerel $LN3+35
	DD	imagerel $unwind$?AuRequestDriverId@@YAIXZ
$pdata$?AuGetConfEntry@@YAPEADIIPEAEH@Z DD imagerel $LN21
	DD	imagerel $LN21+576
	DD	imagerel $unwind$?AuGetConfEntry@@YAPEADIIPEAEH@Z
$pdata$?AuGetDriverName@@YAXIIPEAEH@Z DD imagerel $LN9
	DD	imagerel $LN9+241
	DD	imagerel $unwind$?AuGetDriverName@@YAXIIPEAEH@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?AuDrvMngrInitialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD 040e01H
	DD	053010eH
	DD	060067007H
$unwind$?AuRequestDriverId@@YAIXZ DD 010401H
	DD	02204H
$unwind$?AuGetConfEntry@@YAPEADIIPEAEH@Z DD 011601H
	DD	0a216H
$unwind$?AuGetDriverName@@YAXIIPEAEH@Z DD 011601H
	DD	0c216H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\audrv.cpp
_TEXT	SEGMENT
i$ = 32
p$ = 40
offset$ = 48
drivername$ = 56
vendor_id$ = 112
device_id$ = 120
buffer$ = 128
entryoff$ = 136
?AuGetDriverName@@YAXIIPEAEH@Z PROC			; AuGetDriverName

; 126  : void AuGetDriverName (uint32_t vendor_id, uint32_t device_id,uint8_t* buffer,int entryoff) {

$LN9:
	mov	DWORD PTR [rsp+32], r9d
	mov	QWORD PTR [rsp+24], r8
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 104				; 00000068H

; 127  : 
; 128  : 	/* Get the entry offset for required device driver */
; 129  : 	char* offset = AuGetConfEntry(vendor_id, device_id, buffer, entryoff);

	mov	r9d, DWORD PTR entryoff$[rsp]
	mov	r8, QWORD PTR buffer$[rsp]
	mov	edx, DWORD PTR device_id$[rsp]
	mov	ecx, DWORD PTR vendor_id$[rsp]
	call	?AuGetConfEntry@@YAPEADIIPEAEH@Z	; AuGetConfEntry
	mov	QWORD PTR offset$[rsp], rax

; 130  : 
; 131  : 	if (offset == NULL)

	cmp	QWORD PTR offset$[rsp], 0
	jne	SHORT $LN6@AuGetDrive

; 132  : 		return;

	jmp	$LN7@AuGetDrive
$LN6@AuGetDrive:

; 133  : 	char *p = strchr(offset, ']');

	mov	edx, 93					; 0000005dH
	mov	rcx, QWORD PTR offset$[rsp]
	call	?strchr@@YAPEADPEADH@Z			; strchr
	mov	QWORD PTR p$[rsp], rax

; 134  : 	if (p)

	cmp	QWORD PTR p$[rsp], 0
	je	SHORT $LN5@AuGetDrive

; 135  : 		p++;

	mov	rax, QWORD PTR p$[rsp]
	inc	rax
	mov	QWORD PTR p$[rsp], rax
$LN5@AuGetDrive:

; 136  : 
; 137  : 	/* get the driver path */
; 138  : 	char drivername[32];
; 139  : 	memset(drivername,0, 32);

	mov	r8d, 32					; 00000020H
	xor	edx, edx
	lea	rcx, QWORD PTR drivername$[rsp]
	call	?memset@@YAXPEAXEI@Z			; memset

; 140  : 	int i = 0;

	mov	DWORD PTR i$[rsp], 0

; 141  : 	for (i = 0; i < 32; i++) {

	mov	DWORD PTR i$[rsp], 0
	jmp	SHORT $LN4@AuGetDrive
$LN3@AuGetDrive:
	mov	eax, DWORD PTR i$[rsp]
	inc	eax
	mov	DWORD PTR i$[rsp], eax
$LN4@AuGetDrive:
	cmp	DWORD PTR i$[rsp], 32			; 00000020H
	jge	SHORT $LN2@AuGetDrive

; 142  : 		if(p[i] == '|')

	movsxd	rax, DWORD PTR i$[rsp]
	mov	rcx, QWORD PTR p$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	cmp	eax, 124				; 0000007cH
	jne	SHORT $LN1@AuGetDrive

; 143  : 			break;

	jmp	SHORT $LN2@AuGetDrive
$LN1@AuGetDrive:

; 144  : 		drivername[i] = p[i];

	movsxd	rax, DWORD PTR i$[rsp]
	movsxd	rcx, DWORD PTR i$[rsp]
	mov	rdx, QWORD PTR p$[rsp]
	movzx	eax, BYTE PTR [rdx+rax]
	mov	BYTE PTR drivername$[rsp+rcx], al

; 145  : 	}

	jmp	SHORT $LN3@AuGetDrive
$LN2@AuGetDrive:

; 146  : 
; 147  : 	drivername[i] = 0;

	movsxd	rax, DWORD PTR i$[rsp]
	mov	BYTE PTR drivername$[rsp+rax], 0

; 148  : 
; 149  : 	printf ("Drivername -> %s\n", drivername);

	lea	rdx, QWORD PTR drivername$[rsp]
	lea	rcx, OFFSET FLAT:$SG3948
	call	printf
$LN7@AuGetDrive:

; 150  : }

	add	rsp, 104				; 00000068H
	ret	0
?AuGetDriverName@@YAXIIPEAEH@Z ENDP			; AuGetDriverName
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\audrv.cpp
_TEXT	SEGMENT
p$ = 32
i$ = 40
i$1 = 44
num$ = 48
fbuf$ = 56
devid$ = 64
venid$ = 68
entret$ = 72
entry_num$ = 76
vendor_id$ = 96
device_id$ = 104
buffer$ = 112
entryoff$ = 120
?AuGetConfEntry@@YAPEADIIPEAEH@Z PROC			; AuGetConfEntry

; 48   : char* AuGetConfEntry(uint32_t vendor_id, uint32_t device_id,uint8_t* buffer,int entryoff) {

$LN21:
	mov	DWORD PTR [rsp+32], r9d
	mov	QWORD PTR [rsp+24], r8
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 88					; 00000058H
$re$22:

; 49   : re:
; 50   : 	int entry_num = entryoff;

	mov	eax, DWORD PTR entryoff$[rsp]
	mov	DWORD PTR entry_num$[rsp], eax

; 51   : 	char* fbuf = (char*)buffer;

	mov	rax, QWORD PTR buffer$[rsp]
	mov	QWORD PTR fbuf$[rsp], rax
$search$23:

; 52   : 	/* Check the entry for the device */
; 53   : search:
; 54   : 	char* p = strchr(fbuf,'(');

	mov	edx, 40					; 00000028H
	mov	rcx, QWORD PTR fbuf$[rsp]
	call	?strchr@@YAPEADPEADH@Z			; strchr
	mov	QWORD PTR p$[rsp], rax

; 55   : 	if (p) {

	cmp	QWORD PTR p$[rsp], 0
	je	SHORT $LN18@AuGetConfE

; 56   : 		p++;

	mov	rax, QWORD PTR p$[rsp]
	inc	rax
	mov	QWORD PTR p$[rsp], rax

; 57   : 		fbuf++;

	mov	rax, QWORD PTR fbuf$[rsp]
	inc	rax
	mov	QWORD PTR fbuf$[rsp], rax
$LN18@AuGetConfE:

; 58   : 	}
; 59   : 	int entret = atoi(p);

	mov	rcx, QWORD PTR p$[rsp]
	call	?atoi@@YAHPEBD@Z			; atoi
	mov	DWORD PTR entret$[rsp], eax

; 60   : 	
; 61   : 	/* Check for last entry '(0)' it indicates that
; 62   : 	 * there is no more entry
; 63   : 	 */
; 64   : 	if (entret == 0) {

	cmp	DWORD PTR entret$[rsp], 0
	jne	SHORT $LN17@AuGetConfE

; 65   : 		return 0;

	xor	eax, eax
	jmp	$LN19@AuGetConfE
$LN17@AuGetConfE:

; 66   : 	}
; 67   : 
; 68   : 	if (entret != entry_num)

	mov	eax, DWORD PTR entry_num$[rsp]
	cmp	DWORD PTR entret$[rsp], eax
	je	SHORT $LN16@AuGetConfE

; 69   : 		goto search;

	jmp	SHORT $search$23
$LN16@AuGetConfE:

; 70   : 
; 71   : 
; 72   : 	/* Search for vendor id of the product */
; 73   : 	fbuf = p;

	mov	rax, QWORD PTR p$[rsp]
	mov	QWORD PTR fbuf$[rsp], rax

; 74   : 	p = strchr(fbuf,'[');

	mov	edx, 91					; 0000005bH
	mov	rcx, QWORD PTR fbuf$[rsp]
	call	?strchr@@YAPEADPEADH@Z			; strchr
	mov	QWORD PTR p$[rsp], rax

; 75   : 	int venid ,devid = 0;

	mov	DWORD PTR devid$[rsp], 0

; 76   : 	if (p)

	cmp	QWORD PTR p$[rsp], 0
	je	SHORT $LN15@AuGetConfE

; 77   : 		p++;

	mov	rax, QWORD PTR p$[rsp]
	inc	rax
	mov	QWORD PTR p$[rsp], rax
$LN15@AuGetConfE:

; 78   : 
; 79   : 	fbuf = p;

	mov	rax, QWORD PTR p$[rsp]
	mov	QWORD PTR fbuf$[rsp], rax

; 80   : 	char num[5];
; 81   : 	memset(num, 0, 5);

	mov	r8d, 5
	xor	edx, edx
	lea	rcx, QWORD PTR num$[rsp]
	call	?memset@@YAXPEAXEI@Z			; memset

; 82   : 	int i;
; 83   : 	for (i= 0; i < 5; i++) {

	mov	DWORD PTR i$[rsp], 0
	jmp	SHORT $LN14@AuGetConfE
$LN13@AuGetConfE:
	mov	eax, DWORD PTR i$[rsp]
	inc	eax
	mov	DWORD PTR i$[rsp], eax
$LN14@AuGetConfE:
	cmp	DWORD PTR i$[rsp], 5
	jge	SHORT $LN12@AuGetConfE

; 84   : 		if (p[i] == ',' || p[i] == ']')

	movsxd	rax, DWORD PTR i$[rsp]
	mov	rcx, QWORD PTR p$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	cmp	eax, 44					; 0000002cH
	je	SHORT $LN10@AuGetConfE
	movsxd	rax, DWORD PTR i$[rsp]
	mov	rcx, QWORD PTR p$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	cmp	eax, 93					; 0000005dH
	jne	SHORT $LN11@AuGetConfE
$LN10@AuGetConfE:

; 85   : 			break;

	jmp	SHORT $LN12@AuGetConfE
$LN11@AuGetConfE:

; 86   : 		num[i] = p[i];

	movsxd	rax, DWORD PTR i$[rsp]
	movsxd	rcx, DWORD PTR i$[rsp]
	mov	rdx, QWORD PTR p$[rsp]
	movzx	eax, BYTE PTR [rdx+rax]
	mov	BYTE PTR num$[rsp+rcx], al

; 87   : 		fbuf++;

	mov	rax, QWORD PTR fbuf$[rsp]
	inc	rax
	mov	QWORD PTR fbuf$[rsp], rax

; 88   : 	}

	jmp	SHORT $LN13@AuGetConfE
$LN12@AuGetConfE:

; 89   : 	num[i]=0;

	movsxd	rax, DWORD PTR i$[rsp]
	mov	BYTE PTR num$[rsp+rax], 0

; 90   : 	venid = atoi(num);

	lea	rcx, QWORD PTR num$[rsp]
	call	?atoi@@YAHPEBD@Z			; atoi
	mov	DWORD PTR venid$[rsp], eax

; 91   : 
; 92   : 	/* Now search for device id / product id */
; 93   : 	p = strchr(fbuf,',');

	mov	edx, 44					; 0000002cH
	mov	rcx, QWORD PTR fbuf$[rsp]
	call	?strchr@@YAPEADPEADH@Z			; strchr
	mov	QWORD PTR p$[rsp], rax

; 94   : 	if (p)

	cmp	QWORD PTR p$[rsp], 0
	je	SHORT $LN9@AuGetConfE

; 95   : 		p++;

	mov	rax, QWORD PTR p$[rsp]
	inc	rax
	mov	QWORD PTR p$[rsp], rax
$LN9@AuGetConfE:

; 96   : 	for (int i = 0; i < 5; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN8@AuGetConfE
$LN7@AuGetConfE:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN8@AuGetConfE:
	cmp	DWORD PTR i$1[rsp], 5
	jge	SHORT $LN6@AuGetConfE

; 97   : 		if (p[i] == ',' || p[i] == ']')

	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR p$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	cmp	eax, 44					; 0000002cH
	je	SHORT $LN4@AuGetConfE
	movsxd	rax, DWORD PTR i$1[rsp]
	mov	rcx, QWORD PTR p$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	cmp	eax, 93					; 0000005dH
	jne	SHORT $LN5@AuGetConfE
$LN4@AuGetConfE:

; 98   : 			break;

	jmp	SHORT $LN6@AuGetConfE
$LN5@AuGetConfE:

; 99   : 		num[i] = p[i];

	movsxd	rax, DWORD PTR i$1[rsp]
	movsxd	rcx, DWORD PTR i$1[rsp]
	mov	rdx, QWORD PTR p$[rsp]
	movzx	eax, BYTE PTR [rdx+rax]
	mov	BYTE PTR num$[rsp+rcx], al

; 100  : 	}

	jmp	SHORT $LN7@AuGetConfE
$LN6@AuGetConfE:

; 101  : 	num[i] = 0;

	movsxd	rax, DWORD PTR i$[rsp]
	mov	BYTE PTR num$[rsp+rax], 0

; 102  : 	devid = atoi(num);

	lea	rcx, QWORD PTR num$[rsp]
	call	?atoi@@YAHPEBD@Z			; atoi
	mov	DWORD PTR devid$[rsp], eax

; 103  : 
; 104  : 
; 105  : 	if (vendor_id != venid || devid != device_id) {

	mov	eax, DWORD PTR venid$[rsp]
	cmp	DWORD PTR vendor_id$[rsp], eax
	jne	SHORT $LN2@AuGetConfE
	mov	eax, DWORD PTR device_id$[rsp]
	cmp	DWORD PTR devid$[rsp], eax
	je	SHORT $LN3@AuGetConfE
$LN2@AuGetConfE:

; 106  : 		entryoff++;

	mov	eax, DWORD PTR entryoff$[rsp]
	inc	eax
	mov	DWORD PTR entryoff$[rsp], eax

; 107  : 		goto re;

	jmp	$re$22
$LN3@AuGetConfE:

; 108  : 	}
; 109  : 
; 110  : 	/* Finally we found the device driver */
; 111  : 	if (vendor_id == venid && devid == device_id) {

	mov	eax, DWORD PTR venid$[rsp]
	cmp	DWORD PTR vendor_id$[rsp], eax
	jne	SHORT $LN1@AuGetConfE
	mov	eax, DWORD PTR device_id$[rsp]
	cmp	DWORD PTR devid$[rsp], eax
	jne	SHORT $LN1@AuGetConfE

; 112  : 		return fbuf;

	mov	rax, QWORD PTR fbuf$[rsp]
	jmp	SHORT $LN19@AuGetConfE
$LN1@AuGetConfE:

; 113  : 	}
; 114  : 
; 115  : 	return 0;

	xor	eax, eax
$LN19@AuGetConfE:

; 116  : }

	add	rsp, 88					; 00000058H
	ret	0
?AuGetConfEntry@@YAPEADIIPEAEH@Z ENDP			; AuGetConfEntry
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\audrv.cpp
_TEXT	SEGMENT
?AuDecreaseDriverId@@YAXXZ PROC				; AuDecreaseDriverId

; 37   : 	driver_class_unique_id--;

	mov	eax, DWORD PTR driver_class_unique_id
	dec	eax
	mov	DWORD PTR driver_class_unique_id, eax

; 38   : }

	ret	0
?AuDecreaseDriverId@@YAXXZ ENDP				; AuDecreaseDriverId
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\audrv.cpp
_TEXT	SEGMENT
uid$ = 0
?AuRequestDriverId@@YAIXZ PROC				; AuRequestDriverId

; 29   : uint32_t AuRequestDriverId () {

$LN3:
	sub	rsp, 24

; 30   : 	uint32_t uid = driver_class_unique_id;

	mov	eax, DWORD PTR driver_class_unique_id
	mov	DWORD PTR uid$[rsp], eax

; 31   : 	driver_class_unique_id++;

	mov	eax, DWORD PTR driver_class_unique_id
	inc	eax
	mov	DWORD PTR driver_class_unique_id, eax

; 32   : 	return uid;

	mov	eax, DWORD PTR uid$[rsp]

; 33   : }

	add	rsp, 24
	ret	0
?AuRequestDriverId@@YAIXZ ENDP				; AuRequestDriverId
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\audrv.cpp
_TEXT	SEGMENT
dev$1 = 48
bus$2 = 52
func$3 = 56
conf$ = 64
confdata$ = 72
file$ = 80
config$ = 192
$T4 = 448
$T5 = 552
info$ = 688
?AuDrvMngrInitialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z PROC ; AuDrvMngrInitialize

; 157  : void AuDrvMngrInitialize (KERNEL_BOOT_INFO *info) {

$LN14:
	mov	QWORD PTR [rsp+8], rcx
	push	rsi
	push	rdi
	sub	rsp, 664				; 00000298H

; 158  : 	driver_class_unique_id = 0;

	mov	DWORD PTR driver_class_unique_id, 0

; 159  : 
; 160  : 	/* Load the conf data */
; 161  : 	uint64_t* conf = (uint64_t*)AuPmmngrAlloc();

	call	?AuPmmngrAlloc@@YAPEAXXZ		; AuPmmngrAlloc
	mov	QWORD PTR conf$[rsp], rax

; 162  : 	memset(conf, 0, 4096);

	mov	r8d, 4096				; 00001000H
	xor	edx, edx
	mov	rcx, QWORD PTR conf$[rsp]
	call	?memset@@YAXPEAXEI@Z			; memset

; 163  : 	vfs_node_t file = fat32_open(NULL, "/audrv.cnf");

	lea	r8, OFFSET FLAT:$SG3956
	xor	edx, edx
	lea	rcx, QWORD PTR $T5[rsp]
	call	?fat32_open@@YA?AU_vfs_node_@@PEAU1@PEAD@Z ; fat32_open
	lea	rcx, QWORD PTR $T4[rsp]
	mov	rdi, rcx
	mov	rsi, rax
	mov	ecx, 104				; 00000068H
	rep movsb
	lea	rax, QWORD PTR file$[rsp]
	lea	rcx, QWORD PTR $T4[rsp]
	mov	rdi, rax
	mov	rsi, rcx
	mov	ecx, 104				; 00000068H
	rep movsb

; 164  : 	fat32_read_file (&file,conf,file.size);

	mov	r8d, DWORD PTR file$[rsp+32]
	mov	rdx, QWORD PTR conf$[rsp]
	lea	rcx, QWORD PTR file$[rsp]
	call	?fat32_read_file@@YAXPEAU_vfs_node_@@PEA_KI@Z ; fat32_read_file

; 165  : 
; 166  : 	uint8_t* confdata = (uint8_t*)conf;

	mov	rax, QWORD PTR conf$[rsp]
	mov	QWORD PTR confdata$[rsp], rax

; 167  : 
; 168  : 	pci_device_info config;
; 169  : 	for (int bus = 0; bus < 256; bus++) {

	mov	DWORD PTR bus$2[rsp], 0
	jmp	SHORT $LN11@AuDrvMngrI
$LN10@AuDrvMngrI:
	mov	eax, DWORD PTR bus$2[rsp]
	inc	eax
	mov	DWORD PTR bus$2[rsp], eax
$LN11@AuDrvMngrI:
	cmp	DWORD PTR bus$2[rsp], 256		; 00000100H
	jge	$LN9@AuDrvMngrI

; 170  : 		for (int dev = 0; dev < 32; dev++) {

	mov	DWORD PTR dev$1[rsp], 0
	jmp	SHORT $LN8@AuDrvMngrI
$LN7@AuDrvMngrI:
	mov	eax, DWORD PTR dev$1[rsp]
	inc	eax
	mov	DWORD PTR dev$1[rsp], eax
$LN8@AuDrvMngrI:
	cmp	DWORD PTR dev$1[rsp], 32		; 00000020H
	jge	$LN6@AuDrvMngrI

; 171  : 			for (int func = 0; func < 8; func++) {

	mov	DWORD PTR func$3[rsp], 0
	jmp	SHORT $LN5@AuDrvMngrI
$LN4@AuDrvMngrI:
	mov	eax, DWORD PTR func$3[rsp]
	inc	eax
	mov	DWORD PTR func$3[rsp], eax
$LN5@AuDrvMngrI:
	cmp	DWORD PTR func$3[rsp], 8
	jge	$LN3@AuDrvMngrI

; 172  : 
; 173  : 				read_config_32 (0,bus, dev, func, 0, config.header[0]);

	mov	eax, 4
	imul	rax, 0
	mov	eax, DWORD PTR config$[rsp+rax]
	mov	DWORD PTR [rsp+40], eax
	mov	DWORD PTR [rsp+32], 0
	mov	r9d, DWORD PTR func$3[rsp]
	mov	r8d, DWORD PTR dev$1[rsp]
	mov	edx, DWORD PTR bus$2[rsp]
	xor	ecx, ecx
	call	?read_config_32@@YAXGHHHHI@Z		; read_config_32

; 174  : 				read_config_header (bus, dev, func, &config);

	lea	r9, QWORD PTR config$[rsp]
	mov	r8d, DWORD PTR func$3[rsp]
	mov	edx, DWORD PTR dev$1[rsp]
	mov	ecx, DWORD PTR bus$2[rsp]
	call	?read_config_header@@YAXHHHPEATpci_device_info@@@Z ; read_config_header

; 175  : 				if (config.device.deviceID == 0xFFFF || config.device.vendorID == 0xFFFF) 

	movzx	eax, WORD PTR config$[rsp+2]
	cmp	eax, 65535				; 0000ffffH
	je	SHORT $LN1@AuDrvMngrI
	movzx	eax, WORD PTR config$[rsp]
	cmp	eax, 65535				; 0000ffffH
	jne	SHORT $LN2@AuDrvMngrI
$LN1@AuDrvMngrI:

; 176  : 					continue;	

	jmp	SHORT $LN4@AuDrvMngrI
$LN2@AuDrvMngrI:

; 177  : 				AuGetDriverName(config.device.vendorID,config.device.deviceID,  confdata,1);

	movzx	eax, WORD PTR config$[rsp+2]
	movzx	ecx, WORD PTR config$[rsp]
	mov	r9d, 1
	mov	r8, QWORD PTR confdata$[rsp]
	mov	edx, eax
	call	?AuGetDriverName@@YAXIIPEAEH@Z		; AuGetDriverName

; 178  : 			}

	jmp	$LN4@AuDrvMngrI
$LN3@AuDrvMngrI:

; 179  : 		}

	jmp	$LN7@AuDrvMngrI
$LN6@AuDrvMngrI:

; 180  : 	}

	jmp	$LN10@AuDrvMngrI
$LN9@AuDrvMngrI:

; 181  : 
; 182  : 	printf ("Search over \n");

	lea	rcx, OFFSET FLAT:$SG3974
	call	printf

; 183  : }

	add	rsp, 664				; 00000298H
	pop	rdi
	pop	rsi
	ret	0
?AuDrvMngrInitialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ENDP ; AuDrvMngrInitialize
_TEXT	ENDS
END
