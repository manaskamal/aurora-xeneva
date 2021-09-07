section .text
[BITS 64]

global shl_print
shl_print:
    mov r12, 0
	mov r13, rcx
	mov r14, rdx
	mov r15, r8
	syscall
	ret

global shl_test
shl_test:
    ret
