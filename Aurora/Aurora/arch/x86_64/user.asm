;;======================================================
;;  Copyright (C) Manas Kamal Choudhury 2021
;;
;;  user64.asm -- User Level code for arch x86_64
;;
;;  /PROJECT - Aurora {Xeneva }
;;  /AUTHOR  - Manas Kamal Choudhury
;;
;; -----------------------------------------------------

extern  x64_syscall_handler
extern  funct
extern  syscall_debug
extern  current_thread
section .text
[BITS 64]


;;===========================================================
;;  System Call Entries
;;===========================================================

global syscall_entry
syscall_entry:
     ;RCX : return address
	 ;R11 : FLAGS
	 
	 mov rdx, rsp         ;we save the user stack
	 mov r9, [rel current_thread]
	 ;mov [r9 + 0xD0], rdx
	 mov rsp, [r9 + 0xC8]
	 mov r10, rdx ;[rel current_thread]   ;store the user stack in r10 because rdx will be modified
	 ;mov rsp, qword[fs:0x20]    ;load kernel stack
	 swapgs

	 ;save syscall return stuff
	 push rcx
	 push rdx
	 push r11
	 push rbp
	 mov  rbp, rsp
    
	 ;align the stack
	 and sp, 0xFFF0
	 ;kernel
	 sti

	 sub rsp, 40
	 mov rcx, r12
	 call  x64_syscall_handler
	 mov rcx, r13
	 mov rdx, r14
	 mov r8, r15
	 mov r9, rdi

	 mov rax, [r10 + 40]    ;get other parameters from user stack
	 mov [rsp + 32], rax    ;store it in kernel stack
	 mov rax, [r10 + 48]    ;get other parameters from user stack
	 mov [rsp + 40], rax    ;store it in kernel stack
	 call [rel funct]
	
	 add rsp, 40

	 ;return 
	 cli

	 mov rsp, rbp
	 pop rbp
	 pop r11
	 pop rdx
	 pop rcx

	 swapgs

	 ;user stack
	; mov r10, [rel current_thread]
	 mov rsp, r10 ;[r10 + 0xD0]
	 o64 sysret




x64_compat_common:
     sti
	 call x64_syscall_handler
	 cli
	 ret

global x64_syscall_entry_compat
x64_syscall_entry_compat:
     mov rdx, rsp
	 mov rsp, [fs:0x20]
	 swapgs
	 call x64_compat_common
	 swapgs
	 mov rsp, rdx
	 sysret

global sig_ret
sig_ret:
     mov r12, 26
	 syscall
	 ret


;;=====================================================
;;  User Space Entries
;;=====================================================
