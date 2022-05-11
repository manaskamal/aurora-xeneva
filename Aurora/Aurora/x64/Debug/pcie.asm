; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

CONST	SEGMENT
$SG3150	DB	'MSI-X found for this device', 0aH, 00H
	ORG $+3
$SG3152	DB	'MSI found for this device', 0aH, 00H
CONST	ENDS
PUBLIC	pci_express_scan_class
PUBLIC	pci_express_read
PUBLIC	pcie_print_capabilities
PUBLIC	?pci_express_get_device@@YAIGGGG@Z		; pci_express_get_device
PUBLIC	??$mem_after@PEAUacpiMcfgAlloc@@UacpiMcfg@@@@YAPEAUacpiMcfgAlloc@@PEAUacpiMcfg@@@Z ; mem_after<acpiMcfgAlloc * __ptr64,acpiMcfg>
PUBLIC	??$raw_offset@PECEPEA_K@@YAPECEPEA_KH@Z		; raw_offset<unsigned char volatile * __ptr64,unsigned __int64 * __ptr64>
PUBLIC	??$raw_offset@PECGPEA_K@@YAPECGPEA_KH@Z		; raw_offset<unsigned short volatile * __ptr64,unsigned __int64 * __ptr64>
PUBLIC	??$raw_offset@PECIPEA_K@@YAPECIPEA_KH@Z		; raw_offset<unsigned int volatile * __ptr64,unsigned __int64 * __ptr64>
PUBLIC	?pci_express_read2@@YAIIHH@Z			; pci_express_read2
EXTRN	pci_read:PROC
EXTRN	pci_scan_class:PROC
EXTRN	?acpi_pcie_supported@@YA_NXZ:PROC		; acpi_pcie_supported
EXTRN	?acpi_get_mcfg@@YAPEAUacpiMcfg@@XZ:PROC		; acpi_get_mcfg
EXTRN	printf:PROC
EXTRN	__ImageBase:BYTE
pdata	SEGMENT
$pdata$pci_express_scan_class DD imagerel $LN15
	DD	imagerel $LN15+296
	DD	imagerel $unwind$pci_express_scan_class
$pdata$pci_express_read DD imagerel $LN35
	DD	imagerel $LN35+634
	DD	imagerel $unwind$pci_express_read
$pdata$pcie_print_capabilities DD imagerel $LN8
	DD	imagerel $LN8+212
	DD	imagerel $unwind$pcie_print_capabilities
$pdata$?pci_express_get_device@@YAIGGGG@Z DD imagerel $LN7
	DD	imagerel $LN7+231
	DD	imagerel $unwind$?pci_express_get_device@@YAIGGGG@Z
$pdata$?pci_express_read2@@YAIIHH@Z DD imagerel $LN8
	DD	imagerel $LN8+155
	DD	imagerel $unwind$?pci_express_read2@@YAIIHH@Z
pdata	ENDS
xdata	SEGMENT
$unwind$pci_express_scan_class DD 010c01H
	DD	0a20cH
$unwind$pci_express_read DD 010c01H
	DD	0820cH
$unwind$pcie_print_capabilities DD 010801H
	DD	06208H
$unwind$?pci_express_get_device@@YAIGGGG@Z DD 011a01H
	DD	0821aH
$unwind$?pci_express_read2@@YAIIHH@Z DD 011101H
	DD	06211H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\pcie.cpp
_TEXT	SEGMENT
result$ = 32
address$ = 40
device$ = 64
reg$ = 72
size$ = 80
?pci_express_read2@@YAIIHH@Z PROC			; pci_express_read2

; 150  : uint32_t pci_express_read2 (uint32_t device, int reg, int size) {

$LN8:
	mov	DWORD PTR [rsp+24], r8d
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 56					; 00000038H

; 151  : 	size_t* address = (size_t*)device;

	mov	eax, DWORD PTR device$[rsp]
	mov	QWORD PTR address$[rsp], rax

; 152  : 	uint32_t result = 0;

	mov	DWORD PTR result$[rsp], 0

; 153  : 
; 154  : 	if (size == 1){

	cmp	DWORD PTR size$[rsp], 1
	jne	SHORT $LN5@pci_expres

; 155  : 		result = *raw_offset<volatile uint8_t*>(address, reg);

	mov	edx, DWORD PTR reg$[rsp]
	mov	rcx, QWORD PTR address$[rsp]
	call	??$raw_offset@PECEPEA_K@@YAPECEPEA_KH@Z	; raw_offset<unsigned char volatile * __ptr64,unsigned __int64 * __ptr64>
	movzx	eax, BYTE PTR [rax]
	movzx	eax, al
	mov	DWORD PTR result$[rsp], eax

; 156  : 		return result;

	mov	eax, DWORD PTR result$[rsp]
	jmp	SHORT $LN6@pci_expres
	jmp	SHORT $LN4@pci_expres
$LN5@pci_expres:

; 157  : 	}else if (size == 2) {

	cmp	DWORD PTR size$[rsp], 2
	jne	SHORT $LN3@pci_expres

; 158  : 		result = *raw_offset<volatile uint16_t*>(address, reg);

	mov	edx, DWORD PTR reg$[rsp]
	mov	rcx, QWORD PTR address$[rsp]
	call	??$raw_offset@PECGPEA_K@@YAPECGPEA_KH@Z	; raw_offset<unsigned short volatile * __ptr64,unsigned __int64 * __ptr64>
	movzx	eax, WORD PTR [rax]
	movzx	eax, ax
	mov	DWORD PTR result$[rsp], eax

; 159  : 		return result;

	mov	eax, DWORD PTR result$[rsp]
	jmp	SHORT $LN6@pci_expres
	jmp	SHORT $LN2@pci_expres
$LN3@pci_expres:

; 160  : 	}else if (size == 4) {

	cmp	DWORD PTR size$[rsp], 4
	jne	SHORT $LN1@pci_expres

; 161  : 		result = *raw_offset<volatile uint32_t*>(address, reg);

	mov	edx, DWORD PTR reg$[rsp]
	mov	rcx, QWORD PTR address$[rsp]
	call	??$raw_offset@PECIPEA_K@@YAPECIPEA_KH@Z	; raw_offset<unsigned int volatile * __ptr64,unsigned __int64 * __ptr64>
	mov	eax, DWORD PTR [rax]
	mov	DWORD PTR result$[rsp], eax

; 162  : 		return result;

	mov	eax, DWORD PTR result$[rsp]
	jmp	SHORT $LN6@pci_expres
$LN1@pci_expres:
$LN2@pci_expres:
$LN4@pci_expres:

; 163  : 	}
; 164  : 
; 165  : 	return 0xFFFFFFFF;

	mov	eax, -1					; ffffffffH
$LN6@pci_expres:

; 166  : }

	add	rsp, 56					; 00000038H
	ret	0
?pci_express_read2@@YAIIHH@Z ENDP			; pci_express_read2
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\include\stdint.h
;	COMDAT ??$raw_offset@PECIPEA_K@@YAPECIPEA_KH@Z
_TEXT	SEGMENT
p1$ = 8
offset$ = 16
??$raw_offset@PECIPEA_K@@YAPECIPEA_KH@Z PROC		; raw_offset<unsigned int volatile * __ptr64,unsigned __int64 * __ptr64>, COMDAT

; 183  : 	{

	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx

; 184  : 		return (T) ((size_t)p1 + offset);

	movsxd	rax, DWORD PTR offset$[rsp]
	mov	rcx, QWORD PTR p1$[rsp]
	add	rcx, rax
	mov	rax, rcx

; 185  : 	};

	ret	0
??$raw_offset@PECIPEA_K@@YAPECIPEA_KH@Z ENDP		; raw_offset<unsigned int volatile * __ptr64,unsigned __int64 * __ptr64>
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\include\stdint.h
;	COMDAT ??$raw_offset@PECGPEA_K@@YAPECGPEA_KH@Z
_TEXT	SEGMENT
p1$ = 8
offset$ = 16
??$raw_offset@PECGPEA_K@@YAPECGPEA_KH@Z PROC		; raw_offset<unsigned short volatile * __ptr64,unsigned __int64 * __ptr64>, COMDAT

; 183  : 	{

	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx

; 184  : 		return (T) ((size_t)p1 + offset);

	movsxd	rax, DWORD PTR offset$[rsp]
	mov	rcx, QWORD PTR p1$[rsp]
	add	rcx, rax
	mov	rax, rcx

; 185  : 	};

	ret	0
??$raw_offset@PECGPEA_K@@YAPECGPEA_KH@Z ENDP		; raw_offset<unsigned short volatile * __ptr64,unsigned __int64 * __ptr64>
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\include\stdint.h
;	COMDAT ??$raw_offset@PECEPEA_K@@YAPECEPEA_KH@Z
_TEXT	SEGMENT
p1$ = 8
offset$ = 16
??$raw_offset@PECEPEA_K@@YAPECEPEA_KH@Z PROC		; raw_offset<unsigned char volatile * __ptr64,unsigned __int64 * __ptr64>, COMDAT

; 183  : 	{

	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx

; 184  : 		return (T) ((size_t)p1 + offset);

	movsxd	rax, DWORD PTR offset$[rsp]
	mov	rcx, QWORD PTR p1$[rsp]
	add	rcx, rax
	mov	rax, rcx

; 185  : 	};

	ret	0
??$raw_offset@PECEPEA_K@@YAPECEPEA_KH@Z ENDP		; raw_offset<unsigned char volatile * __ptr64,unsigned __int64 * __ptr64>
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\include\stdint.h
;	COMDAT ??$mem_after@PEAUacpiMcfgAlloc@@UacpiMcfg@@@@YAPEAUacpiMcfgAlloc@@PEAUacpiMcfg@@@Z
_TEXT	SEGMENT
p1$ = 8
??$mem_after@PEAUacpiMcfgAlloc@@UacpiMcfg@@@@YAPEAUacpiMcfgAlloc@@PEAUacpiMcfg@@@Z PROC ; mem_after<acpiMcfgAlloc * __ptr64,acpiMcfg>, COMDAT

; 187  : 	{

	mov	QWORD PTR [rsp+8], rcx

; 188  : 		return (T) (&p1[1]);

	mov	eax, 44					; 0000002cH
	imul	rax, 1
	mov	rcx, QWORD PTR p1$[rsp]
	add	rcx, rax
	mov	rax, rcx

; 189  : 	};

	ret	0
??$mem_after@PEAUacpiMcfgAlloc@@UacpiMcfg@@@@YAPEAUacpiMcfgAlloc@@PEAUacpiMcfg@@@Z ENDP ; mem_after<acpiMcfgAlloc * __ptr64,acpiMcfg>
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\pcie.cpp
_TEXT	SEGMENT
addr$ = 32
allocs$ = 40
mcfg$ = 48
segment$ = 80
bus$ = 88
device$ = 96
function$ = 104
?pci_express_get_device@@YAIGGGG@Z PROC			; pci_express_get_device

; 38   : uint32_t pci_express_get_device (uint16_t segment, uint16_t bus, uint16_t device, uint16_t function) {

$LN7:
	mov	WORD PTR [rsp+32], r9w
	mov	WORD PTR [rsp+24], r8w
	mov	WORD PTR [rsp+16], dx
	mov	WORD PTR [rsp+8], cx
	sub	rsp, 72					; 00000048H

; 39   : 	if (bus > 255)

	movzx	eax, WORD PTR bus$[rsp]
	cmp	eax, 255				; 000000ffH
	jle	SHORT $LN4@pci_expres

; 40   : 		return 0;

	xor	eax, eax
	jmp	$LN5@pci_expres
$LN4@pci_expres:

; 41   : 	if (device > 31)

	movzx	eax, WORD PTR device$[rsp]
	cmp	eax, 31
	jle	SHORT $LN3@pci_expres

; 42   : 		return 0;

	xor	eax, eax
	jmp	$LN5@pci_expres
$LN3@pci_expres:

; 43   : 	if (function > 7)

	movzx	eax, WORD PTR function$[rsp]
	cmp	eax, 7
	jle	SHORT $LN2@pci_expres

; 44   : 		return 0;

	xor	eax, eax
	jmp	$LN5@pci_expres
$LN2@pci_expres:

; 45   : 
; 46   : 	uint32_t addr = 0;

	mov	DWORD PTR addr$[rsp], 0

; 47   : 	acpiMcfg *mcfg = acpi_get_mcfg();

	call	?acpi_get_mcfg@@YAPEAUacpiMcfg@@XZ	; acpi_get_mcfg
	mov	QWORD PTR mcfg$[rsp], rax

; 48   : 	acpiMcfgAlloc *allocs = mem_after<acpiMcfgAlloc*>(mcfg);

	mov	rcx, QWORD PTR mcfg$[rsp]
	call	??$mem_after@PEAUacpiMcfgAlloc@@UacpiMcfg@@@@YAPEAUacpiMcfgAlloc@@PEAUacpiMcfg@@@Z ; mem_after<acpiMcfgAlloc * __ptr64,acpiMcfg>
	mov	QWORD PTR allocs$[rsp], rax

; 49   : 	if (allocs->startBusNum <= bus && bus <= allocs->endBusNum) {

	mov	rax, QWORD PTR allocs$[rsp]
	movzx	eax, BYTE PTR [rax+10]
	movzx	ecx, WORD PTR bus$[rsp]
	cmp	eax, ecx
	jg	SHORT $LN1@pci_expres
	movzx	eax, WORD PTR bus$[rsp]
	mov	rcx, QWORD PTR allocs$[rsp]
	movzx	ecx, BYTE PTR [rcx+11]
	cmp	eax, ecx
	jg	SHORT $LN1@pci_expres

; 50   : 		addr = allocs->baseAddress + ((bus - allocs->startBusNum) << 20) | (device << 15) | (function << 12);

	movzx	eax, WORD PTR bus$[rsp]
	mov	rcx, QWORD PTR allocs$[rsp]
	movzx	ecx, BYTE PTR [rcx+10]
	sub	eax, ecx
	shl	eax, 20
	cdqe
	mov	rcx, QWORD PTR allocs$[rsp]
	mov	rcx, QWORD PTR [rcx]
	add	rcx, rax
	mov	rax, rcx
	movzx	ecx, WORD PTR device$[rsp]
	shl	ecx, 15
	movsxd	rcx, ecx
	or	rax, rcx
	movzx	ecx, WORD PTR function$[rsp]
	shl	ecx, 12
	movsxd	rcx, ecx
	or	rax, rcx
	mov	DWORD PTR addr$[rsp], eax

; 51   : 		return addr;

	mov	eax, DWORD PTR addr$[rsp]
	jmp	SHORT $LN5@pci_expres
$LN1@pci_expres:

; 52   : 	}
; 53   : 
; 54   : 	return 0xFFFFFFFF;

	mov	eax, -1					; ffffffffH
$LN5@pci_expres:

; 55   : }

	add	rsp, 72					; 00000048H
	ret	0
?pci_express_get_device@@YAIGGGG@Z ENDP			; pci_express_get_device
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\pcie.cpp
_TEXT	SEGMENT
capptr$1 = 32
cap_reg$2 = 36
status$ = 40
device$ = 64
pcie_print_capabilities PROC

; 197  : void pcie_print_capabilities (uint32_t device) {

$LN8:
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 56					; 00000038H

; 198  : 	uint32_t status = pci_express_read2 (device,PCI_COMMAND, 4);

	mov	r8d, 4
	mov	edx, 4
	mov	ecx, DWORD PTR device$[rsp]
	call	?pci_express_read2@@YAIIHH@Z		; pci_express_read2
	mov	DWORD PTR status$[rsp], eax

; 199  : 	status >>= 16;

	mov	eax, DWORD PTR status$[rsp]
	shr	eax, 16
	mov	DWORD PTR status$[rsp], eax

; 200  : 	if ((status & (1<<4)) != 0) {

	mov	eax, DWORD PTR status$[rsp]
	and	eax, 16
	test	eax, eax
	je	$LN5@pcie_print

; 201  : 		uint32_t capptr = pci_express_read2(device,PCI_CAPABILITIES_PTR, 4);

	mov	r8d, 4
	mov	edx, 52					; 00000034H
	mov	ecx, DWORD PTR device$[rsp]
	call	?pci_express_read2@@YAIIHH@Z		; pci_express_read2
	mov	DWORD PTR capptr$1[rsp], eax

; 202  : 		capptr &= 0xFF; 

	mov	eax, DWORD PTR capptr$1[rsp]
	and	eax, 255				; 000000ffH
	mov	DWORD PTR capptr$1[rsp], eax

; 203  : 		uint32_t cap_reg = 0;

	mov	DWORD PTR cap_reg$2[rsp], 0
$LN4@pcie_print:

; 204  : 		while (capptr != 0) {

	cmp	DWORD PTR capptr$1[rsp], 0
	je	SHORT $LN3@pcie_print

; 205  : 			cap_reg = pci_express_read2(device,capptr, 4);

	mov	r8d, 4
	mov	edx, DWORD PTR capptr$1[rsp]
	mov	ecx, DWORD PTR device$[rsp]
	call	?pci_express_read2@@YAIIHH@Z		; pci_express_read2
	mov	DWORD PTR cap_reg$2[rsp], eax

; 206  : 			if ((cap_reg & 0xff) == 0x05) {

	mov	eax, DWORD PTR cap_reg$2[rsp]
	and	eax, 255				; 000000ffH
	cmp	eax, 5
	jne	SHORT $LN2@pcie_print

; 207  : 				printf ("MSI-X found for this device\n");

	lea	rcx, OFFSET FLAT:$SG3150
	call	printf

; 208  : 				break;

	jmp	SHORT $LN3@pcie_print
$LN2@pcie_print:

; 209  : 			}
; 210  : 
; 211  : 			if ((cap_reg & 0xff)  == 0x11) {

	mov	eax, DWORD PTR cap_reg$2[rsp]
	and	eax, 255				; 000000ffH
	cmp	eax, 17
	jne	SHORT $LN1@pcie_print

; 212  : 				printf ("MSI found for this device\n");

	lea	rcx, OFFSET FLAT:$SG3152
	call	printf

; 213  : 				break;

	jmp	SHORT $LN3@pcie_print
$LN1@pcie_print:

; 214  : 			}
; 215  : 			capptr = ((cap_reg >> 8) & 0xff);   //((cap_reg >> 8) & 0xFF) / 4;

	mov	eax, DWORD PTR cap_reg$2[rsp]
	shr	eax, 8
	and	eax, 255				; 000000ffH
	mov	DWORD PTR capptr$1[rsp], eax

; 216  : 		}

	jmp	SHORT $LN4@pcie_print
$LN3@pcie_print:
$LN5@pcie_print:

; 217  : 	}
; 218  : }

	add	rsp, 56					; 00000038H
	ret	0
pcie_print_capabilities ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\pcie.cpp
_TEXT	SEGMENT
size$ = 32
result$ = 36
tv71 = 40
address$ = 48
device$ = 80
reg$ = 88
pci_express_read PROC

; 57   : uint32_t pci_express_read (uint32_t device, int reg) {

$LN35:
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 72					; 00000048H

; 58   : 	if(acpi_pcie_supported() == false) {

	call	?acpi_pcie_supported@@YA_NXZ		; acpi_pcie_supported
	movzx	eax, al
	test	eax, eax
	jne	SHORT $LN30@pci_expres

; 59   : 		return pci_read(device,reg);

	mov	edx, DWORD PTR reg$[rsp]
	mov	ecx, DWORD PTR device$[rsp]
	call	pci_read
	jmp	$LN31@pci_expres
$LN30@pci_expres:

; 60   : 	}
; 61   : 
; 62   : 	size_t* address = (size_t*)device;

	mov	eax, DWORD PTR device$[rsp]
	mov	QWORD PTR address$[rsp], rax

; 63   : 	uint32_t result = 0;

	mov	DWORD PTR result$[rsp], 0

; 64   : 
; 65   : 	int size = 0;

	mov	DWORD PTR size$[rsp], 0

; 66   : 	switch(reg) {

	mov	eax, DWORD PTR reg$[rsp]
	mov	DWORD PTR tv71[rsp], eax
	cmp	DWORD PTR tv71[rsp], 61			; 0000003dH
	ja	$LN6@pci_expres
	movsxd	rax, DWORD PTR tv71[rsp]
	lea	rcx, OFFSET FLAT:__ImageBase
	movzx	eax, BYTE PTR $LN33@pci_expres[rcx+rax]
	mov	eax, DWORD PTR $LN34@pci_expres[rcx+rax*4]
	add	rax, rcx
	jmp	rax
$LN27@pci_expres:

; 67   : 	case PCI_VENDOR_ID:
; 68   : 		size = 2;

	mov	DWORD PTR size$[rsp], 2

; 69   : 		break;

	jmp	$LN28@pci_expres
$LN26@pci_expres:

; 70   : 	case PCI_DEVICE_ID:
; 71   : 		size = 2;

	mov	DWORD PTR size$[rsp], 2

; 72   : 		break;

	jmp	$LN28@pci_expres
$LN25@pci_expres:

; 73   : 	case PCI_COMMAND:
; 74   : 		size = 2;

	mov	DWORD PTR size$[rsp], 2

; 75   : 		break;

	jmp	$LN28@pci_expres
$LN24@pci_expres:

; 76   : 	case PCI_STATUS:
; 77   : 		size = 2;

	mov	DWORD PTR size$[rsp], 2

; 78   : 		break;

	jmp	$LN28@pci_expres
$LN23@pci_expres:

; 79   : 	case PCI_REVISION_ID:
; 80   : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 81   : 		break;

	jmp	$LN28@pci_expres
$LN22@pci_expres:

; 82   : 	case PCI_PROG_IF:
; 83   : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 84   : 		break;

	jmp	$LN28@pci_expres
$LN21@pci_expres:

; 85   : 	case PCI_SUBCLASS:
; 86   : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 87   : 		break;

	jmp	$LN28@pci_expres
$LN20@pci_expres:

; 88   : 	case PCI_CLASS:
; 89   : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 90   : 		break;

	jmp	$LN28@pci_expres
$LN19@pci_expres:

; 91   : 	case PCI_CACHE_LINE_SIZE:
; 92   : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 93   : 		break;

	jmp	$LN28@pci_expres
$LN18@pci_expres:

; 94   : 	case PCI_LATENCY_TIMER:
; 95   : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 96   : 		break;

	jmp	SHORT $LN28@pci_expres
$LN17@pci_expres:

; 97   : 	case PCI_HEADER_TYPE:
; 98   : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 99   : 		break;

	jmp	SHORT $LN28@pci_expres
$LN16@pci_expres:

; 100  : 	case PCI_BIST:
; 101  : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 102  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN15@pci_expres:

; 103  : 	case PCI_BAR0:
; 104  : 		size = 4;

	mov	DWORD PTR size$[rsp], 4

; 105  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN14@pci_expres:

; 106  : 	case PCI_BAR1:
; 107  : 		size = 4;

	mov	DWORD PTR size$[rsp], 4

; 108  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN13@pci_expres:

; 109  : 	case PCI_BAR2:
; 110  : 		size = 4;

	mov	DWORD PTR size$[rsp], 4

; 111  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN12@pci_expres:

; 112  : 	case PCI_BAR3:
; 113  : 		size = 4;

	mov	DWORD PTR size$[rsp], 4

; 114  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN11@pci_expres:

; 115  : 	case PCI_BAR4:
; 116  : 		size = 4;

	mov	DWORD PTR size$[rsp], 4

; 117  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN10@pci_expres:

; 118  : 	case PCI_BAR5:
; 119  : 		size = 4;

	mov	DWORD PTR size$[rsp], 4

; 120  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN9@pci_expres:

; 121  : 	case PCI_CAPABILITIES_PTR:
; 122  : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 123  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN8@pci_expres:

; 124  : 	case PCI_INTERRUPT_LINE:
; 125  : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 126  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN7@pci_expres:

; 127  : 	case PCI_INTERRUPT_PIN:
; 128  : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 129  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN6@pci_expres:

; 130  : 	default:
; 131  : 		size = 4;

	mov	DWORD PTR size$[rsp], 4
$LN28@pci_expres:

; 132  : 		break;
; 133  : 	}
; 134  : 
; 135  : 	if (size == 1){

	cmp	DWORD PTR size$[rsp], 1
	jne	SHORT $LN5@pci_expres

; 136  : 		result = *raw_offset<volatile uint8_t*>(address, reg);

	mov	edx, DWORD PTR reg$[rsp]
	mov	rcx, QWORD PTR address$[rsp]
	call	??$raw_offset@PECEPEA_K@@YAPECEPEA_KH@Z	; raw_offset<unsigned char volatile * __ptr64,unsigned __int64 * __ptr64>
	movzx	eax, BYTE PTR [rax]
	movzx	eax, al
	mov	DWORD PTR result$[rsp], eax

; 137  : 		return result;

	mov	eax, DWORD PTR result$[rsp]
	jmp	SHORT $LN31@pci_expres
	jmp	SHORT $LN4@pci_expres
$LN5@pci_expres:

; 138  : 	}else if (size == 2) {

	cmp	DWORD PTR size$[rsp], 2
	jne	SHORT $LN3@pci_expres

; 139  : 		result = *raw_offset<volatile uint16_t*>(address, reg);

	mov	edx, DWORD PTR reg$[rsp]
	mov	rcx, QWORD PTR address$[rsp]
	call	??$raw_offset@PECGPEA_K@@YAPECGPEA_KH@Z	; raw_offset<unsigned short volatile * __ptr64,unsigned __int64 * __ptr64>
	movzx	eax, WORD PTR [rax]
	movzx	eax, ax
	mov	DWORD PTR result$[rsp], eax

; 140  : 		return result;

	mov	eax, DWORD PTR result$[rsp]
	jmp	SHORT $LN31@pci_expres
	jmp	SHORT $LN2@pci_expres
$LN3@pci_expres:

; 141  : 	}else if (size == 4) {

	cmp	DWORD PTR size$[rsp], 4
	jne	SHORT $LN1@pci_expres

; 142  : 		result = *raw_offset<volatile uint32_t*>(address, reg);

	mov	edx, DWORD PTR reg$[rsp]
	mov	rcx, QWORD PTR address$[rsp]
	call	??$raw_offset@PECIPEA_K@@YAPECIPEA_KH@Z	; raw_offset<unsigned int volatile * __ptr64,unsigned __int64 * __ptr64>
	mov	eax, DWORD PTR [rax]
	mov	DWORD PTR result$[rsp], eax

; 143  : 		return result;

	mov	eax, DWORD PTR result$[rsp]
	jmp	SHORT $LN31@pci_expres
$LN1@pci_expres:
$LN2@pci_expres:
$LN4@pci_expres:

; 144  : 	}
; 145  : 
; 146  : 	return 0xFFFFFFFF;

	mov	eax, -1					; ffffffffH
$LN31@pci_expres:

; 147  : }

	add	rsp, 72					; 00000048H
	ret	0
$LN34@pci_expres:
	DD	$LN27@pci_expres
	DD	$LN26@pci_expres
	DD	$LN25@pci_expres
	DD	$LN24@pci_expres
	DD	$LN23@pci_expres
	DD	$LN22@pci_expres
	DD	$LN21@pci_expres
	DD	$LN20@pci_expres
	DD	$LN19@pci_expres
	DD	$LN18@pci_expres
	DD	$LN17@pci_expres
	DD	$LN16@pci_expres
	DD	$LN15@pci_expres
	DD	$LN14@pci_expres
	DD	$LN13@pci_expres
	DD	$LN12@pci_expres
	DD	$LN11@pci_expres
	DD	$LN10@pci_expres
	DD	$LN9@pci_expres
	DD	$LN8@pci_expres
	DD	$LN7@pci_expres
	DD	$LN6@pci_expres
$LN33@pci_expres:
	DB	0
	DB	21
	DB	1
	DB	21
	DB	2
	DB	21
	DB	3
	DB	21
	DB	4
	DB	5
	DB	6
	DB	7
	DB	8
	DB	9
	DB	10
	DB	11
	DB	12
	DB	21
	DB	21
	DB	21
	DB	13
	DB	21
	DB	21
	DB	21
	DB	14
	DB	21
	DB	21
	DB	21
	DB	15
	DB	21
	DB	21
	DB	21
	DB	16
	DB	21
	DB	21
	DB	21
	DB	17
	DB	21
	DB	21
	DB	21
	DB	21
	DB	21
	DB	21
	DB	21
	DB	21
	DB	21
	DB	21
	DB	21
	DB	21
	DB	21
	DB	21
	DB	21
	DB	18
	DB	21
	DB	21
	DB	21
	DB	21
	DB	21
	DB	21
	DB	21
	DB	19
	DB	20
pci_express_read ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\pcie.cpp
_TEXT	SEGMENT
func$1 = 32
dev$2 = 36
bus$3 = 40
address$4 = 44
class_code$5 = 48
sub_ClassCode$6 = 52
allocs$ = 56
mcfg$ = 64
classCode$ = 96
subClassCode$ = 104
pci_express_scan_class PROC

; 169  : uint32_t pci_express_scan_class (uint8_t classCode, uint8_t subClassCode) {

$LN15:
	mov	BYTE PTR [rsp+16], dl
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 88					; 00000058H

; 170  : 	if(acpi_pcie_supported() == false) {

	call	?acpi_pcie_supported@@YA_NXZ		; acpi_pcie_supported
	movzx	eax, al
	test	eax, eax
	jne	SHORT $LN12@pci_expres

; 171  : 		return pci_scan_class(classCode, subClassCode);

	movzx	edx, BYTE PTR subClassCode$[rsp]
	movzx	ecx, BYTE PTR classCode$[rsp]
	call	pci_scan_class
	jmp	$LN13@pci_expres
$LN12@pci_expres:

; 172  : 	}
; 173  : 
; 174  : 	acpiMcfg *mcfg = acpi_get_mcfg();

	call	?acpi_get_mcfg@@YAPEAUacpiMcfg@@XZ	; acpi_get_mcfg
	mov	QWORD PTR mcfg$[rsp], rax

; 175  : 	acpiMcfgAlloc *allocs = mem_after<acpiMcfgAlloc*>(mcfg);

	mov	rcx, QWORD PTR mcfg$[rsp]
	call	??$mem_after@PEAUacpiMcfgAlloc@@UacpiMcfg@@@@YAPEAUacpiMcfgAlloc@@PEAUacpiMcfg@@@Z ; mem_after<acpiMcfgAlloc * __ptr64,acpiMcfg>
	mov	QWORD PTR allocs$[rsp], rax

; 176  : 
; 177  : 	for (int bus = 0; bus < allocs->endBusNum; bus++){

	mov	DWORD PTR bus$3[rsp], 0
	jmp	SHORT $LN11@pci_expres
$LN10@pci_expres:
	mov	eax, DWORD PTR bus$3[rsp]
	inc	eax
	mov	DWORD PTR bus$3[rsp], eax
$LN11@pci_expres:
	mov	rax, QWORD PTR allocs$[rsp]
	movzx	eax, BYTE PTR [rax+11]
	cmp	DWORD PTR bus$3[rsp], eax
	jge	$LN9@pci_expres

; 178  : 		for (int dev = 0; dev < PCI_DEVICE_PER_BUS; dev++) {

	mov	DWORD PTR dev$2[rsp], 0
	jmp	SHORT $LN8@pci_expres
$LN7@pci_expres:
	mov	eax, DWORD PTR dev$2[rsp]
	inc	eax
	mov	DWORD PTR dev$2[rsp], eax
$LN8@pci_expres:
	cmp	DWORD PTR dev$2[rsp], 32		; 00000020H
	jge	$LN6@pci_expres

; 179  : 			for (int func = 0; func < PCI_FUNCTION_PER_DEVICE; func++) {

	mov	DWORD PTR func$1[rsp], 0
	jmp	SHORT $LN5@pci_expres
$LN4@pci_expres:
	mov	eax, DWORD PTR func$1[rsp]
	inc	eax
	mov	DWORD PTR func$1[rsp], eax
$LN5@pci_expres:
	cmp	DWORD PTR func$1[rsp], 8
	jge	SHORT $LN3@pci_expres

; 180  : 				uint32_t address = pci_express_get_device(allocs->pciSegment, bus,dev,func);

	movzx	r9d, WORD PTR func$1[rsp]
	movzx	r8d, WORD PTR dev$2[rsp]
	movzx	edx, WORD PTR bus$3[rsp]
	mov	rax, QWORD PTR allocs$[rsp]
	movzx	ecx, WORD PTR [rax+8]
	call	?pci_express_get_device@@YAIGGGG@Z	; pci_express_get_device
	mov	DWORD PTR address$4[rsp], eax

; 181  : 				//debug_print ("Dev Address ->%x \n", address);
; 182  : 				if (address == 0xFFFFFFFF)

	cmp	DWORD PTR address$4[rsp], -1		; ffffffffH
	jne	SHORT $LN2@pci_expres

; 183  : 					continue;

	jmp	SHORT $LN4@pci_expres
$LN2@pci_expres:

; 184  : 				uint32_t class_code = pci_express_read(address,PCI_CLASS);

	mov	edx, 11
	mov	ecx, DWORD PTR address$4[rsp]
	call	pci_express_read
	mov	DWORD PTR class_code$5[rsp], eax

; 185  : 				uint32_t sub_ClassCode = pci_express_read(address, PCI_SUBCLASS);

	mov	edx, 10
	mov	ecx, DWORD PTR address$4[rsp]
	call	pci_express_read
	mov	DWORD PTR sub_ClassCode$6[rsp], eax

; 186  : 				//debug_print ("ClassCode -> %x, SubClass -> %x \n", classCode, sub_ClassCode);
; 187  : 				if(class_code == classCode && sub_ClassCode == subClassCode) {

	movzx	eax, BYTE PTR classCode$[rsp]
	cmp	DWORD PTR class_code$5[rsp], eax
	jne	SHORT $LN1@pci_expres
	movzx	eax, BYTE PTR subClassCode$[rsp]
	cmp	DWORD PTR sub_ClassCode$6[rsp], eax
	jne	SHORT $LN1@pci_expres

; 188  : 					return address;

	mov	eax, DWORD PTR address$4[rsp]
	jmp	SHORT $LN13@pci_expres
$LN1@pci_expres:

; 189  : 				}
; 190  : 			}

	jmp	SHORT $LN4@pci_expres
$LN3@pci_expres:

; 191  : 		}

	jmp	$LN7@pci_expres
$LN6@pci_expres:

; 192  : 	}

	jmp	$LN10@pci_expres
$LN9@pci_expres:

; 193  : 
; 194  : 	return 0xFFFFFFFF;

	mov	eax, -1					; ffffffffH
$LN13@pci_expres:

; 195  : }

	add	rsp, 88					; 00000058H
	ret	0
pci_express_scan_class ENDP
_TEXT	ENDS
END