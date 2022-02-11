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
$SG3522	DB	'[AHCI]: Taking the control from firmware took %d ms', 0aH
	DB	00H
	ORG $+3
$SG3547	DB	'*******************************', 0aH, 00H
	ORG $+7
$SG3548	DB	'AHCI/SATA not found', 0aH, 00H
	ORG $+3
$SG3549	DB	'Xeneva initialisation failed', 0aH, 00H
	ORG $+2
$SG3550	DB	'Halting System', 0aH, 00H
$SG3551	DB	'*******************************', 0aH, 00H
	ORG $+7
$SG3558	DB	'AHCI/SATA found at dev -> %d, func -> %d, bus -> %d', 0aH
	DB	00H
	ORG $+3
$SG3564	DB	'[AHCI]: Version -- %d.%d', 0aH, 00H
	ORG $+6
$SG3567	DB	'[AHCI]: 64-bit DMA supported', 0aH, 00H
	ORG $+2
$SG3569	DB	'[AHCI]: Num Command Slots -> %d', 0aH, 00H
	ORG $+7
$SG3572	DB	'[AHCI]: Support Staggered spin-up %d', 0aH, 00H
	ORG $+2
$SG3574	DB	'[AHCI]: FIS-Based Switching supported', 0aH, 00H
	ORG $+1
$SG3583	DB	'[AHCI]: SATA Drive found at port %d', 0aH, 00H
	ORG $+3
$SG3586	DB	'[AHCI]: SATAPI Drive found at port %d', 0aH, 00H
	ORG $+1
$SG3589	DB	'[AHCI]: SEMB Drive found at port %d', 0aH, 00H
	ORG $+3
$SG3592	DB	'[AHCI]: PM Drive found at port %d', 0aH, 00H
CONST	ENDS
PUBLIC	?ahci_initialize@@YAXXZ				; ahci_initialize
PUBLIC	?ahci_is_64_bit_supported@@YA_NXZ		; ahci_is_64_bit_supported
PUBLIC	?ahci_check_type@@YAHPEAU_hba_port_@@@Z		; ahci_check_type
PUBLIC	?ahci_control_hand_os@@YAXPEAU_hba_mem_@@@Z	; ahci_control_hand_os
PUBLIC	?ahci_interrupt_handler@@YAX_KPEAX@Z		; ahci_interrupt_handler
EXTRN	?ahci_disk_initialize@@YAXPEAU_hba_port_@@@Z:PROC ; ahci_disk_initialize
EXTRN	?timer_sleep@@YAXI@Z:PROC			; timer_sleep
EXTRN	?interrupt_end@@YAXI@Z:PROC			; interrupt_end
EXTRN	?interrupt_set@@YAX_KP6AX0PEAX@ZE@Z:PROC	; interrupt_set
EXTRN	?read_config_16@@YAXGHHHHPEAG@Z:PROC		; read_config_16
EXTRN	?write_config_16@@YAXGHHHHG@Z:PROC		; write_config_16
EXTRN	?pci_find_device_class@@YA_NEEPEATpci_device_info@@PEAH11@Z:PROC ; pci_find_device_class
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
pdata	SEGMENT
$pdata$?ahci_initialize@@YAXXZ DD imagerel $LN22
	DD	imagerel $LN22+1102
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
	DD	0110107H
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

; 97   : void ahci_interrupt_handler (size_t v, void* p) {

$LN7:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 98   : 	HBA_MEM *hba = (HBA_MEM*)hbabar;

	mov	rax, QWORD PTR ?hbabar@@3PEAXEA		; hbabar
	mov	QWORD PTR hba$[rsp], rax

; 99   : 	uint32_t is = hba->is;

	mov	rax, QWORD PTR hba$[rsp]
	mov	eax, DWORD PTR [rax+8]
	mov	DWORD PTR is$[rsp], eax

; 100  : #if 0
; 101  : 	printf ("[AHCI]: Interrupt fired++\n");
; 102  : #endif
; 103  : 	for (int i = 0; i < 32; i++) {

	mov	DWORD PTR i$1[rsp], 0
	jmp	SHORT $LN4@ahci_inter
$LN3@ahci_inter:
	mov	eax, DWORD PTR i$1[rsp]
	inc	eax
	mov	DWORD PTR i$1[rsp], eax
$LN4@ahci_inter:
	cmp	DWORD PTR i$1[rsp], 32			; 00000020H
	jge	SHORT $LN2@ahci_inter

; 104  : 		if ((hba->is & hba->pi & (1<<i))) {

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

; 105  : #if 0
; 106  : 			printf ("[AHCI]: Interrupt from %d port\n", i);
; 107  : #endif
; 108  : 			uint32_t port_is = hba->port[i].is;

	movsxd	rax, DWORD PTR i$1[rsp]
	imul	rax, 128				; 00000080H
	mov	rcx, QWORD PTR hba$[rsp]
	mov	eax, DWORD PTR [rcx+rax+272]
	mov	DWORD PTR port_is$2[rsp], eax

; 109  : #if 0
; 110  : 			if ((hba->port[i].is & (1<<2))) {
; 111  : 				printf ("[AHCI]: DMA Setup FIS Interrupt\n");
; 112  : 			}else if ((hba->port[i].is & (1<<1))) {
; 113  : 				printf ("[AHCI]: PIO Setup FIS Interrupt\n");
; 114  : 			}else if (hba->port[i].is & (1<<0)) {
; 115  : 				printf ("[AHCI]: D2H Fis received\n");
; 116  : 			}else if (hba->port[i].is & (1<<30)) {
; 117  : 				printf ("[AHCI]: Task File Error Status\n");
; 118  : 			}else if (hba->port[i].is & (1<<29)) {
; 119  : 				printf ("[AHCI]: Host Bus Fetal Error Status\n");
; 120  : 			}else if (hba->port[i].is & (1<<4)) {
; 121  : 				printf ("[AHCI]: Unknown FIS interrupt status\n");
; 122  : 			}
; 123  : #endif
; 124  : 			hba->port[i].is = port_is;

	movsxd	rax, DWORD PTR i$1[rsp]
	imul	rax, 128				; 00000080H
	mov	rcx, QWORD PTR hba$[rsp]
	mov	edx, DWORD PTR port_is$2[rsp]
	mov	DWORD PTR [rcx+rax+272], edx

; 125  : 			break;

	jmp	SHORT $LN2@ahci_inter
$LN1@ahci_inter:

; 126  : 		}
; 127  : 	}

	jmp	SHORT $LN3@ahci_inter
$LN2@ahci_inter:

; 128  : 
; 129  : 	hba->is = is;

	mov	rax, QWORD PTR hba$[rsp]
	mov	ecx, DWORD PTR is$[rsp]
	mov	DWORD PTR [rax+8], ecx

; 130  : 	interrupt_end(0);

	xor	ecx, ecx
	call	?interrupt_end@@YAXI@Z			; interrupt_end

; 131  : }

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

; 85   : void ahci_control_hand_os (HBA_MEM *mem) {

$LN5:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 86   : 	mem->bohc = mem->bohc | GHC_BOHC_OOS;

	mov	rax, QWORD PTR mem$[rsp]
	mov	eax, DWORD PTR [rax+40]
	or	eax, 2
	mov	rcx, QWORD PTR mem$[rsp]
	mov	DWORD PTR [rcx+40], eax

; 87   : 	int i = 0;

	mov	DWORD PTR i$[rsp], 0
$LN2@ahci_contr:

; 88   : 	while (!(mem->bohc & GHC_BOHC_BOS | GHC_BOHC_OOS | GHC_BOHC_OOS)) {

	mov	rax, QWORD PTR mem$[rsp]
	mov	eax, DWORD PTR [rax+40]
	and	eax, 1
	or	eax, 2
	or	eax, 2
	test	eax, eax
	jne	SHORT $LN1@ahci_contr

; 89   : 		i++;

	mov	eax, DWORD PTR i$[rsp]
	inc	eax
	mov	DWORD PTR i$[rsp], eax

; 90   : 	}

	jmp	SHORT $LN2@ahci_contr
$LN1@ahci_contr:

; 91   : 	printf ("[AHCI]: Taking the control from firmware took %d ms\n", i);

	mov	edx, DWORD PTR i$[rsp]
	lea	rcx, OFFSET FLAT:$SG3522
	call	?printf@@YAXPEBDZZ			; printf

; 92   : }

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

; 60   : int ahci_check_type (HBA_PORT *port) {

$LN11:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 24

; 61   : 	uint32_t ssts = port->ssts;

	mov	rax, QWORD PTR port$[rsp]
	mov	eax, DWORD PTR [rax+40]
	mov	DWORD PTR ssts$[rsp], eax

; 62   : 	uint8_t ipm = (ssts >> 8) & 0x0F;

	mov	eax, DWORD PTR ssts$[rsp]
	shr	eax, 8
	and	eax, 15
	mov	BYTE PTR ipm$[rsp], al

; 63   : 	uint8_t det = ssts & 0x0F;

	mov	eax, DWORD PTR ssts$[rsp]
	and	eax, 15
	mov	BYTE PTR det$[rsp], al

; 64   : 
; 65   : 	if (det != HBA_PORT_DET_PRESENT)

	movzx	eax, BYTE PTR det$[rsp]
	cmp	eax, 3
	je	SHORT $LN8@ahci_check

; 66   : 		return AHCI_DEV_NULL;

	xor	eax, eax
	jmp	SHORT $LN9@ahci_check
$LN8@ahci_check:

; 67   : 	if (ipm != HBA_PORT_IPM_ACTIVE)

	movzx	eax, BYTE PTR ipm$[rsp]
	cmp	eax, 1
	je	SHORT $LN7@ahci_check

; 68   : 		return AHCI_DEV_NULL;

	xor	eax, eax
	jmp	SHORT $LN9@ahci_check
$LN7@ahci_check:

; 69   : 
; 70   : 	switch (port->sig) {

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

; 71   : 	case SATA_SIG_ATAPI:
; 72   : 		return AHCI_DEV_SATAPI;

	mov	eax, 4
	jmp	SHORT $LN9@ahci_check
$LN3@ahci_check:

; 73   : 	case SATA_SIG_SEMB:
; 74   : 		return AHCI_DEV_SEMB;

	mov	eax, 2
	jmp	SHORT $LN9@ahci_check
$LN2@ahci_check:

; 75   : 	case SATA_SIG_PM:
; 76   : 		return AHCI_DEV_PM;

	mov	eax, 3
	jmp	SHORT $LN9@ahci_check
$LN1@ahci_check:

; 77   : 	default:
; 78   : 		return AHCI_DEV_SATA;

	mov	eax, 1
$LN9@ahci_check:

; 79   : 	}
; 80   : }

	add	rsp, 24
	ret	0
?ahci_check_type@@YAHPEAU_hba_port_@@@Z ENDP		; ahci_check_type
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\ahci.cpp
_TEXT	SEGMENT
?ahci_is_64_bit_supported@@YA_NXZ PROC			; ahci_is_64_bit_supported

; 233  : 	return ___ahci_64_bit___;

	movzx	eax, BYTE PTR ___ahci_64_bit___

; 234  : }

	ret	0
?ahci_is_64_bit_supported@@YA_NXZ ENDP			; ahci_is_64_bit_supported
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\ahci.cpp
_TEXT	SEGMENT
command_reg$ = 48
i$ = 52
support_spin$ = 56
ahci_not_found$ = 57
hba$ = 64
dev$ = 72
dt$1 = 76
bus$ = 80
func$ = 84
pi$ = 88
int_line$ = 92
info$ = 96
version_minor$ = 104
version_major$ = 108
num_command_slots$ = 112
_bit$ = 116
?ahci_initialize@@YAXXZ PROC				; ahci_initialize

; 136  : void ahci_initialize () {

$LN22:
	sub	rsp, 136				; 00000088H

; 137  : 	pci_device_info *info = (pci_device_info*)pmmngr_alloc();

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	QWORD PTR info$[rsp], rax

; 138  : 	int bus,dev,func;
; 139  : 	bool ahci_not_found = false;

	mov	BYTE PTR ahci_not_found$[rsp], 0

; 140  : 
; 141  : 	/* First find in standard registry */
; 142  : 	if (!pci_find_device_class(0x01,0x06,info,&bus,&dev,&func)) {

	lea	rax, QWORD PTR func$[rsp]
	mov	QWORD PTR [rsp+40], rax
	lea	rax, QWORD PTR dev$[rsp]
	mov	QWORD PTR [rsp+32], rax
	lea	r9, QWORD PTR bus$[rsp]
	mov	r8, QWORD PTR info$[rsp]
	mov	dl, 6
	mov	cl, 1
	call	?pci_find_device_class@@YA_NEEPEATpci_device_info@@PEAH11@Z ; pci_find_device_class
	movzx	eax, al
	test	eax, eax
	jne	SHORT $LN19@ahci_initi

; 143  : 		ahci_not_found = true;

	mov	BYTE PTR ahci_not_found$[rsp], 1
$LN19@ahci_initi:

; 144  : 	}
; 145  : 	/* not found? now search in RAID registry */
; 146  : 	if (ahci_not_found) {

	movzx	eax, BYTE PTR ahci_not_found$[rsp]
	test	eax, eax
	je	SHORT $LN18@ahci_initi

; 147  : 		if (!pci_find_device_class(0x01,0x04,info,&bus,&dev,&func)) {

	lea	rax, QWORD PTR func$[rsp]
	mov	QWORD PTR [rsp+40], rax
	lea	rax, QWORD PTR dev$[rsp]
	mov	QWORD PTR [rsp+32], rax
	lea	r9, QWORD PTR bus$[rsp]
	mov	r8, QWORD PTR info$[rsp]
	mov	dl, 4
	mov	cl, 1
	call	?pci_find_device_class@@YA_NEEPEATpci_device_info@@PEAH11@Z ; pci_find_device_class
	movzx	eax, al
	test	eax, eax
	jne	SHORT $LN17@ahci_initi

; 148  : 			printf ("*******************************\n");

	lea	rcx, OFFSET FLAT:$SG3547
	call	?printf@@YAXPEBDZZ			; printf

; 149  : 			printf ("AHCI/SATA not found\n");

	lea	rcx, OFFSET FLAT:$SG3548
	call	?printf@@YAXPEBDZZ			; printf

; 150  : 			printf ("Xeneva initialisation failed\n");

	lea	rcx, OFFSET FLAT:$SG3549
	call	?printf@@YAXPEBDZZ			; printf

; 151  : 			printf ("Halting System\n");

	lea	rcx, OFFSET FLAT:$SG3550
	call	?printf@@YAXPEBDZZ			; printf

; 152  : 			printf ("*******************************\n");

	lea	rcx, OFFSET FLAT:$SG3551
	call	?printf@@YAXPEBDZZ			; printf
$LN16@ahci_initi:

; 153  : 			for(;;);

	jmp	SHORT $LN16@ahci_initi
$LN17@ahci_initi:
$LN18@ahci_initi:

; 154  : 		}
; 155  : 	}
; 156  : 
; 157  : 	uint16_t command_reg = 0;

	xor	eax, eax
	mov	WORD PTR command_reg$[rsp], ax

; 158  : 	read_config_16 (0,bus,dev,func,0x4, &command_reg);

	lea	rax, QWORD PTR command_reg$[rsp]
	mov	QWORD PTR [rsp+40], rax
	mov	DWORD PTR [rsp+32], 4
	mov	r9d, DWORD PTR func$[rsp]
	mov	r8d, DWORD PTR dev$[rsp]
	mov	edx, DWORD PTR bus$[rsp]
	xor	ecx, ecx
	call	?read_config_16@@YAXGHHHHPEAG@Z		; read_config_16

; 159  : 	command_reg |= (1<<2);

	movzx	eax, WORD PTR command_reg$[rsp]
	or	eax, 4
	mov	WORD PTR command_reg$[rsp], ax

; 160  : 	command_reg &= ~(1<<10);

	movzx	eax, WORD PTR command_reg$[rsp]
	btr	eax, 10
	mov	WORD PTR command_reg$[rsp], ax

; 161  : 	command_reg |= (1<<1);

	movzx	eax, WORD PTR command_reg$[rsp]
	or	eax, 2
	mov	WORD PTR command_reg$[rsp], ax

; 162  :     write_config_16 (0,bus, dev,func,0x4,command_reg);

	movzx	eax, WORD PTR command_reg$[rsp]
	mov	WORD PTR [rsp+40], ax
	mov	DWORD PTR [rsp+32], 4
	mov	r9d, DWORD PTR func$[rsp]
	mov	r8d, DWORD PTR dev$[rsp]
	mov	edx, DWORD PTR bus$[rsp]
	xor	ecx, ecx
	call	?write_config_16@@YAXGHHHHG@Z		; write_config_16

; 163  : 
; 164  : 	uint8_t int_line = info->device.nonBridge.interruptLine;

	mov	rax, QWORD PTR info$[rsp]
	movzx	eax, BYTE PTR [rax+60]
	mov	BYTE PTR int_line$[rsp], al

; 165  : 	if (info->device.nonBridge.interruptLine < 255) {

	mov	rax, QWORD PTR info$[rsp]
	movzx	eax, BYTE PTR [rax+60]
	cmp	eax, 255				; 000000ffH
	jge	SHORT $LN14@ahci_initi

; 166  : 		interrupt_set(11, ahci_interrupt_handler, 11);

	mov	r8b, 11
	lea	rdx, OFFSET FLAT:?ahci_interrupt_handler@@YAX_KPEAX@Z ; ahci_interrupt_handler
	mov	ecx, 11
	call	?interrupt_set@@YAX_KP6AX0PEAX@ZE@Z	; interrupt_set
$LN14@ahci_initi:

; 167  : 	}
; 168  : 
; 169  : 	printf ("AHCI/SATA found at dev -> %d, func -> %d, bus -> %d\n", dev, func, bus);

	mov	r9d, DWORD PTR bus$[rsp]
	mov	r8d, DWORD PTR func$[rsp]
	mov	edx, DWORD PTR dev$[rsp]
	lea	rcx, OFFSET FLAT:$SG3558
	call	?printf@@YAXPEBDZZ			; printf

; 170  : 	HBA_MEM *hba = (HBA_MEM*)(info->device.nonBridge.baseAddress[5] & 0xFFFFFFF0);

	mov	eax, 4
	imul	rax, 5
	mov	rcx, QWORD PTR info$[rsp]
	mov	eax, DWORD PTR [rcx+rax+16]
	and	eax, -16				; fffffff0H
	mov	eax, eax
	mov	QWORD PTR hba$[rsp], rax

; 171  : 	hbabar = (void*)(info->device.nonBridge.baseAddress[5] & 0xFFFFFFF0);

	mov	eax, 4
	imul	rax, 5
	mov	rcx, QWORD PTR info$[rsp]
	mov	eax, DWORD PTR [rcx+rax+16]
	and	eax, -16				; fffffff0H
	mov	eax, eax
	mov	QWORD PTR ?hbabar@@3PEAXEA, rax		; hbabar

; 172  : 	
; 173  : 	hba->ghc = 1;

	mov	rax, QWORD PTR hba$[rsp]
	mov	DWORD PTR [rax+4], 1

; 174  : 
; 175  : 	timer_sleep(500);

	mov	ecx, 500				; 000001f4H
	call	?timer_sleep@@YAXI@Z			; timer_sleep

; 176  : 	hba->ghc = (1<<31);

	mov	rax, QWORD PTR hba$[rsp]
	mov	DWORD PTR [rax+4], -2147483648		; 80000000H

; 177  : 	timer_sleep(100);

	mov	ecx, 100				; 00000064H
	call	?timer_sleep@@YAXI@Z			; timer_sleep

; 178  : 	hba->ghc = (1<<1);

	mov	rax, QWORD PTR hba$[rsp]
	mov	DWORD PTR [rax+4], 2

; 179  : 
; 180  : 	uint32_t version_major = hba->vs >> 16 & 0xff;

	mov	rax, QWORD PTR hba$[rsp]
	mov	eax, DWORD PTR [rax+16]
	shr	eax, 16
	and	eax, 255				; 000000ffH
	mov	DWORD PTR version_major$[rsp], eax

; 181  : 	uint32_t version_minor = hba->vs & 0xff;

	mov	rax, QWORD PTR hba$[rsp]
	mov	eax, DWORD PTR [rax+16]
	and	eax, 255				; 000000ffH
	mov	DWORD PTR version_minor$[rsp], eax

; 182  : 
; 183  : 	printf ("[AHCI]: Version -- %d.%d\n", version_major, version_minor);

	mov	r8d, DWORD PTR version_minor$[rsp]
	mov	edx, DWORD PTR version_major$[rsp]
	lea	rcx, OFFSET FLAT:$SG3564
	call	?printf@@YAXPEBDZZ			; printf

; 184  : 	uint32_t _bit = hba->cap >> 31 & 0xff;

	mov	rax, QWORD PTR hba$[rsp]
	mov	eax, DWORD PTR [rax]
	shr	eax, 31
	and	eax, 255				; 000000ffH
	mov	DWORD PTR _bit$[rsp], eax

; 185  : 	if (_bit) {

	cmp	DWORD PTR _bit$[rsp], 0
	je	SHORT $LN13@ahci_initi

; 186  : 		printf ("[AHCI]: 64-bit DMA supported\n");

	lea	rcx, OFFSET FLAT:$SG3567
	call	?printf@@YAXPEBDZZ			; printf

; 187  : 		___ahci_64_bit___ = true;

	mov	BYTE PTR ___ahci_64_bit___, 1
$LN13@ahci_initi:

; 188  : 	}
; 189  : 
; 190  : 	
; 191  : 	hba->is = UINT32_MAX;

	mov	rax, QWORD PTR hba$[rsp]
	mov	DWORD PTR [rax+8], -1			; ffffffffH

; 192  : 	hba->ghc |= 0x2;

	mov	rax, QWORD PTR hba$[rsp]
	mov	eax, DWORD PTR [rax+4]
	or	eax, 2
	mov	rcx, QWORD PTR hba$[rsp]
	mov	DWORD PTR [rcx+4], eax

; 193  : 
; 194  : 	uint32_t num_command_slots  = hba->cap >> 8 & 0xff;

	mov	rax, QWORD PTR hba$[rsp]
	mov	eax, DWORD PTR [rax]
	shr	eax, 8
	and	eax, 255				; 000000ffH
	mov	DWORD PTR num_command_slots$[rsp], eax

; 195  : 	printf ("[AHCI]: Num Command Slots -> %d\n", num_command_slots);

	mov	edx, DWORD PTR num_command_slots$[rsp]
	lea	rcx, OFFSET FLAT:$SG3569
	call	?printf@@YAXPEBDZZ			; printf

; 196  : 
; 197  : 	uint8_t support_spin = hba->cap & (1<<27);

	mov	rax, QWORD PTR hba$[rsp]
	mov	eax, DWORD PTR [rax]
	and	eax, 134217728				; 08000000H
	mov	BYTE PTR support_spin$[rsp], al

; 198  : 	if (support_spin) {

	movzx	eax, BYTE PTR support_spin$[rsp]
	test	eax, eax
	je	SHORT $LN12@ahci_initi

; 199  : 		printf ("[AHCI]: Support Staggered spin-up %d\n", support_spin);

	movzx	eax, BYTE PTR support_spin$[rsp]
	mov	edx, eax
	lea	rcx, OFFSET FLAT:$SG3572
	call	?printf@@YAXPEBDZZ			; printf
$LN12@ahci_initi:

; 200  : 	}
; 201  : 
; 202  : 	if (hba->cap & (1<<16))

	mov	rax, QWORD PTR hba$[rsp]
	mov	eax, DWORD PTR [rax]
	and	eax, 65536				; 00010000H
	test	eax, eax
	je	SHORT $LN11@ahci_initi

; 203  : 		printf ("[AHCI]: FIS-Based Switching supported\n");

	lea	rcx, OFFSET FLAT:$SG3574
	call	?printf@@YAXPEBDZZ			; printf
$LN11@ahci_initi:

; 204  : 	uint32_t pi = hba->pi;

	mov	rax, QWORD PTR hba$[rsp]
	mov	eax, DWORD PTR [rax+12]
	mov	DWORD PTR pi$[rsp], eax

; 205  : 	int i = 0;

	mov	DWORD PTR i$[rsp], 0
$LN10@ahci_initi:

; 206  : 	while (i < 32) {

	cmp	DWORD PTR i$[rsp], 32			; 00000020H
	jge	$LN9@ahci_initi

; 207  : 		if (pi & 1) {

	mov	eax, DWORD PTR pi$[rsp]
	and	eax, 1
	test	eax, eax
	je	$LN8@ahci_initi

; 208  : 			int dt = ahci_check_type (&hba->port[i]);

	movsxd	rax, DWORD PTR i$[rsp]
	imul	rax, 128				; 00000080H
	mov	rcx, QWORD PTR hba$[rsp]
	lea	rax, QWORD PTR [rcx+rax+256]
	mov	rcx, rax
	call	?ahci_check_type@@YAHPEAU_hba_port_@@@Z	; ahci_check_type
	mov	DWORD PTR dt$1[rsp], eax

; 209  : 			if (dt == AHCI_DEV_SATA) {

	cmp	DWORD PTR dt$1[rsp], 1
	jne	$LN7@ahci_initi

; 210  : 				printf ("[AHCI]: SATA Drive found at port %d\n", i);

	mov	edx, DWORD PTR i$[rsp]
	lea	rcx, OFFSET FLAT:$SG3583
	call	?printf@@YAXPEBDZZ			; printf

; 211  : 				hba->port[i].sctl &= ~PX_SCTL_IPM_MASK;

	movsxd	rax, DWORD PTR i$[rsp]
	imul	rax, 128				; 00000080H
	mov	rcx, QWORD PTR hba$[rsp]
	mov	eax, DWORD PTR [rcx+rax+300]
	and	eax, -4096				; fffff000H
	movsxd	rcx, DWORD PTR i$[rsp]
	imul	rcx, 128				; 00000080H
	mov	rdx, QWORD PTR hba$[rsp]
	mov	DWORD PTR [rdx+rcx+300], eax

; 212  : 				hba->port[i].sctl |= PX_SCTL_IPM_NONE;

	movsxd	rax, DWORD PTR i$[rsp]
	imul	rax, 128				; 00000080H
	mov	rcx, QWORD PTR hba$[rsp]
	mov	eax, DWORD PTR [rcx+rax+300]
	or	eax, 768				; 00000300H
	movsxd	rcx, DWORD PTR i$[rsp]
	imul	rcx, 128				; 00000080H
	mov	rdx, QWORD PTR hba$[rsp]
	mov	DWORD PTR [rdx+rcx+300], eax

; 213  : 				ahci_disk_initialize(&hba->port[i]);

	movsxd	rax, DWORD PTR i$[rsp]
	imul	rax, 128				; 00000080H
	mov	rcx, QWORD PTR hba$[rsp]
	lea	rax, QWORD PTR [rcx+rax+256]
	mov	rcx, rax
	call	?ahci_disk_initialize@@YAXPEAU_hba_port_@@@Z ; ahci_disk_initialize
	jmp	SHORT $LN6@ahci_initi
$LN7@ahci_initi:

; 214  : 			}
; 215  : 			else if (dt == AHCI_DEV_SATAPI) {

	cmp	DWORD PTR dt$1[rsp], 4
	jne	SHORT $LN5@ahci_initi

; 216  : 				printf ("[AHCI]: SATAPI Drive found at port %d\n", i);

	mov	edx, DWORD PTR i$[rsp]
	lea	rcx, OFFSET FLAT:$SG3586
	call	?printf@@YAXPEBDZZ			; printf
	jmp	SHORT $LN4@ahci_initi
$LN5@ahci_initi:

; 217  : 			}else if (dt == AHCI_DEV_SEMB) {

	cmp	DWORD PTR dt$1[rsp], 2
	jne	SHORT $LN3@ahci_initi

; 218  : 				printf ("[AHCI]: SEMB Drive found at port %d\n", i);

	mov	edx, DWORD PTR i$[rsp]
	lea	rcx, OFFSET FLAT:$SG3589
	call	?printf@@YAXPEBDZZ			; printf
	jmp	SHORT $LN2@ahci_initi
$LN3@ahci_initi:

; 219  : 			}else if (dt == AHCI_DEV_PM) {

	cmp	DWORD PTR dt$1[rsp], 3
	jne	SHORT $LN1@ahci_initi

; 220  : 				printf ("[AHCI]: PM Drive found at port %d\n", i);

	mov	edx, DWORD PTR i$[rsp]
	lea	rcx, OFFSET FLAT:$SG3592
	call	?printf@@YAXPEBDZZ			; printf
$LN1@ahci_initi:
$LN2@ahci_initi:
$LN4@ahci_initi:
$LN6@ahci_initi:
$LN8@ahci_initi:

; 221  : 			}
; 222  : 		}
; 223  : 		pi >>= 1;

	mov	eax, DWORD PTR pi$[rsp]
	shr	eax, 1
	mov	DWORD PTR pi$[rsp], eax

; 224  : 		i++;

	mov	eax, DWORD PTR i$[rsp]
	inc	eax
	mov	DWORD PTR i$[rsp], eax

; 225  : 	}

	jmp	$LN10@ahci_initi
$LN9@ahci_initi:

; 226  : }

	add	rsp, 136				; 00000088H
	ret	0
?ahci_initialize@@YAXXZ ENDP				; ahci_initialize
_TEXT	ENDS
END
