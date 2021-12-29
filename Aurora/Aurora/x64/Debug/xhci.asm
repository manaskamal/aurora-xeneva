; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?xusb_dev@@3PEAU_xhci_@@EA			; xusb_dev
_BSS	SEGMENT
?xusb_dev@@3PEAU_xhci_@@EA DQ 01H DUP (?)		; xusb_dev
_BSS	ENDS
CONST	SEGMENT
$SG3336	DB	'[XHCI USB]: Interrupt fired', 0aH, 00H
	ORG $+3
$SG3348	DB	'USB: stating controller took %d ms', 0aH, 00H
	ORG $+4
$SG3350	DB	'USB: error! couldn''t clear controller halted bit', 0aH, 00H
	ORG $+6
$SG3353	DB	'USB: XHCI stopping command ring', 0aH, 00H
	ORG $+7
$SG3358	DB	'USB: xHCI stopping ring took %d ms', 0aH, 00H
	ORG $+4
$SG3360	DB	'USB: xHCI couldn''t stop command ring', 0aH, 00H
	ORG $+2
$SG3365	DB	'USB: xHCI stopping controller took %d ms', 0aH, 00H
	ORG $+6
$SG3367	DB	'USB: xHCI couldn''t set controller halted bit', 0aH, 00H
	ORG $+2
$SG3368	DB	'USB: xHCI controller reset completed ', 0aH, 00H
	ORG $+1
$SG3378	DB	'USB: xHCI resetting controller took %dms ', 0aH, 00H
	ORG $+5
$SG3380	DB	'USB: controller did not clear reset bit', 0aH, 00H
	ORG $+7
$SG3381	DB	'USB: xHCI controller reset successfully', 0aH, 00H
	ORG $+7
$SG3391	DB	'USB xHCI: not found', 0aH, 00H
	ORG $+3
$SG3392	DB	'Scanning MSI support for USB', 0aH, 00H
	ORG $+2
$SG3395	DB	'Legacy Interrupt handling for USB xhci is not supported', 0aH
	DB	00H
	ORG $+7
$SG3399	DB	'USB: xHCI version - (%d.%d%d)', 0aH, 00H
	ORG $+1
$SG3403	DB	'USB: xHCI interrupt line -> %d', 0aH, 00H
$SG3404	DB	'USB: xHCI interrupt pin -> %d', 0aH, 00H
CONST	ENDS
PUBLIC	?xhci_initialize@@YAXXZ				; xhci_initialize
PUBLIC	?xhci_handler@@YAX_KPEAX@Z			; xhci_handler
PUBLIC	?xhci_start_stop@@YAXH@Z			; xhci_start_stop
EXTRN	x64_cli:PROC
EXTRN	x64_sti:PROC
EXTRN	?pci_find_device_class@@YA_NEEPEATpci_device_info@@PEAH11@Z:PROC ; pci_find_device_class
EXTRN	?pci_alloc_msi@@YA_NHHHP6AX_KPEAX@Z@Z:PROC	; pci_alloc_msi
EXTRN	?pci_enable_bus_master@@YAXHHH@Z:PROC		; pci_enable_bus_master
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
pdata	SEGMENT
$pdata$?xhci_initialize@@YAXXZ DD imagerel $LN5
	DD	imagerel $LN5+492
	DD	imagerel $unwind$?xhci_initialize@@YAXXZ
$pdata$?xhci_handler@@YAX_KPEAX@Z DD imagerel $LN3
	DD	imagerel $LN3+31
	DD	imagerel $unwind$?xhci_handler@@YAX_KPEAX@Z
$pdata$?xhci_start_stop@@YAXH@Z DD imagerel $LN21
	DD	imagerel $LN21+419
	DD	imagerel $unwind$?xhci_start_stop@@YAXH@Z
$pdata$?reset@@YAXXZ DD imagerel ?reset@@YAXXZ
	DD	imagerel ?reset@@YAXXZ+179
	DD	imagerel $unwind$?reset@@YAXXZ
pdata	ENDS
xdata	SEGMENT
$unwind$?xhci_initialize@@YAXXZ DD 010401H
	DD	0c204H
$unwind$?xhci_handler@@YAX_KPEAX@Z DD 010e01H
	DD	0420eH
$unwind$?xhci_start_stop@@YAXH@Z DD 010801H
	DD	06208H
$unwind$?reset@@YAXXZ DD 010401H
	DD	06204H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\usb\xhci.cpp
_TEXT	SEGMENT
count$1 = 32
tv75 = 36
op_reg$ = 40
?reset@@YAXXZ PROC					; reset

; 92   : static void reset () {

	sub	rsp, 56					; 00000038H

; 93   : 	//! stop the controller
; 94   : 	xhci_start_stop(0);

	xor	ecx, ecx
	call	?xhci_start_stop@@YAXH@Z		; xhci_start_stop

; 95   : 
; 96   : 	xhci_op_regs* op_reg = (xhci_op_regs*)xusb_dev->xhci_op_address;

	mov	rax, QWORD PTR ?xusb_dev@@3PEAU_xhci_@@EA ; xusb_dev
	mov	rax, QWORD PTR [rax+8]
	mov	QWORD PTR op_reg$[rsp], rax

; 97   : 	op_reg->cmd |= XHCI_CMD_HCRESET;

	mov	rax, QWORD PTR op_reg$[rsp]
	mov	eax, DWORD PTR [rax]
	or	eax, 2
	mov	rcx, QWORD PTR op_reg$[rsp]
	mov	DWORD PTR [rcx], eax

; 98   : 
; 99   : 	//! wait until the host controller clears it
; 100  : 	for (int count = 0; count < 2000; count++){

	mov	DWORD PTR count$1[rsp], 0
	jmp	SHORT $LN5@reset
$LN4@reset:
	mov	eax, DWORD PTR count$1[rsp]
	inc	eax
	mov	DWORD PTR count$1[rsp], eax
$LN5@reset:
	cmp	DWORD PTR count$1[rsp], 2000		; 000007d0H
	jge	SHORT $LN3@reset

; 101  : 		if (! op_reg->cmd & XHCI_CMD_HCRESET) {

	mov	rax, QWORD PTR op_reg$[rsp]
	mov	eax, DWORD PTR [rax]
	test	eax, eax
	jne	SHORT $LN8@reset
	mov	DWORD PTR tv75[rsp], 1
	jmp	SHORT $LN9@reset
$LN8@reset:
	mov	DWORD PTR tv75[rsp], 0
$LN9@reset:
	mov	eax, DWORD PTR tv75[rsp]
	and	eax, 2
	test	eax, eax
	je	SHORT $LN2@reset

; 102  : 			printf ("USB: xHCI resetting controller took %dms \n",count);

	mov	edx, DWORD PTR count$1[rsp]
	lea	rcx, OFFSET FLAT:$SG3378
	call	?printf@@YAXPEBDZZ			; printf

; 103  : 			break;

	jmp	SHORT $LN3@reset
$LN2@reset:

; 104  : 		}
; 105  : 	}

	jmp	SHORT $LN4@reset
$LN3@reset:

; 106  : 
; 107  : 	//! clear
; 108  : 	if (op_reg->cmd & XHCI_CMD_HCRESET)

	mov	rax, QWORD PTR op_reg$[rsp]
	mov	eax, DWORD PTR [rax]
	and	eax, 2
	test	eax, eax
	je	SHORT $LN1@reset

; 109  : 	{
; 110  : 		printf ("USB: controller did not clear reset bit\n");

	lea	rcx, OFFSET FLAT:$SG3380
	call	?printf@@YAXPEBDZZ			; printf

; 111  : 		return;

	jmp	SHORT $LN6@reset
$LN1@reset:

; 112  : 	}
; 113  : 
; 114  : 	//! successfull
; 115  : 	printf ("USB: xHCI controller reset successfully\n");

	lea	rcx, OFFSET FLAT:$SG3381
	call	?printf@@YAXPEBDZZ			; printf
$LN6@reset:

; 116  : }

	add	rsp, 56					; 00000038H
	ret	0
?reset@@YAXXZ ENDP					; reset
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\usb\xhci.cpp
_TEXT	SEGMENT
count$ = 32
op$ = 40
start$ = 64
?xhci_start_stop@@YAXH@Z PROC				; xhci_start_stop

; 25   : void xhci_start_stop (int start) {

$LN21:
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 56					; 00000038H

; 26   : 
; 27   : 	int count;
; 28   : 
; 29   : 	xhci_op_regs* op = (xhci_op_regs*)xusb_dev->xhci_op_address;

	mov	rax, QWORD PTR ?xusb_dev@@3PEAU_xhci_@@EA ; xusb_dev
	mov	rax, QWORD PTR [rax+8]
	mov	QWORD PTR op$[rsp], rax

; 30   : 
; 31   : 	if (start) {

	cmp	DWORD PTR start$[rsp], 0
	je	SHORT $LN18@xhci_start

; 32   : 		//! set the run/stop bit
; 33   : 		op->cmd |= XHCI_CMD_RUNSTOP;

	mov	rax, QWORD PTR op$[rsp]
	mov	eax, DWORD PTR [rax]
	or	eax, 1
	mov	rcx, QWORD PTR op$[rsp]
	mov	DWORD PTR [rcx], eax

; 34   : 
; 35   : 		for (count = 0; count < 20; count++) {

	mov	DWORD PTR count$[rsp], 0
	jmp	SHORT $LN17@xhci_start
$LN16@xhci_start:
	mov	eax, DWORD PTR count$[rsp]
	inc	eax
	mov	DWORD PTR count$[rsp], eax
$LN17@xhci_start:
	cmp	DWORD PTR count$[rsp], 20
	jge	SHORT $LN15@xhci_start

; 36   : 			if (!(op->stat & XHCI_STAT_HCHALTED)) {

	mov	rax, QWORD PTR op$[rsp]
	mov	eax, DWORD PTR [rax+4]
	and	eax, 1
	test	eax, eax
	jne	SHORT $LN14@xhci_start

; 37   : 				printf ("USB: stating controller took %d ms\n", count);

	mov	edx, DWORD PTR count$[rsp]
	lea	rcx, OFFSET FLAT:$SG3348
	call	?printf@@YAXPEBDZZ			; printf

; 38   : 				break;

	jmp	SHORT $LN15@xhci_start
$LN14@xhci_start:

; 39   : 			}
; 40   : 		}

	jmp	SHORT $LN16@xhci_start
$LN15@xhci_start:

; 41   : 
; 42   : 
; 43   : 		//! started ?
; 44   : 		if (op->stat &XHCI_STAT_HCHALTED) {

	mov	rax, QWORD PTR op$[rsp]
	mov	eax, DWORD PTR [rax+4]
	and	eax, 1
	test	eax, eax
	je	SHORT $LN13@xhci_start

; 45   : 			printf ("USB: error! couldn't clear controller halted bit\n");

	lea	rcx, OFFSET FLAT:$SG3350
	call	?printf@@YAXPEBDZZ			; printf

; 46   : 			return;

	jmp	$LN19@xhci_start
$LN13@xhci_start:

; 47   : 		}
; 48   : 	} else {

	jmp	$LN12@xhci_start
$LN18@xhci_start:

; 49   : 		//! stop the controller
; 50   : 		if (op->cmdrctrlLo & XHCI_CRCR_CMDRNGRUNNING) {

	mov	rax, QWORD PTR op$[rsp]
	mov	eax, DWORD PTR [rax+24]
	and	eax, 8
	test	eax, eax
	je	$LN11@xhci_start

; 51   : 			printf ("USB: XHCI stopping command ring\n");

	lea	rcx, OFFSET FLAT:$SG3353
	call	?printf@@YAXPEBDZZ			; printf

; 52   : 			op->cmdrctrlLo = XHCI_CRCR_COMMANDABORT;

	mov	rax, QWORD PTR op$[rsp]
	mov	DWORD PTR [rax+24], 4

; 53   : 			op->cmdrctrlHi = 0;

	mov	rax, QWORD PTR op$[rsp]
	mov	DWORD PTR [rax+28], 0

; 54   : 
; 55   : 			//!wait for stopped
; 56   : 			for (count = 0; count < 5000; count++) {

	mov	DWORD PTR count$[rsp], 0
	jmp	SHORT $LN10@xhci_start
$LN9@xhci_start:
	mov	eax, DWORD PTR count$[rsp]
	inc	eax
	mov	DWORD PTR count$[rsp], eax
$LN10@xhci_start:
	cmp	DWORD PTR count$[rsp], 5000		; 00001388H
	jge	SHORT $LN8@xhci_start

; 57   : 				if (!(op->cmdrctrlLo & XHCI_CRCR_CMDRNGRUNNING)) {

	mov	rax, QWORD PTR op$[rsp]
	mov	eax, DWORD PTR [rax+24]
	and	eax, 8
	test	eax, eax
	jne	SHORT $LN7@xhci_start

; 58   : 					printf ("USB: xHCI stopping ring took %d ms\n", count);

	mov	edx, DWORD PTR count$[rsp]
	lea	rcx, OFFSET FLAT:$SG3358
	call	?printf@@YAXPEBDZZ			; printf

; 59   : 					break;

	jmp	SHORT $LN8@xhci_start
$LN7@xhci_start:

; 60   : 				}
; 61   : 			}

	jmp	SHORT $LN9@xhci_start
$LN8@xhci_start:

; 62   : 
; 63   : 			//! stopped
; 64   : 			if (op->cmdrctrlLo & XHCI_CRCR_CMDRNGRUNNING)

	mov	rax, QWORD PTR op$[rsp]
	mov	eax, DWORD PTR [rax+24]
	and	eax, 8
	test	eax, eax
	je	SHORT $LN6@xhci_start

; 65   : 				printf ("USB: xHCI couldn't stop command ring\n");

	lea	rcx, OFFSET FLAT:$SG3360
	call	?printf@@YAXPEBDZZ			; printf
$LN6@xhci_start:
$LN11@xhci_start:

; 66   : 		}
; 67   : 
; 68   : 		//! clear the run/stop bit
; 69   : 		op->cmd &= ~XHCI_CMD_RUNSTOP;

	mov	rax, QWORD PTR op$[rsp]
	mov	eax, DWORD PTR [rax]
	and	eax, -2					; fffffffeH
	mov	rcx, QWORD PTR op$[rsp]
	mov	DWORD PTR [rcx], eax

; 70   : 
; 71   : 		//!wait for halted
; 72   : 		for (count = 0; count < 20; count++) {

	mov	DWORD PTR count$[rsp], 0
	jmp	SHORT $LN5@xhci_start
$LN4@xhci_start:
	mov	eax, DWORD PTR count$[rsp]
	inc	eax
	mov	DWORD PTR count$[rsp], eax
$LN5@xhci_start:
	cmp	DWORD PTR count$[rsp], 20
	jge	SHORT $LN3@xhci_start

; 73   : 			if (op->stat & XHCI_STAT_HCHALTED) {

	mov	rax, QWORD PTR op$[rsp]
	mov	eax, DWORD PTR [rax+4]
	and	eax, 1
	test	eax, eax
	je	SHORT $LN2@xhci_start

; 74   : 				printf ("USB: xHCI stopping controller took %d ms\n", count);

	mov	edx, DWORD PTR count$[rsp]
	lea	rcx, OFFSET FLAT:$SG3365
	call	?printf@@YAXPEBDZZ			; printf

; 75   : 				break;

	jmp	SHORT $LN3@xhci_start
$LN2@xhci_start:

; 76   : 			}
; 77   : 		}

	jmp	SHORT $LN4@xhci_start
$LN3@xhci_start:

; 78   : 
; 79   : 			//! stopped?
; 80   : 		if (!(op->stat & XHCI_STAT_HCHALTED)){

	mov	rax, QWORD PTR op$[rsp]
	mov	eax, DWORD PTR [rax+4]
	and	eax, 1
	test	eax, eax
	jne	SHORT $LN1@xhci_start

; 81   : 			printf ("USB: xHCI couldn't set controller halted bit\n");

	lea	rcx, OFFSET FLAT:$SG3367
	call	?printf@@YAXPEBDZZ			; printf

; 82   : 			return;

	jmp	SHORT $LN19@xhci_start
$LN1@xhci_start:
$LN12@xhci_start:

; 83   : 		}
; 84   : 	}
; 85   : 
; 86   : 	//!successfull
; 87   : 	printf ("USB: xHCI controller reset completed \n");

	lea	rcx, OFFSET FLAT:$SG3368
	call	?printf@@YAXPEBDZZ			; printf
$LN19@xhci_start:

; 88   : }

	add	rsp, 56					; 00000038H
	ret	0
?xhci_start_stop@@YAXH@Z ENDP				; xhci_start_stop
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\usb\xhci.cpp
_TEXT	SEGMENT
v$ = 48
p$ = 56
?xhci_handler@@YAX_KPEAX@Z PROC				; xhci_handler

; 20   : void xhci_handler (size_t v, void* p) {

$LN3:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 21   : 	printf ("[XHCI USB]: Interrupt fired\n");

	lea	rcx, OFFSET FLAT:$SG3336
	call	?printf@@YAXPEBDZZ			; printf

; 22   : }

	add	rsp, 40					; 00000028H
	ret	0
?xhci_handler@@YAX_KPEAX@Z ENDP				; xhci_handler
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\usb\xhci.cpp
_TEXT	SEGMENT
pci_status$ = 48
func_$ = 52
dev_$ = 56
bus$ = 60
version$ = 64
cap$ = 72
dev$ = 80
?xhci_initialize@@YAXXZ PROC				; xhci_initialize

; 122  : void xhci_initialize () {

$LN5:
	sub	rsp, 104				; 00000068H

; 123  : 	pci_device_info *dev = (pci_device_info*)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR dev$[rsp], rax

; 124  : 	xusb_dev = (xhci*)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR ?xusb_dev@@3PEAU_xhci_@@EA, rax ; xusb_dev

; 125  : 
; 126  : 	int bus, dev_, func_ = 0;

	mov	DWORD PTR func_$[rsp], 0

; 127  : 	if (!pci_find_device_class(0x0C, 0x03, dev, &bus, &dev_, &func_)) {

	lea	rax, QWORD PTR func_$[rsp]
	mov	QWORD PTR [rsp+40], rax
	lea	rax, QWORD PTR dev_$[rsp]
	mov	QWORD PTR [rsp+32], rax
	lea	r9, QWORD PTR bus$[rsp]
	mov	r8, QWORD PTR dev$[rsp]
	mov	dl, 3
	mov	cl, 12
	call	?pci_find_device_class@@YA_NEEPEATpci_device_info@@PEAH11@Z ; pci_find_device_class
	movzx	eax, al
	test	eax, eax
	jne	SHORT $LN2@xhci_initi

; 128  : 		printf ("USB xHCI: not found\n");

	lea	rcx, OFFSET FLAT:$SG3391
	call	?printf@@YAXPEBDZZ			; printf

; 129  : 		return;

	jmp	$LN3@xhci_initi
$LN2@xhci_initi:

; 130  : 	}
; 131  : 
; 132  : 	x64_cli ();

	call	x64_cli

; 133  : 	pci_enable_bus_master (bus, dev_, func_);

	mov	r8d, DWORD PTR func_$[rsp]
	mov	edx, DWORD PTR dev_$[rsp]
	mov	ecx, DWORD PTR bus$[rsp]
	call	?pci_enable_bus_master@@YAXHHH@Z	; pci_enable_bus_master

; 134  : 	printf ("Scanning MSI support for USB\n");

	lea	rcx, OFFSET FLAT:$SG3392
	call	?printf@@YAXPEBDZZ			; printf

; 135  : 	bool pci_status = pci_alloc_msi(func_, dev_, bus, xhci_handler);

	lea	r9, OFFSET FLAT:?xhci_handler@@YAX_KPEAX@Z ; xhci_handler
	mov	r8d, DWORD PTR bus$[rsp]
	mov	edx, DWORD PTR dev_$[rsp]
	mov	ecx, DWORD PTR func_$[rsp]
	call	?pci_alloc_msi@@YA_NHHHP6AX_KPEAX@Z@Z	; pci_alloc_msi
	mov	BYTE PTR pci_status$[rsp], al

; 136  : 	if (!pci_status) {

	movzx	eax, BYTE PTR pci_status$[rsp]
	test	eax, eax
	jne	SHORT $LN1@xhci_initi

; 137  : 		printf ("Legacy Interrupt handling for USB xhci is not supported\n");

	lea	rcx, OFFSET FLAT:$SG3395
	call	?printf@@YAXPEBDZZ			; printf
$LN1@xhci_initi:

; 138  : 	}
; 139  : 
; 140  : 	pci_enable_bus_master (bus, dev_, func_);

	mov	r8d, DWORD PTR func_$[rsp]
	mov	edx, DWORD PTR dev_$[rsp]
	mov	ecx, DWORD PTR bus$[rsp]
	call	?pci_enable_bus_master@@YAXHHH@Z	; pci_enable_bus_master

; 141  : 	xusb_dev->xhci_base_address = dev->device.nonBridge.baseAddress[0] +dev->device.nonBridge.baseAddress[1];

	mov	eax, 4
	imul	rax, 0
	mov	ecx, 4
	imul	rcx, 1
	mov	rdx, QWORD PTR dev$[rsp]
	mov	eax, DWORD PTR [rdx+rax+16]
	mov	rdx, QWORD PTR dev$[rsp]
	add	eax, DWORD PTR [rdx+rcx+16]
	mov	eax, eax
	mov	rcx, QWORD PTR ?xusb_dev@@3PEAU_xhci_@@EA ; xusb_dev
	mov	QWORD PTR [rcx], rax

; 142  : 
; 143  : 	xhci_cap_reg *cap = (xhci_cap_reg*)xusb_dev->xhci_base_address;

	mov	rax, QWORD PTR ?xusb_dev@@3PEAU_xhci_@@EA ; xusb_dev
	mov	rax, QWORD PTR [rax]
	mov	QWORD PTR cap$[rsp], rax

; 144  :     uint32_t version = cap->caps_len_hciver >> 16;

	mov	rax, QWORD PTR cap$[rsp]
	mov	eax, DWORD PTR [rax]
	shr	eax, 16
	mov	DWORD PTR version$[rsp], eax

; 145  : 	printf ("USB: xHCI version - (%d.%d%d)\n",((version >> 8) & 0xFF), ((version>>4) & 0xF), (version & 0xF));

	mov	eax, DWORD PTR version$[rsp]
	and	eax, 15
	mov	ecx, DWORD PTR version$[rsp]
	shr	ecx, 4
	and	ecx, 15
	mov	edx, DWORD PTR version$[rsp]
	shr	edx, 8
	and	edx, 255				; 000000ffH
	mov	r9d, eax
	mov	r8d, ecx
	lea	rcx, OFFSET FLAT:$SG3399
	call	?printf@@YAXPEBDZZ			; printf

; 146  : 
; 147  : 	xusb_dev->xhci_op_address = ((size_t)cap + (cap->caps_len_hciver & 0xFF));

	mov	rax, QWORD PTR cap$[rsp]
	mov	eax, DWORD PTR [rax]
	and	eax, 255				; 000000ffH
	mov	eax, eax
	mov	rcx, QWORD PTR cap$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	rcx, QWORD PTR ?xusb_dev@@3PEAU_xhci_@@EA ; xusb_dev
	mov	QWORD PTR [rcx+8], rax

; 148  : 	xusb_dev->doorbell_address = ((size_t)cap + (cap->dboffset & ~0x3UL));

	mov	rax, QWORD PTR cap$[rsp]
	mov	eax, DWORD PTR [rax+20]
	and	eax, -4					; fffffffcH
	mov	eax, eax
	mov	rcx, QWORD PTR cap$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	rcx, QWORD PTR ?xusb_dev@@3PEAU_xhci_@@EA ; xusb_dev
	mov	QWORD PTR [rcx+16], rax

; 149  : 	xusb_dev->runtime_address = ((size_t)cap + (cap->runtime_offset & ~0x1FUL));

	mov	rax, QWORD PTR cap$[rsp]
	mov	eax, DWORD PTR [rax+24]
	and	eax, -32				; ffffffe0H
	mov	eax, eax
	mov	rcx, QWORD PTR cap$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	rcx, QWORD PTR ?xusb_dev@@3PEAU_xhci_@@EA ; xusb_dev
	mov	QWORD PTR [rcx+24], rax

; 150  : 
; 151  : 	/**if (dev->device.nonBridge.interruptLine != 255)
; 152  : 		interrupt_set (dev->device.nonBridge.interruptLine, xhci_handler, dev->device.nonBridge.interruptLine);**/
; 153  : 
; 154  : 	printf ("USB: xHCI interrupt line -> %d\n", dev->device.nonBridge.interruptLine);

	mov	rax, QWORD PTR dev$[rsp]
	movzx	eax, BYTE PTR [rax+60]
	mov	edx, eax
	lea	rcx, OFFSET FLAT:$SG3403
	call	?printf@@YAXPEBDZZ			; printf

; 155  : 	printf ("USB: xHCI interrupt pin -> %d\n", dev->device.nonBridge.interruptPin);

	mov	rax, QWORD PTR dev$[rsp]
	movzx	eax, BYTE PTR [rax+61]
	mov	edx, eax
	lea	rcx, OFFSET FLAT:$SG3404
	call	?printf@@YAXPEBDZZ			; printf

; 156  : 	reset ();

	call	?reset@@YAXXZ				; reset

; 157  : 	x64_sti();

	call	x64_sti
$LN3@xhci_initi:

; 158  : 	//for(;;);
; 159  : }

	add	rsp, 104				; 00000068H
	ret	0
?xhci_initialize@@YAXXZ ENDP				; xhci_initialize
_TEXT	ENDS
END
