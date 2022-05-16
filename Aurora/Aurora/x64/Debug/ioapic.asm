; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?io_apic_base@@3PEAXEA				; io_apic_base
_BSS	SEGMENT
?io_apic_base@@3PEAXEA DQ 01H DUP (?)			; io_apic_base
_BSS	ENDS
PUBLIC	?ioapic_init@@YAXPEAX@Z				; ioapic_init
PUBLIC	?ioapic_register_irq@@YAX_KP6AX0PEAX@ZE_N@Z	; ioapic_register_irq
PUBLIC	?ioapic_mask_irq@@YAXE_N@Z			; ioapic_mask_irq
PUBLIC	?ioapic_redirect@@YAXEIGE@Z			; ioapic_redirect
PUBLIC	??$raw_offset@PECIPEAX@@YAPECIPEAXH@Z		; raw_offset<unsigned int volatile * __ptr64,void * __ptr64>
EXTRN	setvect:PROC
EXTRN	?read_apic_register@@YA_KG@Z:PROC		; read_apic_register
EXTRN	AuMapMMIO:PROC
pdata	SEGMENT
$pdata$?ioapic_init@@YAXPEAX@Z DD imagerel $LN3
	DD	imagerel $LN3+80
	DD	imagerel $unwind$?ioapic_init@@YAXPEAX@Z
$pdata$?ioapic_register_irq@@YAX_KP6AX0PEAX@ZE_N@Z DD imagerel $LN5
	DD	imagerel $LN5+234
	DD	imagerel $unwind$?ioapic_register_irq@@YAX_KP6AX0PEAX@ZE_N@Z
$pdata$?ioapic_mask_irq@@YAXE_N@Z DD imagerel $LN5
	DD	imagerel $LN5+143
	DD	imagerel $unwind$?ioapic_mask_irq@@YAXE_N@Z
$pdata$?ioapic_redirect@@YAXEIGE@Z DD imagerel $LN5
	DD	imagerel $LN5+206
	DD	imagerel $unwind$?ioapic_redirect@@YAXEIGE@Z
$pdata$?read_ioapic_register@@YAIPEAXE@Z DD imagerel ?read_ioapic_register@@YAIPEAXE@Z
	DD	imagerel ?read_ioapic_register@@YAIPEAXE@Z+71
	DD	imagerel $unwind$?read_ioapic_register@@YAIPEAXE@Z
$pdata$?write_ioapic_register@@YAXPEAXEI@Z DD imagerel ?write_ioapic_register@@YAXPEAXEI@Z
	DD	imagerel ?write_ioapic_register@@YAXPEAXEI@Z+80
	DD	imagerel $unwind$?write_ioapic_register@@YAXPEAXEI@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?ioapic_init@@YAXPEAX@Z DD 010901H
	DD	06209H
$unwind$?ioapic_register_irq@@YAX_KP6AX0PEAX@ZE_N@Z DD 011801H
	DD	06218H
$unwind$?ioapic_mask_irq@@YAXE_N@Z DD 010c01H
	DD	0620cH
$unwind$?ioapic_redirect@@YAXEIGE@Z DD 011701H
	DD	08217H
$unwind$?read_ioapic_register@@YAIPEAXE@Z DD 010d01H
	DD	0620dH
$unwind$?write_ioapic_register@@YAXPEAXEI@Z DD 011201H
	DD	06212H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\ioapic.cpp
_TEXT	SEGMENT
ioregsel$ = 32
ioregwin$ = 40
apic_base$ = 64
offset$ = 72
val$ = 80
?write_ioapic_register@@YAXPEAXEI@Z PROC		; write_ioapic_register

; 30   : {

	mov	DWORD PTR [rsp+24], r8d
	mov	BYTE PTR [rsp+16], dl
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 31   : 	volatile uint32_t* ioregsel = reinterpret_cast<volatile uint32_t*>(io_apic_base);

	mov	rax, QWORD PTR ?io_apic_base@@3PEAXEA	; io_apic_base
	mov	QWORD PTR ioregsel$[rsp], rax

; 32   : 	volatile uint32_t* ioregwin = raw_offset<volatile uint32_t*>(io_apic_base, 0x10);

	mov	edx, 16
	mov	rcx, QWORD PTR ?io_apic_base@@3PEAXEA	; io_apic_base
	call	??$raw_offset@PECIPEAX@@YAPECIPEAXH@Z	; raw_offset<unsigned int volatile * __ptr64,void * __ptr64>
	mov	QWORD PTR ioregwin$[rsp], rax

; 33   : 	*ioregsel = offset;

	movzx	eax, BYTE PTR offset$[rsp]
	mov	rcx, QWORD PTR ioregsel$[rsp]
	mov	DWORD PTR [rcx], eax

; 34   : 	*ioregwin = val;

	mov	rax, QWORD PTR ioregwin$[rsp]
	mov	ecx, DWORD PTR val$[rsp]
	mov	DWORD PTR [rax], ecx

; 35   : }

	add	rsp, 56					; 00000038H
	ret	0
?write_ioapic_register@@YAXPEAXEI@Z ENDP		; write_ioapic_register
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\include\stdint.h
;	COMDAT ??$raw_offset@PECIPEAX@@YAPECIPEAXH@Z
_TEXT	SEGMENT
p1$ = 8
offset$ = 16
??$raw_offset@PECIPEAX@@YAPECIPEAXH@Z PROC		; raw_offset<unsigned int volatile * __ptr64,void * __ptr64>, COMDAT

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
??$raw_offset@PECIPEAX@@YAPECIPEAXH@Z ENDP		; raw_offset<unsigned int volatile * __ptr64,void * __ptr64>
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\ioapic.cpp
_TEXT	SEGMENT
ioregsel$ = 32
ioregwin$ = 40
apic_base$ = 64
offset$ = 72
?read_ioapic_register@@YAIPEAXE@Z PROC			; read_ioapic_register

; 21   : {

	mov	BYTE PTR [rsp+16], dl
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 22   : 	volatile uint32_t* ioregsel = reinterpret_cast<volatile uint32_t*>(io_apic_base);

	mov	rax, QWORD PTR ?io_apic_base@@3PEAXEA	; io_apic_base
	mov	QWORD PTR ioregsel$[rsp], rax

; 23   : 	volatile uint32_t* ioregwin = raw_offset<volatile uint32_t*>(io_apic_base, 0x10);

	mov	edx, 16
	mov	rcx, QWORD PTR ?io_apic_base@@3PEAXEA	; io_apic_base
	call	??$raw_offset@PECIPEAX@@YAPECIPEAXH@Z	; raw_offset<unsigned int volatile * __ptr64,void * __ptr64>
	mov	QWORD PTR ioregwin$[rsp], rax

; 24   : 	*ioregsel = offset;

	movzx	eax, BYTE PTR offset$[rsp]
	mov	rcx, QWORD PTR ioregsel$[rsp]
	mov	DWORD PTR [rcx], eax

; 25   : 	return *ioregwin;

	mov	rax, QWORD PTR ioregwin$[rsp]
	mov	eax, DWORD PTR [rax]

; 26   : }

	add	rsp, 56					; 00000038H
	ret	0
?read_ioapic_register@@YAIPEAXE@Z ENDP			; read_ioapic_register
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\ioapic.cpp
_TEXT	SEGMENT
ioredtbl$ = 32
ioapic_base$ = 36
redirection$ = 40
tv90 = 48
irq$ = 80
gsi$ = 88
flags$ = 96
apic$ = 104
?ioapic_redirect@@YAXEIGE@Z PROC			; ioapic_redirect

; 69   : void ioapic_redirect (uint8_t irq, uint32_t gsi, uint16_t flags, uint8_t apic) {

$LN5:
	mov	BYTE PTR [rsp+32], r9b
	mov	WORD PTR [rsp+24], r8w
	mov	DWORD PTR [rsp+16], edx
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 72					; 00000048H

; 70   : 	uint32_t ioapic_base = 0xfec00000;

	mov	DWORD PTR ioapic_base$[rsp], -20971520	; fec00000H

; 71   : 	uint64_t redirection = irq + 32;

	movzx	eax, BYTE PTR irq$[rsp]
	add	eax, 32					; 00000020H
	cdqe
	mov	QWORD PTR redirection$[rsp], rax

; 72   : 	if (flags & 2) {

	movzx	eax, WORD PTR flags$[rsp]
	and	eax, 2
	test	eax, eax
	je	SHORT $LN2@ioapic_red

; 73   : 		redirection |= 1 << 13;

	mov	rax, QWORD PTR redirection$[rsp]
	bts	rax, 13
	mov	QWORD PTR redirection$[rsp], rax
$LN2@ioapic_red:

; 74   : 	}
; 75   : 
; 76   : 
; 77   : 	if (flags & 8) {

	movzx	eax, WORD PTR flags$[rsp]
	and	eax, 8
	test	eax, eax
	je	SHORT $LN1@ioapic_red

; 78   : 		redirection |= 1 << 15;

	mov	rax, QWORD PTR redirection$[rsp]
	bts	rax, 15
	mov	QWORD PTR redirection$[rsp], rax
$LN1@ioapic_red:

; 79   : 	}
; 80   : 
; 81   : 	redirection |= ((uint64_t)apic) << 56;

	movzx	eax, BYTE PTR apic$[rsp]
	shl	rax, 56					; 00000038H
	mov	rcx, QWORD PTR redirection$[rsp]
	or	rcx, rax
	mov	rax, rcx
	mov	QWORD PTR redirection$[rsp], rax

; 82   : 	
; 83   : 	uint32_t ioredtbl = (gsi - 0) * 2 + 16;

	mov	eax, DWORD PTR gsi$[rsp]
	lea	eax, DWORD PTR [rax+rax+16]
	mov	DWORD PTR ioredtbl$[rsp], eax

; 84   : 
; 85   : 	write_ioapic_register ((void*)ioapic_base,ioredtbl + 0, (uint32_t)(redirection));

	mov	eax, DWORD PTR ioapic_base$[rsp]
	mov	r8d, DWORD PTR redirection$[rsp]
	movzx	edx, BYTE PTR ioredtbl$[rsp]
	mov	ecx, eax
	call	?write_ioapic_register@@YAXPEAXEI@Z	; write_ioapic_register

; 86   : 	write_ioapic_register ((void*)ioapic_base,ioredtbl + 1, (uint32_t)(redirection >> 32));

	mov	rax, QWORD PTR redirection$[rsp]
	shr	rax, 32					; 00000020H
	mov	ecx, DWORD PTR ioredtbl$[rsp]
	inc	ecx
	mov	edx, DWORD PTR ioapic_base$[rsp]
	mov	QWORD PTR tv90[rsp], rdx
	mov	r8d, eax
	movzx	edx, cl
	mov	rax, QWORD PTR tv90[rsp]
	mov	rcx, rax
	call	?write_ioapic_register@@YAXPEAXEI@Z	; write_ioapic_register

; 87   : }

	add	rsp, 72					; 00000048H
	ret	0
?ioapic_redirect@@YAXEIGE@Z ENDP			; ioapic_redirect
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\ioapic.cpp
_TEXT	SEGMENT
low$ = 32
reg$ = 36
irq$ = 64
value$ = 72
?ioapic_mask_irq@@YAXE_N@Z PROC				; ioapic_mask_irq

; 89   : void ioapic_mask_irq (uint8_t irq, bool value){

$LN5:
	mov	BYTE PTR [rsp+16], dl
	mov	BYTE PTR [rsp+8], cl
	sub	rsp, 56					; 00000038H

; 90   : 	uint32_t reg = IOAPIC_REG_RED_TBL_BASE + irq* 2;

	movzx	eax, BYTE PTR irq$[rsp]
	lea	eax, DWORD PTR [rax+rax+16]
	mov	DWORD PTR reg$[rsp], eax

; 91   : 	write_ioapic_register((void*)io_apic_base, reg + 1, read_apic_register(0x02) << 24);

	mov	cx, 2
	call	?read_apic_register@@YA_KG@Z		; read_apic_register
	shl	rax, 24
	mov	ecx, DWORD PTR reg$[rsp]
	inc	ecx
	mov	r8d, eax
	movzx	edx, cl
	mov	rcx, QWORD PTR ?io_apic_base@@3PEAXEA	; io_apic_base
	call	?write_ioapic_register@@YAXPEAXEI@Z	; write_ioapic_register

; 92   : 	uint32_t low = read_ioapic_register ((void*)0xfec00000,reg);

	movzx	edx, BYTE PTR reg$[rsp]
	mov	ecx, -20971520				; fffffffffec00000H
	call	?read_ioapic_register@@YAIPEAXE@Z	; read_ioapic_register
	mov	DWORD PTR low$[rsp], eax

; 93   : 	//!unmask the irq
; 94   : 	if (value)

	movzx	eax, BYTE PTR value$[rsp]
	test	eax, eax
	je	SHORT $LN2@ioapic_mas

; 95   : 		low |= (1<<16);  //mask

	mov	eax, DWORD PTR low$[rsp]
	bts	eax, 16
	mov	DWORD PTR low$[rsp], eax

; 96   : 	else

	jmp	SHORT $LN1@ioapic_mas
$LN2@ioapic_mas:

; 97   : 		low &= ~(1<<16); //unmask

	mov	eax, DWORD PTR low$[rsp]
	btr	eax, 16
	mov	DWORD PTR low$[rsp], eax
$LN1@ioapic_mas:

; 98   : 
; 99   : 	write_ioapic_register((void*)io_apic_base, reg, low);   //vector + 32

	mov	r8d, DWORD PTR low$[rsp]
	movzx	edx, BYTE PTR reg$[rsp]
	mov	rcx, QWORD PTR ?io_apic_base@@3PEAXEA	; io_apic_base
	call	?write_ioapic_register@@YAXPEAXEI@Z	; write_ioapic_register

; 100  : }

	add	rsp, 56					; 00000038H
	ret	0
?ioapic_mask_irq@@YAXE_N@Z ENDP				; ioapic_mask_irq
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\ioapic.cpp
_TEXT	SEGMENT
low$ = 32
reg$ = 36
vector$ = 64
fn$ = 72
irq$ = 80
level$ = 88
?ioapic_register_irq@@YAX_KP6AX0PEAX@ZE_N@Z PROC	; ioapic_register_irq

; 49   : {

$LN5:
	mov	BYTE PTR [rsp+32], r9b
	mov	BYTE PTR [rsp+24], r8b
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 50   : 	uint32_t reg = IOAPIC_REG_RED_TBL_BASE + irq* 2;

	movzx	eax, BYTE PTR irq$[rsp]
	lea	eax, DWORD PTR [rax+rax+16]
	mov	DWORD PTR reg$[rsp], eax

; 51   : 	write_ioapic_register((void*)io_apic_base, reg + 1, read_apic_register(0x02) << 24);

	mov	cx, 2
	call	?read_apic_register@@YA_KG@Z		; read_apic_register
	shl	rax, 24
	mov	ecx, DWORD PTR reg$[rsp]
	inc	ecx
	mov	r8d, eax
	movzx	edx, cl
	mov	rcx, QWORD PTR ?io_apic_base@@3PEAXEA	; io_apic_base
	call	?write_ioapic_register@@YAXPEAXEI@Z	; write_ioapic_register

; 52   : 	uint32_t low = read_ioapic_register ((void*)io_apic_base,reg);

	movzx	edx, BYTE PTR reg$[rsp]
	mov	rcx, QWORD PTR ?io_apic_base@@3PEAXEA	; io_apic_base
	call	?read_ioapic_register@@YAIPEAXE@Z	; read_ioapic_register
	mov	DWORD PTR low$[rsp], eax

; 53   : 	//!unmask the irq
; 54   : 	low &= ~(1<<16);

	mov	eax, DWORD PTR low$[rsp]
	btr	eax, 16
	mov	DWORD PTR low$[rsp], eax

; 55   : 	//!set to physical delivery mode
; 56   : 	low |= (0<<15);

	mov	eax, DWORD PTR low$[rsp]
	mov	DWORD PTR low$[rsp], eax

; 57   : 	if (level)

	movzx	eax, BYTE PTR level$[rsp]
	test	eax, eax
	je	SHORT $LN2@ioapic_reg

; 58   : 		low |= (1<<15);

	mov	eax, DWORD PTR low$[rsp]
	bts	eax, 15
	mov	DWORD PTR low$[rsp], eax

; 59   : 	else

	jmp	SHORT $LN1@ioapic_reg
$LN2@ioapic_reg:

; 60   : 		low |= (0<<15);

	mov	eax, DWORD PTR low$[rsp]
	mov	DWORD PTR low$[rsp], eax
$LN1@ioapic_reg:

; 61   : 	low |= (0<<13);

	mov	eax, DWORD PTR low$[rsp]
	mov	DWORD PTR low$[rsp], eax

; 62   : 	low |= (0<<11);

	mov	eax, DWORD PTR low$[rsp]
	mov	DWORD PTR low$[rsp], eax

; 63   : 	low |= vector + 32;

	mov	rax, QWORD PTR vector$[rsp]
	add	rax, 32					; 00000020H
	mov	ecx, DWORD PTR low$[rsp]
	or	rcx, rax
	mov	rax, rcx
	mov	DWORD PTR low$[rsp], eax

; 64   : 	write_ioapic_register(io_apic_base, reg, low);   //vector + 32

	mov	r8d, DWORD PTR low$[rsp]
	movzx	edx, BYTE PTR reg$[rsp]
	mov	rcx, QWORD PTR ?io_apic_base@@3PEAXEA	; io_apic_base
	call	?write_ioapic_register@@YAXPEAXEI@Z	; write_ioapic_register

; 65   :     setvect(vector + 32, fn);

	mov	rax, QWORD PTR vector$[rsp]
	add	rax, 32					; 00000020H
	mov	rdx, QWORD PTR fn$[rsp]
	mov	rcx, rax
	call	setvect

; 66   : }

	add	rsp, 56					; 00000038H
	ret	0
?ioapic_register_irq@@YAX_KP6AX0PEAX@ZE_N@Z ENDP	; ioapic_register_irq
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\ioapic.cpp
_TEXT	SEGMENT
ver$ = 32
intr_num$ = 36
ioapic_phys$ = 40
address$ = 64
?ioapic_init@@YAXPEAX@Z PROC				; ioapic_init

; 104  : {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 105  : 	uint64_t ioapic_phys = (uint64_t)address;

	mov	rax, QWORD PTR address$[rsp]
	mov	QWORD PTR ioapic_phys$[rsp], rax

; 106  : 	io_apic_base = (void*)AuMapMMIO(ioapic_phys,2);

	mov	edx, 2
	mov	rcx, QWORD PTR ioapic_phys$[rsp]
	call	AuMapMMIO
	mov	QWORD PTR ?io_apic_base@@3PEAXEA, rax	; io_apic_base

; 107  : 
; 108  : 	uint32_t ver = read_ioapic_register(io_apic_base, IOAPIC_REG_VER);

	mov	dl, 1
	mov	rcx, QWORD PTR ?io_apic_base@@3PEAXEA	; io_apic_base
	call	?read_ioapic_register@@YAIPEAXE@Z	; read_ioapic_register
	mov	DWORD PTR ver$[rsp], eax

; 109  : 	uint32_t intr_num = (ver >> 16) & 0xFF;

	mov	eax, DWORD PTR ver$[rsp]
	shr	eax, 16
	and	eax, 255				; 000000ffH
	mov	DWORD PTR intr_num$[rsp], eax

; 110  : 	/*for(size_t n = 0; n <= intr_num; ++n)
; 111  : 	{
; 112  : 		uint32_t reg = IOAPIC_REG_RED_TBL_BASE + n * 2;
; 113  : 		uint32_t val = read_ioapic_register(address, reg);
; 114  : 		write_ioapic_register(io_apic_base, reg, val |(1<<16));
; 115  : 	}*/
; 116  : 
; 117  : }

	add	rsp, 56					; 00000038H
	ret	0
?ioapic_init@@YAXPEAX@Z ENDP				; ioapic_init
_TEXT	ENDS
END
