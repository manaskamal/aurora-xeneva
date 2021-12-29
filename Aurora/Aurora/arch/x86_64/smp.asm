;;
;; COPYRIGHT (C) Manas Kamal Choudhury 2020-present
;; /PROJECT - Aurora's Xeneva v1.0
;; /AUTHOR  - Manas Kamal Choudhury
;;
;;------------------------------------------------------
section .text
[BITS 16]

ap_trampoline:
         cli
	 xor ax, ax
	 mov ds, ax
	 mov es, ax
	 mov ax, 0x0000
	 mov ss, ax
	 mov sp, 0xFFFF

         push dword gdt_address
         push word gdt_limit
         lgdt [esp]

	 hlt


gdt_address:
	; NULL selector
	dq 0
	; 64-bit code selector
	dq 0x0020980000000000
	; 64-bit data selector
	dq 0x0000920000000000
	; 32-bit code selector
	dq 0x00cf98000000ffff
	; 32-bit data selector
	dq 0x00cf92000000ffff

gdt_limit equ 39
