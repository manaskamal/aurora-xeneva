; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?hbabar@@3PEAXEA				; hbabar
_BSS	SEGMENT
___ahci_64_bit___ DB 01H DUP (?)
	ALIGN	8

?hbabar@@3PEAXEA DQ 01H DUP (?)				; hbabar
_BSS	ENDS
CONST	SEGMENT
$SG3756	DB	'[AHCI]: Taking the control from firmware took %d ms', 0aH
	DB	00H
	ORG $+3
$SG3780	DB	'*******************************', 0aH, 00H
	ORG $+7
$SG3781	DB	'AHCI/SATA not found', 0aH, 00H
	ORG $+3
$SG3782	DB	'Xeneva initialisation failed', 0aH, 00H
	ORG $+2
$SG3783	DB	'Halting System', 0aH, 00H
$SG3784	DB	'*******************************', 0aH, 00H
	ORG $+7
$SG3798	DB	'[AHCI]: Version -- %d.%d', 0aH, 00H
	ORG $+6
$SG3801	DB	'[AHCI]: 64-bit DMA supported', 0aH, 00H
	ORG $+2
$SG3803	DB	'[AHCI]: Num Command Slots -> %d', 0aH, 00H
	ORG $+7
$SG3806	DB	'[AHCI]: Support Staggered spin-up %d', 0aH, 00H
	ORG $+2
$SG3808	DB	'[AHCI]: FIS-Based Switching supported', 0aH, 00H
	ORG $+1
$SG3817	DB	'[AHCI]: SATA Drive found at port %d', 0aH, 00H
	ORG $+3
$SG3820	DB	'[AHCI]: SATAPI Drive found at port %d', 0aH, 00H
	ORG $+1
$SG3823	DB	'[AHCI]: SEMB Drive found at port %d', 0aH, 00H
	ORG $+3
$SG3826	DB	'[AHCI]: PM Drive found at port %d', 0aH, 00H
CONST	ENDS
PUBLIC	?ahci_initialize@@YAXXZ				; ahci_initialize
PUBLIC	?ahci_is_64_bit_supported@@YA_NXZ		; ahci_is_64_bit_supported
PUBLIC	?ahci_check_type@@YAHPEAU_hba_port_@@@Z		; ahci_check_type
PUBLIC	?ahci_control_hand_os@@YAXPEAU_hba_mem_@@@Z	; ahci_control_hand_os
PUBLIC	?ahci_interrupt_handler@@YAX_KPEAX@Z		; ahci_interrupt_handler
EXTRN	?ahci_disk_initialize@@YAXPEAU_hba_port_@@@Z:PROC ; ahci_disk_initialize
EXTRN	pci_express_scan_class:PROC
EXTRN	pci_express_read:PROC
EXTRN	pci_express_write:PROC
EXTRN	pcie_alloc_msi:PROC
EXTRN	setvect:PROC
EXTRN	AuMapMMIO:PROC
EXTRN	?timer_sleep@@YAXI@Z:PROC			; timer_sleep
EXTRN	AuInterruptEnd:PROC
EXTRN	printf:PROC
EXTRN	_debug_print_:PROC
pdata	SEGMENT
$pdata$?ahci_initialize@@YAXXZ DD imagerel $LN21
	DD	imagerel $LN21+1130
	DD	imagerel $unwind$?ahci_initialize@@YAXXZ
$pdata$?ahci_check_type@@YAHPEAU_hba_port_@@@Z DD imagerel $LN11
	DD	imagerel $LN11+147
	DD	imagerel $unwind$?ahci_check_type@@YAHPEAU_hba_port_@@@Z
$pdata$?ahci_control_hand_os@@YAXPEAU_hba_mem_@@@Z DD imagerel $LN5
	DD	imagerel $LN5+90
	DD	imagerel $unwind$?ahci_control_hand_os@@YAXPEAU_hba_mem_@@@Z
$pdata$?ahci_interrupt_handler@@YAX_KPEAX@Z DD imagerel $LN7
	DD	imagerel $LN7+186
	DD	imagerel $unwind$?ahci_interrupt_handler@@YAX_KPEAX@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?ahci_initialize@@YAXXZ DD 020701H
	DD	0130107H
$unwind$?ahci_check_type@@YAHPEAU_hba_port_@@@Z DD 010901H
	DD	02209H
$unwind$?ahci_control_hand_os@@YAXPEAU_hba_mem_@@@Z DD 010901H
	DD	06209H
$unwind$?ahci_interrupt_handler@@YAX_KPEAX@Z DD 010e01H
	DD	0820eH
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\ahci.cpp
_TEXT	SEGMENT
i$1 = 32
port_is$2 = 36
is$ = 40
hba$ = 48
v$ = 80
p$ = 88
?ahci_interrupt_handler@@YAX_KPEAX@Z PROC		; ahci_interrupt_handler

; 101  : void ahci_interrupt_handler (size_t v, void* p) {

$LN7:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 102  : 	//x64_cli();
; 103  : 	HBA_MEM *hba = (HBA_MEM*)hbabar;

	mov	rax, QWORD PTR ?hbabar@@3PEAXEA		; hbabar
	mov	QWORD PTR hba$[rsp], rax

; 104  : 	uint32_t is = hba->is;

	mov	rax, QWORD PTR hba$[rsp]
	mov	eax, DWORD PTR [rax+8]
	mov	DWORD PTR is$[rsp], eax

; 105  : 	//_debug_print_ ("AHCI Interrupt handler \r\n");
; 106  : #if 0
; 107  : 	printf ("[AHCI]: Interrupt fired++\n");
; 108  : #endif
; 109  : 	for (int i = 0; i < 32; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN4@ahci_inter
$LN3@ahci_inter:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN4@ahci_inter:
	cmp	DWORD PTR i$1[rsp], 32			; 00000020H
	jge	SHORT $LN2@ahci_inter

; 110  : 		if ((hba->is & hba->pi & (1<<i))) {

	mov	rax, QWORD PTR hba$[rsp]
	mov	rcx, QWORD PTR hba$[rsp]
	mov	ecx, DWORD PTR [rcx+12]
	mov	eax, DWORD PTR [rax+8]
	and	eax, ecx
	mov	ecx, DWORD PTR i$1[rsp]
	mov	edx, 1
	shl	edx, cl
	mov	ecx, edx
	and	eax, ecx
	test	eax, eax
	je	SHORT $LN1@ahci_inter

; 111  : #if 0
; 112  : 			_debug_print_ ("[AHCI]: Interrupt from %d port \r\n", i);
; 113  : #endif
; 114  : 			uint32_t port_is = hba->port[i].is;

	movsxd	rax, DWORD PTR i$1[rsp]
	imul	rax, 128				; 00000080H
	mov	rcx, QWORD PTR hba$[rsp]
	mov	eax, DWORD PTR [rcx+rax+272]
	mov	DWORD PTR port_is$2[rsp], eax

; 115  : 
; 116  : #if 0
; 117  : 			if ((hba->port[i].is & (1<<2))) {
; 118  : 				_debug_print_ ("[AHCI]: DMA Setup FIS Interrupt \r\n");
; 119  : 			}else if ((hba->port[i].is & (1<<1))) {
; 120  : 				_debug_print_ ("[AHCI]: PIO Setup FIS Interrupt \r\n");
; 121  : 			}else if (hba->port[i].is & (1<<0)) {
; 122  : 				_debug_print_ ("[AHCI]: D2H Fis received \r\n");
; 123  : 			}else if (hba->port[i].is & (1<<30)) {
; 124  : 				_debug_print_ ("[AHCI]: Task File Error Status \r\n");
; 125  : 			}else if (hba->port[i].is & (1<<29)) {
; 126  : 				_debug_print_ ("[AHCI]: Host Bus Fetal Error Status \r\n");
; 127  : 			}else if (hba->port[i].is & (1<<4)) {
; 128  : 				_debug_print_ ("[AHCI]: Unknown FIS interrupt status \r\n");
; 129  : 			}
; 130  : #endif
; 131  : 
; 132  : 			hba->port[i].is = port_is;

	movsxd	rax, DWORD PTR i$1[rsp]
	imul	rax, 128				; 00000080H
	mov	rcx, QWORD PTR hba$[rsp]
	mov	edx, DWORD PTR port_is$2[rsp]
	mov	DWORD PTR [rcx+rax+272], edx

; 133  : 			break;

	jmp	SHORT $LN2@ahci_inter
$LN1@ahci_inter:

; 134  : 		}
; 135  : 	}

	jmp	SHORT $LN3@ahci_inter
$LN2@ahci_inter:

; 136  : 
; 137  : 	
; 138  : 	hba->is = is;

	mov	rax, QWORD PTR hba$[rsp]
	mov	ecx, DWORD PTR is$[rsp]
	mov	DWORD PTR [rax+8], ecx

; 139  : 	AuInterruptEnd(0);

	xor	ecx, ecx
	call	AuInterruptEnd

; 140  : 	//x64_sti();
; 141  : 
; 142  : }

	add	rsp, 72					; 00000048H
	ret	0
?ahci_interrupt_handler@@YAX_KPEAX@Z ENDP		; ahci_interrupt_handler
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\ahci.cpp
_TEXT	SEGMENT
i$ = 32
mem$ = 64
?ahci_control_hand_os@@YAXPEAU_hba_mem_@@@Z PROC	; ahci_control_hand_os

; 89   : void ahci_control_hand_os (HBA_MEM *mem) {

$LN5:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 90   : 	mem->bohc = mem->bohc | GHC_BOHC_OOS;

	mov	rax, QWORD PTR mem$[rsp]
	mov	eax, DWORD PTR [rax+40]
	or	eax, 2
	mov	rcx, QWORD PTR mem$[rsp]
	mov	DWORD PTR [rcx+40], eax

; 91   : 	int i = 0;

	mov	DWORD PTR i$[rsp], 0
$LN2@ahci_contr:

; 92   : 	while (!(mem->bohc & GHC_BOHC_BOS | GHC_BOHC_OOS | GHC_BOHC_OOS)) {

	mov	rax, QWORD PTR mem$[rsp]
	mov	eax, DWORD PTR [rax+40]
	and	eax, 1
	or	eax, 2
	or	eax, 2
	test	eax, eax
	jne	SHORT $LN1@ahci_contr

; 93   : 		i++;

	mov	eax, DWORD PTR i$[rsp]
	inc	eax
	mov	DWORD PTR i$[rsp], eax

; 94   : 	}

	jmp	SHORT $LN2@ahci_contr
$LN1@ahci_contr:

; 95   : 	printf ("[AHCI]: Taking the control from firmware took %d ms\n", i);

	mov	edx, DWORD PTR i$[rsp]
	lea	rcx, OFFSET FLAT:$SG3756
	call	printf

; 96   : }

	add	rsp, 56					; 00000038H
	ret	0
?ahci_control_hand_os@@YAXPEAU_hba_mem_@@@Z ENDP	; ahci_control_hand_os
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\ahci.cpp
_TEXT	SEGMENT
det$ = 0
ipm$ = 1
tv75 = 4
ssts$ = 8
port$ = 32
?ahci_check_type@@YAHPEAU_hba_port_@@@Z PROC		; ahci_check_type

; 64   : int ahci_check_type (HBA_PORT *port) {

$LN11:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 24

; 65   : 	uint32_t ssts = port->ssts;

	mov	rax, QWORD PTR port$[rsp]
	mov	eax, DWORD PTR [rax+40]
	mov	DWORD PTR ssts$[rsp], eax

; 66   : 	uint8_t ipm = (ssts >> 8) & 0x0F;

	mov	eax, DWORD PTR ssts$[rsp]
	shr	eax, 8
	and	eax, 15
	mov	BYTE PTR ipm$[rsp], al

; 67   : 	uint8_t det = ssts & 0x0F;

	mov	eax, DWORD PTR ssts$[rsp]
	and	eax, 15
	mov	BYTE PTR det$[rsp], al

; 68   : 
; 69   : 	if (det != HBA_PORT_DET_PRESENT)

	movzx	eax, BYTE PTR det$[rsp]
	cmp	eax, 3
	je	SHORT $LN8@ahci_check

; 70   : 		return AHCI_DEV_NULL;

	xor	eax, eax
	jmp	SHORT $LN9@ahci_check
$LN8@ahci_check:

; 71   : 	if (ipm != HBA_PORT_IPM_ACTIVE)

	movzx	eax, BYTE PTR ipm$[rsp]
	cmp	eax, 1
	je	SHORT $LN7@ahci_check

; 72   : 		return AHCI_DEV_NULL;

	xor	eax, eax
	jmp	SHORT $LN9@ahci_check
$LN7@ahci_check:

; 73   : 
; 74   : 	switch (port->sig) {

	mov	rax, QWORD PTR port$[rsp]
	mov	eax, DWORD PTR [rax+36]
	mov	DWORD PTR tv75[rsp], eax
	cmp	DWORD PTR tv75[rsp], -1771503359	; 96690101H
	je	SHORT $LN2@ahci_check
	cmp	DWORD PTR tv75[rsp], -1019477759	; c33c0101H
	je	SHORT $LN3@ahci_check
	cmp	DWORD PTR tv75[rsp], -351010559		; eb140101H
	je	SHORT $LN4@ahci_check
	jmp	SHORT $LN1@ahci_check
$LN4@ahci_check:

; 75   : 	case SATA_SIG_ATAPI:
; 76   : 		return AHCI_DEV_SATAPI;

	mov	eax, 4
	jmp	SHORT $LN9@ahci_check
$LN3@ahci_check:

; 77   : 	case SATA_SIG_SEMB:
; 78   : 		return AHCI_DEV_SEMB;

	mov	eax, 2
	jmp	SHORT $LN9@ahci_check
$LN2@ahci_check:

; 79   : 	case SATA_SIG_PM:
; 80   : 		return AHCI_DEV_PM;

	mov	eax, 3
	jmp	SHORT $LN9@ahci_check
$LN1@ahci_check:

; 81   : 	default:
; 82   : 		return AHCI_DEV_SATA;

	mov	eax, 1
$LN9@ahci_check:

; 83   : 	}
; 84   : }

	add	rsp, 24
	ret	0
?ahci_check_type@@YAHPEAU_hba_port_@@@Z ENDP		; ahci_check_type
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\ahci.cpp
_TEXT	SEGMENT
?ahci_is_64_bit_supported@@YA_NXZ PROC			; ahci_is_64_bit_supported

; 251  : 	return ___ahci_64_bit___;

	movzx	eax, BYTE PTR ___ahci_64_bit___

; 252  : }

	ret	0
?ahci_is_64_bit_supported@@YA_NXZ ENDP			; ahci_is_64_bit_supported
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\ahci.cpp
_TEXT	SEGMENT
i$ = 48
ahci_not_found$ = 52
support_spin$ = 53
hba$ = 56
func$ = 64
bus$ = 68
dev$ = 72
dt$1 = 76
device$ = 80
pi$ = 88
command$ = 96
hba_phys$ = 104
base_address$ = 108
_bit$ = 112
version_minor$ = 116
num_command_slots$ = 120
version_major$ = 124
mmio$ = 128
int_line$ = 136
?ahci_initialize@@YAXXZ PROC				; ahci_initialize

; 147  : void ahci_initialize () {

$LN21:
	sub	rsp, 152				; 00000098H

; 148  : 	int bus,dev,func = 0;

	mov	DWORD PTR func$[rsp], 0

; 149  : 	bool ahci_not_found = false;

	mov	BYTE PTR ahci_not_found$[rsp], 0

; 150  : 
; 151  : 	/* First find in standard registry */
; 152  : 	uint64_t device = pci_express_scan_class(0x01,0x06, &bus, &dev, &func);

	lea	rax, QWORD PTR func$[rsp]
	mov	QWORD PTR [rsp+32], rax
	lea	r9, QWORD PTR dev$[rsp]
	lea	r8, QWORD PTR bus$[rsp]
	mov	dl, 6
	mov	cl, 1
	call	pci_express_scan_class
	mov	QWORD PTR device$[rsp], rax

; 153  : 	if (device == 0xFFFFFFFF)

	mov	eax, -1					; ffffffffH
	cmp	QWORD PTR device$[rsp], rax
	jne	SHORT $LN18@ahci_initi

; 154  : 		ahci_not_found = true; // pci_express_scan_class(0x01,0x06);

	mov	BYTE PTR ahci_not_found$[rsp], 1
$LN18@ahci_initi:

; 155  : 	
; 156  : 
; 157  : 	/* not found? now search in RAID registry */
; 158  : 	if (ahci_not_found) {

	movzx	eax, BYTE PTR ahci_not_found$[rsp]
	test	eax, eax
	je	SHORT $LN17@ahci_initi

; 159  : 		device = pci_express_scan_class(0x01,0x04, &bus, &dev, &func);

	lea	rax, QWORD PTR func$[rsp]
	mov	QWORD PTR [rsp+32], rax
	lea	r9, QWORD PTR dev$[rsp]
	lea	r8, QWORD PTR bus$[rsp]
	mov	dl, 4
	mov	cl, 1
	call	pci_express_scan_class
	mov	QWORD PTR device$[rsp], rax

; 160  : 		if (device == 0xFFFFFFFF){

	mov	eax, -1					; ffffffffH
	cmp	QWORD PTR device$[rsp], rax
	jne	SHORT $LN16@ahci_initi

; 161  : 			printf ("*******************************\n");

	lea	rcx, OFFSET FLAT:$SG3780
	call	printf

; 162  : 			printf ("AHCI/SATA not found\n");

	lea	rcx, OFFSET FLAT:$SG3781
	call	printf

; 163  : 			printf ("Xeneva initialisation failed\n");

	lea	rcx, OFFSET FLAT:$SG3782
	call	printf

; 164  : 			printf ("Halting System\n");

	lea	rcx, OFFSET FLAT:$SG3783
	call	printf

; 165  : 			printf ("*******************************\n");

	lea	rcx, OFFSET FLAT:$SG3784
	call	printf
$LN15@ahci_initi:

; 166  : 			for(;;);

	jmp	SHORT $LN15@ahci_initi
$LN16@ahci_initi:
$LN17@ahci_initi:

; 167  : 		}
; 168  : 	}
; 169  : 	
; 170  : 	
; 171  : 	uint32_t int_line = pci_express_read(device, PCI_INTERRUPT_LINE, bus, dev, func);

	mov	eax, DWORD PTR func$[rsp]
	mov	DWORD PTR [rsp+32], eax
	mov	r9d, DWORD PTR dev$[rsp]
	mov	r8d, DWORD PTR bus$[rsp]
	mov	edx, 60					; 0000003cH
	mov	rcx, QWORD PTR device$[rsp]
	call	pci_express_read
	mov	DWORD PTR int_line$[rsp], eax

; 172  : 	uint32_t base_address = pci_express_read(device,PCI_BAR5, bus, dev, func);

	mov	eax, DWORD PTR func$[rsp]
	mov	DWORD PTR [rsp+32], eax
	mov	r9d, DWORD PTR dev$[rsp]
	mov	r8d, DWORD PTR bus$[rsp]
	mov	edx, 36					; 00000024H
	mov	rcx, QWORD PTR device$[rsp]
	call	pci_express_read
	mov	DWORD PTR base_address$[rsp], eax

; 173  : 	
; 174  : 
; 175  : 	uint64_t command = pci_express_read(device,PCI_COMMAND, bus, dev, func); 

	mov	eax, DWORD PTR func$[rsp]
	mov	DWORD PTR [rsp+32], eax
	mov	r9d, DWORD PTR dev$[rsp]
	mov	r8d, DWORD PTR bus$[rsp]
	mov	edx, 4
	mov	rcx, QWORD PTR device$[rsp]
	call	pci_express_read
	mov	eax, eax
	mov	QWORD PTR command$[rsp], rax

; 176  : 	command |= (1<<1);

	mov	rax, QWORD PTR command$[rsp]
	or	rax, 2
	mov	QWORD PTR command$[rsp], rax

; 177  : 	command |= (1<<10);

	mov	rax, QWORD PTR command$[rsp]
	bts	rax, 10
	mov	QWORD PTR command$[rsp], rax

; 178  : 	pci_express_write(device, PCI_COMMAND, command, bus, dev, func);

	mov	eax, DWORD PTR func$[rsp]
	mov	DWORD PTR [rsp+40], eax
	mov	eax, DWORD PTR dev$[rsp]
	mov	DWORD PTR [rsp+32], eax
	mov	r9d, DWORD PTR bus$[rsp]
	mov	r8d, DWORD PTR command$[rsp]
	mov	edx, 4
	mov	rcx, QWORD PTR device$[rsp]
	call	pci_express_write

; 179  : 
; 180  : 
; 181  : 	pcie_alloc_msi(device, 36, bus, dev, func);

	mov	eax, DWORD PTR func$[rsp]
	mov	DWORD PTR [rsp+32], eax
	mov	r9d, DWORD PTR dev$[rsp]
	mov	r8d, DWORD PTR bus$[rsp]
	mov	edx, 36					; 00000024H
	mov	rcx, QWORD PTR device$[rsp]
	call	pcie_alloc_msi

; 182  : 	setvect(36, ahci_interrupt_handler);

	lea	rdx, OFFSET FLAT:?ahci_interrupt_handler@@YAX_KPEAX@Z ; ahci_interrupt_handler
	mov	ecx, 36					; 00000024H
	call	setvect

; 183  : 	
; 184  : 
; 185  : 	uintptr_t hba_phys = base_address & 0xFFFFFFF0;

	mov	eax, DWORD PTR base_address$[rsp]
	and	eax, -16				; fffffff0H
	mov	DWORD PTR hba_phys$[rsp], eax

; 186  : 	void* mmio = AuMapMMIO(hba_phys,3);

	mov	eax, DWORD PTR hba_phys$[rsp]
	mov	edx, 3
	mov	ecx, eax
	call	AuMapMMIO
	mov	QWORD PTR mmio$[rsp], rax

; 187  : 	HBA_MEM *hba = (HBA_MEM*)mmio;//(info->device.nonBridge.baseAddress[5] & 0xFFFFFFF0);

	mov	rax, QWORD PTR mmio$[rsp]
	mov	QWORD PTR hba$[rsp], rax

; 188  : 	hbabar = (void*)mmio; //(info->device.nonBridge.baseAddress[5] & 0xFFFFFFF0);

	mov	rax, QWORD PTR mmio$[rsp]
	mov	QWORD PTR ?hbabar@@3PEAXEA, rax		; hbabar

; 189  : 	hba->ghc = 1;

	mov	rax, QWORD PTR hba$[rsp]
	mov	DWORD PTR [rax+4], 1

; 190  : 
; 191  : 	timer_sleep(500);

	mov	ecx, 500				; 000001f4H
	call	?timer_sleep@@YAXI@Z			; timer_sleep

; 192  : 	hba->ghc = (1<<31);

	mov	rax, QWORD PTR hba$[rsp]
	mov	DWORD PTR [rax+4], -2147483648		; 80000000H

; 193  : 	timer_sleep(100);

	mov	ecx, 100				; 00000064H
	call	?timer_sleep@@YAXI@Z			; timer_sleep

; 194  : 	//hba->ghc = (1<<1);
; 195  : 
; 196  : 	uint32_t version_major = hba->vs >> 16 & 0xff;

	mov	rax, QWORD PTR hba$[rsp]
	mov	eax, DWORD PTR [rax+16]
	shr	eax, 16
	and	eax, 255				; 000000ffH
	mov	DWORD PTR version_major$[rsp], eax

; 197  : 	uint32_t version_minor = hba->vs & 0xff;

	mov	rax, QWORD PTR hba$[rsp]
	mov	eax, DWORD PTR [rax+16]
	and	eax, 255				; 000000ffH
	mov	DWORD PTR version_minor$[rsp], eax

; 198  : 
; 199  : 	printf ("[AHCI]: Version -- %d.%d\n", version_major, version_minor);

	mov	r8d, DWORD PTR version_minor$[rsp]
	mov	edx, DWORD PTR version_major$[rsp]
	lea	rcx, OFFSET FLAT:$SG3798
	call	printf

; 200  : 	uint32_t _bit = hba->cap >> 31 & 0xff;

	mov	rax, QWORD PTR hba$[rsp]
	mov	eax, DWORD PTR [rax]
	shr	eax, 31
	and	eax, 255				; 000000ffH
	mov	DWORD PTR _bit$[rsp], eax

; 201  : 	if (_bit) {

	cmp	DWORD PTR _bit$[rsp], 0
	je	SHORT $LN13@ahci_initi

; 202  : 		printf ("[AHCI]: 64-bit DMA supported\n");

	lea	rcx, OFFSET FLAT:$SG3801
	call	printf

; 203  : 		___ahci_64_bit___ = true;

	mov	BYTE PTR ___ahci_64_bit___, 1
$LN13@ahci_initi:

; 204  : 	}
; 205  : 
; 206  : 	
; 207  : 	hba->is = UINT32_MAX;

	mov	rax, QWORD PTR hba$[rsp]
	mov	DWORD PTR [rax+8], -1			; ffffffffH

; 208  : 	hba->ghc |= 0x2;

	mov	rax, QWORD PTR hba$[rsp]
	mov	eax, DWORD PTR [rax+4]
	or	eax, 2
	mov	rcx, QWORD PTR hba$[rsp]
	mov	DWORD PTR [rcx+4], eax

; 209  : 
; 210  : 	uint32_t num_command_slots  = hba->cap >> 8 & 0xff;

	mov	rax, QWORD PTR hba$[rsp]
	mov	eax, DWORD PTR [rax]
	shr	eax, 8
	and	eax, 255				; 000000ffH
	mov	DWORD PTR num_command_slots$[rsp], eax

; 211  : 	_debug_print_ ("[AHCI]: Num Command Slots -> %d\n", num_command_slots);

	mov	edx, DWORD PTR num_command_slots$[rsp]
	lea	rcx, OFFSET FLAT:$SG3803
	call	_debug_print_

; 212  : 
; 213  : 	uint8_t support_spin = hba->cap & (1<<27);

	mov	rax, QWORD PTR hba$[rsp]
	mov	eax, DWORD PTR [rax]
	and	eax, 134217728				; 08000000H
	mov	BYTE PTR support_spin$[rsp], al

; 214  : 	if (support_spin) {

	movzx	eax, BYTE PTR support_spin$[rsp]
	test	eax, eax
	je	SHORT $LN12@ahci_initi

; 215  : 		_debug_print_ ("[AHCI]: Support Staggered spin-up %d\n", support_spin);

	movzx	eax, BYTE PTR support_spin$[rsp]
	mov	edx, eax
	lea	rcx, OFFSET FLAT:$SG3806
	call	_debug_print_
$LN12@ahci_initi:

; 216  : 	}
; 217  : 
; 218  : 	if (hba->cap & (1<<16))

	mov	rax, QWORD PTR hba$[rsp]
	mov	eax, DWORD PTR [rax]
	and	eax, 65536				; 00010000H
	test	eax, eax
	je	SHORT $LN11@ahci_initi

; 219  : 		_debug_print_ ("[AHCI]: FIS-Based Switching supported\n");

	lea	rcx, OFFSET FLAT:$SG3808
	call	_debug_print_
$LN11@ahci_initi:

; 220  : 	uint32_t pi = hba->pi;

	mov	rax, QWORD PTR hba$[rsp]
	mov	eax, DWORD PTR [rax+12]
	mov	DWORD PTR pi$[rsp], eax

; 221  : 	int i = 0;

	mov	DWORD PTR i$[rsp], 0
$LN10@ahci_initi:

; 222  : 	while (i < 32) {

	cmp	DWORD PTR i$[rsp], 32			; 00000020H
	jge	$LN9@ahci_initi

; 223  : 		if (pi & 1) {

	mov	eax, DWORD PTR pi$[rsp]
	and	eax, 1
	test	eax, eax
	je	$LN8@ahci_initi

; 224  : 			int dt = ahci_check_type (&hba->port[i]);

	movsxd	rax, DWORD PTR i$[rsp]
	imul	rax, 128				; 00000080H
	mov	rcx, QWORD PTR hba$[rsp]
	lea	rax, QWORD PTR [rcx+rax+256]
	mov	rcx, rax
	call	?ahci_check_type@@YAHPEAU_hba_port_@@@Z	; ahci_check_type
	mov	DWORD PTR dt$1[rsp], eax

; 225  : 			if (dt == AHCI_DEV_SATA) {

	cmp	DWORD PTR dt$1[rsp], 1
	jne	$LN7@ahci_initi

; 226  : 				printf ("[AHCI]: SATA Drive found at port %d\n", i);

	mov	edx, DWORD PTR i$[rsp]
	lea	rcx, OFFSET FLAT:$SG3817
	call	printf

; 227  : 				hba->port[i].sctl &= ~PX_SCTL_IPM_MASK;

	movsxd	rax, DWORD PTR i$[rsp]
	imul	rax, 128				; 00000080H
	mov	rcx, QWORD PTR hba$[rsp]
	mov	eax, DWORD PTR [rcx+rax+300]
	and	eax, -4096				; fffff000H
	movsxd	rcx, DWORD PTR i$[rsp]
	imul	rcx, 128				; 00000080H
	mov	rdx, QWORD PTR hba$[rsp]
	mov	DWORD PTR [rdx+rcx+300], eax

; 228  : 				hba->port[i].sctl |= PX_SCTL_IPM_NONE;

	movsxd	rax, DWORD PTR i$[rsp]
	imul	rax, 128				; 00000080H
	mov	rcx, QWORD PTR hba$[rsp]
	mov	eax, DWORD PTR [rcx+rax+300]
	or	eax, 768				; 00000300H
	movsxd	rcx, DWORD PTR i$[rsp]
	imul	rcx, 128				; 00000080H
	mov	rdx, QWORD PTR hba$[rsp]
	mov	DWORD PTR [rdx+rcx+300], eax

; 229  : 				ahci_disk_initialize(&hba->port[i]);

	movsxd	rax, DWORD PTR i$[rsp]
	imul	rax, 128				; 00000080H
	mov	rcx, QWORD PTR hba$[rsp]
	lea	rax, QWORD PTR [rcx+rax+256]
	mov	rcx, rax
	call	?ahci_disk_initialize@@YAXPEAU_hba_port_@@@Z ; ahci_disk_initialize
	jmp	SHORT $LN6@ahci_initi
$LN7@ahci_initi:

; 230  : 			}
; 231  : 			else if (dt == AHCI_DEV_SATAPI) {

	cmp	DWORD PTR dt$1[rsp], 4
	jne	SHORT $LN5@ahci_initi

; 232  : 				printf ("[AHCI]: SATAPI Drive found at port %d\n", i);

	mov	edx, DWORD PTR i$[rsp]
	lea	rcx, OFFSET FLAT:$SG3820
	call	printf
	jmp	SHORT $LN4@ahci_initi
$LN5@ahci_initi:

; 233  : 			}else if (dt == AHCI_DEV_SEMB) {

	cmp	DWORD PTR dt$1[rsp], 2
	jne	SHORT $LN3@ahci_initi

; 234  : 				printf ("[AHCI]: SEMB Drive found at port %d\n", i);

	mov	edx, DWORD PTR i$[rsp]
	lea	rcx, OFFSET FLAT:$SG3823
	call	printf
	jmp	SHORT $LN2@ahci_initi
$LN3@ahci_initi:

; 235  : 			}else if (dt == AHCI_DEV_PM) {

	cmp	DWORD PTR dt$1[rsp], 3
	jne	SHORT $LN1@ahci_initi

; 236  : 				printf ("[AHCI]: PM Drive found at port %d\n", i);

	mov	edx, DWORD PTR i$[rsp]
	lea	rcx, OFFSET FLAT:$SG3826
	call	printf
$LN1@ahci_initi:
$LN2@ahci_initi:
$LN4@ahci_initi:
$LN6@ahci_initi:
$LN8@ahci_initi:

; 237  : 			}
; 238  : 		}
; 239  : 		pi >>= 1;

	mov	eax, DWORD PTR pi$[rsp]
	shr	eax, 1
	mov	DWORD PTR pi$[rsp], eax

; 240  : 		i++;

	mov	eax, DWORD PTR i$[rsp]
	inc	eax
	mov	DWORD PTR i$[rsp], eax

; 241  : 	}

	jmp	$LN10@ahci_initi
$LN9@ahci_initi:

; 242  : 
; 243  : 	//pcie_print_capabilities(device);
; 244  : }

	add	rsp, 152				; 00000098H
	ret	0
?ahci_initialize@@YAXXZ ENDP				; ahci_initialize
_TEXT	ENDS
END
