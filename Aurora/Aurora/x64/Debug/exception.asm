; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

include listing.inc

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

CONST	SEGMENT
$SG5734	DB	'***ARCH x86_64 : Exception Occured ***', 0aH, 00H
$SG5737	DB	'[Aurora Kernel]: Below is the code of exception', 0aH, 00H
	ORG $+7
$SG5735	DB	'[Aurora Kernel]: We are sorry to say that, a processor i'
	DB	'nvalid exception has occured', 0aH, 00H
	ORG $+2
$SG5736	DB	'[Aurora Kernel]: please inform it to the master of the k'
	DB	'ernel', 0aH, 00H
	ORG $+1
$SG5742	DB	0aH, 'Divide by 0', 00H
	ORG $+3
$SG5752	DB	0aH, 'Single Step Trap', 00H
	ORG $+6
$SG5760	DB	0aH, 'NMI [Non-Muskable-Interrupt] Trap', 00H
	ORG $+5
$SG5768	DB	0aH, 'Breakpoint Trap', 00H
	ORG $+7
$SG5776	DB	0aH, 'Overflow Trap', 00H
	ORG $+1
$SG5784	DB	0aH, 'Bound Check Fault', 00H
	ORG $+5
$SG5794	DB	'Invalid Opcode Fault', 0aH, 00H
	ORG $+2
$SG5795	DB	'__PROCESSOR TRACE__', 0aH, 00H
	ORG $+3
$SG5796	DB	'RIP -> %x', 0aH, 00H
	ORG $+5
$SG5797	DB	'Stack -> %x', 0aH, 00H
	ORG $+3
$SG5798	DB	'RFLAGS -> %x', 0aH, 00H
	ORG $+2
$SG5799	DB	'CS -> %x', 0aH, 00H
	ORG $+6
$SG5800	DB	'SS -> %x', 0aH, 00H
	ORG $+6
$SG5801	DB	'Current task -> %s', 0aH, 00H
	ORG $+4
$SG5809	DB	0aH, 'No Device Fault', 00H
	ORG $+7
$SG5817	DB	0aH, 'Double Fault Abort', 00H
	ORG $+4
$SG5825	DB	0aH, 'Invalid TSS Fault ', 00H
	ORG $+4
$SG5833	DB	0aH, 'No Segment Fault', 00H
	ORG $+6
$SG5841	DB	0aH, 'Stack Fault at ', 00H
	ORG $+7
$SG5851	DB	'Genral Protection Fault', 0aH, 00H
	ORG $+7
$SG5852	DB	'__PROCESSOR TRACE__', 0aH, 00H
	ORG $+3
$SG5853	DB	'RIP -> %x', 0aH, 00H
	ORG $+5
$SG5854	DB	'Stack -> %x', 0aH, 00H
	ORG $+3
$SG5855	DB	'RFLAGS -> %x', 0aH, 00H
	ORG $+2
$SG5856	DB	'Current task ->%s', 0aH, 00H
	ORG $+5
$SG5857	DB	'CS -> %x, SS -> %x', 0aH, 00H
	ORG $+4
$SG5875	DB	'Page Fault ', 0aH, 00H
	ORG $+3
$SG5876	DB	'Faulting Address -> %x', 0aH, 00H
$SG5877	DB	'__PROCESSOR TRACE__', 0aH, 00H
	ORG $+3
$SG5878	DB	'RIP -> %x', 0aH, 00H
	ORG $+5
$SG5879	DB	'Stack -> %x', 0aH, 00H
	ORG $+3
$SG5880	DB	'RFLAGS -> %x', 0aH, 00H
	ORG $+2
$SG5881	DB	'Current thread -> %s', 0aH, 00H
	ORG $+2
$SG5882	DB	'Current Thread id -> %d', 0aH, 00H
	ORG $+7
$SG5883	DB	'CS -> %x, SS -> %x', 0aH, 00H
	ORG $+4
$SG5884	DB	'******Cause********', 0aH, 00H
	ORG $+3
$SG5885	DB	'***User Priviledge fault***', 0aH, 00H
	ORG $+3
$SG5895	DB	'Page Fault ', 0aH, 00H
	ORG $+3
$SG5896	DB	'Faulting Address -> %x', 0aH, 00H
$SG5897	DB	'__PROCESSOR TRACE__', 0aH, 00H
	ORG $+3
$SG5898	DB	'RIP -> %x', 0aH, 00H
	ORG $+5
$SG5899	DB	'Stack -> %x', 0aH, 00H
	ORG $+3
$SG5900	DB	'RFLAGS -> %x', 0aH, 00H
	ORG $+2
$SG5901	DB	'Current thread -> %s', 0aH, 00H
	ORG $+2
$SG5902	DB	'Current Thread id -> %d', 0aH, 00H
	ORG $+7
$SG5903	DB	'CS -> %x, SS -> %x', 0aH, 00H
	ORG $+4
$SG5904	DB	'******Cause********', 0aH, 00H
	ORG $+3
$SG5905	DB	'*** R/W ***', 0aH, 00H
	ORG $+3
$SG5911	DB	'Page Fault ', 0aH, 00H
	ORG $+3
$SG5912	DB	'Faulting Address -> %x', 0aH, 00H
$SG5913	DB	'__PROCESSOR TRACE__', 0aH, 00H
	ORG $+3
$SG5914	DB	'RIP -> %x', 0aH, 00H
	ORG $+5
$SG5915	DB	'Stack -> %x', 0aH, 00H
	ORG $+3
$SG5916	DB	'RFLAGS -> %x', 0aH, 00H
	ORG $+2
$SG5917	DB	'Current thread -> %s', 0aH, 00H
	ORG $+2
$SG5918	DB	'Current Thread id -> %d', 0aH, 00H
	ORG $+7
$SG5919	DB	'CS -> %x, SS -> %x', 0aH, 00H
	ORG $+4
$SG5920	DB	'******Cause********', 0aH, 00H
	ORG $+3
$SG5921	DB	'*** Reserved Page ***', 0aH, 00H
	ORG $+1
$SG5927	DB	'Page Fault ', 0aH, 00H
	ORG $+3
$SG5928	DB	'Faulting Address -> %x', 0aH, 00H
$SG5929	DB	'__PROCESSOR TRACE__', 0aH, 00H
	ORG $+3
$SG5930	DB	'RIP -> %x', 0aH, 00H
	ORG $+5
$SG5931	DB	'Stack -> %x', 0aH, 00H
	ORG $+3
$SG5932	DB	'RFLAGS -> %x', 0aH, 00H
	ORG $+2
$SG5933	DB	'Current thread -> %s', 0aH, 00H
	ORG $+2
$SG5934	DB	'Current Thread id -> %d', 0aH, 00H
	ORG $+7
$SG5935	DB	'CS -> %x, SS -> %x', 0aH, 00H
	ORG $+4
$SG5936	DB	'******Cause********', 0aH, 00H
	ORG $+3
$SG5937	DB	'*** Invalid Page ****', 0aH, 00H
	ORG $+1
$SG5945	DB	0aH, 'FPU Fault', 00H
	ORG $+5
$SG5953	DB	0aH, 'Alignment Check Fault at address ', 00H
	ORG $+5
$SG5961	DB	0aH, 'Machine Check Abort', 00H
	ORG $+3
$SG5969	DB	0aH, 'SIMD FPU Fault', 00H
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
EXTRN	?printf@@YAXPEBDZZ:PROC				; printf
EXTRN	x64_cli:PROC
EXTRN	x64_sti:PROC
EXTRN	x64_read_cr2:PROC
EXTRN	?setvect@@YAX_KP6AX0PEAX@Z@Z:PROC		; setvect
EXTRN	?pmmngr_alloc@@YAPEAXXZ:PROC			; pmmngr_alloc
EXTRN	?map_page@@YA_N_K0@Z:PROC			; map_page
EXTRN	?get_current_thread@@YAPEAU_thread_@@XZ:PROC	; get_current_thread
pdata	SEGMENT
$pdata$?exception_init@@YAXXZ DD imagerel $LN3
	DD	imagerel $LN3+322
	DD	imagerel $unwind$?exception_init@@YAXXZ
$pdata$?panic@@YAXPEBDZZ DD imagerel $LN3
	DD	imagerel $LN3+87
	DD	imagerel $unwind$?panic@@YAXPEBDZZ
$pdata$?divide_by_zero_fault@@YAX_KPEAX@Z DD imagerel $LN5
	DD	imagerel $LN5+38
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
	DD	imagerel $LN5+189
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
	DD	imagerel $LN5+177
	DD	imagerel $unwind$?general_protection_fault@@YAX_KPEAX@Z
$pdata$?page_fault@@YAX_KPEAX@Z DD imagerel $LN22
	DD	imagerel $LN22+1085
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
$pdata$?simd_fpu_fault@@YAX_KPEAX@Z DD imagerel $LN5
	DD	imagerel $LN5+38
	DD	imagerel $unwind$?simd_fpu_fault@@YAX_KPEAX@Z
pdata	ENDS
xdata	SEGMENT
$unwind$?exception_init@@YAXXZ DD 010401H
	DD	04204H
$unwind$?panic@@YAXPEBDZZ DD 011801H
	DD	04218H
$unwind$?divide_by_zero_fault@@YAX_KPEAX@Z DD 010e01H
	DD	0420eH
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
	DD	0420eH
xdata	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\exception.cpp
_TEXT	SEGMENT
v$ = 48
p$ = 56
?simd_fpu_fault@@YAX_KPEAX@Z PROC			; simd_fpu_fault

; 227  :  void simd_fpu_fault (size_t v, void* p){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 228  : 	 x64_cli();

	call	x64_cli

; 229  : 	 panic("\nSIMD FPU Fault");

	lea	rcx, OFFSET FLAT:$SG5969
	call	?panic@@YAXPEBDZZ			; panic
$LN2@simd_fpu_f:

; 230  : 	 for(;;);

	jmp	SHORT $LN2@simd_fpu_f

; 231  :  }

	add	rsp, 40					; 00000028H
	ret	0
?simd_fpu_fault@@YAX_KPEAX@Z ENDP			; simd_fpu_fault
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\exception.cpp
_TEXT	SEGMENT
v$ = 48
p$ = 56
?machine_check_abort@@YAX_KPEAX@Z PROC			; machine_check_abort

; 220  : void machine_check_abort (size_t v, void* p){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 221  : 	x64_cli();

	call	x64_cli

; 222  : 	panic("\nMachine Check Abort");

	lea	rcx, OFFSET FLAT:$SG5961
	call	?panic@@YAXPEBDZZ			; panic
$LN2@machine_ch:

; 223  : 	for(;;);

	jmp	SHORT $LN2@machine_ch

; 224  : }

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

; 213  : void alignment_check_fault (size_t v, void* p){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 214  : 	x64_cli();

	call	x64_cli

; 215  : 	panic("\nAlignment Check Fault at address ");

	lea	rcx, OFFSET FLAT:$SG5953
	call	?panic@@YAXPEBDZZ			; panic
$LN2@alignment_:

; 216  : 	for(;;);

	jmp	SHORT $LN2@alignment_

; 217  : }

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

; 205  : void fpu_fault (size_t vector, void* p){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 206  : 	x64_cli();

	call	x64_cli

; 207  : 	panic("\nFPU Fault");

	lea	rcx, OFFSET FLAT:$SG5945
	call	?panic@@YAXPEBDZZ			; panic
$LN2@fpu_fault:

; 208  : 	for(;;);

	jmp	SHORT $LN2@fpu_fault

; 209  : }

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

; 134  : void page_fault (size_t vector, void* param){

$LN22:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 88					; 00000058H

; 135  : 	x64_cli();

	call	x64_cli

; 136  : 	interrupt_stack_frame *frame = (interrupt_stack_frame*)param;

	mov	rax, QWORD PTR param$[rsp]
	mov	QWORD PTR frame$[rsp], rax

; 137  : 	void* vaddr = (void*)x64_read_cr2();

	call	x64_read_cr2
	mov	QWORD PTR vaddr$[rsp], rax

; 138  : 
; 139  : 	int present = !(frame->error & 0x1);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rax, QWORD PTR [rax+8]
	and	rax, 1
	test	rax, rax
	jne	SHORT $LN20@page_fault
	mov	DWORD PTR tv68[rsp], 1
	jmp	SHORT $LN21@page_fault
$LN20@page_fault:
	mov	DWORD PTR tv68[rsp], 0
$LN21@page_fault:
	mov	eax, DWORD PTR tv68[rsp]
	mov	DWORD PTR present$[rsp], eax

; 140  : 	int rw = frame->error & 0x2;

	mov	rax, QWORD PTR frame$[rsp]
	mov	rax, QWORD PTR [rax+8]
	and	rax, 2
	mov	DWORD PTR rw$[rsp], eax

; 141  : 	int us = frame->error & 0x4;

	mov	rax, QWORD PTR frame$[rsp]
	mov	rax, QWORD PTR [rax+8]
	and	rax, 4
	mov	DWORD PTR us$[rsp], eax

; 142  : 	int resv = frame->error & 0x8;

	mov	rax, QWORD PTR frame$[rsp]
	mov	rax, QWORD PTR [rax+8]
	and	rax, 8
	mov	DWORD PTR resv$[rsp], eax

; 143  : 	int id = frame->error & 0x10;

	mov	rax, QWORD PTR frame$[rsp]
	mov	rax, QWORD PTR [rax+8]
	and	rax, 16
	mov	DWORD PTR id$[rsp], eax

; 144  :  //
; 145  : 	
; 146  : 	if (us){

	cmp	DWORD PTR us$[rsp], 0
	je	$LN17@page_fault

; 147  : 		panic ("Page Fault \n");

	lea	rcx, OFFSET FLAT:$SG5875
	call	?panic@@YAXPEBDZZ			; panic

; 148  : 		printf ("Faulting Address -> %x\n", vaddr);

	mov	rdx, QWORD PTR vaddr$[rsp]
	lea	rcx, OFFSET FLAT:$SG5876
	call	?printf@@YAXPEBDZZ			; printf

; 149  : 		printf ("__PROCESSOR TRACE__\n");

	lea	rcx, OFFSET FLAT:$SG5877
	call	?printf@@YAXPEBDZZ			; printf

; 150  : 		printf ("RIP -> %x\n", frame->rip);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+16]
	lea	rcx, OFFSET FLAT:$SG5878
	call	?printf@@YAXPEBDZZ			; printf

; 151  : 		printf ("Stack -> %x\n", frame->rsp);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+40]
	lea	rcx, OFFSET FLAT:$SG5879
	call	?printf@@YAXPEBDZZ			; printf

; 152  : 		printf ("RFLAGS -> %x\n", frame->rflags);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+32]
	lea	rcx, OFFSET FLAT:$SG5880
	call	?printf@@YAXPEBDZZ			; printf

; 153  : 		printf ("Current thread -> %s\n", get_current_thread()->name);

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	mov	rdx, QWORD PTR [rax+216]
	lea	rcx, OFFSET FLAT:$SG5881
	call	?printf@@YAXPEBDZZ			; printf

; 154  : 		printf ("Current Thread id -> %d\n", get_current_thread()->id);

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	movzx	eax, WORD PTR [rax+226]
	mov	edx, eax
	lea	rcx, OFFSET FLAT:$SG5882
	call	?printf@@YAXPEBDZZ			; printf

; 155  : 		printf ("CS -> %x, SS -> %x\n", frame->cs, frame->ss);

	mov	rax, QWORD PTR frame$[rsp]
	mov	r8, QWORD PTR [rax+48]
	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+24]
	lea	rcx, OFFSET FLAT:$SG5883
	call	?printf@@YAXPEBDZZ			; printf

; 156  : 		printf ("******Cause********\n");

	lea	rcx, OFFSET FLAT:$SG5884
	call	?printf@@YAXPEBDZZ			; printf

; 157  : 		printf ("***User Priviledge fault***\n");

	lea	rcx, OFFSET FLAT:$SG5885
	call	?printf@@YAXPEBDZZ			; printf
$LN16@page_fault:

; 158  : 		for(;;);

	jmp	SHORT $LN16@page_fault
	jmp	$LN14@page_fault
$LN17@page_fault:

; 159  : 	}else if (present){

	cmp	DWORD PTR present$[rsp], 0
	je	SHORT $LN13@page_fault

; 160  : 		map_page((uint64_t)pmmngr_alloc(), (uint64_t)vaddr);

	call	?pmmngr_alloc@@YAPEAXXZ			; pmmngr_alloc
	mov	rdx, QWORD PTR vaddr$[rsp]
	mov	rcx, rax
	call	?map_page@@YA_N_K0@Z			; map_page
	jmp	$LN12@page_fault
$LN13@page_fault:

; 161  : 	}else if (rw) {

	cmp	DWORD PTR rw$[rsp], 0
	je	$LN11@page_fault

; 162  : 		panic ("Page Fault \n");

	lea	rcx, OFFSET FLAT:$SG5895
	call	?panic@@YAXPEBDZZ			; panic

; 163  : 		printf ("Faulting Address -> %x\n", vaddr);

	mov	rdx, QWORD PTR vaddr$[rsp]
	lea	rcx, OFFSET FLAT:$SG5896
	call	?printf@@YAXPEBDZZ			; printf

; 164  : 		printf ("__PROCESSOR TRACE__\n");

	lea	rcx, OFFSET FLAT:$SG5897
	call	?printf@@YAXPEBDZZ			; printf

; 165  : 		printf ("RIP -> %x\n", frame->rip);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+16]
	lea	rcx, OFFSET FLAT:$SG5898
	call	?printf@@YAXPEBDZZ			; printf

; 166  : 		printf ("Stack -> %x\n", frame->rsp);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+40]
	lea	rcx, OFFSET FLAT:$SG5899
	call	?printf@@YAXPEBDZZ			; printf

; 167  : 		printf ("RFLAGS -> %x\n", frame->rflags);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+32]
	lea	rcx, OFFSET FLAT:$SG5900
	call	?printf@@YAXPEBDZZ			; printf

; 168  : 		printf ("Current thread -> %s\n", get_current_thread()->name);

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	mov	rdx, QWORD PTR [rax+216]
	lea	rcx, OFFSET FLAT:$SG5901
	call	?printf@@YAXPEBDZZ			; printf

; 169  : 		printf ("Current Thread id -> %d\n", get_current_thread()->id);

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	movzx	eax, WORD PTR [rax+226]
	mov	edx, eax
	lea	rcx, OFFSET FLAT:$SG5902
	call	?printf@@YAXPEBDZZ			; printf

; 170  : 		printf ("CS -> %x, SS -> %x\n", frame->cs, frame->ss);

	mov	rax, QWORD PTR frame$[rsp]
	mov	r8, QWORD PTR [rax+48]
	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+24]
	lea	rcx, OFFSET FLAT:$SG5903
	call	?printf@@YAXPEBDZZ			; printf

; 171  : 		printf ("******Cause********\n");

	lea	rcx, OFFSET FLAT:$SG5904
	call	?printf@@YAXPEBDZZ			; printf

; 172  : 		printf ("*** R/W ***\n");

	lea	rcx, OFFSET FLAT:$SG5905
	call	?printf@@YAXPEBDZZ			; printf
$LN10@page_fault:

; 173  : 		for(;;);

	jmp	SHORT $LN10@page_fault
	jmp	$LN8@page_fault
$LN11@page_fault:

; 174  : 	}else if (resv) {

	cmp	DWORD PTR resv$[rsp], 0
	je	$LN7@page_fault

; 175  : 		panic ("Page Fault \n");

	lea	rcx, OFFSET FLAT:$SG5911
	call	?panic@@YAXPEBDZZ			; panic

; 176  : 		printf ("Faulting Address -> %x\n", vaddr);

	mov	rdx, QWORD PTR vaddr$[rsp]
	lea	rcx, OFFSET FLAT:$SG5912
	call	?printf@@YAXPEBDZZ			; printf

; 177  : 		printf ("__PROCESSOR TRACE__\n");

	lea	rcx, OFFSET FLAT:$SG5913
	call	?printf@@YAXPEBDZZ			; printf

; 178  : 		printf ("RIP -> %x\n", frame->rip);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+16]
	lea	rcx, OFFSET FLAT:$SG5914
	call	?printf@@YAXPEBDZZ			; printf

; 179  : 		printf ("Stack -> %x\n", frame->rsp);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+40]
	lea	rcx, OFFSET FLAT:$SG5915
	call	?printf@@YAXPEBDZZ			; printf

; 180  : 		printf ("RFLAGS -> %x\n", frame->rflags);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+32]
	lea	rcx, OFFSET FLAT:$SG5916
	call	?printf@@YAXPEBDZZ			; printf

; 181  : 		printf ("Current thread -> %s\n", get_current_thread()->name);

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	mov	rdx, QWORD PTR [rax+216]
	lea	rcx, OFFSET FLAT:$SG5917
	call	?printf@@YAXPEBDZZ			; printf

; 182  : 		printf ("Current Thread id -> %d\n", get_current_thread()->id);

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	movzx	eax, WORD PTR [rax+226]
	mov	edx, eax
	lea	rcx, OFFSET FLAT:$SG5918
	call	?printf@@YAXPEBDZZ			; printf

; 183  : 		printf ("CS -> %x, SS -> %x\n", frame->cs, frame->ss);

	mov	rax, QWORD PTR frame$[rsp]
	mov	r8, QWORD PTR [rax+48]
	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+24]
	lea	rcx, OFFSET FLAT:$SG5919
	call	?printf@@YAXPEBDZZ			; printf

; 184  : 		printf ("******Cause********\n");

	lea	rcx, OFFSET FLAT:$SG5920
	call	?printf@@YAXPEBDZZ			; printf

; 185  : 		printf ("*** Reserved Page ***\n");

	lea	rcx, OFFSET FLAT:$SG5921
	call	?printf@@YAXPEBDZZ			; printf
$LN6@page_fault:

; 186  : 		for(;;);

	jmp	SHORT $LN6@page_fault
	jmp	$LN4@page_fault
$LN7@page_fault:

; 187  : 	}else if (id) {

	cmp	DWORD PTR id$[rsp], 0
	je	$LN3@page_fault

; 188  : 		panic ("Page Fault \n");

	lea	rcx, OFFSET FLAT:$SG5927
	call	?panic@@YAXPEBDZZ			; panic

; 189  : 		printf ("Faulting Address -> %x\n", vaddr);

	mov	rdx, QWORD PTR vaddr$[rsp]
	lea	rcx, OFFSET FLAT:$SG5928
	call	?printf@@YAXPEBDZZ			; printf

; 190  : 		printf ("__PROCESSOR TRACE__\n");

	lea	rcx, OFFSET FLAT:$SG5929
	call	?printf@@YAXPEBDZZ			; printf

; 191  : 		printf ("RIP -> %x\n", frame->rip);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+16]
	lea	rcx, OFFSET FLAT:$SG5930
	call	?printf@@YAXPEBDZZ			; printf

; 192  : 		printf ("Stack -> %x\n", frame->rsp);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+40]
	lea	rcx, OFFSET FLAT:$SG5931
	call	?printf@@YAXPEBDZZ			; printf

; 193  : 		printf ("RFLAGS -> %x\n", frame->rflags);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+32]
	lea	rcx, OFFSET FLAT:$SG5932
	call	?printf@@YAXPEBDZZ			; printf

; 194  : 		printf ("Current thread -> %s\n", get_current_thread()->name);

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	mov	rdx, QWORD PTR [rax+216]
	lea	rcx, OFFSET FLAT:$SG5933
	call	?printf@@YAXPEBDZZ			; printf

; 195  : 		printf ("Current Thread id -> %d\n", get_current_thread()->id);

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	movzx	eax, WORD PTR [rax+226]
	mov	edx, eax
	lea	rcx, OFFSET FLAT:$SG5934
	call	?printf@@YAXPEBDZZ			; printf

; 196  : 		printf ("CS -> %x, SS -> %x\n", frame->cs, frame->ss);

	mov	rax, QWORD PTR frame$[rsp]
	mov	r8, QWORD PTR [rax+48]
	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+24]
	lea	rcx, OFFSET FLAT:$SG5935
	call	?printf@@YAXPEBDZZ			; printf

; 197  : 		printf ("******Cause********\n");

	lea	rcx, OFFSET FLAT:$SG5936
	call	?printf@@YAXPEBDZZ			; printf

; 198  : 		printf ("*** Invalid Page ****\n");

	lea	rcx, OFFSET FLAT:$SG5937
	call	?printf@@YAXPEBDZZ			; printf
$LN2@page_fault:

; 199  : 		for(;;);

	jmp	SHORT $LN2@page_fault
$LN3@page_fault:
$LN4@page_fault:
$LN8@page_fault:
$LN12@page_fault:
$LN14@page_fault:

; 200  : 	}
; 201  : }

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

; 118  : void general_protection_fault (size_t v, void* p){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 119  : 	x64_cli();

	call	x64_cli

; 120  : 	interrupt_stack_frame *frame = (interrupt_stack_frame*)p;

	mov	rax, QWORD PTR p$[rsp]
	mov	QWORD PTR frame$[rsp], rax

; 121  : 	panic ("Genral Protection Fault\n");

	lea	rcx, OFFSET FLAT:$SG5851
	call	?panic@@YAXPEBDZZ			; panic

; 122  : 	printf ("__PROCESSOR TRACE__\n");

	lea	rcx, OFFSET FLAT:$SG5852
	call	?printf@@YAXPEBDZZ			; printf

; 123  : 	printf ("RIP -> %x\n",frame->rip);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+16]
	lea	rcx, OFFSET FLAT:$SG5853
	call	?printf@@YAXPEBDZZ			; printf

; 124  : 	printf ("Stack -> %x\n", frame->rsp);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+40]
	lea	rcx, OFFSET FLAT:$SG5854
	call	?printf@@YAXPEBDZZ			; printf

; 125  : 	printf ("RFLAGS -> %x\n", frame->rflags);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+32]
	lea	rcx, OFFSET FLAT:$SG5855
	call	?printf@@YAXPEBDZZ			; printf

; 126  : 	printf ("Current task ->%s\n", get_current_thread()->name);

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	mov	rdx, QWORD PTR [rax+216]
	lea	rcx, OFFSET FLAT:$SG5856
	call	?printf@@YAXPEBDZZ			; printf

; 127  : 	printf ("CS -> %x, SS -> %x\n", frame->cs, frame->ss);

	mov	rax, QWORD PTR frame$[rsp]
	mov	r8, QWORD PTR [rax+48]
	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+24]
	lea	rcx, OFFSET FLAT:$SG5857
	call	?printf@@YAXPEBDZZ			; printf
$LN2@general_pr:

; 128  :     for(;;);

	jmp	SHORT $LN2@general_pr

; 129  : }

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

; 110  : void stack_fault (size_t v, void* p){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 111  : 	x64_cli();

	call	x64_cli

; 112  : 	panic("\nStack Fault at ");

	lea	rcx, OFFSET FLAT:$SG5841
	call	?panic@@YAXPEBDZZ			; panic
$LN2@stack_faul:

; 113  : 	for(;;);

	jmp	SHORT $LN2@stack_faul

; 114  : }

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

; 103  : void no_segment_fault (size_t v, void* p){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 104  : 	x64_cli();

	call	x64_cli

; 105  : 	panic("\nNo Segment Fault");

	lea	rcx, OFFSET FLAT:$SG5833
	call	?panic@@YAXPEBDZZ			; panic
$LN2@no_segment:

; 106  : 	for(;;);

	jmp	SHORT $LN2@no_segment

; 107  : }

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

; 96   : void invalid_tss_fault (size_t v, void* p){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 97   : 	x64_cli();

	call	x64_cli

; 98   : 	panic("\nInvalid TSS Fault ");

	lea	rcx, OFFSET FLAT:$SG5825
	call	?panic@@YAXPEBDZZ			; panic
$LN2@invalid_ts:

; 99   : 	for(;;);

	jmp	SHORT $LN2@invalid_ts

; 100  : }

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

; 89   : void double_fault_abort (size_t v, void* p){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 90   : 	x64_cli();

	call	x64_cli

; 91   : 	panic("\nDouble Fault Abort");

	lea	rcx, OFFSET FLAT:$SG5817
	call	?panic@@YAXPEBDZZ			; panic
$LN2@double_fau:

; 92   : 	for(;;);

	jmp	SHORT $LN2@double_fau

; 93   : }

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

; 82   : void no_device_fault (size_t v, void* p){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 83   : 	x64_cli();

	call	x64_cli

; 84   : 	panic("\nNo Device Fault");

	lea	rcx, OFFSET FLAT:$SG5809
	call	?panic@@YAXPEBDZZ			; panic
$LN2@no_device_:

; 85   : 	for(;;);

	jmp	SHORT $LN2@no_device_

; 86   : }

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

; 67   : void invalid_opcode_fault (size_t v, void* p){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 68   : 	x64_cli();

	call	x64_cli

; 69   : 	interrupt_stack_frame *frame = (interrupt_stack_frame*)p;

	mov	rax, QWORD PTR p$[rsp]
	mov	QWORD PTR frame$[rsp], rax

; 70   : 	panic("Invalid Opcode Fault\n");

	lea	rcx, OFFSET FLAT:$SG5794
	call	?panic@@YAXPEBDZZ			; panic

; 71   : 	printf ("__PROCESSOR TRACE__\n");

	lea	rcx, OFFSET FLAT:$SG5795
	call	?printf@@YAXPEBDZZ			; printf

; 72   : 	printf ("RIP -> %x\n",frame->rip);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+16]
	lea	rcx, OFFSET FLAT:$SG5796
	call	?printf@@YAXPEBDZZ			; printf

; 73   : 	printf ("Stack -> %x\n", frame->rsp);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+40]
	lea	rcx, OFFSET FLAT:$SG5797
	call	?printf@@YAXPEBDZZ			; printf

; 74   : 	printf ("RFLAGS -> %x\n", frame->rflags);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+32]
	lea	rcx, OFFSET FLAT:$SG5798
	call	?printf@@YAXPEBDZZ			; printf

; 75   : 	printf ("CS -> %x\n", frame->cs);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+24]
	lea	rcx, OFFSET FLAT:$SG5799
	call	?printf@@YAXPEBDZZ			; printf

; 76   : 	printf ("SS -> %x\n", frame->ss);

	mov	rax, QWORD PTR frame$[rsp]
	mov	rdx, QWORD PTR [rax+48]
	lea	rcx, OFFSET FLAT:$SG5800
	call	?printf@@YAXPEBDZZ			; printf

; 77   : 	printf ("Current task -> %s\n", get_current_thread()->name);

	call	?get_current_thread@@YAPEAU_thread_@@XZ	; get_current_thread
	mov	rdx, QWORD PTR [rax+216]
	lea	rcx, OFFSET FLAT:$SG5801
	call	?printf@@YAXPEBDZZ			; printf
$LN2@invalid_op:

; 78   : 	for(;;);

	jmp	SHORT $LN2@invalid_op

; 79   : }

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

; 60   : void bounds_check_fault (size_t v, void* p){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 61   : 	x64_cli();

	call	x64_cli

; 62   : 	panic("\nBound Check Fault");

	lea	rcx, OFFSET FLAT:$SG5784
	call	?panic@@YAXPEBDZZ			; panic
$LN2@bounds_che:

; 63   : 	for(;;);

	jmp	SHORT $LN2@bounds_che

; 64   : }

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

; 53   : void overflow_trap (size_t v, void* p){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 54   : 	x64_cli();

	call	x64_cli

; 55   : 	panic("\nOverflow Trap");

	lea	rcx, OFFSET FLAT:$SG5776
	call	?panic@@YAXPEBDZZ			; panic
$LN2@overflow_t:

; 56   : 	for(;;);

	jmp	SHORT $LN2@overflow_t

; 57   : }

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

; 46   : void breakpoint_trap (size_t vector, void* param){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 47   : 	x64_cli();

	call	x64_cli

; 48   : 	panic("\nBreakpoint Trap");

	lea	rcx, OFFSET FLAT:$SG5768
	call	?panic@@YAXPEBDZZ			; panic
$LN2@breakpoint:

; 49   : 	for(;;);

	jmp	SHORT $LN2@breakpoint

; 50   : }

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

; 38   : void nmi_trap (size_t vector, void* param){

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 39   : 	x64_cli();

	call	x64_cli

; 40   : 	panic("\nNMI [Non-Muskable-Interrupt] Trap");

	lea	rcx, OFFSET FLAT:$SG5760
	call	?panic@@YAXPEBDZZ			; panic
$LN2@nmi_trap:

; 41   : 	for(;;);

	jmp	SHORT $LN2@nmi_trap

; 42   : 
; 43   : }

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

; 31   : void single_step_trap(size_t vector, void* param) {

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 56					; 00000038H

; 32   : 	x64_cli();

	call	x64_cli

; 33   : 	interrupt_stack_frame *frame = (interrupt_stack_frame*)param;

	mov	rax, QWORD PTR param$[rsp]
	mov	QWORD PTR frame$[rsp], rax

; 34   : 	panic ("\nSingle Step Trap");

	lea	rcx, OFFSET FLAT:$SG5752
	call	?panic@@YAXPEBDZZ			; panic
$LN2@single_ste:

; 35   : 	for(;;);

	jmp	SHORT $LN2@single_ste

; 36   : }

	add	rsp, 56					; 00000038H
	ret	0
?single_step_trap@@YAX_KPEAX@Z ENDP			; single_step_trap
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\exception.cpp
_TEXT	SEGMENT
vector$ = 48
param$ = 56
?divide_by_zero_fault@@YAX_KPEAX@Z PROC			; divide_by_zero_fault

; 25   : void divide_by_zero_fault(size_t vector, void* param) {

$LN5:
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+8], rcx
	sub	rsp, 40					; 00000028H

; 26   : 	x64_cli();

	call	x64_cli

; 27   : 	panic ("\nDivide by 0");

	lea	rcx, OFFSET FLAT:$SG5742
	call	?panic@@YAXPEBDZZ			; panic
$LN2@divide_by_:

; 28   : 	for(;;);

	jmp	SHORT $LN2@divide_by_

; 29   : }

	add	rsp, 40					; 00000028H
	ret	0
?divide_by_zero_fault@@YAX_KPEAX@Z ENDP			; divide_by_zero_fault
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\exception.cpp
_TEXT	SEGMENT
msg$ = 48
?panic@@YAXPEBDZZ PROC					; panic

; 17   : void panic(const char* msg,...) {

$LN3:
	mov	QWORD PTR [rsp+8], rcx
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+24], r8
	mov	QWORD PTR [rsp+32], r9
	sub	rsp, 40					; 00000028H

; 18   : 	printf ("***ARCH x86_64 : Exception Occured ***\n");

	lea	rcx, OFFSET FLAT:$SG5734
	call	?printf@@YAXPEBDZZ			; printf

; 19   : 	printf ("[Aurora Kernel]: We are sorry to say that, a processor invalid exception has occured\n");

	lea	rcx, OFFSET FLAT:$SG5735
	call	?printf@@YAXPEBDZZ			; printf

; 20   : 	printf ("[Aurora Kernel]: please inform it to the master of the kernel\n");

	lea	rcx, OFFSET FLAT:$SG5736
	call	?printf@@YAXPEBDZZ			; printf

; 21   : 	printf ("[Aurora Kernel]: Below is the code of exception\n");

	lea	rcx, OFFSET FLAT:$SG5737
	call	?printf@@YAXPEBDZZ			; printf

; 22   : 	printf (msg);

	mov	rcx, QWORD PTR msg$[rsp]
	call	?printf@@YAXPEBDZZ			; printf

; 23   : }

	add	rsp, 40					; 00000028H
	ret	0
?panic@@YAXPEBDZZ ENDP					; panic
_TEXT	ENDS
; Function compile flags: /Odtpy
; File e:\xeneva project\xeneva\aurora\aurora\arch\x86_64\exception.cpp
_TEXT	SEGMENT
?exception_init@@YAXXZ PROC				; exception_init

; 233  :  void exception_init () {

$LN3:
	sub	rsp, 40					; 00000028H

; 234  : 	 x64_cli ();

	call	x64_cli

; 235  : 	 setvect(0,divide_by_zero_fault);

	lea	rdx, OFFSET FLAT:?divide_by_zero_fault@@YAX_KPEAX@Z ; divide_by_zero_fault
	xor	ecx, ecx
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 236  : 	 setvect(1,single_step_trap);

	lea	rdx, OFFSET FLAT:?single_step_trap@@YAX_KPEAX@Z ; single_step_trap
	mov	ecx, 1
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 237  : 	 setvect(2,nmi_trap);

	lea	rdx, OFFSET FLAT:?nmi_trap@@YAX_KPEAX@Z	; nmi_trap
	mov	ecx, 2
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 238  : 	 setvect(3,breakpoint_trap);

	lea	rdx, OFFSET FLAT:?breakpoint_trap@@YAX_KPEAX@Z ; breakpoint_trap
	mov	ecx, 3
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 239  : 	 setvect(4,overflow_trap);

	lea	rdx, OFFSET FLAT:?overflow_trap@@YAX_KPEAX@Z ; overflow_trap
	mov	ecx, 4
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 240  : 	 setvect(5,bounds_check_fault);

	lea	rdx, OFFSET FLAT:?bounds_check_fault@@YAX_KPEAX@Z ; bounds_check_fault
	mov	ecx, 5
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 241  : 	 setvect(6,invalid_opcode_fault);

	lea	rdx, OFFSET FLAT:?invalid_opcode_fault@@YAX_KPEAX@Z ; invalid_opcode_fault
	mov	ecx, 6
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 242  : 	 setvect(7, no_device_fault);

	lea	rdx, OFFSET FLAT:?no_device_fault@@YAX_KPEAX@Z ; no_device_fault
	mov	ecx, 7
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 243  : 	 setvect(8, double_fault_abort);

	lea	rdx, OFFSET FLAT:?double_fault_abort@@YAX_KPEAX@Z ; double_fault_abort
	mov	ecx, 8
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 244  : 	 setvect(10, invalid_tss_fault);

	lea	rdx, OFFSET FLAT:?invalid_tss_fault@@YAX_KPEAX@Z ; invalid_tss_fault
	mov	ecx, 10
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 245  : 	 setvect(11, no_segment_fault);

	lea	rdx, OFFSET FLAT:?no_segment_fault@@YAX_KPEAX@Z ; no_segment_fault
	mov	ecx, 11
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 246  : 	 setvect(12, stack_fault);

	lea	rdx, OFFSET FLAT:?stack_fault@@YAX_KPEAX@Z ; stack_fault
	mov	ecx, 12
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 247  : 	 setvect(13, general_protection_fault);

	lea	rdx, OFFSET FLAT:?general_protection_fault@@YAX_KPEAX@Z ; general_protection_fault
	mov	ecx, 13
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 248  : 	 setvect(14, page_fault);

	lea	rdx, OFFSET FLAT:?page_fault@@YAX_KPEAX@Z ; page_fault
	mov	ecx, 14
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 249  : 	 setvect(16, fpu_fault);

	lea	rdx, OFFSET FLAT:?fpu_fault@@YAX_KPEAX@Z ; fpu_fault
	mov	ecx, 16
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 250  : 	 setvect(17, alignment_check_fault);

	lea	rdx, OFFSET FLAT:?alignment_check_fault@@YAX_KPEAX@Z ; alignment_check_fault
	mov	ecx, 17
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 251  : 	 setvect(18, machine_check_abort);

	lea	rdx, OFFSET FLAT:?machine_check_abort@@YAX_KPEAX@Z ; machine_check_abort
	mov	ecx, 18
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 252  : 	 setvect(19, simd_fpu_fault);

	lea	rdx, OFFSET FLAT:?simd_fpu_fault@@YAX_KPEAX@Z ; simd_fpu_fault
	mov	ecx, 19
	call	?setvect@@YAX_KP6AX0PEAX@Z@Z		; setvect

; 253  : 	 x64_sti();

	call	x64_sti

; 254  :  }

	add	rsp, 40					; 00000028H
	ret	0
?exception_init@@YAXXZ ENDP				; exception_init
_TEXT	ENDS
END
