section .text
[BITS 64]

global sys_link_libs
sys_link_libs:
    mov r12, 8
	sub rsp, 32
	syscall
	add rsp, 32
	ret
