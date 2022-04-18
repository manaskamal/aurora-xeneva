; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

_BSS	SEGMENT
x2apic	DB	01H DUP (?)
	ALIGN	8

apic	DQ	01H DUP (?)
apic_timer_count DD 01H DUP (?)
_BSS	ENDS
PUBLIC	?initialize_apic@@YAXXZ				; initialize_apic
PUBLIC	?apic_local_eoi@@YAXXZ				; apic_local_eoi
PUBLIC	?read_apic_register@@YA_KG@Z			; read_apic_register
PUBLIC	?write_apic_register@@YAXG_K@Z			; write_apic_register
PUBLIC	?timer_sleep@@YAXI@Z				; timer_sleep
PUBLIC	??$raw_offset@PECIPEAX@@YAPECIPEAXH@Z		; raw_offset<unsigned int volatile * __ptr64,void * __ptr64>
PUBLIC	?x2apic_supported@@YA_NXZ			; x2apic_supported
PUBLIC	?apic_spurious_interrupt@@YAX_KPEAX@Z		; apic_spurious_interrupt
PUBLIC	?apic_timer_interrupt@@YAX_KPEAX@Z		; apic_timer_interrupt
PUBLIC	?icr_dest@@YA_KI@Z				; icr_dest
PUBLIC	?icr_busy@@YA_NXZ				; icr_busy
EXTRN	x64_outportb:PROC
EXTRN	x64_read_msr:PROC
EXTRN	x64_write_msr:PROC
EXTRN	x64_mfence:PROC
EXTRN	x64_cpuid:PROC
EXTRN	?setvect@@YAX_KP6AX0PEAX@Z@Z:PROC		; setvect
EXTRN	?ioapic_init@@YAXPEAX@Z:PROC			; ioapic_init
pdata	SEGMENT
$pdata$?initialize_apic@@YAXXZ DD imagerel $LN4
	DD	imagerel $LN4+279
	DD	imagerel $unwind$?initialize_apic@@YAXXZ
$pdata$?apic_local_eoi@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+20
	DD	imagerel $unwind$?apic_local_eoi@@YAXXZ
$pdata$?read_apic_register@@YA_KG@Z DD imagerel $LN6
	DD	imagerel $LN6+191
	DD	imagerel $unwind$?read_apic_register@@YA_KG@Z
$pdata$?write_apic_register@@YAXG_K@Z DD imagerel $LN6
	DD	imagerel $LN6+231
	DD	imagerel $unwind$?write_apic_register@@YAXG_K@Z
$pdata$?timer_sleep@@YAXI@Z DD imagerel $LN5
	DD	imagerel $LN5+43
	DD	imagerel $unwind$?timer_sleep@@YAXI@Z
$pdata$?x2apic_supported@@YA_NXZ DD imagerel $LN5
	DD	imagerel $LN5+92
	DD	imagerel $unwind$?x2apic_supported@@YA_NXZ
$pdata$?io_wait@@YAXXZ DD imagerel ?io_wait@@YAXXZ
	DD	imagerel ?io_wait@@YAXXZ+44
	DD	imagerel $unwind$?io_wait@@YAXXZ
$pdata$?apic_timer_interrupt@@YAX_KPEAX@Z DD imagerel $LN3
	DD	imagerel $LN3+38
	DD	imagerel $unwind$?apic_timer_interrupt@@YAX_KPEAX@Z
$pdata$?icr_busy@@YA_NXZ DD imagerel $LN5
	DD	imagerel $LN5+52
	DD	imagerel $unwind$?icr_busy@@YA_NXZ
pdata	ENDS
xdata	SEGMENT
$unwind$?initialize_apic@@YAXXZ DD 010401H
	DD	08204H
$unwind$?apic_local_eoi@@YAXXZ DD 010401H
	DD	04204H
$unwind$?read_apic_register@@YA_KG@Z DD 010901H
	DD	08209H
$unwind$?write_apic_register@@YAXG_K@Z DD 010e01H
	DD	0a20eH
$unwind$?timer_sleep@@YAXI@Z DD 010801H
	DD	02208H
$unwind$?x2apic_supported@@YA_NXZ DD 010401H
	DD	0c204H
$unwind$?io_wait@@YAXXZ DD 010401H
	DD	02204H
$unwind$?apic_timer_interrupt@@YAX_KPEAX@Z DD 010e01H
	DD	0420eH
$unwind$?icr_busy@@YA_NXZ DD 010401H
	DD	06204H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\apic.cpp
_TEXT	SEGMENT
tv68 = 32
?icr_busy@@YA_NXZ PROC					; icr_busy

; 195  : bool icr_busy () {

$LN5:
	sub	rsp, 56					; 00000038H

; 196  : 	return (read_apic_register (LAPIC_REGISTER_ICR) & (1 << 12)) != 0;

	mov	cx, 48					; 00000030H
	call	?read_apic_register@@YA_KG@Z		; read_apic_register
	and	rax, 4096				; 00001000H
	test	rax, rax
	je	SHORT $LN3@icr_busy
	mov	DWORD PTR tv68[rsp], 1
	jmp	SHORT $LN4@icr_busy
$LN3@icr_busy:
	mov	DWORD PTR tv68[rsp], 0
$LN4@icr_busy:
	movzx	eax, BYTE PTR tv68[rsp]

; 197  : }

	add	rsp, 56					; 00000038H
	ret	0
?icr_busy@@YA_NXZ ENDP					; icr_busy
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\apic.cpp
_TEXT	SEGMENT
processor$ = 8
?icr_dest@@YA_KI@Z PROC					; icr_dest

; 188  : uint64_t icr_dest (uint32_t processor ) {

	mov	DWORD PTR [rsp+8], ecx

; 189  : 	if (x2apic)

	movzx	eax, BYTE PTR x2apic
	test	eax, eax
	je	SHORT $LN2@icr_dest

; 190  : 		return ((uint64_t)processor << 32);

	mov	eax, DWORD PTR processor$[rsp]
	shl	rax, 32					; 00000020H
	jmp	SHORT $LN3@icr_dest

; 191  : 	else

	jmp	SHORT $LN1@icr_dest
$LN2@icr_dest:

; 192  : 		return ((uint64_t)processor << 56);

	mov	eax, DWORD PTR processor$[rsp]
	shl	rax, 56					; 00000038H
$LN1@icr_dest:
$LN3@icr_dest:

; 193  : }

	fatret	0
?icr_dest@@YA_KI@Z ENDP					; icr_dest
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\apic.cpp
_TEXT	SEGMENT
p$ = 48
param$ = 56
?apic_timer_interrupt@@YAX_KPEAX@Z PROC			; apic_timer_interrupt

; 128  : void  apic_timer_interrupt (size_t p, void* param) {

$LN3:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 129  : 	apic_timer_count++;

	mov	eax, DWORD PTR apic_timer_count
	inc	eax
	mov	DWORD PTR apic_timer_count, eax

; 130  : 	apic_local_eoi();

	call	?apic_local_eoi@@YAXXZ			; apic_local_eoi

; 131  : }

	add	rsp, 40					; 00000028H
	ret	0
?apic_timer_interrupt@@YAX_KPEAX@Z ENDP			; apic_timer_interrupt
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\apic.cpp
_TEXT	SEGMENT
p$ = 8
param$ = 16
?apic_spurious_interrupt@@YAX_KPEAX@Z PROC		; apic_spurious_interrupt

; 102  : void apic_spurious_interrupt (size_t p, void* param) {

	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx

; 103  : }

	ret	0
?apic_spurious_interrupt@@YAX_KPEAX@Z ENDP		; apic_spurious_interrupt
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\apic.cpp
_TEXT	SEGMENT
counter$ = 0
?io_wait@@YAXXZ PROC					; io_wait

; 96   : static void io_wait(){

	sub	rsp, 24

; 97   : 	volatile size_t counter = 0;

	mov	QWORD PTR counter$[rsp], 0
	jmp	SHORT $LN3@io_wait
$LN2@io_wait:

; 98   : 	for(; counter < 1000; ++counter);

	mov	rax, QWORD PTR counter$[rsp]
	inc	rax
	mov	QWORD PTR counter$[rsp], rax
$LN3@io_wait:
	mov	rax, QWORD PTR counter$[rsp]
	cmp	rax, 1000				; 000003e8H
	jae	SHORT $LN1@io_wait
	jmp	SHORT $LN2@io_wait
$LN1@io_wait:

; 99   : }

	add	rsp, 24
	ret	0
?io_wait@@YAXXZ ENDP					; io_wait
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\apic.cpp
_TEXT	SEGMENT
tv72 = 48
c$ = 56
d$ = 64
b$ = 72
a$ = 80
?x2apic_supported@@YA_NXZ PROC				; x2apic_supported

; 89   : bool x2apic_supported(){

$LN5:
	sub	rsp, 104				; 00000068H

; 90   : 
; 91   : 	size_t a, b, c, d;
; 92   : 	x64_cpuid(0x1, &a, &b, &c, &d);

	mov	QWORD PTR [rsp+40], 0
	lea	rax, QWORD PTR d$[rsp]
	mov	QWORD PTR [rsp+32], rax
	lea	r9, QWORD PTR c$[rsp]
	lea	r8, QWORD PTR b$[rsp]
	lea	rdx, QWORD PTR a$[rsp]
	mov	ecx, 1
	call	x64_cpuid

; 93   : 	return (c & (1 << 21)) != 0;

	mov	rax, QWORD PTR c$[rsp]
	and	rax, 2097152				; 00200000H
	test	rax, rax
	je	SHORT $LN3@x2apic_sup
	mov	DWORD PTR tv72[rsp], 1
	jmp	SHORT $LN4@x2apic_sup
$LN3@x2apic_sup:
	mov	DWORD PTR tv72[rsp], 0
$LN4@x2apic_sup:
	movzx	eax, BYTE PTR tv72[rsp]

; 94   : }

	add	rsp, 104				; 00000068H
	ret	0
?x2apic_supported@@YA_NXZ ENDP				; x2apic_supported
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
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\apic.cpp
_TEXT	SEGMENT
tick$ = 0
ms$ = 32
?timer_sleep@@YAXI@Z PROC				; timer_sleep

; 181  : void timer_sleep(uint32_t ms) {

$LN5:
	mov	DWORD PTR [rsp+8], ecx
	sub	rsp, 24

; 182  : 	uint32_t tick = ms + apic_timer_count;

	mov	eax, DWORD PTR apic_timer_count
	mov	ecx, DWORD PTR ms$[rsp]
	add	ecx, eax
	mov	eax, ecx
	mov	DWORD PTR tick$[rsp], eax
$LN2@timer_slee:

; 183  : 	while (tick > apic_timer_count)

	mov	eax, DWORD PTR apic_timer_count
	cmp	DWORD PTR tick$[rsp], eax
	jbe	SHORT $LN1@timer_slee

; 184  : 		;

	jmp	SHORT $LN2@timer_slee
$LN1@timer_slee:

; 185  : }

	add	rsp, 24
	ret	0
?timer_sleep@@YAXI@Z ENDP				; timer_sleep
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\apic.cpp
_TEXT	SEGMENT
high_part$1 = 32
low_part$2 = 36
msr$3 = 40
reg_next_addr$4 = 48
reg_addr$5 = 56
reg_addr$6 = 64
reg$ = 96
value$ = 104
?write_apic_register@@YAXG_K@Z PROC			; write_apic_register

; 57   : void write_apic_register(uint16_t reg, uint64_t value){

$LN6:
	mov	QWORD PTR [rsp+16], rdx
	mov	WORD PTR [rsp+8], cx
	sub	rsp, 88					; 00000058H

; 58   : 
; 59   : 	if (x2apic){

	movzx	eax, BYTE PTR x2apic
	test	eax, eax
	je	SHORT $LN3@write_apic

; 60   : 
; 61   : 		size_t msr = IA32_X2APIC_REGISTER_BASE_MSR + reg;

	movzx	eax, WORD PTR reg$[rsp]
	add	eax, 2048				; 00000800H
	cdqe
	mov	QWORD PTR msr$3[rsp], rax

; 62   : 		x64_write_msr(msr, value);

	mov	rdx, QWORD PTR value$[rsp]
	mov	rcx, QWORD PTR msr$3[rsp]
	call	x64_write_msr

; 63   : 	} else {

	jmp	$LN2@write_apic
$LN3@write_apic:

; 64   : 
; 65   : 		if (reg == LAPIC_REGISTER_ICR){

	movzx	eax, WORD PTR reg$[rsp]
	cmp	eax, 48					; 00000030H
	jne	SHORT $LN1@write_apic

; 66   : 
; 67   : 			volatile uint32_t* reg_addr = raw_offset<volatile uint32_t*>(apic, reg << 4);

	movzx	eax, WORD PTR reg$[rsp]
	shl	eax, 4
	mov	edx, eax
	mov	rcx, QWORD PTR apic
	call	??$raw_offset@PECIPEAX@@YAPECIPEAXH@Z	; raw_offset<unsigned int volatile * __ptr64,void * __ptr64>
	mov	QWORD PTR reg_addr$5[rsp], rax

; 68   : 			volatile uint32_t* reg_next_addr = raw_offset<volatile uint32_t*>(apic, (reg + 1) << 4);

	movzx	eax, WORD PTR reg$[rsp]
	inc	eax
	shl	eax, 4
	mov	edx, eax
	mov	rcx, QWORD PTR apic
	call	??$raw_offset@PECIPEAX@@YAPECIPEAXH@Z	; raw_offset<unsigned int volatile * __ptr64,void * __ptr64>
	mov	QWORD PTR reg_next_addr$4[rsp], rax

; 69   : 			uint32_t low_part = value & UINT32_MAX;

	mov	eax, -1					; ffffffffH
	mov	rcx, QWORD PTR value$[rsp]
	and	rcx, rax
	mov	rax, rcx
	mov	DWORD PTR low_part$2[rsp], eax

; 70   : 			uint32_t high_part = (value >> 32);

	mov	rax, QWORD PTR value$[rsp]
	shr	rax, 32					; 00000020H
	mov	DWORD PTR high_part$1[rsp], eax

; 71   : 			*reg_next_addr = high_part;

	mov	rax, QWORD PTR reg_next_addr$4[rsp]
	mov	ecx, DWORD PTR high_part$1[rsp]
	mov	DWORD PTR [rax], ecx

; 72   : 			x64_mfence();

	call	x64_mfence

; 73   : 			*reg_addr = low_part;

	mov	rax, QWORD PTR reg_addr$5[rsp]
	mov	ecx, DWORD PTR low_part$2[rsp]
	mov	DWORD PTR [rax], ecx
$LN1@write_apic:

; 74   : 		}
; 75   : 		volatile uint32_t* reg_addr = raw_offset<volatile uint32_t*>(apic, reg << 4);

	movzx	eax, WORD PTR reg$[rsp]
	shl	eax, 4
	mov	edx, eax
	mov	rcx, QWORD PTR apic
	call	??$raw_offset@PECIPEAX@@YAPECIPEAXH@Z	; raw_offset<unsigned int volatile * __ptr64,void * __ptr64>
	mov	QWORD PTR reg_addr$6[rsp], rax

; 76   : 		*reg_addr = value;

	mov	rax, QWORD PTR reg_addr$6[rsp]
	mov	ecx, DWORD PTR value$[rsp]
	mov	DWORD PTR [rax], ecx
$LN2@write_apic:

; 77   : 	}
; 78   : }

	add	rsp, 88					; 00000058H
	ret	0
?write_apic_register@@YAXG_K@Z ENDP			; write_apic_register
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\apic.cpp
_TEXT	SEGMENT
msr$1 = 32
reg_addr$2 = 40
reg_next_addr$3 = 48
reg_addr$4 = 56
reg$ = 80
?read_apic_register@@YA_KG@Z PROC			; read_apic_register

; 38   : uint64_t read_apic_register(uint16_t reg){

$LN6:
	mov	WORD PTR [rsp+8], cx
	sub	rsp, 72					; 00000048H

; 39   : 
; 40   : 	if (x2apic){

	movzx	eax, BYTE PTR x2apic
	test	eax, eax
	je	SHORT $LN3@read_apic_

; 41   : 		size_t msr = IA32_X2APIC_REGISTER_BASE_MSR + reg;

	movzx	eax, WORD PTR reg$[rsp]
	add	eax, 2048				; 00000800H
	cdqe
	mov	QWORD PTR msr$1[rsp], rax

; 42   : 		return x64_read_msr(msr);

	mov	rcx, QWORD PTR msr$1[rsp]
	call	x64_read_msr
	jmp	$LN4@read_apic_

; 43   : 	} else{

	jmp	$LN2@read_apic_
$LN3@read_apic_:

; 44   : 
; 45   : 		if (reg == LAPIC_REGISTER_ICR){

	movzx	eax, WORD PTR reg$[rsp]
	cmp	eax, 48					; 00000030H
	jne	SHORT $LN1@read_apic_

; 46   : 			volatile uint32_t* reg_addr = raw_offset<volatile uint32_t*>(apic, reg << 4);

	movzx	eax, WORD PTR reg$[rsp]
	shl	eax, 4
	mov	edx, eax
	mov	rcx, QWORD PTR apic
	call	??$raw_offset@PECIPEAX@@YAPECIPEAXH@Z	; raw_offset<unsigned int volatile * __ptr64,void * __ptr64>
	mov	QWORD PTR reg_addr$2[rsp], rax

; 47   : 			volatile uint32_t* reg_next_addr = raw_offset<volatile uint32_t*>(apic, (reg+1) << 4);

	movzx	eax, WORD PTR reg$[rsp]
	inc	eax
	shl	eax, 4
	mov	edx, eax
	mov	rcx, QWORD PTR apic
	call	??$raw_offset@PECIPEAX@@YAPECIPEAXH@Z	; raw_offset<unsigned int volatile * __ptr64,void * __ptr64>
	mov	QWORD PTR reg_next_addr$3[rsp], rax

; 48   : 			return *reg_addr | ((uint64_t)*reg_next_addr << 32);

	mov	rax, QWORD PTR reg_addr$2[rsp]
	mov	eax, DWORD PTR [rax]
	mov	eax, eax
	mov	rcx, QWORD PTR reg_next_addr$3[rsp]
	mov	ecx, DWORD PTR [rcx]
	mov	ecx, ecx
	shl	rcx, 32					; 00000020H
	or	rax, rcx
	jmp	SHORT $LN4@read_apic_
$LN1@read_apic_:

; 49   : 		}
; 50   : 		volatile uint32_t* reg_addr = raw_offset<volatile uint32_t*>(apic, reg << 4);

	movzx	eax, WORD PTR reg$[rsp]
	shl	eax, 4
	mov	edx, eax
	mov	rcx, QWORD PTR apic
	call	??$raw_offset@PECIPEAX@@YAPECIPEAXH@Z	; raw_offset<unsigned int volatile * __ptr64,void * __ptr64>
	mov	QWORD PTR reg_addr$4[rsp], rax

; 51   : 		return *reg_addr;

	mov	rax, QWORD PTR reg_addr$4[rsp]
	mov	eax, DWORD PTR [rax]
	mov	eax, eax
$LN2@read_apic_:
$LN4@read_apic_:

; 52   : 	}
; 53   : }

	add	rsp, 72					; 00000048H
	ret	0
?read_apic_register@@YA_KG@Z ENDP			; read_apic_register
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\apic.cpp
_TEXT	SEGMENT
?apic_local_eoi@@YAXXZ PROC				; apic_local_eoi

; 82   : extern void apic_local_eoi(){

$LN3:
	sub	rsp, 40					; 00000028H

; 83   : 
; 84   : 	write_apic_register(LAPIC_REGISTER_EOI, 0);

	xor	edx, edx
	mov	cx, 11
	call	?write_apic_register@@YAXG_K@Z		; write_apic_register

; 85   : }

	add	rsp, 40					; 00000028H
	ret	0
?apic_local_eoi@@YAXXZ ENDP				; apic_local_eoi
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\apic.cpp
_TEXT	SEGMENT
apic_base$ = 32
timer_vector$ = 40
timer_reg$ = 48
?initialize_apic@@YAXXZ PROC				; initialize_apic

; 136  : void initialize_apic () {

$LN4:
	sub	rsp, 72					; 00000048H

; 137  : 
; 138  : 	size_t apic_base;
; 139  : 	apic_base = (size_t)0xFEE00000;

	mov	eax, -18874368				; fee00000H
	mov	QWORD PTR apic_base$[rsp], rax

; 140  : 	apic_timer_count = 0;

	mov	DWORD PTR apic_timer_count, 0

; 141  : 	//map_page (0xFEE00000, 0xFEE00000,0);
; 142  : 
; 143  : 	apic = (void*)apic_base;

	mov	rax, QWORD PTR apic_base$[rsp]
	mov	QWORD PTR apic, rax

; 144  : 
; 145  : 	if (x2apic_supported() ) {

	call	?x2apic_supported@@YA_NXZ		; x2apic_supported
	movzx	eax, al
	test	eax, eax
	je	SHORT $LN1@initialize

; 146  : 		x2apic = true;

	mov	BYTE PTR x2apic, 1

; 147  : 		apic_base |= IA32_APIC_BASE_MSR_X2APIC;

	mov	rax, QWORD PTR apic_base$[rsp]
	bts	rax, 10
	mov	QWORD PTR apic_base$[rsp], rax
$LN1@initialize:

; 148  : 	}
; 149  : 
; 150  : 	apic_base |= IA32_APIC_BASE_MSR_ENABLE;

	mov	rax, QWORD PTR apic_base$[rsp]
	bts	rax, 11
	mov	QWORD PTR apic_base$[rsp], rax

; 151  : 	x64_write_msr (IA32_APIC_BASE_MSR, apic_base);

	mov	rdx, QWORD PTR apic_base$[rsp]
	mov	ecx, 27
	call	x64_write_msr

; 152  : 	setvect (0xFF, apic_spurious_interrupt);

	lea	rdx, OFFSET FLAT:?apic_spurious_interrupt@@YAX_KPEAX@Z ; apic_spurious_interrupt
	mov	ecx, 255				; 000000ffH
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 153  : 	write_apic_register (LAPIC_REGISTER_SVR, read_apic_register (LAPIC_REGISTER_SVR) | 
; 154  : 		                                     IA32_APIC_SVR_ENABLE | 0xFF);

	mov	cx, 15
	call	?read_apic_register@@YA_KG@Z		; read_apic_register
	bts	rax, 8
	or	rax, 255				; 000000ffH
	mov	rdx, rax
	mov	cx, 15
	call	?write_apic_register@@YAXG_K@Z		; write_apic_register

; 155  : 
; 156  : 
; 157  : 	//!Register the time speed
; 158  : 	write_apic_register (LAPIC_REGISTER_TMRDIV, 0x3);  //0xa

	mov	edx, 3
	mov	cx, 62					; 0000003eH
	call	?write_apic_register@@YAXG_K@Z		; write_apic_register

; 159  : 
; 160  : 	/*! timer initialized*/
; 161  : 	size_t timer_vector = 0x40;

	mov	QWORD PTR timer_vector$[rsp], 64	; 00000040H

; 162  : 	setvect (timer_vector, apic_timer_interrupt);

	lea	rdx, OFFSET FLAT:?apic_timer_interrupt@@YAX_KPEAX@Z ; apic_timer_interrupt
	mov	rcx, QWORD PTR timer_vector$[rsp]
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 163  : 
; 164  : 	size_t timer_reg = (1 << 17) | timer_vector;

	mov	rax, QWORD PTR timer_vector$[rsp]
	bts	rax, 17
	mov	QWORD PTR timer_reg$[rsp], rax

; 165  : 	write_apic_register (LAPIC_REGISTER_LVT_TIMER, timer_reg);

	mov	rdx, QWORD PTR timer_reg$[rsp]
	mov	cx, 50					; 00000032H
	call	?write_apic_register@@YAXG_K@Z		; write_apic_register

; 166  : 	io_wait ();

	call	?io_wait@@YAXXZ				; io_wait

; 167  : 	write_apic_register (LAPIC_REGISTER_TMRINITCNT,1000);  //100 , 500

	mov	edx, 1000				; 000003e8H
	mov	cx, 56					; 00000038H
	call	?write_apic_register@@YAXG_K@Z		; write_apic_register

; 168  : 	
; 169  : 
; 170  : 	x64_outportb(PIC1_DATA, 0xFF);

	mov	dl, 255					; 000000ffH
	mov	cx, 33					; 00000021H
	call	x64_outportb

; 171  : 	io_wait();

	call	?io_wait@@YAXXZ				; io_wait

; 172  : 	x64_outportb(PIC2_DATA, 0xFF);

	mov	dl, 255					; 000000ffH
	mov	cx, 161					; 000000a1H
	call	x64_outportb

; 173  : 
; 174  : 	//! Finally Intialize I/O APIC
; 175  : 	//map_page (ioapic_base,ioapic_base,0);
; 176  : 	ioapic_init ((void*)0xfec00000);

	mov	ecx, -20971520				; fffffffffec00000H
	call	?ioapic_init@@YAXPEAX@Z			; ioapic_init

; 177  : 
; 178  : }

	add	rsp, 72					; 00000048H
	ret	0
?initialize_apic@@YAXXZ ENDP				; initialize_apic
_TEXT	ENDS
END
