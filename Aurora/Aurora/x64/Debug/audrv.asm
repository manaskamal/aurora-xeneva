; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?drivers@@3PAPEAU_aurora_driver_@@A		; drivers
_BSS	SEGMENT
?drivers@@3PAPEAU_aurora_driver_@@A DQ 0100H DUP (?)	; drivers
driver_class_unique_id DD 01H DUP (?)
	ALIGN	8

driver_load_base DQ 01H DUP (?)
_BSS	ENDS
CONST	SEGMENT
$SG4120	DB	'AuDriverMain', 00H
	ORG $+3
$SG4123	DB	'AuDriverUnload', 00H
	ORG $+1
$SG4129	DB	'[aurora]: initializing drivers, please wait... ', 0aH, 00H
	ORG $+7
$SG4135	DB	'/audrv.cnf', 00H
CONST	ENDS
PUBLIC	?AuDrvMngrInitialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ; AuDrvMngrInitialize
PUBLIC	?AuRequestDriverId@@YAIXZ			; AuRequestDriverId
PUBLIC	?AuDecreaseDriverId@@YAXXZ			; AuDecreaseDriverId
PUBLIC	?AuGetConfEntry@@YAPEADIIPEAEH@Z		; AuGetConfEntry
PUBLIC	?AuCreateDriverInstance@@YAXPEAD@Z		; AuCreateDriverInstance
PUBLIC	?AuGetDriverName@@YAXIIPEAEH@Z			; AuGetDriverName
PUBLIC	?AuDriverLoad@@YAXPEADPEAU_aurora_driver_@@@Z	; AuDriverLoad
EXTRN	strcpy:PROC
EXTRN	strchr:PROC
EXTRN	memset:PROC
EXTRN	?atoi@@YAHPEBD@Z:PROC				; atoi
EXTRN	printf:PROC
EXTRN	?AuGetProcAddress@@YAPEAXPEAXPEBD@Z:PROC	; AuGetProcAddress
EXTRN	?AuPeLinkLibrary@@YAXPEAX@Z:PROC		; AuPeLinkLibrary
EXTRN	AuPmmngrAlloc:PROC
EXTRN	p2v:PROC
EXTRN	v2p:PROC
EXTRN	AuMapPage:PROC
EXTRN	malloc:PROC
EXTRN	?fat32_open@@YA?AU_vfs_node_@@PEAU1@PEAD@Z:PROC	; fat32_open
EXTRN	?fat32_read@@YAXPEAU_vfs_node_@@PEA_K@Z:PROC	; fat32_read
EXTRN	?pci_express_get_device@@YA_KGHHH@Z:PROC	; pci_express_get_device
EXTRN	pci_express_read:PROC
pdata	SEGMENT
$pdata$?AuDrvMngrInitialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD imagerel $LN21
	DD	imagerel $LN21+751
	DD	imagerel $unwind$?AuDrvMngrInitialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z
$pdata$?AuRequestDriverId@@YAIXZ DD imagerel $LN3
	DD	imagerel $LN3+35
	DD	imagerel $unwind$?AuRequestDriverId@@YAIXZ
$pdata$?AuGetConfEntry@@YAPEADIIPEAEH@Z DD imagerel $LN21
	DD	imagerel $LN21+576
	DD	imagerel $unwind$?AuGetConfEntry@@YAPEADIIPEAEH@Z
$pdata$?AuCreateDriverInstance@@YAXPEAD@Z DD imagerel $LN3
	DD	imagerel $LN3+114
	DD	imagerel $unwind$?AuCreateDriverInstance@@YAXPEAD@Z
$pdata$?AuGetDriverName@@YAXIIPEAEH@Z DD imagerel $LN9
	DD	imagerel $LN9+234
	DD	imagerel $unwind$?AuGetDriverName@@YAXIIPEAEH@Z
$pdata$?AuDriverLoad@@YAXPEADPEAU_aurora_driver_@@@Z DD imagerel $LN5
	DD	imagerel $LN5+482
	DD	imagerel $unwind$?AuDriverLoad@@YAXPEADPEAU_aurora_driver_@@@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?AuDrvMngrInitialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z DD 040e01H
	DD	03b010eH
	DD	060067007H
$unwind$?AuRequestDriverId@@YAIXZ DD 010401H
	DD	02204H
$unwind$?AuGetConfEntry@@YAPEADIIPEAEH@Z DD 011601H
	DD	0a216H
$unwind$?AuCreateDriverInstance@@YAXPEAD@Z DD 010901H
	DD	06209H
$unwind$?AuGetDriverName@@YAXIIPEAEH@Z DD 011601H
	DD	0c216H
$unwind$?AuDriverLoad@@YAXPEADPEAU_aurora_driver_@@@Z DD 041301H
	DD	0330113H
	DD	0600b700cH
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\audrv.cpp
_TEXT	SEGMENT
next_base_offset$ = 32
buffer$ = 40
block$1 = 48
entry_addr$ = 56
virtual_base$ = 64
unload_addr$ = 72
file$ = 80
$T2 = 192
$T3 = 296
filename$ = 432
driver$ = 440
?AuDriverLoad@@YAXPEADPEAU_aurora_driver_@@@Z PROC	; AuDriverLoad

; 169  : void AuDriverLoad (char* filename, aurora_driver_t *driver) {

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	push	rsi
	push	rdi
	sub	rsp, 408				; 00000198H

; 170  : 	int next_base_offset = 0;

	mov	DWORD PTR next_base_offset$[rsp], 0

; 171  : 	uint64_t* virtual_base = (uint64_t*)driver_load_base;

	mov	rax, QWORD PTR driver_load_base
	mov	QWORD PTR virtual_base$[rsp], rax

; 172  : 
; 173  : 	vfs_node_t file = fat32_open(NULL, filename);

	mov	r8, QWORD PTR filename$[rsp]
	xor	edx, edx
	lea	rcx, QWORD PTR $T3[rsp]
	call	?fat32_open@@YA?AU_vfs_node_@@PEAU1@PEAD@Z ; fat32_open
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

; 174  : 	uint64_t* buffer = (uint64_t*)AuPmmngrAlloc();

	call	AuPmmngrAlloc
	mov	QWORD PTR buffer$[rsp], rax

; 175  : 	memset(buffer, 0, 4096);

	mov	r8d, 4096				; 00001000H
	xor	edx, edx
	mov	rcx, QWORD PTR buffer$[rsp]
	call	memset

; 176  : 	fat32_read(&file, buffer);

	mov	rdx, QWORD PTR buffer$[rsp]
	lea	rcx, QWORD PTR file$[rsp]
	call	?fat32_read@@YAXPEAU_vfs_node_@@PEA_K@Z	; fat32_read

; 177  : 	AuMapPage((uint64_t)buffer,driver_load_base,0);

	xor	r8d, r8d
	mov	rdx, QWORD PTR driver_load_base
	mov	rcx, QWORD PTR buffer$[rsp]
	call	AuMapPage

; 178  : 	next_base_offset = 1;

	mov	DWORD PTR next_base_offset$[rsp], 1
$LN2@AuDriverLo:

; 179  : 	
; 180  : 
; 181  : 	while(file.eof != 1) {

	movzx	eax, BYTE PTR file$[rsp+36]
	cmp	eax, 1
	je	SHORT $LN1@AuDriverLo

; 182  : 		uint64_t* block = (uint64_t*)AuPmmngrAlloc();

	call	AuPmmngrAlloc
	mov	QWORD PTR block$1[rsp], rax

; 183  : 		memset(block, 0, 4096);

	mov	r8d, 4096				; 00001000H
	xor	edx, edx
	mov	rcx, QWORD PTR block$1[rsp]
	call	memset

; 184  : 		fat32_read (&file,block);

	mov	rdx, QWORD PTR block$1[rsp]
	lea	rcx, QWORD PTR file$[rsp]
	call	?fat32_read@@YAXPEAU_vfs_node_@@PEA_K@Z	; fat32_read

; 185  : 		AuMapPage((uint64_t)block,(driver_load_base + next_base_offset * 4096), 0);

	mov	eax, DWORD PTR next_base_offset$[rsp]
	imul	eax, 4096				; 00001000H
	cdqe
	mov	rcx, QWORD PTR driver_load_base
	add	rcx, rax
	mov	rax, rcx
	xor	r8d, r8d
	mov	rdx, rax
	mov	rcx, QWORD PTR block$1[rsp]
	call	AuMapPage

; 186  : 		next_base_offset++;

	mov	eax, DWORD PTR next_base_offset$[rsp]
	inc	eax
	mov	DWORD PTR next_base_offset$[rsp], eax

; 187  : 	}

	jmp	SHORT $LN2@AuDriverLo
$LN1@AuDriverLo:

; 188  : 
; 189  : 
; 190  : 	void* entry_addr = AuGetProcAddress((void*)driver_load_base,"AuDriverMain");

	lea	rdx, OFFSET FLAT:$SG4120
	mov	rcx, QWORD PTR driver_load_base
	call	?AuGetProcAddress@@YAPEAXPEAXPEBD@Z	; AuGetProcAddress
	mov	QWORD PTR entry_addr$[rsp], rax

; 191  : 	void* unload_addr = AuGetProcAddress((void*)driver_load_base,"AuDriverUnload");

	lea	rdx, OFFSET FLAT:$SG4123
	mov	rcx, QWORD PTR driver_load_base
	call	?AuGetProcAddress@@YAPEAXPEAXPEBD@Z	; AuGetProcAddress
	mov	QWORD PTR unload_addr$[rsp], rax

; 192  : 
; 193  : 	AuPeLinkLibrary(virtual_base);

	mov	rcx, QWORD PTR virtual_base$[rsp]
	call	?AuPeLinkLibrary@@YAXPEAX@Z		; AuPeLinkLibrary

; 194  : 	driver->entry = (au_drv_entry)entry_addr;

	mov	rax, QWORD PTR driver$[rsp]
	mov	rcx, QWORD PTR entry_addr$[rsp]
	mov	QWORD PTR [rax+56], rcx

; 195  : 	driver->unload = (au_drv_unload)unload_addr;

	mov	rax, QWORD PTR driver$[rsp]
	mov	rcx, QWORD PTR unload_addr$[rsp]
	mov	QWORD PTR [rax+64], rcx

; 196  : 	driver->base = AU_DRIVER_BASE_START;

	mov	rax, QWORD PTR driver$[rsp]
	mov	rcx, -70368739983360			; ffffc00000400000H
	mov	QWORD PTR [rax+40], rcx

; 197  : 	driver->end = driver->base + file.size;

	mov	eax, DWORD PTR file$[rsp+32]
	mov	rcx, QWORD PTR driver$[rsp]
	add	rax, QWORD PTR [rcx+40]
	mov	rcx, QWORD PTR driver$[rsp]
	mov	QWORD PTR [rcx+48], rax

; 198  : 	driver->present = true;

	mov	rax, QWORD PTR driver$[rsp]
	mov	BYTE PTR [rax+34], 1

; 199  : 	driver_load_base = driver_load_base + next_base_offset * 4096;

	mov	eax, DWORD PTR next_base_offset$[rsp]
	imul	eax, 4096				; 00001000H
	cdqe
	mov	rcx, QWORD PTR driver_load_base
	add	rcx, rax
	mov	rax, rcx
	mov	QWORD PTR driver_load_base, rax

; 200  : }

	add	rsp, 408				; 00000198H
	pop	rdi
	pop	rsi
	ret	0
?AuDriverLoad@@YAXPEADPEAU_aurora_driver_@@@Z ENDP	; AuDriverLoad
_TEXT	ENDS
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

; 137  : void AuGetDriverName (uint32_t vendor_id, uint32_t device_id,uint8_t* buffer,int entryoff) {

$LN9:
	mov	DWORD PTR [rsp+32], r9d
	mov	QWORD PTR [rsp+24], r8
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 104				; 00000068H

; 138  : 
; 139  : 	/* Get the entry offset for required device driver */
; 140  : 	char* offset = AuGetConfEntry(vendor_id, device_id, buffer, entryoff);

	mov	r9d, DWORD PTR entryoff$[rsp]
	mov	r8, QWORD PTR buffer$[rsp]
	mov	edx, DWORD PTR device_id$[rsp]
	mov	ecx, DWORD PTR vendor_id$[rsp]
	call	?AuGetConfEntry@@YAPEADIIPEAEH@Z	; AuGetConfEntry
	mov	QWORD PTR offset$[rsp], rax

; 141  : 
; 142  : 	if (offset == NULL)

	cmp	QWORD PTR offset$[rsp], 0
	jne	SHORT $LN6@AuGetDrive

; 143  : 		return;

	jmp	$LN7@AuGetDrive
$LN6@AuGetDrive:

; 144  : 	char *p = strchr(offset, ']');

	mov	edx, 93					; 0000005dH
	mov	rcx, QWORD PTR offset$[rsp]
	call	strchr
	mov	QWORD PTR p$[rsp], rax

; 145  : 	if (p)

	cmp	QWORD PTR p$[rsp], 0
	je	SHORT $LN5@AuGetDrive

; 146  : 		p++;

	mov	rax, QWORD PTR p$[rsp]
	inc	rax
	mov	QWORD PTR p$[rsp], rax
$LN5@AuGetDrive:

; 147  : 
; 148  : 	/* get the driver path */
; 149  : 	char drivername[32];
; 150  : 	memset(drivername,0, 32);

	mov	r8d, 32					; 00000020H
	xor	edx, edx
	lea	rcx, QWORD PTR drivername$[rsp]
	call	memset

; 151  : 	int i = 0;

	mov	DWORD PTR i$[rsp], 0

; 152  : 	for (i = 0; i < 32; i++) {

	mov	DWORD PTR i$[rsp], 0
	jmp	SHORT $LN4@AuGetDrive
$LN3@AuGetDrive:
	mov	eax, DWORD PTR i$[rsp]
	inc	eax
	mov	DWORD PTR i$[rsp], eax
$LN4@AuGetDrive:
	cmp	DWORD PTR i$[rsp], 32			; 00000020H
	jge	SHORT $LN2@AuGetDrive

; 153  : 		if(p[i] == '|')

	movsxd	rax, DWORD PTR i$[rsp]
	mov	rcx, QWORD PTR p$[rsp]
	movsx	eax, BYTE PTR [rcx+rax]
	cmp	eax, 124				; 0000007cH
	jne	SHORT $LN1@AuGetDrive

; 154  : 			break;

	jmp	SHORT $LN2@AuGetDrive
$LN1@AuGetDrive:

; 155  : 		drivername[i] = p[i];

	movsxd	rax, DWORD PTR i$[rsp]
	movsxd	rcx, DWORD PTR i$[rsp]
	mov	rdx, QWORD PTR p$[rsp]
	movzx	eax, BYTE PTR [rdx+rax]
	mov	BYTE PTR drivername$[rsp+rcx], al

; 156  : 	}

	jmp	SHORT $LN3@AuGetDrive
$LN2@AuGetDrive:

; 157  : 
; 158  : 	drivername[i] = 0;

	movsxd	rax, DWORD PTR i$[rsp]
	mov	BYTE PTR drivername$[rsp+rax], 0

; 159  : 
; 160  : 	AuCreateDriverInstance(drivername);

	lea	rcx, QWORD PTR drivername$[rsp]
	call	?AuCreateDriverInstance@@YAXPEAD@Z	; AuCreateDriverInstance
$LN7@AuGetDrive:

; 161  : 	return;
; 162  : }

	add	rsp, 104				; 00000068H
	ret	0
?AuGetDriverName@@YAXIIPEAEH@Z ENDP			; AuGetDriverName
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\audrv.cpp
_TEXT	SEGMENT
driver$ = 32
drivername$ = 64
?AuCreateDriverInstance@@YAXPEAD@Z PROC			; AuCreateDriverInstance

; 120  : void AuCreateDriverInstance (char* drivername) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 121  : 	aurora_driver_t *driver = (aurora_driver_t*)malloc(sizeof(aurora_driver_t));

	mov	ecx, 72					; 00000048H
	call	malloc
	mov	QWORD PTR driver$[rsp], rax

; 122  : 	memset(driver, 0, sizeof(aurora_driver_t));

	mov	r8d, 72					; 00000048H
	xor	edx, edx
	mov	rcx, QWORD PTR driver$[rsp]
	call	memset

; 123  : 	strcpy(driver->name, drivername);

	mov	rax, QWORD PTR driver$[rsp]
	add	rax, 2
	mov	rdx, QWORD PTR drivername$[rsp]
	mov	rcx, rax
	call	strcpy

; 124  : 	driver->id = AuRequestDriverId();

	call	?AuRequestDriverId@@YAIXZ		; AuRequestDriverId
	mov	rcx, QWORD PTR driver$[rsp]
	mov	BYTE PTR [rcx], al

; 125  : 	driver->present = false;

	mov	rax, QWORD PTR driver$[rsp]
	mov	BYTE PTR [rax+34], 0

; 126  : 	drivers[driver->id] = driver;

	mov	rax, QWORD PTR driver$[rsp]
	movzx	eax, BYTE PTR [rax]
	lea	rcx, OFFSET FLAT:?drivers@@3PAPEAU_aurora_driver_@@A ; drivers
	mov	rdx, QWORD PTR driver$[rsp]
	mov	QWORD PTR [rcx+rax*8], rdx

; 127  : 
; 128  : }

	add	rsp, 56					; 00000038H
	ret	0
?AuCreateDriverInstance@@YAXPEAD@Z ENDP			; AuCreateDriverInstance
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\audrv.cpp
_TEXT	SEGMENT
num$ = 32
p$ = 40
i$ = 48
i$1 = 52
fbuf$ = 56
devid$ = 64
entret$ = 68
venid$ = 72
entry_num$ = 76
vendor_id$ = 96
device_id$ = 104
buffer$ = 112
entryoff$ = 120
?AuGetConfEntry@@YAPEADIIPEAEH@Z PROC			; AuGetConfEntry

; 50   : char* AuGetConfEntry(uint32_t vendor_id, uint32_t device_id,uint8_t* buffer,int entryoff) {

$LN21:
	mov	DWORD PTR [rsp+32], r9d
	mov	QWORD PTR [rsp+24], r8
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 88					; 00000058H
$re$22:

; 51   : re:
; 52   : 	int entry_num = entryoff;

	mov	eax, DWORD PTR entryoff$[rsp]
	mov	DWORD PTR entry_num$[rsp], eax

; 53   : 	char* fbuf = (char*)buffer;

	mov	rax, QWORD PTR buffer$[rsp]
	mov	QWORD PTR fbuf$[rsp], rax
$search$23:

; 54   : 	/* Check the entry for the device */
; 55   : search:
; 56   : 	char* p = strchr(fbuf,'(');

	mov	edx, 40					; 00000028H
	mov	rcx, QWORD PTR fbuf$[rsp]
	call	strchr
	mov	QWORD PTR p$[rsp], rax

; 57   : 	if (p) {

	cmp	QWORD PTR p$[rsp], 0
	je	SHORT $LN18@AuGetConfE

; 58   : 		p++;

	mov	rax, QWORD PTR p$[rsp]
	inc	rax
	mov	QWORD PTR p$[rsp], rax

; 59   : 		fbuf++;

	mov	rax, QWORD PTR fbuf$[rsp]
	inc	rax
	mov	QWORD PTR fbuf$[rsp], rax
$LN18@AuGetConfE:

; 60   : 	}
; 61   : 	int entret = atoi(p);

	mov	rcx, QWORD PTR p$[rsp]
	call	?atoi@@YAHPEBD@Z			; atoi
	mov	DWORD PTR entret$[rsp], eax

; 62   : 	
; 63   : 	/* Check for last entry '(0)' it indicates that
; 64   : 	 * there is no more entry
; 65   : 	 */
; 66   : 	if (entret == 0) {

	cmp	DWORD PTR entret$[rsp], 0
	jne	SHORT $LN17@AuGetConfE

; 67   : 		return 0;

	xor	eax, eax
	jmp	$LN19@AuGetConfE
$LN17@AuGetConfE:

; 68   : 	}
; 69   : 
; 70   : 	if (entret != entry_num)

	mov	eax, DWORD PTR entry_num$[rsp]
	cmp	DWORD PTR entret$[rsp], eax
	je	SHORT $LN16@AuGetConfE

; 71   : 		goto search;

	jmp	SHORT $search$23
$LN16@AuGetConfE:

; 72   : 
; 73   : 
; 74   : 	/* Search for vendor id of the product */
; 75   : 	fbuf = p;

	mov	rax, QWORD PTR p$[rsp]
	mov	QWORD PTR fbuf$[rsp], rax

; 76   : 	p = strchr(fbuf,'[');

	mov	edx, 91					; 0000005bH
	mov	rcx, QWORD PTR fbuf$[rsp]
	call	strchr
	mov	QWORD PTR p$[rsp], rax

; 77   : 	int venid ,devid = 0;

	mov	DWORD PTR devid$[rsp], 0

; 78   : 	if (p)

	cmp	QWORD PTR p$[rsp], 0
	je	SHORT $LN15@AuGetConfE

; 79   : 		p++;

	mov	rax, QWORD PTR p$[rsp]
	inc	rax
	mov	QWORD PTR p$[rsp], rax
$LN15@AuGetConfE:

; 80   : 
; 81   : 	fbuf = p;

	mov	rax, QWORD PTR p$[rsp]
	mov	QWORD PTR fbuf$[rsp], rax

; 82   : 	char num[2];
; 83   : 	memset(num, 0, 2);

	mov	r8d, 2
	xor	edx, edx
	lea	rcx, QWORD PTR num$[rsp]
	call	memset

; 84   : 	int i;
; 85   : 	for (i= 0; i < 2; i++) {

	mov	DWORD PTR i$[rsp], 0
	jmp	SHORT $LN14@AuGetConfE
$LN13@AuGetConfE:
	mov	eax, DWORD PTR i$[rsp]
	inc	eax
	mov	DWORD PTR i$[rsp], eax
$LN14@AuGetConfE:
	cmp	DWORD PTR i$[rsp], 2
	jge	SHORT $LN12@AuGetConfE

; 86   : 		if (p[i] == ',' || p[i] == ']')

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

; 87   : 			break;

	jmp	SHORT $LN12@AuGetConfE
$LN11@AuGetConfE:

; 88   : 		num[i] = p[i];

	movsxd	rax, DWORD PTR i$[rsp]
	movsxd	rcx, DWORD PTR i$[rsp]
	mov	rdx, QWORD PTR p$[rsp]
	movzx	eax, BYTE PTR [rdx+rax]
	mov	BYTE PTR num$[rsp+rcx], al

; 89   : 		fbuf++;

	mov	rax, QWORD PTR fbuf$[rsp]
	inc	rax
	mov	QWORD PTR fbuf$[rsp], rax

; 90   : 	}

	jmp	SHORT $LN13@AuGetConfE
$LN12@AuGetConfE:

; 91   : 	num[i]=0;

	movsxd	rax, DWORD PTR i$[rsp]
	mov	BYTE PTR num$[rsp+rax], 0

; 92   : 	venid = atoi(num);

	lea	rcx, QWORD PTR num$[rsp]
	call	?atoi@@YAHPEBD@Z			; atoi
	mov	DWORD PTR venid$[rsp], eax

; 93   : 
; 94   : 	/* Now search for device id / product id */
; 95   : 	p = strchr(fbuf,',');

	mov	edx, 44					; 0000002cH
	mov	rcx, QWORD PTR fbuf$[rsp]
	call	strchr
	mov	QWORD PTR p$[rsp], rax

; 96   : 	if (p)

	cmp	QWORD PTR p$[rsp], 0
	je	SHORT $LN9@AuGetConfE

; 97   : 		p++;

	mov	rax, QWORD PTR p$[rsp]
	inc	rax
	mov	QWORD PTR p$[rsp], rax
$LN9@AuGetConfE:

; 98   : 	for (int i = 0; i < 2; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN8@AuGetConfE
$LN7@AuGetConfE:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN8@AuGetConfE:
	cmp	DWORD PTR i$1[rsp], 2
	jge	SHORT $LN6@AuGetConfE

; 99   : 		if (p[i] == ',' || p[i] == ']')

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

; 100  : 			break;

	jmp	SHORT $LN6@AuGetConfE
$LN5@AuGetConfE:

; 101  : 		num[i] = p[i];

	movsxd	rax, DWORD PTR i$1[rsp]
	movsxd	rcx, DWORD PTR i$1[rsp]
	mov	rdx, QWORD PTR p$[rsp]
	movzx	eax, BYTE PTR [rdx+rax]
	mov	BYTE PTR num$[rsp+rcx], al

; 102  : 	}

	jmp	SHORT $LN7@AuGetConfE
$LN6@AuGetConfE:

; 103  : 	num[i] = 0;

	movsxd	rax, DWORD PTR i$[rsp]
	mov	BYTE PTR num$[rsp+rax], 0

; 104  : 	devid = atoi(num);

	lea	rcx, QWORD PTR num$[rsp]
	call	?atoi@@YAHPEBD@Z			; atoi
	mov	DWORD PTR devid$[rsp], eax

; 105  : 
; 106  : 
; 107  : 	if (vendor_id != venid || devid != device_id) {

	mov	eax, DWORD PTR venid$[rsp]
	cmp	DWORD PTR vendor_id$[rsp], eax
	jne	SHORT $LN2@AuGetConfE
	mov	eax, DWORD PTR device_id$[rsp]
	cmp	DWORD PTR devid$[rsp], eax
	je	SHORT $LN3@AuGetConfE
$LN2@AuGetConfE:

; 108  : 		entryoff++;

	mov	eax, DWORD PTR entryoff$[rsp]
	inc	eax
	mov	DWORD PTR entryoff$[rsp], eax

; 109  : 		goto re;

	jmp	$re$22
$LN3@AuGetConfE:

; 110  : 	}
; 111  : 
; 112  : 	/* Finally we found the device driver */
; 113  : 	if (vendor_id == venid && devid == device_id) {

	mov	eax, DWORD PTR venid$[rsp]
	cmp	DWORD PTR vendor_id$[rsp], eax
	jne	SHORT $LN1@AuGetConfE
	mov	eax, DWORD PTR device_id$[rsp]
	cmp	DWORD PTR devid$[rsp], eax
	jne	SHORT $LN1@AuGetConfE

; 114  : 		return fbuf;

	mov	rax, QWORD PTR fbuf$[rsp]
	jmp	SHORT $LN19@AuGetConfE
$LN1@AuGetConfE:

; 115  : 	}
; 116  : 
; 117  : 	return 0;

	xor	eax, eax
$LN19@AuGetConfE:

; 118  : }

	add	rsp, 88					; 00000058H
	ret	0
?AuGetConfEntry@@YAPEADIIPEAEH@Z ENDP			; AuGetConfEntry
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\audrv.cpp
_TEXT	SEGMENT
?AuDecreaseDriverId@@YAXXZ PROC				; AuDecreaseDriverId

; 39   : 	driver_class_unique_id--;

	mov	eax, DWORD PTR driver_class_unique_id
	dec	eax
	mov	DWORD PTR driver_class_unique_id, eax

; 40   : }

	ret	0
?AuDecreaseDriverId@@YAXXZ ENDP				; AuDecreaseDriverId
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\audrv.cpp
_TEXT	SEGMENT
uid$ = 0
?AuRequestDriverId@@YAIXZ PROC				; AuRequestDriverId

; 31   : uint32_t AuRequestDriverId () {

$LN3:
	sub	rsp, 24

; 32   : 	uint32_t uid = driver_class_unique_id;

	mov	eax, DWORD PTR driver_class_unique_id
	mov	DWORD PTR uid$[rsp], eax

; 33   : 	driver_class_unique_id++;

	mov	eax, DWORD PTR driver_class_unique_id
	inc	eax
	mov	DWORD PTR driver_class_unique_id, eax

; 34   : 	return uid;

	mov	eax, DWORD PTR uid$[rsp]

; 35   : }

	add	rsp, 24
	ret	0
?AuRequestDriverId@@YAIXZ ENDP				; AuRequestDriverId
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\audrv.cpp
_TEXT	SEGMENT
dev$1 = 48
func$2 = 52
bus$3 = 56
i$4 = 60
i$5 = 64
sub_class$ = 68
device$6 = 72
vend_id$ = 80
conf$ = 88
driver$7 = 96
class_code$ = 104
dev_id$ = 108
filesize$ = 112
confdata$ = 120
device$ = 128
file$ = 144
$T8 = 256
$T9 = 360
info$ = 496
?AuDrvMngrInitialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z PROC ; AuDrvMngrInitialize

; 206  : void AuDrvMngrInitialize (KERNEL_BOOT_INFO *info) {

$LN21:
	mov	QWORD PTR [rsp+8], rcx
	push	rsi
	push	rdi
	sub	rsp, 472				; 000001d8H

; 207  : 	driver_class_unique_id = 0;

	mov	DWORD PTR driver_class_unique_id, 0

; 208  : 	driver_load_base = AU_DRIVER_BASE_START;

	mov	rax, -70368739983360			; ffffc00000400000H
	mov	QWORD PTR driver_load_base, rax

; 209  : 	printf ("[aurora]: initializing drivers, please wait... \n");

	lea	rcx, OFFSET FLAT:$SG4129
	call	printf

; 210  : 	/* Load the conf data */
; 211  : 	uint64_t* conf = (uint64_t*)p2v((size_t)AuPmmngrAlloc());

	call	AuPmmngrAlloc
	mov	rcx, rax
	call	p2v
	mov	QWORD PTR conf$[rsp], rax

; 212  : 	memset(conf, 0, 4096);

	mov	r8d, 4096				; 00001000H
	xor	edx, edx
	mov	rcx, QWORD PTR conf$[rsp]
	call	memset

; 213  : 	vfs_node_t file = fat32_open(NULL, "/audrv.cnf");

	lea	r8, OFFSET FLAT:$SG4135
	xor	edx, edx
	lea	rcx, QWORD PTR $T9[rsp]
	call	?fat32_open@@YA?AU_vfs_node_@@PEAU1@PEAD@Z ; fat32_open
	lea	rcx, QWORD PTR $T8[rsp]
	mov	rdi, rcx
	mov	rsi, rax
	mov	ecx, 104				; 00000068H
	rep movsb
	lea	rax, QWORD PTR file$[rsp]
	lea	rcx, QWORD PTR $T8[rsp]
	mov	rdi, rax
	mov	rsi, rcx
	mov	ecx, 104				; 00000068H
	rep movsb

; 214  : 	int filesize = file.size / 1024;

	xor	edx, edx
	mov	eax, DWORD PTR file$[rsp+32]
	mov	ecx, 1024				; 00000400H
	div	ecx
	mov	DWORD PTR filesize$[rsp], eax

; 215  : 	if(filesize < 4096)

	cmp	DWORD PTR filesize$[rsp], 4096		; 00001000H
	jge	SHORT $LN18@AuDrvMngrI

; 216  : 		fat32_read(&file,(uint64_t*)v2p((size_t)conf));

	mov	rcx, QWORD PTR conf$[rsp]
	call	v2p
	mov	rdx, rax
	lea	rcx, QWORD PTR file$[rsp]
	call	?fat32_read@@YAXPEAU_vfs_node_@@PEA_K@Z	; fat32_read
$LN18@AuDrvMngrI:

; 217  : 
; 218  : 	uint8_t* confdata = (uint8_t*)conf;

	mov	rax, QWORD PTR conf$[rsp]
	mov	QWORD PTR confdata$[rsp], rax

; 219  : 
; 220  : 	uint32_t vend_id, dev_id, class_code, sub_class = 0;

	mov	DWORD PTR sub_class$[rsp], 0

; 221  : 	uint32_t device = 0;

	mov	DWORD PTR device$[rsp], 0

; 222  : 	for (uint16_t bus = 0; bus < 0x20; bus++) {

	xor	eax, eax
	mov	WORD PTR bus$3[rsp], ax
	jmp	SHORT $LN17@AuDrvMngrI
$LN16@AuDrvMngrI:
	movzx	eax, WORD PTR bus$3[rsp]
	inc	ax
	mov	WORD PTR bus$3[rsp], ax
$LN17@AuDrvMngrI:
	movzx	eax, WORD PTR bus$3[rsp]
	cmp	eax, 32					; 00000020H
	jge	$LN15@AuDrvMngrI

; 223  : 		for (uint16_t dev = 0; dev < 32; dev++) {

	xor	eax, eax
	mov	WORD PTR dev$1[rsp], ax
	jmp	SHORT $LN14@AuDrvMngrI
$LN13@AuDrvMngrI:
	movzx	eax, WORD PTR dev$1[rsp]
	inc	ax
	mov	WORD PTR dev$1[rsp], ax
$LN14@AuDrvMngrI:
	movzx	eax, WORD PTR dev$1[rsp]
	cmp	eax, 32					; 00000020H
	jge	$LN12@AuDrvMngrI

; 224  : 			for (uint16_t func = 0; func < 8; func++) {

	xor	eax, eax
	mov	WORD PTR func$2[rsp], ax
	jmp	SHORT $LN11@AuDrvMngrI
$LN10@AuDrvMngrI:
	movzx	eax, WORD PTR func$2[rsp]
	inc	ax
	mov	WORD PTR func$2[rsp], ax
$LN11@AuDrvMngrI:
	movzx	eax, WORD PTR func$2[rsp]
	cmp	eax, 8
	jge	$LN9@AuDrvMngrI

; 225  : 			
; 226  : 				uint64_t device = pci_express_get_device(0, bus, dev, func);

	movzx	eax, WORD PTR func$2[rsp]
	movzx	ecx, WORD PTR dev$1[rsp]
	movzx	edx, WORD PTR bus$3[rsp]
	mov	r9d, eax
	mov	r8d, ecx
	xor	ecx, ecx
	call	?pci_express_get_device@@YA_KGHHH@Z	; pci_express_get_device
	mov	QWORD PTR device$6[rsp], rax

; 227  : 
; 228  : 				vend_id = pci_express_read(device, PCI_VENDOR_ID, bus, dev, func);

	movzx	eax, WORD PTR func$2[rsp]
	movzx	ecx, WORD PTR dev$1[rsp]
	movzx	edx, WORD PTR bus$3[rsp]
	mov	DWORD PTR [rsp+32], eax
	mov	r9d, ecx
	mov	r8d, edx
	xor	edx, edx
	mov	rcx, QWORD PTR device$6[rsp]
	call	pci_express_read
	mov	DWORD PTR vend_id$[rsp], eax

; 229  : 				dev_id = pci_express_read(device, PCI_DEVICE_ID, bus, dev, func);

	movzx	eax, WORD PTR func$2[rsp]
	movzx	ecx, WORD PTR dev$1[rsp]
	movzx	edx, WORD PTR bus$3[rsp]
	mov	DWORD PTR [rsp+32], eax
	mov	r9d, ecx
	mov	r8d, edx
	mov	edx, 2
	mov	rcx, QWORD PTR device$6[rsp]
	call	pci_express_read
	mov	DWORD PTR dev_id$[rsp], eax

; 230  : 				class_code = pci_express_read(device, PCI_CLASS, bus, dev, func);

	movzx	eax, WORD PTR func$2[rsp]
	movzx	ecx, WORD PTR dev$1[rsp]
	movzx	edx, WORD PTR bus$3[rsp]
	mov	DWORD PTR [rsp+32], eax
	mov	r9d, ecx
	mov	r8d, edx
	mov	edx, 11
	mov	rcx, QWORD PTR device$6[rsp]
	call	pci_express_read
	mov	DWORD PTR class_code$[rsp], eax

; 231  : 				sub_class = pci_express_read(device, PCI_SUBCLASS, bus, dev, func);

	movzx	eax, WORD PTR func$2[rsp]
	movzx	ecx, WORD PTR dev$1[rsp]
	movzx	edx, WORD PTR bus$3[rsp]
	mov	DWORD PTR [rsp+32], eax
	mov	r9d, ecx
	mov	r8d, edx
	mov	edx, 10
	mov	rcx, QWORD PTR device$6[rsp]
	call	pci_express_read
	mov	DWORD PTR sub_class$[rsp], eax

; 232  : 				
; 233  : 				if (dev_id == 0xFFFF || vend_id == 0xFFFF) 

	cmp	DWORD PTR dev_id$[rsp], 65535		; 0000ffffH
	je	SHORT $LN7@AuDrvMngrI
	cmp	DWORD PTR vend_id$[rsp], 65535		; 0000ffffH
	jne	SHORT $LN8@AuDrvMngrI
$LN7@AuDrvMngrI:

; 234  : 					continue;	

	jmp	$LN10@AuDrvMngrI
$LN8@AuDrvMngrI:

; 235  : 				AuGetDriverName(class_code,sub_class,  confdata,1);

	mov	r9d, 1
	mov	r8, QWORD PTR confdata$[rsp]
	mov	edx, DWORD PTR sub_class$[rsp]
	mov	ecx, DWORD PTR class_code$[rsp]
	call	?AuGetDriverName@@YAXIIPEAEH@Z		; AuGetDriverName

; 236  : 				for(int i = 0; i < 1000; i++)

	mov	DWORD PTR i$5[rsp], 0
	jmp	SHORT $LN6@AuDrvMngrI
$LN5@AuDrvMngrI:
	mov	eax, DWORD PTR i$5[rsp]
	inc	eax
	mov	DWORD PTR i$5[rsp], eax
$LN6@AuDrvMngrI:
	cmp	DWORD PTR i$5[rsp], 1000		; 000003e8H
	jge	SHORT $LN4@AuDrvMngrI

; 237  : 					;

	jmp	SHORT $LN5@AuDrvMngrI
$LN4@AuDrvMngrI:

; 238  : 			}

	jmp	$LN10@AuDrvMngrI
$LN9@AuDrvMngrI:

; 239  : 		}

	jmp	$LN13@AuDrvMngrI
$LN12@AuDrvMngrI:

; 240  : 	}

	jmp	$LN16@AuDrvMngrI
$LN15@AuDrvMngrI:

; 241  : 
; 242  : 	/* Serially call each startup entries of each driver */
; 243  : 	for (int i = 0; i < driver_class_unique_id; i++) {

	mov	DWORD PTR i$4[rsp], 0
	jmp	SHORT $LN3@AuDrvMngrI
$LN2@AuDrvMngrI:
	mov	eax, DWORD PTR i$4[rsp]
	inc	eax
	mov	DWORD PTR i$4[rsp], eax
$LN3@AuDrvMngrI:
	mov	eax, DWORD PTR driver_class_unique_id
	cmp	DWORD PTR i$4[rsp], eax
	jae	SHORT $LN1@AuDrvMngrI

; 244  : 		aurora_driver_t *driver = drivers[i];

	movsxd	rax, DWORD PTR i$4[rsp]
	lea	rcx, OFFSET FLAT:?drivers@@3PAPEAU_aurora_driver_@@A ; drivers
	mov	rax, QWORD PTR [rcx+rax*8]
	mov	QWORD PTR driver$7[rsp], rax

; 245  : 		AuDriverLoad(driver->name, driver);

	mov	rax, QWORD PTR driver$7[rsp]
	add	rax, 2
	mov	rdx, QWORD PTR driver$7[rsp]
	mov	rcx, rax
	call	?AuDriverLoad@@YAXPEADPEAU_aurora_driver_@@@Z ; AuDriverLoad

; 246  : 		driver->entry();

	mov	rax, QWORD PTR driver$7[rsp]
	call	QWORD PTR [rax+56]

; 247  : 	}

	jmp	SHORT $LN2@AuDrvMngrI
$LN1@AuDrvMngrI:

; 248  : }

	add	rsp, 472				; 000001d8H
	pop	rdi
	pop	rsi
	ret	0
?AuDrvMngrInitialize@@YAXPEAU_KERNEL_BOOT_INFO_@@@Z ENDP ; AuDrvMngrInitialize
_TEXT	ENDS
END
