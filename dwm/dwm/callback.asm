section .text
[BITS 64]

global print_text
print_text:
    mov r12, 0
	mov r13, rcx
	mov r14, rdx
	mov r15, r8
	syscall
	ret

global sched_wait
sched_wait:
    mov r12, 1
	syscall
	ret

global create_process
create_process:
    mov r12, 2
	mov r13, rcx
	syscall
	ret

global mutex_test
mutex_test:
    mov r12, 3
	syscall
	ret

global get_screen_width
get_screen_width:
    mov r12, 3
	syscall
	ret

global get_screen_height
get_screen_height:
    mov r12, 4
	syscall
	ret

global valloc
valloc:
    mov r12, 5
	mov r13, rcx
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


global map_shared_memory
map_shared_memory:
    mov r12, 8
	mov r13, rcx
	mov r14, rdx
	mov r15, r8
	syscall
	ret

global get_current_pid
get_current_pid
    mov r12, 9
	syscall
	ret

global dwm_put_message
dwm_put_message:
    mov r12, 10
	mov r13, rcx
	syscall
	ret

global dwm_dispatch_message
dwm_dispatch_message:
    mov r12, 11
	mov r13, rcx
	syscall
	ret

global sys_get_fb_mem
sys_get_fb_mem:
    mov r12, 12
	syscall
	ret

global sys_fb_update
sys_fb_update:
    mov r12, 13
	syscall
	ret

global sys_set_mouse_data
sys_set_mouse_data:
    mov r12, 14
	mov r13, rcx
	syscall
	ret

global sys_get_mouse_pack
sys_get_mouse_pack:
    mov r12, 15
	mov r13, rcx
	syscall
	ret

global sys_move_cursor
sys_move_cursor:
    mov r12, 16
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

global sys_create_uthread
sys_create_uthread:
    mov r12, 18
	mov r13, rcx
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


;;==========================================
;;An utility function
;;==========================================
global swap_byte
swap_byte:
      mov rax, rcx
      bswap rax
	  ret

global swap_word
swap_word:
      mov rax, rcx
	  rol rax, 8
	  ret
