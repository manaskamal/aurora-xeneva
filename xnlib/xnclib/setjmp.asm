;;-------------------------------------------------------
;;  Copyright (C) Manas Kamal Choudhury
;;
;;  /PROJECT - Aurora's Xeneva
;;  /AUTHOR  - Manas Kamal Choudhury
;;
;;-------------------------------------------------------

section .text
[BITS 64]

global setjmp
export setjmp
setjmp:
     mov [rcx], rbx
	 mov [rcx + 8], rbp
	 mov [rcx + 16], r12
	 mov [rcx + 24], r13
	 mov [rcx + 32], r14
	 mov [rcx + 40],r15
	 pop r15
	 mov rdx, rsp
	 mov [rcx + 48], rdx
	 push r15
	 mov rdx,[rsp]
	 mov [rcx + 56], rdx
	 xor eax, eax
	 ret
	 

global longjmp
export longjmp
longjmp:
     xor rax, rax
	 cmp rdx, 1
	 adc rax, rdx
	 mov rbx, [rcx]
	 mov rbp, [rcx + 8]
	 mov r12, [rcx + 16]
	 mov r13, [rcx + 24]
	 mov r14, [rcx + 32]
	 mov r15, [rcx + 40]
	 mov rsp, [rcx + 48]
	 jmp [rcx + 56] 