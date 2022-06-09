;;-------------------------------------------------------------
;;  Copyright (C) Manas Kamal Choudhury 2022
;;
;;  sse2.asm -- SSE functions
;;
;;  /PROJECT - Aurora's Xeneva
;;  /AUTHOR  - Manas Kamal Choudhury
;;
;;--------------------------------------------------------------

[BITS 64]
section .text

global memcpy_sse2
export memcpy_sse2
memcpy_sse2:
     and cl, 0xF0
	 add rcx, 0x10
	 and dl, 0xF0
	 add rdx, 0x10
     xor rax, rax
	 mov rsi, rdx
	 mov rdi, rcx
	 mov rcx, r8
	 test rcx, rcx
	 jz ._ret
._loop:
     movdqa xmm0, [rsi + rax]
	 movdqa [rdi + rax], xmm0

	 add rax, 0x10
	 loop ._loop
._ret:
     ret

global memset_sse2
export memset_sse2
memset_sse2:
     and cl, 0xF0
	 add rcx, 0x10
	 and dl, 0xF0
	 add rdx, 0x10
     xor rax, rax
	 mov rsi, rdx
	 mov rdi, rcx
	 
	 mov rcx, r8

	 cmp rcx, 1
	 jle .ret

	 movq xmm1, rsi
	 pxor xmm0, xmm0

	 paddq xmm0, xmm1
	 pslldq xmm0, 4
	 paddq xmm0, xmm1
	 pslldq xmm0, 4
	 paddq xmm0, xmm1
	 pslldq xmm0, 4
	 paddq xmm0, xmm1

.loop:
     movdqa [rdi], xmm0
	 add rdi, 0x10
	 loop .loop

.ret:
     ret

