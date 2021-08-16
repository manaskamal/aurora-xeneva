; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?tss@@3PEAU_tss@@EA				; tss
_BSS	SEGMENT
?tss@@3PEAU_tss@@EA DQ 01H DUP (?)			; tss
_BSS	ENDS
CONST	SEGMENT
$SG2918	DB	'Syscalled occured', 0aH, 00H
	ORG $+5
$SG2919	DB	'Loaded kernel stack is %x', 0aH, 00H
CONST	ENDS
PUBLIC	?initialize_syscall@@YAXXZ			; initialize_syscall
PUBLIC	?initialize_user_land@@YAX_K@Z			; initialize_user_land
PUBLIC	get_kernel_tss
PUBLIC	syscall_debug
EXTRN	x64_write_msr:PROC
EXTRN	x64_sgdt:PROC
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
EXTRN	syscall_entry:PROC
EXTRN	x64_syscall_entry_compat:PROC
pdata	SEGMENT
$pdata$?initialize_syscall@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+110
	DD	imagerel $unwind$?initialize_syscall@@YAXXZ
$pdata$?initialize_user_land@@YAX_K@Z DD imagerel $LN8
	DD	imagerel $LN8+190
	DD	imagerel $unwind$?initialize_user_land@@YAX_K@Z
$pdata$syscall_debug DD imagerel $LN5
	DD	imagerel $LN5+45
	DD	imagerel $unwind$syscall_debug
pdata	ENDS
xdata	SEGMENT
$unwind$?initialize_syscall@@YAXXZ DD 010401H
	DD	06204H
$unwind$?initialize_user_land@@YAX_K@Z DD 010901H
	DD	0a209H
$unwind$syscall_debug DD 010901H
	DD	04209H
xdata	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\user64.cpp
_TEXT	SEGMENT
rcx$ = 48
syscall_debug PROC

; 62   : extern "C" void syscall_debug  (uint64_t rcx) {

$LN5:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 63   : 	printf ("Syscalled occured\n");

	lea	rcx, OFFSET FLAT:$SG2918
	call	?printf@@YAXPEBDZZ			; printf

; 64   : 	printf ("Loaded kernel stack is %x\n", rcx);

	mov	rdx, QWORD PTR rcx$[rsp]
	lea	rcx, OFFSET FLAT:$SG2919
	call	?printf@@YAXPEBDZZ			; printf
$LN2@syscall_de:

; 65   : 	for(;;);

	jmp	SHORT $LN2@syscall_de

; 66   : }

	add	rsp, 40					; 00000028H
	ret	0
syscall_debug ENDP
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\user64.cpp
_TEXT	SEGMENT
get_kernel_tss PROC

; 58   : 	return tss;

	mov	rax, QWORD PTR ?tss@@3PEAU_tss@@EA	; tss

; 59   : }

	ret	0
get_kernel_tss ENDP
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\user64.cpp
_TEXT	SEGMENT
code_sel$ = 32
data_sel$ = 36
tss_entry$ = 40
tv64 = 48
peek_gdt$ = 56
bit$ = 96
?initialize_user_land@@YAX_K@Z PROC			; initialize_user_land

; 32   : void initialize_user_land (size_t bit) {

$LN8:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 88					; 00000058H

; 33   : 
; 34   : 	uint16_t data_sel = SEGVAL (GDT_ENTRY_USER_DATA, 3);

	mov	eax, 35					; 00000023H
	mov	WORD PTR data_sel$[rsp], ax

; 35   : 	uint16_t code_sel = 0;

	xor	eax, eax
	mov	WORD PTR code_sel$[rsp], ax

; 36   : 	switch (bit) {

	mov	rax, QWORD PTR bit$[rsp]
	mov	QWORD PTR tv64[rsp], rax
	cmp	QWORD PTR tv64[rsp], 32			; 00000020H
	je	SHORT $LN2@initialize
	cmp	QWORD PTR tv64[rsp], 64			; 00000040H
	je	SHORT $LN3@initialize
	jmp	SHORT $LN1@initialize
$LN3@initialize:

; 37   : 	case 64:
; 38   : 		code_sel = SEGVAL (GDT_ENTRY_USER_CODE, 3);

	mov	eax, 43					; 0000002bH
	mov	WORD PTR code_sel$[rsp], ax

; 39   : 		break;

	jmp	SHORT $LN4@initialize
$LN2@initialize:

; 40   : 	case 32:
; 41   : 		code_sel = SEGVAL (GDT_ENTRY_USER_CODE32, 3);

	mov	eax, 27
	mov	WORD PTR code_sel$[rsp], ax

; 42   : 		break;

	jmp	SHORT $LN4@initialize
$LN1@initialize:

; 43   : 	default:
; 44   : 		return;

	jmp	SHORT $LN6@initialize
$LN4@initialize:

; 45   : 	}
; 46   : 
; 47   : 	gdtr peek_gdt;
; 48   : 	x64_sgdt (&peek_gdt);

	lea	rcx, QWORD PTR peek_gdt$[rsp]
	call	x64_sgdt

; 49   : 	gdt_entry& tss_entry = peek_gdt.gdtaddr[GDT_ENTRY_TSS];

	mov	eax, 8
	imul	rax, 7
	mov	rcx, QWORD PTR peek_gdt$[rsp+2]
	add	rcx, rax
	mov	rax, rcx
	mov	QWORD PTR tss_entry$[rsp], rax

; 50   : 
; 51   : 	tss = (TSS*) (tss_entry.base_low + (tss_entry.base_mid << 16) + (tss_entry.base_high << 24) + ((uint64_t)*(uint32_t*)&peek_gdt.gdtaddr[GDT_ENTRY_TSS + 1] << 32));

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

; 52   : 	
; 53   : 	/*void* esp_stack = x64_get_stack();
; 54   : 	x64_write_msr (IA32_SYSENTER_ESP, (size_t)esp_stack); */
; 55   : }

	add	rsp, 88					; 00000058H
	ret	0
?initialize_user_land@@YAX_K@Z ENDP			; initialize_user_land
_TEXT	ENDS
; Function compile flags: /Odtp
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\user64.cpp
_TEXT	SEGMENT
sysret_sel$ = 32
syscall_sel$ = 40
?initialize_syscall@@YAXXZ PROC				; initialize_syscall

; 19   : void initialize_syscall ()  {

$LN3:
	sub	rsp, 56					; 00000038H

; 20   : 	
; 21   : 	uint64_t syscall_sel = SEGVAL (GDT_ENTRY_KERNEL_CODE, 0);

	mov	QWORD PTR syscall_sel$[rsp], 8

; 22   : 	uint64_t sysret_sel = SEGVAL (GDT_ENTRY_USER_CODE32, 3);

	mov	QWORD PTR sysret_sel$[rsp], 27

; 23   : 
; 24   : 	x64_write_msr (IA32_STAR, (sysret_sel << 48) | (syscall_sel << 32));

	mov	rax, QWORD PTR sysret_sel$[rsp]
	shl	rax, 48					; 00000030H
	mov	rcx, QWORD PTR syscall_sel$[rsp]
	shl	rcx, 32					; 00000020H
	or	rax, rcx
	mov	rdx, rax
	mov	ecx, -1073741695			; c0000081H
	call	x64_write_msr

; 25   : 	x64_write_msr (IA32_LSTAR, (size_t)&syscall_entry);

	lea	rdx, OFFSET FLAT:syscall_entry
	mov	ecx, -1073741694			; c0000082H
	call	x64_write_msr

; 26   : 	x64_write_msr (IA32_SFMASK, IA32_EFLAGS_INTR | IA32_EFLAGS_DIRF);

	mov	edx, 1536				; 00000600H
	mov	ecx, -1073741692			; c0000084H
	call	x64_write_msr

; 27   : 	x64_write_msr (IA32_CSTAR, (size_t)&x64_syscall_entry_compat);

	lea	rdx, OFFSET FLAT:x64_syscall_entry_compat
	mov	ecx, -1073741693			; c0000083H
	call	x64_write_msr

; 28   : }

	add	rsp, 56					; 00000038H
	ret	0
?initialize_syscall@@YAXXZ ENDP				; initialize_syscall
_TEXT	ENDS
END
