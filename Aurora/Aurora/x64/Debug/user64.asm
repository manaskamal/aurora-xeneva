; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?tss@@3PEAU_tss@@EA				; tss
_BSS	SEGMENT
?tss@@3PEAU_tss@@EA DQ 01H DUP (?)			; tss
_BSS	ENDS
CONST	SEGMENT
$SG3453	DB	'Syscalled occured', 0aH, 00H
	ORG $+5
$SG3454	DB	'Loaded kernel stack is %x', 0aH, 00H
CONST	ENDS
PUBLIC	?initialize_syscall@@YAXXZ			; initialize_syscall
PUBLIC	?initialize_user_land@@YAX_K@Z			; initialize_user_land
PUBLIC	?initialize_user_land_ap@@YAX_K@Z		; initialize_user_land_ap
PUBLIC	get_kernel_tss
PUBLIC	syscall_debug
EXTRN	printf:PROC
EXTRN	x64_write_msr:PROC
EXTRN	x64_sgdt:PROC
EXTRN	syscall_entry:PROC
EXTRN	x64_syscall_entry_compat:PROC
pdata	SEGMENT
$pdata$?initialize_syscall@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+110
	DD	imagerel $unwind$?initialize_syscall@@YAXXZ
$pdata$?initialize_user_land@@YAX_K@Z DD imagerel $LN8
	DD	imagerel $LN8+190
	DD	imagerel $unwind$?initialize_user_land@@YAX_K@Z
$pdata$?initialize_user_land_ap@@YAX_K@Z DD imagerel $LN8
	DD	imagerel $LN8+188
	DD	imagerel $unwind$?initialize_user_land_ap@@YAX_K@Z
$pdata$syscall_debug DD imagerel $LN3
	DD	imagerel $LN3+43
	DD	imagerel $unwind$syscall_debug
pdata	ENDS
xdata	SEGMENT
$unwind$?initialize_syscall@@YAXXZ DD 010401H
	DD	06204H
$unwind$?initialize_user_land@@YAX_K@Z DD 010901H
	DD	0a209H
$unwind$?initialize_user_land_ap@@YAX_K@Z DD 010901H
	DD	0a209H
$unwind$syscall_debug DD 010901H
	DD	04209H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\user64.cpp
_TEXT	SEGMENT
rcx$ = 48
syscall_debug PROC

; 89   : extern "C" void syscall_debug  (uint64_t rcx) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 90   : 	printf ("Syscalled occured\n");

	lea	rcx, OFFSET FLAT:$SG3453
	call	printf

; 91   : 	printf ("Loaded kernel stack is %x\n", rcx);

	mov	rdx, QWORD PTR rcx$[rsp]
	lea	rcx, OFFSET FLAT:$SG3454
	call	printf

; 92   : 	//for(;;);
; 93   : }

	add	rsp, 40					; 00000028H
	ret	0
syscall_debug ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\user64.cpp
_TEXT	SEGMENT
get_kernel_tss PROC

; 85   : 	return tss;

	mov	rax, QWORD PTR ?tss@@3PEAU_tss@@EA	; tss

; 86   : }

	ret	0
get_kernel_tss ENDP
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\user64.cpp
_TEXT	SEGMENT
code_sel$ = 32
data_sel$ = 36
tss_entry$ = 40
tv64 = 48
tss_$ = 56
peek_gdt$ = 64
bit$ = 96
?initialize_user_land_ap@@YAX_K@Z PROC			; initialize_user_land_ap

; 59   : void initialize_user_land_ap (size_t bit) {

$LN8:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 88					; 00000058H

; 60   : 
; 61   : 	uint16_t data_sel = SEGVAL (GDT_ENTRY_USER_DATA, 3);

	mov	eax, 35					; 00000023H
	mov	WORD PTR data_sel$[rsp], ax

; 62   : 	uint16_t code_sel = 0;

	xor	eax, eax
	mov	WORD PTR code_sel$[rsp], ax

; 63   : 	switch (bit) {

	mov	rax, QWORD PTR bit$[rsp]
	mov	QWORD PTR tv64[rsp], rax
	cmp	QWORD PTR tv64[rsp], 32			; 00000020H
	je	SHORT $LN2@initialize
	cmp	QWORD PTR tv64[rsp], 64			; 00000040H
	je	SHORT $LN3@initialize
	jmp	SHORT $LN1@initialize
$LN3@initialize:

; 64   : 	case 64:
; 65   : 		code_sel = SEGVAL (GDT_ENTRY_USER_CODE, 3);

	mov	eax, 43					; 0000002bH
	mov	WORD PTR code_sel$[rsp], ax

; 66   : 		break;

	jmp	SHORT $LN4@initialize
$LN2@initialize:

; 67   : 	case 32:
; 68   : 		code_sel = SEGVAL (GDT_ENTRY_USER_CODE32, 3);

	mov	eax, 27
	mov	WORD PTR code_sel$[rsp], ax

; 69   : 		break;

	jmp	SHORT $LN4@initialize
$LN1@initialize:

; 70   : 	default:
; 71   : 		return;

	jmp	SHORT $LN6@initialize
$LN4@initialize:

; 72   : 	}
; 73   : 
; 74   : 	gdtr peek_gdt;
; 75   : 	x64_sgdt (&peek_gdt);

	lea	rcx, QWORD PTR peek_gdt$[rsp]
	call	x64_sgdt

; 76   : 	gdt_entry& tss_entry = peek_gdt.gdtaddr[GDT_ENTRY_TSS];

	mov	eax, 8
	imul	rax, 7
	mov	rcx, QWORD PTR peek_gdt$[rsp+2]
	add	rcx, rax
	mov	rax, rcx
	mov	QWORD PTR tss_entry$[rsp], rax

; 77   : 
; 78   : 	TSS *tss_ = (TSS*) (tss_entry.base_low + (tss_entry.base_mid << 16) + (tss_entry.base_high << 24) + ((uint64_t)*(uint32_t*)&peek_gdt.gdtaddr[GDT_ENTRY_TSS + 1] << 32));

	mov	rax, QWORD PTR tss_entry$[rsp]
	movzx	eax, WORD PTR [rax+2]
	mov	rcx, QWORD PTR tss_entry$[rsp]
	movzx	ecx, BYTE PTR [rcx+4]
	shl	ecx, 16
	add	eax, ecx
	mov	rcx, QWORD PTR tss_entry$[rsp]
	movzx	ecx, BYTE PTR [rcx+7]
	shl	ecx, 24
	add	eax, ecx
	cdqe
	mov	ecx, 8
	imul	rcx, 8
	mov	rdx, QWORD PTR peek_gdt$[rsp+2]
	mov	ecx, DWORD PTR [rdx+rcx]
	shl	rcx, 32					; 00000020H
	add	rax, rcx
	mov	QWORD PTR tss_$[rsp], rax
$LN6@initialize:

; 79   : 	
; 80   : 	/*void* esp_stack = x64_get_stack();
; 81   : 	x64_write_msr (IA32_SYSENTER_ESP, (size_t)esp_stack); */
; 82   : }

	add	rsp, 88					; 00000058H
	ret	0
?initialize_user_land_ap@@YAX_K@Z ENDP			; initialize_user_land_ap
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\user64.cpp
_TEXT	SEGMENT
code_sel$ = 32
data_sel$ = 36
tss_entry$ = 40
tv64 = 48
peek_gdt$ = 56
bit$ = 96
?initialize_user_land@@YAX_K@Z PROC			; initialize_user_land

; 33   : void initialize_user_land (size_t bit) {

$LN8:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 88					; 00000058H

; 34   : 
; 35   : 	uint16_t data_sel = SEGVAL (GDT_ENTRY_USER_DATA, 3);

	mov	eax, 35					; 00000023H
	mov	WORD PTR data_sel$[rsp], ax

; 36   : 	uint16_t code_sel = 0;

	xor	eax, eax
	mov	WORD PTR code_sel$[rsp], ax

; 37   : 	switch (bit) {

	mov	rax, QWORD PTR bit$[rsp]
	mov	QWORD PTR tv64[rsp], rax
	cmp	QWORD PTR tv64[rsp], 32			; 00000020H
	je	SHORT $LN2@initialize
	cmp	QWORD PTR tv64[rsp], 64			; 00000040H
	je	SHORT $LN3@initialize
	jmp	SHORT $LN1@initialize
$LN3@initialize:

; 38   : 	case 64:
; 39   : 		code_sel = SEGVAL (GDT_ENTRY_USER_CODE, 3);

	mov	eax, 43					; 0000002bH
	mov	WORD PTR code_sel$[rsp], ax

; 40   : 		break;

	jmp	SHORT $LN4@initialize
$LN2@initialize:

; 41   : 	case 32:
; 42   : 		code_sel = SEGVAL (GDT_ENTRY_USER_CODE32, 3);

	mov	eax, 27
	mov	WORD PTR code_sel$[rsp], ax

; 43   : 		break;

	jmp	SHORT $LN4@initialize
$LN1@initialize:

; 44   : 	default:
; 45   : 		return;

	jmp	SHORT $LN6@initialize
$LN4@initialize:

; 46   : 	}
; 47   : 
; 48   : 	gdtr peek_gdt;
; 49   : 	x64_sgdt (&peek_gdt);

	lea	rcx, QWORD PTR peek_gdt$[rsp]
	call	x64_sgdt

; 50   : 	gdt_entry& tss_entry = peek_gdt.gdtaddr[GDT_ENTRY_TSS];

	mov	eax, 8
	imul	rax, 7
	mov	rcx, QWORD PTR peek_gdt$[rsp+2]
	add	rcx, rax
	mov	rax, rcx
	mov	QWORD PTR tss_entry$[rsp], rax

; 51   : 
; 52   : 	tss = (TSS*) (tss_entry.base_low + (tss_entry.base_mid << 16) + (tss_entry.base_high << 24) + ((uint64_t)*(uint32_t*)&peek_gdt.gdtaddr[GDT_ENTRY_TSS + 1] << 32));

	mov	rax, QWORD PTR tss_entry$[rsp]
	movzx	eax, WORD PTR [rax+2]
	mov	rcx, QWORD PTR tss_entry$[rsp]
	movzx	ecx, BYTE PTR [rcx+4]
	shl	ecx, 16
	add	eax, ecx
	mov	rcx, QWORD PTR tss_entry$[rsp]
	movzx	ecx, BYTE PTR [rcx+7]
	shl	ecx, 24
	add	eax, ecx
	cdqe
	mov	ecx, 8
	imul	rcx, 8
	mov	rdx, QWORD PTR peek_gdt$[rsp+2]
	mov	ecx, DWORD PTR [rdx+rcx]
	shl	rcx, 32					; 00000020H
	add	rax, rcx
	mov	QWORD PTR ?tss@@3PEAU_tss@@EA, rax	; tss
$LN6@initialize:

; 53   : 	
; 54   : 	/*void* esp_stack = x64_get_stack();
; 55   : 	x64_write_msr (IA32_SYSENTER_ESP, (size_t)esp_stack); */
; 56   : }

	add	rsp, 88					; 00000058H
	ret	0
?initialize_user_land@@YAX_K@Z ENDP			; initialize_user_land
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\user64.cpp
_TEXT	SEGMENT
sysret_sel$ = 32
syscall_sel$ = 40
?initialize_syscall@@YAXXZ PROC				; initialize_syscall

; 20   : void initialize_syscall ()  {

$LN3:
	sub	rsp, 56					; 00000038H

; 21   : 	
; 22   : 	uint64_t syscall_sel = SEGVAL (GDT_ENTRY_KERNEL_CODE, 0);

	mov	QWORD PTR syscall_sel$[rsp], 8

; 23   : 	uint64_t sysret_sel = SEGVAL (GDT_ENTRY_USER_CODE32, 3);

	mov	QWORD PTR sysret_sel$[rsp], 27

; 24   : 
; 25   : 	x64_write_msr (IA32_STAR, (sysret_sel << 48) | (syscall_sel << 32));

	mov	rax, QWORD PTR sysret_sel$[rsp]
	shl	rax, 48					; 00000030H
	mov	rcx, QWORD PTR syscall_sel$[rsp]
	shl	rcx, 32					; 00000020H
	or	rax, rcx
	mov	rdx, rax
	mov	ecx, -1073741695			; c0000081H
	call	x64_write_msr

; 26   : 	x64_write_msr (IA32_LSTAR, (size_t)&syscall_entry);

	lea	rdx, OFFSET FLAT:syscall_entry
	mov	ecx, -1073741694			; c0000082H
	call	x64_write_msr

; 27   : 	x64_write_msr (IA32_SFMASK, IA32_EFLAGS_INTR | IA32_EFLAGS_DIRF);

	mov	edx, 1536				; 00000600H
	mov	ecx, -1073741692			; c0000084H
	call	x64_write_msr

; 28   : 	x64_write_msr (IA32_CSTAR, (size_t)&x64_syscall_entry_compat);

	lea	rdx, OFFSET FLAT:x64_syscall_entry_compat
	mov	ecx, -1073741693			; c0000083H
	call	x64_write_msr

; 29   : }

	add	rsp, 56					; 00000038H
	ret	0
?initialize_syscall@@YAXXZ ENDP				; initialize_syscall
_TEXT	ENDS
END
