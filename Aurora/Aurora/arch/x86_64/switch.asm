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