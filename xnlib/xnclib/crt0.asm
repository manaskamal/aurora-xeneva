;; =======================================================
;;  Copyright (C) Manas Kamal Choudhury 2021
;;
;; /PROJECT - Aurora Xeneva
;; /AUTHOR  - Manas Kamal Choudhury 
;;
;; ========================================================

extern heap_initialize_allocator
extern sys_exit
extern main

section .text
[BITS 64]


global _start
_start:
     mov rsi, rcx
	 mov rdi, rdx

	 call heap_initialize_allocator

	 sub rsp, 32
	 mov rcx, rsi
	 mov rdx, rdi
	 call main
	 add rsp, 32

	 ;;//exit process
	 ;;//with a return code
	 call sys_exit

