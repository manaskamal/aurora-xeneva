;;
;; BSD 2-Clause License
;;
;; Copyright (c) 2021, Manas Kamal Choudhury
;; All rights reserved.
;;
;; Redistribution and use in source and binary forms, with or without
;; modification, are permitted provided that the following conditions are met:
;;
;; 1. Redistributions of source code must retain the above copyright notice, this
;;    list of conditions and the following disclaimer.
;;
;; 2. Redistributions in binary form must reproduce the above copyright notice,
;;    this list of conditions and the following disclaimer in the documentation
;;    and/or other materials provided with the distribution.
;;
;; THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
;; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
;; IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
;; DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
;; FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
;; DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
;; SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
;; CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
;; OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
;; OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;;
;; /PROJECT - Aurora's Xeneva v1.0
;; @callback.asm -- system call interface for xnclib
;;
;;=====================================================================================

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

global sys_kill
sys_kill:
    mov r12, 34
	mov r13, rcx
	mov r14, rdx
	syscall
	ret

global sys_set_signal
sys_set_signal:
    mov r12, 35
	mov r13, rcx
	mov r14, rdx
	syscall
	ret

global sys_unmap_sh_mem 
sys_unmap_sh_mem:
    mov r12, 36
	mov r13, rcx
	mov r14, rdx
	mov r15, r8
	syscall
	ret

global sys_get_used_ram 
sys_get_used_ram:
    mov r12, 22
	syscall
	ret

global sys_write_file 
sys_write_file:
    mov r12, 37
	mov r13, rcx
	mov r14, rdx
	mov r15, r8
	syscall
	ret

global sys_ttype_create
sys_ttype_create:
    mov r12,13
	mov r13, rcx
	mov r14, rdx
	syscall
	ret

global sys_attach_tty
sys_attach_tty:
    mov r12,26
	mov r13,rcx
	syscall
	ret

global sys_pipe
sys_pipe:
    mov r12, 16
	mov r13, rcx
	mov r14, rdx
	syscall
	ret

global vfree
vfree:
    mov r12, 38
	mov r13, rcx
	syscall
	ret


global sys_get_free_ram 
sys_get_free_ram: 
    mov r12, 23
	syscall
	ret


global sys_create_timer
sys_create_timer:
    mov r12, 10
	mov r13, rcx
	mov r14, rdx
	syscall
	ret

global sys_destroy_timer
sys_destroy_timer:
    mov r12, 11
	mov r13, rcx
	syscall
	ret


global sys_start_timer
sys_start_timer:
    mov r12, 14
	mov r13, rcx
	syscall
	ret

global sys_pause_timer
sys_pause_timer:
    mov r12, 15
	mov r13, rcx
	syscall
	ret

global sys_ttype_dup
sys_ttype_dup:
    mov r12, 21
	mov r13, rcx
	mov r14, rdx
	syscall
	ret

global sys_copy_mem
sys_copy_mem:
    mov r12, 3
	mov r13, rcx
	mov r14, rdx
	mov r15, r8
	syscall
	ret


