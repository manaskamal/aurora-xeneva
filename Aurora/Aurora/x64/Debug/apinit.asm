; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

CONST	SEGMENT
$SG3438	DB	'Welcome to Application Processor %d', 0aH, 00H
CONST	ENDS
PUBLIC	?AuApInit@@YAXPEAX@Z				; AuApInit
EXTRN	x64_cli:PROC
EXTRN	x64_read_msr:PROC
EXTRN	x64_write_msr:PROC
EXTRN	x64_pause:PROC
EXTRN	?gdt_initialize_ap@@YAXXZ:PROC			; gdt_initialize_ap
EXTRN	?interrupt_initialize_ap@@YAXXZ:PROC		; interrupt_initialize_ap
EXTRN	?exception_init@@YAXXZ:PROC			; exception_init
EXTRN	?x86_64_cpu_get_id@@YAEXZ:PROC			; x86_64_cpu_get_id
EXTRN	?hal_cpu_feature_enable@@YAXXZ:PROC		; hal_cpu_feature_enable
EXTRN	printf:PROC
EXTRN	?initialize_apic@@YAX_N@Z:PROC			; initialize_apic
EXTRN	?AuAPStarted@@YAXXZ:PROC			; AuAPStarted
EXTRN	?AuCreatePCPU@@YAXPEAX@Z:PROC			; AuCreatePCPU
EXTRN	?initialize_syscall@@YAXXZ:PROC			; initialize_syscall
EXTRN	?initialize_user_land_ap@@YAX_K@Z:PROC		; initialize_user_land_ap
pdata	SEGMENT
$pdata$?AuApInit@@YAXPEAX@Z DD imagerel $LN5
	DD	imagerel $LN5+192
	DD	imagerel $unwind$?AuApInit@@YAXPEAX@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?AuApInit@@YAXPEAX@Z DD 010901H
	DD	06209H
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\apinit.cpp
_TEXT	SEGMENT
efer$ = 32
cpu$ = 64
?AuApInit@@YAXPEAX@Z PROC				; AuApInit

; 41   : void AuApInit(void* cpu) {

$LN5:
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 42   : 	x64_cli();

	call	x64_cli

; 43   : 	
; 44   : 	AuCreatePCPU(cpu);

	mov	rcx, QWORD PTR cpu$[rsp]
	call	?AuCreatePCPU@@YAXPEAX@Z		; AuCreatePCPU

; 45   : 	/* Initialize GDT & Interrupts for each core */
; 46   : 	gdt_initialize_ap();

	call	?gdt_initialize_ap@@YAXXZ		; gdt_initialize_ap

; 47   : 	interrupt_initialize_ap();

	call	?interrupt_initialize_ap@@YAXXZ		; interrupt_initialize_ap

; 48   : 	/* Setup exception for each core */
; 49   : 	exception_init();

	call	?exception_init@@YAXXZ			; exception_init

; 50   : 	initialize_apic(false);

	xor	ecx, ecx
	call	?initialize_apic@@YAX_N@Z		; initialize_apic

; 51   : 
; 52   : 	size_t efer = x64_read_msr(IA32_EFER);

	mov	ecx, -1073741696			; c0000080H
	call	x64_read_msr
	mov	QWORD PTR efer$[rsp], rax

; 53   : 	efer |= (1<<11);

	mov	rax, QWORD PTR efer$[rsp]
	bts	rax, 11
	mov	QWORD PTR efer$[rsp], rax

; 54   : 	efer |= 1;

	mov	rax, QWORD PTR efer$[rsp]
	or	rax, 1
	mov	QWORD PTR efer$[rsp], rax

; 55   : 	efer |= (1<<0);

	mov	rax, QWORD PTR efer$[rsp]
	or	rax, 1
	mov	QWORD PTR efer$[rsp], rax

; 56   : 	efer |= 1;

	mov	rax, QWORD PTR efer$[rsp]
	or	rax, 1
	mov	QWORD PTR efer$[rsp], rax

; 57   : 	x64_write_msr(IA32_EFER, efer);

	mov	rdx, QWORD PTR efer$[rsp]
	mov	ecx, -1073741696			; c0000080H
	call	x64_write_msr

; 58   : 
; 59   : 	initialize_user_land_ap(64);

	mov	ecx, 64					; 00000040H
	call	?initialize_user_land_ap@@YAX_K@Z	; initialize_user_land_ap

; 60   : 	initialize_syscall();

	call	?initialize_syscall@@YAXXZ		; initialize_syscall

; 61   : 	hal_cpu_feature_enable();

	call	?hal_cpu_feature_enable@@YAXXZ		; hal_cpu_feature_enable

; 62   : 	printf ("Welcome to Application Processor %d\n", x86_64_cpu_get_id());

	call	?x86_64_cpu_get_id@@YAEXZ		; x86_64_cpu_get_id
	movzx	eax, al
	mov	edx, eax
	lea	rcx, OFFSET FLAT:$SG3438
	call	printf

; 63   : 
; 64   : 	/* From here scheduler should be initialized with good spinlock
; 65   : 	 * system */
; 66   : 	AuAPStarted();

	call	?AuAPStarted@@YAXXZ			; AuAPStarted
$LN2@AuApInit:

; 67   : 	for(;;) {
; 68   : 		x64_pause();

	call	x64_pause

; 69   : 	}

	jmp	SHORT $LN2@AuApInit

; 70   : }

	add	rsp, 56					; 00000038H
	ret	0
?AuApInit@@YAXPEAX@Z ENDP				; AuApInit
_TEXT	ENDS
END
