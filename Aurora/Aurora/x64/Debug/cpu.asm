; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

CONST	SEGMENT
$SG3010	DB	'*** [x64_idt] x64_default_handler: Unhandled Exception *'
	DB	'** ', 0aH, 00H
CONST	ENDS
PUBLIC	?hal_x86_64_init@@YAXXZ				; hal_x86_64_init
PUBLIC	?setvect@@YAX_KP6AX0PEAX@Z@Z			; setvect
PUBLIC	load_default_sregs
PUBLIC	?set_gdt_entry@@YAXAEAU_gdt@@_K1EE@Z		; set_gdt_entry
PUBLIC	?save_sregs@@YAXXZ				; save_sregs
PUBLIC	gdt_initialize
PUBLIC	interrupt_dispatcher
PUBLIC	?default_irq@@YAX_KPEAX@Z			; default_irq
PUBLIC	?interrupt_initialize@@YAXXZ			; interrupt_initialize
EXTRN	?initialize_apic@@YAXXZ:PROC			; initialize_apic
EXTRN	x64_cli:PROC
EXTRN	x64_sti:PROC
EXTRN	x64_outportb:PROC
EXTRN	x64_read_msr:PROC
EXTRN	x64_write_msr:PROC
EXTRN	x64_lgdt:PROC
EXTRN	x64_sgdt:PROC
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
EXTRN	?exception_init@@YAXXZ:PROC			; exception_init
EXTRN	?initialize_syscall@@YAXXZ:PROC			; initialize_syscall
EXTRN	?initialize_user_land@@YAX_K@Z:PROC		; initialize_user_land
EXTRN	x64_get_segment_register:PROC
EXTRN	x64_set_segment_register:PROC
EXTRN	x64_ltr:PROC
EXTRN	x64_lidt:PROC
EXTRN	default_irq_handlers:BYTE
_BSS	SEGMENT
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
	DD	imagerel $LN3+193
	DD	imagerel $unwind$?hal_x86_64_init@@YAXXZ
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
$pdata$gdt_initialize DD imagerel $LN3
	DD	imagerel $LN3+81
	DD	imagerel $unwind$gdt_initialize
$pdata$?register_irq@@YAXPEAU_idt@@PEAX@Z DD imagerel ?register_irq@@YAXPEAU_idt@@PEAX@Z
	DD	imagerel ?register_irq@@YAXPEAU_idt@@PEAX@Z+93
	DD	imagerel $unwind$?register_irq@@YAXPEAU_idt@@PEAX@Z
$pdata$interrupt_dispatcher DD imagerel $LN3
	DD	imagerel $LN3+45
	DD	imagerel $unwind$interrupt_dispatcher
$pdata$?default_irq@@YAX_KPEAX@Z DD imagerel $LN5
	DD	imagerel $LN5+38
	DD	imagerel $unwind$?default_irq@@YAX_KPEAX@Z
$pdata$?interrupt_initialize@@YAXXZ DD imagerel $LN12
	DD	imagerel $LN12+535
	DD	imagerel $unwind$?interrupt_initialize@@YAXXZ
pdata	ENDS
xdata	SEGMENT
$unwind$?hal_x86_64_init@@YAXXZ DD 010401H
	DD	06204H
$unwind$load_default_sregs DD 010401H
	DD	04204H
$unwind$?set_gdt_entry@@YAXAEAU_gdt@@EE@Z DD 011201H
	DD	06212H
$unwind$?fill_gdt@@YAXPEAU_gdt@@@Z DD 010901H
	DD	06209H
$unwind$?save_sregs@@YAXXZ DD 010401H
	DD	06204H
$unwind$gdt_initialize DD 010401H
	DD	04204H
$unwind$?register_irq@@YAXPEAU_idt@@PEAX@Z DD 010e01H
	DD	0220eH
$unwind$interrupt_dispatcher DD 010e01H
	DD	0420eH
$unwind$?default_irq@@YAX_KPEAX@Z DD 010e01H
	DD	0420eH
$unwind$?interrupt_initialize@@YAXXZ DD 020701H
	DD	0a30107H
xdata	ENDS
; Function compile flags: /Odtp
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

; 140  : void  interrupt_initialize() {

$LN12:
	sub	rsp, 1304				; 00000518H

; 141  :  
; 142  : 
; 143  : 	void* m_ist[4];
; 144  : 	uint32_t tss[28];
; 145  : 	for (int i = 0; i < 28; i++) tss[i] = 0xffffffff;

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

; 146  : 	for (int i = 0; i < 1; i++)

	mov	DWORD PTR i$2[rsp], 0
	jmp	SHORT $LN6@interrupt_
$LN5@interrupt_:
	mov	eax, DWORD PTR i$2[rsp]
	inc	eax
	mov	DWORD PTR i$2[rsp], eax
$LN6@interrupt_:
	cmp	DWORD PTR i$2[rsp], 1
	jge	SHORT $LN4@interrupt_

; 147  : 	{
; 148  : 		uint8_t bos[1024];
; 149  : 		m_ist[i] = bos + 1024;

	lea	rax, QWORD PTR bos$4[rsp+1024]
	movsxd	rcx, DWORD PTR i$2[rsp]
	mov	QWORD PTR m_ist$[rsp+rcx*8], rax

; 150  : 		tss[9+i*2] = reinterpret_cast<uint64_t>(m_ist[i]) & 0xffffffff;

	movsxd	rax, DWORD PTR i$2[rsp]
	mov	ecx, -1					; ffffffffH
	mov	rax, QWORD PTR m_ist$[rsp+rax*8]
	and	rax, rcx
	mov	ecx, DWORD PTR i$2[rsp]
	lea	ecx, DWORD PTR [rcx+rcx+9]
	movsxd	rcx, ecx
	mov	DWORD PTR tss$[rsp+rcx*4], eax

; 151  : 		tss[9+i*2+1] = reinterpret_cast<uint64_t>(m_ist[i]) >> 32;

	movsxd	rax, DWORD PTR i$2[rsp]
	mov	rax, QWORD PTR m_ist$[rsp+rax*8]
	shr	rax, 32					; 00000020H
	mov	ecx, DWORD PTR i$2[rsp]
	lea	ecx, DWORD PTR [rcx+rcx+10]
	movsxd	rcx, ecx
	mov	DWORD PTR tss$[rsp+rcx*4], eax

; 152  : 	}

	jmp	SHORT $LN5@interrupt_
$LN4@interrupt_:

; 153  : 	gdtr curr_gdt;
; 154  : 	x64_sgdt(&curr_gdt);

	lea	rcx, QWORD PTR curr_gdt$[rsp]
	call	x64_sgdt

; 155  : 	gdt_entry* thegdt = the_gdtr.gdtaddr; //curr_gdt.gdtaddr;

	mov	rax, QWORD PTR the_gdtr+2
	mov	QWORD PTR thegdt$[rsp], rax

; 156  : 	set_gdt_entry(thegdt[GDT_ENTRY_TSS], reinterpret_cast<uint64_t>(tss) & UINT32_MAX, sizeof(tss), GDT_ACCESS_PRESENT | 0x9, 0);

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

; 157  : 	*(uint64_t*)&thegdt[GDT_ENTRY_TSS + 1] = (reinterpret_cast<uint64_t>(tss) >> 32);

	lea	rax, QWORD PTR tss$[rsp]
	shr	rax, 32					; 00000020H
	mov	ecx, 8
	imul	rcx, 8
	mov	rdx, QWORD PTR thegdt$[rsp]
	mov	QWORD PTR [rdx+rcx], rax

; 158  : 	x64_ltr(SEGVAL(GDT_ENTRY_TSS, 0));

	mov	cx, 56					; 00000038H
	call	x64_ltr

; 159  : 
; 160  : 
; 161  : 	IDTR *idtr = (IDTR*)0xFFFFD80000000000;

	mov	rax, -43980465111040			; ffffd80000000000H
	mov	QWORD PTR idtr$[rsp], rax

; 162  : 	idtr->idtaddr = the_idt;

	mov	rax, QWORD PTR idtr$[rsp]
	lea	rcx, OFFSET FLAT:the_idt
	mov	QWORD PTR [rax+2], rcx

; 163  : 	idtr->length = 256 * sizeof(IDT) - 1;

	mov	eax, 4095				; 00000fffH
	mov	rcx, QWORD PTR idtr$[rsp]
	mov	WORD PTR [rcx], ax

; 164  : 	x64_lidt(idtr);

	mov	rcx, QWORD PTR idtr$[rsp]
	call	x64_lidt

; 165  : 	for (int n = 0; n < 256; n++)

	mov	DWORD PTR n$1[rsp], 0
	jmp	SHORT $LN3@interrupt_
$LN2@interrupt_:
	mov	eax, DWORD PTR n$1[rsp]
	inc	eax
	mov	DWORD PTR n$1[rsp], eax
$LN3@interrupt_:
	cmp	DWORD PTR n$1[rsp], 256			; 00000100H
	jge	$LN1@interrupt_

; 166  : 	{
; 167  : 		the_idt[n].ist = 0;

	movsxd	rax, DWORD PTR n$1[rsp]
	imul	rax, 16
	lea	rcx, OFFSET FLAT:the_idt
	mov	BYTE PTR [rcx+rax+4], 0

; 168  : 		the_idt[n].selector = SEGVAL(GDT_ENTRY_KERNEL_CODE, 0);

	movsxd	rax, DWORD PTR n$1[rsp]
	imul	rax, 16
	lea	rcx, OFFSET FLAT:the_idt
	mov	edx, 8
	mov	WORD PTR [rcx+rax+2], dx

; 169  : 		the_idt[n].zero = 0;

	movsxd	rax, DWORD PTR n$1[rsp]
	imul	rax, 16
	lea	rcx, OFFSET FLAT:the_idt
	mov	DWORD PTR [rcx+rax+12], 0

; 170  : 		the_idt[n].type_attr = GDT_ACCESS_PRESENT | 0xE;

	movsxd	rax, DWORD PTR n$1[rsp]
	imul	rax, 16
	lea	rcx, OFFSET FLAT:the_idt
	mov	BYTE PTR [rcx+rax+5], 142		; 0000008eH

; 171  : 		register_irq(&the_idt[n], default_irq_handlers[n]);

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

; 172  : 	}

	jmp	$LN2@interrupt_
$LN1@interrupt_:

; 173  : }

	add	rsp, 1304				; 00000518H
	ret	0
?interrupt_initialize@@YAXXZ ENDP			; interrupt_initialize
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\cpu.cpp
_TEXT	SEGMENT
vect$ = 48
param$ = 56
?default_irq@@YAX_KPEAX@Z PROC				; default_irq

; 132  : void default_irq(size_t vect, void* param){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 133  : 	x64_cli();

	call	x64_cli

; 134  : 	printf("*** [x64_idt] x64_default_handler: Unhandled Exception *** \n");

	lea	rcx, OFFSET FLAT:$SG3010
	call	?printf@@YAXPEBDZZ			; printf
$LN2@default_ir:

; 135  : 	for(;;);

	jmp	SHORT $LN2@default_ir

; 136  : }

	add	rsp, 40					; 00000028H
	ret	0
?default_irq@@YAX_KPEAX@Z ENDP				; default_irq
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\cpu.cpp
_TEXT	SEGMENT
num$ = 48
frame$ = 56
interrupt_dispatcher PROC

; 126  : {	

$LN3:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 127  : 	interrupts_handlers[num](num, frame);

	lea	rax, OFFSET FLAT:interrupts_handlers
	mov	rdx, QWORD PTR frame$[rsp]
	mov	rcx, QWORD PTR num$[rsp]
	mov	r8, QWORD PTR num$[rsp]
	call	QWORD PTR [rax+r8*8]

; 128  : 	return;
; 129  : }

	add	rsp, 40					; 00000028H
	ret	0
interrupt_dispatcher ENDP
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\cpu.cpp
_TEXT	SEGMENT
faddr$ = 0
entry$ = 32
function$ = 40
?register_irq@@YAXPEAU_idt@@PEAX@Z PROC			; register_irq

; 113  : {

	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 24

; 114  : 	size_t faddr = (size_t)function;

	mov	rax, QWORD PTR function$[rsp]
	mov	QWORD PTR faddr$[rsp], rax

; 115  : 	entry->offset_1 = faddr & UINT16_MAX;

	mov	rax, QWORD PTR faddr$[rsp]
	and	rax, 65535				; 0000ffffH
	mov	rcx, QWORD PTR entry$[rsp]
	mov	WORD PTR [rcx], ax

; 116  : 	entry->offset_2 = (faddr >> 16) & UINT16_MAX;

	mov	rax, QWORD PTR faddr$[rsp]
	shr	rax, 16
	and	rax, 65535				; 0000ffffH
	mov	rcx, QWORD PTR entry$[rsp]
	mov	WORD PTR [rcx+6], ax

; 117  : 	entry->offset_3 = (faddr >> 32) & UINT32_MAX;

	mov	rax, QWORD PTR faddr$[rsp]
	shr	rax, 32					; 00000020H
	mov	ecx, -1					; ffffffffH
	and	rax, rcx
	mov	rcx, QWORD PTR entry$[rsp]
	mov	DWORD PTR [rcx+8], eax

; 118  : }

	add	rsp, 24
	ret	0
?register_irq@@YAXPEAU_idt@@PEAX@Z ENDP			; register_irq
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\cpu.cpp
_TEXT	SEGMENT
gdt_initialize PROC

; 94   : {

$LN3:
	sub	rsp, 40					; 00000028H

; 95   : 	x64_sgdt(&old_gdtr);

	lea	rcx, OFFSET FLAT:old_gdtr
	call	x64_sgdt

; 96   : 	save_sregs();

	call	?save_sregs@@YAXXZ			; save_sregs

; 97   : 	fill_gdt(gdt);

	lea	rcx, OFFSET FLAT:gdt
	call	?fill_gdt@@YAXPEAU_gdt@@@Z		; fill_gdt

; 98   : 	the_gdtr.gdtaddr = gdt;

	lea	rax, OFFSET FLAT:gdt
	mov	QWORD PTR the_gdtr+2, rax

; 99   : 	the_gdtr.size = GDT_ENTRIES * sizeof(gdt_entry) - 1;

	mov	eax, 71					; 00000047H
	mov	WORD PTR the_gdtr, ax

; 100  : 	x64_lgdt(&the_gdtr);

	lea	rcx, OFFSET FLAT:the_gdtr
	call	x64_lgdt

; 101  : 	load_default_sregs();

	call	load_default_sregs

; 102  : }

	add	rsp, 40					; 00000028H
	ret	0
gdt_initialize ENDP
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\cpu.cpp
_TEXT	SEGMENT
reg$1 = 32
?save_sregs@@YAXXZ PROC					; save_sregs

; 76   : {

$LN6:
	sub	rsp, 56					; 00000038H

; 77   : 	for (uint_fast8_t reg = 0; reg < 8; ++reg)

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

; 78   : 		oldsregs[reg] = x64_get_segment_register(reg);

	movzx	eax, BYTE PTR reg$1[rsp]
	mov	ecx, eax
	call	x64_get_segment_register
	movzx	ecx, BYTE PTR reg$1[rsp]
	lea	rdx, OFFSET FLAT:oldsregs
	mov	WORD PTR [rdx+rcx*2], ax
	jmp	SHORT $LN2@save_sregs
$LN1@save_sregs:

; 79   : }

	add	rsp, 56					; 00000038H
	ret	0
?save_sregs@@YAXXZ ENDP					; save_sregs
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\cpu.cpp
_TEXT	SEGMENT
thegdt$ = 64
?fill_gdt@@YAXPEAU_gdt@@@Z PROC				; fill_gdt

; 59   : {

	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 60   : 	set_gdt_entry(thegdt[GDT_ENTRY_NULL], 0, 0, 0, 0);    //0x00

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

; 61   : 	//Kernel Code segment: STAR.SYSCALL_CS
; 62   : 	set_gdt_entry(thegdt[GDT_ENTRY_KERNEL_CODE], GDT_ACCESS_PRIVL(0) | GDT_ACCESS_RW | GDT_ACCESS_EX, GDT_FLAG_64BT);  //0x08

	mov	eax, 8
	imul	rax, 1
	mov	rcx, QWORD PTR thegdt$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	r8b, 2
	mov	dl, 10
	mov	rcx, rax
	call	?set_gdt_entry@@YAXAEAU_gdt@@EE@Z	; set_gdt_entry

; 63   : 	//Kernel Data segment
; 64   : 	set_gdt_entry(thegdt[GDT_ENTRY_KERNEL_DATA], GDT_ACCESS_PRIVL(0) | GDT_ACCESS_RW, GDT_FLAG_32BT);    //0x10

	mov	eax, 8
	imul	rax, 2
	mov	rcx, QWORD PTR thegdt$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	r8b, 4
	mov	dl, 2
	mov	rcx, rax
	call	?set_gdt_entry@@YAXAEAU_gdt@@EE@Z	; set_gdt_entry

; 65   : 	//User Code segment (32 bit): STAR.SYSRET_CS
; 66   : 	set_gdt_entry(thegdt[GDT_ENTRY_USER_CODE32], GDT_ACCESS_PRIVL(3) | GDT_ACCESS_RW | GDT_ACCESS_EX, GDT_FLAG_32BT);  //0x18

	mov	eax, 8
	imul	rax, 3
	mov	rcx, QWORD PTR thegdt$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	r8b, 4
	mov	dl, 106					; 0000006aH
	mov	rcx, rax
	call	?set_gdt_entry@@YAXAEAU_gdt@@EE@Z	; set_gdt_entry

; 67   : 	//User Data segment
; 68   : 	set_gdt_entry(thegdt[GDT_ENTRY_USER_DATA], GDT_ACCESS_PRIVL(3) | GDT_ACCESS_RW, GDT_FLAG_32BT);    //0x20

	mov	eax, 8
	imul	rax, 4
	mov	rcx, QWORD PTR thegdt$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	r8b, 4
	mov	dl, 98					; 00000062H
	mov	rcx, rax
	call	?set_gdt_entry@@YAXAEAU_gdt@@EE@Z	; set_gdt_entry

; 69   : 	//User Code segment (64 bit)
; 70   : 	set_gdt_entry(thegdt[GDT_ENTRY_USER_CODE], GDT_ACCESS_PRIVL(3) | GDT_ACCESS_RW | GDT_ACCESS_EX, GDT_FLAG_64BT);   //0x28  | 3 -- 0x2B

	mov	eax, 8
	imul	rax, 5
	mov	rcx, QWORD PTR thegdt$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	r8b, 2
	mov	dl, 106					; 0000006aH
	mov	rcx, rax
	call	?set_gdt_entry@@YAXAEAU_gdt@@EE@Z	; set_gdt_entry

; 71   : 	//Kernel Code segment (32 bit)
; 72   : 	set_gdt_entry(thegdt[GDT_ENTRY_KERNEL_CODE32], GDT_ACCESS_PRIVL(3) | GDT_ACCESS_RW | GDT_ACCESS_EX , GDT_FLAG_32BT);  //0x30

	mov	eax, 8
	imul	rax, 6
	mov	rcx, QWORD PTR thegdt$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	r8b, 4
	mov	dl, 106					; 0000006aH
	mov	rcx, rax
	call	?set_gdt_entry@@YAXAEAU_gdt@@EE@Z	; set_gdt_entry

; 73   : }

	add	rsp, 56					; 00000038H
	ret	0
?fill_gdt@@YAXPEAU_gdt@@@Z ENDP				; fill_gdt
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\cpu.cpp
_TEXT	SEGMENT
entry$ = 64
access$ = 72
flags$ = 80
?set_gdt_entry@@YAXAEAU_gdt@@EE@Z PROC			; set_gdt_entry

; 52   : {

	mov	BYTE PTR [rsp+24], r8b
	mov	BYTE PTR [rsp+16], dl
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 53   : 	access |= GDT_ACCESS_PRESENT | GDT_ACCESS_TYPE;

	movzx	eax, BYTE PTR access$[rsp]
	or	eax, 144				; 00000090H
	mov	BYTE PTR access$[rsp], al

; 54   : 	flags |= GDT_FLAG_GRAN;

	movzx	eax, BYTE PTR flags$[rsp]
	or	eax, 8
	mov	BYTE PTR flags$[rsp], al

; 55   : 	set_gdt_entry(entry, 0, SIZE_MAX, access, flags);

	movzx	eax, BYTE PTR flags$[rsp]
	mov	BYTE PTR [rsp+32], al
	movzx	r9d, BYTE PTR access$[rsp]
	mov	r8d, 1048575				; 000fffffH
	xor	edx, edx
	mov	rcx, QWORD PTR entry$[rsp]
	call	?set_gdt_entry@@YAXAEAU_gdt@@_K1EE@Z	; set_gdt_entry

; 56   : }

	add	rsp, 56					; 00000038H
	ret	0
?set_gdt_entry@@YAXAEAU_gdt@@EE@Z ENDP			; set_gdt_entry
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\cpu.cpp
_TEXT	SEGMENT
entry$ = 8
base$ = 16
limit$ = 24
access$ = 32
flags$ = 40
?set_gdt_entry@@YAXAEAU_gdt@@_K1EE@Z PROC		; set_gdt_entry

; 42   : {

	mov	BYTE PTR [rsp+32], r9b
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx

; 43   : 	entry.base_low = base & 0xFFFF;

	mov	rax, QWORD PTR base$[rsp]
	and	rax, 65535				; 0000ffffH
	mov	rcx, QWORD PTR entry$[rsp]
	mov	WORD PTR [rcx+2], ax

; 44   : 	entry.base_mid = (base >> 16) & 0xFF;

	mov	rax, QWORD PTR base$[rsp]
	shr	rax, 16
	and	rax, 255				; 000000ffH
	mov	rcx, QWORD PTR entry$[rsp]
	mov	BYTE PTR [rcx+4], al

; 45   : 	entry.base_high = (base >> 24) & 0xFF;

	mov	rax, QWORD PTR base$[rsp]
	shr	rax, 24
	and	rax, 255				; 000000ffH
	mov	rcx, QWORD PTR entry$[rsp]
	mov	BYTE PTR [rcx+7], al

; 46   : 	entry.limit_low = limit & 0xFFFF;

	mov	rax, QWORD PTR limit$[rsp]
	and	rax, 65535				; 0000ffffH
	mov	rcx, QWORD PTR entry$[rsp]
	mov	WORD PTR [rcx], ax

; 47   : 	entry.access = access;

	mov	rax, QWORD PTR entry$[rsp]
	movzx	ecx, BYTE PTR access$[rsp]
	mov	BYTE PTR [rax+5], cl

; 48   : 	entry.flags_limit = (flags << 4) | ((limit >> 16) & 0xF);

	movzx	eax, BYTE PTR flags$[rsp]
	shl	eax, 4
	cdqe
	mov	rcx, QWORD PTR limit$[rsp]
	shr	rcx, 16
	and	rcx, 15
	or	rax, rcx
	mov	rcx, QWORD PTR entry$[rsp]
	mov	BYTE PTR [rcx+6], al

; 49   : }

	ret	0
?set_gdt_entry@@YAXAEAU_gdt@@_K1EE@Z ENDP		; set_gdt_entry
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\cpu.cpp
_TEXT	SEGMENT
load_default_sregs PROC

; 82   : {

$LN3:
	sub	rsp, 40					; 00000028H

; 83   : 	x64_set_segment_register(SREG_CS, SEGVAL(GDT_ENTRY_KERNEL_CODE, 0));		

	mov	dx, 8
	xor	ecx, ecx
	call	x64_set_segment_register

; 84   : 	x64_set_segment_register(SREG_DS, SEGVAL(GDT_ENTRY_KERNEL_DATA, 0));

	mov	dx, 16
	mov	ecx, 1
	call	x64_set_segment_register

; 85   : 	x64_set_segment_register(SREG_ES, SEGVAL(GDT_ENTRY_KERNEL_DATA, 0));

	mov	dx, 16
	mov	ecx, 2
	call	x64_set_segment_register

; 86   : 	x64_set_segment_register(SREG_SS, SEGVAL(GDT_ENTRY_KERNEL_DATA, 0));

	mov	dx, 16
	mov	ecx, 5
	call	x64_set_segment_register

; 87   : 	//Per CPU data
; 88   : 	x64_set_segment_register(SREG_FS, SEGVAL(GDT_ENTRY_KERNEL_DATA, 0));

	mov	dx, 16
	mov	ecx, 3
	call	x64_set_segment_register

; 89   : 	x64_set_segment_register(SREG_GS, SEGVAL(GDT_ENTRY_KERNEL_DATA, 0));

	mov	dx, 16
	mov	ecx, 4
	call	x64_set_segment_register

; 90   : }

	add	rsp, 40					; 00000028H
	ret	0
load_default_sregs ENDP
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\cpu.cpp
_TEXT	SEGMENT
vector$ = 8
function$ = 16
?setvect@@YAX_KP6AX0PEAX@Z@Z PROC			; setvect

; 121  : {

	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx

; 122  : 	interrupts_handlers[vector] = function;

	lea	rax, OFFSET FLAT:interrupts_handlers
	mov	rcx, QWORD PTR vector$[rsp]
	mov	rdx, QWORD PTR function$[rsp]
	mov	QWORD PTR [rax+rcx*8], rdx

; 123  : };

	ret	0
?setvect@@YAX_KP6AX0PEAX@Z@Z ENDP			; setvect
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\cpu.cpp
_TEXT	SEGMENT
divisor$ = 32
efer$ = 40
?hal_x86_64_init@@YAXXZ PROC				; hal_x86_64_init

; 176  : void hal_x86_64_init () {

$LN3:
	sub	rsp, 56					; 00000038H

; 177  : 	//! clear interrupts first
; 178  :     x64_cli ();

	call	x64_cli

; 179  : 
; 180  : 	//! initialize the global descriptor table
; 181  : 	gdt_initialize();

	call	gdt_initialize

; 182  : 
; 183  : 	//! initialize the interrupt descriptor table
; 184  : 	interrupt_initialize();

	call	?interrupt_initialize@@YAXXZ		; interrupt_initialize

; 185  : 
; 186  : 	//! initialize all exception handlers
; 187  : 	exception_init ();

	call	?exception_init@@YAXXZ			; exception_init

; 188  : 
; 189  : #ifdef USE_PIC
; 190  : 	initialize_pic(0x20, 0x28);
; 191  : #endif
; 192  : 
; 193  : #ifdef USE_APIC
; 194  : 	//!Initialize APIC
; 195  : 	initialize_apic ();

	call	?initialize_apic@@YAXXZ			; initialize_apic

; 196  : 
; 197  : 	unsigned int divisor =  1193181 / 100;

	mov	DWORD PTR divisor$[rsp], 11931		; 00002e9bH

; 198  : 	x64_outportb(0x43, 0x00 | 0x06 | 0x30 | 0x00);

	mov	dl, 54					; 00000036H
	mov	cx, 67					; 00000043H
	call	x64_outportb

; 199  : 	x64_outportb(0x40, divisor);

	movzx	edx, BYTE PTR divisor$[rsp]
	mov	cx, 64					; 00000040H
	call	x64_outportb

; 200  : 	x64_outportb(0x40, divisor >> 8);

	mov	eax, DWORD PTR divisor$[rsp]
	shr	eax, 8
	movzx	edx, al
	mov	cx, 64					; 00000040H
	call	x64_outportb

; 201  : #endif
; 202  : 
; 203  : 	//!Enable EFER and SYSCALL Extension
; 204  : 	size_t efer = x64_read_msr(IA32_EFER);

	mov	ecx, -1073741696			; c0000080H
	call	x64_read_msr
	mov	QWORD PTR efer$[rsp], rax

; 205  : 	efer |= (1<<11);

	mov	rax, QWORD PTR efer$[rsp]
	bts	rax, 11
	mov	QWORD PTR efer$[rsp], rax

; 206  : 	efer |= 1;

	mov	rax, QWORD PTR efer$[rsp]
	or	rax, 1
	mov	QWORD PTR efer$[rsp], rax

; 207  : 	efer |= (1<<0);

	mov	rax, QWORD PTR efer$[rsp]
	or	rax, 1
	mov	QWORD PTR efer$[rsp], rax

; 208  : 	efer |= 1;

	mov	rax, QWORD PTR efer$[rsp]
	or	rax, 1
	mov	QWORD PTR efer$[rsp], rax

; 209  : 	x64_write_msr(IA32_EFER, efer);

	mov	rdx, QWORD PTR efer$[rsp]
	mov	ecx, -1073741696			; c0000080H
	call	x64_write_msr

; 210  : 	//! now start the interrupts
; 211  : 
; 212  : 	//! initialize the user land environment
; 213  : 	initialize_user_land (64);

	mov	ecx, 64					; 00000040H
	call	?initialize_user_land@@YAX_K@Z		; initialize_user_land

; 214  : 
; 215  : 	//! initialize the syscall entries
; 216  : 	initialize_syscall ();

	call	?initialize_syscall@@YAXXZ		; initialize_syscall

; 217  : 	x64_sti ();

	call	x64_sti

; 218  : }

	add	rsp, 56					; 00000038H
	ret	0
?hal_x86_64_init@@YAXXZ ENDP				; hal_x86_64_init
_TEXT	ENDS
END
