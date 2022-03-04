; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

_BSS	SEGMENT
pit_tick DD	01H DUP (?)
_BSS	ENDS
CONST	SEGMENT
$SG2956	DB	'*** [x64_idt] x64_default_handler: Unhandled Exception *'
	DB	'** ', 0aH, 00H
	ORG $+3
$SG2996	DB	'IDT initialized', 0aH, 00H
	ORG $+7
$SG2997	DB	'Exception initialized', 0aH, 00H
	ORG $+1
$SG2998	DB	'APIC initialized', 0aH, 00H
	ORG $+6
$SG3000	DB	'EFER.SYSCALL enabled', 0aH, 00H
	ORG $+2
$SG3001	DB	'User Land Initialized', 0aH, 00H
	ORG $+1
$SG3002	DB	'System call initialized', 0aH, 00H
	ORG $+7
$SG3010	DB	'x86_64:SSE supported', 0aH, 00H
	ORG $+2
$SG3012	DB	'x86_64:fxsave & fxrstor supported', 0aH, 00H
CONST	ENDS
PUBLIC	?hal_x86_64_init@@YAXXZ				; hal_x86_64_init
PUBLIC	?setvect@@YAX_KP6AX0PEAX@Z@Z			; setvect
PUBLIC	gdt_initialize
PUBLIC	?interrupt_initialize@@YAXXZ			; interrupt_initialize
PUBLIC	?hal_x86_64_setup_int@@YAXXZ			; hal_x86_64_setup_int
PUBLIC	?hal_x86_64_feature_check@@YAXXZ		; hal_x86_64_feature_check
PUBLIC	load_default_sregs
PUBLIC	?set_gdt_entry@@YAXAEAU_gdt@@_K1EE@Z		; set_gdt_entry
PUBLIC	?save_sregs@@YAXXZ				; save_sregs
PUBLIC	interrupt_dispatcher
PUBLIC	?default_irq@@YAX_KPEAX@Z			; default_irq
PUBLIC	?pit_handler_callback@@YAX_KPEAX@Z		; pit_handler_callback
EXTRN	x64_cli:PROC
EXTRN	x64_sti:PROC
EXTRN	x64_read_msr:PROC
EXTRN	x64_write_msr:PROC
EXTRN	x64_cpuid:PROC
EXTRN	x64_lgdt:PROC
EXTRN	x64_sgdt:PROC
EXTRN	?exception_init@@YAXXZ:PROC			; exception_init
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
EXTRN	?initialize_syscall@@YAXXZ:PROC			; initialize_syscall
EXTRN	?initialize_user_land@@YAX_K@Z:PROC		; initialize_user_land
EXTRN	?initialize_apic@@YAXXZ:PROC			; initialize_apic
EXTRN	?apic_local_eoi@@YAXXZ:PROC			; apic_local_eoi
EXTRN	x64_get_segment_register:PROC
EXTRN	x64_set_segment_register:PROC
EXTRN	x64_ltr:PROC
EXTRN	x64_lidt:PROC
EXTRN	?debug_print@@YAXPEBDZZ:PROC			; debug_print
EXTRN	default_irq_handlers:BYTE
_BSS	SEGMENT
	ALIGN	8

gdt	DQ	09H DUP (?)
the_gdtr DB	0aH DUP (?)
	ALIGN	4

old_gdtr DB	0aH DUP (?)
	ALIGN	4

oldsregs DW	08H DUP (?)
interrupts_handlers DQ 0100H DUP (?)
the_idt	DB	01000H DUP (?)
_BSS	ENDS
pdata	SEGMENT
$pdata$?hal_x86_64_init@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+24
	DD	imagerel $unwind$?hal_x86_64_init@@YAXXZ
$pdata$gdt_initialize DD imagerel $LN3
	DD	imagerel $LN3+81
	DD	imagerel $unwind$gdt_initialize
$pdata$?interrupt_initialize@@YAXXZ DD imagerel $LN12
	DD	imagerel $LN12+535
	DD	imagerel $unwind$?interrupt_initialize@@YAXXZ
$pdata$?hal_x86_64_setup_int@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+213
	DD	imagerel $unwind$?hal_x86_64_setup_int@@YAXXZ
$pdata$?hal_x86_64_feature_check@@YAXXZ DD imagerel $LN5
	DD	imagerel $LN5+109
	DD	imagerel $unwind$?hal_x86_64_feature_check@@YAXXZ
$pdata$load_default_sregs DD imagerel $LN3
	DD	imagerel $LN3+90
	DD	imagerel $unwind$load_default_sregs
$pdata$?set_gdt_entry@@YAXAEAU_gdt@@EE@Z DD imagerel ?set_gdt_entry@@YAXAEAU_gdt@@EE@Z
	DD	imagerel ?set_gdt_entry@@YAXAEAU_gdt@@EE@Z+82
	DD	imagerel $unwind$?set_gdt_entry@@YAXAEAU_gdt@@EE@Z
$pdata$?fill_gdt@@YAXPEAU_gdt@@@Z DD imagerel ?fill_gdt@@YAXPEAU_gdt@@@Z
	DD	imagerel ?fill_gdt@@YAXPEAU_gdt@@@Z+253
	DD	imagerel $unwind$?fill_gdt@@YAXPEAU_gdt@@@Z
$pdata$?save_sregs@@YAXXZ DD imagerel $LN6
	DD	imagerel $LN6+67
	DD	imagerel $unwind$?save_sregs@@YAXXZ
$pdata$?register_irq@@YAXPEAU_idt@@PEAX@Z DD imagerel ?register_irq@@YAXPEAU_idt@@PEAX@Z
	DD	imagerel ?register_irq@@YAXPEAU_idt@@PEAX@Z+93
	DD	imagerel $unwind$?register_irq@@YAXPEAU_idt@@PEAX@Z
$pdata$interrupt_dispatcher DD imagerel $LN3
	DD	imagerel $LN3+45
	DD	imagerel $unwind$interrupt_dispatcher
$pdata$?default_irq@@YAX_KPEAX@Z DD imagerel $LN5
	DD	imagerel $LN5+38
	DD	imagerel $unwind$?default_irq@@YAX_KPEAX@Z
$pdata$?pit_handler_callback@@YAX_KPEAX@Z DD imagerel $LN3
	DD	imagerel $LN3+24
	DD	imagerel $unwind$?pit_handler_callback@@YAX_KPEAX@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?hal_x86_64_init@@YAXXZ DD 010401H
	DD	04204H
$unwind$gdt_initialize DD 010401H
	DD	04204H
$unwind$?interrupt_initialize@@YAXXZ DD 020701H
	DD	0a30107H
$unwind$?hal_x86_64_setup_int@@YAXXZ DD 010401H
	DD	06204H
$unwind$?hal_x86_64_feature_check@@YAXXZ DD 010401H
	DD	0a204H
$unwind$load_default_sregs DD 010401H
	DD	04204H
$unwind$?set_gdt_entry@@YAXAEAU_gdt@@EE@Z DD 011201H
	DD	06212H
$unwind$?fill_gdt@@YAXPEAU_gdt@@@Z DD 010901H
	DD	06209H
$unwind$?save_sregs@@YAXXZ DD 010401H
	DD	06204H
$unwind$?register_irq@@YAXPEAU_idt@@PEAX@Z DD 010e01H
	DD	0220eH
$unwind$interrupt_dispatcher DD 010e01H
	DD	0420eH
$unwind$?default_irq@@YAX_KPEAX@Z DD 010e01H
	DD	0420eH
$unwind$?pit_handler_callback@@YAX_KPEAX@Z DD 010e01H
	DD	0420eH
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\cpu.cpp
_TEXT	SEGMENT
p$ = 48
param$ = 56
?pit_handler_callback@@YAX_KPEAX@Z PROC			; pit_handler_callback

; 193  : void pit_handler_callback (size_t p, void* param) {

$LN3:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 194  : 	apic_local_eoi();

	call	?apic_local_eoi@@YAXXZ			; apic_local_eoi

; 195  : }

	add	rsp, 40					; 00000028H
	ret	0
?pit_handler_callback@@YAX_KPEAX@Z ENDP			; pit_handler_callback
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\cpu.cpp
_TEXT	SEGMENT
vect$ = 48
param$ = 56
?default_irq@@YAX_KPEAX@Z PROC				; default_irq

; 137  : void default_irq(size_t vect, void* param){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 138  : 	x64_cli();

	call	x64_cli

; 139  : 	printf("*** [x64_idt] x64_default_handler: Unhandled Exception *** \n");

	lea	rcx, OFFSET FLAT:$SG2956
	call	?printf@@YAXPEBDZZ			; printf
$LN2@default_ir:

; 140  : 	for(;;);

	jmp	SHORT $LN2@default_ir

; 141  : }

	add	rsp, 40					; 00000028H
	ret	0
?default_irq@@YAX_KPEAX@Z ENDP				; default_irq
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\cpu.cpp
_TEXT	SEGMENT
num$ = 48
frame$ = 56
interrupt_dispatcher PROC

; 131  : {	

$LN3:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 132  : 	interrupts_handlers[num](num, frame);

	lea	rax, OFFSET FLAT:interrupts_handlers
	mov	rdx, QWORD PTR frame$[rsp]
	mov	rcx, QWORD PTR num$[rsp]
	mov	r8, QWORD PTR num$[rsp]
	call	QWORD PTR [rax+r8*8]

; 133  : 	return;
; 134  : }

	add	rsp, 40					; 00000028H
	ret	0
interrupt_dispatcher ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\cpu.cpp
_TEXT	SEGMENT
faddr$ = 0
entry$ = 32
function$ = 40
?register_irq@@YAXPEAU_idt@@PEAX@Z PROC			; register_irq

; 118  : {

	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 24

; 119  : 	size_t faddr = (size_t)function;

	mov	rax, QWORD PTR function$[rsp]
	mov	QWORD PTR faddr$[rsp], rax

; 120  : 	entry->offset_1 = faddr & UINT16_MAX;

	mov	rax, QWORD PTR faddr$[rsp]
	and	rax, 65535				; 0000ffffH
	mov	rcx, QWORD PTR entry$[rsp]
	mov	WORD PTR [rcx], ax

; 121  : 	entry->offset_2 = (faddr >> 16) & UINT16_MAX;

	mov	rax, QWORD PTR faddr$[rsp]
	shr	rax, 16
	and	rax, 65535				; 0000ffffH
	mov	rcx, QWORD PTR entry$[rsp]
	mov	WORD PTR [rcx+6], ax

; 122  : 	entry->offset_3 = (faddr >> 32) & UINT32_MAX;

	mov	rax, QWORD PTR faddr$[rsp]
	shr	rax, 32					; 00000020H
	mov	ecx, -1					; ffffffffH
	and	rax, rcx
	mov	rcx, QWORD PTR entry$[rsp]
	mov	DWORD PTR [rcx+8], eax

; 123  : }

	add	rsp, 24
	ret	0
?register_irq@@YAXPEAU_idt@@PEAX@Z ENDP			; register_irq
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\cpu.cpp
_TEXT	SEGMENT
reg$1 = 32
?save_sregs@@YAXXZ PROC					; save_sregs

; 81   : {

$LN6:
	sub	rsp, 56					; 00000038H

; 82   : 	for (uint_fast8_t reg = 0; reg < 8; ++reg)

	mov	BYTE PTR reg$1[rsp], 0
	jmp	SHORT $LN3@save_sregs
$LN2@save_sregs:
	movzx	eax, BYTE PTR reg$1[rsp]
	inc	al
	mov	BYTE PTR reg$1[rsp], al
$LN3@save_sregs:
	movzx	eax, BYTE PTR reg$1[rsp]
	cmp	eax, 8
	jge	SHORT $LN1@save_sregs

; 83   : 		oldsregs[reg] = x64_get_segment_register(reg);

	movzx	eax, BYTE PTR reg$1[rsp]
	mov	ecx, eax
	call	x64_get_segment_register
	movzx	ecx, BYTE PTR reg$1[rsp]
	lea	rdx, OFFSET FLAT:oldsregs
	mov	WORD PTR [rdx+rcx*2], ax
	jmp	SHORT $LN2@save_sregs
$LN1@save_sregs:

; 84   : }

	add	rsp, 56					; 00000038H
	ret	0
?save_sregs@@YAXXZ ENDP					; save_sregs
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\cpu.cpp
_TEXT	SEGMENT
thegdt$ = 64
?fill_gdt@@YAXPEAU_gdt@@@Z PROC				; fill_gdt

; 64   : {

	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 65   : 	set_gdt_entry(thegdt[GDT_ENTRY_NULL], 0, 0, 0, 0);    //0x00

	mov	eax, 8
	imul	rax, 0
	mov	rcx, QWORD PTR thegdt$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	BYTE PTR [rsp+32], 0
	xor	r9d, r9d
	xor	r8d, r8d
	xor	edx, edx
	mov	rcx, rax
	call	?set_gdt_entry@@YAXAEAU_gdt@@_K1EE@Z	; set_gdt_entry

; 66   : 	//Kernel Code segment: STAR.SYSCALL_CS
; 67   : 	set_gdt_entry(thegdt[GDT_ENTRY_KERNEL_CODE], GDT_ACCESS_PRIVL(0) | GDT_ACCESS_RW | GDT_ACCESS_EX, GDT_FLAG_64BT);  //0x08

	mov	eax, 8
	imul	rax, 1
	mov	rcx, QWORD PTR thegdt$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	r8b, 2
	mov	dl, 10
	mov	rcx, rax
	call	?set_gdt_entry@@YAXAEAU_gdt@@EE@Z	; set_gdt_entry

; 68   : 	//Kernel Data segment
; 69   : 	set_gdt_entry(thegdt[GDT_ENTRY_KERNEL_DATA], GDT_ACCESS_PRIVL(0) | GDT_ACCESS_RW, GDT_FLAG_32BT);    //0x10

	mov	eax, 8
	imul	rax, 2
	mov	rcx, QWORD PTR thegdt$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	r8b, 4
	mov	dl, 2
	mov	rcx, rax
	call	?set_gdt_entry@@YAXAEAU_gdt@@EE@Z	; set_gdt_entry

; 70   : 	//User Code segment (32 bit): STAR.SYSRET_CS
; 71   : 	set_gdt_entry(thegdt[GDT_ENTRY_USER_CODE32], GDT_ACCESS_PRIVL(3) | GDT_ACCESS_RW | GDT_ACCESS_EX, GDT_FLAG_32BT);  //0x18

	mov	eax, 8
	imul	rax, 3
	mov	rcx, QWORD PTR thegdt$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	r8b, 4
	mov	dl, 106					; 0000006aH
	mov	rcx, rax
	call	?set_gdt_entry@@YAXAEAU_gdt@@EE@Z	; set_gdt_entry

; 72   : 	//User Data segment
; 73   : 	set_gdt_entry(thegdt[GDT_ENTRY_USER_DATA], GDT_ACCESS_PRIVL(3) | GDT_ACCESS_RW, GDT_FLAG_32BT);    //0x20

	mov	eax, 8
	imul	rax, 4
	mov	rcx, QWORD PTR thegdt$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	r8b, 4
	mov	dl, 98					; 00000062H
	mov	rcx, rax
	call	?set_gdt_entry@@YAXAEAU_gdt@@EE@Z	; set_gdt_entry

; 74   : 	//User Code segment (64 bit)
; 75   : 	set_gdt_entry(thegdt[GDT_ENTRY_USER_CODE], GDT_ACCESS_PRIVL(3) | GDT_ACCESS_RW | GDT_ACCESS_EX, GDT_FLAG_64BT);   //0x28  | 3 -- 0x2B

	mov	eax, 8
	imul	rax, 5
	mov	rcx, QWORD PTR thegdt$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	r8b, 2
	mov	dl, 106					; 0000006aH
	mov	rcx, rax
	call	?set_gdt_entry@@YAXAEAU_gdt@@EE@Z	; set_gdt_entry

; 76   : 	//Kernel Code segment (32 bit)
; 77   : 	set_gdt_entry(thegdt[GDT_ENTRY_KERNEL_CODE32], GDT_ACCESS_PRIVL(3) | GDT_ACCESS_RW | GDT_ACCESS_EX , GDT_FLAG_32BT);  //0x30

	mov	eax, 8
	imul	rax, 6
	mov	rcx, QWORD PTR thegdt$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	r8b, 4
	mov	dl, 106					; 0000006aH
	mov	rcx, rax
	call	?set_gdt_entry@@YAXAEAU_gdt@@EE@Z	; set_gdt_entry

; 78   : }

	add	rsp, 56					; 00000038H
	ret	0
?fill_gdt@@YAXPEAU_gdt@@@Z ENDP				; fill_gdt
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\cpu.cpp
_TEXT	SEGMENT
entry$ = 64
access$ = 72
flags$ = 80
?set_gdt_entry@@YAXAEAU_gdt@@EE@Z PROC			; set_gdt_entry

; 57   : {

	mov	BYTE PTR [rsp+24], r8b
	mov	BYTE PTR [rsp+16], dl
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 58   : 	access |= GDT_ACCESS_PRESENT | GDT_ACCESS_TYPE;

	movzx	eax, BYTE PTR access$[rsp]
	or	eax, 144				; 00000090H
	mov	BYTE PTR access$[rsp], al

; 59   : 	flags |= GDT_FLAG_GRAN;

	movzx	eax, BYTE PTR flags$[rsp]
	or	eax, 8
	mov	BYTE PTR flags$[rsp], al

; 60   : 	set_gdt_entry(entry, 0, SIZE_MAX, access, flags);

	movzx	eax, BYTE PTR flags$[rsp]
	mov	BYTE PTR [rsp+32], al
	movzx	r9d, BYTE PTR access$[rsp]
	mov	r8d, 1048575				; 000fffffH
	xor	edx, edx
	mov	rcx, QWORD PTR entry$[rsp]
	call	?set_gdt_entry@@YAXAEAU_gdt@@_K1EE@Z	; set_gdt_entry

; 61   : }

	add	rsp, 56					; 00000038H
	ret	0
?set_gdt_entry@@YAXAEAU_gdt@@EE@Z ENDP			; set_gdt_entry
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\cpu.cpp
_TEXT	SEGMENT
entry$ = 8
base$ = 16
limit$ = 24
access$ = 32
flags$ = 40
?set_gdt_entry@@YAXAEAU_gdt@@_K1EE@Z PROC		; set_gdt_entry

; 47   : {

	mov	BYTE PTR [rsp+32], r9b
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx

; 48   : 	entry.base_low = base & 0xFFFF;

	mov	rax, QWORD PTR base$[rsp]
	and	rax, 65535				; 0000ffffH
	mov	rcx, QWORD PTR entry$[rsp]
	mov	WORD PTR [rcx+2], ax

; 49   : 	entry.base_mid = (base >> 16) & 0xFF;

	mov	rax, QWORD PTR base$[rsp]
	shr	rax, 16
	and	rax, 255				; 000000ffH
	mov	rcx, QWORD PTR entry$[rsp]
	mov	BYTE PTR [rcx+4], al

; 50   : 	entry.base_high = (base >> 24) & 0xFF;

	mov	rax, QWORD PTR base$[rsp]
	shr	rax, 24
	and	rax, 255				; 000000ffH
	mov	rcx, QWORD PTR entry$[rsp]
	mov	BYTE PTR [rcx+7], al

; 51   : 	entry.limit_low = limit & 0xFFFF;

	mov	rax, QWORD PTR limit$[rsp]
	and	rax, 65535				; 0000ffffH
	mov	rcx, QWORD PTR entry$[rsp]
	mov	WORD PTR [rcx], ax

; 52   : 	entry.access = access;

	mov	rax, QWORD PTR entry$[rsp]
	movzx	ecx, BYTE PTR access$[rsp]
	mov	BYTE PTR [rax+5], cl

; 53   : 	entry.flags_limit = (flags << 4) | ((limit >> 16) & 0xF);

	movzx	eax, BYTE PTR flags$[rsp]
	shl	eax, 4
	cdqe
	mov	rcx, QWORD PTR limit$[rsp]
	shr	rcx, 16
	and	rcx, 15
	or	rax, rcx
	mov	rcx, QWORD PTR entry$[rsp]
	mov	BYTE PTR [rcx+6], al

; 54   : }

	ret	0
?set_gdt_entry@@YAXAEAU_gdt@@_K1EE@Z ENDP		; set_gdt_entry
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\cpu.cpp
_TEXT	SEGMENT
load_default_sregs PROC

; 87   : {

$LN3:
	sub	rsp, 40					; 00000028H

; 88   : 	x64_set_segment_register(SREG_CS, SEGVAL(GDT_ENTRY_KERNEL_CODE, 0));		

	mov	dx, 8
	xor	ecx, ecx
	call	x64_set_segment_register

; 89   : 	x64_set_segment_register(SREG_DS, SEGVAL(GDT_ENTRY_KERNEL_DATA, 0));

	mov	dx, 16
	mov	ecx, 1
	call	x64_set_segment_register

; 90   : 	x64_set_segment_register(SREG_ES, SEGVAL(GDT_ENTRY_KERNEL_DATA, 0));

	mov	dx, 16
	mov	ecx, 2
	call	x64_set_segment_register

; 91   : 	x64_set_segment_register(SREG_SS, SEGVAL(GDT_ENTRY_KERNEL_DATA, 0));

	mov	dx, 16
	mov	ecx, 5
	call	x64_set_segment_register

; 92   : 	//Per CPU data
; 93   : 	x64_set_segment_register(SREG_FS, SEGVAL(GDT_ENTRY_KERNEL_DATA, 0));

	mov	dx, 16
	mov	ecx, 3
	call	x64_set_segment_register

; 94   : 	x64_set_segment_register(SREG_GS, SEGVAL(GDT_ENTRY_KERNEL_DATA, 0));

	mov	dx, 16
	mov	ecx, 4
	call	x64_set_segment_register

; 95   : }

	add	rsp, 40					; 00000028H
	ret	0
load_default_sregs ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\cpu.cpp
_TEXT	SEGMENT
d$ = 48
c$ = 56
b$ = 64
a$ = 72
?hal_x86_64_feature_check@@YAXXZ PROC			; hal_x86_64_feature_check

; 241  : void hal_x86_64_feature_check () {

$LN5:
	sub	rsp, 88					; 00000058H

; 242  : 	size_t a, b, c, d;
; 243  : 	x64_cpuid(1, &a, &b, &c, &d, 0);

	mov	QWORD PTR [rsp+40], 0
	lea	rax, QWORD PTR d$[rsp]
	mov	QWORD PTR [rsp+32], rax
	lea	r9, QWORD PTR c$[rsp]
	lea	r8, QWORD PTR b$[rsp]
	lea	rdx, QWORD PTR a$[rsp]
	mov	ecx, 1
	call	x64_cpuid

; 244  : 	if ((d & (1<<25)) != 0) {

	mov	rax, QWORD PTR d$[rsp]
	and	rax, 33554432				; 02000000H
	test	rax, rax
	je	SHORT $LN2@hal_x86_64

; 245  : 		printf ("x86_64:SSE supported\n");

	lea	rcx, OFFSET FLAT:$SG3010
	call	?printf@@YAXPEBDZZ			; printf

; 246  : 		if ((d & (1<<24)) != 0) {

	mov	rax, QWORD PTR d$[rsp]
	and	rax, 16777216				; 01000000H
	test	rax, rax
	je	SHORT $LN1@hal_x86_64

; 247  : 			printf ("x86_64:fxsave & fxrstor supported\n");

	lea	rcx, OFFSET FLAT:$SG3012
	call	?printf@@YAXPEBDZZ			; printf
$LN1@hal_x86_64:
$LN2@hal_x86_64:

; 248  : 		}
; 249  : 	}
; 250  : }

	add	rsp, 88					; 00000058H
	ret	0
?hal_x86_64_feature_check@@YAXXZ ENDP			; hal_x86_64_feature_check
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\cpu.cpp
_TEXT	SEGMENT
efer$ = 32
?hal_x86_64_setup_int@@YAXXZ PROC			; hal_x86_64_setup_int

; 198  : void hal_x86_64_setup_int () {

$LN3:
	sub	rsp, 56					; 00000038H

; 199  : 	x64_cli();

	call	x64_cli

; 200  : 
; 201  : 	////! initialize the interrupt descriptor table
; 202  : 	interrupt_initialize();

	call	?interrupt_initialize@@YAXXZ		; interrupt_initialize

; 203  : 	debug_print ("IDT initialized\n");

	lea	rcx, OFFSET FLAT:$SG2996
	call	?debug_print@@YAXPEBDZZ			; debug_print

; 204  : 	x64_sti();

	call	x64_sti

; 205  : 	////! initialize all exception handlers
; 206  : 	exception_init ();

	call	?exception_init@@YAXXZ			; exception_init

; 207  : 
; 208  : 	debug_print ("Exception initialized\n");

	lea	rcx, OFFSET FLAT:$SG2997
	call	?debug_print@@YAXPEBDZZ			; debug_print

; 209  : 	
; 210  : 
; 211  : 	//!Initialize APIC   FIXME: Causes triple fault now
; 212  : 	initialize_apic ();

	call	?initialize_apic@@YAXXZ			; initialize_apic

; 213  : 	
; 214  : 	debug_print ("APIC initialized\n");

	lea	rcx, OFFSET FLAT:$SG2998
	call	?debug_print@@YAXPEBDZZ			; debug_print

; 215  : 
; 216  : //	//!Enable EFER and SYSCALL Extension
; 217  : 	size_t efer = x64_read_msr(IA32_EFER);

	mov	ecx, -1073741696			; c0000080H
	call	x64_read_msr
	mov	QWORD PTR efer$[rsp], rax

; 218  : 	efer |= (1<<11);

	mov	rax, QWORD PTR efer$[rsp]
	bts	rax, 11
	mov	QWORD PTR efer$[rsp], rax

; 219  : 	efer |= 1;

	mov	rax, QWORD PTR efer$[rsp]
	or	rax, 1
	mov	QWORD PTR efer$[rsp], rax

; 220  : 	efer |= (1<<0);

	mov	rax, QWORD PTR efer$[rsp]
	or	rax, 1
	mov	QWORD PTR efer$[rsp], rax

; 221  : 	efer |= 1;

	mov	rax, QWORD PTR efer$[rsp]
	or	rax, 1
	mov	QWORD PTR efer$[rsp], rax

; 222  : 	x64_write_msr(IA32_EFER, efer);

	mov	rdx, QWORD PTR efer$[rsp]
	mov	ecx, -1073741696			; c0000080H
	call	x64_write_msr

; 223  : 	//! now start the interrupts
; 224  : 
; 225  : 	debug_print ("EFER.SYSCALL enabled\n");

	lea	rcx, OFFSET FLAT:$SG3000
	call	?debug_print@@YAXPEBDZZ			; debug_print

; 226  : 	//! initialize the user land environment
; 227  : 	initialize_user_land (64);

	mov	ecx, 64					; 00000040H
	call	?initialize_user_land@@YAX_K@Z		; initialize_user_land

; 228  : 
; 229  : 	debug_print ("User Land Initialized\n");

	lea	rcx, OFFSET FLAT:$SG3001
	call	?debug_print@@YAXPEBDZZ			; debug_print

; 230  : 	//! initialize the syscall entries
; 231  : 	initialize_syscall ();

	call	?initialize_syscall@@YAXXZ		; initialize_syscall

; 232  : 
; 233  : 	debug_print ("System call initialized\n");

	lea	rcx, OFFSET FLAT:$SG3002
	call	?debug_print@@YAXPEBDZZ			; debug_print

; 234  : 
; 235  : 	//apic_initialize_timer();
; 236  :     x64_sti ();

	call	x64_sti

; 237  : 	
; 238  : }

	add	rsp, 56					; 00000038H
	ret	0
?hal_x86_64_setup_int@@YAXXZ ENDP			; hal_x86_64_setup_int
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\cpu.cpp
_TEXT	SEGMENT
n$1 = 48
i$2 = 52
i$3 = 56
idtr$ = 64
thegdt$ = 72
tv168 = 80
curr_gdt$ = 88
m_ist$ = 104
tss$ = 144
bos$4 = 256
?interrupt_initialize@@YAXXZ PROC			; interrupt_initialize

; 145  : void  interrupt_initialize() {

$LN12:
	sub	rsp, 1304				; 00000518H

; 146  :  
; 147  : 
; 148  : 	void* m_ist[4];
; 149  : 	uint32_t tss[28];
; 150  : 	for (int i = 0; i < 28; i++) tss[i] = 0xffffffff;

	mov	DWORD PTR i$3[rsp], 0
	jmp	SHORT $LN9@interrupt_
$LN8@interrupt_:
	mov	eax, DWORD PTR i$3[rsp]
	inc	eax
	mov	DWORD PTR i$3[rsp], eax
$LN9@interrupt_:
	cmp	DWORD PTR i$3[rsp], 28
	jge	SHORT $LN7@interrupt_
	movsxd	rax, DWORD PTR i$3[rsp]
	mov	DWORD PTR tss$[rsp+rax*4], -1		; ffffffffH
	jmp	SHORT $LN8@interrupt_
$LN7@interrupt_:

; 151  : 	for (int i = 0; i < 1; i++)

	mov	DWORD PTR i$2[rsp], 0
	jmp	SHORT $LN6@interrupt_
$LN5@interrupt_:
	mov	eax, DWORD PTR i$2[rsp]
	inc	eax
	mov	DWORD PTR i$2[rsp], eax
$LN6@interrupt_:
	cmp	DWORD PTR i$2[rsp], 1
	jge	SHORT $LN4@interrupt_

; 152  : 	{
; 153  : 		uint8_t bos[1024];
; 154  : 		m_ist[i] = bos + 1024;

	lea	rax, QWORD PTR bos$4[rsp+1024]
	movsxd	rcx, DWORD PTR i$2[rsp]
	mov	QWORD PTR m_ist$[rsp+rcx*8], rax

; 155  : 		tss[9+i*2] = reinterpret_cast<uint64_t>(m_ist[i]) & 0xffffffff;

	movsxd	rax, DWORD PTR i$2[rsp]
	mov	ecx, -1					; ffffffffH
	mov	rax, QWORD PTR m_ist$[rsp+rax*8]
	and	rax, rcx
	mov	ecx, DWORD PTR i$2[rsp]
	lea	ecx, DWORD PTR [rcx+rcx+9]
	movsxd	rcx, ecx
	mov	DWORD PTR tss$[rsp+rcx*4], eax

; 156  : 		tss[9+i*2+1] = reinterpret_cast<uint64_t>(m_ist[i]) >> 32;

	movsxd	rax, DWORD PTR i$2[rsp]
	mov	rax, QWORD PTR m_ist$[rsp+rax*8]
	shr	rax, 32					; 00000020H
	mov	ecx, DWORD PTR i$2[rsp]
	lea	ecx, DWORD PTR [rcx+rcx+10]
	movsxd	rcx, ecx
	mov	DWORD PTR tss$[rsp+rcx*4], eax

; 157  : 	}

	jmp	SHORT $LN5@interrupt_
$LN4@interrupt_:

; 158  : 	gdtr curr_gdt;
; 159  : 	x64_sgdt(&curr_gdt);

	lea	rcx, QWORD PTR curr_gdt$[rsp]
	call	x64_sgdt

; 160  : 	gdt_entry* thegdt = the_gdtr.gdtaddr; //curr_gdt.gdtaddr;

	mov	rax, QWORD PTR the_gdtr+2
	mov	QWORD PTR thegdt$[rsp], rax

; 161  : 	set_gdt_entry(thegdt[GDT_ENTRY_TSS], reinterpret_cast<uint64_t>(tss) & UINT32_MAX, sizeof(tss), GDT_ACCESS_PRESENT | 0x9, 0);

	lea	rax, QWORD PTR tss$[rsp]
	mov	ecx, -1					; ffffffffH
	and	rax, rcx
	mov	ecx, 8
	imul	rcx, 7
	mov	rdx, QWORD PTR thegdt$[rsp]
	add	rdx, rcx
	mov	rcx, rdx
	mov	BYTE PTR [rsp+32], 0
	mov	r9b, 137				; 00000089H
	mov	r8d, 112				; 00000070H
	mov	rdx, rax
	call	?set_gdt_entry@@YAXAEAU_gdt@@_K1EE@Z	; set_gdt_entry

; 162  : 	*(uint64_t*)&thegdt[GDT_ENTRY_TSS + 1] = (reinterpret_cast<uint64_t>(tss) >> 32);

	lea	rax, QWORD PTR tss$[rsp]
	shr	rax, 32					; 00000020H
	mov	ecx, 8
	imul	rcx, 8
	mov	rdx, QWORD PTR thegdt$[rsp]
	mov	QWORD PTR [rdx+rcx], rax

; 163  : 	x64_ltr(SEGVAL(GDT_ENTRY_TSS, 0));

	mov	cx, 56					; 00000038H
	call	x64_ltr

; 164  : 
; 165  : 
; 166  : 	IDTR *idtr = (IDTR*)0xFFFFD80000000000;

	mov	rax, -43980465111040			; ffffd80000000000H
	mov	QWORD PTR idtr$[rsp], rax

; 167  : 	idtr->idtaddr = the_idt;

	mov	rax, QWORD PTR idtr$[rsp]
	lea	rcx, OFFSET FLAT:the_idt
	mov	QWORD PTR [rax+2], rcx

; 168  : 	idtr->length = 256 * sizeof(IDT) - 1;

	mov	eax, 4095				; 00000fffH
	mov	rcx, QWORD PTR idtr$[rsp]
	mov	WORD PTR [rcx], ax

; 169  : 	x64_lidt(idtr);

	mov	rcx, QWORD PTR idtr$[rsp]
	call	x64_lidt

; 170  : 	for (int n = 0; n < 256; n++)

	mov	DWORD PTR n$1[rsp], 0
	jmp	SHORT $LN3@interrupt_
$LN2@interrupt_:
	mov	eax, DWORD PTR n$1[rsp]
	inc	eax
	mov	DWORD PTR n$1[rsp], eax
$LN3@interrupt_:
	cmp	DWORD PTR n$1[rsp], 256			; 00000100H
	jge	$LN1@interrupt_

; 171  : 	{
; 172  : 		the_idt[n].ist = 0;

	movsxd	rax, DWORD PTR n$1[rsp]
	imul	rax, 16
	lea	rcx, OFFSET FLAT:the_idt
	mov	BYTE PTR [rcx+rax+4], 0

; 173  : 		the_idt[n].selector = SEGVAL(GDT_ENTRY_KERNEL_CODE, 0);

	movsxd	rax, DWORD PTR n$1[rsp]
	imul	rax, 16
	lea	rcx, OFFSET FLAT:the_idt
	mov	edx, 8
	mov	WORD PTR [rcx+rax+2], dx

; 174  : 		the_idt[n].zero = 0;

	movsxd	rax, DWORD PTR n$1[rsp]
	imul	rax, 16
	lea	rcx, OFFSET FLAT:the_idt
	mov	DWORD PTR [rcx+rax+12], 0

; 175  : 		the_idt[n].type_attr = GDT_ACCESS_PRESENT | 0xE;

	movsxd	rax, DWORD PTR n$1[rsp]
	imul	rax, 16
	lea	rcx, OFFSET FLAT:the_idt
	mov	BYTE PTR [rcx+rax+5], 142		; 0000008eH

; 176  : 		register_irq(&the_idt[n], default_irq_handlers[n]);

	movsxd	rax, DWORD PTR n$1[rsp]
	lea	rcx, OFFSET FLAT:default_irq_handlers
	movsxd	rdx, DWORD PTR n$1[rsp]
	imul	rdx, 16
	lea	r8, OFFSET FLAT:the_idt
	add	r8, rdx
	mov	rdx, r8
	mov	QWORD PTR tv168[rsp], rdx
	mov	rdx, QWORD PTR [rcx+rax*8]
	mov	rax, QWORD PTR tv168[rsp]
	mov	rcx, rax
	call	?register_irq@@YAXPEAU_idt@@PEAX@Z	; register_irq

; 177  : 	}

	jmp	$LN2@interrupt_
$LN1@interrupt_:

; 178  : }

	add	rsp, 1304				; 00000518H
	ret	0
?interrupt_initialize@@YAXXZ ENDP			; interrupt_initialize
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\cpu.cpp
_TEXT	SEGMENT
gdt_initialize PROC

; 99   : {

$LN3:
	sub	rsp, 40					; 00000028H

; 100  : 	x64_sgdt(&old_gdtr);

	lea	rcx, OFFSET FLAT:old_gdtr
	call	x64_sgdt

; 101  : 	save_sregs();

	call	?save_sregs@@YAXXZ			; save_sregs

; 102  : 	fill_gdt(gdt);

	lea	rcx, OFFSET FLAT:gdt
	call	?fill_gdt@@YAXPEAU_gdt@@@Z		; fill_gdt

; 103  : 	the_gdtr.gdtaddr = gdt;

	lea	rax, OFFSET FLAT:gdt
	mov	QWORD PTR the_gdtr+2, rax

; 104  : 	the_gdtr.size = GDT_ENTRIES * sizeof(gdt_entry) - 1;

	mov	eax, 71					; 00000047H
	mov	WORD PTR the_gdtr, ax

; 105  : 	x64_lgdt(&the_gdtr);

	lea	rcx, OFFSET FLAT:the_gdtr
	call	x64_lgdt

; 106  : 	load_default_sregs();

	call	load_default_sregs

; 107  : }

	add	rsp, 40					; 00000028H
	ret	0
gdt_initialize ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\cpu.cpp
_TEXT	SEGMENT
vector$ = 8
function$ = 16
?setvect@@YAX_KP6AX0PEAX@Z@Z PROC			; setvect

; 126  : {

	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx

; 127  : 	interrupts_handlers[vector] = function;

	lea	rax, OFFSET FLAT:interrupts_handlers
	mov	rcx, QWORD PTR vector$[rsp]
	mov	rdx, QWORD PTR function$[rsp]
	mov	QWORD PTR [rax+rcx*8], rdx

; 128  : };

	ret	0
?setvect@@YAX_KP6AX0PEAX@Z@Z ENDP			; setvect
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\cpu.cpp
_TEXT	SEGMENT
?hal_x86_64_init@@YAXXZ PROC				; hal_x86_64_init

; 181  : void hal_x86_64_init () {

$LN3:
	sub	rsp, 40					; 00000028H

; 182  : 	//! clear interrupts first
; 183  :     x64_cli ();

	call	x64_cli

; 184  : 
; 185  : 	////! initialize the global descriptor table
; 186  : 	gdt_initialize();

	call	gdt_initialize

; 187  : 
; 188  : 	x64_sti();

	call	x64_sti

; 189  : }

	add	rsp, 40					; 00000028H
	ret	0
?hal_x86_64_init@@YAXXZ ENDP				; hal_x86_64_init
_TEXT	ENDS
END
