;----------------------------------------------------------------------------------------
;  Copyright (C) Manas Kamal Choudhury 2021
;
;  memcpy -- fast_memcpy operation
;
;  /PROJECT - Xeneva v1.0
;  /AUTHOR  - Manas Kamal Choudhury
;
;-----------------------------------------------------------------------------------------

section .text
[BITS 64]

global memcpy
memcpy:
     mov rax, rcx
	 push rsi
	 push rdi
	 mov rdi,rcx
	 mov rsi,rdx
	 mov rcx,r8
	 rep movsb
	 pop rdi
	 pop rsi
	 ret