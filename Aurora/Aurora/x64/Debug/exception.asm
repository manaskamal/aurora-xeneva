; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

CONST	SEGMENT
$SG3398	DB	'***ARCH x86_64 : Kernel Panic!!! ***', 0aH, 00H
	ORG $+10
$SG3399	DB	'[Aurora Kernel]: We are sorry to say that, a processor i'
	DB	'nvalid exception has occured', 0aH, 00H
	ORG $+2
$SG3400	DB	'[Aurora Kernel]: please inform it to the master of the k'
	DB	'ernel', 0aH, 00H
	ORG $+1
$SG3401	DB	'[Aurora Kernel]: Below is the code of exception', 0aH, 00H
	ORG $+7
$SG3408	DB	0aH, 'Divide by 0', 00H
	ORG $+3
$SG3409	DB	'__PROCESSOR_DATA__', 0aH, 00H
	ORG $+4
$SG3410	DB	'RIP -> %x', 0aH, 00H
	ORG $+5
$SG3411	DB	'RSP -> %x', 0aH, 00H
	ORG $+5
$SG3412	DB	'RFLAGS -> %x', 0aH, 00H
	ORG $+2
$SG3422	DB	0aH, 'Single Step Trap', 00H
	ORG $+6
$SG3430	DB	0aH, 'NMI [Non-Muskable-Interrupt] Trap', 00H
	ORG $+5
$SG3438	DB	0aH, 'Breakpoint Trap', 00H
	ORG $+7
$SG3446	DB	0aH, 'Overflow Trap', 00H
	ORG $+1
$SG3454	DB	0aH, 'Bound Check Fault', 00H
	ORG $+5
$SG3464	DB	'Invalid Opcode Fault', 0aH, 00H
	ORG $+2
$SG3465	DB	'__PROCESSOR TRACE__', 0aH, 00H
	ORG $+3
$SG3466	DB	'RIP -> %x', 0aH, 00H
	ORG $+5
$SG3467	DB	'Stack -> %x', 0aH, 00H
	ORG $+3
$SG3468	DB	'RFLAGS -> %x', 0aH, 00H
	ORG $+2
$SG3469	DB	'CS -> %x', 0aH, 00H
	ORG $+6
$SG3470	DB	'SS -> %x', 0aH, 00H
	ORG $+6
$SG3471	DB	'Current task -> %s', 0aH, 00H
	ORG $+4
$SG3472	DB	'Current task id -> %d', 0aH, 00H
	ORG $+1
$SG3480	DB	0aH, 'No Device Fault', 00H
	ORG $+7
$SG3488	DB	0aH, 'Double Fault Abort', 00H
	ORG $+4
$SG3496	DB	0aH, 'Invalid TSS Fault ', 00H
	ORG $+4
$SG3504	DB	0aH, 'No Segment Fault', 00H
	ORG $+6
$SG3512	DB	0aH, 'Stack Fault at ', 00H
	ORG $+7
$SG3522	DB	'Genral Protection Fault', 0aH, 00H
	ORG $+7
$SG3523	DB	'__PROCESSOR TRACE__', 0aH, 00H
	ORG $+3
$SG3524	DB	'RIP -> %x', 0aH, 00H
	ORG $+5
$SG3525	DB	'Stack -> %x', 0aH, 00H
	ORG $+3
$SG3526	DB	'RFLAGS -> %x', 0aH, 00H
	ORG $+2
$SG3527	DB	'Current task ->%s', 0aH, 00H
	ORG $+5
$SG3528	DB	'CS -> %x, SS -> %x', 0aH, 00H
	ORG $+4
$SG3529	DB	'CURRENT TASK STATE -> %d', 0aH, 00H
	ORG $+6
$SG3546	DB	'Page Fault ', 0aH, 00H
	ORG $+3
$SG3547	DB	'Faulting Address -> %x', 0aH, 00H
$SG3548	DB	'__PROCESSOR TRACE__', 0aH, 00H
	ORG $+3
$SG3549	DB	'RIP -> %x', 0aH, 00H
	ORG $+5
$SG3550	DB	'Stack -> %x', 0aH, 00H
	ORG $+3
$SG3551	DB	'RFLAGS -> %x', 0aH, 00H
	ORG $+2
$SG3552	DB	'Current thread -> %s', 0aH, 00H
	ORG $+2
$SG3553	DB	'Current Thread id -> %d', 0aH, 00H
	ORG $+7
$SG3554	DB	'CS -> %x, SS -> %x', 0aH, 00H
	ORG $+4
$SG3555	DB	'******Cause********', 0aH, 00H
	ORG $+3
$SG3557	DB	'***** User Priviledge not set ******** ', 0aH, 00H
	ORG $+7
$SG3560	DB	'**** Not present ****', 0aH, 00H
	ORG $+1
$SG3563	DB	'*** R/W ***', 0aH, 00H
	ORG $+3
$SG3566	DB	'*** Reserved Page ***', 0aH, 00H
	ORG $+1
$SG3569	DB	'*** Invalid Page ****', 0aH, 00H
	ORG $+1
$SG3577	DB	0aH, 'FPU Fault', 00H
	ORG $+5
$SG3585	DB	0aH, 'Alignment Check Fault at address ', 00H
	ORG $+5
$SG3593	DB	0aH, 'Machine Check Abort', 00H
	ORG $+3
$SG3603	DB	0aH, 'SIMD FPU Fault', 00H
$SG3604	DB	0aH, '__CPU Informations__ ', 0aH, 00H
$SG3605	DB	' RIP -> %x ', 0aH, 00H
	ORG $+3
$SG3606	DB	' RSP -> %x ', 0aH, 00H
	ORG $+3
$SG3607	DB	' RFLAGS -> %x ', 0aH, 00H
$SG3608	DB	' Current thread -> %s', 0aH, 00H
	ORG $+1
$SG3609	DB	' MXCSR bit  -- ', 00H
$SG3614	DB	'Invalid operation flag ', 0aH, 00H
	ORG $+7
$SG3617	DB	'Denormal flag ', 0aH, 00H
$SG3620	DB	'Divide-by-zero flag', 0aH, 00H
	ORG $+3
$SG3623	DB	'Overflow flag', 0aH, 00H
	ORG $+1
$SG3626	DB	'Underflow flag', 0aH, 00H
$SG3629	DB	'Precision flag', 0aH, 00H
$SG3632	DB	'Denormals are zeros', 0aH, 00H
	ORG $+3
$SG3635	DB	'Invalid operation mask', 0aH, 00H
$SG3638	DB	'Denormal mask', 0aH, 00H
	ORG $+1
$SG3641	DB	'Divide-by-zero mask', 0aH, 00H
	ORG $+3
$SG3644	DB	'Overflow mask', 0aH, 00H
	ORG $+1
$SG3647	DB	'Underflow mask', 0aH, 00H
CONST	ENDS
PUBLIC	?exception_init@@YAXXZ				; exception_init
PUBLIC	?panic@@YAXPEBDZZ				; panic
PUBLIC	?divide_by_zero_fault@@YAX_KPEAX@Z		; divide_by_zero_fault
PUBLIC	?single_step_trap@@YAX_KPEAX@Z			; single_step_trap
PUBLIC	?nmi_trap@@YAX_KPEAX@Z				; nmi_trap
PUBLIC	?breakpoint_trap@@YAX_KPEAX@Z			; breakpoint_trap
PUBLIC	?overflow_trap@@YAX_KPEAX@Z			; overflow_trap
PUBLIC	?bounds_check_fault@@YAX_KPEAX@Z		; bounds_check_fault
PUBLIC	?invalid_opcode_fault@@YAX_KPEAX@Z		; invalid_opcode_fault
PUBLIC	?no_device_fault@@YAX_KPEAX@Z			; no_device_fault
PUBLIC	?double_fault_abort@@YAX_KPEAX@Z		; double_fault_abort
PUBLIC	?invalid_tss_fault@@YAX_KPEAX@Z			; invalid_tss_fault
PUBLIC	?no_segment_fault@@YAX_KPEAX@Z			; no_segment_fault
PUBLIC	?stack_fault@@YAX_KPEAX@Z			; stack_fault
PUBLIC	?general_protection_fault@@YAX_KPEAX@Z		; general_protection_fault
PUBLIC	?page_fault@@YAX_KPEAX@Z			; page_fault
PUBLIC	?fpu_fault@@YAX_KPEAX@Z				; fpu_fault
PUBLIC	?alignment_check_fault@@YAX_KPEAX@Z		; alignment_check_fault
PUBLIC	?machine_check_abort@@YAX_KPEAX@Z		; machine_check_abort
PUBLIC	?simd_fpu_fault@@YAX_KPEAX@Z			; simd_fpu_fault
EXTRN	printf:PROC
EXTRN	x64_cli:PROC
EXTRN	x64_read_cr2:PROC
EXTRN	?setvect@@YAX_KP6AX0PEAX@Z@Z:PROC		; setvect
EXTRN	?block_thread@@YAXPEAU_thread_@@@Z:PROC		; block_thread
EXTRN	?get_current_thread@@YAPEAU_thread_@@XZ:PROC	; get_current_thread
EXTRN	?force_sched@@YAXXZ:PROC			; force_sched
pdata	SEGMENT
$pdata$?exception_init@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+312
	DD	imagerel $unwind$?exception_init@@YAXXZ
$pdata$?panic@@YAXPEBDZZ DD imagerel $LN3
	DD	imagerel $LN3+87
	DD	imagerel $unwind$?panic@@YAXPEBDZZ
$pdata$?divide_by_zero_fault@@YAX_KPEAX@Z DD imagerel $LN5
	DD	imagerel $LN5+123
	DD	imagerel $unwind$?divide_by_zero_fault@@YAX_KPEAX@Z
$pdata$?single_step_trap@@YAX_KPEAX@Z DD imagerel $LN5
	DD	imagerel $LN5+48
	DD	imagerel $unwind$?single_step_trap@@YAX_KPEAX@Z
$pdata$?nmi_trap@@YAX_KPEAX@Z DD imagerel $LN5
	DD	imagerel $LN5+38
	DD	imagerel $unwind$?nmi_trap@@YAX_KPEAX@Z
$pdata$?breakpoint_trap@@YAX_KPEAX@Z DD imagerel $LN5
	DD	imagerel $LN5+38
	DD	imagerel $unwind$?breakpoint_trap@@YAX_KPEAX@Z
$pdata$?overflow_trap@@YAX_KPEAX@Z DD imagerel $LN5
	DD	imagerel $LN5+38
	DD	imagerel $unwind$?overflow_trap@@YAX_KPEAX@Z
$pdata$?bounds_check_fault@@YAX_KPEAX@Z DD imagerel $LN5
	DD	imagerel $LN5+38
	DD	imagerel $unwind$?bounds_check_fault@@YAX_KPEAX@Z
$pdata$?invalid_opcode_fault@@YAX_KPEAX@Z DD imagerel $LN5
	DD	imagerel $LN5+215
	DD	imagerel $unwind$?invalid_opcode_fault@@YAX_KPEAX@Z
$pdata$?no_device_fault@@YAX_KPEAX@Z DD imagerel $LN5
	DD	imagerel $LN5+38
	DD	imagerel $unwind$?no_device_fault@@YAX_KPEAX@Z
$pdata$?double_fault_abort@@YAX_KPEAX@Z DD imagerel $LN5
	DD	imagerel $LN5+38
	DD	imagerel $unwind$?double_fault_abort@@YAX_KPEAX@Z
$pdata$?invalid_tss_fault@@YAX_KPEAX@Z DD imagerel $LN5
	DD	imagerel $LN5+38
	DD	imagerel $unwind$?invalid_tss_fault@@YAX_KPEAX@Z
$pdata$?no_segment_fault@@YAX_KPEAX@Z DD imagerel $LN5
	DD	imagerel $LN5+38
	DD	imagerel $unwind$?no_segment_fault@@YAX_KPEAX@Z
$pdata$?stack_fault@@YAX_KPEAX@Z DD imagerel $LN5
	DD	imagerel $LN5+38
	DD	imagerel $unwind$?stack_fault@@YAX_KPEAX@Z
$pdata$?general_protection_fault@@YAX_KPEAX@Z DD imagerel $LN5
	DD	imagerel $LN5+216
	DD	imagerel $unwind$?general_protection_fault@@YAX_KPEAX@Z
$pdata$?page_fault@@YAX_KPEAX@Z DD imagerel $LN16
	DD	imagerel $LN16+452
	DD	imagerel $unwind$?page_fault@@YAX_KPEAX@Z
$pdata$?fpu_fault@@YAX_KPEAX@Z DD imagerel $LN5
	DD	imagerel $LN5+38
	DD	imagerel $unwind$?fpu_fault@@YAX_KPEAX@Z
$pdata$?alignment_check_fault@@YAX_KPEAX@Z DD imagerel $LN5
	DD	imagerel $LN5+38
	DD	imagerel $unwind$?alignment_check_fault@@YAX_KPEAX@Z
$pdata$?machine_check_abort@@YAX_KPEAX@Z DD imagerel $LN5
	DD	imagerel $LN5+38
	DD	imagerel $unwind$?machine_check_abort@@YAX_KPEAX@Z
$pdata$?simd_fpu_fault@@YAX_KPEAX@Z DD imagerel $LN28
	DD	imagerel $LN28+516
	DD	imagerel $unwind$?simd_fpu_fault@@YAX_KPEAX@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?exception_init@@YAXXZ DD 010401H
	DD	04204H
$unwind$?panic@@YAXPEBDZZ DD 011801H
	DD	04218H
$unwind$?divide_by_zero_fault@@YAX_KPEAX@Z DD 010e01H
	DD	0620eH
$unwind$?single_step_trap@@YAX_KPEAX@Z DD 010e01H
	DD	0620eH
$unwind$?nmi_trap@@YAX_KPEAX@Z DD 010e01H
	DD	0420eH
$unwind$?breakpoint_trap@@YAX_KPEAX@Z DD 010e01H
	DD	0420eH
$unwind$?overflow_trap@@YAX_KPEAX@Z DD 010e01H
	DD	0420eH
$unwind$?bounds_check_fault@@YAX_KPEAX@Z DD 010e01H
	DD	0420eH
$unwind$?invalid_opcode_fault@@YAX_KPEAX@Z DD 010e01H
	DD	0620eH
$unwind$?no_device_fault@@YAX_KPEAX@Z DD 010e01H
	DD	0420eH
$unwind$?double_fault_abort@@YAX_KPEAX@Z DD 010e01H
	DD	0420eH
$unwind$?invalid_tss_fault@@YAX_KPEAX@Z DD 010e01H
	DD	0420eH
$unwind$?no_segment_fault@@YAX_KPEAX@Z DD 010e01H
	DD	0420eH
$unwind$?stack_fault@@YAX_KPEAX@Z DD 010e01H
	DD	0420eH
$unwind$?general_protection_fault@@YAX_KPEAX@Z DD 010e01H
	DD	0620eH
$unwind$?page_fault@@YAX_KPEAX@Z DD 010e01H
	DD	0a20eH
$unwind$?fpu_fault@@YAX_KPEAX@Z DD 010e01H
	DD	0420eH
$unwind$?alignment_check_fault@@YAX_KPEAX@Z DD 010e01H
	DD	0420eH
$unwind$?machine_check_abort@@YAX_KPEAX@Z DD 010e01H
	DD	0420eH
$unwind$?simd_fpu_fault@@YAX_KPEAX@Z DD 010e01H
	DD	0820eH
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\exception.cpp
_TEXT	SEGMENT
mxcsr$ = 32
frame$ = 40
state$ = 48
v$ = 80
p$ = 88
?simd_fpu_fault@@YAX_KPEAX@Z PROC			; simd_fpu_fault

; 208  :  void simd_fpu_fault (size_t v, void* p){

$LN28:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 72					; 00000048H

; 209  : 	 x64_cli();

	call	x64_cli

; 210  : 	 interrupt_stack_frame *frame = (interrupt_stack_frame*)p;

	mov	rax, QWORD PTR p$[rsp]
	mov	QWORD PTR frame$[rsp], rax

; 211  : 	 panic("\nSIMD FPU Fault");

	lea	rcx, OFFSET FLAT:$SG3603
	call	?panic@@YAXPEBDZZ			; panic

; 212  : 	 printf ("\n__CPU Informations__ \n");

	lea	rcx, OFFSET FLAT:$SG3604
	call	printf

; 213  : 	 printf (" RIP -> %x \n", frame->rip);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+16]
	lea	rcx, OFFSET FLAT:$SG3605
	call	printf

; 214  : 	 printf (" RSP -> %x \n", frame->rsp);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+40]
	lea	rcx, OFFSET FLAT:$SG3606
	call	printf

; 215  : 	 printf (" RFLAGS -> %x \n", frame->rflags);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+32]
	lea	rcx, OFFSET FLAT:$SG3607
	call	printf

; 216  : 	 printf (" Current thread -> %s\n", get_current_thread()->name);

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	mov	rdx, QWORD PTR [rax+728]
	lea	rcx, OFFSET FLAT:$SG3608
	call	printf

; 217  : 	 printf (" MXCSR bit  -- ");

	lea	rcx, OFFSET FLAT:$SG3609
	call	printf

; 218  : 	 fx_state_t* state = (fx_state_t*)get_current_thread()->fx_state;

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	add	rax, 208				; 000000d0H
	mov	QWORD PTR state$[rsp], rax

; 219  : 	 uint32_t mxcsr = state->mxcsr;

	mov	rax, QWORD PTR state$[rsp]
	mov	eax, DWORD PTR [rax+24]
	mov	DWORD PTR mxcsr$[rsp], eax

; 220  : 	 if (mxcsr & 0x0001)

	mov	eax, DWORD PTR mxcsr$[rsp]
	and	eax, 1
	test	eax, eax
	je	SHORT $LN25@simd_fpu_f

; 221  : 		 printf ("Invalid operation flag \n");

	lea	rcx, OFFSET FLAT:$SG3614
	call	printf
	jmp	$LN24@simd_fpu_f
$LN25@simd_fpu_f:

; 222  : 	 else if (mxcsr & 0x0002)

	mov	eax, DWORD PTR mxcsr$[rsp]
	and	eax, 2
	test	eax, eax
	je	SHORT $LN23@simd_fpu_f

; 223  : 		 printf ("Denormal flag \n");

	lea	rcx, OFFSET FLAT:$SG3617
	call	printf
	jmp	$LN22@simd_fpu_f
$LN23@simd_fpu_f:

; 224  : 	 else if (mxcsr & 0x0004)

	mov	eax, DWORD PTR mxcsr$[rsp]
	and	eax, 4
	test	eax, eax
	je	SHORT $LN21@simd_fpu_f

; 225  : 		 printf ("Divide-by-zero flag\n");

	lea	rcx, OFFSET FLAT:$SG3620
	call	printf
	jmp	$LN20@simd_fpu_f
$LN21@simd_fpu_f:

; 226  : 	 else if (mxcsr & 0x0008)

	mov	eax, DWORD PTR mxcsr$[rsp]
	and	eax, 8
	test	eax, eax
	je	SHORT $LN19@simd_fpu_f

; 227  : 		 printf ("Overflow flag\n");

	lea	rcx, OFFSET FLAT:$SG3623
	call	printf
	jmp	$LN18@simd_fpu_f
$LN19@simd_fpu_f:

; 228  : 	 else if (mxcsr & 0x0010)

	mov	eax, DWORD PTR mxcsr$[rsp]
	and	eax, 16
	test	eax, eax
	je	SHORT $LN17@simd_fpu_f

; 229  : 		 printf ("Underflow flag\n");

	lea	rcx, OFFSET FLAT:$SG3626
	call	printf
	jmp	$LN16@simd_fpu_f
$LN17@simd_fpu_f:

; 230  : 	 else if (mxcsr & 0x0020)

	mov	eax, DWORD PTR mxcsr$[rsp]
	and	eax, 32					; 00000020H
	test	eax, eax
	je	SHORT $LN15@simd_fpu_f

; 231  : 		 printf ("Precision flag\n");

	lea	rcx, OFFSET FLAT:$SG3629
	call	printf
	jmp	$LN14@simd_fpu_f
$LN15@simd_fpu_f:

; 232  : 	 else if (mxcsr & 0x0040)

	mov	eax, DWORD PTR mxcsr$[rsp]
	and	eax, 64					; 00000040H
	test	eax, eax
	je	SHORT $LN13@simd_fpu_f

; 233  : 		 printf ("Denormals are zeros\n");

	lea	rcx, OFFSET FLAT:$SG3632
	call	printf
	jmp	$LN12@simd_fpu_f
$LN13@simd_fpu_f:

; 234  : 	 else if (mxcsr & 0x0080)

	mov	eax, DWORD PTR mxcsr$[rsp]
	and	eax, 128				; 00000080H
	test	eax, eax
	je	SHORT $LN11@simd_fpu_f

; 235  : 		 printf ("Invalid operation mask\n");

	lea	rcx, OFFSET FLAT:$SG3635
	call	printf
	jmp	SHORT $LN10@simd_fpu_f
$LN11@simd_fpu_f:

; 236  : 	 else if (mxcsr & 0x0100)

	mov	eax, DWORD PTR mxcsr$[rsp]
	and	eax, 256				; 00000100H
	test	eax, eax
	je	SHORT $LN9@simd_fpu_f

; 237  : 		 printf ("Denormal mask\n");

	lea	rcx, OFFSET FLAT:$SG3638
	call	printf
	jmp	SHORT $LN8@simd_fpu_f
$LN9@simd_fpu_f:

; 238  : 	 else if (mxcsr & 0x0200)

	mov	eax, DWORD PTR mxcsr$[rsp]
	and	eax, 512				; 00000200H
	test	eax, eax
	je	SHORT $LN7@simd_fpu_f

; 239  : 		 printf ("Divide-by-zero mask\n");

	lea	rcx, OFFSET FLAT:$SG3641
	call	printf
	jmp	SHORT $LN6@simd_fpu_f
$LN7@simd_fpu_f:

; 240  : 	 else if (mxcsr & 0x0400)

	mov	eax, DWORD PTR mxcsr$[rsp]
	and	eax, 1024				; 00000400H
	test	eax, eax
	je	SHORT $LN5@simd_fpu_f

; 241  : 		 printf ("Overflow mask\n");

	lea	rcx, OFFSET FLAT:$SG3644
	call	printf
	jmp	SHORT $LN4@simd_fpu_f
$LN5@simd_fpu_f:

; 242  : 	 else if (mxcsr & 0x0800)

	mov	eax, DWORD PTR mxcsr$[rsp]
	and	eax, 2048				; 00000800H
	test	eax, eax
	je	SHORT $LN3@simd_fpu_f

; 243  : 		 printf ("Underflow mask\n");

	lea	rcx, OFFSET FLAT:$SG3647
	call	printf
$LN3@simd_fpu_f:
$LN4@simd_fpu_f:
$LN6@simd_fpu_f:
$LN8@simd_fpu_f:
$LN10@simd_fpu_f:
$LN12@simd_fpu_f:
$LN14@simd_fpu_f:
$LN16@simd_fpu_f:
$LN18@simd_fpu_f:
$LN20@simd_fpu_f:
$LN22@simd_fpu_f:
$LN24@simd_fpu_f:
$LN2@simd_fpu_f:

; 244  : 	 for(;;);

	jmp	SHORT $LN2@simd_fpu_f

; 245  :  }

	add	rsp, 72					; 00000048H
	ret	0
?simd_fpu_fault@@YAX_KPEAX@Z ENDP			; simd_fpu_fault
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\exception.cpp
_TEXT	SEGMENT
v$ = 48
p$ = 56
?machine_check_abort@@YAX_KPEAX@Z PROC			; machine_check_abort

; 201  : void machine_check_abort (size_t v, void* p){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 202  : 	x64_cli();

	call	x64_cli

; 203  : 	panic("\nMachine Check Abort");

	lea	rcx, OFFSET FLAT:$SG3593
	call	?panic@@YAXPEBDZZ			; panic
$LN2@machine_ch:

; 204  : 	for(;;);

	jmp	SHORT $LN2@machine_ch

; 205  : }

	add	rsp, 40					; 00000028H
	ret	0
?machine_check_abort@@YAX_KPEAX@Z ENDP			; machine_check_abort
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\exception.cpp
_TEXT	SEGMENT
v$ = 48
p$ = 56
?alignment_check_fault@@YAX_KPEAX@Z PROC		; alignment_check_fault

; 194  : void alignment_check_fault (size_t v, void* p){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 195  : 	x64_cli();

	call	x64_cli

; 196  : 	panic("\nAlignment Check Fault at address ");

	lea	rcx, OFFSET FLAT:$SG3585
	call	?panic@@YAXPEBDZZ			; panic
$LN2@alignment_:

; 197  : 	for(;;);

	jmp	SHORT $LN2@alignment_

; 198  : }

	add	rsp, 40					; 00000028H
	ret	0
?alignment_check_fault@@YAX_KPEAX@Z ENDP		; alignment_check_fault
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\exception.cpp
_TEXT	SEGMENT
vector$ = 48
p$ = 56
?fpu_fault@@YAX_KPEAX@Z PROC				; fpu_fault

; 186  : void fpu_fault (size_t vector, void* p){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 187  : 	x64_cli();

	call	x64_cli

; 188  : 	panic("\nFPU Fault");

	lea	rcx, OFFSET FLAT:$SG3577
	call	?panic@@YAXPEBDZZ			; panic
$LN2@fpu_fault:

; 189  : 	for(;;);

	jmp	SHORT $LN2@fpu_fault

; 190  : }

	add	rsp, 40					; 00000028H
	ret	0
?fpu_fault@@YAX_KPEAX@Z ENDP				; fpu_fault
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\exception.cpp
_TEXT	SEGMENT
tv68 = 32
us$ = 36
present$ = 40
rw$ = 44
resv$ = 48
id$ = 52
frame$ = 56
vaddr$ = 64
vector$ = 96
param$ = 104
?page_fault@@YAX_KPEAX@Z PROC				; page_fault

; 146  : void page_fault (size_t vector, void* param){

$LN16:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 88					; 00000058H

; 147  : 	interrupt_stack_frame *frame = (interrupt_stack_frame*)param;

	mov	rax, QWORD PTR param$[rsp]
	mov	QWORD PTR frame$[rsp], rax

; 148  : 	void* vaddr = (void*)x64_read_cr2();

	call	x64_read_cr2
	mov	QWORD PTR vaddr$[rsp], rax

; 149  : 
; 150  : 	int present = !(frame->error & 0x1);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rax, QWORD PTR [rax+8]
	and	rax, 1
	test	rax, rax
	jne	SHORT $LN14@page_fault
	mov	DWORD PTR tv68[rsp], 1
	jmp	SHORT $LN15@page_fault
$LN14@page_fault:
	mov	DWORD PTR tv68[rsp], 0
$LN15@page_fault:
	mov	eax, DWORD PTR tv68[rsp]
	mov	DWORD PTR present$[rsp], eax

; 151  : 	int rw = frame->error & 0x2;

	mov	rax, QWORD PTR frame$[rsp]
	mov	rax, QWORD PTR [rax+8]
	and	rax, 2
	mov	DWORD PTR rw$[rsp], eax

; 152  : 	int us = frame->error & 0x4;

	mov	rax, QWORD PTR frame$[rsp]
	mov	rax, QWORD PTR [rax+8]
	and	rax, 4
	mov	DWORD PTR us$[rsp], eax

; 153  : 	int resv = frame->error & 0x8;

	mov	rax, QWORD PTR frame$[rsp]
	mov	rax, QWORD PTR [rax+8]
	and	rax, 8
	mov	DWORD PTR resv$[rsp], eax

; 154  : 	int id = frame->error & 0x10;

	mov	rax, QWORD PTR frame$[rsp]
	mov	rax, QWORD PTR [rax+8]
	and	rax, 16
	mov	DWORD PTR id$[rsp], eax

; 155  : 
; 156  : 	panic ("Page Fault \n");

	lea	rcx, OFFSET FLAT:$SG3546
	call	?panic@@YAXPEBDZZ			; panic

; 157  : 	printf ("Faulting Address -> %x\n", vaddr);

	mov	rdx, QWORD PTR vaddr$[rsp]
	lea	rcx, OFFSET FLAT:$SG3547
	call	printf

; 158  : 	printf ("__PROCESSOR TRACE__\n");

	lea	rcx, OFFSET FLAT:$SG3548
	call	printf

; 159  : 	printf ("RIP -> %x\n", frame->rip);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+16]
	lea	rcx, OFFSET FLAT:$SG3549
	call	printf

; 160  : 	printf ("Stack -> %x\n", frame->rsp);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+40]
	lea	rcx, OFFSET FLAT:$SG3550
	call	printf

; 161  : 	printf ("RFLAGS -> %x\n", frame->rflags);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+32]
	lea	rcx, OFFSET FLAT:$SG3551
	call	printf

; 162  : 	printf ("Current thread -> %s\n", get_current_thread()->name);

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	mov	rdx, QWORD PTR [rax+728]
	lea	rcx, OFFSET FLAT:$SG3552
	call	printf

; 163  : 	printf ("Current Thread id -> %d\n", get_current_thread()->id);

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	movzx	eax, WORD PTR [rax+738]
	mov	edx, eax
	lea	rcx, OFFSET FLAT:$SG3553
	call	printf

; 164  : 	printf ("CS -> %x, SS -> %x\n", frame->cs, frame->ss);

	mov	rax, QWORD PTR frame$[rsp]
	mov	r8, QWORD PTR [rax+48]
	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+24]
	lea	rcx, OFFSET FLAT:$SG3554
	call	printf

; 165  : 	printf ("******Cause********\n");

	lea	rcx, OFFSET FLAT:$SG3555
	call	printf

; 166  : 	if (us){

	cmp	DWORD PTR us$[rsp], 0
	je	SHORT $LN11@page_fault

; 167  : 		//AuMapPage((uint64_t)AuPmmngrAlloc(), (uint64_t)vaddr,PAGING_USER);
; 168  : 		printf ("***** User Priviledge not set ******** \n");

	lea	rcx, OFFSET FLAT:$SG3557
	call	printf
	jmp	SHORT $LN10@page_fault
$LN11@page_fault:

; 169  : 	}else if (present){

	cmp	DWORD PTR present$[rsp], 0
	je	SHORT $LN9@page_fault

; 170  : 		//map_page((uint64_t)pmmngr_alloc(), (uint64_t)vaddr,PAGING_USER);
; 171  : 		printf ("**** Not present ****\n");

	lea	rcx, OFFSET FLAT:$SG3560
	call	printf
	jmp	SHORT $LN8@page_fault
$LN9@page_fault:

; 172  : 	}else if (rw) {

	cmp	DWORD PTR rw$[rsp], 0
	je	SHORT $LN7@page_fault

; 173  : 		printf ("*** R/W ***\n");

	lea	rcx, OFFSET FLAT:$SG3563
	call	printf
	jmp	SHORT $LN6@page_fault
$LN7@page_fault:

; 174  : 	}else if (resv) {

	cmp	DWORD PTR resv$[rsp], 0
	je	SHORT $LN5@page_fault

; 175  : 		printf ("*** Reserved Page ***\n");

	lea	rcx, OFFSET FLAT:$SG3566
	call	printf
	jmp	SHORT $LN4@page_fault
$LN5@page_fault:

; 176  : 	}else if (id) {

	cmp	DWORD PTR id$[rsp], 0
	je	SHORT $LN3@page_fault

; 177  : 		printf ("*** Invalid Page ****\n");

	lea	rcx, OFFSET FLAT:$SG3569
	call	printf
$LN3@page_fault:
$LN4@page_fault:
$LN6@page_fault:
$LN8@page_fault:
$LN10@page_fault:
$LN2@page_fault:

; 178  : 	}
; 179  : 
; 180  : 
; 181  : 	for(;;);

	jmp	SHORT $LN2@page_fault

; 182  : }

	add	rsp, 88					; 00000058H
	ret	0
?page_fault@@YAX_KPEAX@Z ENDP				; page_fault
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\exception.cpp
_TEXT	SEGMENT
frame$ = 32
v$ = 64
p$ = 72
?general_protection_fault@@YAX_KPEAX@Z PROC		; general_protection_fault

; 127  : void general_protection_fault (size_t v, void* p){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 128  : 	//x64_cli();
; 129  : 	interrupt_stack_frame *frame = (interrupt_stack_frame*)p;

	mov	rax, QWORD PTR p$[rsp]
	mov	QWORD PTR frame$[rsp], rax

; 130  : 	panic ("Genral Protection Fault\n");

	lea	rcx, OFFSET FLAT:$SG3522
	call	?panic@@YAXPEBDZZ			; panic

; 131  : 	printf ("__PROCESSOR TRACE__\n");

	lea	rcx, OFFSET FLAT:$SG3523
	call	printf

; 132  : 	printf ("RIP -> %x\n",frame->rip);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+16]
	lea	rcx, OFFSET FLAT:$SG3524
	call	printf

; 133  : 	printf ("Stack -> %x\n", frame->rsp);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+40]
	lea	rcx, OFFSET FLAT:$SG3525
	call	printf

; 134  : 	printf ("RFLAGS -> %x\n", frame->rflags);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+32]
	lea	rcx, OFFSET FLAT:$SG3526
	call	printf

; 135  : 	printf ("Current task ->%s\n", get_current_thread()->name);

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	mov	rdx, QWORD PTR [rax+728]
	lea	rcx, OFFSET FLAT:$SG3527
	call	printf

; 136  : 	printf ("CS -> %x, SS -> %x\n", frame->cs, frame->ss);

	mov	rax, QWORD PTR frame$[rsp]
	mov	r8, QWORD PTR [rax+48]
	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+24]
	lea	rcx, OFFSET FLAT:$SG3528
	call	printf

; 137  : 	printf ("CURRENT TASK STATE -> %d\n", get_current_thread()->state);

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	movzx	eax, BYTE PTR [rax+736]
	mov	edx, eax
	lea	rcx, OFFSET FLAT:$SG3529
	call	printf
$LN2@general_pr:

; 138  :     for(;;);

	jmp	SHORT $LN2@general_pr

; 139  : 	block_thread(get_current_thread());

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	mov	rcx, rax
	call	?block_thread@@YAXPEAU_thread_@@@Z	; block_thread

; 140  : 	force_sched();

	call	?force_sched@@YAXXZ			; force_sched

; 141  : }

	add	rsp, 56					; 00000038H
	ret	0
?general_protection_fault@@YAX_KPEAX@Z ENDP		; general_protection_fault
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\exception.cpp
_TEXT	SEGMENT
v$ = 48
p$ = 56
?stack_fault@@YAX_KPEAX@Z PROC				; stack_fault

; 119  : void stack_fault (size_t v, void* p){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 120  : 	x64_cli();

	call	x64_cli

; 121  : 	panic("\nStack Fault at ");

	lea	rcx, OFFSET FLAT:$SG3512
	call	?panic@@YAXPEBDZZ			; panic
$LN2@stack_faul:

; 122  : 	for(;;);

	jmp	SHORT $LN2@stack_faul

; 123  : }

	add	rsp, 40					; 00000028H
	ret	0
?stack_fault@@YAX_KPEAX@Z ENDP				; stack_fault
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\exception.cpp
_TEXT	SEGMENT
v$ = 48
p$ = 56
?no_segment_fault@@YAX_KPEAX@Z PROC			; no_segment_fault

; 112  : void no_segment_fault (size_t v, void* p){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 113  : 	x64_cli();

	call	x64_cli

; 114  : 	panic("\nNo Segment Fault");

	lea	rcx, OFFSET FLAT:$SG3504
	call	?panic@@YAXPEBDZZ			; panic
$LN2@no_segment:

; 115  : 	for(;;);

	jmp	SHORT $LN2@no_segment

; 116  : }

	add	rsp, 40					; 00000028H
	ret	0
?no_segment_fault@@YAX_KPEAX@Z ENDP			; no_segment_fault
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\exception.cpp
_TEXT	SEGMENT
v$ = 48
p$ = 56
?invalid_tss_fault@@YAX_KPEAX@Z PROC			; invalid_tss_fault

; 105  : void invalid_tss_fault (size_t v, void* p){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 106  : 	x64_cli();

	call	x64_cli

; 107  : 	panic("\nInvalid TSS Fault ");

	lea	rcx, OFFSET FLAT:$SG3496
	call	?panic@@YAXPEBDZZ			; panic
$LN2@invalid_ts:

; 108  : 	for(;;);

	jmp	SHORT $LN2@invalid_ts

; 109  : }

	add	rsp, 40					; 00000028H
	ret	0
?invalid_tss_fault@@YAX_KPEAX@Z ENDP			; invalid_tss_fault
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\exception.cpp
_TEXT	SEGMENT
v$ = 48
p$ = 56
?double_fault_abort@@YAX_KPEAX@Z PROC			; double_fault_abort

; 98   : void double_fault_abort (size_t v, void* p){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 99   : 	x64_cli();

	call	x64_cli

; 100  : 	panic("\nDouble Fault Abort");

	lea	rcx, OFFSET FLAT:$SG3488
	call	?panic@@YAXPEBDZZ			; panic
$LN2@double_fau:

; 101  : 	for(;;);

	jmp	SHORT $LN2@double_fau

; 102  : }

	add	rsp, 40					; 00000028H
	ret	0
?double_fault_abort@@YAX_KPEAX@Z ENDP			; double_fault_abort
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\exception.cpp
_TEXT	SEGMENT
v$ = 48
p$ = 56
?no_device_fault@@YAX_KPEAX@Z PROC			; no_device_fault

; 91   : void no_device_fault (size_t v, void* p){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 92   : 	x64_cli();

	call	x64_cli

; 93   : 	panic("\nNo Device Fault");

	lea	rcx, OFFSET FLAT:$SG3480
	call	?panic@@YAXPEBDZZ			; panic
$LN2@no_device_:

; 94   : 	for(;;);

	jmp	SHORT $LN2@no_device_

; 95   : }

	add	rsp, 40					; 00000028H
	ret	0
?no_device_fault@@YAX_KPEAX@Z ENDP			; no_device_fault
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\exception.cpp
_TEXT	SEGMENT
frame$ = 32
v$ = 64
p$ = 72
?invalid_opcode_fault@@YAX_KPEAX@Z PROC			; invalid_opcode_fault

; 75   : void invalid_opcode_fault (size_t v, void* p){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 76   : 	x64_cli();

	call	x64_cli

; 77   : 	interrupt_stack_frame *frame = (interrupt_stack_frame*)p;

	mov	rax, QWORD PTR p$[rsp]
	mov	QWORD PTR frame$[rsp], rax

; 78   : 	panic("Invalid Opcode Fault\n");

	lea	rcx, OFFSET FLAT:$SG3464
	call	?panic@@YAXPEBDZZ			; panic

; 79   : 	printf ("__PROCESSOR TRACE__\n");

	lea	rcx, OFFSET FLAT:$SG3465
	call	printf

; 80   : 	printf ("RIP -> %x\n",frame->rip);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+16]
	lea	rcx, OFFSET FLAT:$SG3466
	call	printf

; 81   : 	printf ("Stack -> %x\n", frame->rsp);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+40]
	lea	rcx, OFFSET FLAT:$SG3467
	call	printf

; 82   : 	printf ("RFLAGS -> %x\n", frame->rflags);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+32]
	lea	rcx, OFFSET FLAT:$SG3468
	call	printf

; 83   : 	printf ("CS -> %x\n", frame->cs);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+24]
	lea	rcx, OFFSET FLAT:$SG3469
	call	printf

; 84   : 	printf ("SS -> %x\n", frame->ss);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+48]
	lea	rcx, OFFSET FLAT:$SG3470
	call	printf

; 85   : 	printf ("Current task -> %s\n", get_current_thread()->name);

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	mov	rdx, QWORD PTR [rax+728]
	lea	rcx, OFFSET FLAT:$SG3471
	call	printf

; 86   : 	printf ("Current task id -> %d\n", get_current_thread()->id);

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	movzx	eax, WORD PTR [rax+738]
	mov	edx, eax
	lea	rcx, OFFSET FLAT:$SG3472
	call	printf
$LN2@invalid_op:

; 87   : 	for(;;);

	jmp	SHORT $LN2@invalid_op

; 88   : }

	add	rsp, 56					; 00000038H
	ret	0
?invalid_opcode_fault@@YAX_KPEAX@Z ENDP			; invalid_opcode_fault
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\exception.cpp
_TEXT	SEGMENT
v$ = 48
p$ = 56
?bounds_check_fault@@YAX_KPEAX@Z PROC			; bounds_check_fault

; 68   : void bounds_check_fault (size_t v, void* p){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 69   : 	x64_cli();

	call	x64_cli

; 70   : 	panic("\nBound Check Fault");

	lea	rcx, OFFSET FLAT:$SG3454
	call	?panic@@YAXPEBDZZ			; panic
$LN2@bounds_che:

; 71   : 	for(;;);

	jmp	SHORT $LN2@bounds_che

; 72   : }

	add	rsp, 40					; 00000028H
	ret	0
?bounds_check_fault@@YAX_KPEAX@Z ENDP			; bounds_check_fault
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\exception.cpp
_TEXT	SEGMENT
v$ = 48
p$ = 56
?overflow_trap@@YAX_KPEAX@Z PROC			; overflow_trap

; 61   : void overflow_trap (size_t v, void* p){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 62   : 	x64_cli();

	call	x64_cli

; 63   : 	panic("\nOverflow Trap");

	lea	rcx, OFFSET FLAT:$SG3446
	call	?panic@@YAXPEBDZZ			; panic
$LN2@overflow_t:

; 64   : 	for(;;);

	jmp	SHORT $LN2@overflow_t

; 65   : }

	add	rsp, 40					; 00000028H
	ret	0
?overflow_trap@@YAX_KPEAX@Z ENDP			; overflow_trap
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\exception.cpp
_TEXT	SEGMENT
vector$ = 48
param$ = 56
?breakpoint_trap@@YAX_KPEAX@Z PROC			; breakpoint_trap

; 54   : void breakpoint_trap (size_t vector, void* param){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 55   : 	x64_cli();

	call	x64_cli

; 56   : 	panic("\nBreakpoint Trap");

	lea	rcx, OFFSET FLAT:$SG3438
	call	?panic@@YAXPEBDZZ			; panic
$LN2@breakpoint:

; 57   : 	for(;;);

	jmp	SHORT $LN2@breakpoint

; 58   : }

	add	rsp, 40					; 00000028H
	ret	0
?breakpoint_trap@@YAX_KPEAX@Z ENDP			; breakpoint_trap
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\exception.cpp
_TEXT	SEGMENT
vector$ = 48
param$ = 56
?nmi_trap@@YAX_KPEAX@Z PROC				; nmi_trap

; 46   : void nmi_trap (size_t vector, void* param){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 47   : 	x64_cli();

	call	x64_cli

; 48   : 	panic("\nNMI [Non-Muskable-Interrupt] Trap");

	lea	rcx, OFFSET FLAT:$SG3430
	call	?panic@@YAXPEBDZZ			; panic
$LN2@nmi_trap:

; 49   : 	for(;;);

	jmp	SHORT $LN2@nmi_trap

; 50   : 
; 51   : }

	add	rsp, 40					; 00000028H
	ret	0
?nmi_trap@@YAX_KPEAX@Z ENDP				; nmi_trap
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\exception.cpp
_TEXT	SEGMENT
frame$ = 32
vector$ = 64
param$ = 72
?single_step_trap@@YAX_KPEAX@Z PROC			; single_step_trap

; 39   : void single_step_trap(size_t vector, void* param) {

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 40   : 	x64_cli();

	call	x64_cli

; 41   : 	interrupt_stack_frame *frame = (interrupt_stack_frame*)param;

	mov	rax, QWORD PTR param$[rsp]
	mov	QWORD PTR frame$[rsp], rax

; 42   : 	panic ("\nSingle Step Trap");

	lea	rcx, OFFSET FLAT:$SG3422
	call	?panic@@YAXPEBDZZ			; panic
$LN2@single_ste:

; 43   : 	for(;;);

	jmp	SHORT $LN2@single_ste

; 44   : }

	add	rsp, 56					; 00000038H
	ret	0
?single_step_trap@@YAX_KPEAX@Z ENDP			; single_step_trap
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\exception.cpp
_TEXT	SEGMENT
frame$ = 32
vector$ = 64
param$ = 72
?divide_by_zero_fault@@YAX_KPEAX@Z PROC			; divide_by_zero_fault

; 26   : void divide_by_zero_fault(size_t vector, void* param) {

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 27   : 	x64_cli();

	call	x64_cli

; 28   : 	interrupt_stack_frame *frame = (interrupt_stack_frame*)param;

	mov	rax, QWORD PTR param$[rsp]
	mov	QWORD PTR frame$[rsp], rax

; 29   : 	panic ("\nDivide by 0");

	lea	rcx, OFFSET FLAT:$SG3408
	call	?panic@@YAXPEBDZZ			; panic

; 30   : 
; 31   : 	printf ("__PROCESSOR_DATA__\n");

	lea	rcx, OFFSET FLAT:$SG3409
	call	printf

; 32   : 	printf ("RIP -> %x\n", frame->rip);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+16]
	lea	rcx, OFFSET FLAT:$SG3410
	call	printf

; 33   : 	printf ("RSP -> %x\n", frame->rsp);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+40]
	lea	rcx, OFFSET FLAT:$SG3411
	call	printf

; 34   : 	printf ("RFLAGS -> %x\n",frame->rflags);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+32]
	lea	rcx, OFFSET FLAT:$SG3412
	call	printf
$LN2@divide_by_:

; 35   : 
; 36   : 	for(;;);

	jmp	SHORT $LN2@divide_by_

; 37   : }

	add	rsp, 56					; 00000038H
	ret	0
?divide_by_zero_fault@@YAX_KPEAX@Z ENDP			; divide_by_zero_fault
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\exception.cpp
_TEXT	SEGMENT
msg$ = 48
?panic@@YAXPEBDZZ PROC					; panic

; 18   : void panic(const char* msg,...) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+32], r9
	sub	rsp, 40					; 00000028H

; 19   : 	printf ("***ARCH x86_64 : Kernel Panic!!! ***\n");

	lea	rcx, OFFSET FLAT:$SG3398
	call	printf

; 20   : 	printf ("[Aurora Kernel]: We are sorry to say that, a processor invalid exception has occured\n");

	lea	rcx, OFFSET FLAT:$SG3399
	call	printf

; 21   : 	printf ("[Aurora Kernel]: please inform it to the master of the kernel\n");

	lea	rcx, OFFSET FLAT:$SG3400
	call	printf

; 22   : 	printf ("[Aurora Kernel]: Below is the code of exception\n");

	lea	rcx, OFFSET FLAT:$SG3401
	call	printf

; 23   : 	printf (msg);

	mov	rcx, QWORD PTR msg$[rsp]
	call	printf

; 24   : }

	add	rsp, 40					; 00000028H
	ret	0
?panic@@YAXPEBDZZ ENDP					; panic
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\exception.cpp
_TEXT	SEGMENT
?exception_init@@YAXXZ PROC				; exception_init

; 247  :  void exception_init () {

$LN3:
	sub	rsp, 40					; 00000028H

; 248  : 	 setvect(0,divide_by_zero_fault);

	lea	rdx, OFFSET FLAT:?divide_by_zero_fault@@YAX_KPEAX@Z ; divide_by_zero_fault
	xor	ecx, ecx
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 249  : 	 setvect(1,single_step_trap);

	lea	rdx, OFFSET FLAT:?single_step_trap@@YAX_KPEAX@Z ; single_step_trap
	mov	ecx, 1
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 250  : 	 setvect(2,nmi_trap);

	lea	rdx, OFFSET FLAT:?nmi_trap@@YAX_KPEAX@Z	; nmi_trap
	mov	ecx, 2
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 251  : 	 setvect(3,breakpoint_trap);

	lea	rdx, OFFSET FLAT:?breakpoint_trap@@YAX_KPEAX@Z ; breakpoint_trap
	mov	ecx, 3
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 252  : 	 setvect(4,overflow_trap);

	lea	rdx, OFFSET FLAT:?overflow_trap@@YAX_KPEAX@Z ; overflow_trap
	mov	ecx, 4
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 253  : 	 setvect(5,bounds_check_fault);

	lea	rdx, OFFSET FLAT:?bounds_check_fault@@YAX_KPEAX@Z ; bounds_check_fault
	mov	ecx, 5
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 254  : 	 setvect(6,invalid_opcode_fault);

	lea	rdx, OFFSET FLAT:?invalid_opcode_fault@@YAX_KPEAX@Z ; invalid_opcode_fault
	mov	ecx, 6
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 255  : 	 setvect(7, no_device_fault);

	lea	rdx, OFFSET FLAT:?no_device_fault@@YAX_KPEAX@Z ; no_device_fault
	mov	ecx, 7
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 256  : 	 setvect(8, double_fault_abort);

	lea	rdx, OFFSET FLAT:?double_fault_abort@@YAX_KPEAX@Z ; double_fault_abort
	mov	ecx, 8
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 257  : 	 setvect(10, invalid_tss_fault);

	lea	rdx, OFFSET FLAT:?invalid_tss_fault@@YAX_KPEAX@Z ; invalid_tss_fault
	mov	ecx, 10
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 258  : 	 setvect(11, no_segment_fault);

	lea	rdx, OFFSET FLAT:?no_segment_fault@@YAX_KPEAX@Z ; no_segment_fault
	mov	ecx, 11
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 259  : 	 setvect(12, stack_fault);

	lea	rdx, OFFSET FLAT:?stack_fault@@YAX_KPEAX@Z ; stack_fault
	mov	ecx, 12
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 260  : 	 setvect(13, general_protection_fault);

	lea	rdx, OFFSET FLAT:?general_protection_fault@@YAX_KPEAX@Z ; general_protection_fault
	mov	ecx, 13
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 261  : 	 setvect(14, page_fault);

	lea	rdx, OFFSET FLAT:?page_fault@@YAX_KPEAX@Z ; page_fault
	mov	ecx, 14
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 262  : 	 setvect(16, fpu_fault);

	lea	rdx, OFFSET FLAT:?fpu_fault@@YAX_KPEAX@Z ; fpu_fault
	mov	ecx, 16
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 263  : 	 setvect(17, alignment_check_fault);

	lea	rdx, OFFSET FLAT:?alignment_check_fault@@YAX_KPEAX@Z ; alignment_check_fault
	mov	ecx, 17
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 264  : 	 setvect(18, machine_check_abort);

	lea	rdx, OFFSET FLAT:?machine_check_abort@@YAX_KPEAX@Z ; machine_check_abort
	mov	ecx, 18
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 265  : 	 setvect(19, simd_fpu_fault);

	lea	rdx, OFFSET FLAT:?simd_fpu_fault@@YAX_KPEAX@Z ; simd_fpu_fault
	mov	ecx, 19
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 266  :  }

	add	rsp, 40					; 00000028H
	ret	0
?exception_init@@YAXXZ ENDP				; exception_init
_TEXT	ENDS
END
