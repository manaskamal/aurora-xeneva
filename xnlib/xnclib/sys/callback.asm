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

global create_process
create_process:
    mov r12, 2
	mov r13, rcx
	mov r14, rdx
	syscall
	ret

global message_send
message_send:
    mov r12, 6
	mov r13, rcx
	mov r14, rdx
	syscall
	ret

global message_receive
message_receive:
    mov r12, 7
	mov r13, rcx
	syscall 
	ret


global get_current_pid
get_current_pid
    mov r12, 9
	syscall
	ret


global map_shared_memory
map_shared_memory:
    mov r12, 8
	mov r13, rcx
	mov r14, rdx
	mov r15, r8
	syscall
	ret


global sys_sleep
sys_sleep:
      mov r12, 24
	  mov r13, rcx
	  syscall
	  ret


global create_uthread
create_uthread:
    mov r12, 18
	mov r13, rcx
	mov r14, rdx
	syscall
	ret

global sys_open_file
sys_open_file:
    mov r12, 19
	mov r13, rcx
	mov r14, rdx
	syscall
	ret

global sys_read_file
sys_read_file:
    mov r12, 20
	mov r13, rcx
	mov r14, rdx
	mov r15, r8
	syscall
	ret


global sys_unblock_id
sys_unblock_id:
    mov r12, 17
	mov r13, rcx
	syscall
	ret


global sys_get_current_time
sys_get_current_time:
    mov r12, 32
	mov r13, rcx
	syscall
	ret

global sys_get_system_tick
sys_get_system_tick:
    mov r12, 33
	syscall
	ret






