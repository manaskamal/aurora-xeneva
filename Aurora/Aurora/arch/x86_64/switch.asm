;;============================================================
;; Copyright (C) Manas Kamal Choudhury 2021
;;
;; switch.asm -- Task Switching code
;;
;; /PROJECT - Aurora {Xeneva}
;; /AUTHOR  - Manas Kamal Choudhury
;;
;;===========================================================

section .text
[BITS 64]

;;====================================================
;; Save context saves current registers to a thread
;;====================================================

global save_context
save_context: 
    ;mov r8, [rdx + 0x4]
	;mov [rcx + 0xC8], r8  
	
    mov [rcx + 0x30], rbx     ;;from here to r15
	mov [rcx + 0x48], rsi   
	mov [rcx + 0x50], rdi 
	mov [rcx + 0x58], rbp    ;rflags /rsp 
	mov [rcx + 0x80], r12    ;rsp /ss
	mov [rcx + 0x88], r13    ;ss  /rip
	mov [rcx + 0x90], r14
	mov [rcx + 0x98], r15

	
	mov rdx, [rcx + 0xD0]
	movaps [rdx + 0x00], xmm0
	movaps [rdx + 0x10], xmm1
	movaps [rdx + 0x20], xmm2
	movaps [rdx + 0x30], xmm3
	movaps [rdx + 0x40], xmm4
	movaps [rdx + 0x50], xmm5
	movaps [rdx + 0x60], xmm6
	movaps [rdx + 0x70], xmm7
	;movaps [rdx + 0x80], xmm8
	;movaps [rdx + 0x90], xmm9
	;movaps [rdx + 0xA0], xmm10
	;movaps [rdx + 0xB0], xmm11
	;movaps [rdx + 0xC0], xmm12
	;movaps [rdx + 0xD0], xmm13
	;movaps [rdx + 0xE0], xmm14
	;movaps [rdx + 0xF0], xmm15

	pushfq  
	pop rax
	mov [rcx + 0x10],rax
	
 	pop rdx            ;return address
	mov [rcx + 0x20], rdx

    mov [rcx + 0x08], rsp
	;rsp savings here

	
	xor rax, rax  
	jmp rdx


;=======================================================
; Execute Idle, executes provided thread registers
;=======================================================

global execute_idle
execute_idle:

	mov rbx, [rcx + 0x30]
	mov rsi, [rcx + 0x48]
	mov rdi, [rcx + 0x50]
	mov rbp, [rcx + 0x58]
	mov r12, [rcx + 0x80]
	mov r13, [rcx + 0x88]
	mov r14, [rcx + 0x90]
	mov r15, [rcx + 0x98]
	
	mov ds, [rcx + 0xA0]
	mov es, [rcx + 0xA8]
	mov fs, [rcx + 0xB0]
	mov gs, [rcx + 0xB8]
   
	;mov rax,  [rcx + 0xC8]   ;get the current task rsp0 {kernel mode stack}
	;mov [rdx + 0x4],rax     ;store it in tss, as we are going to enter user mode for user threads
	
	;mov qword[fs:0x20], r8

	mov rdx, [rcx + 0xD0]
	movaps xmm0, [rdx + 0x00]
	movaps xmm1, [rdx + 0x10] 
	movaps xmm2, [rdx + 0x20] 
	movaps xmm3, [rdx + 0x30] 
	movaps xmm4, [rdx + 0x40] 
	movaps xmm5, [rdx + 0x50] 
	movaps xmm6, [rdx + 0x60] 
	movaps xmm7, [rdx + 0x70]
	;movaps xmm8, [rdx + 0x80] 
	;movaps xmm9, [rdx + 0x90] 
	;movaps xmm10, [rdx + 0xA0] 
	;movaps xmm11, [rdx + 0xB0] 
	;movaps xmm12, [rdx + 0xC0] 
	;movaps xmm13, [rdx + 0xD0] 
	;movaps xmm14, [rdx + 0xE0]
	;movaps xmm15, [rdx + 0xF0] 
	
	; returning
    mov r9, 1
	cmp r8, 0
	cmove r8, r9
	mov r9, [rcx + 0x10];
	
	mov r10, [rcx + 0xC0]
	mov cr3, r10

	mov rsp, [rcx + 0x08]
	mov rdx, [rcx + 0x20]
	mov rcx, [rcx + 0x38]
	push r9
	popfq
	jmp rdx


	
	
global force_sched_pic
force_sched_pic:
    int 32
	ret

global force_sched_apic
force_sched_apic:
    int 0x40
	ret