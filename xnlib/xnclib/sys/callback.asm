;; =======================================================
;;  Copyright (C) Manas Kamal Choudhury 2021
;;
;;  /PROJECT - Aurora's Xeneva
;;  /AUTHOR  - Manas Kamal Choudhury
;;
;; =======================================================
;;

section .text
[BITS 64]

;;=========================================================
;; Memory Stuffs
;;=========================================================

global mmap
mmap:
   mov r12, 29
   mov r13, rcx
   mov r14, rdx
   mov r15, r8
   syscall
   ret

global munmap
munmap:
   mov r12, 30
   mov r13, rcx
   mov r14, rdx
   syscall
   ret

global valloc
valloc:
    mov r12, 5
	mov r13, rcx
	syscall
	ret

global sys_exit
sys_exit:
    mov r12, 25
	syscall
	ret

global sys_print_text
sys_print_text:
    mov r12, 0
	mov r13, rcx
	mov r14, rdx
	mov r15, r8
	syscall
	ret


global sys_wait
sys_wait:
    mov r12, 1
	syscall
	ret


global ioquery
ioquery:
    mov r12, 31
	mov r13, rcx
	mov r14, rdx
	mov r15, r8
	syscall
	ret
