; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	pci_read
PUBLIC	pci_scan_class
PUBLIC	pci_scan_device
PUBLIC	pci_write
PUBLIC	pci_enable_bus_master
PUBLIC	pci_enable_interrupts
PUBLIC	?pci_encode_device@@YAIIII@Z			; pci_encode_device
PUBLIC	?pci_decode_bus@@YAHI@Z				; pci_decode_bus
PUBLIC	?pci_decode_slot@@YAHI@Z			; pci_decode_slot
PUBLIC	?pci_decode_func@@YAHI@Z			; pci_decode_func
PUBLIC	?pci_get_address@@YAIIH@Z			; pci_get_address
EXTRN	x64_inportb:PROC
EXTRN	x64_inportw:PROC
EXTRN	x64_inportd:PROC
EXTRN	x64_outportd:PROC
EXTRN	outportw:PROC
EXTRN	outportd:PROC
EXTRN	__ImageBase:BYTE
pdata	SEGMENT
$pdata$pci_read DD imagerel $LN32
	DD	imagerel $LN32+578
	DD	imagerel $unwind$pci_read
$pdata$pci_scan_class DD imagerel $LN14
	DD	imagerel $LN14+234
	DD	imagerel $unwind$pci_scan_class
$pdata$pci_scan_device DD imagerel $LN10
	DD	imagerel $LN10+159
	DD	imagerel $unwind$pci_scan_device
$pdata$pci_write DD imagerel $LN5
	DD	imagerel $LN5+153
	DD	imagerel $unwind$pci_write
$pdata$pci_enable_bus_master DD imagerel $LN3
	DD	imagerel $LN3+61
	DD	imagerel $unwind$pci_enable_bus_master
$pdata$pci_enable_interrupts DD imagerel $LN3
	DD	imagerel $LN3+62
	DD	imagerel $unwind$pci_enable_interrupts
$pdata$?pci_get_address@@YAIIH@Z DD imagerel $LN3
	DD	imagerel $LN3+90
	DD	imagerel $unwind$?pci_get_address@@YAIIH@Z
pdata	ENDS
xdata	SEGMENT
$unwind$pci_read DD 010c01H
	DD	0820cH
$unwind$pci_scan_class DD 010c01H
	DD	0820cH
$unwind$pci_scan_device DD 010c01H
	DD	0820cH
$unwind$pci_write DD 011101H
	DD	06211H
$unwind$pci_enable_bus_master DD 010801H
	DD	06208H
$unwind$pci_enable_interrupts DD 010801H
	DD	06208H
$unwind$?pci_get_address@@YAIIH@Z DD 010c01H
	DD	0620cH
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\pci.cpp
_TEXT	SEGMENT
tv67 = 32
tv71 = 36
device$ = 64
reg$ = 72
?pci_get_address@@YAIIH@Z PROC				; pci_get_address

; 50   : uint32_t pci_get_address(uint32_t device, int reg) {

$LN3:
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 56					; 00000038H

; 51   : 	return 0x80000000 | (pci_decode_bus(device) << 16) | (pci_decode_slot(device) << 11) | (pci_decode_func(device) << 8) | 
; 52   : 		reg & 0x3F;

	mov	ecx, DWORD PTR device$[rsp]
	call	?pci_decode_bus@@YAHI@Z			; pci_decode_bus
	shl	eax, 16
	bts	eax, 31
	mov	DWORD PTR tv67[rsp], eax
	mov	ecx, DWORD PTR device$[rsp]
	call	?pci_decode_slot@@YAHI@Z		; pci_decode_slot
	shl	eax, 11
	mov	ecx, DWORD PTR tv67[rsp]
	or	ecx, eax
	mov	eax, ecx
	mov	DWORD PTR tv71[rsp], eax
	mov	ecx, DWORD PTR device$[rsp]
	call	?pci_decode_func@@YAHI@Z		; pci_decode_func
	shl	eax, 8
	mov	ecx, DWORD PTR tv71[rsp]
	or	ecx, eax
	mov	eax, ecx
	mov	ecx, DWORD PTR reg$[rsp]
	and	ecx, 63					; 0000003fH
	or	eax, ecx

; 53   : }

	add	rsp, 56					; 00000038H
	ret	0
?pci_get_address@@YAIIH@Z ENDP				; pci_get_address
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\pci.cpp
_TEXT	SEGMENT
device$ = 8
?pci_decode_func@@YAHI@Z PROC				; pci_decode_func

; 46   : int pci_decode_func (uint32_t device) {

	mov	DWORD PTR [rsp+8], ecx

; 47   : 	return (uint8_t)(device);

	movzx	eax, BYTE PTR device$[rsp]

; 48   : }

	ret	0
?pci_decode_func@@YAHI@Z ENDP				; pci_decode_func
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\pci.cpp
_TEXT	SEGMENT
device$ = 8
?pci_decode_slot@@YAHI@Z PROC				; pci_decode_slot

; 42   : int pci_decode_slot (uint32_t device) {

	mov	DWORD PTR [rsp+8], ecx

; 43   : 	return (uint8_t)((device >> 8));

	mov	eax, DWORD PTR device$[rsp]
	shr	eax, 8
	movzx	eax, al

; 44   : }

	ret	0
?pci_decode_slot@@YAHI@Z ENDP				; pci_decode_slot
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\pci.cpp
_TEXT	SEGMENT
device$ = 8
?pci_decode_bus@@YAHI@Z PROC				; pci_decode_bus

; 38   : int pci_decode_bus (uint32_t device) {

	mov	DWORD PTR [rsp+8], ecx

; 39   : 	return (uint8_t)((device >> 16));

	mov	eax, DWORD PTR device$[rsp]
	shr	eax, 16
	movzx	eax, al

; 40   : }

	ret	0
?pci_decode_bus@@YAHI@Z ENDP				; pci_decode_bus
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\pci.cpp
_TEXT	SEGMENT
bus$ = 8
slot$ = 16
func$ = 24
?pci_encode_device@@YAIIII@Z PROC			; pci_encode_device

; 56   : uint32_t pci_encode_device(uint32_t bus, uint32_t slot, uint32_t func) {

	mov	DWORD PTR [rsp+24], r8d
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx

; 57   : 	return (uint32_t)((bus << 16)  |(slot << 8) | func);

	mov	eax, DWORD PTR bus$[rsp]
	shl	eax, 16
	mov	ecx, DWORD PTR slot$[rsp]
	shl	ecx, 8
	or	eax, ecx
	or	eax, DWORD PTR func$[rsp]

; 58   : }

	ret	0
?pci_encode_device@@YAIIII@Z ENDP			; pci_encode_device
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\pci.cpp
_TEXT	SEGMENT
command$ = 32
device$ = 64
pci_enable_interrupts PROC

; 191  : void pci_enable_interrupts (uint32_t device) {

$LN3:
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 56					; 00000038H

; 192  : 	uint32_t command = pci_read(device, PCI_COMMAND);

	mov	edx, 4
	mov	ecx, DWORD PTR device$[rsp]
	call	pci_read
	mov	DWORD PTR command$[rsp], eax

; 193  : 	command &= ~(1<<10);

	mov	eax, DWORD PTR command$[rsp]
	btr	eax, 10
	mov	DWORD PTR command$[rsp], eax

; 194  : 	pci_write(device,PCI_COMMAND,command);

	mov	r8d, DWORD PTR command$[rsp]
	mov	edx, 4
	mov	ecx, DWORD PTR device$[rsp]
	call	pci_write

; 195  : }

	add	rsp, 56					; 00000038H
	ret	0
pci_enable_interrupts ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\pci.cpp
_TEXT	SEGMENT
command$ = 32
device$ = 64
pci_enable_bus_master PROC

; 185  : void pci_enable_bus_master (uint32_t device) {

$LN3:
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 56					; 00000038H

; 186  : 	uint32_t command = pci_read(device, PCI_COMMAND);

	mov	edx, 4
	mov	ecx, DWORD PTR device$[rsp]
	call	pci_read
	mov	DWORD PTR command$[rsp], eax

; 187  : 	command |= (1<<2);

	mov	eax, DWORD PTR command$[rsp]
	or	eax, 4
	mov	DWORD PTR command$[rsp], eax

; 188  : 	pci_write(device, PCI_COMMAND,command);

	mov	r8d, DWORD PTR command$[rsp]
	mov	edx, 4
	mov	ecx, DWORD PTR device$[rsp]
	call	pci_write

; 189  : }

	add	rsp, 56					; 00000038H
	ret	0
pci_enable_bus_master ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\pci.cpp
_TEXT	SEGMENT
data$1 = 32
addr$2 = 36
device$ = 64
reg$ = 72
value$ = 80
pci_write PROC

; 141  : void pci_write (uint32_t device, int reg, uint32_t value) {

$LN5:
	mov	DWORD PTR [rsp+24], r8d
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 56					; 00000038H

; 142  : 	if (reg == PCI_COMMAND) {

	cmp	DWORD PTR reg$[rsp], 4
	jne	SHORT $LN2@pci_write

; 143  : 		reg = 2;

	mov	DWORD PTR reg$[rsp], 2

; 144  : 		unsigned short data = (unsigned short)value;

	movzx	eax, WORD PTR value$[rsp]
	mov	WORD PTR data$1[rsp], ax

; 145  : 		unsigned addr = pci_get_address(device, reg/2);

	mov	eax, DWORD PTR reg$[rsp]
	cdq
	sub	eax, edx
	sar	eax, 1
	mov	edx, eax
	mov	ecx, DWORD PTR device$[rsp]
	call	?pci_get_address@@YAIIH@Z		; pci_get_address
	mov	DWORD PTR addr$2[rsp], eax

; 146  : 		outportd(PCI_ADDRESS_PORT, addr);

	mov	edx, DWORD PTR addr$2[rsp]
	mov	cx, 3320				; 00000cf8H
	call	outportd

; 147  : 		outportw((PCI_VALUE_PORT + (reg % 2)),data);

	mov	eax, DWORD PTR reg$[rsp]
	cdq
	and	eax, 1
	xor	eax, edx
	sub	eax, edx
	add	eax, 3324				; 00000cfcH
	movzx	edx, WORD PTR data$1[rsp]
	movzx	ecx, ax
	call	outportw

; 148  : 	}else {

	jmp	SHORT $LN1@pci_write
$LN2@pci_write:

; 149  : 		x64_outportd(PCI_ADDRESS_PORT, pci_get_address(device,reg));

	mov	edx, DWORD PTR reg$[rsp]
	mov	ecx, DWORD PTR device$[rsp]
	call	?pci_get_address@@YAIIH@Z		; pci_get_address
	mov	edx, eax
	mov	cx, 3320				; 00000cf8H
	call	x64_outportd

; 150  : 		x64_outportd(PCI_VALUE_PORT, value);

	mov	edx, DWORD PTR value$[rsp]
	mov	cx, 3324				; 00000cfcH
	call	x64_outportd
$LN1@pci_write:

; 151  : 	}
; 152  : }

	add	rsp, 56					; 00000038H
	ret	0
pci_write ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\pci.cpp
_TEXT	SEGMENT
func$1 = 32
dev$2 = 36
addr$3 = 40
v$4 = 44
d$5 = 48
vendid$ = 80
devid$ = 88
pci_scan_device PROC

; 171  : uint32_t pci_scan_device(uint32_t vendid, uint32_t devid) {

$LN10:
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 72					; 00000048H

; 172  : 	for (int dev = 0; dev < PCI_DEVICE_PER_BUS; dev++) {

	mov	DWORD PTR dev$2[rsp], 0
	jmp	SHORT $LN7@pci_scan_d
$LN6@pci_scan_d:
	mov	eax, DWORD PTR dev$2[rsp]
	inc	eax
	mov	DWORD PTR dev$2[rsp], eax
$LN7@pci_scan_d:
	cmp	DWORD PTR dev$2[rsp], 32		; 00000020H
	jge	SHORT $LN5@pci_scan_d

; 173  : 		for (int func = 0; func < PCI_FUNCTION_PER_DEVICE; func++) {

	mov	DWORD PTR func$1[rsp], 0
	jmp	SHORT $LN4@pci_scan_d
$LN3@pci_scan_d:
	mov	eax, DWORD PTR func$1[rsp]
	inc	eax
	mov	DWORD PTR func$1[rsp], eax
$LN4@pci_scan_d:
	cmp	DWORD PTR func$1[rsp], 8
	jge	SHORT $LN2@pci_scan_d

; 174  : 			uint32_t addr = pci_encode_device(0,dev,func);

	mov	r8d, DWORD PTR func$1[rsp]
	mov	edx, DWORD PTR dev$2[rsp]
	xor	ecx, ecx
	call	?pci_encode_device@@YAIIII@Z		; pci_encode_device
	mov	DWORD PTR addr$3[rsp], eax

; 175  : 			uint32_t v = pci_read(addr,PCI_VENDOR_ID);

	xor	edx, edx
	mov	ecx, DWORD PTR addr$3[rsp]
	call	pci_read
	mov	DWORD PTR v$4[rsp], eax

; 176  : 			uint32_t d = pci_read(addr,PCI_DEVICE_ID);

	mov	edx, 2
	mov	ecx, DWORD PTR addr$3[rsp]
	call	pci_read
	mov	DWORD PTR d$5[rsp], eax

; 177  : 			if (v == vendid && d == devid) 

	mov	eax, DWORD PTR vendid$[rsp]
	cmp	DWORD PTR v$4[rsp], eax
	jne	SHORT $LN1@pci_scan_d
	mov	eax, DWORD PTR devid$[rsp]
	cmp	DWORD PTR d$5[rsp], eax
	jne	SHORT $LN1@pci_scan_d

; 178  : 				return addr;

	mov	eax, DWORD PTR addr$3[rsp]
	jmp	SHORT $LN8@pci_scan_d
$LN1@pci_scan_d:

; 179  : 		}

	jmp	SHORT $LN3@pci_scan_d
$LN2@pci_scan_d:

; 180  : 	}

	jmp	SHORT $LN6@pci_scan_d
$LN5@pci_scan_d:

; 181  : 
; 182  : 	return 0xFFFFFFFF;

	mov	eax, -1					; ffffffffH
$LN8@pci_scan_d:

; 183  : }

	add	rsp, 72					; 00000048H
	ret	0
pci_scan_device ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\pci.cpp
_TEXT	SEGMENT
func$1 = 32
dev$2 = 36
bus$3 = 40
addr$4 = 44
cc$5 = 48
sc$6 = 52
classcode$ = 80
subclass$ = 88
pci_scan_class PROC

; 154  : uint32_t pci_scan_class(uint8_t classcode, uint8_t subclass) {

$LN14:
	mov	BYTE PTR [rsp+16], dl
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 72					; 00000048H

; 155  : 	for (int bus = 0; bus < PCI_MAX_BUS; bus++) {

	mov	DWORD PTR bus$3[rsp], 0
	jmp	SHORT $LN11@pci_scan_c
$LN10@pci_scan_c:
	mov	eax, DWORD PTR bus$3[rsp]
	inc	eax
	mov	DWORD PTR bus$3[rsp], eax
$LN11@pci_scan_c:
	cmp	DWORD PTR bus$3[rsp], 256		; 00000100H
	jge	$LN9@pci_scan_c

; 156  : 		for (int dev = 0; dev < PCI_DEVICE_PER_BUS; dev++) {

	mov	DWORD PTR dev$2[rsp], 0
	jmp	SHORT $LN8@pci_scan_c
$LN7@pci_scan_c:
	mov	eax, DWORD PTR dev$2[rsp]
	inc	eax
	mov	DWORD PTR dev$2[rsp], eax
$LN8@pci_scan_c:
	cmp	DWORD PTR dev$2[rsp], 32		; 00000020H
	jge	$LN6@pci_scan_c

; 157  : 			for (int func = 0; func < PCI_FUNCTION_PER_DEVICE; func++) {

	mov	DWORD PTR func$1[rsp], 0
	jmp	SHORT $LN5@pci_scan_c
$LN4@pci_scan_c:
	mov	eax, DWORD PTR func$1[rsp]
	inc	eax
	mov	DWORD PTR func$1[rsp], eax
$LN5@pci_scan_c:
	cmp	DWORD PTR func$1[rsp], 8
	jge	SHORT $LN3@pci_scan_c

; 158  : 				uint32_t addr = pci_encode_device(bus,dev,func);

	mov	r8d, DWORD PTR func$1[rsp]
	mov	edx, DWORD PTR dev$2[rsp]
	mov	ecx, DWORD PTR bus$3[rsp]
	call	?pci_encode_device@@YAIIII@Z		; pci_encode_device
	mov	DWORD PTR addr$4[rsp], eax

; 159  : 				uint32_t cc = pci_read(addr,PCI_CLASS);

	mov	edx, 11
	mov	ecx, DWORD PTR addr$4[rsp]
	call	pci_read
	mov	DWORD PTR cc$5[rsp], eax

; 160  : 				uint32_t sc = pci_read(addr,PCI_SUBCLASS);

	mov	edx, 10
	mov	ecx, DWORD PTR addr$4[rsp]
	call	pci_read
	mov	DWORD PTR sc$6[rsp], eax

; 161  : 				if (cc == 0xFF && sc == 0xFF)

	cmp	DWORD PTR cc$5[rsp], 255		; 000000ffH
	jne	SHORT $LN2@pci_scan_c
	cmp	DWORD PTR sc$6[rsp], 255		; 000000ffH
	jne	SHORT $LN2@pci_scan_c

; 162  : 					continue;

	jmp	SHORT $LN4@pci_scan_c
$LN2@pci_scan_c:

; 163  : 				if (cc == classcode && sc == subclass) 

	movzx	eax, BYTE PTR classcode$[rsp]
	cmp	DWORD PTR cc$5[rsp], eax
	jne	SHORT $LN1@pci_scan_c
	movzx	eax, BYTE PTR subclass$[rsp]
	cmp	DWORD PTR sc$6[rsp], eax
	jne	SHORT $LN1@pci_scan_c

; 164  : 					return addr;

	mov	eax, DWORD PTR addr$4[rsp]
	jmp	SHORT $LN12@pci_scan_c
$LN1@pci_scan_c:

; 165  : 			}

	jmp	SHORT $LN4@pci_scan_c
$LN3@pci_scan_c:

; 166  : 		}

	jmp	$LN7@pci_scan_c
$LN6@pci_scan_c:

; 167  : 	}

	jmp	$LN10@pci_scan_c
$LN9@pci_scan_c:

; 168  : 	return 0xFFFFFFFF;

	mov	eax, -1					; ffffffffH
$LN12@pci_scan_c:

; 169  : }

	add	rsp, 72					; 00000048H
	ret	0
pci_scan_class ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\drivers\pci.cpp
_TEXT	SEGMENT
t$1 = 32
t$2 = 36
size$ = 40
tv64 = 44
t$3 = 48
device$ = 80
reg$ = 88
pci_read PROC

; 60   : uint32_t pci_read (uint32_t device, int reg) {

$LN32:
	mov	DWORD PTR [rsp+16], edx
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 72					; 00000048H

; 61   : 	int size = 0;

	mov	DWORD PTR size$[rsp], 0

; 62   : 	switch(reg) {

	mov	eax, DWORD PTR reg$[rsp]
	mov	DWORD PTR tv64[rsp], eax
	cmp	DWORD PTR tv64[rsp], 61			; 0000003dH
	ja	$LN26@pci_read
	movsxd	rax, DWORD PTR tv64[rsp]
	lea	rcx, OFFSET FLAT:__ImageBase
	movzx	eax, BYTE PTR $LN30@pci_read[rcx+rax]
	mov	eax, DWORD PTR $LN31@pci_read[rcx+rax*4]
	add	rax, rcx
	jmp	rax
$LN25@pci_read:

; 63   : 	case PCI_VENDOR_ID:
; 64   : 		size = 2;

	mov	DWORD PTR size$[rsp], 2

; 65   : 		break;

	jmp	$LN26@pci_read
$LN24@pci_read:

; 66   : 	case PCI_DEVICE_ID:
; 67   : 		size = 2;

	mov	DWORD PTR size$[rsp], 2

; 68   : 		break;

	jmp	$LN26@pci_read
$LN23@pci_read:

; 69   : 	case PCI_COMMAND:
; 70   : 		size = 4;

	mov	DWORD PTR size$[rsp], 4

; 71   : 		break;

	jmp	$LN26@pci_read
$LN22@pci_read:

; 72   : 	case PCI_STATUS:
; 73   : 		size = 2;

	mov	DWORD PTR size$[rsp], 2

; 74   : 		break;

	jmp	$LN26@pci_read
$LN21@pci_read:

; 75   : 	case PCI_REVISION_ID:
; 76   : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 77   : 		break;

	jmp	$LN26@pci_read
$LN20@pci_read:

; 78   : 	case PCI_PROG_IF:
; 79   : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 80   : 		break;

	jmp	$LN26@pci_read
$LN19@pci_read:

; 81   : 	case PCI_SUBCLASS:
; 82   : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 83   : 		break;

	jmp	$LN26@pci_read
$LN18@pci_read:

; 84   : 	case PCI_CLASS:
; 85   : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 86   : 		break;

	jmp	SHORT $LN26@pci_read
$LN17@pci_read:

; 87   : 	case PCI_CACHE_LINE_SIZE:
; 88   : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 89   : 		break;

	jmp	SHORT $LN26@pci_read
$LN16@pci_read:

; 90   : 	case PCI_LATENCY_TIMER:
; 91   : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 92   : 		break;

	jmp	SHORT $LN26@pci_read
$LN15@pci_read:

; 93   : 	case PCI_HEADER_TYPE:
; 94   : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 95   : 		break;

	jmp	SHORT $LN26@pci_read
$LN14@pci_read:

; 96   : 	case PCI_BIST:
; 97   : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 98   : 		break;

	jmp	SHORT $LN26@pci_read
$LN13@pci_read:

; 99   : 	case PCI_BAR0:
; 100  : 		size = 4;

	mov	DWORD PTR size$[rsp], 4

; 101  : 		break;

	jmp	SHORT $LN26@pci_read
$LN12@pci_read:

; 102  : 	case PCI_BAR1:
; 103  : 		size = 4;

	mov	DWORD PTR size$[rsp], 4

; 104  : 		break;

	jmp	SHORT $LN26@pci_read
$LN11@pci_read:

; 105  : 	case PCI_BAR2:
; 106  : 		size = 4;

	mov	DWORD PTR size$[rsp], 4

; 107  : 		break;

	jmp	SHORT $LN26@pci_read
$LN10@pci_read:

; 108  : 	case PCI_BAR3:
; 109  : 		size = 4;

	mov	DWORD PTR size$[rsp], 4

; 110  : 		break;

	jmp	SHORT $LN26@pci_read
$LN9@pci_read:

; 111  : 	case PCI_BAR4:
; 112  : 		size = 4;

	mov	DWORD PTR size$[rsp], 4

; 113  : 		break;

	jmp	SHORT $LN26@pci_read
$LN8@pci_read:

; 114  : 	case PCI_BAR5:
; 115  : 		size = 4;

	mov	DWORD PTR size$[rsp], 4

; 116  : 		break;

	jmp	SHORT $LN26@pci_read
$LN7@pci_read:

; 117  : 	case PCI_INTERRUPT_LINE:
; 118  : 		size = 1;

	mov	DWORD PTR size$[rsp], 1

; 119  : 		break;

	jmp	SHORT $LN26@pci_read
$LN6@pci_read:

; 120  : 	case PCI_INTERRUPT_PIN:
; 121  : 		size = 1;

	mov	DWORD PTR size$[rsp], 1
$LN26@pci_read:

; 122  : 		break;
; 123  : 	}
; 124  : 
; 125  : 	x64_outportd(PCI_ADDRESS_PORT, pci_get_address(device, reg));

	mov	edx, DWORD PTR reg$[rsp]
	mov	ecx, DWORD PTR device$[rsp]
	call	?pci_get_address@@YAIIH@Z		; pci_get_address
	mov	edx, eax
	mov	cx, 3320				; 00000cf8H
	call	x64_outportd

; 126  : 
; 127  : 	if (size == 4) {

	cmp	DWORD PTR size$[rsp], 4
	jne	SHORT $LN5@pci_read

; 128  : 		uint32_t t = x64_inportd(PCI_VALUE_PORT);

	mov	cx, 3324				; 00000cfcH
	call	x64_inportd
	mov	DWORD PTR t$3[rsp], eax

; 129  : 		return t;

	mov	eax, DWORD PTR t$3[rsp]
	jmp	SHORT $LN28@pci_read
	jmp	SHORT $LN4@pci_read
$LN5@pci_read:

; 130  : 	}else if (size == 2) {

	cmp	DWORD PTR size$[rsp], 2
	jne	SHORT $LN3@pci_read

; 131  : 		uint16_t t =  x64_inportw(PCI_VALUE_PORT + (reg & 2)); //+ (reg & 2));

	mov	eax, DWORD PTR reg$[rsp]
	and	eax, 2
	add	eax, 3324				; 00000cfcH
	movzx	ecx, ax
	call	x64_inportw
	mov	WORD PTR t$2[rsp], ax

; 132  : 		return t;

	movzx	eax, WORD PTR t$2[rsp]
	jmp	SHORT $LN28@pci_read
	jmp	SHORT $LN2@pci_read
$LN3@pci_read:

; 133  : 	}else if (size == 1) {

	cmp	DWORD PTR size$[rsp], 1
	jne	SHORT $LN1@pci_read

; 134  : 		uint8_t t = x64_inportb (PCI_VALUE_PORT + (reg & 3));

	mov	eax, DWORD PTR reg$[rsp]
	and	eax, 3
	add	eax, 3324				; 00000cfcH
	movzx	ecx, ax
	call	x64_inportb
	mov	BYTE PTR t$1[rsp], al

; 135  : 		return t;

	movzx	eax, BYTE PTR t$1[rsp]
	jmp	SHORT $LN28@pci_read
$LN1@pci_read:
$LN2@pci_read:
$LN4@pci_read:

; 136  : 	}
; 137  : 
; 138  : 	return 0xFFFF;

	mov	eax, 65535				; 0000ffffH
$LN28@pci_read:

; 139  : }

	add	rsp, 72					; 00000048H
	ret	0
	npad	1
$LN31@pci_read:
	DD	$LN25@pci_read
	DD	$LN24@pci_read
	DD	$LN23@pci_read
	DD	$LN22@pci_read
	DD	$LN21@pci_read
	DD	$LN20@pci_read
	DD	$LN19@pci_read
	DD	$LN18@pci_read
	DD	$LN17@pci_read
	DD	$LN16@pci_read
	DD	$LN15@pci_read
	DD	$LN14@pci_read
	DD	$LN13@pci_read
	DD	$LN12@pci_read
	DD	$LN11@pci_read
	DD	$LN10@pci_read
	DD	$LN9@pci_read
	DD	$LN8@pci_read
	DD	$LN7@pci_read
	DD	$LN6@pci_read
	DD	$LN26@pci_read
$LN30@pci_read:
	DB	0
	DB	20
	DB	1
	DB	20
	DB	2
	DB	20
	DB	3
	DB	20
	DB	4
	DB	5
	DB	6
	DB	7
	DB	8
	DB	9
	DB	10
	DB	11
	DB	12
	DB	20
	DB	20
	DB	20
	DB	13
	DB	20
	DB	20
	DB	20
	DB	14
	DB	20
	DB	20
	DB	20
	DB	15
	DB	20
	DB	20
	DB	20
	DB	16
	DB	20
	DB	20
	DB	20
	DB	17
	DB	20
	DB	20
	DB	20
	DB	20
	DB	20
	DB	20
	DB	20
	DB	20
	DB	20
	DB	20
	DB	20
	DB	20
	DB	20
	DB	20
	DB	20
	DB	20
	DB	20
	DB	20
	DB	20
	DB	20
	DB	20
	DB	20
	DB	20
	DB	18
	DB	19
pci_read ENDP
_TEXT	ENDS
END
