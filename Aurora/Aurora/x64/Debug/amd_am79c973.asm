; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?amd_io_base@@3_KA				; amd_io_base
PUBLIC	?amd_mac@@3PAEA					; amd_mac
PUBLIC	?amd_irq@@3IA					; amd_irq
PUBLIC	?a_card_net@@3PEAU_amd_net_@@EA			; a_card_net
_BSS	SEGMENT
?amd_io_base@@3_KA DQ 01H DUP (?)			; amd_io_base
?amd_mac@@3PAEA DB 06H DUP (?)				; amd_mac
	ALIGN	4

?amd_irq@@3IA DD 01H DUP (?)				; amd_irq
	ALIGN	8

?a_card_net@@3PEAU_amd_net_@@EA DQ 01H DUP (?)		; a_card_net
_BSS	ENDS
CONST	SEGMENT
$SG3310	DB	'AMD NIC Interrupt handler++', 0aH, 00H
	ORG $+3
$SG3320	DB	'AMD PCNet card not found', 0aH, 00H
	ORG $+2
$SG3356	DB	'%x', 00H
	ORG $+1
$SG3321	DB	'AMD Interrupt pin -> %x', 0aH, 00H
	ORG $+3
$SG3357	DB	0aH, 00H
	ORG $+2
$SG3322	DB	'AMD PCNet card found -> device id -> %x, vendor id -> %x'
	DB	0aH, 00H
	ORG $+6
$SG3323	DB	'AMD Base Address -> %x, -> %x', 0aH, 00H
	ORG $+1
$SG3324	DB	'AMD Interrupt line -> %d', 0aH, 00H
	ORG $+6
$SG3351	DB	'AMD Mac Code -> ', 00H
	ORG $+7
$SG3360	DB	'MSI for amd not found', 0aH, 00H
CONST	ENDS
PUBLIC	?amd_pcnet_initialize@@YAXXZ			; amd_pcnet_initialize
PUBLIC	?amd_write_bcr@@YAXGG@Z				; amd_write_bcr
PUBLIC	?amd_write_csr@@YAXEG@Z				; amd_write_csr
PUBLIC	?amd_read_csr@@YAGE@Z				; amd_read_csr
PUBLIC	?amd_interrupt_handler@@YAX_KPEAX@Z		; amd_interrupt_handler
EXTRN	x64_cli:PROC
EXTRN	x64_sti:PROC
EXTRN	x64_inportw:PROC
EXTRN	x64_outportw:PROC
EXTRN	?interrupt_end@@YAXI@Z:PROC			; interrupt_end
EXTRN	?interrupt_set@@YAX_KP6AX0PEAX@ZE@Z:PROC	; interrupt_set
EXTRN	?pci_find_device_class@@YA_NEEPEATpci_device_info@@PEAH11@Z:PROC ; pci_find_device_class
EXTRN	?pci_alloc_msi@@YA_NHHHP6AX_KPEAX@Z@Z:PROC	; pci_alloc_msi
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	?memset@@YAXPEAXEI@Z:PROC			; memset
EXTRN	memcpy:PROC
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
pdata	SEGMENT
$pdata$?amd_pcnet_initialize@@YAXXZ DD imagerel $LN14
	DD	imagerel $LN14+1398
	DD	imagerel $unwind$?amd_pcnet_initialize@@YAXXZ
$pdata$?amd_write_bcr@@YAXGG@Z DD imagerel $LN3
	DD	imagerel $LN3+67
	DD	imagerel $unwind$?amd_write_bcr@@YAXGG@Z
$pdata$?amd_write_csr@@YAXEG@Z DD imagerel $LN3
	DD	imagerel $LN3+66
	DD	imagerel $unwind$?amd_write_csr@@YAXEG@Z
$pdata$?amd_read_csr@@YAGE@Z DD imagerel $LN3
	DD	imagerel $LN3+56
	DD	imagerel $unwind$?amd_read_csr@@YAGE@Z
$pdata$?amd_interrupt_handler@@YAX_KPEAX@Z DD imagerel $LN3
	DD	imagerel $LN3+42
	DD	imagerel $unwind$?amd_interrupt_handler@@YAX_KPEAX@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?amd_pcnet_initialize@@YAXXZ DD 020701H
	DD	0110107H
$unwind$?amd_write_bcr@@YAXGG@Z DD 010e01H
	DD	0420eH
$unwind$?amd_write_csr@@YAXEG@Z DD 010d01H
	DD	0420dH
$unwind$?amd_read_csr@@YAGE@Z DD 010801H
	DD	04208H
$unwind$?amd_interrupt_handler@@YAX_KPEAX@Z DD 010e01H
	DD	0420eH
xdata	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\drivers\net\amd_am79c973.cpp
_TEXT	SEGMENT
v$ = 48
p$ = 56
?amd_interrupt_handler@@YAX_KPEAX@Z PROC		; amd_interrupt_handler

; 39   : void amd_interrupt_handler (size_t v, void* p) {

$LN3:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 40   : 	printf ("AMD NIC Interrupt handler++\n");

	lea	rcx, OFFSET FLAT:$SG3310
	call	?printf@@YAXPEBDZZ			; printf

; 41   : 	//apic_local_eoi();
; 42   : 	interrupt_end(amd_irq);

	mov	ecx, DWORD PTR ?amd_irq@@3IA		; amd_irq
	call	?interrupt_end@@YAXI@Z			; interrupt_end

; 43   : }

	add	rsp, 40					; 00000028H
	ret	0
?amd_interrupt_handler@@YAX_KPEAX@Z ENDP		; amd_interrupt_handler
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\drivers\net\amd_am79c973.cpp
_TEXT	SEGMENT
csr$ = 48
?amd_read_csr@@YAGE@Z PROC				; amd_read_csr

; 33   : uint16_t amd_read_csr (uint8_t csr) {

$LN3:
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 40					; 00000028H

; 34   : 	x64_outportw (amd_io_base + RAP, csr);

	movzx	eax, BYTE PTR csr$[rsp]
	mov	rcx, QWORD PTR ?amd_io_base@@3_KA	; amd_io_base
	add	rcx, 18
	movzx	edx, ax
	call	x64_outportw

; 35   : 	return x64_inportw (amd_io_base+RDP);

	mov	rax, QWORD PTR ?amd_io_base@@3_KA	; amd_io_base
	add	rax, 16
	movzx	ecx, ax
	call	x64_inportw

; 36   : }

	add	rsp, 40					; 00000028H
	ret	0
?amd_read_csr@@YAGE@Z ENDP				; amd_read_csr
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\drivers\net\amd_am79c973.cpp
_TEXT	SEGMENT
csr$ = 48
value$ = 56
?amd_write_csr@@YAXEG@Z PROC				; amd_write_csr

; 28   : void amd_write_csr (uint8_t csr, uint16_t value) {

$LN3:
	mov	WORD PTR [rsp+16], dx
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 40					; 00000028H

; 29   : 	x64_outportw (amd_io_base + RAP, csr);

	movzx	eax, BYTE PTR csr$[rsp]
	mov	rcx, QWORD PTR ?amd_io_base@@3_KA	; amd_io_base
	add	rcx, 18
	movzx	edx, ax
	call	x64_outportw

; 30   : 	x64_outportw (amd_io_base + RDP, value);

	mov	rax, QWORD PTR ?amd_io_base@@3_KA	; amd_io_base
	add	rax, 16
	movzx	edx, WORD PTR value$[rsp]
	movzx	ecx, ax
	call	x64_outportw

; 31   : }

	add	rsp, 40					; 00000028H
	ret	0
?amd_write_csr@@YAXEG@Z ENDP				; amd_write_csr
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\drivers\net\amd_am79c973.cpp
_TEXT	SEGMENT
bcr$ = 48
value$ = 56
?amd_write_bcr@@YAXGG@Z PROC				; amd_write_bcr

; 23   : void amd_write_bcr (uint16_t bcr, uint16_t value) {

$LN3:
	mov	WORD PTR [rsp+16], dx
	mov	WORD PTR [rsp+8], cx
	sub	rsp, 40					; 00000028H

; 24   : 	x64_outportw (amd_io_base + RAP, bcr);

	mov	rax, QWORD PTR ?amd_io_base@@3_KA	; amd_io_base
	add	rax, 18
	movzx	edx, WORD PTR bcr$[rsp]
	movzx	ecx, ax
	call	x64_outportw

; 25   : 	x64_outportw (amd_io_base + 0x16, value);

	mov	rax, QWORD PTR ?amd_io_base@@3_KA	; amd_io_base
	add	rax, 22
	movzx	edx, WORD PTR value$[rsp]
	movzx	ecx, ax
	call	x64_outportw

; 26   : }

	add	rsp, 40					; 00000028H
	ret	0
?amd_write_bcr@@YAXGG@Z ENDP				; amd_write_bcr
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\drivers\net\amd_am79c973.cpp
_TEXT	SEGMENT
i$1 = 48
temp$ = 52
pci_status$ = 56
dev$ = 64
init_block$ = 72
i$2 = 80
i$3 = 84
func_$ = 88
dev_$ = 92
rx_buffer$ = 96
bus$ = 104
tx_buffer$ = 112
?amd_pcnet_initialize@@YAXXZ PROC			; amd_pcnet_initialize

; 45   : void amd_pcnet_initialize () {

$LN14:
	sub	rsp, 136				; 00000088H

; 46   : 	pci_device_info *dev = (pci_device_info*)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR dev$[rsp], rax

; 47   : 	a_card_net = (amd_net*)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR ?a_card_net@@3PEAU_amd_net_@@EA, rax ; a_card_net

; 48   : 	//x64_outportw (dev->device.commandReg, ~(1 << 10));
; 49   : 	x64_cli();

	call	x64_cli

; 50   : 	int bus,dev_, func_ = 0;

	mov	DWORD PTR func_$[rsp], 0

; 51   : 	if (!pci_find_device_class (0x02,0x00,dev, &bus, &dev_, &func_)) {

	lea	rax, QWORD PTR func_$[rsp]
	mov	QWORD PTR [rsp+40], rax
	lea	rax, QWORD PTR dev_$[rsp]
	mov	QWORD PTR [rsp+32], rax
	lea	r9, QWORD PTR bus$[rsp]
	mov	r8, QWORD PTR dev$[rsp]
	xor	edx, edx
	mov	cl, 2
	call	?pci_find_device_class@@YA_NEEPEATpci_device_info@@PEAH11@Z ; pci_find_device_class
	movzx	eax, al
	test	eax, eax
	jne	SHORT $LN11@amd_pcnet_

; 52   : 		printf ("AMD PCNet card not found\n");

	lea	rcx, OFFSET FLAT:$SG3320
	call	?printf@@YAXPEBDZZ			; printf

; 53   : 		return;

	jmp	$LN12@amd_pcnet_
$LN11@amd_pcnet_:

; 54   : 	}
; 55   : 	printf ("AMD Interrupt pin -> %x\n", dev->device.nonBridge.interruptPin);

	mov	rax, QWORD PTR dev$[rsp]
	movzx	eax, BYTE PTR [rax+61]
	mov	edx, eax
	lea	rcx, OFFSET FLAT:$SG3321
	call	?printf@@YAXPEBDZZ			; printf

; 56   : 	amd_io_base = dev->device.nonBridge.baseAddress[0];

	mov	eax, 4
	imul	rax, 0
	mov	rcx, QWORD PTR dev$[rsp]
	mov	eax, DWORD PTR [rcx+rax+16]
	mov	QWORD PTR ?amd_io_base@@3_KA, rax	; amd_io_base

; 57   : 	printf ("AMD PCNet card found -> device id -> %x, vendor id -> %x\n", dev->device.deviceID, dev->device.vendorID);

	mov	rax, QWORD PTR dev$[rsp]
	movzx	eax, WORD PTR [rax]
	mov	rcx, QWORD PTR dev$[rsp]
	movzx	ecx, WORD PTR [rcx+2]
	mov	r8d, eax
	mov	edx, ecx
	lea	rcx, OFFSET FLAT:$SG3322
	call	?printf@@YAXPEBDZZ			; printf

; 58   : 	printf ("AMD Base Address -> %x, -> %x\n", dev->device.nonBridge.baseAddress[0], dev->device.nonBridge.baseAddress[6]);

	mov	eax, 4
	imul	rax, 6
	mov	ecx, 4
	imul	rcx, 0
	mov	rdx, QWORD PTR dev$[rsp]
	mov	r8d, DWORD PTR [rdx+rax+16]
	mov	rax, QWORD PTR dev$[rsp]
	mov	edx, DWORD PTR [rax+rcx+16]
	lea	rcx, OFFSET FLAT:$SG3323
	call	?printf@@YAXPEBDZZ			; printf

; 59   : 	printf ("AMD Interrupt line -> %d\n", dev->device.bridge.interruptLine);

	mov	rax, QWORD PTR dev$[rsp]
	movzx	eax, BYTE PTR [rax+60]
	mov	edx, eax
	lea	rcx, OFFSET FLAT:$SG3324
	call	?printf@@YAXPEBDZZ			; printf

; 60   : 
; 61   : 	amd_irq = dev->device.nonBridge.interruptLine;

	mov	rax, QWORD PTR dev$[rsp]
	movzx	eax, BYTE PTR [rax+60]
	mov	DWORD PTR ?amd_irq@@3IA, eax		; amd_irq

; 62   : 	//pci_print_capabilities(func_,dev_,bus);
; 63   : 
; 64   : 	
; 65   : 
; 66   : 	uint16_t temp = x64_inportw (amd_io_base + APROM0);

	movzx	ecx, WORD PTR ?amd_io_base@@3_KA
	call	x64_inportw
	mov	WORD PTR temp$[rsp], ax

; 67   : 	amd_mac[0] = temp;

	mov	eax, 1
	imul	rax, 0
	lea	rcx, OFFSET FLAT:?amd_mac@@3PAEA	; amd_mac
	movzx	edx, BYTE PTR temp$[rsp]
	mov	BYTE PTR [rcx+rax], dl

; 68   : 	amd_mac[1] = temp >> 8;

	movzx	eax, WORD PTR temp$[rsp]
	sar	eax, 8
	mov	ecx, 1
	imul	rcx, 1
	lea	rdx, OFFSET FLAT:?amd_mac@@3PAEA	; amd_mac
	mov	BYTE PTR [rdx+rcx], al

; 69   : 	temp = x64_inportw (amd_io_base + APROM2);

	mov	rax, QWORD PTR ?amd_io_base@@3_KA	; amd_io_base
	add	rax, 2
	movzx	ecx, ax
	call	x64_inportw
	mov	WORD PTR temp$[rsp], ax

; 70   : 	amd_mac[2] = temp;

	mov	eax, 1
	imul	rax, 2
	lea	rcx, OFFSET FLAT:?amd_mac@@3PAEA	; amd_mac
	movzx	edx, BYTE PTR temp$[rsp]
	mov	BYTE PTR [rcx+rax], dl

; 71   : 	amd_mac[3] = temp >> 8;

	movzx	eax, WORD PTR temp$[rsp]
	sar	eax, 8
	mov	ecx, 1
	imul	rcx, 3
	lea	rdx, OFFSET FLAT:?amd_mac@@3PAEA	; amd_mac
	mov	BYTE PTR [rdx+rcx], al

; 72   : 	temp = x64_inportw(amd_io_base + APROM4);

	mov	rax, QWORD PTR ?amd_io_base@@3_KA	; amd_io_base
	add	rax, 4
	movzx	ecx, ax
	call	x64_inportw
	mov	WORD PTR temp$[rsp], ax

; 73   : 	amd_mac[4] = temp;

	mov	eax, 1
	imul	rax, 4
	lea	rcx, OFFSET FLAT:?amd_mac@@3PAEA	; amd_mac
	movzx	edx, BYTE PTR temp$[rsp]
	mov	BYTE PTR [rcx+rax], dl

; 74   : 	amd_mac[5] = temp>>8;

	movzx	eax, WORD PTR temp$[rsp]
	sar	eax, 8
	mov	ecx, 1
	imul	rcx, 5
	lea	rdx, OFFSET FLAT:?amd_mac@@3PAEA	; amd_mac
	mov	BYTE PTR [rdx+rcx], al

; 75   : 
; 76   : 
; 77   : 	x64_inportw (amd_io_base + RESET);

	mov	rax, QWORD PTR ?amd_io_base@@3_KA	; amd_io_base
	add	rax, 20
	movzx	ecx, ax
	call	x64_inportw

; 78   : 	x64_outportw (amd_io_base + RESET, 0);

	mov	rax, QWORD PTR ?amd_io_base@@3_KA	; amd_io_base
	add	rax, 20
	xor	edx, edx
	movzx	ecx, ax
	call	x64_outportw

; 79   : 	for (int i = 0; i < 20; i++)

	mov	DWORD PTR i$3[rsp], 0
	jmp	SHORT $LN10@amd_pcnet_
$LN9@amd_pcnet_:
	mov	eax, DWORD PTR i$3[rsp]
	inc	eax
	mov	DWORD PTR i$3[rsp], eax
$LN10@amd_pcnet_:
	cmp	DWORD PTR i$3[rsp], 20
	jge	SHORT $LN8@amd_pcnet_

; 80   : 		;

	jmp	SHORT $LN9@amd_pcnet_
$LN8@amd_pcnet_:

; 81   : 	
; 82   : 	amd_write_bcr(20,0x102);//amd_write_csr (20,0x0102);

	mov	dx, 258					; 00000102H
	mov	cx, 20
	call	?amd_write_bcr@@YAXGG@Z			; amd_write_bcr

; 83   : 
; 84   : 	//!stop
; 85   : 	amd_write_csr (0, 0x04);

	mov	dx, 4
	xor	ecx, ecx
	call	?amd_write_csr@@YAXEG@Z			; amd_write_csr

; 86   : 
; 87   : 
; 88   : 	uint32_t* rx_buffer = (uint32_t*)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR rx_buffer$[rsp], rax

; 89   : 	uint32_t* tx_buffer = rx_buffer + 2048;

	mov	rax, QWORD PTR rx_buffer$[rsp]
	add	rax, 8192				; 00002000H
	mov	QWORD PTR tx_buffer$[rsp], rax

; 90   : 	
; 91   : 	a_card_net->recv_desc = (amd_descriptor*)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	rcx, QWORD PTR ?a_card_net@@3PEAU_amd_net_@@EA ; a_card_net
	mov	QWORD PTR [rcx+8], rax

; 92   : 	a_card_net->trans_desc = (amd_descriptor*)(a_card_net->recv_desc + sizeof(amd_descriptor));

	mov	rax, QWORD PTR ?a_card_net@@3PEAU_amd_net_@@EA ; a_card_net
	mov	rax, QWORD PTR [rax+8]
	add	rax, 256				; 00000100H
	mov	rcx, QWORD PTR ?a_card_net@@3PEAU_amd_net_@@EA ; a_card_net
	mov	QWORD PTR [rcx], rax

; 93   : 
; 94   : 	for (uint8_t i = 0; i < 8; i++) {

	mov	BYTE PTR i$1[rsp], 0
	jmp	SHORT $LN7@amd_pcnet_
$LN6@amd_pcnet_:
	movzx	eax, BYTE PTR i$1[rsp]
	inc	al
	mov	BYTE PTR i$1[rsp], al
$LN7@amd_pcnet_:
	movzx	eax, BYTE PTR i$1[rsp]
	cmp	eax, 8
	jge	$LN5@amd_pcnet_

; 95   : 		a_card_net->recv_desc[i].address = (uint32_t)rx_buffer + i * 2048;

	movzx	eax, BYTE PTR i$1[rsp]
	imul	eax, 2048				; 00000800H
	mov	ecx, DWORD PTR rx_buffer$[rsp]
	add	ecx, eax
	mov	eax, ecx
	movzx	ecx, BYTE PTR i$1[rsp]
	imul	rcx, 16
	mov	rdx, QWORD PTR ?a_card_net@@3PEAU_amd_net_@@EA ; a_card_net
	mov	rdx, QWORD PTR [rdx+8]
	mov	DWORD PTR [rdx+rcx], eax

; 96   : 		a_card_net->recv_desc[i].flags = 0x80000000 | 0x0000F000 | (-2048 & 0xFFF);

	movzx	eax, BYTE PTR i$1[rsp]
	imul	rax, 16
	mov	rcx, QWORD PTR ?a_card_net@@3PEAU_amd_net_@@EA ; a_card_net
	mov	rcx, QWORD PTR [rcx+8]
	mov	DWORD PTR [rcx+rax+4], -2147420160	; 8000f800H

; 97   : 		a_card_net->recv_desc[i].flags2 = 0;

	movzx	eax, BYTE PTR i$1[rsp]
	imul	rax, 16
	mov	rcx, QWORD PTR ?a_card_net@@3PEAU_amd_net_@@EA ; a_card_net
	mov	rcx, QWORD PTR [rcx+8]
	mov	DWORD PTR [rcx+rax+8], 0

; 98   : 		a_card_net->recv_desc[i].avail = (uint32_t)rx_buffer + i * 2048;

	movzx	eax, BYTE PTR i$1[rsp]
	imul	eax, 2048				; 00000800H
	mov	ecx, DWORD PTR rx_buffer$[rsp]
	add	ecx, eax
	mov	eax, ecx
	movzx	ecx, BYTE PTR i$1[rsp]
	imul	rcx, 16
	mov	rdx, QWORD PTR ?a_card_net@@3PEAU_amd_net_@@EA ; a_card_net
	mov	rdx, QWORD PTR [rdx+8]
	mov	DWORD PTR [rdx+rcx+12], eax

; 99   : 
; 100  : 		a_card_net->trans_desc[i].address = (uint32_t)tx_buffer+i*2048;

	movzx	eax, BYTE PTR i$1[rsp]
	imul	eax, 2048				; 00000800H
	mov	ecx, DWORD PTR tx_buffer$[rsp]
	add	ecx, eax
	mov	eax, ecx
	movzx	ecx, BYTE PTR i$1[rsp]
	imul	rcx, 16
	mov	rdx, QWORD PTR ?a_card_net@@3PEAU_amd_net_@@EA ; a_card_net
	mov	rdx, QWORD PTR [rdx]
	mov	DWORD PTR [rdx+rcx], eax

; 101  : 		a_card_net->trans_desc[i].flags = 0x0000F000;

	movzx	eax, BYTE PTR i$1[rsp]
	imul	rax, 16
	mov	rcx, QWORD PTR ?a_card_net@@3PEAU_amd_net_@@EA ; a_card_net
	mov	rcx, QWORD PTR [rcx]
	mov	DWORD PTR [rcx+rax+4], 61440		; 0000f000H

; 102  : 		a_card_net->trans_desc[i].flags2 = 0;

	movzx	eax, BYTE PTR i$1[rsp]
	imul	rax, 16
	mov	rcx, QWORD PTR ?a_card_net@@3PEAU_amd_net_@@EA ; a_card_net
	mov	rcx, QWORD PTR [rcx]
	mov	DWORD PTR [rcx+rax+8], 0

; 103  : 		a_card_net->trans_desc[i].avail = (uint32_t)tx_buffer+i*2048;

	movzx	eax, BYTE PTR i$1[rsp]
	imul	eax, 2048				; 00000800H
	mov	ecx, DWORD PTR tx_buffer$[rsp]
	add	ecx, eax
	mov	eax, ecx
	movzx	ecx, BYTE PTR i$1[rsp]
	imul	rcx, 16
	mov	rdx, QWORD PTR ?a_card_net@@3PEAU_amd_net_@@EA ; a_card_net
	mov	rdx, QWORD PTR [rdx]
	mov	DWORD PTR [rdx+rcx+12], eax

; 104  : 	}

	jmp	$LN6@amd_pcnet_
$LN5@amd_pcnet_:

; 105  : 
; 106  : 	amd_init_block *init_block = (amd_init_block*)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR init_block$[rsp], rax

; 107  : 	memset (init_block, 0, sizeof (amd_init_block));

	mov	r8d, 32					; 00000020H
	xor	edx, edx
	mov	rcx, QWORD PTR init_block$[rsp]
	call	?memset@@YAXPEAXEI@Z			; memset

; 108  : 	init_block->mode = 0x0180;

	mov	eax, 384				; 00000180H
	mov	rcx, QWORD PTR init_block$[rsp]
	mov	WORD PTR [rcx], ax

; 109  : 	init_block->receive_length = 3;

	mov	rax, QWORD PTR init_block$[rsp]
	mov	eax, DWORD PTR [rax+4]
	and	eax, -241				; ffffff0fH
	or	eax, 48					; 00000030H
	mov	rcx, QWORD PTR init_block$[rsp]
	mov	DWORD PTR [rcx+4], eax

; 110  : 	init_block->transfer_length = 3;

	mov	rax, QWORD PTR init_block$[rsp]
	mov	eax, DWORD PTR [rax+4]
	and	eax, -61441				; ffff0fffH
	or	eax, 12288				; 00003000H
	mov	rcx, QWORD PTR init_block$[rsp]
	mov	DWORD PTR [rcx+4], eax

; 111  : 	memcpy (&init_block->physical_address, amd_mac, 6);

	mov	rax, QWORD PTR init_block$[rsp]
	add	rax, 8
	mov	r8d, 6
	lea	rdx, OFFSET FLAT:?amd_mac@@3PAEA	; amd_mac
	mov	rcx, rax
	call	memcpy

; 112  : 	init_block->receive_descriptor = (uint32_t)a_card_net->recv_desc;

	mov	rax, QWORD PTR init_block$[rsp]
	mov	rcx, QWORD PTR ?a_card_net@@3PEAU_amd_net_@@EA ; a_card_net
	mov	ecx, DWORD PTR [rcx+8]
	mov	DWORD PTR [rax+24], ecx

; 113  : 	init_block->transmit_descriptor = (uint32_t)a_card_net->trans_desc;

	mov	rax, QWORD PTR init_block$[rsp]
	mov	rcx, QWORD PTR ?a_card_net@@3PEAU_amd_net_@@EA ; a_card_net
	mov	ecx, DWORD PTR [rcx]
	mov	DWORD PTR [rax+28], ecx

; 114  : 	amd_write_csr(1,(uint16_t)init_block);

	movzx	edx, WORD PTR init_block$[rsp]
	mov	cl, 1
	call	?amd_write_csr@@YAXEG@Z			; amd_write_csr

; 115  : 	amd_write_csr(2, (uint16_t)init_block >> 16);

	movzx	eax, WORD PTR init_block$[rsp]
	sar	eax, 16
	movzx	edx, ax
	mov	cl, 2
	call	?amd_write_csr@@YAXEG@Z			; amd_write_csr

; 116  : 	
; 117  : 
; 118  : 	printf ("AMD Mac Code -> ");

	lea	rcx, OFFSET FLAT:$SG3351
	call	?printf@@YAXPEBDZZ			; printf

; 119  : 	for (int i = 0; i < 6; i++)

	mov	DWORD PTR i$2[rsp], 0
	jmp	SHORT $LN4@amd_pcnet_
$LN3@amd_pcnet_:
	mov	eax, DWORD PTR i$2[rsp]
	inc	eax
	mov	DWORD PTR i$2[rsp], eax
$LN4@amd_pcnet_:
	cmp	DWORD PTR i$2[rsp], 6
	jge	SHORT $LN2@amd_pcnet_

; 120  : 		printf ("%x", amd_mac[i]);

	movsxd	rax, DWORD PTR i$2[rsp]
	lea	rcx, OFFSET FLAT:?amd_mac@@3PAEA	; amd_mac
	movzx	eax, BYTE PTR [rcx+rax]
	mov	edx, eax
	lea	rcx, OFFSET FLAT:$SG3356
	call	?printf@@YAXPEBDZZ			; printf
	jmp	SHORT $LN3@amd_pcnet_
$LN2@amd_pcnet_:

; 121  : 	printf ("\n");

	lea	rcx, OFFSET FLAT:$SG3357
	call	?printf@@YAXPEBDZZ			; printf

; 122  : 
; 123  : 	bool pci_status = pci_alloc_msi (func_, dev_, bus,amd_interrupt_handler);

	lea	r9, OFFSET FLAT:?amd_interrupt_handler@@YAX_KPEAX@Z ; amd_interrupt_handler
	mov	r8d, DWORD PTR bus$[rsp]
	mov	edx, DWORD PTR dev_$[rsp]
	mov	ecx, DWORD PTR func_$[rsp]
	call	?pci_alloc_msi@@YA_NHHHP6AX_KPEAX@Z@Z	; pci_alloc_msi
	mov	BYTE PTR pci_status$[rsp], al

; 124  : 	if (!pci_status) {

	movzx	eax, BYTE PTR pci_status$[rsp]
	test	eax, eax
	jne	SHORT $LN1@amd_pcnet_

; 125  : 		printf ("MSI for amd not found\n");

	lea	rcx, OFFSET FLAT:$SG3360
	call	?printf@@YAXPEBDZZ			; printf

; 126  : 		interrupt_set (dev->device.nonBridge.interruptLine, amd_interrupt_handler, dev->device.nonBridge.interruptLine);

	mov	rax, QWORD PTR dev$[rsp]
	movzx	eax, BYTE PTR [rax+60]
	mov	rcx, QWORD PTR dev$[rsp]
	movzx	r8d, BYTE PTR [rcx+60]
	lea	rdx, OFFSET FLAT:?amd_interrupt_handler@@YAX_KPEAX@Z ; amd_interrupt_handler
	mov	ecx, eax
	call	?interrupt_set@@YAX_KP6AX0PEAX@ZE@Z	; interrupt_set
$LN1@amd_pcnet_:

; 127  : 	}
; 128  : 	//!initialize
; 129  : 	amd_write_csr (0, 0x0041);

	mov	dx, 65					; 00000041H
	xor	ecx, ecx
	call	?amd_write_csr@@YAXEG@Z			; amd_write_csr

; 130  : 	amd_write_csr (0,amd_read_csr(0));

	xor	ecx, ecx
	call	?amd_read_csr@@YAGE@Z			; amd_read_csr
	movzx	edx, ax
	xor	ecx, ecx
	call	?amd_write_csr@@YAXEG@Z			; amd_write_csr

; 131  : 	amd_write_csr(4,0xC00 | amd_read_csr(4));

	mov	cl, 4
	call	?amd_read_csr@@YAGE@Z			; amd_read_csr
	movzx	eax, ax
	or	eax, 3072				; 00000c00H
	movzx	edx, ax
	mov	cl, 4
	call	?amd_write_csr@@YAXEG@Z			; amd_write_csr

; 132  : 	amd_write_csr (0,0x0042);

	mov	dx, 66					; 00000042H
	xor	ecx, ecx
	call	?amd_write_csr@@YAXEG@Z			; amd_write_csr

; 133  : 
; 134  : 
; 135  : 	
; 136  : 
; 137  : 	x64_sti();

	call	x64_sti
$LN12@amd_pcnet_:

; 138  : 	//pmmngr_free(init_block);
; 139  : }

	add	rsp, 136				; 00000088H
	ret	0
?amd_pcnet_initialize@@YAXXZ ENDP			; amd_pcnet_initialize
_TEXT	ENDS
END