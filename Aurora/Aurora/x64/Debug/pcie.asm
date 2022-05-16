; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

CONST	SEGMENT
$SG3458	DB	'MSI found for this device', 0aH, 00H
	ORG $+5
$SG3462	DB	'writing msi address -> %x, as -> %x ', 0aH, 00H
	ORG $+2
$SG3466	DB	'MSI Debug Addr -> %x , msi_data -> %d ', 0aH, 00H
$SG3471	DB	'64Bit msi', 0aH, 00H
	ORG $+5
$SG3474	DB	'Maskable msi', 0aH, 00H
	ORG $+2
$SG3478	DB	'MSI DATA REREAD -> %d', 0aH, 00H
	ORG $+1
$SG3480	DB	'MSI-X found for this device', 0aH, 00H
CONST	ENDS
PUBLIC	pci_express_scan_class
PUBLIC	pci_express_read
PUBLIC	pci_express_write
PUBLIC	pcie_alloc_msi
PUBLIC	?pci_express_get_device@@YAIGGGG@Z		; pci_express_get_device
PUBLIC	??$mem_after@PEAUacpiMcfgAlloc@@UacpiMcfg@@@@YAPEAUacpiMcfgAlloc@@PEAUacpiMcfg@@@Z ; mem_after<acpiMcfgAlloc * __ptr64,acpiMcfg>
PUBLIC	??$raw_offset@PECEPEA_K@@YAPECEPEA_KH@Z		; raw_offset<unsigned char volatile * __ptr64,unsigned __int64 * __ptr64>
PUBLIC	??$raw_offset@PECGPEA_K@@YAPECGPEA_KH@Z		; raw_offset<unsigned short volatile * __ptr64,unsigned __int64 * __ptr64>
PUBLIC	??$raw_offset@PECIPEA_K@@YAPECIPEA_KH@Z		; raw_offset<unsigned int volatile * __ptr64,unsigned __int64 * __ptr64>
PUBLIC	?pci_express_read2@@YAIIHH@Z			; pci_express_read2
EXTRN	pci_read:PROC
EXTRN	pci_scan_class:PROC
EXTRN	pci_write:PROC
EXTRN	?acpi_pcie_supported@@YA_NXZ:PROC		; acpi_pcie_supported
EXTRN	?acpi_get_mcfg@@YAPEAUacpiMcfg@@XZ:PROC		; acpi_get_mcfg
EXTRN	printf:PROC
EXTRN	?cpu_msi_address@@YA_KPEA_K_KIEE@Z:PROC		; cpu_msi_address
EXTRN	__ImageBase:BYTE
pdata	SEGMENT
$pdata$pci_express_scan_class DD imagerel $LN19
	DD	imagerel $LN19+369
	DD	imagerel $unwind$pci_express_scan_class
$pdata$pci_express_read DD imagerel $LN35
	DD	imagerel $LN35+634
	DD	imagerel $unwind$pci_express_read
$pdata$pci_express_write DD imagerel $LN35
	DD	imagerel $LN35+618
	DD	imagerel $unwind$pci_express_write
$pdata$pcie_alloc_msi DD imagerel $LN15
	DD	imagerel $LN15+815
	DD	imagerel $unwind$pcie_alloc_msi
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
$unwind$pci_express_write DD 011101H
	DD	06211H
$unwind$pcie_alloc_msi DD 021001H
	DD	0110110H
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

; 237  : uint32_t pci_express_read2 (uint32_t device, int reg, int size) {

$LN8:
	mov	DWORD PTR [rsp+24], r8d
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 56					; 00000038H

; 238  : 	size_t* address = (size_t*)device;

	mov	eax, DWORD PTR device$[rsp]
	mov	QWORD PTR address$[rsp], rax

; 239  : 	uint32_t result = 0;

	mov	DWORD PTR result$[rsp], 0

; 240  : 
; 241  : 	if (size == 1){

	cmp	DWORD PTR size$[rsp], 1
	jne	SHORT $LN5@pci_expres

; 242  : 		result = *raw_offset<volatile uint8_t*>(address, reg);

	mov	edx, DWORD PTR reg$[rsp]
	mov	rcx, QWORD PTR address$[rsp]
	call	??$raw_offset@PECEPEA_K@@YAPECEPEA_KH@Z	; raw_offset<unsigned char volatile * __ptr64,unsigned __int64 * __ptr64>
	movzx	eax, BYTE PTR [rax]
	movzx	eax, al
	mov	DWORD PTR result$[rsp], eax

; 243  : 		return result;

	mov	eax, DWORD PTR result$[rsp]
	jmp	SHORT $LN6@pci_expres
	jmp	SHORT $LN4@pci_expres
$LN5@pci_expres:

; 244  : 	}else if (size == 2) {

	cmp	DWORD PTR size$[rsp], 2
	jne	SHORT $LN3@pci_expres

; 245  : 		result = *raw_offset<volatile uint16_t*>(address, reg);

	mov	edx, DWORD PTR reg$[rsp]
	mov	rcx, QWORD PTR address$[rsp]
	call	??$raw_offset@PECGPEA_K@@YAPECGPEA_KH@Z	; raw_offset<unsigned short volatile * __ptr64,unsigned __int64 * __ptr64>
	movzx	eax, WORD PTR [rax]
	movzx	eax, ax
	mov	DWORD PTR result$[rsp], eax

; 246  : 		return result;

	mov	eax, DWORD PTR result$[rsp]
	jmp	SHORT $LN6@pci_expres
	jmp	SHORT $LN2@pci_expres
$LN3@pci_expres:

; 247  : 	}else if (size == 4) {

	cmp	DWORD PTR size$[rsp], 4
	jne	SHORT $LN1@pci_expres

; 248  : 		result = *raw_offset<volatile uint32_t*>(address, reg);

	mov	edx, DWORD PTR reg$[rsp]
	mov	rcx, QWORD PTR address$[rsp]
	call	??$raw_offset@PECIPEA_K@@YAPECIPEA_KH@Z	; raw_offset<unsigned int volatile * __ptr64,unsigned __int64 * __ptr64>
	mov	eax, DWORD PTR [rax]
	mov	DWORD PTR result$[rsp], eax

; 249  : 		return result;

	mov	eax, DWORD PTR result$[rsp]
	jmp	SHORT $LN6@pci_expres
$LN1@pci_expres:
$LN2@pci_expres:
$LN4@pci_expres:

; 250  : 	}
; 251  : 
; 252  : 	return 0xABCD;

	mov	eax, 43981				; 0000abcdH
$LN6@pci_expres:

; 253  : }

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

; 39   : uint32_t pci_express_get_device (uint16_t segment, uint16_t bus, uint16_t device, uint16_t function) {

$LN7:
	mov	WORD PTR [rsp+32], r9w
	mov	WORD PTR [rsp+24], r8w
	mov	WORD PTR [rsp+16], dx
	mov	WORD PTR [rsp+8], cx
	sub	rsp, 72					; 00000048H

; 40   : 	if (bus > 255)

	movzx	eax, WORD PTR bus$[rsp]
	cmp	eax, 255				; 000000ffH
	jle	SHORT $LN4@pci_expres

; 41   : 		return 0;

	xor	eax, eax
	jmp	$LN5@pci_expres
$LN4@pci_expres:

; 42   : 	if (device > 31)

	movzx	eax, WORD PTR device$[rsp]
	cmp	eax, 31
	jle	SHORT $LN3@pci_expres

; 43   : 		return 0;

	xor	eax, eax
	jmp	$LN5@pci_expres
$LN3@pci_expres:

; 44   : 	if (function > 7)

	movzx	eax, WORD PTR function$[rsp]
	cmp	eax, 7
	jle	SHORT $LN2@pci_expres

; 45   : 		return 0;

	xor	eax, eax
	jmp	$LN5@pci_expres
$LN2@pci_expres:

; 46   : 
; 47   : 	uint32_t addr = 0;

	mov	DWORD PTR addr$[rsp], 0

; 48   : 	acpiMcfg *mcfg = acpi_get_mcfg();

	call	?acpi_get_mcfg@@YAPEAUacpiMcfg@@XZ	; acpi_get_mcfg
	mov	QWORD PTR mcfg$[rsp], rax

; 49   : 	acpiMcfgAlloc *allocs = mem_after<acpiMcfgAlloc*>(mcfg);

	mov	rcx, QWORD PTR mcfg$[rsp]
	call	??$mem_after@PEAUacpiMcfgAlloc@@UacpiMcfg@@@@YAPEAUacpiMcfgAlloc@@PEAUacpiMcfg@@@Z ; mem_after<acpiMcfgAlloc * __ptr64,acpiMcfg>
	mov	QWORD PTR allocs$[rsp], rax

; 50   : 	if (allocs->startBusNum <= bus && bus <= allocs->endBusNum) {

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

; 51   : 		addr = allocs->baseAddress + ((bus - allocs->startBusNum) << 20) | (device << 15) | (function << 12);

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

; 52   : 		return addr;

	mov	eax, DWORD PTR addr$[rsp]
	jmp	SHORT $LN5@pci_expres
$LN1@pci_expres:

; 53   : 	}
; 54   : 
; 55   : 	return 0xFFFFFFFF;

	mov	eax, -1					; ffffffffH
$LN5@pci_expres:

; 56   : }

	add	rsp, 72					; 00000048H
	ret	0
?pci_express_get_device@@YAIGGGG@Z ENDP			; pci_express_get_device
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\pcie.cpp
_TEXT	SEGMENT
msi_reg$1 = 48
cap_reg$2 = 52
maskcap$3 = 56
bit64_cap$4 = 57
mscntrl$5 = 60
capptr$6 = 64
data_offset$7 = 68
status$ = 72
msi_addr$8 = 80
tv150 = 88
tv146 = 92
msi_data$9 = 96
debug_addr$10 = 104
msd$11 = 112
device$ = 144
vector$ = 152
pcie_alloc_msi PROC

; 290  : void pcie_alloc_msi (uint32_t device, size_t vector) {

$LN15:
	mov	QWORD PTR [rsp+16], rdx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 136				; 00000088H

; 291  : 	if (acpi_pcie_supported() == false)

	call	?acpi_pcie_supported@@YA_NXZ		; acpi_pcie_supported
	movzx	eax, al
	test	eax, eax
	jne	SHORT $LN8@pcie_alloc

; 292  : 		return;

	jmp	$LN9@pcie_alloc
$LN8@pcie_alloc:

; 293  : 
; 294  : 	uint32_t status = pci_express_read2 (device,PCI_COMMAND, 4);

	mov	r8d, 4
	mov	edx, 4
	mov	ecx, DWORD PTR device$[rsp]
	call	?pci_express_read2@@YAIIHH@Z		; pci_express_read2
	mov	DWORD PTR status$[rsp], eax

; 295  : 	status >>= 16;

	mov	eax, DWORD PTR status$[rsp]
	shr	eax, 16
	mov	DWORD PTR status$[rsp], eax

; 296  : 	if ((status & (1<<4)) != 0) {

	mov	eax, DWORD PTR status$[rsp]
	and	eax, 16
	test	eax, eax
	je	$LN7@pcie_alloc

; 297  : 		uint32_t capptr = pci_express_read2(device,PCI_CAPABILITIES_PTR, 4);

	mov	r8d, 4
	mov	edx, 52					; 00000034H
	mov	ecx, DWORD PTR device$[rsp]
	call	?pci_express_read2@@YAIIHH@Z		; pci_express_read2
	mov	DWORD PTR capptr$6[rsp], eax

; 298  : 		capptr &= 0xFF; 

	mov	eax, DWORD PTR capptr$6[rsp]
	and	eax, 255				; 000000ffH
	mov	DWORD PTR capptr$6[rsp], eax

; 299  : 		uint32_t cap_reg = 0;

	mov	DWORD PTR cap_reg$2[rsp], 0

; 300  : 		uint32_t msi_reg = 0;

	mov	DWORD PTR msi_reg$1[rsp], 0
$LN6@pcie_alloc:

; 301  : 		while (capptr != 0) {

	cmp	DWORD PTR capptr$6[rsp], 0
	je	$LN5@pcie_alloc

; 302  : 			cap_reg = pci_express_read2(device,capptr, 4);

	mov	r8d, 4
	mov	edx, DWORD PTR capptr$6[rsp]
	mov	ecx, DWORD PTR device$[rsp]
	call	?pci_express_read2@@YAIIHH@Z		; pci_express_read2
	mov	DWORD PTR cap_reg$2[rsp], eax

; 303  : 			if ((cap_reg & 0xff) == 0x05) {

	mov	eax, DWORD PTR cap_reg$2[rsp]
	and	eax, 255				; 000000ffH
	cmp	eax, 5
	jne	$LN4@pcie_alloc

; 304  : 				printf ("MSI found for this device\n");

	lea	rcx, OFFSET FLAT:$SG3458
	call	printf

; 305  : 				msi_reg = cap_reg;

	mov	eax, DWORD PTR cap_reg$2[rsp]
	mov	DWORD PTR msi_reg$1[rsp], eax

; 306  : 				uint32_t mscntrl = cap_reg >> 16;

	mov	eax, DWORD PTR cap_reg$2[rsp]
	shr	eax, 16
	mov	DWORD PTR mscntrl$5[rsp], eax

; 307  : 				//printf ("MSIReg -> %x, cntrl -> %x \n", (device + msi_reg), mscntrl);
; 308  : 				uint64_t msi_data;
; 309  : 				uint64_t msi_addr = cpu_msi_address(&msi_data,vector,0,1,0);

	mov	BYTE PTR [rsp+32], 0
	mov	r9b, 1
	xor	r8d, r8d
	mov	rdx, QWORD PTR vector$[rsp]
	lea	rcx, QWORD PTR msi_data$9[rsp]
	call	?cpu_msi_address@@YA_KPEA_K_KIEE@Z	; cpu_msi_address
	mov	QWORD PTR msi_addr$8[rsp], rax

; 310  : 				printf ("writing msi address -> %x, as -> %x \n", msi_addr, (msi_addr & 0xffffffff));

	mov	eax, -1					; ffffffffH
	mov	rcx, QWORD PTR msi_addr$8[rsp]
	and	rcx, rax
	mov	rax, rcx
	mov	r8, rax
	mov	rdx, QWORD PTR msi_addr$8[rsp]
	lea	rcx, OFFSET FLAT:$SG3462
	call	printf

; 311  : 				pci_express_write(device,msi_reg + 1, msi_addr);

	mov	eax, DWORD PTR msi_reg$1[rsp]
	inc	eax
	mov	r8d, DWORD PTR msi_addr$8[rsp]
	mov	edx, eax
	mov	ecx, DWORD PTR device$[rsp]
	call	pci_express_write

; 312  : 				*(uint64_t*)(device + msi_reg + 1) = msi_addr & UINT32_MAX;

	mov	eax, -1					; ffffffffH
	mov	rcx, QWORD PTR msi_addr$8[rsp]
	and	rcx, rax
	mov	rax, rcx
	mov	ecx, DWORD PTR device$[rsp]
	mov	edx, DWORD PTR msi_reg$1[rsp]
	lea	ecx, DWORD PTR [rcx+rdx+1]
	mov	ecx, ecx
	mov	QWORD PTR [rcx], rax

; 313  : 
; 314  : 				uint64_t debug_addr = *(uint64_t*)(device + msi_reg + 1);

	mov	eax, DWORD PTR device$[rsp]
	mov	ecx, DWORD PTR msi_reg$1[rsp]
	lea	eax, DWORD PTR [rax+rcx+1]
	mov	eax, eax
	mov	rax, QWORD PTR [rax]
	mov	QWORD PTR debug_addr$10[rsp], rax

; 315  : 				printf ("MSI Debug Addr -> %x , msi_data -> %d \n", debug_addr, msi_data);

	mov	r8, QWORD PTR msi_data$9[rsp]
	mov	rdx, QWORD PTR debug_addr$10[rsp]
	lea	rcx, OFFSET FLAT:$SG3466
	call	printf

; 316  : 				
; 317  : 				bool bit64_cap = ((mscntrl & (1<<7)) != 0);

	mov	eax, DWORD PTR mscntrl$5[rsp]
	and	eax, 128				; 00000080H
	test	eax, eax
	je	SHORT $LN11@pcie_alloc
	mov	DWORD PTR tv146[rsp], 1
	jmp	SHORT $LN12@pcie_alloc
$LN11@pcie_alloc:
	mov	DWORD PTR tv146[rsp], 0
$LN12@pcie_alloc:
	movzx	eax, BYTE PTR tv146[rsp]
	mov	BYTE PTR bit64_cap$4[rsp], al

; 318  : 				bool maskcap = ((mscntrl & (1<<8)) != 0);

	mov	eax, DWORD PTR mscntrl$5[rsp]
	and	eax, 256				; 00000100H
	test	eax, eax
	je	SHORT $LN13@pcie_alloc
	mov	DWORD PTR tv150[rsp], 1
	jmp	SHORT $LN14@pcie_alloc
$LN13@pcie_alloc:
	mov	DWORD PTR tv150[rsp], 0
$LN14@pcie_alloc:
	movzx	eax, BYTE PTR tv150[rsp]
	mov	BYTE PTR maskcap$3[rsp], al

; 319  : 
; 320  : 				uint32_t data_offset = 2;

	mov	DWORD PTR data_offset$7[rsp], 2

; 321  : 				if (bit64_cap){

	movzx	eax, BYTE PTR bit64_cap$4[rsp]
	test	eax, eax
	je	SHORT $LN3@pcie_alloc

; 322  : 					pci_express_write(device, msi_reg + 2,(msi_addr >> 32));

	mov	rax, QWORD PTR msi_addr$8[rsp]
	shr	rax, 32					; 00000020H
	mov	ecx, DWORD PTR msi_reg$1[rsp]
	add	ecx, 2
	mov	r8d, eax
	mov	edx, ecx
	mov	ecx, DWORD PTR device$[rsp]
	call	pci_express_write

; 323  : 					printf ("64Bit msi\n");

	lea	rcx, OFFSET FLAT:$SG3471
	call	printf

; 324  : 					++data_offset;

	mov	eax, DWORD PTR data_offset$7[rsp]
	inc	eax
	mov	DWORD PTR data_offset$7[rsp], eax
$LN3@pcie_alloc:

; 325  : 				}if (maskcap){

	movzx	eax, BYTE PTR maskcap$3[rsp]
	test	eax, eax
	je	SHORT $LN2@pcie_alloc

; 326  : 					pci_express_write(device, msi_reg + 4, 0);

	mov	eax, DWORD PTR msi_reg$1[rsp]
	add	eax, 4
	xor	r8d, r8d
	mov	edx, eax
	mov	ecx, DWORD PTR device$[rsp]
	call	pci_express_write

; 327  : 					*(uint64_t*)(device + msi_reg + 4) = 0;

	mov	eax, DWORD PTR device$[rsp]
	mov	ecx, DWORD PTR msi_reg$1[rsp]
	lea	eax, DWORD PTR [rax+rcx+4]
	mov	eax, eax
	mov	QWORD PTR [rax], 0

; 328  : 					printf ("Maskable msi\n");

	lea	rcx, OFFSET FLAT:$SG3474
	call	printf
$LN2@pcie_alloc:

; 329  : 				}
; 330  : 
; 331  : 				//pci_express_write(device,msi_reg + data_offset,msi_data);
; 332  : 				*(uint64_t*)(device + msi_reg + data_offset) = msi_data;

	mov	eax, DWORD PTR msi_reg$1[rsp]
	mov	ecx, DWORD PTR device$[rsp]
	add	ecx, eax
	mov	eax, ecx
	add	eax, DWORD PTR data_offset$7[rsp]
	mov	eax, eax
	mov	rcx, QWORD PTR msi_data$9[rsp]
	mov	QWORD PTR [rax], rcx

; 333  : 				uint64_t msd = *(uint64_t*)(device + msi_reg + data_offset);

	mov	eax, DWORD PTR msi_reg$1[rsp]
	mov	ecx, DWORD PTR device$[rsp]
	add	ecx, eax
	mov	eax, ecx
	add	eax, DWORD PTR data_offset$7[rsp]
	mov	eax, eax
	mov	rax, QWORD PTR [rax]
	mov	QWORD PTR msd$11[rsp], rax

; 334  : 				printf ("MSI DATA REREAD -> %d\n", msd);

	mov	rdx, QWORD PTR msd$11[rsp]
	lea	rcx, OFFSET FLAT:$SG3478
	call	printf

; 335  : 
; 336  : 
; 337  : 				mscntrl |= 1;

	mov	eax, DWORD PTR mscntrl$5[rsp]
	or	eax, 1
	mov	DWORD PTR mscntrl$5[rsp], eax

; 338  : 				cap_reg = (cap_reg & UINT16_MAX) | (mscntrl << 16);

	mov	eax, DWORD PTR cap_reg$2[rsp]
	and	eax, 65535				; 0000ffffH
	mov	ecx, DWORD PTR mscntrl$5[rsp]
	shl	ecx, 16
	or	eax, ecx
	mov	DWORD PTR cap_reg$2[rsp], eax

; 339  : 				pci_express_write(device, msi_reg, cap_reg);

	mov	r8d, DWORD PTR cap_reg$2[rsp]
	mov	edx, DWORD PTR msi_reg$1[rsp]
	mov	ecx, DWORD PTR device$[rsp]
	call	pci_express_write

; 340  : 				break;

	jmp	SHORT $LN5@pcie_alloc
$LN4@pcie_alloc:

; 341  : 			}
; 342  : 
; 343  : 			if ((cap_reg & 0xff)  == 0x11) {

	mov	eax, DWORD PTR cap_reg$2[rsp]
	and	eax, 255				; 000000ffH
	cmp	eax, 17
	jne	SHORT $LN1@pcie_alloc

; 344  : 				printf ("MSI-X found for this device\n");

	lea	rcx, OFFSET FLAT:$SG3480
	call	printf

; 345  : 				break;

	jmp	SHORT $LN5@pcie_alloc
$LN1@pcie_alloc:

; 346  : 			}
; 347  : 			capptr = ((cap_reg >> 8) & 0xff);   //((cap_reg >> 8) & 0xFF) / 4;

	mov	eax, DWORD PTR cap_reg$2[rsp]
	shr	eax, 8
	and	eax, 255				; 000000ffH
	mov	DWORD PTR capptr$6[rsp], eax

; 348  : 		}

	jmp	$LN6@pcie_alloc
$LN5@pcie_alloc:
$LN7@pcie_alloc:
$LN9@pcie_alloc:

; 349  : 	}
; 350  : }

	add	rsp, 136				; 00000088H
	ret	0
pcie_alloc_msi ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\pcie.cpp
_TEXT	SEGMENT
size$ = 32
tv71 = 36
address$ = 40
device$ = 64
reg$ = 72
val$ = 80
pci_express_write PROC

; 151  : void pci_express_write (uint32_t device, int reg, uint32_t val) {

$LN35:
	mov	DWORD PTR [rsp+24], r8d
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 56					; 00000038H

; 152  : 	if(acpi_pcie_supported() == false) {

	call	?acpi_pcie_supported@@YA_NXZ		; acpi_pcie_supported
	movzx	eax, al
	test	eax, eax
	jne	SHORT $LN30@pci_expres

; 153  : 		return pci_write(device,reg, val);

	mov	r8d, DWORD PTR val$[rsp]
	mov	edx, DWORD PTR reg$[rsp]
	mov	ecx, DWORD PTR device$[rsp]
	call	pci_write
	jmp	$LN31@pci_expres
$LN30@pci_expres:

; 154  : 	}
; 155  : 
; 156  : 	size_t* address = (size_t*)device;

	mov	eax, DWORD PTR device$[rsp]
	mov	QWORD PTR address$[rsp], rax

; 157  : 	reg = reg;

	mov	eax, DWORD PTR reg$[rsp]
	mov	DWORD PTR reg$[rsp], eax

; 158  : 	int size = 0;

	mov	DWORD PTR size$[rsp], 0

; 159  : 	switch(reg) {

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

; 160  : 	case PCI_VENDOR_ID:
; 161  : 		size = 2;

	mov	DWORD PTR size$[rsp], 2

; 162  : 		break;

	jmp	$LN28@pci_expres
$LN26@pci_expres:

; 163  : 	case PCI_DEVICE_ID:
; 164  : 		size = 2;

	mov	DWORD PTR size$[rsp], 2

; 165  : 		break;

	jmp	$LN28@pci_expres
$LN25@pci_expres:

; 166  : 	case PCI_COMMAND:
; 167  : 		size = 2;

	mov	DWORD PTR size$[rsp], 2

; 168  : 		break;

	jmp	$LN28@pci_expres
$LN24@pci_expres:

; 169  : 	case PCI_STATUS:
; 170  : 		size = 2;

	mov	DWORD PTR size$[rsp], 2

; 171  : 		break;

	jmp	$LN28@pci_expres
$LN23@pci_expres:

; 172  : 	case PCI_REVISION_ID:
; 173  : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 174  : 		break;

	jmp	$LN28@pci_expres
$LN22@pci_expres:

; 175  : 	case PCI_PROG_IF:
; 176  : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 177  : 		break;

	jmp	$LN28@pci_expres
$LN21@pci_expres:

; 178  : 	case PCI_SUBCLASS:
; 179  : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 180  : 		break;

	jmp	$LN28@pci_expres
$LN20@pci_expres:

; 181  : 	case PCI_CLASS:
; 182  : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 183  : 		break;

	jmp	$LN28@pci_expres
$LN19@pci_expres:

; 184  : 	case PCI_CACHE_LINE_SIZE:
; 185  : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 186  : 		break;

	jmp	$LN28@pci_expres
$LN18@pci_expres:

; 187  : 	case PCI_LATENCY_TIMER:
; 188  : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 189  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN17@pci_expres:

; 190  : 	case PCI_HEADER_TYPE:
; 191  : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 192  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN16@pci_expres:

; 193  : 	case PCI_BIST:
; 194  : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 195  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN15@pci_expres:

; 196  : 	case PCI_BAR0:
; 197  : 		size = 4;

	mov	DWORD PTR size$[rsp], 4

; 198  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN14@pci_expres:

; 199  : 	case PCI_BAR1:
; 200  : 		size = 4;

	mov	DWORD PTR size$[rsp], 4

; 201  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN13@pci_expres:

; 202  : 	case PCI_BAR2:
; 203  : 		size = 4;

	mov	DWORD PTR size$[rsp], 4

; 204  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN12@pci_expres:

; 205  : 	case PCI_BAR3:
; 206  : 		size = 4;

	mov	DWORD PTR size$[rsp], 4

; 207  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN11@pci_expres:

; 208  : 	case PCI_BAR4:
; 209  : 		size = 4;

	mov	DWORD PTR size$[rsp], 4

; 210  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN10@pci_expres:

; 211  : 	case PCI_BAR5:
; 212  : 		size = 4;

	mov	DWORD PTR size$[rsp], 4

; 213  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN9@pci_expres:

; 214  : 	case PCI_CAPABILITIES_PTR:
; 215  : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 216  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN8@pci_expres:

; 217  : 	case PCI_INTERRUPT_LINE:
; 218  : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 219  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN7@pci_expres:

; 220  : 	case PCI_INTERRUPT_PIN:
; 221  : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 222  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN6@pci_expres:

; 223  : 	default:
; 224  : 		size = 4;

	mov	DWORD PTR size$[rsp], 4
$LN28@pci_expres:

; 225  : 		break;
; 226  : 	}
; 227  : 
; 228  : 	if (size == 1){

	cmp	DWORD PTR size$[rsp], 1
	jne	SHORT $LN5@pci_expres

; 229  : 		*raw_offset<volatile uint8_t*>(address, reg) = val;

	mov	edx, DWORD PTR reg$[rsp]
	mov	rcx, QWORD PTR address$[rsp]
	call	??$raw_offset@PECEPEA_K@@YAPECEPEA_KH@Z	; raw_offset<unsigned char volatile * __ptr64,unsigned __int64 * __ptr64>
	movzx	ecx, BYTE PTR val$[rsp]
	mov	BYTE PTR [rax], cl
	jmp	SHORT $LN4@pci_expres
$LN5@pci_expres:

; 230  : 	}else if (size == 2) {

	cmp	DWORD PTR size$[rsp], 2
	jne	SHORT $LN3@pci_expres

; 231  : 		*raw_offset<volatile uint16_t*>(address, reg) = val;

	mov	edx, DWORD PTR reg$[rsp]
	mov	rcx, QWORD PTR address$[rsp]
	call	??$raw_offset@PECGPEA_K@@YAPECGPEA_KH@Z	; raw_offset<unsigned short volatile * __ptr64,unsigned __int64 * __ptr64>
	movzx	ecx, WORD PTR val$[rsp]
	mov	WORD PTR [rax], cx
	jmp	SHORT $LN2@pci_expres
$LN3@pci_expres:

; 232  : 	}else if (size == 4) {

	cmp	DWORD PTR size$[rsp], 4
	jne	SHORT $LN1@pci_expres

; 233  : 		*raw_offset<volatile uint32_t*>(address, reg) = val;

	mov	edx, DWORD PTR reg$[rsp]
	mov	rcx, QWORD PTR address$[rsp]
	call	??$raw_offset@PECIPEA_K@@YAPECIPEA_KH@Z	; raw_offset<unsigned int volatile * __ptr64,unsigned __int64 * __ptr64>
	mov	ecx, DWORD PTR val$[rsp]
	mov	DWORD PTR [rax], ecx
$LN1@pci_expres:
$LN2@pci_expres:
$LN4@pci_expres:
$LN31@pci_expres:

; 234  : 	}
; 235  : }

	add	rsp, 56					; 00000038H
	ret	0
	npad	2
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
pci_express_write ENDP
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

; 58   : uint32_t pci_express_read (uint32_t device, int reg) {

$LN35:
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 72					; 00000048H

; 59   : 	if(acpi_pcie_supported() == false) {

	call	?acpi_pcie_supported@@YA_NXZ		; acpi_pcie_supported
	movzx	eax, al
	test	eax, eax
	jne	SHORT $LN30@pci_expres

; 60   : 		return pci_read(device,reg);

	mov	edx, DWORD PTR reg$[rsp]
	mov	ecx, DWORD PTR device$[rsp]
	call	pci_read
	jmp	$LN31@pci_expres
$LN30@pci_expres:

; 61   : 	}
; 62   : 
; 63   : 	size_t* address = (size_t*)device;

	mov	eax, DWORD PTR device$[rsp]
	mov	QWORD PTR address$[rsp], rax

; 64   : 	uint32_t result = 0;

	mov	DWORD PTR result$[rsp], 0

; 65   : 
; 66   : 	int size = 0;

	mov	DWORD PTR size$[rsp], 0

; 67   : 	switch(reg) {

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

; 68   : 	case PCI_VENDOR_ID:
; 69   : 		size = 2;

	mov	DWORD PTR size$[rsp], 2

; 70   : 		break;

	jmp	$LN28@pci_expres
$LN26@pci_expres:

; 71   : 	case PCI_DEVICE_ID:
; 72   : 		size = 2;

	mov	DWORD PTR size$[rsp], 2

; 73   : 		break;

	jmp	$LN28@pci_expres
$LN25@pci_expres:

; 74   : 	case PCI_COMMAND:
; 75   : 		size = 2;

	mov	DWORD PTR size$[rsp], 2

; 76   : 		break;

	jmp	$LN28@pci_expres
$LN24@pci_expres:

; 77   : 	case PCI_STATUS:
; 78   : 		size = 2;

	mov	DWORD PTR size$[rsp], 2

; 79   : 		break;

	jmp	$LN28@pci_expres
$LN23@pci_expres:

; 80   : 	case PCI_REVISION_ID:
; 81   : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 82   : 		break;

	jmp	$LN28@pci_expres
$LN22@pci_expres:

; 83   : 	case PCI_PROG_IF:
; 84   : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 85   : 		break;

	jmp	$LN28@pci_expres
$LN21@pci_expres:

; 86   : 	case PCI_SUBCLASS:
; 87   : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 88   : 		break;

	jmp	$LN28@pci_expres
$LN20@pci_expres:

; 89   : 	case PCI_CLASS:
; 90   : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 91   : 		break;

	jmp	$LN28@pci_expres
$LN19@pci_expres:

; 92   : 	case PCI_CACHE_LINE_SIZE:
; 93   : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 94   : 		break;

	jmp	$LN28@pci_expres
$LN18@pci_expres:

; 95   : 	case PCI_LATENCY_TIMER:
; 96   : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 97   : 		break;

	jmp	SHORT $LN28@pci_expres
$LN17@pci_expres:

; 98   : 	case PCI_HEADER_TYPE:
; 99   : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 100  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN16@pci_expres:

; 101  : 	case PCI_BIST:
; 102  : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 103  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN15@pci_expres:

; 104  : 	case PCI_BAR0:
; 105  : 		size = 4;

	mov	DWORD PTR size$[rsp], 4

; 106  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN14@pci_expres:

; 107  : 	case PCI_BAR1:
; 108  : 		size = 4;

	mov	DWORD PTR size$[rsp], 4

; 109  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN13@pci_expres:

; 110  : 	case PCI_BAR2:
; 111  : 		size = 4;

	mov	DWORD PTR size$[rsp], 4

; 112  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN12@pci_expres:

; 113  : 	case PCI_BAR3:
; 114  : 		size = 4;

	mov	DWORD PTR size$[rsp], 4

; 115  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN11@pci_expres:

; 116  : 	case PCI_BAR4:
; 117  : 		size = 4;

	mov	DWORD PTR size$[rsp], 4

; 118  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN10@pci_expres:

; 119  : 	case PCI_BAR5:
; 120  : 		size = 4;

	mov	DWORD PTR size$[rsp], 4

; 121  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN9@pci_expres:

; 122  : 	case PCI_CAPABILITIES_PTR:
; 123  : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 124  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN8@pci_expres:

; 125  : 	case PCI_INTERRUPT_LINE:
; 126  : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 127  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN7@pci_expres:

; 128  : 	case PCI_INTERRUPT_PIN:
; 129  : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 130  : 		break;

	jmp	SHORT $LN28@pci_expres
$LN6@pci_expres:

; 131  : 	default:
; 132  : 		size = 1;

	mov	DWORD PTR size$[rsp], 1
$LN28@pci_expres:

; 133  : 		break;
; 134  : 	}
; 135  : 
; 136  : 	if (size == 1){

	cmp	DWORD PTR size$[rsp], 1
	jne	SHORT $LN5@pci_expres

; 137  : 		result = *raw_offset<volatile uint8_t*>(address, reg);

	mov	edx, DWORD PTR reg$[rsp]
	mov	rcx, QWORD PTR address$[rsp]
	call	??$raw_offset@PECEPEA_K@@YAPECEPEA_KH@Z	; raw_offset<unsigned char volatile * __ptr64,unsigned __int64 * __ptr64>
	movzx	eax, BYTE PTR [rax]
	movzx	eax, al
	mov	DWORD PTR result$[rsp], eax

; 138  : 		return result;

	mov	eax, DWORD PTR result$[rsp]
	jmp	SHORT $LN31@pci_expres
	jmp	SHORT $LN4@pci_expres
$LN5@pci_expres:

; 139  : 	}else if (size == 2) {

	cmp	DWORD PTR size$[rsp], 2
	jne	SHORT $LN3@pci_expres

; 140  : 		result = *raw_offset<volatile uint16_t*>(address, reg);

	mov	edx, DWORD PTR reg$[rsp]
	mov	rcx, QWORD PTR address$[rsp]
	call	??$raw_offset@PECGPEA_K@@YAPECGPEA_KH@Z	; raw_offset<unsigned short volatile * __ptr64,unsigned __int64 * __ptr64>
	movzx	eax, WORD PTR [rax]
	movzx	eax, ax
	mov	DWORD PTR result$[rsp], eax

; 141  : 		return result;

	mov	eax, DWORD PTR result$[rsp]
	jmp	SHORT $LN31@pci_expres
	jmp	SHORT $LN2@pci_expres
$LN3@pci_expres:

; 142  : 	}else if (size == 4) {

	cmp	DWORD PTR size$[rsp], 4
	jne	SHORT $LN1@pci_expres

; 143  : 		result = *raw_offset<volatile uint32_t*>(address, reg);

	mov	edx, DWORD PTR reg$[rsp]
	mov	rcx, QWORD PTR address$[rsp]
	call	??$raw_offset@PECIPEA_K@@YAPECIPEA_KH@Z	; raw_offset<unsigned int volatile * __ptr64,unsigned __int64 * __ptr64>
	mov	eax, DWORD PTR [rax]
	mov	DWORD PTR result$[rsp], eax

; 144  : 		return result;

	mov	eax, DWORD PTR result$[rsp]
	jmp	SHORT $LN31@pci_expres
$LN1@pci_expres:
$LN2@pci_expres:
$LN4@pci_expres:

; 145  : 	}
; 146  : 
; 147  : 	return 0xFFFFFFFF;

	mov	eax, -1					; ffffffffH
$LN31@pci_expres:

; 148  : }

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
pciSegment$ = 32
address$1 = 36
bus$2 = 40
dev$3 = 44
func$4 = 48
sub_ClassCode$5 = 52
allocs$ = 56
class_code$6 = 64
mcfg$ = 72
classCode$ = 96
subClassCode$ = 104
pci_express_scan_class PROC

; 256  : uint32_t pci_express_scan_class (uint8_t classCode, uint8_t subClassCode) {

$LN19:
	mov	BYTE PTR [rsp+16], dl
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 88					; 00000058H

; 257  : 	if(acpi_pcie_supported() == false) {

	call	?acpi_pcie_supported@@YA_NXZ		; acpi_pcie_supported
	movzx	eax, al
	test	eax, eax
	jne	SHORT $LN16@pci_expres

; 258  : 		return pci_scan_class(classCode, subClassCode);

	movzx	edx, BYTE PTR subClassCode$[rsp]
	movzx	ecx, BYTE PTR classCode$[rsp]
	call	pci_scan_class
	jmp	$LN17@pci_expres
$LN16@pci_expres:

; 259  : 	}
; 260  : 
; 261  : 	acpiMcfg *mcfg = acpi_get_mcfg();

	call	?acpi_get_mcfg@@YAPEAUacpiMcfg@@XZ	; acpi_get_mcfg
	mov	QWORD PTR mcfg$[rsp], rax

; 262  : 	acpiMcfgAlloc *allocs = mem_after<acpiMcfgAlloc*>(mcfg);

	mov	rcx, QWORD PTR mcfg$[rsp]
	call	??$mem_after@PEAUacpiMcfgAlloc@@UacpiMcfg@@@@YAPEAUacpiMcfgAlloc@@PEAUacpiMcfg@@@Z ; mem_after<acpiMcfgAlloc * __ptr64,acpiMcfg>
	mov	QWORD PTR allocs$[rsp], rax

; 263  : 	uint16_t pciSegment = 0;

	xor	eax, eax
	mov	WORD PTR pciSegment$[rsp], ax

; 264  : 	if (allocs->pciSegment <= 65535)

	mov	rax, QWORD PTR allocs$[rsp]
	movzx	eax, WORD PTR [rax+8]
	cmp	eax, 65535				; 0000ffffH
	jg	SHORT $LN15@pci_expres

; 265  : 		pciSegment = allocs->pciSegment;

	mov	rax, QWORD PTR allocs$[rsp]
	movzx	eax, WORD PTR [rax+8]
	mov	WORD PTR pciSegment$[rsp], ax

; 266  : 	else

	jmp	SHORT $LN14@pci_expres
$LN15@pci_expres:

; 267  : 		pciSegment = 0;

	xor	eax, eax
	mov	WORD PTR pciSegment$[rsp], ax
$LN14@pci_expres:

; 268  : 
; 269  : 	for (int bus = 0; bus < allocs->endBusNum; bus++){

	mov	DWORD PTR bus$2[rsp], 0
	jmp	SHORT $LN13@pci_expres
$LN12@pci_expres:
	mov	eax, DWORD PTR bus$2[rsp]
	inc	eax
	mov	DWORD PTR bus$2[rsp], eax
$LN13@pci_expres:
	mov	rax, QWORD PTR allocs$[rsp]
	movzx	eax, BYTE PTR [rax+11]
	cmp	DWORD PTR bus$2[rsp], eax
	jge	$LN11@pci_expres

; 270  : 		for (int dev = 0; dev < PCI_DEVICE_PER_BUS; dev++) {

	mov	DWORD PTR dev$3[rsp], 0
	jmp	SHORT $LN10@pci_expres
$LN9@pci_expres:
	mov	eax, DWORD PTR dev$3[rsp]
	inc	eax
	mov	DWORD PTR dev$3[rsp], eax
$LN10@pci_expres:
	cmp	DWORD PTR dev$3[rsp], 32		; 00000020H
	jge	$LN8@pci_expres

; 271  : 			for (int func = 0; func < PCI_FUNCTION_PER_DEVICE; func++) {

	mov	DWORD PTR func$4[rsp], 0
	jmp	SHORT $LN7@pci_expres
$LN6@pci_expres:
	mov	eax, DWORD PTR func$4[rsp]
	inc	eax
	mov	DWORD PTR func$4[rsp], eax
$LN7@pci_expres:
	cmp	DWORD PTR func$4[rsp], 8
	jge	$LN5@pci_expres

; 272  : 				uint32_t address = pci_express_get_device(pciSegment, bus,dev,func);

	movzx	r9d, WORD PTR func$4[rsp]
	movzx	r8d, WORD PTR dev$3[rsp]
	movzx	edx, WORD PTR bus$2[rsp]
	movzx	ecx, WORD PTR pciSegment$[rsp]
	call	?pci_express_get_device@@YAIGGGG@Z	; pci_express_get_device
	mov	DWORD PTR address$1[rsp], eax

; 273  : 				//debug_print ("Dev Address ->%x \n", address);
; 274  : 				if (address == 0xFFFFFFFF)

	cmp	DWORD PTR address$1[rsp], -1		; ffffffffH
	jne	SHORT $LN4@pci_expres

; 275  : 					continue;

	jmp	SHORT $LN6@pci_expres
$LN4@pci_expres:

; 276  : 				uint32_t class_code = pci_express_read(address,PCI_CLASS);

	mov	edx, 11
	mov	ecx, DWORD PTR address$1[rsp]
	call	pci_express_read
	mov	DWORD PTR class_code$6[rsp], eax

; 277  : 				uint32_t sub_ClassCode = pci_express_read(address, PCI_SUBCLASS);

	mov	edx, 10
	mov	ecx, DWORD PTR address$1[rsp]
	call	pci_express_read
	mov	DWORD PTR sub_ClassCode$5[rsp], eax

; 278  : 				if (classCode == 0xFF || sub_ClassCode == 0xFF)

	movzx	eax, BYTE PTR classCode$[rsp]
	cmp	eax, 255				; 000000ffH
	je	SHORT $LN2@pci_expres
	cmp	DWORD PTR sub_ClassCode$5[rsp], 255	; 000000ffH
	jne	SHORT $LN3@pci_expres
$LN2@pci_expres:

; 279  : 					continue;

	jmp	SHORT $LN6@pci_expres
$LN3@pci_expres:

; 280  : 				if(class_code == classCode && sub_ClassCode == subClassCode) {

	movzx	eax, BYTE PTR classCode$[rsp]
	cmp	DWORD PTR class_code$6[rsp], eax
	jne	SHORT $LN1@pci_expres
	movzx	eax, BYTE PTR subClassCode$[rsp]
	cmp	DWORD PTR sub_ClassCode$5[rsp], eax
	jne	SHORT $LN1@pci_expres

; 281  : 					return address;

	mov	eax, DWORD PTR address$1[rsp]
	jmp	SHORT $LN17@pci_expres
$LN1@pci_expres:

; 282  : 				}
; 283  : 			}

	jmp	$LN6@pci_expres
$LN5@pci_expres:

; 284  : 		}

	jmp	$LN9@pci_expres
$LN8@pci_expres:

; 285  : 	}

	jmp	$LN12@pci_expres
$LN11@pci_expres:

; 286  : 
; 287  : 	return 0xFFFFFFFF;

	mov	eax, -1					; ffffffffH
$LN17@pci_expres:

; 288  : }

	add	rsp, 88					; 00000058H
	ret	0
pci_express_scan_class ENDP
_TEXT	ENDS
END
