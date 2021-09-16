;;=======================================================
;;  Copyright (C) Manas Kamal Choudhury 2021
;;
;;  _fast_copy.asm -- Memcpy definition
;;
;;  /PROJECT - Aurora's Xneva
;;  /AUTHOR  - Manas Kamal Choudhury
;;
;;=======================================================


section .text
[BITS 64]

global fastcpy
fastcpy:
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