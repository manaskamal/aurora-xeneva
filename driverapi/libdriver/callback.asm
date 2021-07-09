;; 
;;   Copyright (C) Manas Kamal Choudhury 2021
;;
;;   _low_level.asm -- Machine Level assembly codes
;;                     for x86_64 
;;
;;   /PROJECT -- Aurora v1.0 {Xeneva}
;;   /AUTHOR  -- Manas Kamal Choudhury
;;
;; ===========================================================
;;

section .text
[BITS 64]

;----------------------------------------
; Port functions
;----------------------------------------

global x64_inportb
x64_inportb:
      mov dx, cx
	  in  al, dx
	  ret

global x64_inportw
x64_inportw:
      mov dx, cx
	  in  ax, dx
	  ret

global x64_inportd
x64_inportd:
      mov dx, cx
	  in  eax, dx
	  ret


global x64_outportb
x64_outportb:
      mov al, dl
	  mov dx, cx
	  out dx, al
	  ret

global x64_outportw
x64_outportw:
      mov ax, dx
	  mov dx, cx
	  out dx, ax
	  ret

global x64_outportd
x64_outportd:
      mov eax, edx
	  mov dx, cx
	  out dx, eax
	  ret


	  
;--------------------------------------------------
; Interrupt flags
;--------------------------------------------------
global x64_cli
x64_cli:
     cli
	 ret

global x64_sti
x64_sti:
     sti
	 ret