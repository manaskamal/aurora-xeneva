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
         add esp, 6

         mov eax, cr0
         or  eax, 1
         mov cr0, eax

         hlt
         jmp 0x18:ap_32  ;;FIXME: GDT Issue

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


[BITS 32]
ap_32:
      ; set up 32-bit data/stack segments
      mov ax, 0x20
      mov ds, ax
      mov ss, ax

      ;enable PAE paging (bit 5 of cr4)
      mov eax, cr4
      or  eax, 1 << 5
      mov cr4, eax

      ;enable long mode (bit 8 of EFER) and NXE bit (bit 11)
      mov ecx, 0xc0000080
      rdmsr
      or  eax, 1<<8
      or  eax, 1<<11
      wrmsr

      hlt

      ;set up cr4
      ;mov eax, dword [pml4_address]
      ;mov cr3, eax

      ;enable paging (bit 31 of cr0) and write protection (bit 16)
      ;mov eax, cr0
     ; or  eax, 1<<31
      ;or  eax, 1<<16
      ;mov cr0, eax

      