;;======================================================
;;   Copyright (C) Manas Kamal Choudhury 2021
;;
;;  backdoor_stuff -- Low Level Assembly
;;
;;  /PROJECT - Aurroa {Xeneva}
;;  /AUTHOR  - Manas Kamal Choudhury 
;;
;; =====================================================

section .text
[BITS 64]

global vm_backdoor_in 
vm_backdoor_in:
    mov eax, 0x564D5868
	mov ebx, ecx
	mov cx, dx
	mov dx, 0x5658
	in eax, dx
	mov r8, rcx
	ret

global vm_backdoor_get_ecx
vm_backdoor_get_ecx:
    mov rax, r8
	ret

global vm_backdoor_get_ebx
vm_backdoor_get_ebx:
   mov eax, ebx
   ret

global vm_backdoor_get_edx
vm_backdoor_get_edx:
   mov eax, edx
   ret

